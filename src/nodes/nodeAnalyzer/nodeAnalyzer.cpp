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