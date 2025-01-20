#include "headers/lexer.hpp"
#include "headers/DFA.hpp"
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <fstream>

using namespace std;

string syntaxkindToString[] = {"", "INTEGER_LITERAL", "FLOAT_LITERAL", "STRING_LITERAL", "IDENTIFIER", "KEYWORD_IF", "KEYWORD_WHILE", "KEYWORD_FOR",
                               "KEYWORD_FN", "KEYWORD_RET", "KEYWORD_INT", "KEYWORD_FLOAT", "EQUALS", "COMMA", "PLUS", "MINUS", "SLASH", "STAR", "AMPERSAND",
                               "PIPE", "BANG", "SEMICOLON", "LESS_THAN", "GREATER_THAN", "OPEN_PAREN", "CLOSED_PAREN", "OPEN_CURLY", "CLOSED_CURLY", "OPEN_BRACKET",
                               "CLOSED_BRACKET", "RIGHT_ARROW", "PLUS_EQUALS", "DASH_EQUALS", "SLASH_EQUALS", "STAR_EQUALS", "EQUALS_EQUALS", "LESS_THAN_EQUALS",
                               "GREATER_THAN_EQUALS", "AMPERSAND_AMPERSAND", "PIPE_PIPE", "BANG_EQUALS", "END_OF_FILE", "UNEXPECTED_TOKEN"};

SyntaxToken Lexer::getNextToken()
{
    char currentChar;
    int currentState = _dfa.getStartState();
    fstream src(_srcFile);
    stringstream currentToken;
    SyntaxToken resToken;
    src.seekg(0, ios::end);
    int fileSize = src.tellg();
    src.seekg(_cursor, ios::beg);

    if (_cursor >= fileSize)
    {
        resToken.kind = syntaxKind::END_OF_FILE;
        return resToken;
    }

    if (!src.is_open())
    {
        cerr << "Error: Unable to open file " << _srcFile << endl;
        return resToken;
    }

    src.get(currentChar);

    src.seekg(-1, ios::cur);

    while (src.get(currentChar) && isWhitespace(currentChar))
    {
        _cursor++;
    }

    src.seekg(-1, ios::cur);
    _cursor--;

    while (src.get(currentChar) && _dfa.getState(currentState, currentChar) != -1)
    {
        cout << "Reading: " << currentChar << " from state: " << currentState << endl;

        currentToken << currentChar;
        currentState = _dfa.getState(currentState, currentChar);
        cout << "gone to: " << currentState << endl;
        _cursor++;
    }

    _cursor++;

    cout << " from state: " << currentState << endl;

    vector<int> endStates = _dfa.getEndStates();
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

void Lexer::printTransitionMatrix() const
{
    _dfa.printMatrix();
}

string syntaxTokenToString(SyntaxToken token)
{
    stringstream res;
    string tokenValue = token.val;
    res << syntaxkindToString[token.kind]
        << " ";

    if (!tokenValue.empty())
    {
        res << "| " << tokenValue;
    }

    return res.str();
}

bool isWhitespace(char ch)
{
    return ch == ' ' || ch == '\n' || ch == '\t';
}