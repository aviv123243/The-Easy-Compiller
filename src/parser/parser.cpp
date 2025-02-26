#include "parser.hpp"
#include "../errors/errors.hpp"
#include "../nodes/nodes.hpp"
#include "../token/token.hpp"
#include "grammerSymbol/grammerSymbol.hpp"
#include <vector>

Parser::Parser(vector<SyntaxToken *> tokens, int numOfStates, ErrorHandler *handler)
    : _actionTable(numOfStates), _gotoTable(numOfStates), _rules(), _stack(), _errorHandler(handler), _cursor(0), _tokens(tokens) {}

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

bool Parser::match(ASTNode *node, NonTerminalKind type)
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
    ASTNode *node = new TerminalNode(token->kind, token);

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
            if (!match(_stack.top().node, rule.getTerminal(i)))
            {
                
            }
        }
        else
        {
            if (!match(_stack.top().node, rule.getNonTerminal(i)))
            {
                throw runtime_error("Syntax error");
            }
        }

        node->AddChildToFront(_stack.top().node);
        _stack.pop();
    }

    // Push to stack
    _stack.push(StackItem{_gotoTable.get(_stack.top().state, rule.getLeft()), node});
}