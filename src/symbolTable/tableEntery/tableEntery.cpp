#include "tableEntery.hpp"
#include <iostream>

using namespace std;

tableEntery createEntery(SyntaxToken *nameToken,SyntaxToken *valTypeToken,enteryType enterytype)
{
    if(nameToken->kind != SyntaxKind::IDENTIFIER) 
    {
        cerr << "type mismatch in creating table entery";
        exit(-1);
    }

    return tableEntery{nameToken->val,enterytype,valTypeToken->kind};
}