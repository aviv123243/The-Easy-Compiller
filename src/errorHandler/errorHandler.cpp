#include "../errorHandler/errorHandler.hpp"

int ErrorHandler::getErrorCount() const
{
    return _errors.size();
}

void ErrorHandler::addError(Error *error)
{
    _errors.push_back(error);
}

void ErrorHandler::printErrors()
{
    for (int i = 0; i < _errors.size(); i++)
    {
        cout << _errors[i] -> toString() << endl;
    }
}