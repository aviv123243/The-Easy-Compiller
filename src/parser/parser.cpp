#include "parser.hpp"
#include "../errors/errors.hpp"
#include "../nodes/nodes.hpp"
#include "stackItem/stackItem.hpp"
#include "../token/token.hpp"
#include "grammerSymbol/grammerSymbol.hpp"
#include "productionRule/productionRule.hpp"
#include "../symbolTable/functionEntry/functionEntry.hpp"
#include <vector>
#include <iostream>

#define PARSER_DEBUG

using namespace std;

Parser::Parser(vector<SyntaxToken *> tokens, int numOfStates, ErrorHandler *handler, SemanticAnalyzer *semanticAnalyser)
    : _actionTable(numOfStates), _gotoTable(numOfStates), _semanticAnalyzer(semanticAnalyser), _rules(), _stack(), _errorHandler(handler), _tokens(tokens), _cursor(0)
{
    _stack.push(StackItem{0, new NonTerminalNode(NonTerminal::START)});
    initProductionRules();
    fillTables();
    initFollowSets();
}

SyntaxToken *Parser::getNextToken()
{
    _cursor++;
    return peek(0);
}

SyntaxToken *Parser::peek(int index)
{
    if (_cursor + index >= _tokens.size())
    {
        SyntaxToken *resToken = new SyntaxToken();
        resToken->kind = SyntaxKind::END_OF_FILE;
        return resToken;
    }

    return _tokens[_cursor + index];
}

SyntaxToken *Parser::getCurrToken()
{
    return peek(0);
}

void Parser::addProductionRule(productionRule rule)
{
    _rules.push_back(rule);
}

bool Parser::match(ASTNode *node, SyntaxKind type)
{
    if (node->GetType() != GrammarSymbolType::TERMINAL)
    {
        _errorHandler->addError(new SyntacticError());
        return false;
    }

    TerminalNode *terminalNode = (TerminalNode *)node;
    if (terminalNode->getTerminalKind() != type)
    {
        _errorHandler->addError(new SyntacticError(terminalNode->getToken()));
        return false;
    }

    return true;
}

bool Parser::match(ASTNode *node, NonTerminal type)
{
    bool res = true;

    if (node->GetType() != GrammarSymbolType::NON_TERMINAL)
    {
        res = false;
    }

    if (((NonTerminalNode *)node)->getNonTerminalKind() != type)
    {
        res = false;
    }

    return res;
}

action Parser::getCurrAction()
{
    return _actionTable.get(_stack.top().state, peek(0)->kind);
}

void Parser::shift(action currAction)
{
    int state = currAction.num;
    SyntaxToken *token = getCurrToken();

#ifdef PARSER_DEBUG
    cout << "Shifting to state " << currAction.num << " with token " << syntaxTokenToString(*token) << endl;
#endif

    // Create a new terminalNode
    ASTNode *node = new TerminalNode(token);

    // assign the node type for semantic analysis
    _semanticAnalyzer->assignNodeType(node);

    // Push to stack
    _stack.push(StackItem{state, node});

    // Update current state
    _currState = state;

    // update the scope
    _semanticAnalyzer -> updateScope(getCurrToken());

    // proceed to next token
    getNextToken();
}

void Parser::reduce(action currAction)
{
    int productionRuleNum = currAction.num;

#ifdef PARSER_DEBUG
    cout << "Reducing with rule " << productionRuleNum << endl;
#endif

    productionRule rule = _rules[productionRuleNum];

#ifdef PARSER_DEBUG
    cout << rule.toString() << endl;
#endif

    // Create a new nonTerminalNode
    NonTerminalNode *node = new NonTerminalNode(rule.getLeft());

    if ((rule.getType(0) == GrammarSymbolType::TERMINAL) && (rule.getTerminal(0) == EPSILON)) // if rule is empty return without adding children
    {
        _stack.push(StackItem{_gotoTable.get(_stack.top().state, rule.getLeft()), node});
    }
    else
    {
        reduceStatmentToNode(node, rule);

        // Push to stack
        int currentState = _stack.top().state;
        _stack.push(StackItem{_gotoTable.get(currentState, rule.getLeft()), node});

        // Update current state
        _currState = currentState;
    }

    cout <<"AAAAA";
    _semanticAnalyzer->assignNodeType(node); // assign the node type for semantic analysis
    cout << "BBBBB";
    _semanticAnalyzer-> updateSybolTable(_stack.top().node);     // update the symbol table with the new node
    cout << "CCCCC";
}

