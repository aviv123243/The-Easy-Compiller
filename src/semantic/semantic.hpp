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
    SymbolTable *_symbolTable;
    std::stack<scope *> _scopeStack;
    scope *_currRootScope;
    std::vector<NonTerminalNode *> _currFunctionParamNodes;
    std::vector<NonTerminalNode *> _currFunctionReturnNodes;
    std::map<NonTerminal, void (SemanticAnalyzer::*)(ASTNode *)> _nonTerminalAssignActions;

    // Refactored helper functions
    bool isPointerToPointerAssignInvalid(valType left, valType right, SyntaxToken *token);
    bool isArrayToPointerAssignAllowed(valType left, valType right);
    bool isArrayAssignmentInvalid(valType left, valType right, SyntaxToken *token);
    bool isPointerMismatch(valType left, valType right, SyntaxToken *token);

    // Assignment type inference helpers
    void initAssignActions();
    valType getVarType(SyntaxToken *IDToken);
    valType getFunctionCallValTypeAndCheck(NonTerminalNode *funcCallNode);
    

    // Type assignment
    void assignParamNodeType(ASTNode *node);
    void assignTypeNodeType(ASTNode *node);
    void assignBaseTypeNodeType(ASTNode *node);
    void assignVarDeclExprNodeType(ASTNode *node);
    void assignAssignValueNodeType(ASTNode *node);
    void assignAssignExprNodeType(ASTNode *node);
    void assignAssignTargetNodeType(ASTNode *node);
    void assignConditionOpNodeType(ASTNode *node);
    void assignSimpleStmtNodeType(ASTNode *node);
    void assignExprListNodeType(ASTNode *node);
    void assignExprListNonEmptyNodeType(ASTNode *node);
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

public:
    SemanticAnalyzer(ErrorHandler *errorHandler, SymbolTable *symbolTable);

    void updateSybolTable(ASTNode *node);
    void updateScope(SyntaxToken *currToken);
    void addFunctionNodeToSymbolTable(NonTerminalNode *funcDeclNode);
    void addVariableNodeToSymbolTable(NonTerminalNode *varDeclNode);
    void addParamNodeToSymbolTable(NonTerminalNode *paramNode);
    void addParamListToSymbolTable(std::vector<NonTerminalNode *> paramNodes);
    void assignNodeType(ASTNode *node);

    valType checkCompatibilityBinaryOp(valType leftOp, valType rightOp, SyntaxToken *opToken);
    valType checkCompatibilityAssignExp(valType leftOp, valType rightOp, SyntaxToken *opToken);

    void checkReturnStatements(functionEntry *funcEntry);
    void checkForMainFunction();
};

#endif // SEMANTIC_HPP
