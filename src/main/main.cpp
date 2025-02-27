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

        Parser parser(tokens, 4, &errorHandler);

        cout << "Parsing...1" << endl;

        productionRule exp(NonTerminal::EXPRESSION);
        exp.addSymbol(NonTerminal::PRIMARY_EXPRESSION);
        exp.addSymbol(NonTerminal::PRIMARY_EXPRESSION);

        cout << "Parsing...2" << endl;

        productionRule primaryExp1(NonTerminal::PRIMARY_EXPRESSION);
        primaryExp1.addSymbol(SyntaxKind::IDENTIFIER);
        primaryExp1.addSymbol(NonTerminal::PRIMARY_EXPRESSION);

        cout << "Parsing...3" << endl;

        productionRule primaryExp2(NonTerminal::PRIMARY_EXPRESSION);
        primaryExp2.addSymbol(SyntaxKind::FLOAT_LITERAL);

        cout << "Parsing...4" << endl;

        parser.addProductionRule(exp);
        parser.addProductionRule(primaryExp1);
        parser.addProductionRule(primaryExp2);

        cout << "Parsing...5" << endl;

        parser.printStack();
        ASTNode *root = parser.parse();

        cout << "Parsing...6" << endl;

        PrintParseTree(root, "", true);
    }
}
