#ifndef __LEXER
#define __LEXER

struct SyntaxToken;

#include "../DFA/DFA.hpp"
#include "../errorHandler/errorHandler.hpp"
#include "../errors/errors.hpp"
#include "../token/token.hpp"
#include "../parser/grammerSymbol/grammerSymbol.hpp"
#include <string>
#include <vector>
#include <sstream>

using namespace std;

#define NUM_OF_STATES 107

extern SyntaxKind endStateToSyntaxKind[];

class Lexer
{
private:
    string _srcFile;
    DFA _dfa;
    int _cursor;
    int _fileSize;

    ErrorHandler *_errorHandler;

    int _currLine;
    int _currColumn;

public:
    Lexer(string srcFile, string DFAConfigFile, ErrorHandler *handler);
    vector<SyntaxToken *> getTokens();
    SyntaxToken *getNextToken();
    void updatePosition(char ch);
    void printTransitionMatrix() const;
};

SyntaxKind getSyntaxKind(int state);
string syntaxTokenToString(SyntaxToken token);
bool isSkipState(int state);
bool isWhitespace(char ch);
#endif