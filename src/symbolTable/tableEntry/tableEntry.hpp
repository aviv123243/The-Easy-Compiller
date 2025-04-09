#ifndef __TABLE_ENTERY
#define __TABLE_ENTERY

#include "../../token/token.hpp"

using namespace std;

struct valType
{
    SyntaxKind type;
    int size;
    bool isPointer;
    bool isArray;
};

struct tableEntery
{
    string name;
    valType type;
    bool isInitialized = false;
};

string valTypeToString(valType vType);
void printValType(valType vtype);
void printTableEntery(tableEntery *entry);

#endif