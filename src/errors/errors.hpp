#ifndef __ERRORS
#define __ERRORS

#include "../token/token.hpp"
#include <string>
#include <sstream>

using namespace std;

#define RED "\e[0;31m"
#define WHT "\e[0;37m"

class Error
{
    protected:
        string _body;
        string _errorType;

    public:

        Error(string errorType) : _body("") 
        {
            stringstream errorHeader;
            errorHeader << RED << errorType << ": " << WHT;
            _errorType = errorHeader.str();
        }

        virtual string toString() 
        {
            return _errorType + _body;
        }
};

class SyntaxError : public Error
{
    private:
        int _line;
        int _column;

    public:
        SyntaxError(string body, SyntaxToken *token) : Error("Syntax Error")
        {
            _body = body + " with token on {" + to_string(token->line) + ":" + to_string(token->column) + "}\n";
        }
};

class SyntacticError : public Error
{
    public:
        SyntacticError(SyntaxToken * token) : Error("Parsing Error"){
            int line = token -> line;
            int column = token ->column;

            _body = " unvalid placment of token " + syntaxTokenToString(*token) + "on" + "{" + to_string(line) +":" + to_string(column) + "}\n";
        }

        SyntacticError(SyntaxToken * errorToken, SyntaxKind replacment) : Error("Parsing Error"){
            int line = errorToken -> line;
            int column = errorToken ->column;

            _body = " on {" + to_string(line) +":" + to_string(column) + "} with token " + syntaxTokenToString(*errorToken) + "\n mabe try using " + syntaxKindToString(replacment) + " instead\n";
        }

        SyntacticError() : Error("Parsing Error"){
            _body = " broken code structure";
        }

};

class semanticError : public Error
{
    public:
        semanticError(string body) : Error("Semantic Error") {_body = body;}

        semanticError(string body, SyntaxToken * token) : Error("Semantic Error"){
            int line = token -> line;
            int column = token ->column;

            _body = " on {" + to_string(line) +":" + to_string(column) + "} with token " + syntaxTokenToString(*token) + "\n" + body;
        }
  
};

#endif