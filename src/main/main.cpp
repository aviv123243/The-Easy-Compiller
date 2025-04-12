#include "../lexer/lexer.hpp"
#include "../token/token.hpp"
#include "../errorHandler/errorHandler.hpp"
#include "../parser/parser.hpp"
#include "../semantic/semantic.hpp"
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

    ErrorHandler errorHandler;
    SymbolTable symbolTable;
    Lexer lex(filePath, "..\\src\\lexerDFAConfig.txt", &errorHandler);
    vector<SyntaxToken *> tokens = lex.getTokens();

    if (errorHandler.getErrorCount() > 0)
    {
        errorHandler.printErrors();
    }
    else
    {
        for (int i = 0; i < tokens.size(); i++)
        {
            cout << syntaxTokenToString(*tokens[i]) << endl;
        }

        SemanticAnalyzer semantic(&errorHandler, &symbolTable);
        Parser parser(tokens, 183, &errorHandler,&semantic);

        ASTNode *root = parser.parse();


        if (errorHandler.getErrorCount() > 0)
        {
            errorHandler.printErrors();
        }
        else
        {
            cout << "Parsing completed successfully!" << endl;
            PrintParseTree(root);
        }

    }
}
