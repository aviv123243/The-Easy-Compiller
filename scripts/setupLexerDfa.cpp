#include "../src/headers/DFA.hpp"
#include <iostream>

using namespace std;
int main()
{
    DFA dfa;
    
    dfa.setStateCount(4);
    
    //initialising the alphabet
    for (char i = '!'; i <= '~'; i++)
    {
        dfa.addAlpha(i);
    }

    dfa.initMatrix();
    
    dfa.setStartState(0);
    
    //--[integer part]-- (end state=1)
    dfa.addEndState(1);
    for (int i = '1'; i <= '9'; i++)
    {
        dfa.insertTransition(0,i,1);
    }

    for (int i = '0'; i <= '9'; i++)
    {
        dfa.insertTransition(1,i,1);
    }

    //--[float part]-- (end state=3)
    dfa.addEndState(3);
    dfa.insertTransition(1,'.',2);

    for (int i = '0'; i <= '9'; i++)
    {
        dfa.insertTransition(2,i,3);
    }

    for (int i = '0'; i <= '9'; i++)
    {
        dfa.insertTransition(3,i,3);
    }

    dfa.writeDFAToFile("C:\\Users\\pc-admin\\Documents\\aviv coading\\COMPILLER\\src\\lexerDFA.txt");
}