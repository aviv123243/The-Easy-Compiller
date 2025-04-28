#include "../lexer/lexer.hpp"
#include "../DFA/DFA.hpp"
#include "../errors/errors.hpp"
#include "../token/token.hpp"
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <fstream>

// #define LEXER_DEBUG

using namespace std;

SyntaxKind endStateToSyntaxKind[] = {
    SyntaxKind::UNEXPECTED_TOKEN, SyntaxKind::INTEGER_LITERAL, SyntaxKind::FLOAT_LITERAL, SyntaxKind::CHAR_LITERAL,
    SyntaxKind::STRING_LITERAL, SyntaxKind::IDENTIFIER, SyntaxKind::KEYWORD_IF,SyntaxKind::KEYWORD_ELSE,
    SyntaxKind::KEYWORD_WHILE, SyntaxKind::KEYWORD_FOR, SyntaxKind::KEYWORD_FN,
    SyntaxKind::KEYWORD_RET, SyntaxKind::KEYWORD_INT, SyntaxKind::KEYWORD_FLOAT, SyntaxKind::KEYWORD_CHAR,
    SyntaxKind::EQUALS, SyntaxKind::COMMA, SyntaxKind::PLUS, SyntaxKind::MINUS,
    SyntaxKind::SLASH, SyntaxKind::STAR, SyntaxKind::AMPERSAND, SyntaxKind::PIPE,
    SyntaxKind::CARET, SyntaxKind::TILDE,SyntaxKind::BANG, SyntaxKind::SEMICOLON, SyntaxKind::LESS_THAN,
    SyntaxKind::GREATER_THAN, SyntaxKind::OPEN_PAREN, SyntaxKind::CLOSED_PAREN, SyntaxKind::OPEN_CURLY,
    SyntaxKind::CLOSED_CURLY, SyntaxKind::OPEN_BRACKET, SyntaxKind::CLOSED_BRACKET,
    SyntaxKind::RIGHT_ARROW, SyntaxKind::PLUS_PLUS, SyntaxKind::MINUS_MINUS,
    SyntaxKind::PLUS_EQUALS, SyntaxKind::MINUS_EQUALS, SyntaxKind::SLASH_EQUALS,
    SyntaxKind::STAR_EQUALS, SyntaxKind::AMPERSAND_EQUALS,SyntaxKind::PIPE_EQUALS, SyntaxKind::CARET_EQUALS,
    SyntaxKind::TILDE_EQUALS, SyntaxKind::EQUALS_EQUALS, SyntaxKind::LESS_THAN_EQUALS,
    SyntaxKind::GREATER_THAN_EQUALS, SyntaxKind::AMPERSAND_AMPERSAND, SyntaxKind::PIPE_PIPE,
    SyntaxKind::BANG_EQUALS, SyntaxKind::END_OF_FILE, SyntaxKind::UNEXPECTED_TOKEN
};

Lexer::Lexer(string srcFile, string DFAConfigFile, ErrorHandler *handler)
    : _srcFile(srcFile), _dfa(DFAConfigFile), _errorHandler(handler), _cursor(0), _currLine(1), _currColumn(1)
{
    ifstream src(_srcFile);

    src.seekg(0, ios::end);
    _fileSize = src.tellg();
    src.close();
}

vector<SyntaxToken *> Lexer::getTokens()
{
    vector<SyntaxToken *> tokens;
    SyntaxToken *currToken;

    while ((currToken = getNextToken())->kind != SyntaxKind::END_OF_FILE)
    {
        tokens.push_back(currToken);
    }

    tokens.push_back(currToken); // pushing the EOF token

    #ifdef LEXER_DEBUG
        for (int i = 0; i < tokens.size(); i++)
            {
                cout << syntaxTokenToString(*tokens[i]) << endl;
            }
    #endif 

    return tokens;
}

SyntaxToken *Lexer::getNextToken()
{
    char currentChar;
    stringstream val;
    int currentState = _dfa.getStartState();
    int prevState;
    SyntaxToken *resToken = new SyntaxToken();
    ifstream src(_srcFile);
    src.seekg(_cursor, ios::beg);

    if (_cursor >= _fileSize)
    {
        resToken->kind = SyntaxKind::END_OF_FILE;
        return resToken;
    }

    if (!src.is_open())
    {
        runtime_error("Error: Unable to open sorce file");
        return resToken;
    }

    do
    {
        // get the next character
        src.get(currentChar);
        _cursor++;

        // get the corresponding next state
        prevState = currentState;
        currentState = _dfa.getState(currentState, currentChar);

        // if we didnt finish lexing the token, recognize it.
        if (currentState != -1 && _cursor <= _fileSize)
        {
            val << currentChar;
        }

        // if we dident pocess the token, update the position
        if (currentState != -1 || prevState == _dfa.getStartState())
        {
            updatePosition(currentChar);
        }

    } while (currentState != -1 && _cursor <= _fileSize);

    _cursor--;
    currentState = prevState;
    src.close();

    // if the state is a skip state, take the token after it
    if (isSkipState(currentState))
    {
        delete resToken;
        resToken = getNextToken();
    }
    else
    {
        // else if the state is an end state, return the token
        resToken->line = _currLine;
        resToken->column = _currColumn;

        vector<int> endStates = _dfa.getEndStates();
        if (find(endStates.begin(), endStates.end(), currentState) != endStates.end())
        {
            resToken->kind = getSyntaxKind(currentState);
            resToken->val = val.str();
        }

        // else the token is invalid so return an unexpected token
        else
        {
            // if the token is invalid, add an error to the handler and skip it
            _cursor++;
            resToken->kind = SyntaxKind::UNEXPECTED_TOKEN;
            _errorHandler->addError(new SyntaxError("Unexpected token error", resToken));
        }
    }


    return resToken;
}

void Lexer::updatePosition(char ch)
{
    if (ch == '\t')
    {
        _currColumn += 4; // (tab is 4 spaces)
    }
    else if (ch == 0x0A)
    {
        _currColumn = 0;
        _currLine++;

        _cursor++; // skip the carriage return in the src code
    }
    else if (ch != 0x0D) // Skip carriage return characters
    {
        _currColumn++;
    }
}

// print & print helper funcs:
SyntaxKind getSyntaxKind(int state)
{
    if (state < SyntaxKind::UNEXPECTED_TOKEN)
        return endStateToSyntaxKind[state];

    return SyntaxKind::IDENTIFIER;
}

void Lexer::printTransitionMatrix() const
{
    _dfa.printMatrix();
}

bool isSkipState(int state)
{
    return state == NUM_OF_STATES - 1 || state == NUM_OF_STATES - 2;
}

bool isWhitespace(char ch)
{
    return ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r';
}