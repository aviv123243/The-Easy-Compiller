#include "tableEntry.hpp"
#include <iostream>
#include <string>
#include <sstream>

string varTypeToString(varType vType)
{
    stringstream res;

    res << "\e[1;34m<"
        << syntaxKindToString(vType.type)
        << ">\033[0m";
    if (vType.isPointer)
    {
        res << "*";
    }
    if (vType.isArray)
    {
        res << "["
        << vType.size
        << "]";
    }


    return res.str();
}

void printVarType(varType vtype)
{
    cout << varTypeToString(vtype) << endl;
}

void printTableEntery(tableEntery *entry)
{
    cout << "---------------------------------" << endl;
    cout << "Variable Name: " << entry->name << endl;
    cout << "Variable Type: " << syntaxKindToString(entry->type.type) << endl;
    printVarType(entry->type);
    cout << "---------------------------------" << endl;
}

