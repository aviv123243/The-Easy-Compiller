#include "actionTable.hpp"
#include "tableEntry/tableEntry.hpp"
#include "functionEntry/functionEntry.hpp"
#include "symbolTable.hpp"
#include "../parser/grammerSymbol/grammerSymbol.hpp"
#include "../semantic/semantic.hpp"
#include "../token/token.hpp"
#include "../nodes/nodes.hpp"
#include <map>
#include <vector>
#include <String>
#include <algorithm>

// returns the entry with the requested name
// if function not found returns nullptr
functionEntry *SymbolTable::getFunction(string name)
{
    functionEntry *res = nullptr;
    vector<functionEntry *> enteries = getFunctions();

    for (functionEntry *entry : enteries)
    {
        if (entry->getName() == name)
        {
            res = entry;
        }
    }

    return res;
}

valType createVarDeclExprType(NonTerminalNode *typeNode)
{
    vector<ASTNode *> children = typeNode->GetChildren();

    NonTerminalNode *baseTypeNode = (NonTerminalNode *)children[0];
    SyntaxKind type = ((TerminalNode *)baseTypeNode->GetChildren()[0])->getToken()->kind;

    int size = 1;
    bool isPointer = false;
    bool isArray = false;

    // pointer
    if (children.size() == 2)
    {
        isPointer = true;
    }

    // array
    if (children.size() == 4)
    {
        isArray = true;

        TerminalNode *sizeNode = (TerminalNode *)children[2];
        size = stoi(sizeNode->getToken()->val);
    }

    valType res = {assignTerminal[type], size, isPointer, isArray};
    return res;
}

tableEntry createTableEntery_varDec(NonTerminalNode *varDecNode)
{
    tableEntry res = tableEntry{"", valType{UNDIFINED, 1, false, false}, false};
    vector<ASTNode *> children = varDecNode->GetChildren();

    // set name
    res.name = ((TerminalNode *)children[1])->getToken()->val;

    // set type
    res.type = createVarDeclExprType((NonTerminalNode *)children[0]);

    return res;
}

tableEntry createTableEntery_param(NonTerminalNode *paramNode)
{
    tableEntry res = tableEntry{"", valType{UNDIFINED, 1, false, false}, false};
    vector<ASTNode *> children = paramNode->GetChildren();

    // set name
    res.name = ((TerminalNode *)children[1])->getToken()->val;

    // set type
    res.type = createVarDeclExprType((NonTerminalNode *)children[0]);

    return res;
}

void createFunctionParamTypesHelper(NonTerminalNode *paramListNonEmptyNode, vector<valType> *paramTypes)
{
    vector<ASTNode *> childern = paramListNonEmptyNode->GetChildren();
    int numOfChildren = childern.size();
    NonTerminalNode *typeNode;
    if (numOfChildren == 1)
    {
        typeNode = ((NonTerminalNode *)(childern[0]->GetChildren()[0]));

        paramTypes->push_back(createVarDeclExprType(typeNode));
    }

    if (numOfChildren == 3)
    {
        typeNode = ((NonTerminalNode *)(childern[2]->GetChildren()[0]));

        paramTypes->push_back(createVarDeclExprType(typeNode));

        createFunctionParamTypesHelper((NonTerminalNode *)childern[0], paramTypes);
    }
}

vector<valType> createFunctionParamTypes(NonTerminalNode *paramListNode)
{
    vector<ASTNode *> childern = paramListNode->GetChildren();
    vector<valType> res;

    if (childern.size() > 0)
    {
        createFunctionParamTypesHelper((NonTerminalNode *)childern[0], &res);
    }
    
    std::reverse(res.begin(), res.end());
    return res;
}

void createFunctionParamEnteriesHelper(NonTerminalNode *paramListNonEmptyNode, vector<tableEntry> *enteries)
{
    vector<ASTNode *> childern = paramListNonEmptyNode->GetChildren();
    int numOfChildren = childern.size();
    NonTerminalNode *paramNode;
    if (numOfChildren == 1)
    {
        paramNode = ((NonTerminalNode *)(childern[0]));
        enteries->push_back(createTableEntery_param(paramNode));
    }

    if (numOfChildren == 3)
    {
        paramNode = ((NonTerminalNode *)(childern[2]));
        enteries->push_back(createTableEntery_param(paramNode));
        createFunctionParamEnteriesHelper((NonTerminalNode *)childern[0], enteries);
    }
}

vector<tableEntry> createFunctionParamEnteries(NonTerminalNode *paramListNode)
{
    vector<ASTNode *> childern = paramListNode->GetChildren();
    vector<tableEntry> res;

    if (childern.size() > 0)
    {
        createFunctionParamEnteriesHelper((NonTerminalNode *)childern[0], &res);
    }

    std::reverse(res.begin(), res.end());
    return res;
}
