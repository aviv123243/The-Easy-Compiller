#include "codeGen.hpp"

CodeGenarator::CodeGenarator(string outputFile, ASTNode *root, SymbolTable *symbolTable)
    : _outputFile(outputFile), _root(root), _functions(symbolTable->getFunctions()), _currFunctionIndex(0) {}

void CodeGenarator::genCode()
{
    floatMacroCodeGen();

    _outputFile << ".data\n";
    _outputFile << "format_int db \"%d \", 10, 0\n";
    _outputFile << "format_float db \"%lf \", 10, 0\n";
    _outputFile << "\n.code\n";
    _outputFile << "extern ExitProcess : proc\n";

    _outputFile << "extern printf : proc\n";

    _outputFile << "\nmain PROC\n";
    _outputFile << "\tcall function_main\n";
    _outputFile << "\tmov ecx, eax\n";
    _outputFile << "\tcall ExitProcess\n";
    _outputFile << " main ENDP\n";
    printIntFuncCodeGen();
    printFloatFuncCodeGen();
    vector<NonTerminalNode *> funcDeclNodes = getFunctionDeclNodes((NonTerminalNode *)_root);
    int j = 0;
    for (int i = NUM_OF_BUILT_IN_FUNCTIONS; i < _functions.size(); i++)
    {
        _currFunctionIndex = i;

        funcCodeGen(funcDeclNodes[j++]);
    }

    _outputFile << "\n\nEND";
    _outputFile.close();
}

void CodeGenarator::funcCodeGen(NonTerminalNode *node)
{
    _scopeStack.push(getCurrFunctionEntry()->getInnerScope());
    string funcName = getCurrFunctionEntry()->getName();
    _outputFile << "\n"
                << _lableManager.getFunctionLable(funcName) << ":\n";
    _outputFile << "\tpush rbp\n";
    _outputFile << "\tmov rbp, rsp\n";

    int offset = assignStackOffset(getCurrFunctionEntry()->getInnerScope());

    _outputFile << "\tsub rsp, " << offset << "\n";
    loadFunctionVariables(getCurrFunctionEntry());

    stmtListCodeGen((NonTerminalNode *)node->GetChildren()[8]);

    _outputFile << _lableManager.getFunctionEpilogueLable(funcName) << ":\n";
    _outputFile << "\tmov rsp, rbp\n";
    _outputFile << "\tpop rbp\n";
    _outputFile << "\tret\n";
    _scopeStack.pop();
}

void CodeGenarator::stmtListCodeGen(NonTerminalNode *node)
{
    vector<NonTerminalNode *> children = getStmtNodes(node);
    for (NonTerminalNode *child : children)
    {
        stmtCodeGen((NonTerminalNode *)child);
    }
}

void CodeGenarator::stmtCodeGen(NonTerminalNode *node)
{
    vector<ASTNode *> children = node->GetChildren();
    NonTerminalNode *firstChild = (NonTerminalNode *)children[0];
    if (firstChild->getNonTerminalKind() == SIMPLE_STMT)
    {
        simpleStmtCodeGen(firstChild);
    }

    else if (firstChild->getNonTerminalKind() == IF_STMT)
    {
        ifStmtCodeGen(firstChild);
    }

    else if (firstChild->getNonTerminalKind() == WHILE_STMT)
    {
        whileStmtCodeGen(firstChild);
    }

    else if (firstChild->getNonTerminalKind() == FOR_STMT)
    {
        forStmtCodeGen(firstChild);
    }
}

void CodeGenarator::simpleStmtCodeGen(NonTerminalNode *node)
{
    vector<ASTNode *> children = node->GetChildren();
    NonTerminalNode *firstChild = (NonTerminalNode *)children[0];

    if (isReturnStatement(node))
    {
        ASTNode *exprOptNode = node->GetChildren()[1];
        if (!exprOptNode->GetChildren().empty())
        {
            exprOptCodeGen((NonTerminalNode *)exprOptNode);
            _outputFile << "\tmov rax, " << _scratchManager.getName(exprOptNode->GetRegister()) << "\n";
            _scratchManager.free(exprOptNode->GetRegister());
        }
        _outputFile << "\tjmp " << _lableManager.getFunctionEpilogueLable(getCurrFunctionEntry()->getName()) << "\n";
        _outputFile << endl;
    }

    if (firstChild->getNonTerminalKind() == VAR_DECL_EXPR)
    {
        varDeclExprCodeGen(firstChild);
    }

    if (isFuncCall(node))
    {
        callExprCodeGen(node);
        _scratchManager.free(node->GetRegister());
    }

    if (firstChild->getNonTerminalKind() == ASSIGN_EXPR)
    {
        assignExpressionCodeGen((NonTerminalNode *)firstChild);

        int reg = firstChild->GetRegister();
        _scratchManager.free(reg);
    }
}

