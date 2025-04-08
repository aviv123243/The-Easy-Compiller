#include "functionEntry.hpp"
#include <iostream>
#include <string>
#include <vector>

void functionEntery::print() const
{
    cout << "Function Name: " << name << endl;
    cout << "Return Type: " << syntaxKindToString(returnType) << endl;
    cout << "Parameter Types: ";
    for (const auto &paramType : paramTypes)
    {
        cout << syntaxKindToString(paramType) << " ";
    }
    cout << endl;
}