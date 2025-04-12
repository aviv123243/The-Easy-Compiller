#include "semantic.hpp"
#include "../symbolTable/symbolTable.hpp"
#include "../token/token.hpp"
#include <vector>

using namespace std;

std::map<SyntaxKind, baseType> assignTerminal = {
    {KEYWORD_INT, INT},
    {KEYWORD_CHAR, CHAR},
    {KEYWORD_FLOAT, FLOAT},
    {INTEGER_LITERAL, INT},
    {CHAR_LITERAL, CHAR},
    {FLOAT_LITERAL, FLOAT}};

SemanticAnalyzer::SemanticAnalyzer(ErrorHandler *errorHandler, SymbolTable *symbolTable) : _errorHandler(errorHandler), _symbolTable(symbolTable)
{
    initAssignActions();
}

void SemanticAnalyzer::updateScope(SyntaxToken *currToken)
{
    if (currToken->kind == SyntaxKind::OPEN_CURLY)
    {
        // entering scope
        scope *newScope = new scope();

        // if the stack is empty it means its a new function
        // so just connect it to the stack knowing it dosent have a parent
        // later wre connect the function to the scope in the updateSymbolTable() func

        if (!_scopeStack.empty())
        {
            scope *oldScope = _scopeStack.top();
            oldScope->addInnerScope(newScope);
        }

        _scopeStack.push(newScope);
        cout << "entering scope" << endl;
        cout << "size of scope stack: " << _scopeStack.size() << endl;
    }
    else if (currToken->kind == SyntaxKind::CLOSED_CURLY)
    {
        // exiting scope
        scope *currScope = _scopeStack.top();
        _scopeStack.pop();

        if (_scopeStack.empty())
            _currRootScope = currScope; // if the stack is empty it means we are at the end of the function

        cout << "exiting scope" << endl;
        cout << "size of scope stack: " << _scopeStack.size() << endl;
    }
}

void SemanticAnalyzer::updateSybolTable(ASTNode *node)
{
    if (node->GetType() == NON_TERMINAL)
    {
        NonTerminalNode *ntNode = (NonTerminalNode *)node;
        if (ntNode->getNonTerminalKind() == FUNCTION_DECL)
        {
            // if we encounter a function declaration we need to procces it correctly in order to update the symbol table

            // get the second child value (name)
            TerminalNode *nameNode = (TerminalNode *)(ntNode->GetChildren()[1]);
            string name = ((TerminalNode *)(ntNode->GetChildren()[1]))->getToken()->val;

            // check if the function already exists in the symbol table
            functionEntry *funcEntry = _symbolTable->getFunction(name);
            if (funcEntry != nullptr)
            {
                _errorHandler->addError(new semanticError("function already declared", nameNode->getToken()));
            }
            else
            {
                // get the seventh child value (the type)
                valType funcVarType = createVarDeclExprType((NonTerminalNode *)(ntNode->GetChildren()[6]));

                // get the forth child value (the types of the function parameters)
                vector<valType> paramTypes = createFunctionParamTypes((NonTerminalNode *)(ntNode->GetChildren()[3]));

                // create the entry
                functionEntry *funcEntry = new functionEntry(name, funcVarType, paramTypes);

                // add the current root scope as their scope
                funcEntry->setInnerScope(_currRootScope);

                // add the the scope their parameters and variables
                vector<tableEntery> paramEntries = createFunctionParamEnteries((NonTerminalNode *)(ntNode->GetChildren()[3]));
                for (int i = 0; i < paramEntries.size(); i++)
                {
                    _currRootScope->printScope();
                    _currRootScope->addTableEntry(paramEntries[i]);
                }

                // and finally, add the function to the table
                _symbolTable->addFunction(funcEntry);
            }
        }

        else if (ntNode->getNonTerminalKind() == VAR_DECL_EXPR)
        {
            // get the current scope
            scope *currScope = _scopeStack.top();

            // add variable to the symbol table
            currScope->addTableEntry(createTableEntery_varDec(ntNode));
        }
    }
}

