#include "../lexer/lexer.hpp"
#include "../DFA/DFA.hpp"
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <fstream>

using namespace std;

string syntaxkindToString[] = {"INTEGER_LITERAL", "FLOAT_LITERAL", "STRING_LITERAL", "IDENTIFIER", "KEYWORD_IF", "KEYWORD_WHILE", "KEYWORD_FOR",
                               "KEYWORD_FN", "KEYWORD_RET", "KEYWORD_INT", "KEYWORD_FLOAT", "EQUALS", "COMMA", "PLUS", "MINUS", "SLASH", "STAR", "AMPERSAND",
                               "PIPE", "BANG", "SEMICOLON", "LESS_THAN", "GREATER_THAN", "OPEN_PAREN", "CLOSED_PAREN", "OPEN_CURLY", "CLOSED_CURLY", "OPEN_BRACKET",
                               "CLOSED_BRACKET", "RIGHT_ARROW","PLUS_PLUS","DASH_DASH", "PLUS_EQUALS", "DASH_EQUALS", "SLASH_EQUALS", "STAR_EQUALS", "EQUALS_EQUALS", "LESS_THAN_EQUALS",
                               "GREATER_THAN_EQUALS", "AMPERSAND_AMPERSAND", "PIPE_PIPE", "BANG_EQUALS", "END_OF_FILE", "UNEXPECTED_TOKEN"};

syntaxKind endStateToSyntaxKind[] = {
    syntaxKind::UNEXPECTED_TOKEN,
    syntaxKind::INTEGER_LITERAL,
    syntaxKind::FLOAT_LITERAL,
    syntaxKind::STRING_LITERAL,
    syntaxKind::IDENTIFIER,
    syntaxKind::KEYWORD_IF,
    syntaxKind::KEYWORD_WHILE,
    syntaxKind::KEYWORD_FOR,
    syntaxKind::KEYWORD_FN,
    syntaxKind::KEYWORD_RET,
    syntaxKind::KEYWORD_INT,
    syntaxKind::KEYWORD_FLOAT,
    syntaxKind::EQUALS,
    syntaxKind::COMMA,
    syntaxKind::PLUS,
    syntaxKind::MINUS,
    syntaxKind::SLASH,
    syntaxKind::STAR,
    syntaxKind::AMPERSAND,
    syntaxKind::PIPE,
    syntaxKind::BANG,
    syntaxKind::SEMICOLON,
    syntaxKind::LESS_THAN,
    syntaxKind::GREATER_THAN,
    syntaxKind::OPEN_PAREN,
    syntaxKind::CLOSED_PAREN,
    syntaxKind::OPEN_CURLY,
    syntaxKind::CLOSED_CURLY,
    syntaxKind::OPEN_BRACKET,
    syntaxKind::CLOSED_BRACKET,
    syntaxKind::RIGHT_ARROW,
    syntaxKind::PLUS_PLUS,
    syntaxKind::DASH_DASH,
    syntaxKind::PLUS_EQUALS,
    syntaxKind::DASH_EQUALS,
    syntaxKind::SLASH_EQUALS,
    syntaxKind::STAR_EQUALS,
    syntaxKind::EQUALS_EQUALS,
    syntaxKind::LESS_THAN_EQUALS,
    syntaxKind::GREATER_THAN_EQUALS,
    syntaxKind::AMPERSAND_AMPERSAND,
    syntaxKind::PIPE_PIPE,
    syntaxKind::BANG_EQUALS,
    syntaxKind::END_OF_FILE,
    syntaxKind::UNEXPECTED_TOKEN,
};

Lexer::Lexer(string DFAConfigFile, string srcFile) : _dfa(DFAConfigFile), _cursor(0), _srcFile(srcFile)
{
    ifstream src(_srcFile);

    src.seekg(0, ios::end);
    _fileSize = src.tellg();
    src.close();
}

SyntaxToken Lexer::getNextToken()
{
    char currentChar;
    stringstream val;
    bool autoTerminated = true;
    int currentState = _dfa.getStartState();
    SyntaxToken resToken;
    ifstream src(_srcFile);
    src.seekg(_cursor, ios::beg);

    // cout << "cursor at " << this->_cursor << endl;

    if (_cursor >= _fileSize)
    {
        resToken.kind = syntaxKind::END_OF_FILE;
        return resToken;
    }

    if (!src.is_open())
    {
        runtime_error("Error: Unable to open sorce file");
        return resToken;
    }

    src.get(currentChar);
    _cursor++;
    // cout << "transition from state " << currentState << " with char " << currentChar
    //      << " gone to: " << _dfa.getState(currentState, currentChar) << endl;

    while (_dfa.getState(currentState, currentChar) != -1 && _cursor <= _fileSize)
    {
        // cout << "transition from state " << currentState << " with char " << currentChar
        //      << " gone to: " << _dfa.getState(currentState, currentChar) << endl;
        autoTerminated = false;
        val << currentChar;
        currentState = _dfa.getState(currentState, currentChar);
        src.get(currentChar);
        _cursor++;
    }
    _cursor--;

    src.close();

    // if the state is a skip state, take the token after it
    if (isSkipState(currentState))
    {
        if (autoTerminated) 
            _cursor--;
        resToken = getNextToken();
    }
    else
    {
        // else if the state is an end state, return the token
        vector<int> endStates = _dfa.getEndStates();
        if (find(endStates.begin(), endStates.end(), currentState) != endStates.end())
        {
            resToken.kind = getSyntaxKind(currentState);
            resToken.val = val.str();
        }

        // else the token is invalid so return an unexpected token
        else
        {
            cout << "syntaxKind::UNEXPECTED_TOKEN at state " << currentState << endl;
            resToken.kind = syntaxKind::UNEXPECTED_TOKEN;
            if (autoTerminated)
                _cursor++;
        }
    }

    return resToken;
}

syntaxKind getSyntaxKind(int state)
{
    if (state < syntaxKind::UNEXPECTED_TOKEN)
        return endStateToSyntaxKind[state];

    return syntaxKind::IDENTIFIER;
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

bool isSkipState(int state)
{
    return state == 105 || state == 106;
}

bool isWhitespace(char ch)
{
    return ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r';
}