#ifndef __SYMBOL_TABLE
#define __SYMBOL_TABLE

#include "tableEntery/tableEntery.hpp"
#include <map>
#include <vector>
#include <String>

using namespace std;

class SymbolTable
{
    private:
        map<string, tableEntery> _table;
        vector<SymbolTable*> _innerScopes;

    public:
        SymbolTable();
        tableEntery getEntery(string name);
        bool isExists(string name);
        bool addSymbol(SyntaxToken *nameToken,SyntaxToken *valTypeToken,enteryType enterytype);
        const vector<SymbolTable*> &getInnerScopes();   
};



#endif
