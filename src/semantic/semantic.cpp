#include "semantic.hpp"
#include <vector>

using namespace std;

SemanticAnalyzer::SemanticAnalyzer(ASTNode *root, ErrorHandler *errorHandler, SymbolTable *symbolTable)
    : _root(root), _errorHandler(errorHandler), _symbolTable(symbolTable), _functionCursor(0) {}

// init the stack to contain the nodes level by level
// on the top - all the leaf nodes
// in the bottom - the root
void SemanticAnalyzer::fillStack()
{
    stack<ASTNode *> helper;
    _nodesStack.push(_root);
    helper.push(_root);

    vector<ASTNode *> currNodeChildren;
    vector<ASTNode *> currLevelChildren;
    ASTNode *currNode;

    while (!helper.empty())
    {
        while (!helper.empty())
        {
            currNode = helper.top();
            helper.pop();

            currNodeChildren = currNode->GetChildren();
            currLevelChildren.insert(currLevelChildren.end(), currNodeChildren.begin(), currNodeChildren.end());
        }

        for (int i = 0; i < currLevelChildren.size(); i++)
        {
            helper.push(currLevelChildren[i]);
            _nodesStack.push(currLevelChildren[i]);
        }

        currLevelChildren.clear();
        currNodeChildren.clear();
    }
}

void SemanticAnalyzer::initAndCheckTypes()
{
    ASTNode *currNode;

    while (!_nodesStack.empty())
    {
        currNode = _nodesStack.top();
        _nodesStack.pop();

        if (currNode->GetType() == NON_TERMINAL)
            {
                NonTerminalNode *ntNode = ((NonTerminalNode *)currNode);
                if (ntNode->getNonTerminalKind() == FUNCTION_DECL)
                {
                    
                }
            }
        else if (currNode->GetType() == TERMINAL)
        {
            TerminalNode *tNode = ((TerminalNode *)currNode);
            if (tNode->getTerminalKind() == IDENTIFIER)
            {
                // check if var is declared twice
                // check if var is in scope
                // check if var is initialized
            }
        }
        
    }
}

bool SemanticAnalyzer::analyzeTypesMatch_varDec(NonTerminalNode *varDecNode)
{
    
}

bool SemanticAnalyzer::isFuncCall(ASTNode *node)
{
    bool res = false;

    if (node->GetType() == NON_TERMINAL)
    {
        NonTerminalNode *ntNode = ((NonTerminalNode *)node);
        if (ntNode->getNonTerminalKind() == PRIMARY_EXPR)
        {
            vector<ASTNode *> children = ntNode->GetChildren();

            if (children.size() == 4)
            {
                if (((TerminalNode *)children[1])->getTerminalKind() == OPEN_PAREN)
                    res = true;
            }
        }
    }

    return res;
}

bool SemanticAnalyzer::checkIfFuncInScope(NonTerminalNode *funcCallNode)
{
    bool inScope = false;
    vector<ASTNode *> children = funcCallNode->GetChildren();
    string name = ((TerminalNode *)children[0])->getToken()->val;

    vector<functionEntry *> enteries = _symbolTable->getFunctions();

    for (int i = 0; i < _functionCursor; i++)
    {
        // if function exsists
        // return true
        if (enteries[i]->getName().compare(name) == 0 )
            inScope = true;
    }

    if(!inScope) _errorHandler->addError(new semanticError("no function \"" + name + "\" was found in scope"));
}

void SemanticAnalyzer::analyze()
{
    ASTNode *currNode;
    fillStack();

    while (!_nodesStack.empty())
    {
        currNode = _nodesStack.top();
        _nodesStack.pop();

        if(isFuncCall(currNode)) checkIfFuncInScope((NonTerminalNode *)currNode);
    }
}