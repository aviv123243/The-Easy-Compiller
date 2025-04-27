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
    vector<tableEntry> _tableEntries;
    vector<scope *> _innerScopes;
    scope *_parentScope = nullptr;

public:
    scope() {}

    void addTableEntry(tableEntry entry)
    {
        _tableEntries.push_back(entry);
    }

    void addInnerScope(scope *innerScope) { _innerScopes.push_back(innerScope); }
    void setParentScope(scope *parentScope) { _parentScope = parentScope; }
    scope *getParentScope() const { return _parentScope; }

    vector<tableEntry> &getEntries() { return _tableEntries; }

    // returns the entery with the requested name
    // if the name is not found in this scope, it will search in the inner scopes
    tableEntry getEntry(string name)
    {
        tableEntry res = {"_undeclared", {}};

        for (tableEntry entry : _tableEntries)
        {
            if (entry.name == name)
            {
                res = entry;
            }
        }

        if (res.name == "_undeclared" && _parentScope != nullptr)
        {
            res = _parentScope->getEntry(name);
        }

        return res;
    }
    vector<scope *> getInnerScopes() const { return _innerScopes; }

    // returns the entery with the requested name
    tableEntry getInnerScopeEntrie(string name)
    {
        tableEntry res = {"_undeclared", {}};
        for (tableEntry entry : _tableEntries)
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
        
        for (auto &entry : _tableEntries)
        {
            // Make sure printTableEntery handles nullptrs or malformed data
            printTableEntery(&entry);
        }

        for (auto *innerScope : _innerScopes)
        {
            if (innerScope != nullptr) // <-- this is the fix
            {
                innerScope->printScope();
            }
            else
            {
                cout << "Warning: nullptr inner scope found!" << endl;
            }
        }

    }
};

#endif