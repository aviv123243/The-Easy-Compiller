#ifndef __ACTION_TABLE
#define __ACTION_TABLE

#include "../../lexer/lexer.hpp"

enum actionType
{
    SHIFT,
    REDUCE,
    ACCEPT,
    ERROR
};

struct action
{
    actionType type;
    int num;
};

class actionTable
{
private:
    action **_table;
    int _numOfStates;

public:
    actionTable(int numOfStates);
    ~actionTable();
    void add(int state, SyntaxKind terminal, action act);
    action get(int state, SyntaxKind terminal);
};

#endif
