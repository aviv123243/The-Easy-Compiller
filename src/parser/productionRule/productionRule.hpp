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
    NonTerminal _left;

    // right side of the production rule
    int _numOfRightSideSymbols;
    vector<int> _rightSideSymbols;
    vector<GrammarSymbolType> _rightSideTypes;

public:
    productionRule(NonTerminal left);
    productionRule();
    ~productionRule();
    productionRule& addSymbol(SyntaxKind terminal);
    productionRule& addSymbol(NonTerminal nonTerminal);
    productionRule& addSymbol();
    NonTerminal getNonTerminal(int index);
    SyntaxKind getTerminal(int index);
    GrammarSymbolType getType(int index);
    int getNumOfRightSideSymbols();
    NonTerminal getLeft();
    void setLeft(NonTerminal left);
    void reset();
    string toString();
};

#endif