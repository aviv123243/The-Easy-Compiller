#ifndef __LEXER_DEBUGGING_UTILS
#define __LEXER_DEBUGGING_UTILS

#include "../../token/token.hpp"
#include <string>
#include <sstream>
#include <iostream>

extern std::string syntaxkindToString[]; // Declare the array
std::string syntaxTokenToString(SyntaxToken token); // Declare the function
void printSyntaxToken(SyntaxToken token); // Declare the function

#endif