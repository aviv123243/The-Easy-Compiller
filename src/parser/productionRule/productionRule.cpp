#include "productionRule.hpp"
#include "../GrammerSymbol/grammerSymbol.hpp"
#include "../../token/token.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

productionRule::productionRule(NonTerminal left) : _left(left), _numOfRightSideSymbols(0) {}

productionRule::productionRule() :productionRule(NonTerminal::PROGRAM) {}

productionRule::~productionRule() {}

productionRule& productionRule::addSymbol(SyntaxKind terminal)
{
    _rightSideSymbols.push_back(terminal);
    _rightSideTypes.push_back(GrammarSymbolType::TERMINAL);
    _numOfRightSideSymbols++;

    return *this;
}

productionRule& productionRule::addSymbol(NonTerminal nonTerminal)
{
    _rightSideSymbols.push_back(nonTerminal);
    _rightSideTypes.push_back(GrammarSymbolType::NON_TERMINAL);
    _numOfRightSideSymbols++;

    return *this;
}

productionRule& productionRule::addSymbol()
{
    return addSymbol(SyntaxKind::EPSILON);
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

NonTerminal productionRule::getNonTerminal(int index)
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

void productionRule::setLeft(NonTerminal left)
{
    _left = left;
}

void productionRule::reset()
{
    _numOfRightSideSymbols = 0;
    _rightSideSymbols.clear();
    _rightSideTypes.clear();
}

string productionRule::toString()
{
    stringstream str;
    str << nonTerminalToString(_left)
        << " \e[0;33m=>\033[0m";

    for (int i = 0; i < _numOfRightSideSymbols; i++)
    {
        if (_rightSideTypes[i] == GrammarSymbolType::TERMINAL)
        {
            str << " " << syntaxKindToString((SyntaxKind)(_rightSideSymbols[i]));
        }
        else
        {
            str << " " << nonTerminalToString((NonTerminal)_rightSideSymbols[i]);
        }
    }

    return str.str();
}