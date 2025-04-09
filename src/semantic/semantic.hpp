#ifndef __SEMANTIC_ANALYZER
#define __SEMANTIC_ANALYZER

#include "../nodes/nodes.hpp"
#include "../symbolTable/scope/scope.hpp"
#include "../symbolTable/tableEntry/tableEntry.hpp"
#include "../symbolTable/symbolTable.hpp"
#include "../errorHandler/errorHandler.hpp"
#include "../errors/errors.hpp"
#include <stack>

class SemanticAnalyzer
{
private:
    ASTNode *_root;
    stack<ASTNode *> _nodesStack;
    stack<scope *> _scopeStack;

    int _functionCursor;

    ErrorHandler *_errorHandler;
    SymbolTable *_symbolTable;

    // helper functions
    bool isFuncCall(ASTNode *node);

public:
    SemanticAnalyzer(ASTNode *root, ErrorHandler *errorHandler, SymbolTable *symbolTable);
    void fillStack();
    void initAndCheckTypes();

    bool analyzeTypesMatch_varDec(NonTerminalNode* ntNode);
    bool isTypesMatch_assignment();
    bool isTypesMatch_funcCall();
    bool isTypesMatch_return();
    bool isIndexInt();
    bool checkIfFuncInScope(NonTerminalNode *funcCallNode);
    bool isVarInScope();

    void checkSymbolTable();
    bool isFunctionDeclaredTwice();
    bool isVarDeclaredTwice();

    void analyze();
};

#endif