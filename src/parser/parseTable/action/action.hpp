#ifndef __ACTION
#define __ACTION
#include <string>
#include <sstream>

using namespace std;

enum actionType
{
    SHIFT,
    REDUCE,
    ACCEPT,
    DEFAULT,
};

struct action
{
    actionType type;
    int num;
};

string actionTypeToString(action type);
#endif