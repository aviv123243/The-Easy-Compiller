#include "headers/lexer.hpp"
// #include "headers/parser.hpp"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char **argv)
{
    string filePath;

    if (argc > 2)
    {
        cout << "ERROR: Please enter the input file";
        return 1;
    }

    //-------ONLY FOR CONVENIENCE---------
    else if (argc == 1)
    {
        filePath = "..\\demos\\DEMO3.EZ";
    }
    //-------------------------------------

    Lexer lex("lexerDFAConfig.txt", filePath);

    // lex.printTransitionMatrix();
    SyntaxToken currToken;

    // while ((currToken = lex.getNextToken()).kind != syntaxKind::END_OF_FILE)
    // {
    //     cout << syntaxTokenToString(currToken) << endl;
    // }

    for (int i = 0; i < 10; i++)
    {
        currToken = lex.getNextToken();
        cout << syntaxTokenToString(currToken) << endl;
    }
    

    cout << syntaxTokenToString(currToken) << endl;
}
