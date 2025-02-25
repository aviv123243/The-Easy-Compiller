#ifndef PARSER
#define PARSER

#include "../lexer/lexer.hpp"
// #include "../nodes/nodes.hpp"
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iostream>

enum GrammarSymbolType
{
    TERMINAL,
    NON_TERMINAL
};

enum NonTerminal
{
    PROGRAM,
    STATEMENT,
    EXPRESSION,
    BINARY_EXPRESSION,
    UNARY_EXPRESSION,
    PRIMARY_EXPRESSION,
    LITERAL_EXPRESSION,
    IDENTIFIER_EXPRESSION,
    PARENTHESIZED_EXPRESSION,
    ASSIGNMENT_EXPRESSION,
    CALL_EXPRESSION,
    ARGUMENT_LIST,
    IF_STATEMENT,
    WHILE_STATEMENT,
    FOR_STATEMENT,
    FUNCTION_DECLARATION,
    RETURN_STATEMENT,
    VARIABLE_DECLARATION,
    TYPE,
    BLOCK,
    STATEMENT_LIST,
    EXPRESSION_STATEMENT,
    EMPTY_STATEMENT,
    NON_TERMINAL_COUNT
};

class Parser
{
    private:
        vector<SyntaxToken> _tokens;

    public:
};

#endif

