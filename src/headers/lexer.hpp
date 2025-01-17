#ifndef __LEXER
#define __LEXER

#include "DFA.hpp"
#include <string>
#include <vector>

using namespace std;

enum syntaxKind
{
    INTEGER_LITERAL,
    IDENTIFIER,
    KEYWORD_IF,
    KEYWORD_WHILE,
    KEYWORD_FOR,
    KEYWORD_FN,
    KEYWORD_RETURN,
    RIGHT_ARROW,
    ASSIGN,
    INT,
    COMMA,

    PLUS,
    MINUS,
    SLASH,
    STAR,
    AMPERSAND,
    PIPE,

//not inplamanted 
    PLUS_EQUALS,
    DASH_EQUALS,
    SLASH_EQUALS,
    STAR_EQUALS,
//^^^^^^^^^^^^^^^^^

    OPEN_PAREN,
    CLOSED_PAREN,
    OPEN_CURLY,
    CLOSED_CURLY,
    OPEN_BRACKET,
    CLOSED_BRACKET,
    
    SEMICOLON,
    LESS_THAN,
    GREATER_THAN,
    
    BANG,
    EQUALS_EQUALS,
    LESS_THAN_EQUALS,
    GREATER_THAN_EQUALS,
    AMPERSAND_AMPERSAND,
    PIPE_PIPE,
    BANG_EQUALS,
    END_OF_FILE,
    WHITESPACE,
    UNEXPECTED_TOKEN
};
    
struct SyntaxToken
{
    syntaxKind kind;
    string val;
};

class Lexer
{
    private:
        DFA dfa;

    public:
        // Lexer(string srcFile);
        // SyntaxToken getNextToken(); const

};





#endif