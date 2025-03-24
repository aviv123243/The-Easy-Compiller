// #include <iostream>
// #include <fstream>
// #include <sstream>
// #include <unordered_map>
// #include "../src/parser/parser.hpp"  // Include necessary parser headers

// void generateParserInit(const std::string &bisonOutputFile, const std::string &outputFile);

// int main(int argc, char const *argv[])
// {
//     generateParserInit("bison.output", "parserInit.cpp"); // Generate parser initialization function
//     return 0;
// }

// // Function to parse Bison output and generate parser initialization
// void generateParserInit(const std::string &bisonOutputFile, const std::string &outputFile)
// {
//     std::ifstream infile(bisonOutputFile);
//     if (!infile)
//     {
//         std::cerr << "Error: Could not open file " << bisonOutputFile << std::endl;
//         return;
//     }

//     std::ofstream outfile(outputFile);
//     if (!outfile)
//     {
//         std::cerr << "Error: Could not open output file " << outputFile << std::endl;
//         return;
//     }

//     std::string line;
//     int currentState = -1;
//     std::unordered_map<int, std::unordered_map<std::string, std::string>> actionTable;
//     std::unordered_map<int, std::unordered_map<std::string, int>> gotoTable;
//     std::unordered_map<int, std::string> defaultActions;

//     while (std::getline(infile, line))
//     {
//         cout << "here" << endl;
//         std::istringstream iss(line);
//         std::string firstWord;
//         iss >> firstWord;

//         if (firstWord == "state")
//         {
//             iss >> currentState; // Extract the state number
//             cout << "here2 " << currentState << endl;
//         }
//         else if (!firstWord.empty() && currentState != -1)
//         {
//             std::string action;
//             if (line.find("shift") != std::string::npos)
//             {
//                 int targetState;
//                 iss >> action >> targetState;
//                 actionTable[currentState][firstWord] = "SHIFT(" + std::to_string(targetState) + ")";
//             }
//             else if (line.find("reduce") != std::string::npos)
//             {
//                 int ruleNum;
//                 iss >> action >> ruleNum;
//                 actionTable[currentState][firstWord] = "REDUCE(" + std::to_string(ruleNum) + ")";
//             }
//             else if (line.find("go to state") != std::string::npos)
//             {
//                 int targetState;
//                 iss >> action >> action >> targetState;
//                 gotoTable[currentState][firstWord] = targetState;
//             }
//             else if (line.find("accept") != std::string::npos)
//             {
//                 actionTable[currentState][firstWord] = "ACCEPT";
//             }
//             else if (line.find("$default") != std::string::npos)
//             {
//                 std::string defaultAction;
//                 std::getline(iss, defaultAction);
//                 defaultActions[currentState] = defaultAction;
//             }
//         }
//     }

//     // Write generated code to the output file
//     outfile << "void Parser::fillTables() {\n";
//     for (const auto &state : actionTable)
//     {
//         for (const auto &entry : state.second)
//         {
//             outfile << "    _actionTable.add(" << state.first << ", " << entry.first << ", " << entry.second << ");\n";
//         }
//     }

//     for (const auto &state : gotoTable)
//     {
//         for (const auto &entry : state.second)
//         {
//             outfile << "    _gotoTable.add(" << state.first << ", " << entry.first << ", " << entry.second << ");\n";
//         }
//     }

//     for (const auto &state : defaultActions)
//     {
//         outfile << "    _actionTable.addDefault(" << state.first << ", " << state.second << ");\n";
//     }

//     outfile << "}\n";

//     infile.close();
//     outfile.close();

//     std::cout << "Parser initialization function generated successfully in " << outputFile << std::endl;
// }
