#ifndef __NODES
#define __NODES

#include "../token/token.hpp"
#include "../parser/grammerSymbol/grammerSymbol.hpp"
#include "../symbolTable/tableEntry/tableEntry.hpp"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class ASTNode
{
protected:
    GrammarSymbolType _type;
    valType _valType; //be used for semantic analysis
    int _register; //be used for code gen phase 

public:
    const GrammarSymbolType GetType() const
    {
        return _type;
    }

    const valType GetValType() const
    {
        return _valType;
    }
    
    void SetValType(valType valType)
    {
        _valType = valType;
    }

    int GetRegister() const
    {
        return _register;
    }

    void SetRegister(int regIndex)
    {
        _register = regIndex;
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
void PrintParseTree(ASTNode *parent);
void PrintParseTreeHelper(ASTNode *parent, const std::string &prefix, bool isLast);
#endif
