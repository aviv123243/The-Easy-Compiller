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

void SemanticAnalyzer::addFunctionNodeToSymbolTable(NonTerminalNode *funcDeclNode)
{
    /// if we encounter a function declaration we need to procces it correctly in order to update the symbol table

    // get the second child value (name)
    TerminalNode *nameNode = (TerminalNode *)(funcDeclNode->GetChildren()[1]);
    string name = ((TerminalNode *)(funcDeclNode->GetChildren()[1]))->getToken()->val;

    // check if the function already exists in the symbol table
    functionEntry *funcEntry = _symbolTable->getFunction(name);
    if (funcEntry != nullptr)
    {
        _errorHandler->addError(new semanticError("function already declared", nameNode->getToken()));
    }
    else
    {
        // get the seventh child value (the type)
        valType funcVarType = createVarDeclExprType((NonTerminalNode *)(funcDeclNode->GetChildren()[6]));

        // get the forth child value (the types of the function parameters)
        vector<valType> paramTypes = createFunctionParamTypes((NonTerminalNode *)(funcDeclNode->GetChildren()[3]));

        // create the entry
        functionEntry *funcEntry = new functionEntry(name, funcVarType, paramTypes);

        // check return statements
        checkReturnStatements(funcEntry);

        // add the current root scope as their scope
        funcEntry->setInnerScope(_currRootScope);

        // and finally, add the function to the table
        _symbolTable->addFunction(funcEntry);
    }
}

void SemanticAnalyzer::addVariableNodeToSymbolTable(NonTerminalNode *varDeclNode)
{
    // get the current scope
    scope *currScope = _scopeStack.top();

    // check if the variable already exists in the symbol table (in current or parent scope)
    TerminalNode *nameNode = (TerminalNode *)(varDeclNode->GetChildren()[1]);
    string name = nameNode->getToken()->val;
    tableEntery entry = currScope->getEntry(name);

    if (entry.name != "_undeclared")
    {
        _errorHandler->addError(new semanticError("variable already declared", nameNode->getToken()));
    }
    else
    {
        // add variable to the symbol table
        currScope->addTableEntry(createTableEntery_varDec(varDeclNode));
    }
}

void SemanticAnalyzer::addParamNodeToSymbolTable(NonTerminalNode *paramNode)
{
    // get the current scope
    scope *currScope = _scopeStack.top();

    // check if the variable already exists in the symbol table (in current or parent scope)
    cout << "adding param node to symbol table" << endl;
    TerminalNode *nameNode = (TerminalNode *)(paramNode->GetChildren()[1]);
    string name = nameNode->getToken()->val;
    tableEntery entry = currScope->getEntry(name);

    if (entry.name != "_undeclared")
    {
        _errorHandler->addError(new semanticError("variable already declared", nameNode->getToken()));
    }
    else
    {
        // add variable to the symbol table
        currScope->addTableEntry(createTableEntery_param(paramNode));
    }
}

void SemanticAnalyzer::addParamListToSymbolTable(vector<NonTerminalNode *> paramNodes)
{
    // get the current scope
    scope *currScope = _scopeStack.top();
    currScope->printScope();

    for (int i = 0; i < paramNodes.size(); i++)
    {
        addParamNodeToSymbolTable(paramNodes[i]);
    }
}

