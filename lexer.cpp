#include "headers/lexer.hpp"
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iostream>

using namespace std;

char Lexer :: peek(int offset)
{   
    int tempPlace = _cursor + offset;
    
    if (tempPlace >= 0 && tempPlace < _codeLen)
    {
        return _sorceCode.at(_cursor + offset);
    }

    return '\0';
}

SyntaxToken * Lexer :: nextToken()
{
    SyntaxToken * tokenP = new SyntaxToken;

    //tokenizing white space
    if(_current == ' ' || _current == '\n' || _current == '\r')
    {
        while (_current == ' ' || _current == '\n' || _current == '\r')
        {
            next();
        }
        tokenP -> kind = syntaxKind::WHITESPACE;
        return tokenP;
    }

    //tokenizing kew words and id's
    if(isalpha(_current) || _current == '_')
    {
        stringstream tokenVal;

        while (isalnum(_current) || _current == '_')
        {
            tokenVal << _current;
            next();
        }

        string tokenValStr = tokenVal.str();

        if(find(kewWords.begin(), kewWords.end(), tokenValStr) != kewWords.end())
        {
            if(tokenValStr == "if") tokenP -> kind = syntaxKind::KEYWORD_IF;
            if(tokenValStr == "for") tokenP -> kind = syntaxKind::KEYWORD_FOR;
            if(tokenValStr == "while") tokenP -> kind = syntaxKind::KEYWORD_WHILE;
            if(tokenValStr == "fn") tokenP -> kind = syntaxKind::KEYWORD_FN;
            if(tokenValStr == "int") tokenP -> kind = syntaxKind::INT;
            if(tokenValStr == "return") tokenP -> kind = syntaxKind::KEYWORD_RETURN;
        }
        else
        {
            tokenP -> kind = syntaxKind::IDENTIFIER;
            tokenP -> val = tokenVal.str();
        }
        
        
        return tokenP;
    }

    //tokenizing integer literals
    if(isdigit(_current))
    {
        stringstream tokenVal;

        while (isdigit(_current))
        {
            tokenVal << _current;
            next();
        }

        tokenP -> kind = syntaxKind::INTEGER_LITERAL;
        tokenP -> val = tokenVal.str();
        return tokenP;
    }

    //tokenizing other symbols
    if (_current == '+')
    {
        tokenP -> kind = syntaxKind::PLUS;
        tokenP -> val = '+';
        next();
        return tokenP;
    }

    if (_current == '-')
    {
        tokenP -> kind = syntaxKind::MINUS;
        tokenP -> val = '-';
        next();
        return tokenP;
        
    }

    if (_current == '*')
    {
        tokenP -> kind = syntaxKind::STAR;
        tokenP -> val = '*';
        next();
        return tokenP;
        
    }

    if (_current == '/')
    {
        tokenP -> kind = syntaxKind::SLASH;
        tokenP -> val = '/';
        next();
        return tokenP;
    }

    if (_current == '(')
    {
        tokenP -> kind = syntaxKind::OPEN_PAREN;
        next();
        return tokenP;
        
    }

    if (_current == ')')
    {
        tokenP -> kind = syntaxKind::CLOSED_PAREN;
        next();
        return tokenP;
        
    }

    if (_current == '{')
    {
        tokenP -> kind = syntaxKind::OPEN_CURLY;
        next();
        return tokenP;
        
    }

    if (_current == '}')
    {
        tokenP -> kind = syntaxKind::CLOSED_CURLY;
        next();
        return tokenP;
        
    }

    if (_current == '[')
    {
        tokenP -> kind = syntaxKind::OPEN_BRACKET;
        next();
        return tokenP;
        
    }

    if (_current == ']')
    {
        tokenP -> kind = syntaxKind::CLOSED_BRACKET;
        next();
        return tokenP;
        
    }

    if (_current == ';')
    {
        tokenP -> kind = syntaxKind::SEMICOLON;
        next();
        return tokenP;
        
    }

    if (_current == ',')
    {
        tokenP -> kind = syntaxKind::COMMA;
        next();
        return tokenP;
        
    }

    if (_current == '=')
    {
        if(peek(1) == '=')
        {
            tokenP -> kind = syntaxKind::EQUALS_EQUALS;
            next();
        }
        else if (peek(1) == '>')
        {
            tokenP -> kind = syntaxKind::RIGHT_ARROW;
            next();
        }
        else
        {
            tokenP -> kind = syntaxKind::ASSIGN;    
        }

        next();
        return tokenP;
    }

    if (_current == '<')
    {
        if(peek(1) == '=')
        {
            tokenP -> kind = syntaxKind::LESS_THAN_EQUALS;
            next();
        }
        else
        {
            tokenP -> kind = syntaxKind::LESS_THAN;
        }

        next();
        return tokenP;
    }

    if (_current == '>')
    {
        if(peek(1) == '=')
        {
            tokenP -> kind = syntaxKind::GREATER_THAN;
            next();
        }
        else
        {
            tokenP -> kind = syntaxKind::GREATER_THAN;
        }

        next();
        return tokenP;
    }

    if (_current == '&')
    {
        if(peek(1) == '&')
        {
            tokenP -> kind = syntaxKind::AMPERSAND_AMPERSAND;
            next();
        }
        else
        {
            tokenP -> kind = syntaxKind::AMPERSAND;
        }

        next();
        return tokenP;
    }

    if (_current == '|')
    {
        if(peek(1) == '|')
        {
            tokenP -> kind = syntaxKind::PIPE_PIPE;
            next();
        }
        else
        {
            tokenP -> kind = syntaxKind::PIPE;
        }

        next();
        return tokenP;
    }

    if (_current == '!')
    {
        if(peek(1) == '=')
        {
            tokenP -> kind = syntaxKind::BANG_EQUALS;
            next();
        }
        else
        {
            tokenP -> kind = syntaxKind::BANG;
        }

        next();
        return tokenP;
    }

    tokenP -> kind = syntaxKind::UNEXPECTED_TOKEN;
    next();
    return tokenP;
}