void SemanticAnalyzer::assignNodeType(ASTNode *node)
{
    if (node->GetType() == NON_TERMINAL)
    {
        NonTerminalNode *ntNode = (NonTerminalNode *)node;
        NonTerminal ntKind = ntNode->getNonTerminalKind();

        if (_nonTerminalAssignActions.find(ntKind) != _nonTerminalAssignActions.end())
        {
            (this->*_nonTerminalAssignActions[ntKind])(node);
        }
    }
    else if (node->GetType() == TERMINAL)
    {
        cout << "HERE";
        TerminalNode *tNode = (TerminalNode *)node;
        SyntaxKind kind = tNode->getToken()->kind;

        if (assignTerminal.find(kind) != assignTerminal.end())
        {
            node->SetValType(valType{assignTerminal[kind], 0, false, false});
        }
    }
}

valType SemanticAnalyzer::checkCompatibilityBinaryOp(valType leftOp, valType rightOp, SyntaxToken *opToken)
{
    valType res = {INT, 0, false, false};
    bool errorOccurred = false;

    if (opToken->kind == PLUS || opToken->kind == MINUS || opToken->kind == STAR || opToken->kind == SLASH)
    {
        if (leftOp.isPointer || rightOp.isPointer)
        {
            if ((opToken->kind == PLUS || opToken->kind == MINUS) &&
                ((leftOp.isPointer && rightOp.type == INT) || (rightOp.isPointer && leftOp.type == INT)))
            {
                res = leftOp.isPointer ? leftOp : rightOp;
            }
            else
            {
                _errorHandler->addError(new semanticError("pointer arithmetic not allowed", opToken));
                errorOccurred = true;
            }
        }
        else if (leftOp.isArray || rightOp.isArray)
        {
            _errorHandler->addError(new semanticError("array arithmetic not allowed", opToken));
            errorOccurred = true;
        }
        else if (leftOp.type == FLOAT || rightOp.type == FLOAT)
        {
            res.type = FLOAT;
        }
        else if (leftOp.type == INT || rightOp.type == INT)
        {
            res.type = INT;
        }
        else if (leftOp.type == CHAR || rightOp.type == CHAR)
        {
            res.type = CHAR;
        }
        else
        {
            _errorHandler->addError(new semanticError("incompatible types for arithmetic", opToken));
            errorOccurred = true;
        }
    }
    else if (opToken->kind == EQUALS_EQUALS || opToken->kind == BANG_EQUALS || opToken->kind == LESS_THAN ||
             opToken->kind == GREATER_THAN || opToken->kind == LESS_THAN_EQUALS || opToken->kind == GREATER_THAN_EQUALS)
    {
        res.type = INT;
        if ((leftOp.isPointer && !rightOp.isPointer) || (!leftOp.isPointer && rightOp.isPointer) ||
            (leftOp.isArray && !rightOp.isArray) || (!leftOp.isArray && rightOp.isArray))
        {
            _errorHandler->addError(new semanticError("incompatible types for comparison", opToken));
            errorOccurred = true;
        }
    }
    else if (opToken->kind == PIPE_PIPE || opToken->kind == AMPERSAND_AMPERSAND)
    {
        res.type = INT;
        if (leftOp.type != INT || rightOp.type != INT)
        {
            _errorHandler->addError(new semanticError("logical operators require int operands", opToken));
            errorOccurred = true;
        }
    }
    else
    {
        _errorHandler->addError(new semanticError("unsupported operator", opToken));
        errorOccurred = true;
    }

    if (errorOccurred)
    {
        res = {UNDIFINED, 0, false, false};
    }

    return res;
}

valType SemanticAnalyzer::checkCompatibilityAssignExp(valType leftOp, valType rightOp, SyntaxToken *opToken)
{
    valType res = leftOp;
    bool errorOccurred = false;

    if (leftOp.isPointer && rightOp.isPointer)
    {
        if (leftOp.type != rightOp.type)
        {
            _errorHandler->addError(new semanticError("incompatible pointer types for assignment", opToken));
            errorOccurred = true;
        }
    }
    else if (leftOp.isPointer && !rightOp.isPointer)
    {
        _errorHandler->addError(new semanticError("cannot assign non-pointer to pointer", opToken));
        errorOccurred = true;
    }
    else if (!leftOp.isPointer && rightOp.isPointer)
    {
        _errorHandler->addError(new semanticError("cannot assign pointer to non-pointer", opToken));
        errorOccurred = true;
    }
    else if (leftOp.isArray || rightOp.isArray)
    {
        _errorHandler->addError(new semanticError("array assignment not allowed", opToken));
        errorOccurred = true;
    }
    else if (leftOp.type == FLOAT && (rightOp.type == FLOAT || rightOp.type == FLOAT))
    {
        res.type = FLOAT;
    }
    else if (leftOp.type == INT && (rightOp.type == INT || rightOp.type == CHAR))
    {
        res.type = INT;
    }
    else if (leftOp.type == CHAR && rightOp.type == CHAR)
    {
        res.type = CHAR;
    }
    else
    {
        _errorHandler->addError(new semanticError("incompatible types for assignment", opToken));
        errorOccurred = true;
    }

    if (errorOccurred)
    {
        res = {UNDIFINED, 0, false, false};
    }

    return res;
}

