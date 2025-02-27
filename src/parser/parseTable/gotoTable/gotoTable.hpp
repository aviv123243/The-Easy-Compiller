#ifndef __GOTO_TABLE
#define __GOTO_TABLE

#include "../../../token/token.hpp"
#include "../../grammerSymbol/grammerSymbol.hpp"

#include <map>
#include <vector>

class GotoTable
{
private:
    int **_table;

public:
    int _numOfStates;

    GotoTable(int numOfStates);
    ~GotoTable();
    void add(int startState, NonTerminal nt, int endState);
    int get(int state, NonTerminal nt);
};

#endif