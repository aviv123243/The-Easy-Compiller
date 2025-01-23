#include "../src/headers/DFA.hpp"
#include "../src/headers/lexer.hpp"
#include <iostream>

#define START_STATE 0

using namespace std;
int main()
{
    DFA dfa;
    int i, j, k;
    int prev;

    dfa.setStateCount(120);

    int endState = 1;
    int midState = 90;

    // initialising the alphabet
    for (char i = ' '; i <= '~'; i++)
    {
        dfa.addAlpha(i);
    }

    dfa.addAlpha('\n');
    dfa.addAlpha('\r');
    dfa.addAlpha('\t');

    dfa.initMatrix();

    vector<char> alphabet = dfa.getAlphabet();

    dfa.setStartState(START_STATE);

    //--[integer]-- (end state=1)
    dfa.addEndState(endState); // 1
    for (int i = '1'; i <= '9'; i++)
    {
        dfa.insertTransition(START_STATE, i, endState);
    }

    for (int i = '0'; i <= '9'; i++)
    {
        dfa.insertTransition(endState, i, endState);
    }

    endState++;
    //--[float]-- (end state=2)
    dfa.addEndState(endState);
    dfa.insertTransition(endState - 1, '.', midState);

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
    dfa.insertTransition(START_STATE, '"', midState);

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

    for (int i = 'A'; i <= 'Z'; i++)
    {
        dfa.insertTransition(START_STATE, i, endState);
        dfa.insertTransition(endState, i, endState);
    }

    for (int i = 'a'; i <= 'z'; i++)
    {
        dfa.insertTransition(START_STATE, i, endState);
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
        prev = START_STATE;
        dfa.addEndState(endState);

        for (j = 0; j < keyWords[i].size() - 1; j++)
        {
            // check if the connection already exists
            if (dfa.getState(prev, keyWords[i][j]) == syntaxKind::IDENTIFIER + 1 || dfa.getState(prev, keyWords[i][j]) == -1)
            {
                // if the connection is non-existant, make it
                dfa.insertTransition(prev, keyWords[i][j], midState);
                midState++;
            }

            // for any other letter unrealated to the keyword labale it as ID
            for (k = 'A'; k <= 'Z'; k++)
            {
                if (dfa.getState(prev, k) == -1)
                {
                    dfa.insertTransition(prev, k, syntaxKind::IDENTIFIER + 1);
                }
            }

            for (k = 'a'; k <= 'z'; k++)
            {
                if (dfa.getState(prev, k) == -1)
                {
                    dfa.insertTransition(prev, k, syntaxKind::IDENTIFIER + 1);
                }
            }

            // defining it as an ID end state
            prev = dfa.getState(prev, keyWords[i][j]);
            dfa.addEndState(prev);
        }

        // connect to end state
        dfa.insertTransition(prev, keyWords[i][j], endState);

        for (k = 'A'; k <= 'z'; k++)
        {
            if (dfa.getState(prev, k) == -1)
                dfa.insertTransition(prev, k, syntaxKind::IDENTIFIER + 1);
        }
        endState++;
    }

    //---------[other symobls]---------
    vector<string> symbols = {"=", ",", "+", "-", "/", "*", "&", "|", "!", ";", "<", ">", "(", ")", "{", "}", "[", "]", "=>","++","--", "+=", "-=", "/=", "*=", "==", "<=", ">=", "&&", "||", "!="};

    for (i = 0; i < symbols.size(); i++)
    {
        j = 0;
        prev = START_STATE;
        dfa.addEndState(endState);

        if (symbols[i].size() == 2)
        {
            // Set up the first state
            if (dfa.getState(prev, symbols[i][j]) == -1)
            {
                dfa.insertTransition(prev, symbols[i][j], midState);
                midState++;
            }

            // move to the next state
            prev = dfa.getState(prev, symbols[i][j]);
            j++;
        }

        // connect to end state
        dfa.insertTransition(prev, symbols[i][j], endState);
        endState++;
    }

    //---------[skip state]---------
    vector<char> whiteSpaceCharacters = {' ', '\t', '\n', '\r'};
    for (i = 0; i < whiteSpaceCharacters.size(); i++)
    {
        dfa.insertTransition(START_STATE, whiteSpaceCharacters[i], midState);
        dfa.insertTransition(midState, whiteSpaceCharacters[i], midState);
    }
    midState++;

    prev = dfa.getState(START_STATE, '<');
    dfa.insertTransition(prev, '>', midState);
    prev = midState;
    midState++;

    for (i = 0; i < alphabet.size(); i++)
    {
        if (alphabet[i] != '\n')
            dfa.insertTransition(prev, alphabet[i], prev);
    }

    dfa.writeDFAToFile("..\\src\\lexerDFAConfig.txt");
    cout << "created config file!";
}