void Parser::reduceStatmentToNode(NonTerminalNode *node, productionRule rule)
{
    // Pop from stack and create the new node
    for (int i = rule.getNumOfRightSideSymbols() - 1; i >= 0; i--)
    {
        if (rule.getType(i) == GrammarSymbolType::TERMINAL)
        {
            match(_stack.top().node, rule.getTerminal(i));
        }

        if (rule.getType(i) == GrammarSymbolType::NON_TERMINAL)
        {
            match(_stack.top().node, rule.getNonTerminal(i));
        }

        node->AddChildToFront(_stack.top().node);
        _stack.pop();
    }
}



ASTNode *Parser::parse()
{
    action currAction;
    bool panic = false;

    do
    {
#ifdef PARSER_DEBUG
        cout << endl;
        printStack();
        cout << endl;
#endif

        int state = _stack.top().state;

        currAction = getCurrAction();

#ifdef PARSER_DEBUG
        cout << "state:" << state << " token:" << syntaxTokenToString(*peek(0)) << " Action: " << actionTypeToString(currAction) << endl;
#endif

        if (currAction.type == actionType::REDUCE)
        {
            reduce(currAction);
            panic = false; // reset panic mode
        }
        else if (currAction.type == actionType::SHIFT)
        {
            shift(currAction);
            panic = false; // reset panic mode
        }
        else if (currAction.type == actionType::DEFAULT) // error
        {
            if (!panic)
            {
                panic = true; // enter panic mode
                reportParsingError();
            }

            getNextToken();

            if (getCurrToken()->kind == SyntaxKind::END_OF_FILE)
            {
                currAction.type = actionType::ACCEPT; // end of file token
            }
        }

    } while (currAction.type != actionType::ACCEPT);

    _stack.pop(); // pop the end of file token

    return _stack.top().node;
}

void Parser::reportParsingError()
{
    // adding error to the error handler
    // with the expected token
    ASTNode *node = _stack.top().node;
    SyntaxKind recoveryKind;
    if (node->GetType() == GrammarSymbolType::TERMINAL)
    {
        recoveryKind = getTerminalFollowSetItem(((TerminalNode *)node)->getToken()->kind);
        _errorHandler->addError(new SyntacticError(peek(0), recoveryKind));
    }
    else
    {
        recoveryKind = getNonTerminalFollowSetItem(((NonTerminalNode *)node)->getNonTerminalKind());
        _errorHandler->addError(new SyntacticError(peek(0), recoveryKind));
    }
}

SyntaxKind Parser::getNonTerminalFollowSetItem(NonTerminal nt)
{
    SyntaxKind res = SyntaxKind::UNEXPECTED_TOKEN;

    auto it = _followSets.find(nt);
    if (it != _followSets.end())
    {
        res = *it->second.begin();
    }

    return res; // return the first item in the follow set
}

SyntaxKind Parser::getTerminalFollowSetItem(SyntaxKind kind)
{
    SyntaxKind res = SyntaxKind::UNEXPECTED_TOKEN;

    auto it = _followTerminalsSets.find(kind);
    if (it != _followTerminalsSets.end())
    {
        res = *it->second.begin();
    }

    return res; // return the first item in the follow set
}

void Parser::printStack()
{
    if (_stack.empty())
    {
        cout << "[Empty Stack]" << endl;
        return;
    }

    stack<StackItem> tempStack;
    StackItem item;

    while (!_stack.empty())
    {
        item = _stack.top();
        tempStack.push(item);
        _stack.pop();
    }

    while (!tempStack.empty())
    {
        item = tempStack.top();
        cout << stackItemToString(item) << ", ";
        tempStack.pop();
        _stack.push(item);
    }

    cout << " ->" << endl;
}

void Parser::printRules()
{
    for (int i = 0; i < _rules.size(); i++)
    {
        cout << "\e[0;31mRule " << i << "\e[0;37m : " << _rules[i].toString() << endl;
    }
}

void Parser::printFollowSet()
{
    for (int i = 0; i < _rules.size(); i++)
    {
        NonTerminal nt = _rules[i].getLeft();
        cout << "follow(" << nonTerminalToString(nt) << ") = {";

        int j = _followSets[_rules[i].getLeft()].size(); // size of follow set
        for (const SyntaxKind &terminal : _followSets[nt])
        {
            cout << syntaxKindToString(terminal);
            if (j != 1)
                cout << ", ";

            j--;
        }

        cout << "}" << endl;
    }

    for (int i = 0; i < SYNTAX_KIND_COUNT; i++)
    {
        SyntaxKind kind = (SyntaxKind)i;
        cout << "follow(" << syntaxKindToString(kind) << ") = {";

        int j = _followTerminalsSets[kind].size(); // size of follow set
        for (const SyntaxKind &terminal : _followTerminalsSets[kind])
        {
            cout << syntaxKindToString(terminal);
            if (j != 1)
                cout << ", ";

            j--;
        }

        cout << "}" << endl;
    }
}
