#ifndef __GOTO_TABLE
#define __GOTO_TABLE

#include "../../parser.hpp"
#include <map>
#include <vector>

class gotoTable
{
private:
    int **_table;
    int _numOfStates;

public:
    gotoTable(int numOfStates);
    ~gotoTable();
    void add(int startState, NonTerminal nt, int endState);
    int get(int state, NonTerminal nt);
};

#endif