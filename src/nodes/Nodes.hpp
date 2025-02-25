#ifndef __NODES
#define __NODES

#include "../lexer/lexer.hpp"
#include <sstream>

class ASTNode
{
protected:
    SyntaxKind _syntaxKind;

public:
    virtual vector<ASTNode *> GetChildren() const = 0;

    virtual string ToString() const
    {
        return SyntaxKindToString(_syntaxKind);
    }
};

class ExpressionNode : public ASTNode
{

public:
    // virtual int Eval();
};

class BinaryExpressionNode : public ExpressionNode
{
private:
    ExpressionNode *_left;
    ExpressionNode *_right;

public:
    BinaryExpressionNode(ExpressionNode *left, SyntaxKind binOperator, ExpressionNode *right) : _left(left), _right(right)
    {
        _syntaxKind = binOperator;
    }

    vector<ASTNode *> GetChildren() const override
    {
        vector<ASTNode *> children;
        children.push_back(_right);
        children.push_back(_left);
        return children;
    }
};

class UnaryExpressionNode : public ExpressionNode
{
private:
    ExpressionNode *_child;

public:
    UnaryExpressionNode(ExpressionNode *child, SyntaxKind unaryOparator)
    {
        _syntaxKind = unaryOparator;
        _child = child;
    }

    vector<ASTNode *> GetChildren() const override
    {
        vector<ASTNode *> children;
        children.push_back(_child);
        return children;
    }
};

class IdExpressionNode : public ExpressionNode
{
public:
    string _name;

    IdExpressionNode(string name)
    {
        _syntaxKind = SyntaxKind::IDENTIFIER;
        _name = name;
    }

    vector<ASTNode *> GetChildren() const override
    {
        return {};
    }

    string ToString() const override
    {
        std::stringstream res;
        res << SyntaxKindToString(_syntaxKind)
            << "(" << _name << ")";
        return res.str();
    }
};

class NumberExpressionNode : public ExpressionNode
{
protected:
    vector<ASTNode *> GetChildren() const override
    {
        return {};
    }
};

class IntNumberExpressionNode : public NumberExpressionNode
{
private:
    int _number;

public:
    IntNumberExpressionNode(int number) : _number(number)
    {
        _syntaxKind = SyntaxKind::INTEGER_LITERAL;
    }

    string ToString() const override
    {
        std::stringstream res;
        res << SyntaxKindToString(_syntaxKind)
            << "(" << _number << ")";
        return res.str();
    }
    // vector<SyntaxToken*> * GetChildren() override;
};

#endif
