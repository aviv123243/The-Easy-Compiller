#include "../src/headers/DFA.hpp"
#include <iostream>

using namespace std;
int main()
{
    DFA dfa;
    
    dfa.setStateCount(7);
    
    //initialising the alphabet
    for (char i = ' '; i <= '~'; i++)
    {
        dfa.addAlpha(i);
    }

    dfa.initMatrix();
    
    dfa.setStartState(0);
    
    //--[integer]-- (end state=1)
    dfa.addEndState(1);
    for (int i = '1'; i <= '9'; i++)
    {
        dfa.insertTransition(0,i,1);
    }

    for (int i = '0'; i <= '9'; i++)
    {
        dfa.insertTransition(1,i,1);
    }

    //--[float]-- (end state=3)
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

    //--[string literal]-- (end state=5)
    dfa.addEndState(5);
    dfa.insertTransition(0,'"',4);

    for (int i = ' '; i <= '~'; i++)
    {
        if(i != '"') dfa.insertTransition(4,i,4);
    }

    dfa.insertTransition(4,'"',5);

    //--[id]-- (end state=6)
    dfa.addEndState(6);

    for (int i = 'A'; i <= 'z'; i++)
    {
        dfa.insertTransition(0,i,6);
    }

    for (int i = 'A'; i <= 'z'; i++)
    {
        dfa.insertTransition(6,i,6);
    }

    for (int i = '0'; i <= '9'; i++)
    {
        dfa.insertTransition(6,i,6);
    }

    dfa.insertTransition(6,'_',6);

    dfa.writeDFAToFile("C:\\Users\\pc-admin\\Documents\\aviv coading\\COMPILLER\\src\\lexerDFAConfig.txt");
}