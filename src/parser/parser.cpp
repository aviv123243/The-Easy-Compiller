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

    // state 0
    _actionTable.add(0, SyntaxKind::IDENTIFIER, action{actionType::SHIFT, 3});
    _actionTable.add(0, SyntaxKind::FLOAT_LITERAL, action{actionType::SHIFT, 4});
    _gotoTable.add(0, NonTerminal::EXPRESSION, 1);
    _gotoTable.add(0, NonTerminal::PRIMARY_EXPRESSION, 2);

    // state 1
    _actionTable.add(1, SyntaxKind::END_OF_FILE, action{actionType::ACCEPT, 0});

    // state 2
    _actionTable.add(2, SyntaxKind::IDENTIFIER, action{actionType::SHIFT, 6});
    _actionTable.add(2, SyntaxKind::FLOAT_LITERAL, action{actionType::SHIFT, 7});
    _gotoTable.add(2, NonTerminal::PRIMARY_EXPRESSION, 5);

    // state 3
    _actionTable.add(3, SyntaxKind::IDENTIFIER, action{actionType::SHIFT, 3});
    _actionTable.add(3, SyntaxKind::FLOAT_LITERAL, action{actionType::SHIFT, 4});
    _gotoTable.add(3, NonTerminal::PRIMARY_EXPRESSION, 8);

    // state 4
    _actionTable.add(4, SyntaxKind::IDENTIFIER, action{actionType::REDUCE, 3});
    _actionTable.add(4, SyntaxKind::FLOAT_LITERAL, action{actionType::REDUCE, 3});

    // state 5
    _actionTable.add(5, SyntaxKind::END_OF_FILE, action{actionType::REDUCE, 1});

    // state 6
    _actionTable.add(6, SyntaxKind::IDENTIFIER, action{actionType::SHIFT, 6});
    _actionTable.add(6, SyntaxKind::FLOAT_LITERAL, action{actionType::SHIFT, 7});
    _gotoTable.add(6, NonTerminal::PRIMARY_EXPRESSION, 9);

    // state 7
    _actionTable.add(7, SyntaxKind::END_OF_FILE, action{actionType::REDUCE, 3});

    // state 8
    _actionTable.add(8, SyntaxKind::IDENTIFIER, action{actionType::REDUCE, 2});
    _actionTable.add(8, SyntaxKind::FLOAT_LITERAL, action{actionType::REDUCE, 2});

    // state 9
    _actionTable.add(9, SyntaxKind::END_OF_FILE, action{actionType::REDUCE, 2});

    _stack.push(StackItem{0, new NonTerminalNode(NonTerminal::PROGRAM)});

    computeFirstSets();
    computeFollowSets();
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

action Parser::getCurrAction()
{
    return _actionTable.get(_stack.top().state, peek(0)->kind);
}

void Parser::shift(action currAction)
{
    int state = currAction.num;
    SyntaxToken *token = getNextToken();

    cout << "Shifting to state " << currAction.num << " with token " << syntaxTokenToString(*token) << endl;
    // Create a new terminalNode
    ASTNode *node = new TerminalNode(token);

    // Push to stack
    _stack.push(StackItem{state, node});

    // Update current state
    _currState = state;
}

void Parser::reduce(action currAction)
{
    int productionRuleNum = currAction.num;
    cout << "Reducing with rule " << productionRuleNum << endl;
    productionRule rule = _rules[productionRuleNum];

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
    int currentState = _stack.top().state;
    _stack.push(StackItem{_gotoTable.get(currentState, rule.getLeft()), node});

    // Update current state
    _currState = currentState;
}

ASTNode *Parser::parse()
{
    action currAction;

    do
    {
        cout << endl;
        printStack();
        cout << endl;
        int state = _stack.top().state;

        currAction = getCurrAction();
        cout << "state:" << state << " token:" << syntaxTokenToString(*peek(0)) << " Action: " << actionTypeToString(currAction) << endl;

        if (currAction.type == actionType::REDUCE)
        {
            reduce(currAction);
        }
        else
        {
            if (currAction.type == actionType::SHIFT)
            {
                shift(currAction);
            }

            else if (currAction.type == actionType::ERROR)
            {
                // cout << "Error" << endl;
                // _errorHandler->addError(new SyntacticError(token));
            }
        }

    } while (currAction.type != actionType::ACCEPT);

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
        cout << "\e[0;31mRule " << i << "\e[0;37m : " << _rules[i].toString() << endl;
    }
}

