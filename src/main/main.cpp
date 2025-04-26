#include "../lexer/lexer.hpp"
#include "../token/token.hpp"
#include "../errorHandler/errorHandler.hpp"
#include "../parser/parser.hpp"
#include "../semantic/semantic.hpp"
#include "../codeGenarator/codeGen.hpp"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;
string getFileBaseName(string fileName);

int main(int argc, char **argv)
{
    string filePath;

    if (argc != 2)
    {
        cout << "ERROR: Please enter the input file";
        return 1;
    }

    filePath = argv[1];
    string baseName = getFileBaseName(filePath);

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
        Parser parser(tokens, 185, &errorHandler, &semantic);

        ASTNode *root = parser.parse();

        PrintParseTree(root);
        // parser.printRules();

        if (errorHandler.getErrorCount() > 0)
        {
            cout << "Parsing failed with errors!" << endl;
            errorHandler.printErrors();
        }
        else
        {
            cout << "Parsing completed successfully!" << endl;
            cout << "Generating code to " << baseName << ".asm" << endl;
            CodeGenarator codeGen(baseName + ".asm", root, &symbolTable);
            codeGen.genCode();
        }

        cout << "compiling finished!";

        // symbolTable.print();
    }
}

string getFileBaseName(string fileName)
{

    size_t lastSlash = fileName.find_last_of("\\/");
    if (lastSlash == string::npos)
        lastSlash = -1; 

    size_t lastDot = fileName.find_last_of('.');
    if (lastDot == string::npos)
        lastDot = fileName.length(); 

    string baseName = fileName.substr(lastSlash + 1, lastDot - lastSlash - 1);

    return baseName;
}