void CodeGenarator::varDeclExprCodeGen(NonTerminalNode *node)
{
    vector<ASTNode *> varDeclChildren = node->GetChildren();
    NonTerminalNode *initOptNode = (NonTerminalNode *)varDeclChildren[2];

    if (initOptNode->GetChildren().size() != 0)
    {
        NonTerminalNode *assignValueNode = (NonTerminalNode *)(initOptNode->GetChildren()[1]);
        NonTerminalNode *exprNode = (NonTerminalNode *)(assignValueNode->GetChildren()[0]);

        exprCodeGen(exprNode);
        int reg = exprNode->GetRegister();
        storeMem(getVarAddr(((TerminalNode *)varDeclChildren[1])->getToken()->val), reg);
        _scratchManager.free(reg);
    }
}

void CodeGenarator::ifStmtCodeGen(NonTerminalNode *node)
{
    vector<ASTNode *> children = node->GetChildren();
    NonTerminalNode *conditionOpNode = (NonTerminalNode *)children[2];

    int elseLabel = _lableManager.create();
    int endLabel = _lableManager.create();

    conditionOptionCodeGen(conditionOpNode);
    compareToZero(conditionOpNode->GetRegister());
    _outputFile << "\tjz " << _lableManager.getName(elseLabel) << "\n";
    bodyCodeGen((NonTerminalNode *)children[4]);
    _outputFile << "\tjmp " << _lableManager.getName(endLabel) << "\n";
    _outputFile << _lableManager.getName(elseLabel) << ":\n";

    if (children.size() == 7)
    {
        bodyCodeGen((NonTerminalNode *)children[6]);
    }

    _outputFile << _lableManager.getName(endLabel) << ":\n";
}

void CodeGenarator::conditionOptionCodeGen(NonTerminalNode *node)
{
    vector<ASTNode *> children = node->GetChildren();
    NonTerminalNode *firstChild = (NonTerminalNode *)children[0];

    if (firstChild->getNonTerminalKind() == EXPR)
    {
        exprCodeGen(firstChild);
    }
    else if (firstChild->getNonTerminalKind() == ASSIGN_EXPR)
    {
        assignExpressionCodeGen(firstChild);
    }

    node->SetRegister(firstChild->GetRegister());
}

void CodeGenarator::whileStmtCodeGen(NonTerminalNode *node)
{
    vector<ASTNode *> children = node->GetChildren();
    NonTerminalNode *conditionOpNode = (NonTerminalNode *)children[2];

    int startLabel = _lableManager.create();
    int endLabel = _lableManager.create();

    _outputFile << _lableManager.getName(startLabel) << ":\n";

    conditionOptionCodeGen(conditionOpNode);

    compareToZero(conditionOpNode->GetRegister());
    _outputFile << "\tjz " << _lableManager.getName(endLabel) << "\n";
    bodyCodeGen((NonTerminalNode *)children[4]);
    _outputFile << "\tjmp " << _lableManager.getName(startLabel) << "\n";
    _outputFile << _lableManager.getName(endLabel) << ":\n";
}

void CodeGenarator::forStmtCodeGen(NonTerminalNode *node)
{
    vector<ASTNode *> children = node->GetChildren();
    NonTerminalNode *forIntNode = (NonTerminalNode *)children[2];
    NonTerminalNode *exprOpNode = (NonTerminalNode *)children[4];
    NonTerminalNode *incrementOptNode = (NonTerminalNode *)children[6];

    int startLabel = _lableManager.create();
    int endLabel = _lableManager.create();

    forInitCodeGen(forIntNode);

    _outputFile << _lableManager.getName(startLabel) << ":\n";

    exprOptCodeGen(exprOpNode);
    compareToZero(exprOpNode->GetRegister());
    _outputFile << "\tjz " << _lableManager.getName(endLabel) << "\n";
    bodyCodeGen((NonTerminalNode *)children[8]);

    forUpdateCodeGen(incrementOptNode);

    _outputFile << "\tjmp " << _lableManager.getName(startLabel) << "\n";
    _outputFile << _lableManager.getName(endLabel) << ":\n";
}

