#include "headers/DFA.hpp"
#include <iostream>

using namespace std;


int main()
{
    DFA dfa("lexerDFAConfig.txt");

    dfa.printMatrix();

    string num = "\"\"";
    cout << boolalpha << dfa.inLanguage(num).first << endl;
    cout << dfa.inLanguage(num).second;
}