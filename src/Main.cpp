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
        filePath = "C:\\Users\\pc-admin\\Documents\\aviv coading\\COMPILLER\\demos\\DEMO3.EZ";
    }
    //-------------------------------------

    Lexer lex("lexerDFAConfig.txt", filePath);

    lex.printTransitionMatrix();
    
    SyntaxToken currToken;

    while ((currToken = lex.getNextToken()).kind != syntaxKind::END_OF_FILE)
    {
        cout << SyntaxTokenToString(currToken) << endl;
    }

    cout << SyntaxTokenToString(currToken) << endl;
    
    
    
}
