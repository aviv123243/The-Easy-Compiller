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
    SymbolTable() { 
        addFunction(new functionEntry("printInt", {INT}, {valType{INT}})); 
        addFunction(new functionEntry("printFloat", {INT}, {valType{FLOAT}}));
    }

    void addFunction(functionEntry *function) { _functions.push_back(function); }
    functionEntry *getFunction(string name);
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

valType createVarDeclExprType(NonTerminalNode *varNode);
tableEntry createTableEntery_varDec(NonTerminalNode *varDecNode);
tableEntry createTableEntery_param(NonTerminalNode *varDecNode);
vector<valType> createFunctionParamTypes(NonTerminalNode *paramListNode);
void createFunctionParamTypesHelper(NonTerminalNode *paramListNode, vector<valType> *paramTypes);
vector<tableEntry> createFunctionParamEnteries(NonTerminalNode *paramListNode);
void createFunctionParamEnteriesHelper(NonTerminalNode *paramListNode, vector<tableEntry> *paramTypes);

#endif
