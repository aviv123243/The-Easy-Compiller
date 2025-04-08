#include "tableEntry.hpp"
#include <iostream>
#include <string>

void printTableEntery(tableEntery *entry)
{
    cout << "---------------------------------" << endl;
    cout << "Variable Name: " << entry->name << endl;
    cout << "Variable Type: " << syntaxKindToString(entry->type.type) << endl;
    cout << "Is Pointer: " << (entry->type.isPointer ? "Yes" : "No") << endl;
    cout << "Is Array: " << (entry->type.isArray ? "Yes" : "No") << endl;
    cout << "Is Initialized: " << (entry->isInitialized ? "Yes" : "No") << endl;
    cout << "---------------------------------" << endl;
}

