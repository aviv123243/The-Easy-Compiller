#include "productionRule.hpp"
#include "../../lexer/lexer.hpp"
#include "../parser.hpp"
#include <vector>
#include <map>

productionRule::productionRule(NonTerminal left) : _left(left), _numOfRightSideSymbols(0) {}

productionRule::~productionRule() {}

void productionRule::addSymbol(SyntaxKind terminal)
{
    _rightSideSymbols.push_back(terminal);
    _rightSideTypes.push_back(GrammarSymbolType::TERMINAL);
    _numOfRightSideSymbols++;
}

void productionRule::addSymbol(NonTerminal nonTerminal)
{
    _rightSideSymbols.push_back(nonTerminal);
    _rightSideTypes.push_back(GrammarSymbolType::NON_TERMINAL);
    _numOfRightSideSymbols++;
}

SyntaxKind productionRule::getTerminal(int index)
{
    if (index >= _numOfRightSideSymbols)
    {
        runtime_error("Index out of range");
    }

    if (_rightSideTypes[index] != GrammarSymbolType::TERMINAL)
    {
        runtime_error("Symbol at index is not a terminal");
    }

    return (SyntaxKind)_rightSideSymbols[index];
}

NonTerminal productionRule::getNonTerminal(int index)
{
    if (index >= _numOfRightSideSymbols)
    {
        runtime_error("Index out of range");
    }

    if (_rightSideTypes[index] != GrammarSymbolType::NON_TERMINAL)
    {
        runtime_error("Symbol at index is not a non terminal");
    }

    return (NonTerminal)_rightSideSymbols[index];
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

NonTerminal productionRule::getLeft()
{
    return _left;
}