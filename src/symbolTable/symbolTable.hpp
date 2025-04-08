#ifndef __SYMBOL_TABLE
#define __SYMBOL_TABLE

#include "tableEntry/tableEntry.hpp"
class functionEntery;
#include "../parser/grammerSymbol/grammerSymbol.hpp"
#include "../token/token.hpp"
#include "../nodes/nodes.hpp"
#include <map>
#include <vector>
#include <String>

using namespace std;

struct symbolTable
{
    vector<functionEntery*> functions;
};

varType createVarType(NonTerminalNode * varNode);
tableEntery createTableEntery(NonTerminalNode *varDecNode);
vector<SyntaxKind> getFunctionParamTypes(NonTerminalNode *paramListNode);



#endif
