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
        bool addEntery(tableEntery entery);
        const vector<SymbolTable*> &getInnerScopes();
        
};



#endif
