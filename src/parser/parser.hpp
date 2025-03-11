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
    bool match(ASTNode *node, SyntaxKind type);
    bool match(ASTNode *node, NonTerminal type);

    //First and Follow sets
    unordered_map<NonTerminal, unordered_set<SyntaxKind>> _firstSets;
    unordered_map<NonTerminal, unordered_set<SyntaxKind>> _followSets;
    
    unordered_set<SyntaxKind> &computeFirst(NonTerminal nt);
    unordered_set<SyntaxKind> &computeFollow(NonTerminal nt);
    void computeFirstSets();
    void computeFollowSets();

    //Navigation and helpers
    vector<SyntaxToken *> _tokens;
    vector<productionRule> _rules;
    int _cursor;

    SyntaxToken *getNextToken();
    SyntaxToken *getCurrToken();
    SyntaxToken *peek(int index);
    void addProductionRule(productionRule rule);

    //error handling
    ErrorHandler *_errorHandler;

    

public:
    Parser(vector<SyntaxToken *> tokens, int numOfStates, ErrorHandler *handler);
    
    
    ASTNode *parse();

    // Debugging
    void printStack();
    void printRules();
    void printFirstSet();
    void printFollowSet();
};

#endif
