#include "nodeAnalyzer.hpp"
#include <algorithm>

bool isFuncCall(ASTNode *node)
{
    bool res = false;

    if (node->GetType() == NON_TERMINAL)
    {
        NonTerminalNode *ntNode = ((NonTerminalNode *)node);
        if (ntNode->getNonTerminalKind() == PRIMARY_EXPR || ntNode->getNonTerminalKind() == SIMPLE_STMT)
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
        cout << "11";
        NonTerminalNode *ntNode = ((NonTerminalNode *)node);
        if (ntNode->getNonTerminalKind() == SIMPLE_STMT)
        {
            cout << "22";

            vector<ASTNode *> children = ntNode->GetChildren();

            if (children.size() == 2)
            {
                res = true;
            }
        }
    }

    cout << "returning: " << res;
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

int getExprListNonEmptySize(NonTerminalNode *exprListNonEmptyNode)
{
    vector<ASTNode *> childern = exprListNonEmptyNode->GetChildren();
    int numOfChildren = childern.size();

    int res = 0;

    if (numOfChildren == 1)
    {
        res = 1;
    }

    if (numOfChildren == 3)
    {
        res = 1 + getExprListNonEmptySize((NonTerminalNode *)childern[0]);
    }

    return 0;
}

vector<NonTerminalNode *> getFunctionParamNodes(NonTerminalNode *paramListNode)
{
    vector<ASTNode *> childern = paramListNode->GetChildren();
    vector<NonTerminalNode *> res;

    if (childern.size() > 0)
    {
        getFunctionParamNodesHelper((NonTerminalNode *)childern[0], &res);
    }

    std::reverse(res.begin(), res.end());
    return res;
}

void getFunctionCallArgsNodesHelper(NonTerminalNode *exprListNonEmptyNode, vector<NonTerminalNode *> *exprNodes)
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
        getFunctionCallArgsNodesHelper((NonTerminalNode *)childern[0], exprNodes);
    }
}

vector<NonTerminalNode *> getFunctionCallArgsNodes(NonTerminalNode *exprListNode)
{
    vector<ASTNode *> childern = exprListNode->GetChildren();
    vector<NonTerminalNode *> res;

    if (childern.size() > 0)
    {
        getFunctionParamNodesHelper((NonTerminalNode *)childern[0], &res);
    }

    std::reverse(res.begin(), res.end());
    return res;
}

void getFunctionDeclNodesHelper(NonTerminalNode *programNode, vector<NonTerminalNode *> *funcDeclNodes)
{
    const vector<ASTNode *> &children = programNode->GetChildren();

    if (children.size() == 2)
    {
        funcDeclNodes->push_back((NonTerminalNode *)children[1]);
        getFunctionDeclNodesHelper((NonTerminalNode *)children[0], funcDeclNodes);
    }
}

vector<NonTerminalNode *> getFunctionDeclNodes(NonTerminalNode *programNode)
{
    vector<NonTerminalNode *> res;
    if (!programNode->GetChildren().empty())
    {
        getFunctionDeclNodesHelper(programNode, &res);
    }

    std::reverse(res.begin(), res.end());
    return res;
}

void getStmtNodesHelper(NonTerminalNode *stmtListNonEmptyNode, vector<NonTerminalNode *> *stmtNodes)
{
    const vector<ASTNode *> &children = stmtListNonEmptyNode->GetChildren();

    if (children.size() == 2)
    {
        stmtNodes->push_back((NonTerminalNode *)children[1]);
        getStmtNodesHelper((NonTerminalNode *)children[0], stmtNodes);
    }
}

vector<NonTerminalNode *> getStmtNodes(NonTerminalNode *stmtListNode)
{
    vector<NonTerminalNode *> res;
    if (!stmtListNode->GetChildren().empty())
    {
        getStmtNodesHelper(stmtListNode, &res);
    }

    std::reverse(res.begin(), res.end());
    return res;
}
