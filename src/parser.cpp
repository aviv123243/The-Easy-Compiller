#include "headers/lexer.hpp"
#include "headers/parser.hpp"
#include <vector>

bool tryParseInt(string num);

Parser::Parser(vector<SyntaxToken*> *tokens)
{
    _tokens = *tokens;
    _current = _tokens.at(0);
    _currentTokenIndex = 0;
    _size = _tokens.size();
}

SyntaxToken * Parser::Match(syntaxKind kind)
{
    if (_current -> kind != kind)
    {
        _diagnostics << "[!] Syntax error" << endl
        << "expected:"<<SyntaxKindToString(kind) << " but got: " <<SyntaxKindToString(_current -> kind)  << endl;
    }

    return NextToken();
}

SyntaxToken * Parser::Peek(int offset)
{
    int index = _currentTokenIndex + offset;

    if (index < _size)
    {
        return _tokens.at(index);
    }

    return _tokens.at(_size - 1);
}

SyntaxToken * Parser::NextToken()
{   
    SyntaxToken * current = _current;
    _currentTokenIndex++;
    _current = Peek(0);
    return current;
}

ExpressionNode * Parser::Parse()
{
    ExpressionNode * expression = ParseExpression();
    Match(syntaxKind::END_OF_FILE);
    return expression;
}

ExpressionNode * Parser::ParseExpression()
{
    return ParseTermExpression();
}

ExpressionNode * Parser::ParseTermExpression()
{
    ExpressionNode* left = ParseFactorExpression();

    syntaxKind kind = _current -> kind;

    
    while (kind == syntaxKind::PLUS || kind == syntaxKind::MINUS)
    {
        NextToken();

        ExpressionNode * right = ParseFactorExpression();
        left = new BinaryExpressionNode(left,kind,right); 

        kind = _current -> kind;
    }
    return left;
}

ExpressionNode * Parser::ParseUnaryExpression()
{   syntaxKind kind = _current -> kind;
    NextToken();
    return new UnaryExpressionNode(ParsePrimaryExpression(),kind);   
}

ExpressionNode * Parser::ParseFactorExpression()
{
    

    ExpressionNode* left = ParsePrimaryExpression();

    syntaxKind kind = _current -> kind;

    

    while (kind == syntaxKind::SLASH || kind == syntaxKind::STAR)
    {
        NextToken();
        
        ExpressionNode* right = ParsePrimaryExpression();
        left = new BinaryExpressionNode(left,kind,right);
    
        kind = _current -> kind;
        
    }


    return left;
}

ExpressionNode * Parser::ParsePrimaryExpression()
{
    if(_current -> kind == syntaxKind :: OPEN_PAREN)
    {
        NextToken();
        ExpressionNode * parenContent = ParseExpression();
        Match(syntaxKind :: CLOSED_PAREN);
        return parenContent;
    }

    if(_current -> kind == syntaxKind::PLUS || _current -> kind == syntaxKind::MINUS)
    {
        return ParseUnaryExpression();
    } 

    if(_current -> kind == syntaxKind::IDENTIFIER)
    {
        return new IdExpressionNode(NextToken() -> val);
    } 

    string numVal = Match(syntaxKind::INTEGER_LITERAL) -> val;
    
    if (tryParseInt(numVal))
    {
        return new IntNumberExpressionNode(stoi(numVal));
    }
    
    return new IntNumberExpressionNode(0);
}



void PrintParseTree(const ASTNode *parent,const string& prefix = "",bool isLast = true)
{
    if (parent == nullptr)
    {
        return;
    }
    
    cout << prefix;

    cout << (isLast ? "|__ " : "|-- ") << parent->ToString() << endl;
    
    vector<ASTNode*> children = parent -> GetChildren();
    int childernCount = children.size();
    for (int i = 0; i < childernCount; i++)
    {
        string newPrefix = prefix + (isLast ? "    " : "|   ");
        PrintParseTree(children.at(i),newPrefix,i == childernCount-1);
    }
    
}

void PrintParseTree(ASTNode * base)
{
    PrintParseTree(base,"",true);
}

bool tryParseInt(string num)
{
    try{
        stoi(num);

        return true;
    }catch(invalid_argument)
    {
        return false;
    }
    catch(out_of_range)
    {
        return false;
    }
}