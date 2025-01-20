#include "../src/headers/DFA.hpp"
#include "../src/headers/lexer.hpp"
#include <iostream>

using namespace std;
int main()
{
    DFA dfa;
    int i, j, k;

    dfa.setStateCount(110);

    int endState = 1;
    int midState = 43;

    // initialising the alphabet
    for (char i = ' '; i <= '~'; i++)
    {
        dfa.addAlpha(i);
    }

    dfa.initMatrix();

    dfa.setStartState(0);

    //--[integer]-- (end state=1)
    dfa.addEndState(endState); // 1
    for (int i = '1'; i <= '9'; i++)
    {
        dfa.insertTransition(0, i, endState);
    }

    for (int i = '0'; i <= '9'; i++)
    {
        dfa.insertTransition(endState, i, endState);
    }

    endState++;
    //--[float]-- (end state=2)
    dfa.addEndState(endState);
    dfa.insertTransition(midState, '.', endState);

    for (int i = '0'; i <= '9'; i++)
    {
        dfa.insertTransition(midState, i, endState);
    }

    for (int i = '0'; i <= '9'; i++)
    {
        dfa.insertTransition(endState, i, endState);
    }

    midState++;
    endState++;
    //--[string literal]-- (end state=3)
    dfa.addEndState(endState); // 3
    dfa.insertTransition(0, '"', midState);

    for (int i = ' '; i <= '~'; i++)
    {
        if (i != '"')
            dfa.insertTransition(midState, i, midState);
    }

    dfa.insertTransition(midState, '"', endState);

    midState++;
    endState++;
    //--[id]-- (end state=4)
    dfa.addEndState(endState);

    for (int i = 'A'; i <= 'z'; i++)
    {
        dfa.insertTransition(0, i, endState);
    }

    for (int i = 'A'; i <= 'z'; i++)
    {
        dfa.insertTransition(endState, i, endState);
    }

    for (int i = '0'; i <= '9'; i++)
    {
        dfa.insertTransition(endState, i, endState);
    }

    dfa.insertTransition(endState, '_', endState);
    endState++;
    //---------[keyWords]---------
    vector<string> keyWords = {"if", "while", "for", "fn", "ret", "int", "float"};

    for (i = 0; i < keyWords.size(); i++)
    {
        dfa.addEndState(endState);

        dfa.insertTransition(0, keyWords[i][0], midState);
        for (j = 1; j < keyWords[i].size() - 1; j++)
        {
            for (k = 'A'; k <= 'z'; k++)
            {
                dfa.insertTransition(midState, k, syntaxKind::IDENTIFIER); // setting deafult to be an id
            }

            dfa.insertTransition(midState, keyWords[i][j], midState + 1);
            midState++;
        }

        dfa.insertTransition(midState, keyWords[i][j], endState);

        endState++;
    }

    //---------[single symobls]---------
    vector<char> symobls = {'=', ',', '+', '-', '/', '*', '&', '|', '!', ';', '<', '>', '(', ')', '{', '}', '[', ']'};

    for (i = 0; i < symobls.size() - 1; i++)
    {
        dfa.addEndState(endState);
        dfa.insertTransition(0, symobls[i], endState);
        endState++;
    }

    dfa.writeDFAToFile("C:\\Users\\pc-admin\\Documents\\aviv coading\\COMPILLER\\src\\lexerDFAConfig.txt");
}