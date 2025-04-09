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

class SymbolTable
{
private:
    vector<functionEntry *> _functions;

public:
    void addFunction(functionEntry *function) { _functions.push_back(function); }
    const std::vector<functionEntry *> &getFunctions() const { return _functions; }

    void print() const
    {
        cout << "Symbol Table:" << endl;
        cout << "num of functions: " << _functions.size() << endl;
        for (const auto &function : _functions)
        {
            function->print();
        }
        cout << "End of Symbol Table" << endl;
    }
};

valType createVarType(NonTerminalNode *varNode);
tableEntery createTableEntery_varDec(NonTerminalNode *varDecNode);
tableEntery createTableEntery_param(NonTerminalNode *varDecNode);
vector<valType> createFunctionParamTypes(NonTerminalNode *paramListNode);
void createFunctionParamTypesHelper(NonTerminalNode *paramListNode, vector<valType> *paramTypes);
vector<tableEntery> createFunctionParamEnteries(NonTerminalNode *paramListNode);
void createFunctionParamEnteriesHelper(NonTerminalNode *paramListNode, vector<tableEntery> *paramTypes);

#endif