void SemanticAnalyzer::initAssignActions()
{
    _nonTerminalAssignActions[ASSIGN_EXPR] = &SemanticAnalyzer::assignAssignExprNodeType;
    _nonTerminalAssignActions[ASSIGN_TARGET] = &SemanticAnalyzer::assignAssignTargetNodeType;
    _nonTerminalAssignActions[CONDITION_OP] = &SemanticAnalyzer::assignConditionOpNodeType;
    _nonTerminalAssignActions[EXPR] = &SemanticAnalyzer::assignExprNodeType;
    _nonTerminalAssignActions[LOGICAL_EXPR] = &SemanticAnalyzer::assignLogicalExprNodeType;
    _nonTerminalAssignActions[RELATIONAL_EXPR] = &SemanticAnalyzer::assignRelationalExprNodeType;
    _nonTerminalAssignActions[ADD_EXPR] = &SemanticAnalyzer::assignAddExprNodeType;
    _nonTerminalAssignActions[MUL_EXPR] = &SemanticAnalyzer::assignMulExprNodeType;
    _nonTerminalAssignActions[UNARY_EXPR] = &SemanticAnalyzer::assignUnaryExprNodeType;
    _nonTerminalAssignActions[INCREMENT_EXPR] = &SemanticAnalyzer::assignIncrementExprNodeType;
    _nonTerminalAssignActions[ADDRESS_EXPR] = &SemanticAnalyzer::assignAddressExprNodeType;
    _nonTerminalAssignActions[DEREFERENCE_EXPR] = &SemanticAnalyzer::assignDereferenceExprNodeType;
    _nonTerminalAssignActions[PRIMARY_EXPR] = &SemanticAnalyzer::assignPrimaryExprNodeType;
}

void SemanticAnalyzer::assignParamNodeType(ASTNode *node)
{
    valType resType = {UNDIFINED, 0, false, false};
    NonTerminalNode *ntNode = dynamic_cast<NonTerminalNode *>(node);

    if (ntNode)
    {
        vector<ASTNode *> children = ntNode->GetChildren();
        if (!children.empty())
        {
            resType = children[0]->GetValType();
        }
    }

    node->SetValType(resType);
}

void SemanticAnalyzer::assignTypeNodeType(ASTNode *node)
{
    valType resType = {UNDIFINED, 0, false, false};
    NonTerminalNode *ntNode = dynamic_cast<NonTerminalNode *>(node);

    if (ntNode)
    {
        vector<ASTNode *> children = ntNode->GetChildren();
        if (!children.empty())
        {
            valType baseType = children[0]->GetValType();
            if (children.size() == 1)
            {
                resType = baseType;
            }
            else if (children.size() == 2)
            {
                resType = {baseType.type, baseType.size, true, false};
            }
            else if (children.size() == 4)
            {
                resType = {baseType.type, baseType.size, false, true};
            }
        }
    }

    node->SetValType(resType);
}

void SemanticAnalyzer::assignBaseTypeNodeType(ASTNode *node)
{
    valType resType = {UNDIFINED, 0, false, false};
    NonTerminalNode *ntNode = dynamic_cast<NonTerminalNode *>(node);

    if (ntNode)
    {
        vector<ASTNode *> children = ntNode->GetChildren();
        if (!children.empty())
        {
            resType = children[0]->GetValType();
        }
    }

    node->SetValType(resType);
}

