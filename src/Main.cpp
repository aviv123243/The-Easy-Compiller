#include "headers/lexer.hpp"
#include "headers/parser.hpp"
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
        filePath = "demos\\DEMO2.EZ";
    }
//-------------------------------------    

    else
    {
        filePath = argv[1];
    }

    ifstream srcFile;
    srcFile.open(filePath);
    
    if (!srcFile.is_open()) {
        cerr << "Failed to open file: " << filePath << endl;
        return 1;
    }

    string line;
    stringstream srcCode;

    while (getline(srcFile,line))
    {
        srcCode << line;
    }
    
    Lexer l = Lexer(srcCode.str());
    vector<SyntaxToken *> tokens = l.GenerateTokes();
    //PrintTokens(&tokens);
    Parser p = Parser(&tokens);
    
    ExpressionNode *AST = p.Parse();
    PrintParseTree(AST);

    cout << "-------------------------------------" << endl;
    cout << p.getDiagnostics() << endl;

}





