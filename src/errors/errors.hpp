#ifndef __ERRORS
#define __ERRORS

#include "../token/token.hpp"
#include <string>
using namespace std;

class Error
{
    protected:
        string _body;

    public:
        Error(string body) : _body(body) {}
        Error() : _body("") {}

        virtual string toString() const = 0;  
};

class SyntaxError : public Error
{
    private:
        int _line;
        int _column;

    public:
        SyntaxError(string body, int line, int column) : Error(body), _line(line), _column(column) {}

        string toString() const override
        {
            return "Syntax Error: " + _body + " in " + to_string(_line) + ":" + to_string(_column);
        }
};

class SyntacticError : public Error
{
    public:
        SyntacticError(SyntaxToken * token) {
            int line = token -> line;
            int column = token ->column;

            _body = "unvalid placment of token " + syntaxTokenToString(*token) + "on" + "{" + to_string(line) +":" + to_string(column) + "}\n";
        }

        SyntacticError(SyntaxToken * errorToken, SyntaxKind replacment) {
            int line = errorToken -> line;
            int column = errorToken ->column;

            _body = "Parser error on {" + to_string(line) +":" + to_string(column) + "} with token " + syntaxTokenToString(*errorToken) + "\n mabe try using " + syntaxKindToString(replacment) + " instead\n";
        }

        SyntacticError() {
            _body = "broken code structure";
        }

        string toString() const override
        {
            return "SyntaticError: " + _body;
        }
};

class semanticError : public Error
{
    public:
        semanticError(string body) {_body = body;}

        string toString() const override
        {
            return "semanticError: " + _body;
        }
        
};

#endif