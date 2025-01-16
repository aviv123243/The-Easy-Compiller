#include "headers/dfa.hpp"
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <fstream>

using namespace std;

DFA::DFA(string DFAConfigFile)
{
    ifstream file(DFAConfigFile);
    string currLine;
    stringstream ss;
    int currentNum;
    int from;
    char currSymbol;
    int to;

    if (!file.is_open())
    {
        throw runtime_error("Failed to open file");
    }

    // initialising states
    getline(file, currLine);
    ss.clear();
    ss.str(currLine);
    while (ss >> currentNum)
    {
        if (currentNum != _tm.addState())
        {
            cout << currentNum;
            throw runtime_error("invalid state!");
        }
    }

    // initialising start state
    getline(file, currLine);
    ss.clear();
    ss.str(currLine);
    ss >> currentNum;
    _startState = currentNum;

    // initialising end states
    getline(file, currLine);
    ss.clear();
    ss.str(currLine);

    while (ss >> currentNum)
    {
        _endStates.push_back(currentNum);
    }

    // initialising alphabet
    getline(file, currLine);
    ss.clear();
    ss.str(currLine);

    while (ss >> currSymbol)
    {
        _tm.addAlpha(currSymbol);
    }

    // initialising matrix
    _tm.initMatrix();

    // initialising transitions
    while (getline(file, currLine))
    {
        _tm.insertTransitionString(currLine);
    }

    
}

bool DFA::inLanguage(string &word) const
{
    int currState = _startState;
    int i = 0;

    while (currState != -1 && i < word.length())
    {
        currState = _tm.getState(currState, word[i]);
        i++;
    }

    return find(_endStates.begin(), _endStates.end(), currState) != _endStates.end();
}

void DFA::printTM()
{
    _tm.printMatrix();
}