void Parser::printFirstSet()
{
    for (int i = 0; i < _rules.size(); i++)
    {
        NonTerminal nt = _rules[i].getLeft();
        cout << "first(" << nonTerminalToString(nt) << ") = {";

        int j = _firstSets[_rules[i].getLeft()].size(); // size of follow set
        for (const SyntaxKind &terminal : _firstSets[nt])
        {
            cout << syntaxKindToString(terminal);
            if (j != 1)
                cout << ", ";

            j--;
        }

        cout << "}" << endl;
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
}

void Parser::computeFirstSets()
{
    for (int i = 0; i < _rules.size(); i++)
    {
        _firstSets[_rules[i].getLeft()] = unordered_set<SyntaxKind>();
    }

    for (int i = 0; i < _rules.size(); i++)
    {
        computeFirst(_rules[i].getLeft());
    }
}

unordered_set<SyntaxKind> &Parser::computeFirst(NonTerminal nt)
{
    if (_firstSets[nt].size() > 0)
    {
        return _firstSets[nt];
    }

    unordered_set<SyntaxKind> &firstSet = _firstSets[nt];
    for (int i = 0; i < _rules.size(); i++)
    {
        if (_rules[i].getLeft() == nt)
        {
            GrammarSymbolType type = _rules[i].getType(0);
            if (type == GrammarSymbolType::TERMINAL)
            {
                firstSet.insert(_rules[i].getTerminal(0));
            }
            else if (type == GrammarSymbolType::NON_TERMINAL)
            {
                // Recursively compute FIRST set for non-terminal
                unordered_set<SyntaxKind> &subFirstSet = computeFirst(_rules[i].getNonTerminal(0));
                firstSet.insert(subFirstSet.begin(), subFirstSet.end());
            }
        }
    }

    return firstSet;
}

void Parser::computeFollowSets()
{
    // Initialize follow sets for all non-terminals
    for (int i = 0; i < _rules.size(); i++)
    {
        _followSets[_rules[i].getLeft()] = unordered_set<SyntaxKind>();
    }

    // Add EOF marker to the follow set of the start symbol
    _followSets[NonTerminal::STATEMENT].insert(SyntaxKind::END_OF_FILE);

    bool changed;
    do
    {
        changed = false;
        // iterate over every rule
        for (int i = 0; i < _rules.size(); i++)
        {
            productionRule &rule = _rules[i];

            // iterate over every right hand side symbol
            for (int j = 0; j < rule.getNumOfRightSideSymbols(); j++)
            {
                // if you found in the form of αBβ follow(B) = first(β)
                if (rule.getType(j) == GrammarSymbolType::NON_TERMINAL)
                {
                    NonTerminal B = rule.getNonTerminal(j);
                    unordered_set<SyntaxKind> followB = _followSets[B];

                    if (j == rule.getNumOfRightSideSymbols() - 1)
                    {
                        // if is last symbol and nonterminal follow(A) = follow(B)
                        unordered_set<SyntaxKind> followA = _followSets[rule.getLeft()];
                        followB.insert(followA.begin(), followA.end());
                    }
                    else
                    {
                        if (rule.getType(j) == GrammarSymbolType::TERMINAL)
                        {
                            followB.insert(rule.getTerminal(j));
                        }
                        else
                        {
                            unordered_set<SyntaxKind> firstNext = _firstSets[rule.getNonTerminal(j + 1)];
                            followB.insert(firstNext.begin(), firstNext.end());
                        }
                    }

                    if (_followSets[B].size() != followB.size())
                    {
                        _followSets[B] = followB;
                        changed = true;
                    }
                }
            }
        }
    } while (changed);
}
