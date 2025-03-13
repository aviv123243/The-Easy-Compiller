#ifndef __TABLE_ENTERY
#define __TABLE_ENTERY

#include "../../token/token.hpp"
#include <String>

using namespace std;

enum enteryType
{
    FUNC,
    VAR
};

struct tableEntery
{
    SyntaxToken *symbol;
    enteryType valType;
};

tableEntery createEntery(SyntaxToken *symbol,enteryType type);
#endif