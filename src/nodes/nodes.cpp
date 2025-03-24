#include "Nodes.hpp"
#include "../token/token.hpp"
#include "../parser/grammerSymbol/grammerSymbol.hpp"
#include <vector>
#include <string>

using namespace std;

TerminalNode::TerminalNode(SyntaxToken *token) : _token(token)
{
    _syntaxKind = token->kind;
    _type = GrammarSymbolType::TERMINAL;
}

SyntaxKind TerminalNode::getTerminalKind() const
{
    return _syntaxKind;
}

SyntaxToken *TerminalNode::getToken() const
{
    return _token;
}

const vector<ASTNode *> &TerminalNode::GetChildren() const
{
    static const vector<ASTNode *> empty;
    return empty;
}

//--------------------------------non terminal node--------------------------------

NonTerminalNode::NonTerminalNode(NonTerminal nonTerminalKind)
    : _nonTerminalKind(nonTerminalKind), _children()
{
    _type = GrammarSymbolType::NON_TERMINAL;
}

void NonTerminalNode::AddChildToEnd(ASTNode *child)
{
    _children.push_back(child);
}

void NonTerminalNode::AddChildToFront(ASTNode *child)
{
    _children.insert(_children.begin(), child);
}

NonTerminal NonTerminalNode::getNonTerminalKind() const
{
    return _nonTerminalKind;
}

const std::vector<ASTNode *> &NonTerminalNode::GetChildren() const
{
    return _children;
}

//--------------------------------debugging--------------------------------

string AstNodeToString(ASTNode *node)
{
    if (node->GetType() == GrammarSymbolType::TERMINAL)
    {
        return syntaxTokenToString(*((TerminalNode *)node)->getToken());
    }
    else
    {
        return nonTerminalToString(((NonTerminalNode *)node)->getNonTerminalKind());
    }
}

void printAstNode(ASTNode *node)
{
    cout << AstNodeToString(node) << endl;
}

void PrintParseTree(ASTNode *node)
{
    PrintParseTreeHelper(node,"",true);
}

void PrintParseTreeHelper(ASTNode *parent, const string &prefix, bool isLast)
{
    if (parent == nullptr)
    {
        return;
    }

    cout << prefix;

    cout << (isLast ? "|__ " : "|-- ") << AstNodeToString(parent) << endl;

    vector<ASTNode *> children = parent->GetChildren();

    int childernCount = children.size();

    for (int i = 0; i < childernCount; i++)
    {
        string newPrefix = prefix + (isLast ? "    " : "|   ");
        PrintParseTreeHelper(children.at(i), newPrefix, i == childernCount - 1);
    }
}

