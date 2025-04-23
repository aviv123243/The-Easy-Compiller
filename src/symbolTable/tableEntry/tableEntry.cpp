#include "tableEntry.hpp"
#include <iostream>
#include <string>
#include <sstream>

string valTypeToString(valType vType)
{
    stringstream res;

    res << "\e[0;35m"
        << baseTypeToString(vType.type)
        << "\033[0m";
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

string baseTypeToString(baseType bType)
{
    switch (bType)
    {
    case INT:
        return "int";
    case FLOAT:
        return "float";
    case CHAR:
        return "char";
    case UNDIFINED:
        return "undefined";
    default:
        return "unknown type";
    }
}

void printValType(valType vtype)
{
    cout << valTypeToString(vtype) << endl;
}

void printTableEntery(tableEntry *entry)
{
    cout << "---------------------------------" << endl;
    cout << "Variable Name: " << entry->name << endl;
    cout << "Variable Type: " << valTypeToString(entry->type) << endl;
    cout << "---------------------------------" << endl;
}
