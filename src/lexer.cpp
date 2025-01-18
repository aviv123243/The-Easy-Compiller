#include "headers/lexer.hpp"
#include "headers/DFA.hpp"
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <fstream>

using namespace std;

SyntaxToken Lexer::getNextToken()
{
    char currentChar;
    int currentState = dfa.getStartState();
    fstream src(_srcFile);
    stringstream currentToken;
    SyntaxToken resToken;
    src.seekg(_cursor, ios::beg);

    if (!src.is_open())
    {
        cerr << "Error: Unable to open file " << _srcFile << endl;
        return resToken; 
    }

    while (src.get(currentChar) && dfa.getState(currentState, currentChar) != -1)
    {
        //cout << "Reading: " << currentChar << " from state: " << currentState << endl;
        currentToken << currentChar;
        currentState = dfa.getState(currentState, currentChar);
        _cursor++;
    }

    _cursor++;

    vector<int> endStates = dfa.getEndStates();
    if (find(endStates.begin(), endStates.end(), currentState) != endStates.end())
    {
        resToken.kind = syntaxKind(currentState);
        resToken.val = currentToken.str();
    }
    else
    {
        resToken.kind = syntaxKind::UNEXPECTED_TOKEN;
    }

    return resToken;
}

// print & print helper funcs:

string SyntaxKindToString(syntaxKind kind)
{
    switch (kind)
    {
    case INTEGER_LITERAL:
        return "INTEGER_LITERAL";
    case IDENTIFIER:
        return "IDENTIFIER";
    case KEYWORD_IF:
        return "KEYWORD_IF";
    case KEYWORD_WHILE:
        return "KEYWORD_WHILE";
    case KEYWORD_FOR:
        return "KEYWORD_FOR";
    case KEYWORD_FN:
        return "KEYWORD_FN";
    case KEYWORD_RETURN:
        return "KEYWORD_RETURN";
    case RIGHT_ARROW:
        return "RIGHT_ARROW";
    case ASSIGN:
        return "ASSIGN";
    case INT:
        return "INT";
    case COMMA:
        return "COMMA";

    case PLUS:
        return "PLUS";
    case MINUS:
        return "MINUS";
    case SLASH:
        return "SLASH";
    case STAR:
        return "STAR";
    case AMPERSAND:
        return "AMPERSAND";
    case PIPE:
        return "PIPE";

    case PLUS_EQUALS:
        return "PLUS_EQUALS";
    case DASH_EQUALS:
        return "DASH_EQUALS";
    case SLASH_EQUALS:
        return "SLASH_EQUALS";
    case STAR_EQUALS:
        return "STAR_EQUALS";

    case OPEN_PAREN:
        return "OPEN_PAREN";
    case CLOSED_PAREN:
        return "CLOSED_PAREN";
    case OPEN_CURLY:
        return "OPEN_CURLY";
    case CLOSED_CURLY:
        return "CLOSED_CURLY";
    case OPEN_BRACKET:
        return "OPEN_BRACKET";
    case CLOSED_BRACKET:
        return "CLOSED_BRACKET";
    case SEMICOLON:
        return "SEMICOLON";
    case LESS_THAN:
        return "LESS_THAN";
    case GREATER_THAN:
        return "GREATER_THAN";

    case BANG:
        return "BANG";
    case EQUALS_EQUALS:
        return "EQUALS_EQUALS";
    case LESS_THAN_EQUALS:
        return "LESS_THAN_EQUALS";
    case GREATER_THAN_EQUALS:
        return "GREATER_THAN_EQUALS";
    case AMPERSAND_AMPERSAND:
        return "AMPERSAND_AMPERSAND";
    case PIPE_PIPE:
        return "PIPE_PIPE";
    case BANG_EQUALS:
        return "BANG_EQUALS";
    case END_OF_FILE:
        return "END_OF_FILE";
    case WHITESPACE:
        return "WHITESPACE";
    case UNEXPECTED_TOKEN:
        return "UNEXPECTED_TOKEN";

    default:
        return "UNKNOWN";
    }
}

string SyntaxTokenToString(SyntaxToken token)
{
    stringstream res;
    string tokenValue = token.val;
    res << SyntaxKindToString(token.kind)
        << " ";

    if (!tokenValue.empty())
    {
        res << "| " << tokenValue;
    }

    return res.str();
}