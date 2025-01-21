#ifndef __LEXER
#define __LEXER

#include "DFA.hpp"
#include <string>
#include <vector>
#include <sstream>

using namespace std;

enum syntaxKind { INTEGER_LITERAL, FLOAT_LITERAL, STRING_LITERAL, IDENTIFIER, KEYWORD_IF, KEYWORD_WHILE, KEYWORD_FOR, KEYWORD_FN,
                    KEYWORD_RET, KEYWORD_INT, KEYWORD_FLOAT, EQUALS, COMMA, PLUS, MINUS, SLASH, STAR, AMPERSAND, PIPE, BANG, SEMICOLON,
                     LESS_THAN, GREATER_THAN, OPEN_PAREN, CLOSED_PAREN, OPEN_CURLY, CLOSED_CURLY, OPEN_BRACKET, CLOSED_BRACKET, RIGHT_ARROW,
                    PLUS_EQUALS, DASH_EQUALS, SLASH_EQUALS, STAR_EQUALS, EQUALS_EQUALS, LESS_THAN_EQUALS, GREATER_THAN_EQUALS, 
                    AMPERSAND_AMPERSAND, PIPE_PIPE, BANG_EQUALS, END_OF_FILE, UNEXPECTED_TOKEN };


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
        int _cursor;
        string _srcFile;
        DFA _dfa;

    public:
        Lexer(string DFAConfigFile, string srcFile) : _dfa(DFAConfigFile), _srcFile(srcFile) {_cursor = 0;}
        void printTransitionMatrix() const;
        SyntaxToken getNextToken();
};

syntaxKind getSyntaxKind(int state);
string syntaxTokenToString(SyntaxToken token);
bool isWhitespace(char ch);
#endif