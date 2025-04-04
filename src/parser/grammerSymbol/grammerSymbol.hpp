#ifndef __GAMMER_SYMBOL
#define __GAMMER_SYMBOL

#include <string>

using namespace std;



enum GrammarSymbolType
{
    TERMINAL,
    NON_TERMINAL
};

enum NonTerminal
{
    START,
    PROGRAM,
    FUNCTION_DECL,
    PARAM_LIST,
    PARAM_TAIL,
    PARAM,
    TYPE,
    BASE_TYPE,
    TYPE_TAIL,
    STMT_LIST,
    STMT,
    BODY,
    VAR_DECL_STMT,
    VAR_DECL_EXPR,
    INIT_OPT,
    ASSIGN_VALUE,       
    ASSIGN_STMT,
    ASSIGN_EXPR,
    ASSIGN_TARGET,
    ASSIGN_OP,
    IF_STMT,
    WHILE_STMT,
    CONDITION_OP,       
    FOR_STMT,
    FOR_INIT,
    EXPR_OPT,
    FOR_UPDATE,
    RETURN_STMT,
    EXPR_STMT,
    EXPR_LIST,
    EXPR_TAIL,
    EXPR,
    REL_OP_TAIL,
    REL_OP,
    UNARY_EXPR,
    UNARY_OP,
    POINTER_REF_EXPR,    
    POST_INCREMENT,     
    PRE_INCREMENT,      
    SIMPLE_EXPR,
    ADD_OP_TAIL,
    ADD_OP,
    TERM,
    MUL_OP_TAIL,
    MUL_OP,
    FACTOR,
    NON_TERMINAL_COUNT
};
 

string nonTerminalToString(NonTerminal kind);

#endif