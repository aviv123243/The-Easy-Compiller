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
    scope *_parentScope = nullptr;

public:
    void addTableEntry(tableEntery entry)
    {
        _tableEntries.push_back(entry);
    }

    void addInnerScope(scope *innerScope) { _innerScopes.push_back(innerScope);}
    void setParentScope(scope *parentScope) { _parentScope = parentScope; }

    vector<tableEntery> getInnerScopeEntries() const
    {
        return _tableEntries;
    }

    tableEntery getEntry(string name)
    {
        tableEntery res = {"_undeclared", {}};

        for (tableEntery entry : _tableEntries)
        {
            if (entry.name == name)
            {
                res = entry;
            }
        }

        if(res.name == "_undeclared" && _parentScope != nullptr)
        {
            res = _parentScope->getEntry(name);
        }

        return res;
    }
    vector<scope *> getInnerScopes() const { return _innerScopes; }

    // returns the entery with the requested name
    // if the name is not found in this scope, it will search in the inner scopes
    tableEntery getEntryGlobal(string name)
    {
        tableEntery res = {"_undeclared", {}};

        getInnerScopeEntrie(name);

        for (scope *innerScope : _innerScopes)
        {
            res = innerScope->getEntryGlobal(name);
        }
        
        return res;
    }

    // returns the entery with the requested name
    tableEntery getInnerScopeEntrie(string name)
    {
        tableEntery res = {"_undeclared", {}};
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