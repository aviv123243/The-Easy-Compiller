#ifndef __ERROR_HANDLER
#define __ERROR_HANDLER

#include "../errors/errors.hpp"
#include <vector>
#include <iostream>

class ErrorHandler
{
    private:
        vector<Error*> _errors;

    public:
        ErrorHandler() {}

        int getErrorCount() const;

        void addError(Error *error);

        void printErrors();

};

#endif