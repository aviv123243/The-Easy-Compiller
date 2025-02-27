#include "stackItem.hpp"
#include "../../nodes/nodes.hpp"
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

string stackItemToString(StackItem item)
{
    stringstream res;
    res << "(" << ""<<AstNodeToString(item.node)<<"" << " | " << item.state << ")";
    return res.str();
}

void printStackItem(StackItem item)
{
    cout << stackItemToString(item) << endl;
}