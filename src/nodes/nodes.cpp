#include "Nodes.hpp"
#include "../token/token.hpp"
#include "../parser/grammerSymbol/grammerSymbol.hpp"
#include <vector>
#include <string>

using namespace std;

TerminalNode::TerminalNode(SyntaxKind syntaxKind, SyntaxToken *token) : _syntaxKind(syntaxKind), _token(token)
{
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

NonTerminalNode::NonTerminalNode(NonTerminalKind nonTerminalKind)
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

NonTerminalKind NonTerminalNode::getNonTerminalKind() const
{
    return _nonTerminalKind;
}

const std::vector<ASTNode *> &NonTerminalNode::GetChildren() const
{
    return _children;
}
