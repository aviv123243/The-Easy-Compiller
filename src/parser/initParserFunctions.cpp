#include "parser.hpp"
#include "productionRule/productionRule.hpp"
#include "../token/token.hpp"

void Parser::initProductionRules()
{
    productionRule rule;

    // Rule 0: Start -> program EOF
    rule.setLeft(START);
    rule.addSymbol(PROGRAM).addSymbol(END_OF_FILE);
    addProductionRule(rule);
    rule.reset();

    // Rule 1: Program -> FunctionDecl Program
    rule.setLeft(PROGRAM);
    rule.addSymbol(FUNCTION_DECL).addSymbol(PROGRAM);
    addProductionRule(rule);
    rule.reset();

    // Rule 2: Program -> /* empty */
    rule.setLeft(PROGRAM);
    rule.addSymbol(); // empty
    addProductionRule(rule);
    rule.reset();

    // Rule 3: FunctionDecl -> KEYWORD_FN IDENTIFIER OPEN_PAREN ParamList CLOSED_PAREN RIGHT_ARROW Type OPEN_CURLY StmtList CLOSED_CURLY
    rule.setLeft(FUNCTION_DECL);
    rule.addSymbol(KEYWORD_FN)
        .addSymbol(IDENTIFIER)
        .addSymbol(OPEN_PAREN)
        .addSymbol(PARAM_LIST)
        .addSymbol(CLOSED_PAREN)
        .addSymbol(RIGHT_ARROW)
        .addSymbol(TYPE)
        .addSymbol(OPEN_CURLY)
        .addSymbol(STMT_LIST)
        .addSymbol(CLOSED_CURLY);
    addProductionRule(rule);
    rule.reset();

    // Rule 4: ParamList -> Param ParamTail
    rule.setLeft(PARAM_LIST);
    rule.addSymbol(PARAM).addSymbol(PARAM_TAIL);
    addProductionRule(rule);
    rule.reset();

    // Rule 5: ParamList -> /* empty */
    rule.setLeft(PARAM_LIST);
    rule.addSymbol(); // empty
    addProductionRule(rule);
    rule.reset();

    // Rule 6: ParamTail -> COMMA Param ParamTail
    rule.setLeft(PARAM_TAIL);
    rule.addSymbol(COMMA).addSymbol(PARAM).addSymbol(PARAM_TAIL);
    addProductionRule(rule);
    rule.reset();

    // Rule 7: ParamTail -> /* empty */
    rule.setLeft(PARAM_TAIL);
    rule.addSymbol(); // empty
    addProductionRule(rule);
    rule.reset();

    // Rule 8: Param -> Type IDENTIFIER
    rule.setLeft(PARAM);
    rule.addSymbol(TYPE).addSymbol(IDENTIFIER);
    addProductionRule(rule);
    rule.reset();

    // Rule 9: Type -> BaseType TypeTail
    rule.setLeft(TYPE);
    rule.addSymbol(BASE_TYPE).addSymbol(TYPE_TAIL);
    addProductionRule(rule);
    rule.reset();

    // Rule 10: BaseType -> KEYWORD_INT
    rule.setLeft(BASE_TYPE);
    rule.addSymbol(KEYWORD_INT);
    addProductionRule(rule);
    rule.reset();

    // Rule 11: BaseType -> KEYWORD_FLOAT
    rule.setLeft(BASE_TYPE);
    rule.addSymbol(KEYWORD_FLOAT);
    addProductionRule(rule);
    rule.reset();

    // Rule 12: BaseType -> KEYWORD_CHAR
    rule.setLeft(BASE_TYPE);
    rule.addSymbol(KEYWORD_CHAR);
    addProductionRule(rule);
    rule.reset();

    // Rule 13: TypeTail -> OPEN_BRACKET INTEGER_LITERAL CLOSED_BRACKET TypeTail
    rule.setLeft(TYPE_TAIL);
    rule.addSymbol(OPEN_BRACKET)
        .addSymbol(INTEGER_LITERAL)
        .addSymbol(CLOSED_BRACKET)
        .addSymbol(TYPE_TAIL);
    addProductionRule(rule);
    rule.reset();

    // Rule 14: TypeTail -> STAR TypeTail
    rule.setLeft(TYPE_TAIL);
    rule.addSymbol(STAR).addSymbol(TYPE_TAIL);
    addProductionRule(rule);
    rule.reset();

    // Rule 15: TypeTail -> /* empty */
    rule.setLeft(TYPE_TAIL);
    rule.addSymbol(); // empty
    addProductionRule(rule);
    rule.reset();

    // Rule 16: StmtList -> Stmt StmtList
    rule.setLeft(STMT_LIST);
    rule.addSymbol(STMT).addSymbol(STMT_LIST);
    addProductionRule(rule);
    rule.reset();

    // Rule 17: StmtList -> /* empty */
    rule.setLeft(STMT_LIST);
    rule.addSymbol(); // empty
    addProductionRule(rule);
    rule.reset();

    // Rule 18: Stmt -> VarDeclStmt
    rule.setLeft(STMT);
    rule.addSymbol(VAR_DECL_STMT);
    addProductionRule(rule);
    rule.reset();

    // Rule 19: Stmt -> AssignStmt
    rule.setLeft(STMT);
    rule.addSymbol(ASSIGN_STMT);
    addProductionRule(rule);
    rule.reset();

    // Rule 20: Stmt -> IfStmt
    rule.setLeft(STMT);
    rule.addSymbol(IF_STMT);
    addProductionRule(rule);
    rule.reset();

    // Rule 21: Stmt -> WhileStmt
    rule.setLeft(STMT);
    rule.addSymbol(WHILE_STMT);
    addProductionRule(rule);
    rule.reset();

    // Rule 22: Stmt -> ForStmt
    rule.setLeft(STMT);
    rule.addSymbol(FOR_STMT);
    addProductionRule(rule);
    rule.reset();

    // Rule 23: Stmt -> ReturnStmt
    rule.setLeft(STMT);
    rule.addSymbol(RETURN_STMT);
    addProductionRule(rule);
    rule.reset();

    // Rule 24: Stmt -> ExprStmt
    rule.setLeft(STMT);
    rule.addSymbol(EXPR_STMT);
    addProductionRule(rule);
    rule.reset();

    // Rule 25: Body -> OPEN_CURLY StmtList CLOSED_CURLY
    rule.setLeft(BODY);
    rule.addSymbol(OPEN_CURLY).addSymbol(STMT_LIST).addSymbol(CLOSED_CURLY);
    addProductionRule(rule);
    rule.reset();

    // Rule 26: Body -> Stmt
    rule.setLeft(BODY);
    rule.addSymbol(STMT);
    addProductionRule(rule);
    rule.reset();

    // Rule 27: VarDeclStmt -> VarDeclExpr SEMICOLON
    rule.setLeft(VAR_DECL_STMT);
    rule.addSymbol(VAR_DECL_EXPR).addSymbol(SEMICOLON);
    addProductionRule(rule);
    rule.reset();

    // Rule 28: VarDeclExpr -> Type IDENTIFIER InitOpt
    rule.setLeft(VAR_DECL_EXPR);
    rule.addSymbol(TYPE).addSymbol(IDENTIFIER).addSymbol(INIT_OPT);
    addProductionRule(rule);
    rule.reset();

    // Rule 29: InitOpt -> EQUALS Expr
    rule.setLeft(INIT_OPT);
    rule.addSymbol(EQUALS).addSymbol(EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 30: InitOpt -> /* empty */
    rule.setLeft(INIT_OPT);
    rule.addSymbol(); // empty
    addProductionRule(rule);
    rule.reset();

    // Rule 31: AssignStmt -> AssignExpr SEMICOLON
    rule.setLeft(ASSIGN_STMT);
    rule.addSymbol(ASSIGN_EXPR).addSymbol(SEMICOLON);
    addProductionRule(rule);
    rule.reset();

    // Rule 32: AssignExpr -> AssignTarget AssignOp Expr
    rule.setLeft(ASSIGN_EXPR);
    rule.addSymbol(ASSIGN_TARGET).addSymbol(ASSIGN_OP).addSymbol(EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 33: AssignTarget -> IDENTIFIER
    rule.setLeft(ASSIGN_TARGET);
    rule.addSymbol(IDENTIFIER);
    addProductionRule(rule);
    rule.reset();

    // Rule 34: AssignTarget -> IDENTIFIER OPEN_BRACKET Expr CLOSED_BRACKET
    rule.setLeft(ASSIGN_TARGET);
    rule.addSymbol(IDENTIFIER).addSymbol(OPEN_BRACKET).addSymbol(EXPR).addSymbol(CLOSED_BRACKET);
    addProductionRule(rule);
    rule.reset();

    // Rule 35: AssignTarget -> STAR IDENTIFIER
    rule.setLeft(ASSIGN_TARGET);
    rule.addSymbol(STAR).addSymbol(IDENTIFIER);
    addProductionRule(rule);
    rule.reset();

    // Rule 36: AssignOp -> EQUALS
    rule.setLeft(ASSIGN_OP);
    rule.addSymbol(EQUALS);
    addProductionRule(rule);
    rule.reset();

    // Rule 37: AssignOp -> PLUS_EQUALS
    rule.setLeft(ASSIGN_OP);
    rule.addSymbol(PLUS_EQUALS);
    addProductionRule(rule);
    rule.reset();

    // Rule 38: AssignOp -> MINUS_EQUALS
    rule.setLeft(ASSIGN_OP);
    rule.addSymbol(MINUS_EQUALS);
    addProductionRule(rule);
    rule.reset();

    // Rule 39: AssignOp -> SLASH_EQUALS
    rule.setLeft(ASSIGN_OP);
    rule.addSymbol(SLASH_EQUALS);
    addProductionRule(rule);
    rule.reset();

    // Rule 40: AssignOp -> STAR_EQUALS
    rule.setLeft(ASSIGN_OP);
    rule.addSymbol(STAR_EQUALS);
    addProductionRule(rule);
    rule.reset();

    // Rule 41: AssignOp -> AMPERSAND_EQUALS
    rule.setLeft(ASSIGN_OP);
    rule.addSymbol(AMPERSAND_EQUALS);
    addProductionRule(rule);
    rule.reset();

    // Rule 42: AssignOp -> PIPE_EQUALS
    rule.setLeft(ASSIGN_OP);
    rule.addSymbol(PIPE_EQUALS);
    addProductionRule(rule);
    rule.reset();

    // Rule 43: AssignOp -> CARET_EQUALS
    rule.setLeft(ASSIGN_OP);
    rule.addSymbol(CARET_EQUALS);
    addProductionRule(rule);
    rule.reset();

    // Rule 44: AssignOp -> TILDE_EQUALS
    rule.setLeft(ASSIGN_OP);
    rule.addSymbol(TILDE_EQUALS);
    addProductionRule(rule);
    rule.reset();

    // Rule 45: IfStmt -> KEYWORD_IF OPEN_PAREN Expr CLOSED_PAREN Body
    rule.setLeft(IF_STMT);
    rule.addSymbol(KEYWORD_IF).addSymbol(OPEN_PAREN).addSymbol(EXPR).addSymbol(CLOSED_PAREN).addSymbol(BODY);
    addProductionRule(rule);
    rule.reset();

    // Rule 46: IfStmt -> KEYWORD_IF OPEN_PAREN Expr CLOSED_PAREN Body KEYWORD_ELSE Body
    rule.setLeft(IF_STMT);
    rule.addSymbol(KEYWORD_IF)
        .addSymbol(OPEN_PAREN)
        .addSymbol(EXPR)
        .addSymbol(CLOSED_PAREN)
        .addSymbol(BODY)
        .addSymbol(KEYWORD_ELSE)
        .addSymbol(BODY);
    addProductionRule(rule);
    rule.reset();

    // Rule 47: WhileStmt -> KEYWORD_WHILE OPEN_PAREN Expr CLOSED_PAREN Body
    rule.setLeft(WHILE_STMT);
    rule.addSymbol(KEYWORD_WHILE).addSymbol(OPEN_PAREN).addSymbol(EXPR).addSymbol(CLOSED_PAREN).addSymbol(BODY);
    addProductionRule(rule);
    rule.reset();

    // Rule 48: ForStmt -> KEYWORD_FOR OPEN_PAREN ForInit SEMICOLON ExprOpt SEMICOLON ForUpdate CLOSED_PAREN Body
    rule.setLeft(FOR_STMT);
    rule.addSymbol(KEYWORD_FOR)
        .addSymbol(OPEN_PAREN)
        .addSymbol(FOR_INIT)
        .addSymbol(SEMICOLON)
        .addSymbol(EXPR_OPT)
        .addSymbol(SEMICOLON)
        .addSymbol(FOR_UPDATE)
        .addSymbol(CLOSED_PAREN)
        .addSymbol(BODY);
    addProductionRule(rule);
    rule.reset();

    // Rule 49: ForInit -> VarDeclExpr
    rule.setLeft(FOR_INIT);
    rule.addSymbol(VAR_DECL_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 50: ForInit -> AssignExpr
    rule.setLeft(FOR_INIT);
    rule.addSymbol(ASSIGN_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 51: ForInit -> /* empty */
    rule.setLeft(FOR_INIT);
    rule.addSymbol(); // empty
    addProductionRule(rule);
    rule.reset();

    // Rule 52: ExprOpt -> Expr
    rule.setLeft(EXPR_OPT);
    rule.addSymbol(EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 53: ExprOpt -> /* empty */
    rule.setLeft(EXPR_OPT);
    rule.addSymbol(); // empty
    addProductionRule(rule);
    rule.reset();

    // Rule 54: ForUpdate -> AssignExpr
    rule.setLeft(FOR_UPDATE);
    rule.addSymbol(ASSIGN_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 55: ForUpdate -> /* empty */
    rule.setLeft(FOR_UPDATE);
    rule.addSymbol(); // empty
    addProductionRule(rule);
    rule.reset();

    // Rule 56: ReturnStmt -> KEYWORD_RET ExprOpt SEMICOLON
    rule.setLeft(RETURN_STMT);
    rule.addSymbol(KEYWORD_RET).addSymbol(EXPR_OPT).addSymbol(SEMICOLON);
    addProductionRule(rule);
    rule.reset();

    // Rule 57: ExprStmt -> Expr SEMICOLON
    rule.setLeft(EXPR_STMT);
    rule.addSymbol(EXPR).addSymbol(SEMICOLON);
    addProductionRule(rule);
    rule.reset();

    // Rule 58: ExprList -> Expr ExprTail
    rule.setLeft(EXPR_LIST);
    rule.addSymbol(EXPR).addSymbol(EXPR_TAIL);
    addProductionRule(rule);
    rule.reset();

    // Rule 59: ExprList -> /* empty */
    rule.setLeft(EXPR_LIST);
    rule.addSymbol(); // empty
    addProductionRule(rule);
    rule.reset();

    // Rule 60: ExprTail -> COMMA Expr ExprTail
    rule.setLeft(EXPR_TAIL);
    rule.addSymbol(COMMA).addSymbol(EXPR).addSymbol(EXPR_TAIL);
    addProductionRule(rule);
    rule.reset();

    // Rule 61: ExprTail -> /* empty */
    rule.setLeft(EXPR_TAIL);
    rule.addSymbol(); // empty
    addProductionRule(rule);
    rule.reset();

    // Rule 62: Expr -> UnaryExpr RelOpTail
    rule.setLeft(EXPR);
    rule.addSymbol(UNARY_EXPR).addSymbol(REL_OP_TAIL);
    addProductionRule(rule);
    rule.reset();

    // Rule 63: RelOpTail -> RelOp UnaryExpr RelOpTail
    rule.setLeft(REL_OP_TAIL);
    rule.addSymbol(REL_OP).addSymbol(UNARY_EXPR).addSymbol(REL_OP_TAIL);
    addProductionRule(rule);
    rule.reset();

    // Rule 64: RelOpTail -> /* empty */
    rule.setLeft(REL_OP_TAIL);
    rule.addSymbol(); // empty
    addProductionRule(rule);
    rule.reset();

    // Rule 65: RelOp -> LESS_THAN
    rule.setLeft(REL_OP);
    rule.addSymbol(LESS_THAN);
    addProductionRule(rule);
    rule.reset();

    // Rule 66: RelOp -> GREATER_THAN
    rule.setLeft(REL_OP);
    rule.addSymbol(GREATER_THAN);
    addProductionRule(rule);
    rule.reset();

    // Rule 67: RelOp -> LESS_THAN_EQUALS
    rule.setLeft(REL_OP);
    rule.addSymbol(LESS_THAN_EQUALS);
    addProductionRule(rule);
    rule.reset();

    // Rule 68: RelOp -> GREATER_THAN_EQUALS
    rule.setLeft(REL_OP);
    rule.addSymbol(GREATER_THAN_EQUALS);
    addProductionRule(rule);
    rule.reset();

    // Rule 69: RelOp -> EQUALS_EQUALS
    rule.setLeft(REL_OP);
    rule.addSymbol(EQUALS_EQUALS);
    addProductionRule(rule);
    rule.reset();

    // Rule 70: RelOp -> BANG_EQUALS
    rule.setLeft(REL_OP);
    rule.addSymbol(BANG_EQUALS);
    addProductionRule(rule);
    rule.reset();

    // Rule 71: UnaryExpr -> UnaryOp UnaryExpr
    rule.setLeft(UNARY_EXPR);
    rule.addSymbol(UNARY_OP).addSymbol(UNARY_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 72: UnaryExpr -> SimpleExpr
    rule.setLeft(UNARY_EXPR);
    rule.addSymbol(SIMPLE_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 73: UnaryOp -> MINUS
    rule.setLeft(UNARY_OP);
    rule.addSymbol(MINUS);
    addProductionRule(rule);
    rule.reset();

    // Rule 74: UnaryOp -> BANG
    rule.setLeft(UNARY_OP);
    rule.addSymbol(BANG);
    addProductionRule(rule);
    rule.reset();

    // Rule 75: SimpleExpr -> Term AddOpTail
    rule.setLeft(SIMPLE_EXPR);
    rule.addSymbol(TERM).addSymbol(ADD_OP_TAIL);
    addProductionRule(rule);
    rule.reset();

    // Rule 76: AddOpTail -> AddOp Term AddOpTail
    rule.setLeft(ADD_OP_TAIL);
    rule.addSymbol(ADD_OP).addSymbol(TERM).addSymbol(ADD_OP_TAIL);
    addProductionRule(rule);
    rule.reset();

    // Rule 77: AddOpTail -> /* empty */
    rule.setLeft(ADD_OP_TAIL);
    rule.addSymbol(); // empty
    addProductionRule(rule);
    rule.reset();

    // Rule 78: AddOp -> PLUS
    rule.setLeft(ADD_OP);
    rule.addSymbol(PLUS);
    addProductionRule(rule);
    rule.reset();

    // Rule 79: AddOp -> MINUS
    rule.setLeft(ADD_OP);
    rule.addSymbol(MINUS);
    addProductionRule(rule);
    rule.reset();

    // Rule 80: AddOp -> PIPE
    rule.setLeft(ADD_OP);
    rule.addSymbol(PIPE);
    addProductionRule(rule);
    rule.reset();

    // Rule 81: AddOp -> CARET
    rule.setLeft(ADD_OP);
    rule.addSymbol(CARET);
    addProductionRule(rule);
    rule.reset();

    // Rule 82: AddOp -> PIPE_PIPE
    rule.setLeft(ADD_OP);
    rule.addSymbol(PIPE_PIPE);
    addProductionRule(rule);
    rule.reset();

    // Rule 83: Term -> Factor MulOpTail
    rule.setLeft(TERM);
    rule.addSymbol(FACTOR).addSymbol(MUL_OP_TAIL);
    addProductionRule(rule);
    rule.reset();

    // Rule 84: MulOpTail -> MulOp Factor MulOpTail
    rule.setLeft(MUL_OP_TAIL);
    rule.addSymbol(MUL_OP).addSymbol(FACTOR).addSymbol(MUL_OP_TAIL);
    addProductionRule(rule);
    rule.reset();

    // Rule 85: MulOpTail -> /* empty */
    rule.setLeft(MUL_OP_TAIL);
    rule.addSymbol(); // empty
    addProductionRule(rule);
    rule.reset();

    // Rule 86: MulOp -> STAR
    rule.setLeft(MUL_OP);
    rule.addSymbol(STAR);
    addProductionRule(rule);
    rule.reset();

    // Rule 87: MulOp -> SLASH
    rule.setLeft(MUL_OP);
    rule.addSymbol(SLASH);
    addProductionRule(rule);
    rule.reset();

    // Rule 88: MulOp -> AMPERSAND
    rule.setLeft(MUL_OP);
    rule.addSymbol(AMPERSAND);
    addProductionRule(rule);
    rule.reset();

    // Rule 89: MulOp -> AMPERSAND_AMPERSAND
    rule.setLeft(MUL_OP);
    rule.addSymbol(AMPERSAND_AMPERSAND);
    addProductionRule(rule);
    rule.reset();

    // Rule 90: Factor -> OPEN_PAREN Expr CLOSED_PAREN
    rule.setLeft(FACTOR);
    rule.addSymbol(OPEN_PAREN).addSymbol(EXPR).addSymbol(CLOSED_PAREN);
    addProductionRule(rule);
    rule.reset();

    // Rule 91: Factor -> IDENTIFIER
    rule.setLeft(FACTOR);
    rule.addSymbol(IDENTIFIER);
    addProductionRule(rule);
    rule.reset();

    // Rule 92: Factor -> INTEGER_LITERAL
    rule.setLeft(FACTOR);
    rule.addSymbol(INTEGER_LITERAL);
    addProductionRule(rule);
    rule.reset();

    // Rule 93: Factor -> FLOAT_LITERAL
    rule.setLeft(FACTOR);
    rule.addSymbol(FLOAT_LITERAL);
    addProductionRule(rule);
    rule.reset();

    // Rule 94: Factor -> CHAR_LITERAL
    rule.setLeft(FACTOR);
    rule.addSymbol(CHAR_LITERAL);
    addProductionRule(rule);
    rule.reset();

    // Rule 95: Factor -> IDENTIFIER OPEN_PAREN ExprList CLOSED_PAREN
    rule.setLeft(FACTOR);
    rule.addSymbol(IDENTIFIER).addSymbol(OPEN_PAREN).addSymbol(EXPR_LIST).addSymbol(CLOSED_PAREN);
    addProductionRule(rule);
    rule.reset();
}

void Parser::fillTables()
{
    // State 0
    _actionTable.add(0, KEYWORD_FN, {SHIFT, 1});
    _actionTable.addDefault(0, {REDUCE, 2}); // Program -> /* empty */
    _gotoTable.add(0, PROGRAM, 2);
    _gotoTable.add(0, FUNCTION_DECL, 3);

    // State 1
    _actionTable.add(1, IDENTIFIER, {SHIFT, 4});

    // State 2
    _actionTable.add(2, END_OF_FILE, {SHIFT, 5}); // $end

    // State 3
    _actionTable.add(3, KEYWORD_FN, {SHIFT, 1});
    _actionTable.addDefault(3, {REDUCE, 2}); // Program -> /* empty */
    _gotoTable.add(3, PROGRAM, 6);
    _gotoTable.add(3, FUNCTION_DECL, 3);

    // State 4
    _actionTable.add(4, OPEN_PAREN, {SHIFT, 7});

    // State 5
    _actionTable.addDefault(5, {ACCEPT, 0}); // Accept state

    // State 6
    _actionTable.addDefault(6, {REDUCE, 1}); // Program -> FunctionDecl Program

    // State 7
    _actionTable.add(7, KEYWORD_INT, {SHIFT, 8});
    _actionTable.add(7, KEYWORD_FLOAT, {SHIFT, 9});
    _actionTable.add(7, KEYWORD_CHAR, {SHIFT, 10});
    _actionTable.addDefault(7, {REDUCE, 5}); // ParamList -> /* empty */
    _gotoTable.add(7, PARAM_LIST, 11);
    _gotoTable.add(7, PARAM, 12);
    _gotoTable.add(7, TYPE, 13);
    _gotoTable.add(7, BASE_TYPE, 14);

    // State 8
    _actionTable.addDefault(8, {REDUCE, 10}); // BaseType -> KEYWORD_INT

    // State 9
    _actionTable.addDefault(9, {REDUCE, 11}); // BaseType -> KEYWORD_FLOAT

    // State 10
    _actionTable.addDefault(10, {REDUCE, 12}); // BaseType -> KEYWORD_CHAR

    // State 11
    _actionTable.add(11, CLOSED_PAREN, {SHIFT, 15});

    // State 12
    _actionTable.add(12, COMMA, {SHIFT, 16});
    _actionTable.addDefault(12, {REDUCE, 7}); // ParamTail -> /* empty */
    _gotoTable.add(12, PARAM_TAIL, 17);

    // State 13
    _actionTable.add(13, IDENTIFIER, {SHIFT, 18});

    // State 14
    _actionTable.add(14, OPEN_BRACKET, {SHIFT, 19});
    _actionTable.add(14, STAR, {SHIFT, 20});
    _actionTable.addDefault(14, {REDUCE, 15}); // TypeTail -> /* empty */
    _gotoTable.add(14, TYPE_TAIL, 21);

    // State 15
    _actionTable.add(15, RIGHT_ARROW, {SHIFT, 22});

    // State 16
    _actionTable.add(16, KEYWORD_INT, {SHIFT, 8});
    _actionTable.add(16, KEYWORD_FLOAT, {SHIFT, 9});
    _actionTable.add(16, KEYWORD_CHAR, {SHIFT, 10});
    _gotoTable.add(16, PARAM, 23);
    _gotoTable.add(16, TYPE, 13);
    _gotoTable.add(16, BASE_TYPE, 14);

    // State 17
    _actionTable.addDefault(17, {REDUCE, 4}); // ParamList -> Param ParamTail

    // State 18
    _actionTable.addDefault(18, {REDUCE, 8}); // Param -> Type IDENTIFIER

    // State 19
    _actionTable.add(19, INTEGER_LITERAL, {SHIFT, 24});

    // State 20
    _actionTable.add(20, OPEN_BRACKET, {SHIFT, 19});
    _actionTable.add(20, STAR, {SHIFT, 20});
    _actionTable.addDefault(20, {REDUCE, 15}); // TypeTail -> /* empty */
    _gotoTable.add(20, TYPE_TAIL, 25);

    // State 21
    _actionTable.addDefault(21, {REDUCE, 9}); // Type -> BaseType TypeTail

    // State 22
    _actionTable.add(22, KEYWORD_INT, {SHIFT, 8});
    _actionTable.add(22, KEYWORD_FLOAT, {SHIFT, 9});
    _actionTable.add(22, KEYWORD_CHAR, {SHIFT, 10});
    _gotoTable.add(22, TYPE, 26);
    _gotoTable.add(22, BASE_TYPE, 14);

    // State 23
    _actionTable.add(23, COMMA, {SHIFT, 16});
    _actionTable.addDefault(23, {REDUCE, 7}); // ParamTail -> /* empty */
    _gotoTable.add(23, PARAM_TAIL, 27);

    // State 24
    _actionTable.add(24, CLOSED_BRACKET, {SHIFT, 28});

    // State 25
    _actionTable.addDefault(25, {REDUCE, 14}); // TypeTail -> STAR TypeTail

    // State 26
    _actionTable.add(26, OPEN_CURLY, {SHIFT, 29});

    // State 27
    _actionTable.addDefault(27, {REDUCE, 6}); // ParamTail -> COMMA Param ParamTail

    // State 28
    _actionTable.add(28, OPEN_BRACKET, {SHIFT, 19});
    _actionTable.add(28, STAR, {SHIFT, 20});
    _actionTable.addDefault(28, {REDUCE, 15}); // TypeTail -> /* empty */
    _gotoTable.add(28, TYPE_TAIL, 30);

    // State 29
    _actionTable.add(29, IDENTIFIER, {SHIFT, 31});
    _actionTable.add(29, OPEN_PAREN, {SHIFT, 32});
    _actionTable.add(29, KEYWORD_INT, {SHIFT, 8});
    _actionTable.add(29, KEYWORD_FLOAT, {SHIFT, 9});
    _actionTable.add(29, KEYWORD_CHAR, {SHIFT, 10});
    _actionTable.add(29, STAR, {SHIFT, 33});
    _actionTable.add(29, KEYWORD_IF, {SHIFT, 34});
    _actionTable.add(29, KEYWORD_WHILE, {SHIFT, 35});
    _actionTable.add(29, KEYWORD_FOR, {SHIFT, 36});
    _actionTable.add(29, KEYWORD_RET, {SHIFT, 37});
    _actionTable.add(29, MINUS, {SHIFT, 38});
    _actionTable.add(29, BANG, {SHIFT, 39});
    _actionTable.add(29, INTEGER_LITERAL, {SHIFT, 40});
    _actionTable.add(29, FLOAT_LITERAL, {SHIFT, 41});
    _actionTable.add(29, CHAR_LITERAL, {SHIFT, 42});
    _actionTable.addDefault(29, {REDUCE, 17}); // StmtList -> /* empty */
    _gotoTable.add(29, TYPE, 43);
    _gotoTable.add(29, BASE_TYPE, 14);
    _gotoTable.add(29, STMT_LIST, 44);
    _gotoTable.add(29, STMT, 45);
    _gotoTable.add(29, VAR_DECL_STMT, 46);
    _gotoTable.add(29, VAR_DECL_EXPR, 47);
    _gotoTable.add(29, ASSIGN_STMT, 48);
    _gotoTable.add(29, ASSIGN_EXPR, 49);
    _gotoTable.add(29, ASSIGN_TARGET, 50);
    _gotoTable.add(29, IF_STMT, 51);
    _gotoTable.add(29, WHILE_STMT, 52);
    _gotoTable.add(29, FOR_STMT, 53);
    _gotoTable.add(29, RETURN_STMT, 54);
    _gotoTable.add(29, EXPR_STMT, 55);
    _gotoTable.add(29, EXPR, 56);
    _gotoTable.add(29, UNARY_EXPR, 57);
    _gotoTable.add(29, UNARY_OP, 58);
    _gotoTable.add(29, SIMPLE_EXPR, 59);
    _gotoTable.add(29, TERM, 60);
    _gotoTable.add(29, FACTOR, 61);

    // State 30
    _actionTable.addDefault(30, {REDUCE, 13}); // TypeTail -> OPEN_BRACKET INTEGER_LITERAL CLOSED_BRACKET TypeTail

    // State 31
    _actionTable.add(31, OPEN_PAREN, {SHIFT, 62});
    _actionTable.add(31, OPEN_BRACKET, {SHIFT, 63});
    _actionTable.add(31, EQUALS, {REDUCE, 33});
    _actionTable.add(31, PLUS_EQUALS, {REDUCE, 33});
    _actionTable.add(31, MINUS_EQUALS, {REDUCE, 33});
    _actionTable.add(31, SLASH_EQUALS, {REDUCE, 33});
    _actionTable.add(31, STAR_EQUALS, {REDUCE, 33});
    _actionTable.add(31, AMPERSAND_EQUALS, {REDUCE, 33});
    _actionTable.add(31, PIPE_EQUALS, {REDUCE, 33});
    _actionTable.add(31, CARET_EQUALS, {REDUCE, 33});
    _actionTable.add(31, TILDE_EQUALS, {REDUCE, 33});
    _actionTable.addDefault(31, {REDUCE, 91}); // Factor -> IDENTIFIER

    // State 32
    _actionTable.add(32, IDENTIFIER, {SHIFT, 64});
    _actionTable.add(32, OPEN_PAREN, {SHIFT, 32});
    _actionTable.add(32, MINUS, {SHIFT, 38});
    _actionTable.add(32, BANG, {SHIFT, 39});
    _actionTable.add(32, INTEGER_LITERAL, {SHIFT, 40});
    _actionTable.add(32, FLOAT_LITERAL, {SHIFT, 41});
    _actionTable.add(32, CHAR_LITERAL, {SHIFT, 42});
    _gotoTable.add(32, EXPR, 65);
    _gotoTable.add(32, UNARY_EXPR, 57);
    _gotoTable.add(32, UNARY_OP, 58);
    _gotoTable.add(32, SIMPLE_EXPR, 59);
    _gotoTable.add(32, TERM, 60);
    _gotoTable.add(32, FACTOR, 61);

    // State 33
    _actionTable.add(33, IDENTIFIER, {SHIFT, 66});

    // State 34
    _actionTable.add(34, OPEN_PAREN, {SHIFT, 67});

    // State 35
    _actionTable.add(35, OPEN_PAREN, {SHIFT, 68});

    // State 36
    _actionTable.add(36, OPEN_PAREN, {SHIFT, 69});

    // State 37
    _actionTable.add(37, IDENTIFIER, {SHIFT, 64});
    _actionTable.add(37, OPEN_PAREN, {SHIFT, 32});
    _actionTable.add(37, MINUS, {SHIFT, 38});
    _actionTable.add(37, BANG, {SHIFT, 39});
    _actionTable.add(37, INTEGER_LITERAL, {SHIFT, 40});
    _actionTable.add(37, FLOAT_LITERAL, {SHIFT, 41});
    _actionTable.add(37, CHAR_LITERAL, {SHIFT, 42});
    _actionTable.addDefault(37, {REDUCE, 53}); // ExprOpt -> /* empty */
    _gotoTable.add(37, EXPR_OPT, 70);
    _gotoTable.add(37, EXPR, 71);
    _gotoTable.add(37, UNARY_EXPR, 57);
    _gotoTable.add(37, UNARY_OP, 58);
    _gotoTable.add(37, SIMPLE_EXPR, 59);
    _gotoTable.add(37, TERM, 60);
    _gotoTable.add(37, FACTOR, 61);

    // State 38
    _actionTable.addDefault(38, {REDUCE, 73}); // UnaryOp -> MINUS

    // State 39
    _actionTable.addDefault(39, {REDUCE, 74}); // UnaryOp -> BANG

    // State 40
    _actionTable.addDefault(40, {REDUCE, 92}); // Factor -> INTEGER_LITERAL

    // State 41
    _actionTable.addDefault(41, {REDUCE, 93}); // Factor -> FLOAT_LITERAL

    // State 42
    _actionTable.addDefault(42, {REDUCE, 94}); // Factor -> CHAR_LITERAL

    // State 43
    _actionTable.add(43, IDENTIFIER, {SHIFT, 72});

    // State 44
    _actionTable.add(44, CLOSED_CURLY, {SHIFT, 73});

    // State 45
    _actionTable.add(45, IDENTIFIER, {SHIFT, 31});
    _actionTable.add(45, OPEN_PAREN, {SHIFT, 32});
    _actionTable.add(45, KEYWORD_INT, {SHIFT, 8});
    _actionTable.add(45, KEYWORD_FLOAT, {SHIFT, 9});
    _actionTable.add(45, KEYWORD_CHAR, {SHIFT, 10});
    _actionTable.add(45, STAR, {SHIFT, 33});
    _actionTable.add(45, KEYWORD_IF, {SHIFT, 34});
    _actionTable.add(45, KEYWORD_WHILE, {SHIFT, 35});
    _actionTable.add(45, KEYWORD_FOR, {SHIFT, 36});
    _actionTable.add(45, KEYWORD_RET, {SHIFT, 37});
    _actionTable.add(45, MINUS, {SHIFT, 38});
    _actionTable.add(45, BANG, {SHIFT, 39});
    _actionTable.add(45, INTEGER_LITERAL, {SHIFT, 40});
    _actionTable.add(45, FLOAT_LITERAL, {SHIFT, 41});
    _actionTable.add(45, CHAR_LITERAL, {SHIFT, 42});
    _actionTable.addDefault(45, {REDUCE, 17}); // StmtList -> /* empty */
    _gotoTable.add(45, TYPE, 43);
    _gotoTable.add(45, BASE_TYPE, 14);
    _gotoTable.add(45, STMT_LIST, 74);
    _gotoTable.add(45, STMT, 45);
    _gotoTable.add(45, VAR_DECL_STMT, 46);
    _gotoTable.add(45, VAR_DECL_EXPR, 47);
    _gotoTable.add(45, ASSIGN_STMT, 48);
    _gotoTable.add(45, ASSIGN_EXPR, 49);
    _gotoTable.add(45, ASSIGN_TARGET, 50);
    _gotoTable.add(45, IF_STMT, 51);
    _gotoTable.add(45, WHILE_STMT, 52);
    _gotoTable.add(45, FOR_STMT, 53);
    _gotoTable.add(45, RETURN_STMT, 54);
    _gotoTable.add(45, EXPR_STMT, 55);
    _gotoTable.add(45, EXPR, 56);
    _gotoTable.add(45, UNARY_EXPR, 57);
    _gotoTable.add(45, UNARY_OP, 58);
    _gotoTable.add(45, SIMPLE_EXPR, 59);
    _gotoTable.add(45, TERM, 60);
    _gotoTable.add(45, FACTOR, 61);

    // State 46
    _actionTable.addDefault(46, {REDUCE, 18}); // Stmt -> VarDeclStmt

    // State 47
    _actionTable.add(47, SEMICOLON, {SHIFT, 75});

    // State 48
    _actionTable.addDefault(48, {REDUCE, 19}); // Stmt -> AssignStmt

    // State 49
    _actionTable.add(49, SEMICOLON, {SHIFT, 76});

    // State 50
    _actionTable.add(50, EQUALS, {SHIFT, 77});
    _actionTable.add(50, PLUS_EQUALS, {SHIFT, 78});
    _actionTable.add(50, MINUS_EQUALS, {SHIFT, 79});
    _actionTable.add(50, SLASH_EQUALS, {SHIFT, 80});
    _actionTable.add(50, STAR_EQUALS, {SHIFT, 81});
    _actionTable.add(50, AMPERSAND_EQUALS, {SHIFT, 82});
    _actionTable.add(50, PIPE_EQUALS, {SHIFT, 83});
    _actionTable.add(50, CARET_EQUALS, {SHIFT, 84});
    _actionTable.add(50, TILDE_EQUALS, {SHIFT, 85});
    _gotoTable.add(50, ASSIGN_OP, 86);

    // State 51
    _actionTable.addDefault(51, {REDUCE, 20}); // Stmt -> IfStmt

    // State 52
    _actionTable.addDefault(52, {REDUCE, 21}); // Stmt -> WhileStmt

    // State 53
    _actionTable.addDefault(53, {REDUCE, 22}); // Stmt -> ForStmt

    // State 54
    _actionTable.addDefault(54, {REDUCE, 23}); // Stmt -> ReturnStmt

    // State 55
    _actionTable.addDefault(55, {REDUCE, 24}); // Stmt -> ExprStmt

    // State 56
    _actionTable.add(56, SEMICOLON, {SHIFT, 87});

    // State 57
    _actionTable.add(57, LESS_THAN, {SHIFT, 88});
    _actionTable.add(57, GREATER_THAN, {SHIFT, 89});
    _actionTable.add(57, LESS_THAN_EQUALS, {SHIFT, 90});
    _actionTable.add(57, GREATER_THAN_EQUALS, {SHIFT, 91});
    _actionTable.add(57, EQUALS_EQUALS, {SHIFT, 92});
    _actionTable.add(57, BANG_EQUALS, {SHIFT, 93});
    _actionTable.addDefault(57, {REDUCE, 64}); // RelOpTail -> /* empty */
    _gotoTable.add(57, REL_OP_TAIL, 94);
    _gotoTable.add(57, REL_OP, 95);

    // State 58
    _actionTable.add(58, IDENTIFIER, {SHIFT, 64});
    _actionTable.add(58, OPEN_PAREN, {SHIFT, 32});
    _actionTable.add(58, MINUS, {SHIFT, 38});
    _actionTable.add(58, BANG, {SHIFT, 39});
    _actionTable.add(58, INTEGER_LITERAL, {SHIFT, 40});
    _actionTable.add(58, FLOAT_LITERAL, {SHIFT, 41});
    _actionTable.add(58, CHAR_LITERAL, {SHIFT, 42});
    _gotoTable.add(58, UNARY_EXPR, 96);
    _gotoTable.add(58, UNARY_OP, 58);
    _gotoTable.add(58, SIMPLE_EXPR, 59);
    _gotoTable.add(58, TERM, 60);
    _gotoTable.add(58, FACTOR, 61);

    // State 59
    _actionTable.addDefault(59, {REDUCE, 72}); // UnaryExpr -> SimpleExpr

    // State 60
    _actionTable.add(60, MINUS, {SHIFT, 97});
    _actionTable.add(60, PLUS, {SHIFT, 98});
    _actionTable.add(60, PIPE, {SHIFT, 99});
    _actionTable.add(60, CARET, {SHIFT, 100});
    _actionTable.add(60, PIPE_PIPE, {SHIFT, 101});
    _actionTable.addDefault(60, {REDUCE, 77}); // AddOpTail -> /* empty */
    _gotoTable.add(60, ADD_OP_TAIL, 102);
    _gotoTable.add(60, ADD_OP, 103);

    // State 61
    _actionTable.add(61, STAR, {SHIFT, 104});
    _actionTable.add(61, SLASH, {SHIFT, 105});
    _actionTable.add(61, AMPERSAND, {SHIFT, 106});
    _actionTable.add(61, AMPERSAND_AMPERSAND, {SHIFT, 107});
    _actionTable.addDefault(61, {REDUCE, 85}); // MulOpTail -> /* empty */
    _gotoTable.add(61, MUL_OP_TAIL, 108);
    _gotoTable.add(61, MUL_OP, 109);

    // State 62
    _actionTable.add(62, IDENTIFIER, {SHIFT, 64});
    _actionTable.add(62, OPEN_PAREN, {SHIFT, 32});
    _actionTable.add(62, MINUS, {SHIFT, 38});
    _actionTable.add(62, BANG, {SHIFT, 39});
    _actionTable.add(62, INTEGER_LITERAL, {SHIFT, 40});
    _actionTable.add(62, FLOAT_LITERAL, {SHIFT, 41});
    _actionTable.add(62, CHAR_LITERAL, {SHIFT, 42});
    _actionTable.addDefault(62, {REDUCE, 59}); // ExprList -> /* empty */
    _gotoTable.add(62, EXPR_LIST, 110);
    _gotoTable.add(62, EXPR, 111);
    _gotoTable.add(62, UNARY_EXPR, 57);
    _gotoTable.add(62, UNARY_OP, 58);
    _gotoTable.add(62, SIMPLE_EXPR, 59);
    _gotoTable.add(62, TERM, 60);
    _gotoTable.add(62, FACTOR, 61);

    // State 63
    _actionTable.add(63, IDENTIFIER, {SHIFT, 64});
    _actionTable.add(63, OPEN_PAREN, {SHIFT, 32});
    _actionTable.add(63, MINUS, {SHIFT, 38});
    _actionTable.add(63, BANG, {SHIFT, 39});
    _actionTable.add(63, INTEGER_LITERAL, {SHIFT, 40});
    _actionTable.add(63, FLOAT_LITERAL, {SHIFT, 41});
    _actionTable.add(63, CHAR_LITERAL, {SHIFT, 42});
    _gotoTable.add(63, EXPR, 112);
    _gotoTable.add(63, UNARY_EXPR, 57);
    _gotoTable.add(63, UNARY_OP, 58);
    _gotoTable.add(63, SIMPLE_EXPR, 59);
    _gotoTable.add(63, TERM, 60);
    _gotoTable.add(63, FACTOR, 61);

    // State 64
    _actionTable.add(64, OPEN_PAREN, {SHIFT, 62});
    _actionTable.addDefault(64, {REDUCE, 91}); // Factor -> IDENTIFIER

    // State 65
    _actionTable.add(65, CLOSED_PAREN, {SHIFT, 113});

    // State 66
    _actionTable.addDefault(66, {REDUCE, 35}); // AssignTarget -> STAR IDENTIFIER

    // State 67
    _actionTable.add(67, IDENTIFIER, {SHIFT, 64});
    _actionTable.add(67, OPEN_PAREN, {SHIFT, 32});
    _actionTable.add(67, MINUS, {SHIFT, 38});
    _actionTable.add(67, BANG, {SHIFT, 39});
    _actionTable.add(67, INTEGER_LITERAL, {SHIFT, 40});
    _actionTable.add(67, FLOAT_LITERAL, {SHIFT, 41});
    _actionTable.add(67, CHAR_LITERAL, {SHIFT, 42});
    _gotoTable.add(67, EXPR, 114);
    _gotoTable.add(67, UNARY_EXPR, 57);
    _gotoTable.add(67, UNARY_OP, 58);
    _gotoTable.add(67, SIMPLE_EXPR, 59);
    _gotoTable.add(67, TERM, 60);
    _gotoTable.add(67, FACTOR, 61);

    // State 68
    _actionTable.add(68, IDENTIFIER, {SHIFT, 64});
    _actionTable.add(68, OPEN_PAREN, {SHIFT, 32});
    _actionTable.add(68, MINUS, {SHIFT, 38});
    _actionTable.add(68, BANG, {SHIFT, 39});
    _actionTable.add(68, INTEGER_LITERAL, {SHIFT, 40});
    _actionTable.add(68, FLOAT_LITERAL, {SHIFT, 41});
    _actionTable.add(68, CHAR_LITERAL, {SHIFT, 42});
    _gotoTable.add(68, EXPR, 115);
    _gotoTable.add(68, UNARY_EXPR, 57);
    _gotoTable.add(68, UNARY_OP, 58);
    _gotoTable.add(68, SIMPLE_EXPR, 59);
    _gotoTable.add(68, TERM, 60);
    _gotoTable.add(68, FACTOR, 61);

    // State 69
    _actionTable.add(69, IDENTIFIER, {SHIFT, 116});
    _actionTable.add(69, KEYWORD_INT, {SHIFT, 8});
    _actionTable.add(69, KEYWORD_FLOAT, {SHIFT, 9});
    _actionTable.add(69, KEYWORD_CHAR, {SHIFT, 10});
    _actionTable.add(69, STAR, {SHIFT, 33});
    _actionTable.addDefault(69, {REDUCE, 51}); // ForInit -> /* empty */
    _gotoTable.add(69, TYPE, 43);
    _gotoTable.add(69, BASE_TYPE, 14);
    _gotoTable.add(69, VAR_DECL_EXPR, 117);
    _gotoTable.add(69, ASSIGN_EXPR, 118);
    _gotoTable.add(69, ASSIGN_TARGET, 50);
    _gotoTable.add(69, FOR_INIT, 119);

    // State 70
    _actionTable.add(70, SEMICOLON, {SHIFT, 120});
    _gotoTable.add(70, EXPR, 71);
    _gotoTable.add(70, UNARY_EXPR, 57);
    _gotoTable.add(70, UNARY_OP, 58);
    _gotoTable.add(70, SIMPLE_EXPR, 59);
    _gotoTable.add(70, TERM, 60);
    _gotoTable.add(70, FACTOR, 61);

    // State 71
    _actionTable.addDefault(71, {REDUCE, 52}); // ExprOpt -> Expr

    // State 72
    _actionTable.add(72, EQUALS, {SHIFT, 121});
    _actionTable.addDefault(72, {REDUCE, 30}); // InitOpt -> /* empty */
    _gotoTable.add(72, INIT_OPT, 122);

    // State 73
    _actionTable.addDefault(73, {REDUCE, 3}); // FunctionDecl -> KEYWORD_FN IDENTIFIER OPEN_PAREN ParamList CLOSED_PAREN RIGHT_ARROW Type OPEN_CURLY StmtList CLOSED_CURLY

    // State 74
    _actionTable.addDefault(74, {REDUCE, 16}); // StmtList -> Stmt StmtList

    // State 75
    _actionTable.addDefault(75, {REDUCE, 27}); // VarDeclStmt -> VarDeclExpr SEMICOLON

    // State 76
    _actionTable.addDefault(76, {REDUCE, 31}); // AssignStmt -> AssignExpr SEMICOLON

    // State 77
    _actionTable.addDefault(77, {REDUCE, 36}); // AssignOp -> EQUALS

    // State 78
    _actionTable.addDefault(78, {REDUCE, 37}); // AssignOp -> PLUS_EQUALS

    // State 79
    _actionTable.addDefault(79, {REDUCE, 38}); // AssignOp -> MINUS_EQUALS

    // State 80
    _actionTable.addDefault(80, {REDUCE, 39}); // AssignOp -> SLASH_EQUALS

    // State 81
    _actionTable.addDefault(81, {REDUCE, 40}); // AssignOp -> STAR_EQUALS

    // State 82
    _actionTable.addDefault(82, {REDUCE, 41}); // AssignOp -> AMPERSAND_EQUALS

    // State 83
    _actionTable.addDefault(83, {REDUCE, 42}); // AssignOp -> PIPE_EQUALS

    // State 84
    _actionTable.addDefault(84, {REDUCE, 43}); // AssignOp -> CARET_EQUALS

    // State 85
    _actionTable.addDefault(85, {REDUCE, 44}); // AssignOp -> TILDE_EQUALS

    // State 86
    _actionTable.add(86, IDENTIFIER, {SHIFT, 64});
    _actionTable.add(86, OPEN_PAREN, {SHIFT, 32});
    _actionTable.add(86, MINUS, {SHIFT, 38});
    _actionTable.add(86, BANG, {SHIFT, 39});
    _actionTable.add(86, INTEGER_LITERAL, {SHIFT, 40});
    _actionTable.add(86, FLOAT_LITERAL, {SHIFT, 41});
    _actionTable.add(86, CHAR_LITERAL, {SHIFT, 42});
    _gotoTable.add(86, EXPR, 123);
    _gotoTable.add(86, UNARY_EXPR, 57);
    _gotoTable.add(86, UNARY_OP, 58);
    _gotoTable.add(86, SIMPLE_EXPR, 59);
    _gotoTable.add(86, TERM, 60);
    _gotoTable.add(86, FACTOR, 61);

    // State 87
    _actionTable.addDefault(87, {REDUCE, 57}); // ExprStmt -> Expr SEMICOLON

    // State 88
    _actionTable.addDefault(88, {REDUCE, 65}); // RelOp -> LESS_THAN

    // State 89
    _actionTable.addDefault(89, {REDUCE, 66}); // RelOp -> GREATER_THAN

    // State 90
    _actionTable.addDefault(90, {REDUCE, 67}); // RelOp -> LESS_THAN_EQUALS

    // State 91
    _actionTable.addDefault(91, {REDUCE, 68}); // RelOp -> GREATER_THAN_EQUALS

    // State 92
    _actionTable.addDefault(92, {REDUCE, 69}); // RelOp -> EQUALS_EQUALS

    // State 93
    _actionTable.addDefault(93, {REDUCE, 70}); // RelOp -> BANG_EQUALS

    // State 94
    _actionTable.addDefault(94, {REDUCE, 62}); // Expr -> UnaryExpr RelOpTail

    // State 95
    _actionTable.add(95, IDENTIFIER, {SHIFT, 64});
    _actionTable.add(95, OPEN_PAREN, {SHIFT, 32});
    _actionTable.add(95, MINUS, {SHIFT, 38});
    _actionTable.add(95, BANG, {SHIFT, 39});
    _actionTable.add(95, INTEGER_LITERAL, {SHIFT, 40});
    _actionTable.add(95, FLOAT_LITERAL, {SHIFT, 41});
    _actionTable.add(95, CHAR_LITERAL, {SHIFT, 42});
    _gotoTable.add(95, UNARY_EXPR, 124);
    _gotoTable.add(95, UNARY_OP, 58);
    _gotoTable.add(95, SIMPLE_EXPR, 59);
    _gotoTable.add(95, TERM, 60);
    _gotoTable.add(95, FACTOR, 61);

    // State 96
    _actionTable.addDefault(96, {REDUCE, 71}); // UnaryExpr -> UnaryOp UnaryExpr

    // State 97
    _actionTable.addDefault(97, {REDUCE, 79}); // AddOp -> MINUS

    // State 98
    _actionTable.addDefault(98, {REDUCE, 78}); // AddOp -> PLUS

    // State 99
    _actionTable.addDefault(99, {REDUCE, 80}); // AddOp -> PIPE

    // State 100
    _actionTable.addDefault(100, {REDUCE, 81}); // AddOp -> CARET

    // State 101
    _actionTable.addDefault(101, {REDUCE, 82}); // AddOp -> PIPE_PIPE

    // State 102
    _actionTable.addDefault(102, {REDUCE, 75}); // SimpleExpr -> Term AddOpTail

    // State 103
    _actionTable.add(103, IDENTIFIER, {SHIFT, 64});
    _actionTable.add(103, OPEN_PAREN, {SHIFT, 32});
    _actionTable.add(103, INTEGER_LITERAL, {SHIFT, 40});
    _actionTable.add(103, FLOAT_LITERAL, {SHIFT, 41});
    _actionTable.add(103, CHAR_LITERAL, {SHIFT, 42});
    _gotoTable.add(103, TERM, 125);
    _gotoTable.add(103, FACTOR, 61);

    // State 104
    _actionTable.addDefault(104, {REDUCE, 86}); // MulOp -> STAR

    // State 105
    _actionTable.addDefault(105, {REDUCE, 87}); // MulOp -> SLASH

    // State 106
    _actionTable.addDefault(106, {REDUCE, 88}); // MulOp -> AMPERSAND

    // State 107
    _actionTable.addDefault(107, {REDUCE, 89}); // MulOp -> AMPERSAND_AMPERSAND

    // State 108
    _actionTable.addDefault(108, {REDUCE, 83}); // Term -> Factor MulOpTail

    // State 109
    _actionTable.add(109, IDENTIFIER, {SHIFT, 64});
    _actionTable.add(109, OPEN_PAREN, {SHIFT, 32});
    _actionTable.add(109, INTEGER_LITERAL, {SHIFT, 40});
    _actionTable.add(109, FLOAT_LITERAL, {SHIFT, 41});
    _actionTable.add(109, CHAR_LITERAL, {SHIFT, 42});
    _gotoTable.add(109, FACTOR, 126);

    // State 110
    _actionTable.add(110, CLOSED_PAREN, {SHIFT, 127});

    // State 111
    _actionTable.add(111, COMMA, {SHIFT, 128});
    _actionTable.addDefault(111, {REDUCE, 61}); // ExprTail -> /* empty */
    _gotoTable.add(111, EXPR_TAIL, 129);

    // State 112
    _actionTable.add(112, CLOSED_BRACKET, {SHIFT, 130});

    // State 113
    _actionTable.addDefault(113, {REDUCE, 90}); // Factor -> OPEN_PAREN Expr CLOSED_PAREN

    // State 114
    _actionTable.add(114, CLOSED_PAREN, {SHIFT, 131});

    // State 115
    _actionTable.add(115, CLOSED_PAREN, {SHIFT, 132});

    // State 116
    _actionTable.add(116, OPEN_BRACKET, {SHIFT, 63});
    _actionTable.addDefault(116, {REDUCE, 33}); // AssignTarget -> IDENTIFIER

    // State 117
    _actionTable.addDefault(117, {REDUCE, 49}); // ForInit -> VarDeclExpr

    // State 118
    _actionTable.addDefault(118, {REDUCE, 50}); // ForInit -> AssignExpr

    // State 119
    _actionTable.add(119, SEMICOLON, {SHIFT, 133});

    // State 120
    _actionTable.addDefault(120, {REDUCE, 56}); // ReturnStmt -> KEYWORD_RET ExprOpt SEMICOLON

    // State 121
    _actionTable.add(121, IDENTIFIER, {SHIFT, 64});
    _actionTable.add(121, OPEN_PAREN, {SHIFT, 32});
    _actionTable.add(121, MINUS, {SHIFT, 38});
    _actionTable.add(121, BANG, {SHIFT, 39});
    _actionTable.add(121, INTEGER_LITERAL, {SHIFT, 40});
    _actionTable.add(121, FLOAT_LITERAL, {SHIFT, 41});
    _actionTable.add(121, CHAR_LITERAL, {SHIFT, 42});
    _gotoTable.add(121, EXPR, 134);
    _gotoTable.add(121, UNARY_EXPR, 57);
    _gotoTable.add(121, UNARY_OP, 58);
    _gotoTable.add(121, SIMPLE_EXPR, 59);
    _gotoTable.add(121, TERM, 60);
    _gotoTable.add(121, FACTOR, 61);

    // State 122
    _actionTable.addDefault(122, {REDUCE, 28}); // VarDeclExpr -> Type IDENTIFIER InitOpt

    // State 123
    _actionTable.addDefault(123, {REDUCE, 32}); // AssignExpr -> AssignTarget AssignOp Expr

    // State 124
    _actionTable.add(124, LESS_THAN, {SHIFT, 88});
    _actionTable.add(124, GREATER_THAN, {SHIFT, 89});
    _actionTable.add(124, LESS_THAN_EQUALS, {SHIFT, 90});
    _actionTable.add(124, GREATER_THAN_EQUALS, {SHIFT, 91});
    _actionTable.add(124, EQUALS_EQUALS, {SHIFT, 92});
    _actionTable.add(124, BANG_EQUALS, {SHIFT, 93});
    _actionTable.addDefault(124, {REDUCE, 64}); // RelOpTail -> /* empty */
    _gotoTable.add(124, REL_OP_TAIL, 135);
    _gotoTable.add(124, REL_OP, 95);

    // State 125
    _actionTable.add(125, MINUS, {SHIFT, 97});
    _actionTable.add(125, PLUS, {SHIFT, 98});
    _actionTable.add(125, PIPE, {SHIFT, 99});
    _actionTable.add(125, CARET, {SHIFT, 100});
    _actionTable.add(125, PIPE_PIPE, {SHIFT, 101});
    _actionTable.addDefault(125, {REDUCE, 77}); // AddOpTail -> /* empty */
    _gotoTable.add(125, ADD_OP_TAIL, 136);
    _gotoTable.add(125, ADD_OP, 103);

    // State 126
    _actionTable.add(126, STAR, {SHIFT, 104});
    _actionTable.add(126, SLASH, {SHIFT, 105});
    _actionTable.add(126, AMPERSAND, {SHIFT, 106});
    _actionTable.add(126, AMPERSAND_AMPERSAND, {SHIFT, 107});
    _actionTable.addDefault(126, {REDUCE, 85}); // MulOpTail -> /* empty */
    _gotoTable.add(126, MUL_OP_TAIL, 137);
    _gotoTable.add(126, MUL_OP, 109);

    // State 127
    _actionTable.addDefault(127, {REDUCE, 95}); // Factor -> IDENTIFIER OPEN_PAREN ExprList CLOSED_PAREN

    // State 128
    _actionTable.add(128, IDENTIFIER, {SHIFT, 64});
    _actionTable.add(128, OPEN_PAREN, {SHIFT, 32});
    _actionTable.add(128, MINUS, {SHIFT, 38});
    _actionTable.add(128, BANG, {SHIFT, 39});
    _actionTable.add(128, INTEGER_LITERAL, {SHIFT, 40});
    _actionTable.add(128, FLOAT_LITERAL, {SHIFT, 41});
    _actionTable.add(128, CHAR_LITERAL, {SHIFT, 42});
    _gotoTable.add(128, EXPR, 138);
    _gotoTable.add(128, UNARY_EXPR, 57);
    _gotoTable.add(128, UNARY_OP, 58);
    _gotoTable.add(128, SIMPLE_EXPR, 59);
    _gotoTable.add(128, TERM, 60);
    _gotoTable.add(128, FACTOR, 61);

    // State 129
    _actionTable.addDefault(129, {REDUCE, 58}); // ExprList -> Expr ExprTail

    // State 130
    _actionTable.addDefault(130, {REDUCE, 34}); // AssignTarget -> IDENTIFIER OPEN_BRACKET Expr CLOSED_BRACKET

    // State 131
    _actionTable.add(131, IDENTIFIER, {SHIFT, 31});
    _actionTable.add(131, OPEN_PAREN, {SHIFT, 32});
    _actionTable.add(131, OPEN_CURLY, {SHIFT, 139});
    _actionTable.add(131, KEYWORD_INT, {SHIFT, 8});
    _actionTable.add(131, KEYWORD_FLOAT, {SHIFT, 9});
    _actionTable.add(131, KEYWORD_CHAR, {SHIFT, 10});
    _actionTable.add(131, STAR, {SHIFT, 33});
    _actionTable.add(131, KEYWORD_IF, {SHIFT, 34});
    _actionTable.add(131, KEYWORD_WHILE, {SHIFT, 35});
    _actionTable.add(131, KEYWORD_FOR, {SHIFT, 36});
    _actionTable.add(131, KEYWORD_RET, {SHIFT, 37});
    _actionTable.add(131, MINUS, {SHIFT, 38});
    _actionTable.add(131, BANG, {SHIFT, 39});
    _actionTable.add(131, INTEGER_LITERAL, {SHIFT, 40});
    _actionTable.add(131, FLOAT_LITERAL, {SHIFT, 41});
    _actionTable.add(131, CHAR_LITERAL, {SHIFT, 42});
    _gotoTable.add(131, TYPE, 43);
    _gotoTable.add(131, BASE_TYPE, 14);
    _gotoTable.add(131, STMT, 140);
    _gotoTable.add(131, BODY, 141);
    _gotoTable.add(131, VAR_DECL_STMT, 46);
    _gotoTable.add(131, VAR_DECL_EXPR, 47);
    _gotoTable.add(131, ASSIGN_STMT, 48);
    _gotoTable.add(131, ASSIGN_EXPR, 49);
    _gotoTable.add(131, ASSIGN_TARGET, 50);
    _gotoTable.add(131, IF_STMT, 51);
    _gotoTable.add(131, WHILE_STMT, 52);
    _gotoTable.add(131, FOR_STMT, 53);
    _gotoTable.add(131, RETURN_STMT, 54);
    _gotoTable.add(131, EXPR_STMT, 55);
    _gotoTable.add(131, EXPR, 56);
    _gotoTable.add(131, UNARY_EXPR, 57);
    _gotoTable.add(131, UNARY_OP, 58);
    _gotoTable.add(131, SIMPLE_EXPR, 59);
    _gotoTable.add(131, TERM, 60);
    _gotoTable.add(131, FACTOR, 61);

    // State 132
    _actionTable.add(132, IDENTIFIER, {SHIFT, 31});
    _actionTable.add(132, OPEN_PAREN, {SHIFT, 32});
    _actionTable.add(132, OPEN_CURLY, {SHIFT, 139});
    _actionTable.add(132, KEYWORD_INT, {SHIFT, 8});
    _actionTable.add(132, KEYWORD_FLOAT, {SHIFT, 9});
    _actionTable.add(132, KEYWORD_CHAR, {SHIFT, 10});
    _actionTable.add(132, STAR, {SHIFT, 33});
    _actionTable.add(132, KEYWORD_IF, {SHIFT, 34});
    _actionTable.add(132, KEYWORD_WHILE, {SHIFT, 35});
    _actionTable.add(132, KEYWORD_FOR, {SHIFT, 36});
    _actionTable.add(132, KEYWORD_RET, {SHIFT, 37});
    _actionTable.add(132, MINUS, {SHIFT, 38});
    _actionTable.add(132, BANG, {SHIFT, 39});
    _actionTable.add(132, INTEGER_LITERAL, {SHIFT, 40});
    _actionTable.add(132, FLOAT_LITERAL, {SHIFT, 41});
    _actionTable.add(132, CHAR_LITERAL, {SHIFT, 42});
    _gotoTable.add(132, TYPE, 43);
    _gotoTable.add(132, BASE_TYPE, 14);
    _gotoTable.add(132, STMT, 140);
    _gotoTable.add(132, BODY, 142);
    _gotoTable.add(132, VAR_DECL_STMT, 46);
    _gotoTable.add(132, VAR_DECL_EXPR, 47);
    _gotoTable.add(132, ASSIGN_STMT, 48);
    _gotoTable.add(132, ASSIGN_EXPR, 49);
    _gotoTable.add(132, ASSIGN_TARGET, 50);
    _gotoTable.add(132, IF_STMT, 51);
    _gotoTable.add(132, WHILE_STMT, 52);
    _gotoTable.add(132, FOR_STMT, 53);
    _gotoTable.add(132, RETURN_STMT, 54);
    _gotoTable.add(132, EXPR_STMT, 55);
    _gotoTable.add(132, EXPR, 56);
    _gotoTable.add(132, UNARY_EXPR, 57);
    _gotoTable.add(132, UNARY_OP, 58);
    _gotoTable.add(132, SIMPLE_EXPR, 59);
    _gotoTable.add(132, TERM, 60);
    _gotoTable.add(132, FACTOR, 61);

    // State 133
    _actionTable.add(133, IDENTIFIER, {SHIFT, 64});
    _actionTable.add(133, OPEN_PAREN, {SHIFT, 32});
    _actionTable.add(133, MINUS, {SHIFT, 38});
    _actionTable.add(133, BANG, {SHIFT, 39});
    _actionTable.add(133, INTEGER_LITERAL, {SHIFT, 40});
    _actionTable.add(133, FLOAT_LITERAL, {SHIFT, 41});
    _actionTable.add(133, CHAR_LITERAL, {SHIFT, 42});
    _actionTable.addDefault(133, {REDUCE, 53}); // ExprOpt -> /* empty */
    _gotoTable.add(133, EXPR_OPT, 143);
    _gotoTable.add(133, EXPR, 71);
    _gotoTable.add(133, UNARY_EXPR, 57);
    _gotoTable.add(133, UNARY_OP, 58);
    _gotoTable.add(133, SIMPLE_EXPR, 59);
    _gotoTable.add(133, TERM, 60);
    _gotoTable.add(133, FACTOR, 61);

    // State 134
    _actionTable.addDefault(134, {REDUCE, 29}); // InitOpt -> EQUALS Expr

    // State 135
    _actionTable.addDefault(135, {REDUCE, 63}); // RelOpTail -> RelOp UnaryExpr RelOpTail

    // State 136
    _actionTable.addDefault(136, {REDUCE, 76}); // AddOpTail -> AddOp Term AddOpTail

    // State 137
    _actionTable.addDefault(137, {REDUCE, 84}); // MulOpTail -> MulOp Factor MulOpTail

    // State 138
    _actionTable.add(138, COMMA, {SHIFT, 128});
    _actionTable.addDefault(138, {REDUCE, 61}); // ExprTail -> /* empty */
    _gotoTable.add(138, EXPR_TAIL, 144);

    // State 139
    _actionTable.add(139, IDENTIFIER, {SHIFT, 31});
    _actionTable.add(139, OPEN_PAREN, {SHIFT, 32});
    _actionTable.add(139, KEYWORD_INT, {SHIFT, 8});
    _actionTable.add(139, KEYWORD_FLOAT, {SHIFT, 9});
    _actionTable.add(139, KEYWORD_CHAR, {SHIFT, 10});
    _actionTable.add(139, STAR, {SHIFT, 33});
    _actionTable.add(139, KEYWORD_IF, {SHIFT, 34});
    _actionTable.add(139, KEYWORD_WHILE, {SHIFT, 35});
    _actionTable.add(139, KEYWORD_FOR, {SHIFT, 36});
    _actionTable.add(139, KEYWORD_RET, {SHIFT, 37});
    _actionTable.add(139, MINUS, {SHIFT, 38});
    _actionTable.add(139, BANG, {SHIFT, 39});
    _actionTable.add(139, INTEGER_LITERAL, {SHIFT, 40});
    _actionTable.add(139, FLOAT_LITERAL, {SHIFT, 41});
    _actionTable.add(139, CHAR_LITERAL, {SHIFT, 42});
    _actionTable.addDefault(139, {REDUCE, 17}); // StmtList -> /* empty */
    _gotoTable.add(139, TYPE, 43);
    _gotoTable.add(139, BASE_TYPE, 14);
    _gotoTable.add(139, STMT_LIST, 145);
    _gotoTable.add(139, STMT, 45);
    _gotoTable.add(139, VAR_DECL_STMT, 46);
    _gotoTable.add(139, VAR_DECL_EXPR, 47);
    _gotoTable.add(139, ASSIGN_STMT, 48);
    _gotoTable.add(139, ASSIGN_EXPR, 49);
    _gotoTable.add(139, ASSIGN_TARGET, 50);
    _gotoTable.add(139, IF_STMT, 51);
    _gotoTable.add(139, WHILE_STMT, 52);
    _gotoTable.add(139, FOR_STMT, 53);
    _gotoTable.add(139, RETURN_STMT, 54);
    _gotoTable.add(139, EXPR_STMT, 55);
    _gotoTable.add(139, EXPR, 56);
    _gotoTable.add(139, UNARY_EXPR, 57);
    _gotoTable.add(139, UNARY_OP, 58);
    _gotoTable.add(139, SIMPLE_EXPR, 59);
    _gotoTable.add(139, TERM, 60);
    _gotoTable.add(139, FACTOR, 61);

    // State 140
    _actionTable.addDefault(140, {REDUCE, 26}); // Body -> Stmt

    // State 141
    _actionTable.add(141, KEYWORD_ELSE, {SHIFT, 146});
    _actionTable.addDefault(141, {REDUCE, 45}); // IfStmt -> KEYWORD_IF OPEN_PAREN Expr CLOSED_PAREN Body

    // State 142
    _actionTable.addDefault(142, {REDUCE, 47}); // WhileStmt -> KEYWORD_WHILE OPEN_PAREN Expr CLOSED_PAREN Body

    // State 143
    _actionTable.add(143, SEMICOLON, {SHIFT, 147});

    // State 144
    _actionTable.addDefault(144, {REDUCE, 60}); // ExprTail -> COMMA Expr ExprTail

    // State 145
    _actionTable.add(145, CLOSED_CURLY, {SHIFT, 148});

    // State 146
    _actionTable.add(146, IDENTIFIER, {SHIFT, 31});
    _actionTable.add(146, OPEN_PAREN, {SHIFT, 32});
    _actionTable.add(146, OPEN_CURLY, {SHIFT, 139});
    _actionTable.add(146, KEYWORD_INT, {SHIFT, 8});
    _actionTable.add(146, KEYWORD_FLOAT, {SHIFT, 9});
    _actionTable.add(146, KEYWORD_CHAR, {SHIFT, 10});
    _actionTable.add(146, STAR, {SHIFT, 33});
    _actionTable.add(146, KEYWORD_IF, {SHIFT, 34});
    _actionTable.add(146, KEYWORD_WHILE, {SHIFT, 35});
    _actionTable.add(146, KEYWORD_FOR, {SHIFT, 36});
    _actionTable.add(146, KEYWORD_RET, {SHIFT, 37});
    _actionTable.add(146, MINUS, {SHIFT, 38});
    _actionTable.add(146, BANG, {SHIFT, 39});
    _actionTable.add(146, INTEGER_LITERAL, {SHIFT, 40});
    _actionTable.add(146, FLOAT_LITERAL, {SHIFT, 41});
    _actionTable.add(146, CHAR_LITERAL, {SHIFT, 42});
    _gotoTable.add(146, TYPE, 43);
    _gotoTable.add(146, BASE_TYPE, 14);
    _gotoTable.add(146, STMT, 140);
    _gotoTable.add(146, BODY, 149);
    _gotoTable.add(146, VAR_DECL_STMT, 46);
    _gotoTable.add(146, VAR_DECL_EXPR, 47);
    _gotoTable.add(146, ASSIGN_STMT, 48);
    _gotoTable.add(146, ASSIGN_EXPR, 49);
    _gotoTable.add(146, ASSIGN_TARGET, 50);
    _gotoTable.add(146, IF_STMT, 51);
    _gotoTable.add(146, WHILE_STMT, 52);
    _gotoTable.add(146, FOR_STMT, 53);
    _gotoTable.add(146, RETURN_STMT, 54);
    _gotoTable.add(146, EXPR_STMT, 55);
    _gotoTable.add(146, EXPR, 56);
    _gotoTable.add(146, UNARY_EXPR, 57);
    _gotoTable.add(146, UNARY_OP, 58);
    _gotoTable.add(146, SIMPLE_EXPR, 59);
    _gotoTable.add(146, TERM, 60);
    _gotoTable.add(146, FACTOR, 61);

    // State 147
    _actionTable.add(147, IDENTIFIER, {SHIFT, 116});
    _actionTable.add(147, STAR, {SHIFT, 33});
    _actionTable.addDefault(147, {REDUCE, 55}); // ForUpdate -> /* empty */
    _gotoTable.add(147, ASSIGN_EXPR, 150);
    _gotoTable.add(147, ASSIGN_TARGET, 50);
    _gotoTable.add(147, FOR_UPDATE, 151);

    // State 148
    _actionTable.addDefault(148, {REDUCE, 25}); // Body -> OPEN_CURLY StmtList CLOSED_CURLY

    // State 149
    _actionTable.addDefault(149, {REDUCE, 46}); // IfStmt -> KEYWORD_IF OPEN_PAREN Expr CLOSED_PAREN Body KEYWORD_ELSE Body

    // State 150
    _actionTable.addDefault(150, {REDUCE, 54}); // ForUpdate -> AssignExpr

    // State 151
    _actionTable.add(151, CLOSED_PAREN, {SHIFT, 152});

    // State 152
    _actionTable.add(152, IDENTIFIER, {SHIFT, 31});
    _actionTable.add(152, OPEN_PAREN, {SHIFT, 32});
    _actionTable.add(152, OPEN_CURLY, {SHIFT, 139});
    _actionTable.add(152, KEYWORD_INT, {SHIFT, 8});
    _actionTable.add(152, KEYWORD_FLOAT, {SHIFT, 9});
    _actionTable.add(152, KEYWORD_CHAR, {SHIFT, 10});
    _actionTable.add(152, STAR, {SHIFT, 33});
    _actionTable.add(152, KEYWORD_IF, {SHIFT, 34});
    _actionTable.add(152, KEYWORD_WHILE, {SHIFT, 35});
    _actionTable.add(152, KEYWORD_FOR, {SHIFT, 36});
    _actionTable.add(152, KEYWORD_RET, {SHIFT, 37});
    _actionTable.add(152, MINUS, {SHIFT, 38});
    _actionTable.add(152, BANG, {SHIFT, 39});
    _actionTable.add(152, INTEGER_LITERAL, {SHIFT, 40});
    _actionTable.add(152, FLOAT_LITERAL, {SHIFT, 41});
    _actionTable.add(152, CHAR_LITERAL, {SHIFT, 42});
    _gotoTable.add(152, TYPE, 43);
    _gotoTable.add(152, BASE_TYPE, 14);
    _gotoTable.add(152, STMT, 140);
    _gotoTable.add(152, BODY, 153);
    _gotoTable.add(152, VAR_DECL_STMT, 46);
    _gotoTable.add(152, VAR_DECL_EXPR, 47);
    _gotoTable.add(152, ASSIGN_STMT, 48);
    _gotoTable.add(152, ASSIGN_EXPR, 49);
    _gotoTable.add(152, ASSIGN_TARGET, 50);
    _gotoTable.add(152, IF_STMT, 51);
    _gotoTable.add(152, WHILE_STMT, 52);
    _gotoTable.add(152, FOR_STMT, 53);
    _gotoTable.add(152, RETURN_STMT, 54);
    _gotoTable.add(152, EXPR_STMT, 55);
    _gotoTable.add(152, EXPR, 56);
    _gotoTable.add(152, UNARY_EXPR, 57);
    _gotoTable.add(152, UNARY_OP, 58);
    _gotoTable.add(152, SIMPLE_EXPR, 59);
    _gotoTable.add(152, TERM, 60);
    _gotoTable.add(152, FACTOR, 61);

    // State 153
    _actionTable.addDefault(153, {REDUCE, 48}); // ForStmt -> KEYWORD_FOR OPEN_PAREN ForInit SEMICOLON ExprOpt SEMICOLON ForUpdate CLOSED_PAREN Body
}