void SemanticAnalyzer::updateScope(SyntaxToken *currToken)
{
    if (currToken->kind == SyntaxKind::OPEN_CURLY)
    {
        // entering scope
        scope *newScope = new scope();

        bool isFunctionScope = true;

        // if the stack is empty it means its a new function
        // so just connect it to the stack knowing it dosent have a parent
        // later wre connect the function to the scope in the updateSymbolTable() func

        if (!_scopeStack.empty())
        {
            scope *oldScope = _scopeStack.top();
            oldScope->addInnerScope(newScope);
            newScope->setParentScope(oldScope);
            isFunctionScope = false;
        }

        _scopeStack.push(newScope);

        if (isFunctionScope)
        {
            addParamListToSymbolTable(_currFunctionParamNodes);
            _currFunctionParamNodes.clear(); // clear the param nodes after adding them to the symbol table
        }

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
            addFunctionNodeToSymbolTable(ntNode);
        }

        else if (ntNode->getNonTerminalKind() == VAR_DECL_EXPR)
        {
            addVariableNodeToSymbolTable(ntNode);
        }

        else if (ntNode->getNonTerminalKind() == PARAM_LIST)
        {
            _currFunctionParamNodes = getFunctionParamNodes(ntNode);
        }

        else if (isReturnStatement(node))
        {
            _currFunctionReturnNodes.push_back((NonTerminalNode *)node);
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
        TerminalNode *tNode = (TerminalNode *)node;
        SyntaxKind kind = tNode->getToken()->kind;

        if (assignTerminal.find(kind) != assignTerminal.end())
        {
            node->SetValType(valType{assignTerminal[kind], 0, false, false});
        }
    }
}

bool areTypesEqual(valType a, valType b)
{
    return a.type == b.type &&
           a.isPointer == b.isPointer &&
           a.isArray == b.isArray;
}

valType checkArithmeticCompatibility(valType left, valType right, SyntaxToken *opToken, ErrorHandler *_errorHandler)
{
    valType res = {UNDIFINED, 0, false, false};
    bool errorOccurred = false;

    if (left.isPointer || right.isPointer)
    {
        if ((opToken->kind == PLUS || opToken->kind == MINUS) &&
            ((left.isPointer && right.type == INT) || (right.isPointer && left.type == INT)))
        {
            res = left.isPointer ? left : right;
        }
        else
        {
            _errorHandler->addError(new semanticError("pointer arithmetic not allowed", opToken));
            errorOccurred = true;
        }
    }
    else if (left.isArray || right.isArray)
    {
        _errorHandler->addError(new semanticError("array arithmetic not allowed", opToken));
        errorOccurred = true;
    }
    else if (left.type == FLOAT || right.type == FLOAT)
    {
        res = {FLOAT, 0, false, false};
    }
    else if (left.type == INT || right.type == INT)
    {
        res = {INT, 0, false, false};
    }
    else if (left.type == CHAR || right.type == CHAR)
    {
        res = {INT, 0, false, false};
    }
    else
    {
        _errorHandler->addError(new semanticError("incompatible types for arithmetic", opToken));
        errorOccurred = true;
    }

    if (errorOccurred)
        res = {UNDIFINED, 0, false, false};

    return res;
}

valType checkComparisonCompatibility(valType left, valType right, SyntaxToken *opToken, ErrorHandler *_errorHandler)
{
    valType res = {INT, 0, false, false};
    if (!areTypesEqual(left, right))
    {
        _errorHandler->addError(new semanticError("incompatible types for comparison", opToken));
        res = {UNDIFINED, 0, false, false};
    }
    return res;
}

valType checkLogicalCompatibility(valType left, valType right, SyntaxToken *opToken, ErrorHandler *_errorHandler)
{
    valType res = {INT, 0, false, false};
    if (left.type != INT || right.type != INT)
    {
        _errorHandler->addError(new semanticError("logical operators require int operands", opToken));
        res = {UNDIFINED, 0, false, false};
    }
    return res;
}

valType checkBitwiseCompatibility(valType left, valType right, SyntaxToken *opToken, ErrorHandler *_errorHandler)
{
    valType res = {INT, 0, false, false};
    if ((left.type != INT && left.type != CHAR) || (right.type != INT && right.type != CHAR))
    {
        _errorHandler->addError(new semanticError("bitwise operators require int or char operands", opToken));
        res = {UNDIFINED, 0, false, false};
    }
    return res;
}