void SemanticAnalyzer::assignVarDeclExprNodeType(ASTNode *node)
{
    valType resType = {UNDIFINED, 0, false, false};
    NonTerminalNode *ntNode = dynamic_cast<NonTerminalNode *>(node);

    if (ntNode)
    {
        vector<ASTNode *> children = ntNode->GetChildren();
        if (children.size() >= 3)
        {
            valType varType = children[0]->GetValType();
            valType initOptType = children[2]->GetValType();
            SyntaxToken *opToken = dynamic_cast<TerminalNode *>(children[1])->getToken();
            resType = SemanticAnalyzer::checkCompatibilityAssignExp(varType, initOptType, opToken);
        }
    }

    node->SetValType(resType);
}

void SemanticAnalyzer::assignInitOptNodeType(ASTNode *node)
{
    valType resType = {UNDIFINED, 0, false, false};
    NonTerminalNode *ntNode = dynamic_cast<NonTerminalNode *>(node);

    if (ntNode)
    {
        vector<ASTNode *> children = ntNode->GetChildren();
        if (!children.empty() && children.size() == 3)
        {
            resType = children[1]->GetValType();
        }
    }

    node->SetValType(resType);
}

void SemanticAnalyzer::assignAssignValueNodeType(ASTNode *node)
{
    valType resType = {UNDIFINED, 0, false, false};
    NonTerminalNode *ntNode = dynamic_cast<NonTerminalNode *>(node);

    if (ntNode)
    {
        vector<ASTNode *> children = ntNode->GetChildren();
        if (!children.empty())
        {
            if (children.size() == 1)
            {
                resType = children[0]->GetValType();
            }
            else if (children.size() == 3)
            {
                valType type = children[1]->GetValType();
                resType = {type.type, type.size, type.isPointer, true};
            }
        }
    }

    node->SetValType(resType);
}

void SemanticAnalyzer::assignAssignExprNodeType(ASTNode *node)
{
    valType resType = {UNDIFINED, 0, false, false};
    NonTerminalNode *ntNode = dynamic_cast<NonTerminalNode *>(node);

    if (ntNode)
    {
        vector<ASTNode *> children = ntNode->GetChildren();
        if (children.size() >= 3)
        {
            valType leftOp = children[0]->GetValType();
            valType rightOp = children[2]->GetValType();
            SyntaxToken *opToken = dynamic_cast<TerminalNode *>(children[1])->getToken();
            resType = SemanticAnalyzer::checkCompatibilityAssignExp(leftOp, rightOp, opToken);
        }
    }

    node->SetValType(resType);
}

void SemanticAnalyzer::assignAssignTargetNodeType(ASTNode *node)
{
    valType resType = {UNDIFINED, 0, false, false};
    NonTerminalNode *ntNode = dynamic_cast<NonTerminalNode *>(node);

    if (ntNode)
    {
        vector<ASTNode *> children = ntNode->GetChildren();
        if (!children.empty())
        {
            if (children.size() == 1)
            {
                resType = children[0]->GetValType();
            }
            else if (children.size() == 4)
            {
                valType arrType = children[0]->GetValType();
                if (!arrType.isArray)
                {
                    _errorHandler->addError(new semanticError("indexing non-array type", dynamic_cast<TerminalNode *>(children[1])->getToken()));
                }
                else
                {
                    resType = {arrType.type, arrType.size, arrType.isPointer, false};
                }
            }
            else if (children.size() == 2)
            {
                valType ptrType = children[1]->GetValType();
                if (!ptrType.isPointer)
                {
                    _errorHandler->addError(new semanticError("dereferencing non-pointer type", dynamic_cast<TerminalNode *>(children[0])->getToken()));
                }
                else
                {
                    resType = {ptrType.type, ptrType.size, false, ptrType.isArray};
                }
            }
        }
    }

    node->SetValType(resType);
}

void SemanticAnalyzer::assignConditionOpNodeType(ASTNode *node)
{
    valType resType = {UNDIFINED, 0, false, false};
    NonTerminalNode *ntNode = dynamic_cast<NonTerminalNode *>(node);

    if (ntNode)
    {
        vector<ASTNode *> children = ntNode->GetChildren();
        if (!children.empty())
        {
            valType condType = children[0]->GetValType();
            if (condType.type != INT && !condType.isPointer)
            {
                _errorHandler->addError(new semanticError("condition must be int or pointer", dynamic_cast<TerminalNode *>(children[0])->getToken()));
            }
            else
            {
                resType = condType;
            }
        }
    }

    node->SetValType(resType);
}

