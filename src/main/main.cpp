#include "../lexer/lexer.hpp"
#include "../errorHandler/errorHandler.hpp"
// #include "headers/parser.hpp"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char **argv)
{
    //   errorHandler   errors;
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

    ErrorHandler errorHandler;
    Lexer lex(filePath, "..\\src\\lexerDFAConfig.txt", &errorHandler);
    vector<SyntaxToken> tokens = lex.getTokens();

    if (errorHandler.getErrorCount() > 0)
    {
        errorHandler.printErrors();
    }
    else
    {
        for (int i = 0; i < tokens.size(); i++)
        {
            cout << syntaxTokenToString(tokens[i]) << endl;
        }
    }
}

// int main()
// {
//     gotoTable table;
//     nonTerminal nt1 = nonTerminal(nonTerminalKind::PROGRAM);
//     nonTerminal nt11 = nonTerminal(nonTerminalKind::PROGRAM);
//     nonTerminal nt2 = nonTerminal(nonTerminalKind::STATEMENT);
//     nonTerminal nt3 = nonTerminal(nonTerminalKind::EXPRESSION);

//     table.add(nt1, 0, 1);
//     table.add(nt1, 1, 2);
//     table.add(nt2, 0, 3);
//     table.add(nt2, 1, 4);

//     cout << table.get(nt1, 0) << endl;
//     cout << table.get(nt11, 0) << endl;
// }
