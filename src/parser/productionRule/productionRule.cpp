#include "productionRule.hpp"
#include "../GrammerSymbol/grammerSymbol.hpp"
#include <iostream>
#include <vector>
#include <map>

using namespace std;

productionRule::productionRule(NonTerminalKind left) : _left(left), _numOfRightSideSymbols(0) {}

productionRule::~productionRule() {}

void productionRule::addSymbol(SyntaxKind terminal)
{
    _rightSideSymbols.push_back(terminal);
    _rightSideTypes.push_back(GrammarSymbolType::TERMINAL);
    _numOfRightSideSymbols++;
}

void productionRule::addSymbol(NonTerminalKind nonTerminal)
{
    _rightSideSymbols.push_back(nonTerminal);
    _rightSideTypes.push_back(GrammarSymbolType::NON_TERMINAL);
    _numOfRightSideSymbols++;
}

SyntaxKind productionRule::getTerminal(int index)
{
    if (index >= _numOfRightSideSymbols)
    {
        cerr << ("Index out of range");
        exit(1);
    }

    if (_rightSideTypes[index] != GrammarSymbolType::TERMINAL)
    {
        cerr << ("Symbol at index is not a terminal");
        exit(1);
    }

    return (SyntaxKind)_rightSideSymbols[index];
}

NonTerminalKind productionRule::getNonTerminal(int index)
{
    if (index >= _numOfRightSideSymbols)
    {
        cerr << ("Index out of range");
        exit(1);
    }

    if (_rightSideTypes[index] != GrammarSymbolType::NON_TERMINAL)
    {
        cerr << ("Symbol at index is not a non terminal");
        exit(1);
    }

    return (NonTerminalKind)_rightSideSymbols[index];
}

GrammarSymbolType productionRule::getType(int index)
{
    if (index >= _numOfRightSideSymbols)
    {
        runtime_error("Index out of range");
    }

    return _rightSideTypes[index];
}

int productionRule::getNumOfRightSideSymbols()
{
    return _numOfRightSideSymbols;
}

NonTerminalKind productionRule::getLeft()
{
    return _left;
}