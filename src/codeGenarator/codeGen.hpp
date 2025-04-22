#ifndef CODEGEN_HPP
#define CODEGEN_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <string>
#include <sstream>
#include "../nodes/nodes.hpp"
#include "../nodeAnalyzer/nodeAnalyzer.hpp"
#include "../symbolTable/symbolTable.hpp"
#include "../symbolTable/functionEntry/functionEntry.hpp"
#include "../symbolTable/tableEntry/tableEntry.hpp"
#include "scratch/scratch.hpp"
#include "lableManager/lableManager.hpp"
#include <stack>
#include <fstream>

using namespace std;

class CodeGenarator
{
private:
    ofstream _outputFile;
    ASTNode *_root;
    vector<functionEntry *> _functions;
    int _currFunctionIndex;
    stack<scope *> _scopeStack;

    ScratchManager _scratchManager;
    LabelManager _lableManager;

    functionEntry *getCurrFunctionEntry() { return _functions[_currFunctionIndex]; }
    int assignStackOffset(scope *currScope);

    void funcCodeGen(NonTerminalNode *node);
    void stmtCodeGen(NonTerminalNode *node);
    void simpleStmtCodeGen(NonTerminalNode *node);

    void exprOptCodeGen(NonTerminalNode *node);
    void exprCodeGen(ASTNode *node);
    void addExprCodeGen(NonTerminalNode *node);
    void mulExprCodeGen(NonTerminalNode *node);
    void unaryExprCodeGen(NonTerminalNode *node);
    void primaryExprCodeGen(NonTerminalNode *node);
    void callExprCodeGen(NonTerminalNode *node);

    void logicalExprCodeGen(NonTerminalNode *node);
    void relationalExprCodeGen(NonTerminalNode *node);
    void incrementExprCodeGen(NonTerminalNode *node);
    void pointerExprCodeGen(NonTerminalNode *node);
    void addressExprCodeGen(NonTerminalNode *node);
    void dereferenceExprCodeGen(NonTerminalNode *node);

    void castCharToInt(int charReg, int intReg);
    void castIntToFloat(int intReg, int xmmReg);

    void pushAllCodeGen();
    void popAllCodeGen();
    void movCodeGen(ASTNode *to, ASTNode *from);

    int sizeOfType(const valType &t) const;
    string nameOfType(const valType &t) const;
    int layoutLocals(scope *s, int runningOffset);
    void loadFunctionVariables(functionEntry *func);
    void loadFunctionVar(string srcAddr, string dstAddr, int reg);
    void movCommendCodeGen(int leftReg, int rightReg);
    void loadMem(string srcAddr, int reg);
    void storeMem(string srcAddr, int reg);
    string getVarAddr(const std::string &name) const;

public:
    CodeGenarator(string outputFile, ASTNode *root, SymbolTable *symbolTable);
    void genCode();
};

#endif
