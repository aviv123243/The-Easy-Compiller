#include "actionTable.hpp"
#include <map>
#include <vector>
#include "../action/action.hpp"
#include "../../../nodes/nodes.hpp"
#include "../../../token/token.hpp"
#include "../../grammerSymbol/grammerSymbol.hpp"

using namespace std;

ActionTable ::ActionTable(int numOfStates) : _numOfStates(numOfStates)
{
    _table = new action *[_numOfStates];
    _defaultActions = new action[_numOfStates];
    for (int i = 0; i < _numOfStates; i++)
    {
        _defaultActions[i] = {actionType::DEFAULT, -1};
        _table[i] = new action[SyntaxKind::SYNTAX_KIND_COUNT];
        for (int j = 0; j < SyntaxKind::SYNTAX_KIND_COUNT; j++)
        {
            _table[i][j].type = actionType::DEFAULT;
            _table[i][j].num = -1;
        }
    }

    
}

ActionTable ::~ActionTable()
{
    for (int i = 0; i < _numOfStates; i++)
    {
        delete[] _table[i];
    }
    
    delete[] _defaultActions;
    delete[] _table;
}

void ActionTable ::add(int state, SyntaxKind terminal, action act)
{
    if (state >= _numOfStates || terminal >= SyntaxKind::SYNTAX_KIND_COUNT)
    {
        runtime_error("Invalid state or symbol");
    }

    else if (_table[state][terminal].type == actionType::DEFAULT)
    {
        _table[state][terminal] = act;
    }

    else
    {
        runtime_error("Conflict in action table");
    }
}

void ActionTable::addDefault(int state, action act)
{
    if (state >= _numOfStates)
    {
        runtime_error("Invalid state");
    }

    else if (_defaultActions[state].num == -1)
    {
        _defaultActions[state] = act;
    }

    else
    {
        runtime_error("Conflict in action table");
    }
}

action ActionTable ::get(int state, SyntaxKind terminal)
{
    if (state >= _numOfStates || terminal >= SyntaxKind::SYNTAX_KIND_COUNT)
    {
        runtime_error("Invalid state or terminal");
    }

    if(_table[state][terminal].type == DEFAULT)
    {
        return _defaultActions[state];
    }

    return _table[state][terminal];
}