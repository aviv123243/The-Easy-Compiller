#ifndef SCOPE
#define SCOPE

#include "..\tableEntry\tableEntry.hpp"

#include <string>
#include <vector>

using namespace std;

class scope
{
    private:
        vector<tableEntery> _tableEntries;
        vector<scope*> _innerScopes;

    public:
        void addTableVarDecEntry(tableEntery entry) { _tableEntries.push_back(entry); }
        void addInnerScope(scope* innerScope) { _innerScopes.push_back(innerScope); }

        vector<tableEntery> getTableEntries() const { return _tableEntries; }
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