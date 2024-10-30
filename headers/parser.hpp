#include "lexer.hpp"
#include "Nodes.hpp"
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iostream>

class Parser
{
private:
    vector<SyntaxToken*> _tokens;
    SyntaxToken *_current;
    int _currentTokenIndex;
    int _size;
    stringstream _diagnostics;
public:
    Parser(vector<SyntaxToken*> *tokens);
    SyntaxToken * Match(syntaxKind kind);
    SyntaxToken * Peek(int offset);
    SyntaxToken * NextToken();
    ExpressionNode * Parse();
    ExpressionNode * ParseExpression();
    ExpressionNode * ParseTermExpression();
    ExpressionNode * ParseFactorExpression();
    ExpressionNode * ParseUnaryExpression();
    ExpressionNode * ParsePrimaryExpression();

    string getDiagnostics()
    {
        return _diagnostics.str();
    }
};

void PrintParseTree(ASTNode * base);







