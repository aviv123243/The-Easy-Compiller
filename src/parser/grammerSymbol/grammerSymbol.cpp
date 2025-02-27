#include "grammerSymbol.hpp"
#include <string>
#include <sstream>

using namespace std;

string nonTerminalEnumToString[] = {
    "PROGRAM", "STATEMENT", "EXPRESSION", "BINARY_EXPRESSION", "UNARY_EXPRESSION",
    "PRIMARY_EXPRESSION", "LITERAL_EXPRESSION", "IDENTIFIER_EXPRESSION",
    "PARENTHESIZED_EXPRESSION", "ASSIGNMENT_EXPRESSION", "CALL_EXPRESSION",
    "ARGUMENT_LIST", "IF_STATEMENT", "WHILE_STATEMENT", "FOR_STATEMENT",
    "FUNCTION_DECLARATION", "RETURN_STATEMENT", "VARIABLE_DECLARATION",
    "TYPE", "BLOCK", "STATEMENT_LIST", "EXPRESSION_STATEMENT", "EMPTY_STATEMENT"};

string nonTerminalToString(NonTerminal kind)
{
    stringstream res;
    res << "\e[1;34m<"
        << nonTerminalEnumToString[(int)kind]
        << ">\033[0m";

    return res.str();
}