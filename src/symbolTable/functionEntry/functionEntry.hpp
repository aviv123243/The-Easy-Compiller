#ifndef __FUNCTION_ENTRY
#define __FUNCTION_ENTRY

#include "../../token/token.hpp"
#include "../scope/scope.hpp"
#include <String>
#include <vector>

class functionEntry
{
private:
    string _name;
    varType _returnType;
    vector<varType> _paramTypes;

    scope *_scopeRoot;

public:
    functionEntry(string name, varType returnType, vector<varType> paramTypes) : _name(name), _returnType(returnType), _paramTypes(paramTypes) {}

    string getName() const { return _name; }
    varType getReturnType() const { return _returnType; }
    vector<varType> getParamTypes() const { return _paramTypes; }

    void setInnerScope(scope *innerScope) { _scopeRoot = innerScope; }
    void print() const;
};

#endif 