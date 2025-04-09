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
#include "../token/token.hpp"
#include "symbolTable/symbolTable.hpp"
#include "../scope/scope.hpp"
#include <stack>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <iostream>

extern string nonTerminalKindToString[];

class Parser
{
private:
    // parse table
    ActionTable _actionTable;
    GotoTable _gotoTable;
    stack<StackItem> _stack;
    int _currState;

    action getCurrAction();
    void shift(action currAction);
    void reduce(action currAction);
    void reduceStatmentToNode(NonTerminalNode *node, productionRule rule);
    bool match(ASTNode *node, SyntaxKind type);
    bool match(ASTNode *node, NonTerminal type);

    // symbol table mangaement
    SymbolTable *_symbolTable;
    stack<scope *> _scopeStack;
    scope *_currRootScope;
    void updateScope();
    void updateSybolTable(ASTNode *node);

    // init functions
    void initProductionRules();
    void fillTables();

    // Follow sets
    unordered_map<NonTerminal, unordered_set<SyntaxKind>> _followSets;
    unordered_map<SyntaxKind, unordered_set<SyntaxKind>> _followTerminalsSets;
    SyntaxKind getNonTerminalFollowSetItem(NonTerminal nt);
    SyntaxKind getTerminalFollowSetItem(SyntaxKind kind);

    void initFollowSets();

    // Navigation and helpers
    vector<SyntaxToken *> _tokens;
    vector<productionRule> _rules;
    int _cursor;

    SyntaxToken *getNextToken();
    SyntaxToken *getCurrToken();
    SyntaxToken *peek(int index);
    void addProductionRule(productionRule rule);

    // error handling
    ErrorHandler *_errorHandler;

    void reportParsingError();

public:
    Parser(vector<SyntaxToken *> tokens, int numOfStates, ErrorHandler *handler, SymbolTable *symbolTable);

    ASTNode *parse();

    // Debugging
    void printStack();
    void printRules();
    void printFollowSet();
};

#endif