void SemanticAnalyzer::assignExprNodeType(ASTNode *node)
{
    valType resType = {UNDIFINED, 0, false, false};
    NonTerminalNode *ntNode = dynamic_cast<NonTerminalNode *>(node);

    if (ntNode)
    {
        vector<ASTNode *> children = ntNode->GetChildren();
        if (!children.empty())
        {
            resType = children[0]->GetValType();
        }
    }

    node->SetValType(resType);
}

void SemanticAnalyzer::assignLogicalExprNodeType(ASTNode *node)
{
    valType resType = {UNDIFINED, 0, false, false};
    NonTerminalNode *ntNode = dynamic_cast<NonTerminalNode *>(node);

    if (ntNode)
    {
        vector<ASTNode *> children = ntNode->GetChildren();
        if (!children.empty())
        {
            if (children.size() == 1)
            {
                resType = children[0]->GetValType();
            }
            else if (children.size() == 3)
            {
                valType leftOp = children[0]->GetValType();
                valType rightOp = children[2]->GetValType();
                SyntaxToken *opToken = dynamic_cast<TerminalNode *>(children[1])->getToken();
                resType = checkCompatibilityBinaryOp(leftOp, rightOp, opToken);
            }
        }
    }

    node->SetValType(resType);
}

void SemanticAnalyzer::assignRelationalExprNodeType(ASTNode *node)
{
    valType resType = {UNDIFINED, 0, false, false};
    NonTerminalNode *ntNode = dynamic_cast<NonTerminalNode *>(node);

    if (ntNode)
    {
        vector<ASTNode *> children = ntNode->GetChildren();
        if (!children.empty())
        {
            if (children.size() == 1)
            {
                resType = children[0]->GetValType();
            }
            else if (children.size() == 3)
            {
                valType leftOp = children[0]->GetValType();
                valType rightOp = children[2]->GetValType();
                SyntaxToken *opToken = dynamic_cast<TerminalNode *>(children[1])->getToken();
                resType = checkCompatibilityBinaryOp(leftOp, rightOp, opToken);
            }
        }
    }

    node->SetValType(resType);
}

void SemanticAnalyzer::assignAddExprNodeType(ASTNode *node)
{
    valType resType = {UNDIFINED, 0, false, false};
    NonTerminalNode *ntNode = dynamic_cast<NonTerminalNode *>(node);

    if (ntNode)
    {
        vector<ASTNode *> children = ntNode->GetChildren();
        if (!children.empty())
        {
            if (children.size() == 1)
            {
                resType = children[0]->GetValType();
            }
            else if (children.size() == 3)
            {
                valType leftOp = children[0]->GetValType();
                valType rightOp = children[2]->GetValType();
                SyntaxToken *opToken = dynamic_cast<TerminalNode *>(children[1])->getToken();
                resType = checkCompatibilityBinaryOp(leftOp, rightOp, opToken);
            }
        }
    }

    node->SetValType(resType);
}

void SemanticAnalyzer::assignMulExprNodeType(ASTNode *node)
{
    valType resType = {UNDIFINED, 0, false, false};
    NonTerminalNode *ntNode = dynamic_cast<NonTerminalNode *>(node);

    if (ntNode)
    {
        vector<ASTNode *> children = ntNode->GetChildren();
        if (!children.empty())
        {
            if (children.size() == 1)
            {
                resType = children[0]->GetValType();
            }
            else if (children.size() == 3)
            {
                valType leftOp = children[0]->GetValType();
                valType rightOp = children[2]->GetValType();
                SyntaxToken *opToken = dynamic_cast<TerminalNode *>(children[1])->getToken();
                resType = checkCompatibilityBinaryOp(leftOp, rightOp, opToken);
            }
        }
    }

    node->SetValType(resType);
}