void CodeGenarator::forInitCodeGen(NonTerminalNode *node)
{
    vector<ASTNode *> children = node->GetChildren();
    if (children.size() != 0)
    {
        NonTerminalNode *firstChild = (NonTerminalNode *)children[0];
        if (firstChild->getNonTerminalKind() == VAR_DECL_EXPR)
        {
            exprCodeGen(firstChild);
            _scratchManager.free(firstChild->GetRegister());
        }
        else if (firstChild->getNonTerminalKind() == ASSIGN_EXPR)
        {
            assignExpressionCodeGen(firstChild);
        }
    }
}

void CodeGenarator::forUpdateCodeGen(NonTerminalNode *node)
{
    vector<ASTNode *> children = node->GetChildren();
    if (children.size() != 0)
    {
        NonTerminalNode *firstChild = (NonTerminalNode *)children[0];
        if (firstChild->getNonTerminalKind() == ASSIGN_EXPR)
        {
            assignExpressionCodeGen(firstChild);
        }

        else if (firstChild->getNonTerminalKind() == INCREMENT_EXPR)
        {
            incrementExprCodeGen(firstChild);
        }
    }
}

void CodeGenarator::bodyCodeGen(NonTerminalNode *node)
{
    vector<ASTNode *> children = node->GetChildren();
    NonTerminalNode *firstChild = (NonTerminalNode *)children[0];

    if (children.size() == 3)
    {
        stmtListCodeGen((NonTerminalNode *)children[1]);
    }
    else if (children.size() == 2)
    {
        simpleStmtCodeGen((NonTerminalNode *)children[0]);
    }
    else if (firstChild->getNonTerminalKind() == IF_STMT)
    {
        ifStmtCodeGen((NonTerminalNode *)firstChild);
    }
    else if (firstChild->getNonTerminalKind() == WHILE_STMT)
    {
        whileStmtCodeGen((NonTerminalNode *)firstChild);
    }
    else if (firstChild->getNonTerminalKind() == FOR_STMT)
    {
        forStmtCodeGen((NonTerminalNode *)firstChild);
    }
}
void CodeGenarator::assignExpressionCodeGen(NonTerminalNode *node)
{
    vector<ASTNode *> children = node->GetChildren();
    NonTerminalNode *leftExprNode = (NonTerminalNode *)children[0];
    NonTerminalNode *rightExprNode = (NonTerminalNode *)children[2];

    exprCodeGen(rightExprNode);
    int reg = rightExprNode->GetRegister();

    if(leftExprNode->GetChildren().size() == 2)
    {
        storeMemPtrValue(getVarAddr(((TerminalNode *)leftExprNode->GetChildren()[1])->getToken()->val), reg);
    }else
    {
        storeMem(getVarAddr(((TerminalNode *)leftExprNode->GetChildren()[0])->getToken()->val), reg);
    }

    node->SetRegister(reg);
}

void CodeGenarator::exprOptCodeGen(NonTerminalNode *node)
{
    if (!node->GetChildren().empty())
    {
        exprCodeGen(node->GetChildren()[0]);
        node->SetRegister(node->GetChildren()[0]->GetRegister());
    }
}

void CodeGenarator::exprCodeGen(ASTNode *node)
{
    ASTNode *child = node->GetChildren()[0];
    if (child->GetType() == NON_TERMINAL) {
      auto nt = (NonTerminalNode*)child;
      switch (nt->getNonTerminalKind()) {
        case LOGICAL_EXPR:
          logicalExprCodeGen(nt);
          break;
        case ADDRESS_EXPR:
          addressExprCodeGen(nt);
          break;
        case PRIMARY_EXPR:
          primaryExprCodeGen(nt);
          break;
      }
    }
    node->SetRegister(child->GetRegister());
}


