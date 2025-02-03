#include "../src/DFA/DFA.hpp"
#include "../src/lexer/lexer.hpp"
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>

#define START_STATE 0

using namespace std;

void generateGraphviz(int** mat, int numStates, std::unordered_map<char, int>& charToIndex, const std::string& outputFile) {
    std::ofstream out(outputFile);

    // Write the header for the Graphviz DOT file
    out << "digraph DFA {\n";
    
    // Optional: To mark start state (assuming state 0 is the start state)
    out << "  0 [shape=circle, style=filled, color=lightgray];\n";
    
    // Optional: If you want to mark accepting states
    // For example, assuming the last state is an accepting state
    out << "  \"" << numStates - 1 << "\" [shape=doublecircle];\n";

    // Loop through all states
    for (int state = 0; state < numStates; ++state) {
        // Loop through all input symbols
        for (const auto& pair : charToIndex) {
            char inputSymbol = pair.first;
            int symbolIndex = pair.second;

            string inputSymbolStr = string(1, inputSymbol);

            if (inputSymbol == '\n') {
                inputSymbolStr = "\\n";
            } else if (inputSymbol == '\r') {
                inputSymbolStr = "\\r";
            } else if (inputSymbol == '\t') {
                inputSymbolStr = "\\t";
            } else if (inputSymbol == ' ') {
                inputSymbolStr = "space";
            } else if (inputSymbol == '"') {
                inputSymbolStr = "\\\"";
            }else if (inputSymbol == '"') {
                inputSymbolStr = "\\\"";
            }else if (inputSymbol == '\\') {
                inputSymbolStr = "\\\\";
            }
            
            

            // Get the target state from the transition matrix
            int nextState = mat[state][symbolIndex];
            
            // Ensure that the transition label is not empty
            if (inputSymbol != '\0') {
                // Write the transition to the DOT file with the label
                out << "  \"" << state << "\" -> \"" << nextState << "\" [label=\"" << inputSymbolStr << "\"];\n";
            }
        }
    }

    // Write the footer for the Graphviz DOT file
    out << "}\n";

    out.close();
}

int main()
{
    DFA dfa;
    int i, j, k;
    int prev;

    dfa.setStateCount(NUM_OF_STATES);

    int endState = 1;
    int midState = 70;

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
    //the skip states are the last two states

    int skipState1 = NUM_OF_STATES - 2;
    int skipState2 = NUM_OF_STATES - 1;

    vector<char> whiteSpaceCharacters = {' ', '\t', '\n', '\r'};
    for (i = 0; i < whiteSpaceCharacters.size(); i++)
    {
        dfa.insertTransition(START_STATE, whiteSpaceCharacters[i], skipState1);
        dfa.insertTransition(skipState1, whiteSpaceCharacters[i], skipState1);
    }

    prev = dfa.getState(START_STATE, '<');
    dfa.insertTransition(prev, '>', skipState2);

    for (i = 0; i < alphabet.size(); i++)
    {
        if (alphabet[i] != '\n')
            dfa.insertTransition(skipState2, alphabet[i], skipState2);
    }

    generateGraphviz(dfa._mat, NUM_OF_STATES, dfa._alphabetToIndex, "graph.dot");
    dfa.writeDFAToFile("..\\src\\lexerDFAConfig.txt");
    cout << "created config file!";
}