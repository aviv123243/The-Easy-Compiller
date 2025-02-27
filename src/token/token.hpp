#ifndef __TOKEN
#define __TOKEN

#include <string>

using namespace std;

enum SyntaxKind
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
    UNEXPECTED_TOKEN,
    SYNTAX_KIND_COUNT
};

struct SyntaxToken
{
    SyntaxKind kind;
    string val;
    int line;
    int column;
};


string syntaxTokenToString(SyntaxToken token);
string syntaxKindToString(SyntaxKind kind);
void printSyntaxToken(SyntaxToken token);

#endif