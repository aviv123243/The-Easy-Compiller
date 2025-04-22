#ifndef __TABLE_ENTERY
#define __TABLE_ENTERY

#include "../../token/token.hpp"

using namespace std;

enum baseType
{
    INT,
    FLOAT,
    CHAR,
    UNDIFINED,
};

struct valType
{
    baseType type = UNDIFINED;
    int size = 1;
    bool isPointer = false;
    bool isArray = false;
};

struct tableEntry
{
    string name;
    valType type;
    bool isInitialized = false;
    string addr = "";
};

string valTypeToString(valType vType);
string baseTypeToString(baseType bType);
void printValType(valType vtype);
void printTableEntery(tableEntry *entry);

#endif