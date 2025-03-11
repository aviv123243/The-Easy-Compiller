#include "../lexer/lexer.hpp"
#include "../token/token.hpp"
#include "../errorHandler/errorHandler.hpp"
#include "../parser/parser.hpp"
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

        Parser parser(tokens, 10, &errorHandler);
        parser.printFirstSet();
        parser.printFollowSet();
        parser.printRules();
        

        ASTNode *root = parser.parse();
        PrintParseTree(root);
    }
}