void CodeGenarator::logicalExprCodeGen(NonTerminalNode *node)
{
    vector<ASTNode *> children = node->GetChildren();

    if (children.size() == 1)
    {
        relationalExprCodeGen((NonTerminalNode *)children[0]);
        node->SetRegister(children[0]->GetRegister());
        return;
    }

    logicalExprCodeGen((NonTerminalNode *)children[0]);
    relationalExprCodeGen((NonTerminalNode *)children[2]);

    int leftReg = children[0]->GetRegister();
    int rightReg = children[2]->GetRegister();

    string left = _scratchManager.getName(leftReg);
    string right = _scratchManager.getName(rightReg);

    SyntaxKind opKind = ((TerminalNode *)children[1])->getTerminalKind();

    string resultReg = left;

    // Compare both sides to zero
    _outputFile << "\tcmp " << left << ", 0\n";
    _outputFile << "\tsetne al\n";
    _outputFile << "\tmovzx " << left << ", al\n";

    _outputFile << "\tcmp " << right << ", 0\n";
    _outputFile << "\tsetne al\n";
    _outputFile << "\tmovzx " << right << ", al\n";

    if (opKind == PIPE_PIPE)
    {
        _outputFile << "\tor " << left << ", " << right << "\n";
    }
    else if (opKind == AMPERSAND_AMPERSAND)
    {
        _outputFile << "\tand " << left << ", " << right << "\n";
    }

    node->SetRegister(leftReg);
    _scratchManager.free(rightReg);
}

void CodeGenarator::relationalExprCodeGen(NonTerminalNode *node)
{
    vector<ASTNode *> children = node->GetChildren();
    if (children.size() == 1)
    {
        addExprCodeGen((NonTerminalNode *)children[0]);
        node->SetRegister(children[0]->GetRegister());
        return;
    }

    relationalExprCodeGen((NonTerminalNode *)children[0]);
    addExprCodeGen((NonTerminalNode *)children[2]);

    int leftReg = children[0]->GetRegister();
    int rightReg = children[2]->GetRegister();

    _outputFile << "\tcmp " << _scratchManager.getName(leftReg) << ", " << _scratchManager.getName(rightReg) << "\n";

    SyntaxKind opKind = ((TerminalNode *)children[1])->getTerminalKind();
    string instr;
    if (opKind == LESS_THAN)
        instr = "setl";
    else if (opKind == LESS_THAN_EQUALS)
        instr = "setle ";
    else if (opKind == GREATER_THAN)
        instr = "setg";
    else if (opKind == GREATER_THAN_EQUALS)
        instr = "setge";
    else if (opKind == EQUALS_EQUALS)
        instr = "sete";
    else if (opKind == BANG_EQUALS)
        instr = "setne";

    _outputFile << "\t" << instr << " al\n";
    _outputFile << "\tmovzx " << _scratchManager.getName(leftReg) << ", al\n";

    node->SetRegister(leftReg);
    _scratchManager.free(rightReg);
}

void CodeGenarator::addExprCodeGen(NonTerminalNode *node)
{
    cout << "<ADD_EXPR> ";
    auto &children = node->GetChildren();
    if (children.size() == 1)
    {
        mulExprCodeGen((NonTerminalNode *)children[0]);
        node->SetRegister(children[0]->GetRegister());
        return;
    }

    addExprCodeGen((NonTerminalNode *)children[0]);
    mulExprCodeGen((NonTerminalNode *)children[2]);

    int leftReg = children[0]->GetRegister();
    int rightReg = children[2]->GetRegister();

    SyntaxKind opKind = ((TerminalNode *)children[1])->getTerminalKind();
    string op;
    if (opKind == PLUS)
        op = "add";
    else if (opKind == MINUS)
        op = "sub";
    else if (opKind == PIPE)
        op = "or";
    else if (opKind == CARET)
        op = "xor";

    _outputFile << "\t" << op << " " << _scratchManager.getName(leftReg) << ", " << _scratchManager.getName(rightReg) << "\n";

    node->SetRegister(leftReg);
    _scratchManager.free(rightReg);
}

