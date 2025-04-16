#include "nodeAnalyzer.hpp"

bool isFuncCall(ASTNode *node)
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

bool isArrDeref(ASTNode *node)
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
                if (((TerminalNode *)children[1])->getTerminalKind() == OPEN_BRACKET)
                    res = true;
            }
        }
    }

    return res;
}

bool isReturnStatement(ASTNode *node)
{
    bool res = false;

    if (node->GetType() == NON_TERMINAL)
    {
        NonTerminalNode *ntNode = ((NonTerminalNode *)node);
        if (ntNode->getNonTerminalKind() == SIMPLE_STMT)
        {
            vector<ASTNode *> children = ntNode->GetChildren();

            if (children.size() == 2)
            {
                res = true;
            }
        }
    }

    return res;
}



void getFunctionParamNodesHelper(NonTerminalNode *paramListNonEmptyNode, vector<NonTerminalNode *> *paramNodes)
{
    vector<ASTNode *> childern = paramListNonEmptyNode->GetChildren();
    int numOfChildren = childern.size();

    NonTerminalNode *paramNode;
    if (numOfChildren == 1)
    {
        paramNode = ((NonTerminalNode *)(childern[0]));
        paramNodes->push_back(paramNode);
    }

    if (numOfChildren == 3)
    {
        paramNode = ((NonTerminalNode *)(childern[2]));
        paramNodes->push_back(paramNode);
        getFunctionParamNodesHelper((NonTerminalNode *)childern[0], paramNodes);
    }
}

vector<NonTerminalNode *> getFunctionParamNodes(NonTerminalNode *paramListNode)
{
    vector<ASTNode *> childern = paramListNode->GetChildren();
    vector<NonTerminalNode *> res;

    if (childern.size() > 0)
    {
        getFunctionParamNodesHelper((NonTerminalNode *)childern[0], &res);
    }

    return res;
}

void getFunctionCallParamNodesHelper(NonTerminalNode *exprListNonEmptyNode, vector<NonTerminalNode *> *exprNodes)
{
    vector<ASTNode *> childern = exprListNonEmptyNode->GetChildren();
    int numOfChildren = childern.size();

    NonTerminalNode *exprNode;
    if (numOfChildren == 1)
    {
        exprNode = ((NonTerminalNode *)(childern[0]));
        exprNodes->push_back(exprNode);
    }

    if (numOfChildren == 3)
    {
        exprNode = ((NonTerminalNode *)(childern[2]));
        exprNodes->push_back(exprNode);
        getFunctionCallParamNodesHelper((NonTerminalNode *)childern[0], exprNodes);
    }
}

vector<NonTerminalNode *> getFunctionCallParamNodes(NonTerminalNode *paramListNode)
{
    vector<ASTNode *> childern = paramListNode->GetChildren();
    vector<NonTerminalNode *> res;

    if (childern.size() > 0)
    {
        getFunctionParamNodesHelper((NonTerminalNode *)childern[0], &res);
    }

    return res;
}