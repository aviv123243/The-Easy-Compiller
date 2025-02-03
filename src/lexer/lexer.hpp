#ifndef __LEXER
#define __LEXER

#include "../DFA/DFA.hpp"
#include "../errorHandler/errorHandler.hpp"
#include "../errors/errors.hpp"
#include <string>
#include <vector>
#include <sstream>

using namespace std;

#define NUM_OF_STATES 107

enum syntaxKind
{
    INTEGER_LITERAL,
    FLOAT_LITERAL,
    STRING_LITERAL,
    IDENTIFIER,
    KEYWORD_IF,
    KEYWORD_WHILE,
    KEYWORD_FOR,
    KEYWORD_FN,
    KEYWORD_RET,
    KEYWORD_INT,
    KEYWORD_FLOAT,
    EQUALS,
    COMMA,
    PLUS,
    MINUS,
    SLASH,
    STAR,
    AMPERSAND,
    PIPE,
    BANG,
    SEMICOLON,
    LESS_THAN,
    GREATER_THAN,
    OPEN_PAREN,
    CLOSED_PAREN,
    OPEN_CURLY,
    CLOSED_CURLY,
    OPEN_BRACKET,
    CLOSED_BRACKET,
    RIGHT_ARROW,
    PLUS_PLUS,
    DASH_DASH,
    PLUS_EQUALS,
    DASH_EQUALS,
    SLASH_EQUALS,
    STAR_EQUALS,
    EQUALS_EQUALS,
    LESS_THAN_EQUALS,
    GREATER_THAN_EQUALS,
    AMPERSAND_AMPERSAND,
    PIPE_PIPE,
    BANG_EQUALS,
    END_OF_FILE,
    UNEXPECTED_TOKEN
};

extern string syntaxkindToString[];

extern syntaxKind endStateToSyntaxKind[];

struct SyntaxToken
{
    syntaxKind kind;
    string val;
};

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
    vector<SyntaxToken> getTokens();
    SyntaxToken getNextToken();
    SyntaxToken getNextToken2();
    void updatePosition(char ch);
    void printTransitionMatrix() const;
};

syntaxKind getSyntaxKind(int state);
string syntaxTokenToString(SyntaxToken token);
bool isSkipState(int state);
bool isWhitespace(char ch);
#endif