void CodeGenarator::mulExprCodeGen(NonTerminalNode *node)
{
    vector<ASTNode *> children = node->GetChildren();
    if (children.size() == 1)
    {
        unaryExprCodeGen((NonTerminalNode *)children[0]);
        node->SetRegister(children[0]->GetRegister());
        return;
    }

    mulExprCodeGen((NonTerminalNode *)children[0]);
    unaryExprCodeGen((NonTerminalNode *)children[2]);

    int leftReg = children[0]->GetRegister();
    int rightReg = children[2]->GetRegister();

    SyntaxKind opKind = ((TerminalNode *)children[1])->getTerminalKind();
    if (opKind == STAR)
    {
        _outputFile << "\timul " << _scratchManager.getName(leftReg) << ", " << _scratchManager.getName(rightReg) << "\n";
    }
    else if (opKind == SLASH)
    {
        _outputFile << "\tmov rax, " << _scratchManager.getName(leftReg) << "\n";
        _outputFile << "\tcqo\n";
        _outputFile << "\tidiv " << _scratchManager.getName(rightReg) << "\n";
        _outputFile << "\tmov " << _scratchManager.getName(leftReg) << ", rax\n";
    }
    else if (opKind == AMPERSAND)
    {
        _outputFile << "\tand " << _scratchManager.getName(leftReg) << ", " << _scratchManager.getName(rightReg) << "\n";
    }

    node->SetRegister(leftReg);
    _scratchManager.free(rightReg);
}

void CodeGenarator::unaryExprCodeGen(NonTerminalNode *node)
{
    vector<ASTNode *> children = node->GetChildren();
    if (children.size() == 1)
    {
        primaryExprCodeGen((NonTerminalNode *)children[0]);
        node->SetRegister(children[0]->GetRegister());
        return;
    }

    unaryExprCodeGen((NonTerminalNode *)children[1]);
    int reg = children[1]->GetRegister();
    node->SetRegister(reg);

    SyntaxKind op = ((TerminalNode *)children[0])->getTerminalKind();
    if (op == MINUS)
        neg(reg);
    else if (op == BANG)
    {
        compareToZero(reg);
        _outputFile << "\tsete al\n";
        _outputFile << "\tmovzx " << _scratchManager.getName(reg) << ", al\n";
    }
}

void CodeGenarator::neg(int reg)
{
    if (_scratchManager.isFloat(reg))
    {
        // -x ==> 0 - x

        int zeroReg = _scratchManager.allocFloat();
        _outputFile << "xorps " << _scratchManager.getName(zeroReg) << ", " << _scratchManager.getName(zeroReg) << "\n";
        _outputFile << "\tpsubd " << _scratchManager.getName(zeroReg) << ", " << _scratchManager.getName(reg) << "\n";
        _outputFile << "\tmovsd " << _scratchManager.getName(reg) << ", " << _scratchManager.getName(zeroReg) << "\n";
        _scratchManager.free(zeroReg);
    }
    else
    {
        _outputFile << "\tneg " << _scratchManager.getName(reg) << "\n";
    }
}

void CodeGenarator::compareToZero(int reg)
{
    if (_scratchManager.isFloat(reg))
    {
        int zeroReg = _scratchManager.allocFloat();
        _outputFile << "xorps " << _scratchManager.getName(zeroReg) << ", " << _scratchManager.getName(zeroReg) << "\n";
        _outputFile << "\tcomisd " << _scratchManager.getName(reg) << ", " << _scratchManager.getName(zeroReg) << "\n";
        _scratchManager.free(zeroReg);
    }
    else
    {
        _outputFile << "\tcmp " << _scratchManager.getName(reg) << ", 0\n";
    }
}

