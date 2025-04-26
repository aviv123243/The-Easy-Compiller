#ifndef __LABLE_MANAGER
#define __LABLE_MANAGER

#include <sstream>
#include <string>

using namespace std;

class LabelManager
{
private:
    int _lableNum;

public:
    LabelManager();
    int create();
    string getFunctionLable(string funcName);
    string getFunctionPreambleLable(string funcName);
    string getFunctionEpilogueLable(string funcName);
    string getName(int lableNum);
};

#endif