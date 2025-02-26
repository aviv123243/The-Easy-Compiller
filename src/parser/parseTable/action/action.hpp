#ifndef __ACTION
#define __ACTION

enum actionType
{
    SHIFT,
    REDUCE,
    ACCEPT,
    ERROR
};

struct action
{
    actionType type;
    int num;
};

#endif