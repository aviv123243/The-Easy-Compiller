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
    : _actionTable(numOfStates), _gotoTable(numOfStates), _rules(), _stack(), _errorHandler(handler), _cursor(0), _tokens(tokens) {}

SyntaxToken *Parser::getNextToken()
{
    _cursor++;
    return peek(0);
    ;
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
    // Create a new terminalNode
    ASTNode *node = new TerminalNode(token);

    // Push to stack
    _stack.push(StackItem{state, node});
}

void Parser::reduce(int ruleNum)
{
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
        printStack();
        int state = _stack.top().state;

        act = _actionTable.get(state, token->kind);

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
                _errorHandler->addError(new SyntacticError(token));
            }

            getNextToken();
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
        cout << stackItemToString(item) << ", ";
        tempStack.push(item);
        _stack.pop();
    }

    while (!tempStack.empty())
    {
        item = tempStack.top();
        tempStack.pop();
        _stack.push(item);
    }
    
    cout << " ->" << endl;
}

void Parser::printRules()
{
    for (int i = 0; i < _rules.size(); i++)
    {
        cout << "Rule " << i << ": " << _rules[i].toString() << endl;
    }
}