void CodeGenarator::primaryExprCodeGen(NonTerminalNode *node)
{
    std::vector<ASTNode*> children = node->GetChildren();
    ASTNode *first = children[0];

    // 1) if it's a nested non-terminal for * or ++/--, delegate immediately
    if (first->GetType() == NON_TERMINAL) {
        NonTerminalNode *nt = (NonTerminalNode*) first;
        if (nt->getNonTerminalKind() == DEREFERENCE_EXPR) {
            dereferenceExprCodeGen(nt);
            node->SetRegister(nt->GetRegister());
            return;
        }
        if (nt->getNonTerminalKind() == INCREMENT_EXPR) {
            incrementExprCodeGen(nt);
            node->SetRegister(nt->GetRegister());
            return;
        }
    }

    TerminalNode *tNode = (TerminalNode*) first;
    SyntaxToken *tok = tNode->getToken();

    // integer literal
    if (tok->kind == INTEGER_LITERAL) {
        int r = _scratchManager.alloc();
        _outputFile << "\tmov " << _scratchManager.getName(r)
                    << ", " << tok->val << "\n";
        node->SetRegister(r);
    }
    // float literal
    else if (tok->kind == FLOAT_LITERAL) {
        int r = _scratchManager.allocFloat();
        _outputFile << "\tmovsd " << _scratchManager.getName(r)
                    << ", FP8(" << tok->val << ")\n";
        node->SetRegister(r);
    }
    // simple variable load
    else if (tok->kind == IDENTIFIER && children.size() == 1) {
        int r = _scratchManager.alloc();
        loadMem(getVarAddr(tok->val), r);
        node->SetRegister(r);
    }
    // parenthesized expression: ( Expr )
    else if (tok->kind == OPEN_PAREN && children.size() == 3) {
        exprCodeGen(children[1]);
        node->SetRegister(children[1]->GetRegister());
    }
    // function call: IDENTIFIER OPEN_PAREN ExprList CLOSED_PAREN
    else if (isFuncCall(node)) {
        callExprCodeGen(node);
    }
    
}


void CodeGenarator::callExprCodeGen(NonTerminalNode *node)
{
    string funcName = ((TerminalNode *)node->GetChildren()[0])->getToken()->val;
    vector<NonTerminalNode *> args = getFunctionCallArgsNodes((NonTerminalNode *)node->GetChildren()[2]);

    pushArgs(args);

    _outputFile << "\tcall " << _lableManager.getFunctionLable(funcName) << "\n";

    valType funcRetType = getCurrFunctionEntry()->getReturnType();
    int reg;

    if (funcRetType.type == FLOAT)
    {
        reg = _scratchManager.allocFloat();
        _outputFile << "\tmovsd " << _scratchManager.getName(reg) << ", xmm0\n";
    }
    else
    {
        reg = _scratchManager.alloc();
        _outputFile << "\tmov " << _scratchManager.getName(reg) << ", rax\n";
        node->SetRegister(reg);
    }

    node->SetRegister(reg);
}

void CodeGenarator::pushArgs(vector<NonTerminalNode *> args)
{
    for (int i = args.size() - 1; i >= 0; i--)
    {
        NonTerminalNode *arg = args[i];
        exprCodeGen(arg);
        push(arg->GetRegister());
        _scratchManager.free(arg->GetRegister());
    }
}
void CodeGenarator::incrementExprCodeGen(NonTerminalNode *node)
{
    auto kids = node->GetChildren();
    TerminalNode *opNode = ((TerminalNode *)kids[0])->getTerminalKind() != IDENTIFIER ? (TerminalNode *)kids[0] : (TerminalNode *)kids[1];
    TerminalNode *idNode = ((TerminalNode *)kids[0])->getTerminalKind() == IDENTIFIER ? (TerminalNode *)kids[0] : (TerminalNode *)kids[1];
    SyntaxKind op = opNode->getTerminalKind();

    string opCommand = (op == PLUS_PLUS) ? "inc" : "dec";
    bool isPost = ((TerminalNode *)kids[0])->getTerminalKind() == IDENTIFIER;

    tableEntry varEntry = _scopeStack.top()->getEntry(idNode->getToken()->val);
    int reg = _scratchManager.alloc();
    int tempReg = _scratchManager.alloc();
    loadMem(varEntry.addr, tempReg);

    if (isPost)
    {
        mov(_scratchManager.getName(reg), _scratchManager.getName(tempReg));
        _outputFile << "\t" << opCommand << " " << _scratchManager.getName(tempReg) << "\n";
    }
    else
    {
        _outputFile << "\t" << opCommand << " " << _scratchManager.getName(tempReg) << "\n";
        mov(_scratchManager.getName(reg), _scratchManager.getName(tempReg));
    }

    storeMem(varEntry.addr, tempReg);

    _scratchManager.free(tempReg);
    node->SetRegister(reg);
}

