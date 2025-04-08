#include "functionEntry.hpp"
#include <iostream>
#include <string>
#include <vector>

void functionEntry::print() const
{
    cout << "Function Name: " << _name << endl;
    cout << "Return Type: " << syntaxKindToString(_returnType) << endl;
    cout << "Parameter Types: ";
    for (const auto &paramType : _paramTypes)
    {
        cout << syntaxKindToString(paramType) << " ";
    }
    cout << endl;
}