#include "headers/DFA.hpp"
#include <iostream>

using namespace std;
int main()
{
    DFA dfa("doubleConfig.txt");

    // dfa.printTM();

    string num = "1.1";
    cout << boolalpha << dfa.inLanguage(num);
}