valType SemanticAnalyzer::checkCompatibilityBinaryOp(valType leftOp, valType rightOp, SyntaxToken *opToken)
{
    valType res = {UNDIFINED, 0, false, false};

    if (opToken->kind == PLUS || opToken->kind == MINUS || opToken->kind == STAR || opToken->kind == SLASH)
    {
        res = checkArithmeticCompatibility(leftOp, rightOp, opToken, _errorHandler);
    }
    else if (opToken->kind == EQUALS_EQUALS || opToken->kind == BANG_EQUALS ||
             opToken->kind == LESS_THAN || opToken->kind == GREATER_THAN ||
             opToken->kind == LESS_THAN_EQUALS || opToken->kind == GREATER_THAN_EQUALS)
    {
        res = checkComparisonCompatibility(leftOp, rightOp, opToken, _errorHandler);
    }
    else if (opToken->kind == PIPE_PIPE || opToken->kind == AMPERSAND_AMPERSAND)
    {
        res = checkLogicalCompatibility(leftOp, rightOp, opToken, _errorHandler);
    }
    else if (opToken->kind == PIPE || opToken->kind == AMPERSAND || opToken->kind == CARET)
    {
        res = checkBitwiseCompatibility(leftOp, rightOp, opToken, _errorHandler);
    }

    return res;
}

bool isWideningCompatible(baseType target, baseType source)
{
    if (target == FLOAT)
        return source == FLOAT || source == INT || source == CHAR;
    if (target == INT)
        return source == INT || source == CHAR;
    if (target == CHAR)
        return source == CHAR;
    return false;
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
    else if (isWideningCompatible(leftOp.type, rightOp.type))
    {
        res.type = leftOp.type;
    }

    if (errorOccurred)
    {
        res = {UNDIFINED, 0, false, false};
    }

    return res;
}

void SemanticAnalyzer::checkReturnStatements(functionEntry *funcEntry)
{
    cout << "checking return types" << endl;
    // check if the function has a return statement
    vector<NonTerminalNode *> returnNodes = _currFunctionReturnNodes;
    valType returnType = funcEntry->getReturnType();

    for (int i = 0; i < returnNodes.size(); i++)
    {
        cout << "size of return nodes: " << returnNodes.size() << endl;
        NonTerminalNode *returnNode = returnNodes[i];
        cout << "return node: " << returnNode->GetValType().type << endl;
        valType nodeType = returnNode->GetValType();
        cout << "node type: " << nodeType.type << endl;

        if (nodeType.type != returnType.type || nodeType.isPointer != returnType.isPointer || nodeType.isArray != returnType.isArray)
        {
            _errorHandler->addError(new semanticError("return type does not match function declaration"));
        }

        cout << "return node: " << returnNode->GetValType().type << endl;
    }

    _currFunctionReturnNodes.clear();
}

valType SemanticAnalyzer::getVarType(SyntaxToken *IDToken)
{
    // get the current scope
    scope *currScope = _scopeStack.top();

    // check if the variable already exists in the symbol table (in current or parent scope)
    string name = IDToken->val;
    tableEntery entry = currScope->getEntry(name);

    if (entry.name == "_undeclared")
    {
        return {UNDIFINED, 0, false, false};
        _errorHandler->addError(new semanticError("variable not declared", IDToken));
    }
    else
    {
        return entry.type;
    }
}

