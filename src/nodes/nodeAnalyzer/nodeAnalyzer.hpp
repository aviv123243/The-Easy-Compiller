#ifndef __NODE_ANALYZER
#define __NODE_ANALYZER

#include "../nodes.hpp"
#include "../../parser/grammerSymbol/grammerSymbol.hpp"
#include "../../token/token.hpp"

bool isFuncCall(ASTNode *node);
bool isArrDeref(ASTNode *node);
bool isReturnStatement(ASTNode *node);
vector<NonTerminalNode *> getFunctionParamNodes(NonTerminalNode *paramListNode);
vector<NonTerminalNode *> getFunctionCallParamNodes(NonTerminalNode *paramListNode);



#endif