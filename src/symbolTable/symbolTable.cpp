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
bool SymbolTable::addSymbol(SyntaxToken *nameToken,SyntaxToken *valTypeToken,enteryType enterytype)
{
    if(isExists(nameToken -> val)) return false;

    tableEntery entery = createEntery(nameToken,valTypeToken,enterytype);
    _table[entery.name] = entery;
}

//returns an vector of the inner scopes 
//every inner scope is an symbol table itself
const vector<SymbolTable*> &SymbolTable::getInnerScopes()
{
    return _innerScopes;
}