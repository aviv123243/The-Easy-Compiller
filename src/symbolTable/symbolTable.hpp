#ifndef __SYMBOL_TABLE
#define __SYMBOL_TABLE

#include "tableEntry/tableEntry.hpp"
#include "functionEntry/functionEntry.hpp"
#include "../parser/grammerSymbol/grammerSymbol.hpp"
#include "../token/token.hpp"
#include "../nodes/nodes.hpp"
#include <map>
#include <vector>
#include <String>

using namespace std;

class symbolTable
{
private:
    vector<functionEntry *> functions;

public:
    void addFunction(functionEntry *function) { functions.push_back(function); }
    void print() const
    {
        cout << "Symbol Table:" << endl;
        cout << "num of functions: " << functions.size() << endl;
        for (const auto &function : functions)
        {
            function->print();
        }
        cout << "End of Symbol Table" << endl;
    }
};

varType createVarType(NonTerminalNode *varNode);
tableEntery createTableEntery(NonTerminalNode *varDecNode);
vector<SyntaxKind> createFunctionParamTypes(NonTerminalNode *paramListNode);

#endif
