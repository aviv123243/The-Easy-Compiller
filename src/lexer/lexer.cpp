#include "../lexer/lexer.hpp"
#include "../DFA/DFA.hpp"
#include "../errors/errors.hpp"
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
                               "CLOSED_BRACKET", "RIGHT_ARROW", "PLUS_PLUS", "DASH_DASH", "PLUS_EQUALS", "DASH_EQUALS", "SLASH_EQUALS", "STAR_EQUALS", "EQUALS_EQUALS",
                               "LESS_THAN_EQUALS", "GREATER_THAN_EQUALS", "AMPERSAND_AMPERSAND", "PIPE_PIPE", "BANG_EQUALS", "END_OF_FILE", "UNEXPECTED_TOKEN"};

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

Lexer::Lexer(string srcFile, string DFAConfigFile, ErrorHandler *handler)
    : _srcFile(srcFile), _dfa(DFAConfigFile), _errorHandler(handler), _cursor(0), _currLine(1), _currColumn(0)
{
    ifstream src(_srcFile);

    src.seekg(0, ios::end);
    _fileSize = src.tellg();
    src.close();
}

vector<SyntaxToken> Lexer::getTokens()
{
    vector<SyntaxToken> tokens;
    SyntaxToken currToken;

    while ((currToken = getNextToken()).kind != syntaxKind::END_OF_FILE)
    {
        tokens.push_back(currToken);
    }

    tokens.push_back(currToken); // pushing the EOF token
    return tokens;
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

    cout << "cursor at " << this->_cursor << endl;

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
    cout << "read from beggining: " << currentChar << endl;

    // cout << "transition from state " << currentState << " with char " << currentChar
    //      << " gone to: " << _dfa.getState(currentState, currentChar) << endl;

    while (_dfa.getState(currentState, currentChar) != -1 && _cursor <= _fileSize)
    {
        // cout << "transition from state " << currentState << " with char " << currentChar
        //      << " gone to: " << _dfa.getState(currentState, currentChar) << endl;
        updatePosition(currentChar);

        if (autoTerminated)
            autoTerminated = false;

        val << currentChar;
        currentState = _dfa.getState(currentState, currentChar);
        src.get(currentChar);
        cout << "read from loop: " << currentChar << endl;
        _cursor++;
    }

    if (!autoTerminated)
    {
        _cursor--;
    }

    if (autoTerminated)
    {
        updatePosition(currentChar);
    }

    src.close();

    // if the state is a skip state, take the token after it
    if (isSkipState(currentState))
    {
        resToken = getNextToken();
        cout << "skipped token! " <<  endl;
    }
    else
    {
        // else if the state is an end state, return the token
        vector<int> endStates = _dfa.getEndStates();
        if (find(endStates.begin(), endStates.end(), currentState) != endStates.end())
        {
            resToken.kind = getSyntaxKind(currentState);
            resToken.val = val.str();
            cout << "GOOD token! " <<  endl;
        }

        // else the token is invalid so return an unexpected token
        else
        {
            // if the token is invalid, add an error to the handler
            resToken.kind = syntaxKind::UNEXPECTED_TOKEN;
            cout << "BAD token! " <<  endl;
            _errorHandler->addError(new SyntaxError("Unexpected token error", _currLine, _currColumn));
        }
    }

    return resToken;
}

void Lexer::updatePosition(char ch)
{
    cout << "char: " << ch;
    if (ch == '\t')
    {
        _currColumn += 4; // assuming a tab is 4 spaces
    }
    else if (ch == '\n')
    {
        _currColumn = 0;
        _currLine++;
    }
    else if (ch != '\r') // Skip carriage return characters
    {
        _currColumn++;
    }
    cout << " at: {" << _currLine << ":" << _currColumn << "}" << endl;
}
// print & print helper funcs:

syntaxKind getSyntaxKind(int state)
{
    if (state < syntaxKind::UNEXPECTED_TOKEN)
        return endStateToSyntaxKind[state];

    return syntaxKind::IDENTIFIER;
}

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
    return state == NUM_OF_STATES - 1 || state == NUM_OF_STATES - 2;
}

bool isWhitespace(char ch)
{
    return ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r';
}