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
        vector<scope*> _innerScopes;

    public:
        void addTableVarDecEntry(tableEntery entry) {cout << "Adding entry: " << entry.name << endl;
             _tableEntries.push_back(entry); }
        void addInnerScope(scope* innerScope) { _innerScopes.push_back(innerScope); }

        vector<tableEntery> getTableEntries() const { 
            cout << "Table entries size: " << _tableEntries.size() << endl;
            return _tableEntries; 
        }
        vector<scope*> getInnerScopes() const { return _innerScopes; }

        tableEntery getEntry(string name) {
            tableEntery res = {};
            for (tableEntery entry : _tableEntries) {
                if (entry.name == name) {
                    res = entry;
                }
            }
            return res;
        }
};

#endif