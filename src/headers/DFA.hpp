#ifndef __DFA
#define __DFA

#include "transitionMatrix.hpp"
#include <vector>
#include <string>

using namespace std;

class DFA
{
    private:
        int _startState;
        vector<int> _endStates;
        transitionMatrix _tm;

    public:
        DFA(string DFAConfigFile);
        bool inLanguage(string &word) const;
        void printTM();
};


#endif