void CodeGenarator::addressExprCodeGen(NonTerminalNode *node)
{
    std::string var = ((TerminalNode *)node->GetChildren()[1])->getToken()->val;
    std::string addr = getVarAddr(var);
    int r = _scratchManager.alloc();
    _outputFile << "\tlea " << _scratchManager.getName(r) << ", " << addr << "\n";
    node->SetRegister(r);
}

void CodeGenarator::dereferenceExprCodeGen(NonTerminalNode *node)
{
    int reg = _scratchManager.alloc();
    TerminalNode *idNode = (TerminalNode *)node->GetChildren()[1];

    string idAddr = getVarAddr(idNode->getToken()->val);
    loadMemPtrValue(idAddr,reg);

    node->SetRegister(reg);
}

void CodeGenarator::castToFloat(int intReg, int xmmReg)
{
    _outputFile << "\tcvtsi2ss " << _scratchManager.getName(xmmReg) << ", " << _scratchManager.getName(intReg) << "\n";
}

int CodeGenarator::assignStackOffset(scope *root)
{
    int bytes = layoutLocals(root, 0) + 8; // add rbp
    if (bytes & 0xF)
        bytes = (bytes + 15) & ~0xF; // keep 16‑byte align
    return bytes;
}

void CodeGenarator::pushAllCodeGen() {}
void CodeGenarator::popAllCodeGen() {}

int CodeGenarator::sizeOfType(const valType &t) const
{
    int base = 8;
    if (t.type == CHAR)
        base = 1;

    return base * t.size; // arrays: len × elem
}

string CodeGenarator::nameOfType(const valType &t) const
{
    string res = "QWORD";

    if (t.type == CHAR)
        res = "BYTE";

    return res;
}

int CodeGenarator::layoutLocals(scope *s, int offsetSoFar)
{
    for (auto &e : s->getEntries())
    {
        int sizeInStack = sizeOfType(e.type);
        offsetSoFar += sizeInStack;
        e.addr = nameOfType(e.type) + " ptr [rbp - " + to_string(offsetSoFar) + "]";
        e.offset = offsetSoFar;
    }
    for (scope *inner : s->getInnerScopes())
        offsetSoFar = layoutLocals(inner, offsetSoFar);
    return offsetSoFar;
}

void CodeGenarator::loadFunctionVariables(functionEntry *func)
{
    const vector<valType> &params = func->getParamTypes();
    int startOfParams = 16;
    int offset = 0;
    int reg;

    valType currParam;
    stringstream dstName;
    stringstream srcName;

    for (size_t i = 0; i < params.size(); i++)
    {
        currParam = params[i];
        reg = _scratchManager.alloc();

        srcName << nameOfType(currParam) << " PTR [rbp+" << startOfParams + offset << "]";
        dstName << nameOfType(currParam) << " PTR [rbp-" << offset + 8 << "]";

        if (currParam.type == FLOAT)
            reg = _scratchManager.allocFloat();

        loadFunctionVar(srcName.str(), dstName.str(), reg);

        offset += SIZE_OF_STACK_VAR;

        _scratchManager.free(reg);

        // clear the string streams
        srcName.str("");
        srcName.clear();
        dstName.str("");
        dstName.clear();
    }
}

void CodeGenarator::loadFunctionVar(string srcAddr, string dstAddr, int reg)
{
    loadMem(srcAddr, reg);
    storeMem(dstAddr, reg);
}

void CodeGenarator::push(int reg)
{
    if (_scratchManager.isFloat(reg))
    {
        _outputFile << "\tsub rsp, 8\n";
        _outputFile << "\tmovsd QWORD PTR [rsp], " << _scratchManager.getName(reg) << "\n";
    }
    else
    {
        _outputFile << "\tpush " << _scratchManager.getName(reg) << "\n";
    }
}

void CodeGenarator::mov(string leftReg, string rightReg)
{
    string movCommand = "mov ";
    if (leftReg.find("xmm") != string::npos)
        movCommand = "movsd ";

    _outputFile << "\t" << movCommand << leftReg << ", " << rightReg << "\n";
}

void CodeGenarator::loadMemPtrValue(string srcAddr, int reg)
{
    string movCommand = "mov ";
    string regName = _scratchManager.getName(reg);


    if (srcAddr.find("BYTE") != string::npos)
        regName = _scratchManager.getLowerByteName(reg);

    
    _outputFile << "\t" << "mov " << regName << ", " << srcAddr << "\n";
    _outputFile << "\t" << "mov " << regName << ", [" << regName << "]\n";  
}

