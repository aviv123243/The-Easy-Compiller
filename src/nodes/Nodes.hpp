#ifndef __NODES
#define __NODES

#include "../token/token.hpp"
#include "../parser/grammerSymbol/grammerSymbol.hpp"
#include <vector>


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

        TerminalNode(SyntaxKind syntaxKind, SyntaxToken *token);

        SyntaxKind getTerminalKind() const;
        SyntaxToken *getToken() const;
        const vector<ASTNode *> &GetChildren() const override;
};

class NonTerminalNode : public ASTNode
{
    private:
        NonTerminalKind _nonTerminalKind;
        vector<ASTNode *> _children;

    public:
    NonTerminalNode(NonTerminalKind nonTerminalKind);

    void AddChildToFront(ASTNode *child);
    void AddChildToEnd(ASTNode *child);
    
    NonTerminalKind getNonTerminalKind() const;
    const std::vector<ASTNode *> &GetChildren() const override;
};

#endif
