#include "codeGen.hpp"

CodeGenarator::CodeGenarator(string outputFile, ASTNode *root, SymbolTable *symbolTable)
    : _outputFile(outputFile), _root(root), _functions(symbolTable->getFunctions()), _currFunctionIndex(0) {}

void CodeGenarator::genCode()
{
    _outputFile << ".data\n";
    _outputFile << "\n.code\n";
    _outputFile << "extern ExitProcess : proc\n";

    vector<NonTerminalNode *> funcDeclNodes = getFunctionDeclNodes((NonTerminalNode *)_root);
    for (int i = 0; i < funcDeclNodes.size(); i++)
    {
        _currFunctionIndex++;
        funcCodeGen(funcDeclNodes[i]);
    }

    _outputFile << "\nmain:\n";
    _outputFile << "\tcall function_main\n";
    _outputFile << "\tmov ecx, eax\n";
    _outputFile << "\tcall ExitProcess\n";
    _outputFile << "END main\n";
    _outputFile.close();
}

void CodeGenarator::funcCodeGen(NonTerminalNode *node)
{
    _scopeStack.push(getCurrFunctionEntry()->getInnerScope());
    string funcName = getCurrFunctionEntry()->getName();
    _outputFile << "\n"
                << _lableManager.getFunctionLable(funcName) << "\n";
    _outputFile << "\tpush rbp\n";
    _outputFile << "\tmov rbp, rsp\n";
    int offset = assignStackOffset(getCurrFunctionEntry()->getInnerScope());
    _outputFile << "\tsub rsp, " << offset << "\n";
    loadFunctionVariables(getCurrFunctionEntry());
    vector<NonTerminalNode *> stmtNodes = getStmtNodes((NonTerminalNode *)node->GetChildren()[8]);
    for (auto stmt : stmtNodes)
    {
        stmtCodeGen(stmt);
    }

    _outputFile << _lableManager.getFunctionEpilogueLable(funcName) << "\n";
    _outputFile << "\tmov rsp, rbp\n";
    _outputFile << "\tpop rbp\n";
    _outputFile << "\tret\n";
    _scopeStack.pop();
}

void CodeGenarator::stmtCodeGen(NonTerminalNode *node)
{
    simpleStmtCodeGen((NonTerminalNode *)node->GetChildren()[0]);
}

