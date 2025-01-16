#include "headers/DFA.hpp"
#include <iostream>

using namespace std;
int main()
{
    DFA dfa("intConfig.txt");

    //dfa.printTM();

    string num = "13";
    cout << dfa.inLanguage(num);
}