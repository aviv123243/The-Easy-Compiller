#include "action.hpp"

string actionTypeToString(action type)
{
    stringstream res;
    switch (type.type)
    {
    case actionType::SHIFT:
        res << "s" << type.num;
        break;
    case actionType::REDUCE:
        res << "r" << type.num;
        break;
    case actionType::ACCEPT:
        res << "acc";
        break;
    case actionType::ERROR:
        res << "ERROR";
        break;
    default:
        res << "UNKNOWN";
        break;
    }

    return res.str();
}