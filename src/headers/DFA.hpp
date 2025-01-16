#ifndef __TRANSITION_MATRIX
#define __TRANSITION_MATRIX

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <unordered_map>

using namespace std;

class DFA
{
private:
    int **_mat;
    int _stateCount;
    int _startState;
    vector<int> _endStates;

    unordered_map<char, int> _alphabetToIndex;

    void isStateExistsWErr(int state, bool wantedResult) const;
    void isSymbolExistsErr(char alpha, bool wantedResult) const;

public:
    DFA(vector<int> *states, vector<char> *alphabet);
    DFA(string DFAConfigFile);
    int addState();
    void addAlpha(char alpha);
    void setStartState(int state);
    void addEndState(char state);
    int getState(int state, char alpha) const;
    void initMatrix();
    void insertTransition(int from, char alpha, int to);
    void insertTransitionString(string &transition);
    bool isStateExsists(int state) const;
    bool isSymbolExists(const char alpha) const;
    bool inLanguage(string &word) const;
    void printMatrix() const;
};

#endif
