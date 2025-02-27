#ifndef __STACK_ITEM
#define __STACK_ITEM
#include <string>

#include "../../nodes/nodes.hpp"

using namespace std;

struct StackItem
{
    int state;
    ASTNode *node;
};

string stackItemToString(StackItem item);
void printStackItem(StackItem item);
#endif