// returns the functions return type and checks if the function call parameters match the function declaration parameters
//  if the function is not declared it will add an error to the error handler
//  if the function call parameters do not match the function declaration parameters it will add an error to the error handler
valType SemanticAnalyzer::getFunctionCallValTypeAndCheck(NonTerminalNode *funcCallNode)
{
    valType res = {UNDIFINED, 1, false, false};
    // get the function name
    TerminalNode *nameNode = (TerminalNode *)(funcCallNode->GetChildren()[0]);
    string name = nameNode->getToken()->val;

    // check if the function call parameters match the function declaration parameters
    vector<ASTNode *> children = funcCallNode->GetChildren();

    NonTerminalNode *exprList = (NonTerminalNode *)(children[2]);
    vector<ASTNode *> paramListChildren = exprList->GetChildren();

    vector<NonTerminalNode *> paramNodes = getFunctionCallParamNodes(exprList);
    functionEntry *entry = _symbolTable->getFunction(name);

    bool match = true;

    if (entry == nullptr)
    {
        _errorHandler->addError(new semanticError("function not declared", nameNode->getToken()));
    }
    else
    {
        res = entry->getReturnType();
        vector<valType> paramTypes = entry->getParamTypes();
        if (paramNodes.size() != paramTypes.size())
        {
            match = false;
        }
        else
        {
            for (int i = 0; i < paramNodes.size(); i++)
            {
                valType paramType = paramNodes[i]->GetValType();
                valType expectedType = paramTypes[i];

                if (paramType.type != expectedType.type || paramType.isPointer != expectedType.isPointer || paramType.isArray != expectedType.isArray)
                {
                    match = false;
                }
            }
        }
    }

    if (!match)
    {
        _errorHandler->addError(new semanticError("function call parameters do not match", nameNode->getToken()));
    }

    return res;
}

void SemanticAnalyzer::initAssignActions()
{
    _nonTerminalAssignActions[PARAM] = &SemanticAnalyzer::assignParamNodeType;
    _nonTerminalAssignActions[TYPE] = &SemanticAnalyzer::assignTypeNodeType;
    _nonTerminalAssignActions[BASE_TYPE] = &SemanticAnalyzer::assignBaseTypeNodeType;
    _nonTerminalAssignActions[VAR_DECL_EXPR] = &SemanticAnalyzer::assignVarDeclExprNodeType;
    _nonTerminalAssignActions[ASSIGN_VALUE] = &SemanticAnalyzer::assignAssignValueNodeType;
    _nonTerminalAssignActions[ASSIGN_EXPR] = &SemanticAnalyzer::assignAssignExprNodeType;
    _nonTerminalAssignActions[ASSIGN_TARGET] = &SemanticAnalyzer::assignAssignTargetNodeType;
    _nonTerminalAssignActions[CONDITION_OP] = &SemanticAnalyzer::assignConditionOpNodeType;
    _nonTerminalAssignActions[SIMPLE_STMT] = &SemanticAnalyzer::assignSimpleStmtNodeType;
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
    NonTerminalNode *ntNode = (NonTerminalNode *)(node);

    vector<ASTNode *> children = ntNode->GetChildren();
    if (children.size() == 1)
    {
        resType = children[0]->GetValType();
    }

    node->SetValType(resType);
}

void SemanticAnalyzer::assignTypeNodeType(ASTNode *node)
{
    valType resType = {UNDIFINED, 0, false, false};
    NonTerminalNode *ntNode = (NonTerminalNode *)(node);

    vector<ASTNode *> children = ntNode->GetChildren();

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

    node->SetValType(resType);
}

void SemanticAnalyzer::assignBaseTypeNodeType(ASTNode *node)
{
    valType resType = {UNDIFINED, 0, false, false};
    NonTerminalNode *ntNode = (NonTerminalNode *)(node);

    vector<ASTNode *> children = ntNode->GetChildren();
    if (children.size() == 1)
    {
        resType = children[0]->GetValType();
    }

    node->SetValType(resType);
}

void SemanticAnalyzer::assignVarDeclExprNodeType(ASTNode *node)
{
    valType resType = {UNDIFINED, 0, false, false};
    NonTerminalNode *ntNode = (NonTerminalNode *)(node);

    TerminalNode *varNode = (TerminalNode *)(ntNode->GetChildren()[1]);
    varNode->SetValType(getVarType(varNode->getToken()));

    vector<ASTNode *> children = ntNode->GetChildren();

    valType leftOpVarType = children[0]->GetValType();

    NonTerminalNode *initOptNode = (NonTerminalNode *)(children[2]);
    vector<ASTNode *> initOptChildren = initOptNode->GetChildren();

    if (initOptChildren.size() > 0)
    {
        TerminalNode *assignOpNode = (TerminalNode *)(initOptChildren[0]);
        SyntaxToken *opToken = assignOpNode->getToken();

        NonTerminalNode *assignValueNode = (NonTerminalNode *)(initOptChildren[1]);
        valType rightOpVarType = assignValueNode->GetValType();

        resType = checkCompatibilityAssignExp(leftOpVarType, rightOpVarType, assignOpNode->getToken());
        node->SetValType(resType);
    }
}