void CodeGenarator::simpleStmtCodeGen(NonTerminalNode *node)
{
    if (isReturnStatement(node))
    {
        ASTNode *exprOptNode = node->GetChildren()[1];
        if (!exprOptNode->GetChildren().empty())
        {
            exprOptCodeGen((NonTerminalNode *)exprOptNode);
            _outputFile << "\tmov rax, " << _scratchManager.getName(exprOptNode->GetRegister()) << "\n";
            _scratchManager.free(exprOptNode->GetRegister());
        }
        cout << _currFunctionIndex;
        cout << _lableManager.getFunctionEpilogueLable(getCurrFunctionEntry()->getName());
        _outputFile << "\tjmp " << _lableManager.getFunctionEpilogueLable(getCurrFunctionEntry()->getName()) << "\n";
        _outputFile << endl;
    }
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

    NonTerminal childKind = ((NonTerminalNode *)child)->getNonTerminalKind();
    switch (childKind)
    {
    case LOGICAL_EXPR:
        logicalExprCodeGen((NonTerminalNode *)child);
        break;
    case INCREMENT_EXPR:
        incrementExprCodeGen((NonTerminalNode *)child);
        break;
    case ADDRESS_EXPR:
        addressExprCodeGen((NonTerminalNode *)child);
        break;
    case DEREFERENCE_EXPR:
        dereferenceExprCodeGen((NonTerminalNode *)child);
        break;
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
    cout << "<<UNARY_EXPR>> ";
    auto &children = node->GetChildren();
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
        _outputFile << "\tneg " << _scratchManager.getName(reg) << "\n";
    else if (op == BANG)
    {
        _outputFile << "\tcmp " << _scratchManager.getName(reg) << ", 0\n";
        _outputFile << "\tsete al\n";
        _outputFile << "\tmovzx " << _scratchManager.getName(reg) << ", al\n";
    }
}
void CodeGenarator::primaryExprCodeGen(NonTerminalNode *node)
{
    auto &children = node->GetChildren();
    ASTNode *first = children[0];

    if (first->GetType() == TERMINAL)
    {
        SyntaxToken *tok = ((TerminalNode *)first)->getToken();

        if (tok->kind == INTEGER_LITERAL)
        {
            int r = _scratchManager.alloc();
            _outputFile << "\tmov " << _scratchManager.getName(r)
                        << ", " << tok->val << "\n";
            node->SetRegister(r);
        }
        else if (tok->kind == IDENTIFIER && children.size() == 1)
        {
            int r = _scratchManager.alloc();
            loadMem(_scopeStack.top()->getEntry(tok->val).addr, r);
            node->SetRegister(r);
        }
        else if (tok->kind == IDENTIFIER && children.size() == 4)
        {
            callExprCodeGen(node);
        }
        else if (tok->kind == OPEN_PAREN)
        {
            exprCodeGen(children[1]);
            node->SetRegister(children[1]->GetRegister());
        }
    }
}

void CodeGenarator::callExprCodeGen(NonTerminalNode *node)
{
    string funcName = ((TerminalNode *)node->GetChildren()[0])->getToken()->val;
    _outputFile << "\tcall " << funcName << "\n";
    int reg = _scratchManager.alloc();
    _outputFile << "\tmov " << _scratchManager.getName(reg) << ", rax\n";
    node->SetRegister(reg);
}

void CodeGenarator::incrementExprCodeGen(NonTerminalNode *node)
{
    auto kids = node->GetChildren();
    TerminalNode *firstChild = ((TerminalNode *)kids[0]);
    TerminalNode *secondChild = ((TerminalNode *)kids[1]);
    SyntaxKind op = firstChild->getTerminalKind() != IDENTIFIER ? firstChild->getTerminalKind() : secondChild->getTerminalKind();

    string opCommand = (op == PLUS_PLUS) ? "inc" : "dec";

    tableEntry varEntry;
    int reg = _scratchManager.alloc();

    bool isPre = firstChild->getTerminalKind() != IDENTIFIER;

    int tempReg = _scratchManager.alloc();
    movCommendCodeGen(tempReg, reg);
    _outputFile << "\t" << opCommand << " " << _scratchManager.getName(tempReg) << "\n";
    
    if (isPre)
    {
        varEntry = _scopeStack.top()->getEntry(secondChild->getToken()->val);
        
        _outputFile << "\t" << opCommand << " " << varEntry.addr << "\n";
        loadMem(varEntry.addr, reg);
    }
    else
    {
        varEntry = _scopeStack.top()->getEntry(firstChild->getToken()->val);

        loadMem(varEntry.addr, reg);
        _outputFile << "\t" << opCommand << " " << varEntry.addr << "\n";

    }

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
    NonTerminalNode *inner = (NonTerminalNode *)node->GetChildren()[1];
    exprCodeGen(inner);
    int addrReg = inner->GetRegister();

    int reg = _scratchManager.alloc();
    _outputFile << "\tmov " << _scratchManager.getName(reg) << ", [" << _scratchManager.getName(addrReg) << "]\n";

    _scratchManager.free(addrReg);
    node->SetRegister(reg);
}

void CodeGenarator::castCharToInt(int charReg, int intReg)
{
    // Sign-extend 8-bit to 32-bit
    _outputFile << "\tmovsxd " << _scratchManager.getName(intReg) << ", " << _scratchManager.getName(charReg) << "\n"; // signed cast
}

void CodeGenarator::castIntToFloat(int intReg, int xmmReg)
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

        srcName << nameOfType(currParam) << " ptr [rbp+" << startOfParams + offset << "]";
        dstName << nameOfType(currParam) << " ptr [rbp-" << offset + 8 << "]";

        if (currParam.type == FLOAT)
            reg = _scratchManager.allocFloat();

        loadFunctionVar(srcName.str(), dstName.str(), reg);

        offset += sizeOfType(currParam);

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

void CodeGenarator::movCommendCodeGen(int leftReg, int rightReg)
{
    string movCommand = "mov ";
    if (_scratchManager.isFloat(leftReg))
        movCommand = "movsd ";

    _outputFile << "\t" << movCommand << _scratchManager.getName(leftReg) << ", " << _scratchManager.getName(rightReg) << "\n";
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
