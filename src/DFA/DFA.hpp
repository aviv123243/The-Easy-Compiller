#ifndef __DFA
#define __DFA

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
    DFA(int stateCount, vector<char> *alphabet);
    DFA(string DFAConfigFile);
    DFA();
    void addAlpha(char alpha);
    void setStateCount(int numOfStates);
    void setStartState(int state);
    int getStartState() const;
    void addEndState(int state);
    const vector<int> &getEndStates() const;
    vector<char> getAlphabet() const;
    int getState(int state, char alpha) const;
    void initMatrix();
    void insertTransition(int from, char alpha, int to);
    void insertTransitionString(string &transition);
    bool isStateExsists(int state) const;
    bool isSymbolExists(const char alpha) const;
    pair<bool, int> inLanguage(string &word) const;
    void writeDFAToFile(string dstFile);
    void printMatrix() const;
};

#endif