void SemanticAnalyzer::assignAssignValueNodeType(ASTNode *node)
{
    valType resType = {UNDIFINED, 0, false, false};
    NonTerminalNode *ntNode = (NonTerminalNode *)(node);

    vector<ASTNode *> children = ntNode->GetChildren();

    if (children.size() == 1)
    {
        resType = children[0]->GetValType();
    }

    else if (children.size() == 3)
    {
        valType type = children[1]->GetValType();
        resType = {type.type, type.size, type.isPointer, true};
    }

    node->SetValType(resType);
}

void SemanticAnalyzer::assignAssignExprNodeType(ASTNode *node)
{
    valType resType = {UNDIFINED, 0, false, false};
    NonTerminalNode *ntNode = (NonTerminalNode *)(node);

    vector<ASTNode *> children = ntNode->GetChildren();
    if (children.size() >= 3)
    {
        valType leftOp = children[0]->GetValType();
        valType rightOp = children[2]->GetValType();

        NonTerminalNode *assignOpNode = (NonTerminalNode *)(children[1]);
        SyntaxToken *opToken = ((TerminalNode *)(assignOpNode->GetChildren()[0]))->getToken();

        resType = checkCompatibilityAssignExp(leftOp, rightOp, opToken);
    }

    node->SetValType(resType);
}

void SemanticAnalyzer::assignAssignTargetNodeType(ASTNode *node)
{
    valType resType = {UNDIFINED, 0, false, false};
    NonTerminalNode *ntNode = (NonTerminalNode *)(node);

    vector<ASTNode *> children = ntNode->GetChildren();
    if (children.size() == 1)
    {
        TerminalNode *varNode = (TerminalNode *)(children[0]);
        resType = getVarType(varNode->getToken());
    }
    else if (children.size() == 4)
    {
        valType arrType = children[0]->GetValType();
        if (!arrType.isArray)
        {
            _errorHandler->addError(new semanticError("indexing non-array type", ((TerminalNode *)(children[1]))->getToken()));
        }
        else
        {
            resType = {arrType.type, arrType.size, arrType.isPointer, false};
        }
    }
    else if (children.size() == 2)
    {
        valType ptrType = _scopeStack.top()->getEntry(((TerminalNode *)(children[1]))->getToken()->val).type;
        if (!ptrType.isPointer)
        {
            _errorHandler->addError(new semanticError("dereferencing non-pointer type", ((TerminalNode *)(children[0]))->getToken()));
        }
        else
        {
            resType = {ptrType.type, ptrType.size, false, ptrType.isArray};
        }
    }

    node->SetValType(resType);
}

void SemanticAnalyzer::assignConditionOpNodeType(ASTNode *node)
{
    valType resType = {UNDIFINED, 0, false, false};
    NonTerminalNode *ntNode = (NonTerminalNode *)(node);

    vector<ASTNode *> children = ntNode->GetChildren();
    if (children.size() == 1)
    {
        valType condType = children[0]->GetValType();
        if (condType.type != INT && !condType.isPointer)
        {
            _errorHandler->addError(new semanticError("condition must be int or pointer", ((TerminalNode *)(children[0]))->getToken()));
        }
        else
        {
            resType = condType;
        }
    }

    node->SetValType(resType);
}

