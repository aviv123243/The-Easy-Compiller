#ifndef __PRODUCTION_RULE
#define __PRODUCTION_RULE

#include "../../token/token.hpp"
#include "../grammerSymbol/grammerSymbol.hpp"
#include <vector>

using namespace std;

class productionRule
{
private:
    // left side of the production rule
    NonTerminalKind _left;

    // right side of the production rule
    int _numOfRightSideSymbols;
    vector<int> _rightSideSymbols;
    vector<GrammarSymbolType> _rightSideTypes;

public:
    productionRule(NonTerminalKind left);
    ~productionRule();
    void addSymbol(SyntaxKind terminal);
    void addSymbol(NonTerminalKind nonTerminal);
    NonTerminalKind getNonTerminal(int index);
    SyntaxKind getTerminal(int index);
    GrammarSymbolType getType(int index);
    int getNumOfRightSideSymbols();
    NonTerminalKind getLeft();
};

#endif