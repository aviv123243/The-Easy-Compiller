#include "functionEntry.hpp"
#include <iostream>
#include <string>
#include <vector>

void functionEntry::print() const
{
    cout << "Function Name: " << _name << endl;
    cout << "Return Type: " << valTypeToString(_returnType) << endl;
    cout << "Parameter Types: ";
    for (const auto &paramType : _paramTypes)
    {
        cout << valTypeToString(paramType) << " ";
    }

    _scopeRoot->printScope();
    cout << endl;
}