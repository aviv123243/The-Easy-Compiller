#include "token.hpp"
#include <sstream>
#include <iostream>

using namespace std;

string syntaxKindEnumToString[] = {
            "INTEGER_LITERAL", "FLOAT_LITERAL", "CHAR_LITERAL", "STRING_LITERAL", "IDENTIFIER", "KEYWORD_IF", "KEYWORD_ELSE", "KEYWORD_WHILE", "KEYWORD_FOR",
            "KEYWORD_FN", "KEYWORD_RET", "KEYWORD_INT", "KEYWORD_FLOAT", "KEYWORD_CHAR", "EQUALS", "COMMA", "PLUS", 
            "MINUS", "SLASH", "STAR", "AMPERSAND","PIPE", "CARET", "TILDE", 
            "BANG", "SEMICOLON", "LESS_THAN", "GREATER_THAN", "OPEN_PAREN", "CLOSED_PAREN", "OPEN_CURLY", "CLOSED_CURLY", "OPEN_BRACKET",
            "CLOSED_BRACKET", "RIGHT_ARROW", "PLUS_PLUS", "MINUS_MINUS", "PLUS_EQUALS", "MINUS_EQUALS", "SLASH_EQUALS", "STAR_EQUALS",
            "AMPERSAND_EQUALS","PIPE_EQUALS", "CARET_EQUALS", "TILDE_EQUALS", "EQUALS_EQUALS",
            "LESS_THAN_EQUALS", "GREATER_THAN_EQUALS", "AMPERSAND_AMPERSAND", "PIPE_PIPE", "BANG_EQUALS", "END_OF_FILE", "UNEXPECTED_TOKEN"
};


string syntaxTokenToString(SyntaxToken token)
{
    stringstream res;
    string tokenValue = token.val;
    res << syntaxKindToString(token.kind)
        << " ";

    if (!tokenValue.empty())
    {
        res << "| " << tokenValue;
    }

    return res.str();
}

string syntaxKindToString(SyntaxKind kind)
{
    stringstream res;
    res << "\e[0;36m"
        << syntaxKindEnumToString[kind]
        << "\e[0m";

    return res.str();
}

void printSyntaxToken(SyntaxToken token)
{
    cout << syntaxTokenToString(token) << endl;
}