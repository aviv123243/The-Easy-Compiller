#include "../src/DFA/DFA.hpp"
#include "../src/lexer/lexer.hpp"
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <map>
#include <vector>

//garbege function that "seppose" to generate a graphviz file but its trush
//maybe it will be imporved in the future
//i hate this function
void generateGraphviz(int **mat, int numStates, std::unordered_map<char, int> &charToIndex, const std::string &outputFile)
{
    std::ofstream out(outputFile);

    // Write header with styling
    out << "digraph DFA {\n";
    out << "  rankdir=LR;\n"; // Left to right layout
    out << "  node [shape=circle, fontname=\"Arial\", fontsize=12];\n";
    out << "  edge [fontname=\"Arial\", fontsize=10];\n";

    // Style start state
    out << "  0 [style=filled, fillcolor=lightgray];\n";

    // Style accepting states (states 1-20 are typically accepting states in your DFA)
    // Mark all end states with double circles
    for (int i = 1; i < numStates - 2; i++)
    { // Excluding the last two states (skip states)
        if (i >= 43 && i <= 104) continue;

        out << "  " << i << " [shape=doublecircle, label=\"" << syntaxkindToString[getSyntaxKind(i)]  << "\"];\n";
    }
    // Mark skip states specially
    out << "  " << (numStates - 2) << " [shape=doublecircle, style=dashed, label=\"WhiteSpace\"];\n";
    out << "  " << (numStates - 1) << " [shape=doublecircle, style=dashed, label=\"Comment\"];\n";

    // Organize transitions to combine edges with same source and target
    std::map<std::pair<int, int>, std::vector<char>> transitions;

    for (int state = 0; state < numStates; ++state)
    {
        for (const auto &pair : charToIndex)
        {
            int nextState = mat[state][pair.second];
            if (nextState != -1)
            {
                transitions[{state, nextState}].push_back(pair.first);
            }
        }
    }

    // Write transitions with combined labels
    for (const auto &trans : transitions)
    {
        std::string label;
        if (trans.second.size() > 3)
        {
            if (trans.second.front() >= 'A' && trans.second.back() <= 'z')
            {
                label += "letter";
            }
            else if (trans.second.front() >= '0' && trans.second.back() <= '9')
            {
                label += "number";
            }else{
                label += "ALL SYMBOLS";
            }
        }
        else if (trans.first.first != -1 && trans.first.second != -1)
        {
            // Otherwise list individual characters
            for (char c : trans.second)
            {
                if (c == '\n')
                    label += "\\n";
                else if (c == '\r')
                    label += "\\r";
                else if (c == '\t')
                    label += "\\t";
                else if (c == ' ')
                    label += "space";
                else if (c == '"')
                    label += "\\\"";
                else if (c == '\\')
                    label += "\\\\";
                else
                    label += c;
            }
        }

        out << "  " << trans.first.first << " -> " << trans.first.second
            << " [label=\"" << label << "\"];\n";
    }

    out << "}\n";
    out.close();
}