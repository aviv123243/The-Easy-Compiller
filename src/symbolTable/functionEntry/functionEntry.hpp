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
    SyntaxKind _returnType;
    vector<SyntaxKind> _paramTypes;

    scope *_scopeRoot;

public:
    functionEntry(string name, SyntaxKind returnType, vector<SyntaxKind> paramTypes) : _name(name), _returnType(returnType), _paramTypes(paramTypes) {}

    string getName() const { return _name; }
    SyntaxKind getReturnType() const { return _returnType; }
    vector<SyntaxKind> getParamTypes() const { return _paramTypes; }

    void setInnerScope(scope *innerScope) { _scopeRoot = innerScope; }
    void print() const;
};

#endif 