void SemanticAnalyzer::assignSimpleStmtNodeType(ASTNode *node)
{
    if (isReturnStatement(node))
    {
        NonTerminalNode *ntNode = (NonTerminalNode *)node;
        vector<ASTNode *> children = ntNode->GetChildren();

        NonTerminalNode *ExptOpt = (NonTerminalNode *)(children[1]);
        vector<ASTNode *> ExptOptChildren = ExptOpt->GetChildren();
        if (ExptOptChildren.size() > 0)
        {
            valType returnType = ExptOptChildren[0]->GetValType();
            node->SetValType(returnType);
        }
    }
}

void SemanticAnalyzer::assignExprNodeType(ASTNode *node)
{
    valType resType = {UNDIFINED, 0, false, false};
    NonTerminalNode *ntNode = (NonTerminalNode *)(node);

    vector<ASTNode *> children = ntNode->GetChildren();
    if (children.size() == 1)
    {
        resType = children[0]->GetValType();
    }

    node->SetValType(resType);
}

void SemanticAnalyzer::assignLogicalExprNodeType(ASTNode *node)
{
    valType resType = {UNDIFINED, 0, false, false};
    NonTerminalNode *ntNode = (NonTerminalNode *)(node);

    vector<ASTNode *> children = ntNode->GetChildren();
    if (children.size() == 1)
    {
        resType = children[0]->GetValType();
    }
    else if (children.size() == 3)
    {
        valType leftOp = children[0]->GetValType();
        valType rightOp = children[2]->GetValType();
        SyntaxToken *opToken = ((TerminalNode *)(children[1]))->getToken();
        resType = checkCompatibilityBinaryOp(leftOp, rightOp, opToken);
    }

    node->SetValType(resType);
}

void SemanticAnalyzer::assignRelationalExprNodeType(ASTNode *node)
{
    valType resType = {UNDIFINED, 0, false, false};
    NonTerminalNode *ntNode = (NonTerminalNode *)(node);

    vector<ASTNode *> children = ntNode->GetChildren();
    if (children.size() == 1)
    {
        resType = children[0]->GetValType();
    }
    else if (children.size() == 3)
    {
        valType leftOp = children[0]->GetValType();
        valType rightOp = children[2]->GetValType();
        SyntaxToken *opToken = ((TerminalNode *)(children[1]))->getToken();
        resType = checkCompatibilityBinaryOp(leftOp, rightOp, opToken);
    }

    node->SetValType(resType);
}

void SemanticAnalyzer::assignAddExprNodeType(ASTNode *node)
{
    valType resType = {UNDIFINED, 0, false, false};
    NonTerminalNode *ntNode = (NonTerminalNode *)(node);

    vector<ASTNode *> children = ntNode->GetChildren();
    if (children.size() == 1)
    {
        resType = children[0]->GetValType();
    }
    else if (children.size() == 3)
    {
        valType leftOp = children[0]->GetValType();
        valType rightOp = children[2]->GetValType();
        SyntaxToken *opToken = ((TerminalNode *)(children[1]))->getToken();
        resType = checkCompatibilityBinaryOp(leftOp, rightOp, opToken);
    }

    node->SetValType(resType);
}

void SemanticAnalyzer::assignMulExprNodeType(ASTNode *node)
{
    valType resType = {UNDIFINED, 0, false, false};
    NonTerminalNode *ntNode = (NonTerminalNode *)(node);

    vector<ASTNode *> children = ntNode->GetChildren();
    if (children.size() == 1)
    {
        resType = children[0]->GetValType();
    }
    else if (children.size() == 3)
    {
        valType leftOp = children[0]->GetValType();
        valType rightOp = children[2]->GetValType();
        SyntaxToken *opToken = ((TerminalNode *)(children[1]))->getToken();
        resType = checkCompatibilityBinaryOp(leftOp, rightOp, opToken);
    }

    node->SetValType(resType);
}

