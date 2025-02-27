#ifndef PARSER
#define PARSER

#include "productionRule/productionRule.hpp"
#include "parseTable/gotoTable/gotoTable.hpp"
#include "parseTable/actionTable/actionTable.hpp"
#include "productionRule/productionRule.hpp"
#include "stackItem/stackItem.hpp"
#include "../nodes/nodes.hpp"
#include "../errorHandler/errorHandler.hpp"
#include "../errors/errors.hpp"
#include <stack>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iostream>

extern string nonTerminalKindToString[];

class Parser
{
private:
    // parse table
    ActionTable _actionTable;
    GotoTable _gotoTable;
    stack<StackItem> _stack;

    vector<SyntaxToken *> _tokens;
    vector<productionRule> _rules;

    ErrorHandler *_errorHandler;

    int _cursor;

public:
    Parser(vector<SyntaxToken *> tokens, int numOfStates, ErrorHandler *handler);
    SyntaxToken *getNextToken();
    SyntaxToken *peek(int index);
    void addProductionRule(productionRule rule);
    void shift(int state, SyntaxToken *token);
    void reduce(int ruleNum);
    bool match(ASTNode *node, SyntaxKind type);
    bool match(ASTNode *node, NonTerminal type);
    ASTNode *parse();

    // Debugging
    void printStack();
    void printRules();
};

#endif
