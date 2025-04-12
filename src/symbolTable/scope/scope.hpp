#ifndef SCOPE
#define SCOPE

#include "..\tableEntry\tableEntry.hpp"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class scope
{
private:
    vector<tableEntery> _tableEntries;
    vector<scope *> _innerScopes;

public:
    void addTableEntry(tableEntery entry)
    {
        _tableEntries.push_back(entry);
    }
    void addInnerScope(scope *innerScope) { _innerScopes.push_back(innerScope); }

    vector<tableEntery> getTableEntries() const
    {
        return _tableEntries;
    }
    vector<scope *> getInnerScopes() const { return _innerScopes; }

    // returns the entery with the requested name
    // if the name is not found in this scope, it will search in the inner scopes
    tableEntery getEntryGlobal(string name)
    {
        tableEntery res = {};

        for (tableEntery entry : _tableEntries)
        {
            if (entry.name == name)
            {
                res = entry;
            }
        }

        for (scope *innerScope : _innerScopes)
        {
            res = innerScope->getEntryGlobal(name);
        }
        
        return res;
    }

    // returns the entery with the requested name
    tableEntery getEntry(string name)
    {
        tableEntery res = {};
        for (tableEntery entry : _tableEntries)
        {
            if (entry.name == name)
            {
                res = entry;
            }
        }
        return res;
    }

    void printScope()
    {
        cout << "Scope:" << endl;

        for (tableEntery entry : _tableEntries)
        {
            printTableEntery(&entry);
        }

        cout << "Inner Scopes:" << endl;
        if (_innerScopes.size() != 0)
        {
            for (scope *innerScope : _innerScopes)
            {
                innerScope->printScope();
            }
        }
        cout << "End of Scope" << endl;
    }
};

#endif