void SemanticAnalyzer::assignUnaryExprNodeType(ASTNode *node)
{
    valType resType = {UNDIFINED, 0, false, false};
    NonTerminalNode *ntNode = dynamic_cast<NonTerminalNode *>(node);

    if (ntNode)
    {
        vector<ASTNode *> children = ntNode->GetChildren();
        if (!children.empty())
        {
            if (children.size() == 1)
            {
                resType = children[0]->GetValType();
            }
            else if (children.size() == 2)
            {
                valType operandType = children[1]->GetValType();
                SyntaxToken *opToken = dynamic_cast<TerminalNode *>(children[0])->getToken();
                if (opToken->kind == MINUS)
                {
                    if (operandType.type != INT && operandType.type != FLOAT)
                    {
                        _errorHandler->addError(new semanticError("unary minus requires int or float", opToken));
                    }
                    else
                    {
                        resType = operandType;
                    }
                }
                else if (opToken->kind == BANG)
                {
                    if (operandType.type != INT)
                    {
                        _errorHandler->addError(new semanticError("logical not requires int", opToken));
                    }
                    else
                    {
                        resType = {INT, 0, false, false};
                    }
                }
            }
        }
    }

    node->SetValType(resType);
}

void SemanticAnalyzer::assignIncrementExprNodeType(ASTNode *node)
{
    valType resType = {UNDIFINED, 0, false, false};
    NonTerminalNode *ntNode = dynamic_cast<NonTerminalNode *>(node);

    if (ntNode)
    {
        vector<ASTNode *> children = ntNode->GetChildren();
        if (children.size() >= 2)
        {
            valType operandType = children[children.size() - 1]->GetValType();
            SyntaxToken *opToken = dynamic_cast<TerminalNode *>(children[children.size() - 2])->getToken();
            if (operandType.type != INT && !operandType.isPointer)
            {
                _errorHandler->addError(new semanticError("increment/decrement requires int or pointer", opToken));
            }
            else
            {
                resType = operandType;
            }
        }
    }

    node->SetValType(resType);
}

void SemanticAnalyzer::assignAddressExprNodeType(ASTNode *node)
{
    valType resType = {UNDIFINED, 0, false, false};
    NonTerminalNode *ntNode = dynamic_cast<NonTerminalNode *>(node);

    if (ntNode)
    {
        vector<ASTNode *> children = ntNode->GetChildren();
        if (children.size() == 2)
        {
            valType varType = children[1]->GetValType();
            resType = {varType.type, varType.size, true, varType.isArray};
        }
    }

    node->SetValType(resType);
}

void SemanticAnalyzer::assignDereferenceExprNodeType(ASTNode *node)
{
    valType resType = {UNDIFINED, 0, false, false};
    NonTerminalNode *ntNode = dynamic_cast<NonTerminalNode *>(node);

    if (ntNode)
    {
        vector<ASTNode *> children = ntNode->GetChildren();
        if (children.size() == 2)
        {
            valType ptrType = children[1]->GetValType();
            if (!ptrType.isPointer)
            {
                _errorHandler->addError(new semanticError("dereferencing non-pointer type", dynamic_cast<TerminalNode *>(children[0])->getToken()));
            }
            else
            {
                resType = {ptrType.type, ptrType.size, false, ptrType.isArray};
            }
        }
    }

    node->SetValType(resType);
}

void SemanticAnalyzer::assignPrimaryExprNodeType(ASTNode *node)
{
    valType resType = {UNDIFINED, 0, false, false};
    NonTerminalNode *ntNode = dynamic_cast<NonTerminalNode *>(node);

    if (ntNode)
    {
        vector<ASTNode *> children = ntNode->GetChildren();
        if (!children.empty())
        {
            if (children.size() == 1)
            {
                resType = children[0]->GetValType();
            }

            else if (children.size() == 4 && children[2]->GetType() == GrammarSymbolType::NON_TERMINAL)
            {
                valType arrType = children[0]->GetValType();
                if (!arrType.isArray)
                {
                    _errorHandler->addError(new semanticError("indexing non-array type", dynamic_cast<TerminalNode *>(children[1])->getToken()));
                }
                else
                {
                    resType = {arrType.type, arrType.size, arrType.isPointer, false};
                }
            }

            else if (children.size() == 3)
            {
                resType = children[1]->GetValType();
            }

            else if (children.size() >= 3 && children[1]->GetType() == GrammarSymbolType::TERMINAL &&
                     dynamic_cast<TerminalNode *>(children[1])->getToken()->kind == OPEN_PAREN)
            {
                resType = {INT, 0, false, false}; // Placeholder for function call return type
            }
        }
    }

    node->SetValType(resType);
}