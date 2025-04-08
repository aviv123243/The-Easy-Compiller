#include "grammerSymbol.hpp"
#include <string>
#include <sstream>

using namespace std;

string nonTerminalEnumToString[] = {
    "START",
    "PROGRAM",
    "FUNCTION_DECL",
    "PARAM_LIST",
    "PARAM_LIST_NON_EMPTY",
    "PARAM",
    "TYPE",
    "BASE_TYPE",
    "STMT_LIST",
    "STMT",
    "SIMPLE_STMT",
    "VAR_DECL_EXPR",
    "INIT_OPT",
    "ASSIGN_VALUE",
    "ASSIGN_EXPR",
    "ASSIGN_TARGET",
    "ASSIGN_OP",
    "IF_STMT",
    "WHILE_STMT",
    "CONDITION_OP",
    "FOR_STMT",
    "FOR_INIT",
    "EXPR_OPT",
    "FOR_UPDATE",
    "BODY",
    "EXPR_LIST",
    "EXPR_LIST_NON_EMPTY",
    "EXPR",
    "LOGICAL_EXPR",
    "RELATIONAL_EXPR",
    "ADD_EXPR",
    "MUL_EXPR",
    "UNARY_EXPR",
    "INCREMENT_EXPR",
    "ADDRESS_EXPR",
    "DEREFERENCE_EXPR",
    "PRIMARY_EXPR"
};


string nonTerminalToString(NonTerminal kind)
{
    stringstream res;
    res << "\e[1;34m<"
        << nonTerminalEnumToString[(int)kind]
        << ">\033[0m";

    return res.str();
}