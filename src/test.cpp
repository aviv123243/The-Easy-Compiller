#include "headers/DFA.hpp"
#include <iostream>

using namespace std;


int main()
{
    DFA dfa("lexerDFA.txt");

    //dfa.printMatrix();

    string num = " 777";
    cout << boolalpha << dfa.inLanguage(num).first << endl;
    cout << dfa.inLanguage(num).second;
}