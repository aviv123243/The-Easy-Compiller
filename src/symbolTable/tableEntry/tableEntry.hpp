#ifndef __TABLE_ENTERY
#define __TABLE_ENTERY

#include "../../token/token.hpp"


using namespace std;

struct varType
{
    SyntaxKind type;
    bool isPointer;
    bool isArray;
};

struct tableEntery
{
    string name;
    varType type;
    bool isInitialized = false;
};


void printTableEntery(tableEntery *entry);



#endif