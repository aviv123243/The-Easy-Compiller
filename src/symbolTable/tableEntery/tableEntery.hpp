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
    string name;
    enteryType enteryType;
    SyntaxKind valType;
};

tableEntery createEntery(SyntaxToken *nameToken,SyntaxToken *valTypeToken,enteryType enterytype);
#endif