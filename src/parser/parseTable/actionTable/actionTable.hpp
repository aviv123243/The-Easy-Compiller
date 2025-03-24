#ifndef __ACTION_TABLE
#define __ACTION_TABLE

#include "../action/action.hpp"
#include "../../../token/token.hpp"
#include "../../grammerSymbol/grammerSymbol.hpp"

class ActionTable
{
    private:
        action **_table;
        action *_defaultActions;
        int _numOfStates;

    public:
        ActionTable(int numOfStates);
        ~ActionTable();
        void add(int state, SyntaxKind terminal, action act);
        void addDefault(int state, action act);
        action get(int state, SyntaxKind terminal);
};

#endif
