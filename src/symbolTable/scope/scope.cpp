#ifndef SCOPE
#include "../tableEntry/tableEntry.hpp"
#include "../symbolTable.hpp"
#include <vector>

struct scope
{
    vector<tableEntery> entries;
    vector<symbolTable*> _innerScopes;
};



#define SCOPE
#endif