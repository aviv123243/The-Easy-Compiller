#include "symbolTable.hpp"

//initiallising an empty table
SymbolTable::SymbolTable() : _table() {}

//returns an entery in the table by name of symbol
tableEntery SymbolTable::getEntery(string name)
{
    return _table[name];
}

//finds if an given symbol name exists in the table
bool SymbolTable::isExists(string name)
{
    return _table.find(name) != _table.end();
}

//add entery to table 
//if symbol already exists it wont do enything and return false
//otherwise returns true
bool SymbolTable::addEntery(tableEntery entery)
{
    if(isExists(entery.symbol->val)) return false;

    _table[entery.symbol->val] = entery;
}

//returns an vector of the inner scopes 
//every inner scope is an symbol table itself
const vector<SymbolTable*> &SymbolTable::getInnerScopes()
{
    return _innerScopes;
}