#include "gotoTable.hpp"
#include <map>
#include <vector>
#include "../../parser.hpp"

using namespace std;

gotoTable::gotoTable(int numOfStates) : _numOfStates(numOfStates)
{
    int **_table = new int *[_numOfStates];
    for (int i = 0; i < _numOfStates; i++)
    {
        _table[i] = new int[NonTerminal::NON_TERMINAL_COUNT];
        for (int j = 0; j < NonTerminal::NON_TERMINAL_COUNT; j++)
        {
            _table[i][j] = -1;
        }
    }
}

gotoTable::~gotoTable()
{
}

// adds a new entry to the table
void gotoTable::add(int startState, NonTerminal nt, int endState)
{
    if (nt >= NonTerminal::NON_TERMINAL_COUNT || startState >= _numOfStates || endState >= _numOfStates)
    {
        runtime_error("Invalid non terminal or state");
    }

    else if (_table[startState][nt] == -1)
    {
        _table[startState][nt] = endState;
    }
    else
    {
        runtime_error("Conflict in goto table");
    }
}

// gets the end state of a non terminal in a given state
int gotoTable::get(int state, NonTerminal nt)
{
    if (nt >= NonTerminal::NON_TERMINAL_COUNT || state >= _numOfStates)
    {
        runtime_error("Invalid non terminal or state");
    }

    return _table[state][nt];
}