void SemanticAnalyzer::assignUnaryExprNodeType(ASTNode *node)
{
    valType resType = {UNDIFINED, 0, false, false};
    NonTerminalNode *ntNode = (NonTerminalNode *)(node);

    vector<ASTNode *> children = ntNode->GetChildren();
    if (children.size() == 1)
    {
        resType = children[0]->GetValType();
    }
    else if (children.size() == 2)
    {
        valType operandType = children[1]->GetValType();
        SyntaxToken *opToken = ((TerminalNode *)(children[0]))->getToken();
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

    node->SetValType(resType);
}

void SemanticAnalyzer::assignIncrementExprNodeType(ASTNode *node)
{
    valType resType = {UNDIFINED, 0, false, false};
    NonTerminalNode *ntNode = (NonTerminalNode *)(node);

    vector<ASTNode *> children = ntNode->GetChildren();
    if (children.size() >= 2)
    {
        valType operandType = children[children.size() - 1]->GetValType();
        SyntaxToken *opToken = ((TerminalNode *)(children[children.size() - 2]))->getToken();
        if (operandType.type != INT && !operandType.isPointer)
        {
            _errorHandler->addError(new semanticError("increment/decrement requires int or pointer", opToken));
        }
        else
        {
            resType = operandType;
        }
    }

    node->SetValType(resType);
}

void SemanticAnalyzer::assignAddressExprNodeType(ASTNode *node)
{
    valType resType = {UNDIFINED, 0, false, false};
    NonTerminalNode *ntNode = (NonTerminalNode *)(node);

    vector<ASTNode *> children = ntNode->GetChildren();
    if (children.size() == 2)
    {
        valType varType = children[1]->GetValType();
        resType = {varType.type, varType.size, true, varType.isArray};
    }

    node->SetValType(resType);
}

void SemanticAnalyzer::assignDereferenceExprNodeType(ASTNode *node)
{
    valType resType = {UNDIFINED, 0, false, false};
    NonTerminalNode *ntNode = (NonTerminalNode *)(node);

    vector<ASTNode *> children = ntNode->GetChildren();
    if (children.size() == 2)
    {
        valType varType = _scopeStack.top()->getEntry(((TerminalNode *)(children[1]))->getToken()->val).type;
        if (!varType.isPointer)
        {
            _errorHandler->addError(new semanticError("dereferencing non-pointer type", ((TerminalNode *)(children[0]))->getToken()));
        }
        else
        {
            resType = {varType.type, varType.size, false, varType.isArray};
        }
    }

    node->SetValType(resType);
}

void SemanticAnalyzer::assignPrimaryExprNodeType(ASTNode *node)
{
    valType resType = {UNDIFINED, 1, false, false};
    NonTerminalNode *ntNode = (NonTerminalNode *)(node);

    vector<ASTNode *> children = ntNode->GetChildren();
    if (children.size() == 1)
    {
        TerminalNode *tNode = (TerminalNode *)(children[0]);
        if (tNode->getToken()->kind == IDENTIFIER)
        {
            resType = getVarType(tNode->getToken());
        }
        else
        {
            resType.type = assignTerminal[tNode->getToken()->kind];
        }
    }
    else if (isArrDeref(node))
    {
        string varName = ((TerminalNode *)(children[0]))->getToken()->val;
        valType type = _scopeStack.top()->getEntry(varName).type;
        if (!type.isArray && !type.isPointer)
        {
            _errorHandler->addError(new semanticError("indexing non-array type", ((TerminalNode *)(children[1]))->getToken()));
        }
        else
        {
            resType = {type.type, type.size, false, false};
        }
    }
    else if (children.size() == 3)
    {
        resType = children[1]->GetValType();
    }
    else if (isFuncCall(node))
    {
        // function call
        resType = getFunctionCallValTypeAndCheck(ntNode);
    }

    node->SetValType(resType);
}

void SemanticAnalyzer::checkForMainFunction()
{
    // check if the main function is declared
    functionEntry *mainFunc = _symbolTable->getFunction("main");
    if (mainFunc == nullptr)
    {
        _errorHandler->addError(new semanticError("main function not declared"));
    }
}
