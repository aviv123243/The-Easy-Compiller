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

#define NUM_OF_BUILT_IN_FUNCTIONS 3
#define SIZE_OF_STACK_VAR 8

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
    void stmtListCodeGen(NonTerminalNode *node);
    void stmtCodeGen(NonTerminalNode *node);
    void simpleStmtCodeGen(NonTerminalNode *node);
    void varDeclExprCodeGen(NonTerminalNode *node);
    void ifStmtCodeGen(NonTerminalNode *node);
    void conditionOptionCodeGen(NonTerminalNode *node);
    void whileStmtCodeGen(NonTerminalNode *node);
    void forStmtCodeGen(NonTerminalNode *node);
    void forInitCodeGen(NonTerminalNode *node);
    void forUpdateCodeGen(NonTerminalNode *node);
    void bodyCodeGen(NonTerminalNode *node);
    void assignExpressionCodeGen(NonTerminalNode *node);
    void exprOptCodeGen(NonTerminalNode *node);
    void exprCodeGen(ASTNode *node);
    void addExprCodeGen(NonTerminalNode *node);
    void mulExprCodeGen(NonTerminalNode *node);
    void unaryExprCodeGen(NonTerminalNode *node);
    void primaryExprCodeGen(NonTerminalNode *node);
    void callExprCodeGen(NonTerminalNode *node);
    void logicalExprCodeGen(NonTerminalNode *node);
    void relationalExprCodeGen(NonTerminalNode *node);
    void pushArgs(vector<NonTerminalNode *> args);
    void incrementExprCodeGen(NonTerminalNode *node);
    void addressExprCodeGen(NonTerminalNode *node);
    void dereferenceExprCodeGen(NonTerminalNode *node);

    void castToFloat(int intReg, int xmmReg);

    int sizeOfType(const valType &t) const;
    string nameOfType(const valType &t) const;
    int layoutLocals(scope *s, int runningOffset);
    void loadFunctionVariables(functionEntry *func);
    void loadFunctionVar(string srcAddr, string dstAddr, int reg);
    void push(int reg);
    void mov(string leftReg, string rightReg);
    void neg(int reg);
    void compareToZero(int reg);
    void loadMemPtrValue(string srcAddr, int reg);
    void loadMem(string srcAddr, int reg);
    void storeMemPtrValue(string srcAddr, int reg);
    void storeMem(string srcAddr, int reg);
    string getVarAddr(const string &name) const;
    void printIntFuncCodeGen();
    void printFloatFuncCodeGen();
    void printBoolFuncCodeGen();
    void floatMacroCodeGen();

public:
    CodeGenarator(string outputFile, ASTNode *root, SymbolTable *symbolTable);
    void genCode();
};

#endif
