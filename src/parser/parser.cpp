#include "parser.hpp"
#include "../errors/errors.hpp"
#include "../nodes/nodes.hpp"
#include "stackItem/stackItem.hpp"
#include "../token/token.hpp"
#include "grammerSymbol/grammerSymbol.hpp"
#include "productionRule/productionRule.hpp"
#include <vector>
#include <iostream>

using namespace std;

Parser::Parser(vector<SyntaxToken *> tokens, int numOfStates, ErrorHandler *handler)
    : _actionTable(numOfStates), _gotoTable(numOfStates), _rules(), _stack(), _errorHandler(handler), _cursor(0), _tokens(tokens) 
    {
        productionRule S(NonTerminal::STATEMENT);
        S.addSymbol(NonTerminal::PRIMARY_EXPRESSION);
        S.addSymbol(NonTerminal::PRIMARY_EXPRESSION);

        productionRule exp(NonTerminal::EXPRESSION);
        exp.addSymbol(NonTerminal::PRIMARY_EXPRESSION);
        exp.addSymbol(NonTerminal::PRIMARY_EXPRESSION);

        productionRule primaryExp1(NonTerminal::PRIMARY_EXPRESSION);
        primaryExp1.addSymbol(SyntaxKind::IDENTIFIER);
        primaryExp1.addSymbol(NonTerminal::PRIMARY_EXPRESSION);

        productionRule primaryExp2(NonTerminal::PRIMARY_EXPRESSION);
        primaryExp2.addSymbol(SyntaxKind::FLOAT_LITERAL);

        addProductionRule(S);
        addProductionRule(exp);
        addProductionRule(primaryExp1);
        addProductionRule(primaryExp2);

        //state 0
        _actionTable.add(0, SyntaxKind::IDENTIFIER, action{actionType::SHIFT, 3});
        _actionTable.add(0, SyntaxKind::FLOAT_LITERAL, action{actionType::SHIFT, 4});
        _gotoTable.add(0, NonTerminal::EXPRESSION, 1);
        _gotoTable.add(0, NonTerminal::PRIMARY_EXPRESSION, 2);

        //state 1
        _actionTable.add(1, SyntaxKind::END_OF_FILE, action{actionType::ACCEPT, 0});

        //state 2
        _actionTable.add(2, SyntaxKind::IDENTIFIER, action{actionType::SHIFT, 6});
        _actionTable.add(2, SyntaxKind::FLOAT_LITERAL, action{actionType::SHIFT, 7});
        _gotoTable.add(2, NonTerminal::PRIMARY_EXPRESSION, 5);

        //state 3
        _actionTable.add(3, SyntaxKind::IDENTIFIER, action{actionType::SHIFT, 3});
        _actionTable.add(3, SyntaxKind::FLOAT_LITERAL, action{actionType::SHIFT, 4});
        _gotoTable.add(3, NonTerminal::PRIMARY_EXPRESSION, 8);

        //state 4
        _actionTable.add(4, SyntaxKind::IDENTIFIER, action{actionType::REDUCE, 3});
        _actionTable.add(4, SyntaxKind::FLOAT_LITERAL, action{actionType::REDUCE, 3});

        //state 5
        _actionTable.add(5, SyntaxKind::END_OF_FILE, action{actionType::REDUCE, 1});

        //state 6
        _actionTable.add(6, SyntaxKind::IDENTIFIER, action{actionType::SHIFT, 6});
        _actionTable.add(6, SyntaxKind::FLOAT_LITERAL, action{actionType::SHIFT, 7});
        _gotoTable.add(6, NonTerminal::PRIMARY_EXPRESSION, 9);

        //state 7
        _actionTable.add(7, SyntaxKind::END_OF_FILE, action{actionType::REDUCE, 3});
        
        //state 8
        _actionTable.add(8, SyntaxKind::IDENTIFIER, action{actionType::REDUCE, 2});
        _actionTable.add(8, SyntaxKind::FLOAT_LITERAL, action{actionType::REDUCE, 2});

        //state 9
        _actionTable.add(9, SyntaxKind::END_OF_FILE, action{actionType::REDUCE, 2});

        _stack.push(StackItem{0, new NonTerminalNode(NonTerminal::PROGRAM)});
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
    if (node->GetType() != GrammarSymbolType::NON_TERMINAL)
    {
        return false;
    }

    if (((NonTerminalNode *)node)->getNonTerminalKind() != type)
    {
        return false;
    }

    return true;
}

void Parser::shift(int state, SyntaxToken *token)
{
    cout << "Shifting to state " << state << " with token " << syntaxTokenToString(*token) << endl;
    // Create a new terminalNode
    ASTNode *node = new TerminalNode(token);

    // Push to stack
    _stack.push(StackItem{state, node});
}

void Parser::reduce(int ruleNum)
{
    cout << "Reducing with rule " << ruleNum << endl;
    productionRule rule = _rules[ruleNum];

    // Create a new nonTerminalNode
    NonTerminalNode *node = new NonTerminalNode(rule.getLeft());

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

    // Push to stack
    _stack.push(StackItem{_gotoTable.get(_stack.top().state, rule.getLeft()), node});
}

ASTNode *Parser::parse()
{
    SyntaxToken *token = peek(0);
    action act;

    do
    {
        cout << endl;
        printStack();
        cout << endl;
        int state = _stack.top().state;

        act = _actionTable.get(state, peek(0)->kind);
        cout << "state:"<< state << " token:"<< syntaxTokenToString(*peek(0))<<" Action: " << actionTypeToString(act) << endl;
        
        if (act.type == actionType::REDUCE)
        {
            reduce(act.num);
        }
        else
        {
            if (act.type == actionType::SHIFT)
            {
                shift(act.num, token);
            }

            else if (act.type == actionType::ERROR)
            {
                cout << "Error" << endl;
                _errorHandler->addError(new SyntacticError(token));
            }

            token = getNextToken();
        }
     

    } while (act.type != actionType::ACCEPT);

    return _stack.top().node;
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
        cout << "\e[0;31mRule "  << i << "\e[0;37m : " << _rules[i].toString() << endl;
    }
}