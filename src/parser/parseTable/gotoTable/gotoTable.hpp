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
    int _numOfStates;

public:
    GotoTable(int numOfStates);
    ~GotoTable();
    void add(int startState, NonTerminalKind nt, int endState);
    int get(int state, NonTerminalKind nt);
};

#endif