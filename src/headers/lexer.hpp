#ifndef __LEXER
#define __LEXER

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
    
        string _sorceCode;
        int _cursor;
        int _codeLen;
        char _current;
        vector<string> kewWords = {"if","for","while","return","fn","int"};

        void next() 
        {
            _cursor++;
            _current = peek(0);
        } 

        SyntaxToken * nextToken();

    public:
        Lexer(string sorceCode)
        {
            _sorceCode = sorceCode;
            _cursor = 0;
            _codeLen = sorceCode.length();
            _current = peek(0);
        }

        char GetCurrent() const {return _current;}
       
        vector<SyntaxToken *> GenerateTokes();

        char peek(int);     
};

void PrintTokens(vector<SyntaxToken *> * tokens);

void PrintTokensNoWhiteSpace(vector<SyntaxToken *> * tokens);

string SyntaxKindToString(syntaxKind kind);

string SyntaxTokenToString(SyntaxToken * token);



#endif