vector<SyntaxToken *> Lexer :: GenerateTokes()
{
    vector<SyntaxToken *> tokens;
    while (_cursor < _codeLen)
    {   
        SyntaxToken *token = nextToken();
        if (token -> kind != syntaxKind::WHITESPACE)
        {
            tokens.push_back(token);
        } 
    }

    SyntaxToken * EOFTokenP = new SyntaxToken;
    EOFTokenP -> kind = syntaxKind::END_OF_FILE;
    tokens.push_back(EOFTokenP);

    return tokens;
}

//print & print helper funcs:

string SyntaxKindToString(syntaxKind kind)
{
    switch (kind) {
        case INTEGER_LITERAL: return "INTEGER_LITERAL";
        case IDENTIFIER: return "IDENTIFIER";
        case KEYWORD_IF: return "KEYWORD_IF";
        case KEYWORD_WHILE: return "KEYWORD_WHILE";
        case KEYWORD_FOR: return "KEYWORD_FOR";
        case KEYWORD_FN: return "KEYWORD_FN";
        case KEYWORD_RETURN: return "KEYWORD_RETURN";
        case RIGHT_ARROW: return "RIGHT_ARROW";
        case ASSIGN: return "ASSIGN";
        case INT: return "INT";
        case COMMA: return "COMMA";

        case PLUS: return "PLUS";
        case MINUS: return "MINUS";
        case SLASH: return "SLASH";
        case STAR: return "STAR";
        case AMPERSAND: return "AMPERSAND";
        case PIPE: return "PIPE";

        case PLUS_EQUALS: return "PLUS_EQUALS";
        case DASH_EQUALS: return "DASH_EQUALS";
        case SLASH_EQUALS: return "SLASH_EQUALS";
        case STAR_EQUALS: return "STAR_EQUALS";

        case OPEN_PAREN: return "OPEN_PAREN";
        case CLOSED_PAREN: return "CLOSED_PAREN";
        case OPEN_CURLY: return "OPEN_CURLY";
        case CLOSED_CURLY: return "CLOSED_CURLY";
        case OPEN_BRACKET: return "OPEN_BRACKET";
        case CLOSED_BRACKET: return "CLOSED_BRACKET";
        case SEMICOLON: return "SEMICOLON";
        case LESS_THAN: return "LESS_THAN";
        case GREATER_THAN: return "GREATER_THAN";

        case BANG: return "BANG";
        case EQUALS_EQUALS: return "EQUALS_EQUALS";
        case LESS_THAN_EQUALS: return "LESS_THAN_EQUALS";
        case GREATER_THAN_EQUALS: return "GREATER_THAN_EQUALS";
        case AMPERSAND_AMPERSAND: return "AMPERSAND_AMPERSAND";
        case PIPE_PIPE: return "PIPE_PIPE";
        case BANG_EQUALS: return "BANG_EQUALS";
        case END_OF_FILE: return "END_OF_FILE";
        case WHITESPACE: return "WHITESPACE";
        case UNEXPECTED_TOKEN: return "UNEXPECTED_TOKEN";

        default: return "UNKNOWN";
    }
}

string SyntaxTokenToString(SyntaxToken * token)
{
    stringstream res;
    string tokenValue = token -> val;
    res << SyntaxKindToString(token -> kind)
        << " ";

    if(!tokenValue.empty())
    {
        res << "| "<< tokenValue;
    }
    
        

    return res.str();
}

void PrintTokens(vector<SyntaxToken *> * tokens)
{
    for(SyntaxToken * token : *tokens)
    {
        cout << SyntaxTokenToString(token) << endl;
    }
}

void PrintTokensNoWhiteSpace(vector<SyntaxToken *> * tokens)
{
    for(SyntaxToken * token : *tokens)
    {
        if (token -> kind != syntaxKind :: WHITESPACE)
        {
            cout << SyntaxTokenToString(token) << endl;
        }
    }
}