#include "gotoTable.hpp"
#include "../../../token/token.hpp"
#include "../../grammerSymbol/grammerSymbol.hpp"
#include <map>
#include <vector>
#include <iostream>


using namespace std;

GotoTable::GotoTable(int numOfStates) : _numOfStates(numOfStates)
{
    _table = new int *[_numOfStates];
    for (int i = 0; i < _numOfStates; i++)
    {
        _table[i] = new int[NonTerminalKind::NON_TERMINAL_COUNT];
        for (int j = 0; j < NonTerminalKind::NON_TERMINAL_COUNT; j++)
        {
            _table[i][j] = -1;
        }
    }
}

GotoTable::~GotoTable()
{
}

// adds a new entry to the table
void GotoTable::add(int startState, NonTerminalKind nt, int endState)
{
    cout << "(" << startState << "," << nt << ") -> " << endState << endl;
    if (nt >= NonTerminalKind::NON_TERMINAL_COUNT || startState >= _numOfStates || endState >= _numOfStates)
    {
        cerr << "Invalid input on gotoTable::add() function" << endl;
        exit(1);
    }
    else if (_table[startState][nt] == -1)
    {
        _table[startState][nt] = endState;
    }
    else
    {
        cerr << "Conflict in goto table" << endl;
        exit(1);
    }
}

// gets the end state of a non terminal in a given state
int GotoTable::get(int state, NonTerminalKind nt)
{
    if (nt >= NonTerminalKind::NON_TERMINAL_COUNT || state >= _numOfStates)
    {
        runtime_error("Invalid non terminal or state");
    }

    return _table[state][nt];
}