void CodeGenarator::loadMem(string srcAddr, int reg)
{
    string movCommand = "mov ";

    if (_scratchManager.isFloat(reg))
        movCommand = "movsd ";

    if (srcAddr.find("BYTE") != string::npos)
        movCommand = "movzx ";

    _outputFile << "\t" << movCommand << _scratchManager.getName(reg) << ", " << srcAddr << "\n";
}

void CodeGenarator::storeMemPtrValue(string srcAddr, int reg)
{
    string movCommand = "mov ";
    string regName = _scratchManager.getName(reg);

    if (_scratchManager.isFloat(reg))
        movCommand = "movsd ";

    if (srcAddr.find("BYTE") != string::npos)
        regName = _scratchManager.getLowerByteName(reg);

        cout << "srcAddr: " << srcAddr << endl;
    int tempReg = _scratchManager.alloc();
    loadMem(srcAddr, tempReg);

    string targetAddr = "QWORD PTR [" + _scratchManager.getName(tempReg) + "]";

    storeMem(targetAddr, reg);
    _scratchManager.free(tempReg);
}
void CodeGenarator::storeMem(string srcAddr, int reg)
{
    string movCommand = "mov ";
    string regName = _scratchManager.getName(reg);

    if (_scratchManager.isFloat(reg))
        movCommand = "movsd ";

    if (srcAddr.find("BYTE") != string::npos)
        regName = _scratchManager.getLowerByteName(reg);

    _outputFile << "\t" << movCommand << srcAddr << ", " << regName << "\n";
}

string CodeGenarator::getVarAddr(const string &name) const
{
    scope *it = _scopeStack.top();
    string res = "";
    while (it)
    {
        for (const auto &e : it->getEntries())
            if (e.name == name && !e.addr.empty())
                res = e.addr;
        it = it->getParentScope();
    }

    return res;
}

void CodeGenarator::printIntFuncCodeGen()
{
    _outputFile << "function_printInt:\n";
    _outputFile << "\tpush rbp\n";
    _outputFile << "\tmov rbp, rsp\n";
    _outputFile << "\tsub rsp, 16\n"; // stack space for alignment

    _outputFile << "\tsub rsp, 32\n"; // shadow space (Windows x64 ABI)

    _outputFile << "\tmov rdx, QWORD PTR [rbp+16]\n"; // parameter -> rdx
    _outputFile << "\tlea rcx, format_int\n";         // format string -> rcx
    _outputFile << "\tcall printf\n";

    _outputFile << "\tadd rsp, 32\n";
    _outputFile << "\tmov eax, 0\n";
    _outputFile << "\tmov rsp, rbp\n";
    _outputFile << "\tpop rbp\n";
    _outputFile << "\tret\n";
}

void CodeGenarator::printFloatFuncCodeGen()
{
    _outputFile << "function_printFloat:\n";
    _outputFile << "\tpush rbp\n";
    _outputFile << "\tmov rbp, rsp\n";

    _outputFile << "\tsub rsp, 32\n"; // Allocate shadow space for Windows x64 ABI

    _outputFile << "\tmovsd xmm1, QWORD PTR [rbp+16]\n"; // Move float parameter into xmm1
    _outputFile << "\tlea rcx, format_float\n";          // Load address of format string into rcx
    _outputFile << "\tcall printf\n";

    _outputFile << "\tadd rsp, 32\n";
    _outputFile << "\tmov eax, 0\n";
    _outputFile << "\tmov rsp, rbp\n";
    _outputFile << "\tpop rbp\n";
    _outputFile << "\tret\n";
}

void CodeGenarator::floatMacroCodeGen()
{
    _outputFile << "; Floating-point constant macros\n";

    // 64-bit double macro
    _outputFile << "FP8 MACRO value\n";
    _outputFile << "    LOCAL vname\n";
    _outputFile << "    .const\n";
    _outputFile << "    align 8\n";
    _outputFile << "    vname REAL8 value\n";
    _outputFile << "    .code\n";
    _outputFile << "    EXITM <vname>\n";
    _outputFile << "ENDM\n\n";
}
