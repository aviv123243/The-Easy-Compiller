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

#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define WHT "\e[0;37m"

using namespace std;
string getFileBaseName(string fileName);

int main(int argc, char **argv)
{
    string filePath;
    int errorLevel = 0;

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
        errorLevel = 1;
    }
    else
    {
        cout << GRN << "Lexing completed successfully!" << WHT << endl;

        SemanticAnalyzer semantic(&errorHandler, &symbolTable);
        Parser parser(tokens, 185, &errorHandler, &semantic);

        ASTNode *root = parser.parse();

        if (errorHandler.getErrorCount() > 0)
        {
            errorHandler.printErrors();
            errorLevel = 1;
        }
        else
        {
            cout <<GRN<< "Parsing completed successfully!" <<WHT<< endl;
            CodeGenarator codeGen(baseName + ".asm", root, &symbolTable);
            codeGen.genCode();

            cout << GRN<<"compiling finished!"<<WHT<<"\n\n";
        }

    }

    return errorLevel;
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