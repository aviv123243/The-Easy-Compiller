#ifndef __NODES
#define __NODES

#include "../token/token.hpp"
#include "../parser/grammerSymbol/grammerSymbol.hpp"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class ASTNode
{
protected:
    GrammarSymbolType _type;

public:
    const GrammarSymbolType GetType() const
    {
        return _type;
    }

    const virtual vector<ASTNode *> &GetChildren() const = 0;
};

class TerminalNode : public ASTNode
{
private:
    SyntaxKind _syntaxKind;
    SyntaxToken *_token;

public:
    TerminalNode(SyntaxToken *token);

    SyntaxKind getTerminalKind() const;
    SyntaxToken *getToken() const;
    const vector<ASTNode *> &GetChildren() const override;
};

class NonTerminalNode : public ASTNode
{
private:
    NonTerminal _nonTerminalKind;
    vector<ASTNode *> _children;

public:
    NonTerminalNode(NonTerminal nonTerminalKind);

    void AddChildToFront(ASTNode *child);
    void AddChildToEnd(ASTNode *child);

    NonTerminal getNonTerminalKind() const;
    const std::vector<ASTNode *> &GetChildren() const override;
};

string AstNodeToString(ASTNode *node);
void printAstNode(ASTNode *node);
void PrintParseTree(ASTNode *parent, const std::string &prefix, bool isLast);
#endif
