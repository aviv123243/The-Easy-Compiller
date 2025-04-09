#include "actionTable.hpp"
#include "tableEntry/tableEntry.hpp"
#include "../parser/grammerSymbol/grammerSymbol.hpp"
#include "../token/token.hpp"
#include "../nodes/nodes.hpp"
#include <map>
#include <vector>
#include <String>

varType createVarType(NonTerminalNode *varNode)
{
    vector<ASTNode *> children = varNode->GetChildren();

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

    varType res = {type, size, isPointer, isArray};
    return res;
}

tableEntery createTableEntery_varDec(NonTerminalNode *varDecNode)
{
    tableEntery res = tableEntery{"", varType{UNEXPECTED_TOKEN, 1, false, false}, false};
    vector<ASTNode *> children = varDecNode->GetChildren();

    //set name
    res.name = ((TerminalNode *)children[1])->getToken()->val;

    //set type
    res.type = createVarType((NonTerminalNode *)children[0]);

    return res;
}

tableEntery createTableEntery_param(NonTerminalNode *paramNode)
{
    tableEntery res = tableEntery{"", varType{UNEXPECTED_TOKEN, 1, false, false}, false};
    vector<ASTNode *> children = paramNode->GetChildren();

    //set name
    res.name = ((TerminalNode *)children[1])->getToken()->val;

    //set type
    res.type = createVarType((NonTerminalNode *)children[0]);

    return res;
}

void createFunctionParamTypesHelper(NonTerminalNode *paramListNonEmptyNode, vector<varType> *paramTypes)
{
    vector<ASTNode *> childern = paramListNonEmptyNode->GetChildren();
    int numOfChildren = childern.size();
    NonTerminalNode *typeNode;
    if (numOfChildren == 1)
    {
        typeNode = ((NonTerminalNode *)(childern[0]->GetChildren()[0]));

        paramTypes->push_back(createVarType(typeNode));
    }

    if (numOfChildren == 3)
    {
        typeNode = ((NonTerminalNode *)(childern[2]->GetChildren()[0]));

        paramTypes->push_back(createVarType(typeNode));

        createFunctionParamTypesHelper((NonTerminalNode *)childern[0], paramTypes);
    }
}

vector<varType> createFunctionParamTypes(NonTerminalNode *paramListNode)
{
    vector<ASTNode *> childern = paramListNode->GetChildren();
    vector<varType> res;

    if (childern.size() > 0)
    {
        createFunctionParamTypesHelper((NonTerminalNode *)childern[0], &res);
    }

    return res;
}

void createFunctionParamEnteriesHelper(NonTerminalNode *paramListNonEmptyNode, vector<tableEntery> *enteries)
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

vector<tableEntery> createFunctionParamEnteries(NonTerminalNode *paramListNode)
{
    vector<ASTNode *> childern = paramListNode->GetChildren();
    vector<tableEntery> res;

    if (childern.size() > 0)
    {
        createFunctionParamEnteriesHelper((NonTerminalNode *)childern[0], &res);
    }

    return res;
}


