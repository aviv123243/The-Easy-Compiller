#include "../../src/DFA/DFA.hpp"
#include "../../src/lexer/lexer.hpp"
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <map>
#include <vector>

// not updated
string syntaxKindEnumToString[] = {
    "INTEGER_LITERAL", "FLOAT_LITERAL", "CHAR_LITERAL", "STRING_LITERAL", "IDENTIFIER", "KEYWORD_IF", "KEYWORD_ELSE", "KEYWORD_WHILE", "KEYWORD_FOR",
    "KEYWORD_FN", "KEYWORD_RET", "KEYWORD_INT", "KEYWORD_FLOAT", "KEYWORD_CHAR", "EQUALS", "COMMA", "PLUS",
    "MINUS", "SLASH", "STAR", "AMPERSAND", "PIPE", "CARET", "TILDE",
    "BANG", "SEMICOLON", "LESS_THAN", "GREATER_THAN", "OPEN_PAREN", "CLOSED_PAREN", "OPEN_CURLY", "CLOSED_CURLY", "OPEN_BRACKET",
    "CLOSED_BRACKET", "RIGHT_ARROW", "PLUS_PLUS", "MINUS_MINUS", "PLUS_EQUALS", "MINUS_EQUALS", "SLASH_EQUALS", "STAR_EQUALS",
    "AMPERSAND_EQUALS", "PIPE_EQUALS", "CARET_EQUALS", "TILDE_EQUALS", "EQUALS_EQUALS",
    "LESS_THAN_EQUALS", "GREATER_THAN_EQUALS", "AMPERSAND_AMPERSAND", "PIPE_PIPE", "BANG_EQUALS", "END_OF_FILE", "UNEXPECTED_TOKEN"};

// garbege function that "seppose" to generate a graphviz file but its trush
// maybe it will be imporved in the future
// i hate this function
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <utility>
#include <cctype>
#include <stdexcept>
#include <string>
#include <unordered_map>

// Forward declaration for retrieving token names from state index
// You should implement or include getSyntaxKind and syntaxKindEnumToString as needed
SyntaxKind getSyntaxKind(int state);
extern const std::string syntaxKindEnumToString[];

// Escape special characters for Graphviz labels
std::string escapeChar(char c)
{
    switch (c)
    {
    case '\n':
        return "\\n";
    case '\r':
        return "\\r";
    case '\t':
        return "\\t";
    case ' ':
        return "space";
    case '"':
        return "\\\"";
    case '\\':
        return "\\\\";
    default:
        return std::string(1, c);
    }
}

// Build a compact label for a set of transition characters
std::string buildLabel(const std::vector<char> &chars)
{
    if (chars.size() > 5)
    {
        bool allLetters = std::all_of(chars.begin(), chars.end(), [](char c)
                                      { return std::isalpha(static_cast<unsigned char>(c)); });
        if (allLetters)
            return "letter";
        bool allDigits = std::all_of(chars.begin(), chars.end(), [](char c)
                                     { return std::isdigit(static_cast<unsigned char>(c)); });
        if (allDigits)
            return "digit";
        return "other";
    }
    std::ostringstream oss;
    for (char c : chars)
    {
        oss << escapeChar(c);
    }
    return oss.str();
}

// Generates a Graphviz DOT of the DFA, labeling states with their semantic names
void generateGraphviz(int **mat,
                      int numStates,
                      const std::unordered_map<char, int> &charToIndex,
                      const std::vector<int> &endStates,
                      const std::string &outputFile)
{
    std::ofstream out(outputFile);
    if (!out)
        throw std::runtime_error("Cannot open output file: " + outputFile);

    out << "digraph DFA {\n"
        << "  rankdir=LR;\n"
        << "  node [fontname=\"Arial\", fontsize=12];\n"
        << "  edge [fontname=\"Arial\", fontsize=10];\n";

    int startState = 0;
    int wsState = numStates - 2;
    int commentState = numStates - 1;

    // Label every state node
    for (int s = 0; s < numStates; ++s)
    {
        out << "  " << s << " [";
        // Shape selection
        if (s == startState)
        {
            out << "shape=doublecircle, style=filled, fillcolor=lightblue";
        }
        else if (s == wsState || s == commentState)
        {
            out << "shape=doublecircle, style=dashed";
        }
        else if (std::find(endStates.begin(), endStates.end(), s) != endStates.end())
        {
            out << "shape=doublecircle";
        }
        else
        {
            out << "shape=circle";
        }
        // Label content
        out << ", label=\"";
        if (s == startState)
        {
            out << "START";
        }
        else if (s == wsState)
        {
            out << "WhiteSpace";
        }
        else if (s == commentState)
        {
            out << "Comment";
        }
        else if (std::find(endStates.begin(), endStates.end(), s) != endStates.end())
        {
            int kind = static_cast<int>(getSyntaxKind(s));
            out << syntaxKindEnumToString[kind];
        }
        else
        {
            out << s;
        }
        out << "\"];\n";
    }

    // Helper to escape and group transition labels
    auto escapeChar = [](char c)
    {
        switch (c)
        {
        case '\n':
            return std::string("\\n");
        case '\r':
            return std::string("\\r");
        case '\t':
            return std::string("\\t");
        case ' ':
            return std::string("space");
        case '"':
            return std::string("\\\"");
        case '\\':
            return std::string("\\\\");
        default:
            return std::string(1, c);
        }
    };
    auto buildLabel = [&](const std::vector<char> &chars)
    {
        if (chars.size() > 5)
        {
            bool allLetters = std::all_of(chars.begin(), chars.end(),
                                          [](char c)
                                          { return std::isalpha(static_cast<unsigned char>(c)); });
            if (allLetters)
                return std::string("letter");
            bool allDigits = std::all_of(chars.begin(), chars.end(),
                                         [](char c)
                                         { return std::isdigit(static_cast<unsigned char>(c)); });
            if (allDigits)
                return std::string("digit");
            return std::string("other");
        }
        std::ostringstream oss;
        for (char c : chars)
            oss << escapeChar(c);
        return oss.str();
    };

    // Collect transitions grouped by (from -> to)
    std::map<std::pair<int, int>, std::vector<char>> transitions;
    for (int s = 0; s < numStates; ++s)
    {
        for (auto &kv : charToIndex)
        {
            int t = mat[s][kv.second];
            if (t >= 0)
                transitions[{s, t}].push_back(kv.first);
        }
    }

    // Emit edges with grouped labels
    for (auto &kv : transitions)
    {
        int from = kv.first.first;
        int to = kv.first.second;
        std::string lbl = buildLabel(kv.second);
        out << "  " << from << " -> " << to
            << " [label=\"" << lbl << "\"];\n";
    }

    out << "}\n";
    out.close();
}
