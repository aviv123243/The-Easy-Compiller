#ifndef __SEMANTIC_ANALYZER
#define __SEMANTIC_ANALYZER

#include "../nodes/nodes.hpp"
#include "../nodes/nodeAnalyzer/nodeAnalyzer.hpp"
#include "../symbolTable/scope/scope.hpp"
#include "../symbolTable/tableEntry/tableEntry.hpp"
#include "../symbolTable/symbolTable.hpp"
#include "../errorHandler/errorHandler.hpp"
#include "../errors/errors.hpp"
#include <stack>

extern map<SyntaxKind, baseType> assignTerminal;

class SemanticAnalyzer
{
private:
    ErrorHandler *_errorHandler;

    map<NonTerminal, void (SemanticAnalyzer::*)(ASTNode *)> _nonTerminalAssignActions;

    // symbol table mangaement
    SymbolTable *_symbolTable;
    stack<scope *> _scopeStack;
    scope *_currRootScope;
    vector<NonTerminalNode *> _currFunctionParamNodes;
    vector<NonTerminalNode *> _currFunctionReturnNodes;

public:
    SemanticAnalyzer(ErrorHandler *errorHandler, SymbolTable *symbolTable);

    // symbol table mangaement
    void updateScope(SyntaxToken *currToken);
    void updateSybolTable(ASTNode *node);

    void addFunctionNodeToSymbolTable(NonTerminalNode *funcDeclNode);
    void addVariableNodeToSymbolTable(NonTerminalNode *varDeclNode);
    void addParamNodeToSymbolTable(NonTerminalNode *paramNode);
    void addParamListToSymbolTable(vector<NonTerminalNode *> paramNodes);

    const SymbolTable *getSymbolTable() const { return _symbolTable; }
    const scope *getCurrRootScope() const { return _currRootScope; }
    const stack<scope *> &getScopeStack() const { return _scopeStack; }

    valType checkCompatibilityBinaryOp(valType leftOp, valType rightOp, SyntaxToken *opToken);
    valType checkCompatibilityAssignExp(valType leftOp, valType rightOp, SyntaxToken *opToken);
    void checkReturnStatements(functionEntry *funcEntry);
    valType getVarType(SyntaxToken *IDToken);
    valType getFunctionCallValTypeAndCheck(NonTerminalNode *funcCallNode);

    void initAssignActions();

    void assignNodeType(ASTNode *node);
    void assignParamNodeType(ASTNode *node);
    void assignTypeNodeType(ASTNode *node);
    void assignBaseTypeNodeType(ASTNode *node);
    void assignVarDeclExprNodeType(ASTNode *node);
    void assignAssignValueNodeType(ASTNode *node);
    void assignAssignExprNodeType(ASTNode *node);
    void assignAssignTargetNodeType(ASTNode *node);
    void assignConditionOpNodeType(ASTNode *node);
    void assignSimpleStmtNodeType(ASTNode *node);
    void assignExprNodeType(ASTNode *node);
    void assignLogicalExprNodeType(ASTNode *node);
    void assignRelationalExprNodeType(ASTNode *node);
    void assignAddExprNodeType(ASTNode *node);
    void assignMulExprNodeType(ASTNode *node);
    void assignUnaryExprNodeType(ASTNode *node);
    void assignIncrementExprNodeType(ASTNode *node);
    void assignAddressExprNodeType(ASTNode *node);
    void assignDereferenceExprNodeType(ASTNode *node);
    void assignPrimaryExprNodeType(ASTNode *node);

    void checkForMainFunction();
};

#endif