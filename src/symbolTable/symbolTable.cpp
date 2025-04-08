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
    SyntaxKind type = UNEXPECTED_TOKEN;
    bool isPointer = false;
    bool isArray = false;

    type = ((TerminalNode *)children[0])->getTerminalKind();

    // pointer
    if (children.size() == 2)
    {
        isPointer = true;
    }

    // array
    if (children.size() == 3)
    {
        isArray = true;
    }

    varType res = {type, isPointer, isArray};
    return res;
}

tableEntery createTableEntery(NonTerminalNode *varDecNode)
{
    cout << "Creating table entry" << endl;
    tableEntery res = tableEntery{"", varType{UNEXPECTED_TOKEN, false, false}, false};
    vector<ASTNode *> children = varDecNode->GetChildren();

    cout << "Children size: " << children.size() << endl;
    res.name = ((TerminalNode *)children[1])->getToken()->val;

    cout << "Name: " << res.name << endl;
    res.type = createVarType((NonTerminalNode *)children[0]);

    res.isInitialized = false;

    return res;
}

vector<SyntaxKind> createFunctionParamTypes(NonTerminalNode *paramListNode)
{
    vector<SyntaxKind> paramTypes;
    vector<ASTNode *> children = paramListNode->GetChildren();

    for (ASTNode *child : children)
    {
        if (child->GetType() == GrammarSymbolType::NON_TERMINAL)
        {
            NonTerminalNode *paramNode = (NonTerminalNode *)child;
            if (paramNode->getNonTerminalKind() == PARAM)
            {
                vector<ASTNode *> paramChildren = paramNode->GetChildren();
                SyntaxKind type = ((TerminalNode *)paramChildren[0])->getTerminalKind();
                paramTypes.push_back(type);
            }
        }
    }

    return paramTypes;
}
