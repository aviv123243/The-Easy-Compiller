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
    valType _returnType;
    vector<valType> _paramTypes;

    scope *_scopeRoot;

public:
    functionEntry(string name, valType returnType, vector<valType> paramTypes) : _name(name), _returnType(returnType), _paramTypes(paramTypes) {}

    string getName() const { return _name; }
    valType getReturnType() const { return _returnType; }
    vector<valType> getParamTypes() const { return _paramTypes; }

    scope *getInnerScope() const { return _scopeRoot; }

    void setInnerScope(scope *innerScope) { _scopeRoot = innerScope; }
    void print() const;
};

#endif