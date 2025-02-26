#ifndef __PARSER_DEBUGGING_UTILS
#define __PARSER_DEBUGGING_UTILS

#include "../globalEnums.hpp"
#include "../nodes/Nodes.hpp"
#include <string>

using namespace std;

string nonTerminalKindToString[] = {
    "PROGRAM", "STATEMENT", "EXPRESSION", "BINARY_EXPRESSION", "UNARY_EXPRESSION", 
    "PRIMARY_EXPRESSION", "LITERAL_EXPRESSION", "IDENTIFIER_EXPRESSION", 
    "PARENTHESIZED_EXPRESSION", "ASSIGNMENT_EXPRESSION", "CALL_EXPRESSION", 
    "ARGUMENT_LIST", "IF_STATEMENT", "WHILE_STATEMENT", "FOR_STATEMENT", 
    "FUNCTION_DECLARATION", "RETURN_STATEMENT", "VARIABLE_DECLARATION", 
    "TYPE", "BLOCK", "STATEMENT_LIST", "EXPRESSION_STATEMENT", "EMPTY_STATEMENT"
};

string AstNodeToString(ASTNode *node)
{
    if(node->GetType() == GrammarSymbolType::TERMINAL)
    {
        return syntaxkindToString[((TerminalNode *)node)->getTerminalKind()];
    }
    else
    {
        return nonTerminalKindToString[((NonTerminalNode *)node)->getNonTerminalKind()];
    }   
}
void printAstNode(ASTNode *node)
{
    cout << AstNodeToString(node) << endl;
}

#endif