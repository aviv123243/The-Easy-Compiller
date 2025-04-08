#include "../../token/token.hpp"
#include "../scope/scope.hpp"
#include <String>
#include <vector>

class functionEntery
{
    private:
        string name;
        SyntaxKind returnType;
        vector<SyntaxKind> paramTypes;

        vector<scope *> innerScopes;

    public:
        functionEntery(string name, SyntaxKind returnType, vector<SyntaxKind> paramTypes) : name(name), returnType(returnType), paramTypes(paramTypes) {}

        string getName() const { return name; }
        SyntaxKind getReturnType() const { return returnType; }
        vector<SyntaxKind> getParamTypes() const { return paramTypes; }

        void addInnerScope(scope *innerScope) { innerScopes.push_back(innerScope); }
        vector<scope *> getInnerScopes() const { return innerScopes; }
        void print() const;

};