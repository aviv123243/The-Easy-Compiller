#ifndef __ERRORS
#define __ERRORS

#include <string>
using namespace std;

class Error
{
    protected:
        string _body;

    public:
        Error(string body) : _body(body) {}

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

#endif