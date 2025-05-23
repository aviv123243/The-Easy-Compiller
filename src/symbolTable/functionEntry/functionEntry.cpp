#include "functionEntry.hpp"
#include <iostream>
#include <string>
#include <vector>

void functionEntry::print() const
{
    cout << "Function Name: " << _name << endl;
    cout << "Return Type: " << valTypeToString(_returnType) << endl;
    cout << "Parameter Types: " << endl;
    cout << "num of parameters: " << _paramTypes.size() << endl;
    for (const auto &paramType : _paramTypes)
    {
        cout << valTypeToString(paramType) << " ";
    }

    if(_scopeRoot) _scopeRoot->printScope();

    cout << "End of Function" << endl;
    cout << "----------------------------------------" << endl;
    cout << endl;
}