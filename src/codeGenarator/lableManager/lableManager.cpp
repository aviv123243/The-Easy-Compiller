#include "lableManager.hpp"

using namespace std;

LabelManager::LabelManager() : _lableNum(0) {}

int LabelManager::create()
{
    return _lableNum++;
}

string LabelManager::getName(int lableNum)
{
    stringstream res;
    res << "L" << lableNum;
    return res.str();
}

string LabelManager::getFunctionLable(string funcName)
{
    return "function_" + funcName ;
}

string LabelManager::getFunctionPreambleLable(string funcName)
{
    return "function_" + funcName + "_preamble";
}

string LabelManager::getFunctionEpilogueLable(string funcName)
{
    return "function_" + funcName + "_epilogue";
}
