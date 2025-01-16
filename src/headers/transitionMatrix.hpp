#ifndef __TRANSITION_MATRIX
#define __TRANSITION_MATRIX

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <unordered_map>

using namespace std;

class transitionMatrix
{
private:
    int **_mat;
    int _stateCount;

    unordered_map<char, int> _alphabetToIndex;

    void isStateExistsWErr(int state, bool wantedResult) const;
    void isSymbolExistsErr(char alpha, bool wantedResult) const;

public:
    transitionMatrix(vector<int> *states, vector<char> *alphabet);
    transitionMatrix();
    int addState();
    void addAlpha(char alpha);
    int getState(int state, char alpha) const;
    void initMatrix();
    void insertTransition(int from, char alpha, int to);
    void insertTransitionString(string &transition);
    bool isStateExsists(int state) const;
    bool isSymbolExists(const char alpha) const;
    void printMatrix() const;
};

#endif
