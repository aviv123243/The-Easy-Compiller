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
    rule.addSymbol(KEYWORD_FN).addSymbol(IDENTIFIER).addSymbol(OPEN_PAREN).addSymbol(PARAM_LIST).addSymbol(CLOSED_PAREN).addSymbol(RIGHT_ARROW).addSymbol(TYPE).addSymbol(OPEN_CURLY).addSymbol(STMT_LIST).addSymbol(CLOSED_CURLY);
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

    // Rule 13: TypeTail -> OPEN_BRACKET INTEGER_LITERAL CLOSED_BRACKET
    rule.setLeft(TYPE_TAIL);
    rule.addSymbol(OPEN_BRACKET).addSymbol(INTEGER_LITERAL).addSymbol(CLOSED_BRACKET);
    addProductionRule(rule);
    rule.reset();

    // Rule 14: TypeTail -> STAR
    rule.setLeft(TYPE_TAIL);
    rule.addSymbol(STAR);
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

    // Rule 29: InitOpt -> EQUALS AssignValue
    rule.setLeft(INIT_OPT);
    rule.addSymbol(EQUALS).addSymbol(ASSIGN_VALUE);
    addProductionRule(rule);
    rule.reset();

    // Rule 30: InitOpt -> /* empty */
    rule.setLeft(INIT_OPT);
    rule.addSymbol(); // empty
    addProductionRule(rule);
    rule.reset();

    // Rule 31: AssignValue -> Expr
    rule.setLeft(ASSIGN_VALUE);
    rule.addSymbol(EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 32: AssignValue -> OPEN_CURLY ExprList CLOSED_CURLY
    rule.setLeft(ASSIGN_VALUE);
    rule.addSymbol(OPEN_CURLY).addSymbol(EXPR_LIST).addSymbol(CLOSED_CURLY);
    addProductionRule(rule);
    rule.reset();

    // Rule 33: AssignStmt -> AssignExpr SEMICOLON
    rule.setLeft(ASSIGN_STMT);
    rule.addSymbol(ASSIGN_EXPR).addSymbol(SEMICOLON);
    addProductionRule(rule);
    rule.reset();

    // Rule 34: AssignExpr -> AssignTarget AssignOp Expr
    rule.setLeft(ASSIGN_EXPR);
    rule.addSymbol(ASSIGN_TARGET).addSymbol(ASSIGN_OP).addSymbol(EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 35: AssignTarget -> IDENTIFIER
    rule.setLeft(ASSIGN_TARGET);
    rule.addSymbol(IDENTIFIER);
    addProductionRule(rule);
    rule.reset();

    // Rule 36: AssignTarget -> IDENTIFIER OPEN_BRACKET Expr CLOSED_BRACKET
    rule.setLeft(ASSIGN_TARGET);
    rule.addSymbol(IDENTIFIER).addSymbol(OPEN_BRACKET).addSymbol(EXPR).addSymbol(CLOSED_BRACKET);
    addProductionRule(rule);
    rule.reset();

    // Rule 37: AssignTarget -> STAR IDENTIFIER
    rule.setLeft(ASSIGN_TARGET);
    rule.addSymbol(STAR).addSymbol(IDENTIFIER);
    addProductionRule(rule);
    rule.reset();

    // Rule 38: AssignOp -> EQUALS
    rule.setLeft(ASSIGN_OP);
    rule.addSymbol(EQUALS);
    addProductionRule(rule);
    rule.reset();

    // Rule 39: AssignOp -> PLUS_EQUALS
    rule.setLeft(ASSIGN_OP);
    rule.addSymbol(PLUS_EQUALS);
    addProductionRule(rule);
    rule.reset();

    // Rule 40: AssignOp -> MINUS_EQUALS
    rule.setLeft(ASSIGN_OP);
    rule.addSymbol(MINUS_EQUALS);
    addProductionRule(rule);
    rule.reset();

    // Rule 41: AssignOp -> SLASH_EQUALS
    rule.setLeft(ASSIGN_OP);
    rule.addSymbol(SLASH_EQUALS);
    addProductionRule(rule);
    rule.reset();

    // Rule 42: AssignOp -> STAR_EQUALS
    rule.setLeft(ASSIGN_OP);
    rule.addSymbol(STAR_EQUALS);
    addProductionRule(rule);
    rule.reset();

    // Rule 43: AssignOp -> AMPERSAND_EQUALS
    rule.setLeft(ASSIGN_OP);
    rule.addSymbol(AMPERSAND_EQUALS);
    addProductionRule(rule);
    rule.reset();

    // Rule 44: AssignOp -> PIPE_EQUALS
    rule.setLeft(ASSIGN_OP);
    rule.addSymbol(PIPE_EQUALS);
    addProductionRule(rule);
    rule.reset();

    // Rule 45: AssignOp -> CARET_EQUALS
    rule.setLeft(ASSIGN_OP);
    rule.addSymbol(CARET_EQUALS);
    addProductionRule(rule);
    rule.reset();

    // Rule 46: AssignOp -> TILDE_EQUALS
    rule.setLeft(ASSIGN_OP);
    rule.addSymbol(TILDE_EQUALS);
    addProductionRule(rule);
    rule.reset();

    // Rule 47: IfStmt -> KEYWORD_IF OPEN_PAREN ConditionOp CLOSED_PAREN Body
    rule.setLeft(IF_STMT);
    rule.addSymbol(KEYWORD_IF).addSymbol(OPEN_PAREN).addSymbol(CONDITION_OP).addSymbol(CLOSED_PAREN).addSymbol(BODY);
    addProductionRule(rule);
    rule.reset();

    // Rule 48: IfStmt -> KEYWORD_IF OPEN_PAREN ConditionOp CLOSED_PAREN Body KEYWORD_ELSE Body
    rule.setLeft(IF_STMT);
    rule.addSymbol(KEYWORD_IF).addSymbol(OPEN_PAREN).addSymbol(CONDITION_OP).addSymbol(CLOSED_PAREN).addSymbol(BODY).addSymbol(KEYWORD_ELSE).addSymbol(BODY);
    addProductionRule(rule);
    rule.reset();

    // Rule 49: WhileStmt -> KEYWORD_WHILE OPEN_PAREN ConditionOp CLOSED_PAREN Body
    rule.setLeft(WHILE_STMT);
    rule.addSymbol(KEYWORD_WHILE).addSymbol(OPEN_PAREN).addSymbol(CONDITION_OP).addSymbol(CLOSED_PAREN).addSymbol(BODY);
    addProductionRule(rule);
    rule.reset();

    // Rule 50: ConditionOp -> Expr
    rule.setLeft(CONDITION_OP);
    rule.addSymbol(EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 51: ConditionOp -> AssignExpr
    rule.setLeft(CONDITION_OP);
    rule.addSymbol(ASSIGN_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 52: ForStmt -> KEYWORD_FOR OPEN_PAREN ForInit SEMICOLON ExprOpt SEMICOLON ForUpdate CLOSED_PAREN Body
    rule.setLeft(FOR_STMT);
    rule.addSymbol(KEYWORD_FOR).addSymbol(OPEN_PAREN).addSymbol(FOR_INIT).addSymbol(SEMICOLON).addSymbol(EXPR_OPT).addSymbol(SEMICOLON).addSymbol(FOR_UPDATE).addSymbol(CLOSED_PAREN).addSymbol(BODY);
    addProductionRule(rule);
    rule.reset();

    // Rule 53: ForInit -> VarDeclExpr
    rule.setLeft(FOR_INIT);
    rule.addSymbol(VAR_DECL_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 54: ForInit -> AssignExpr
    rule.setLeft(FOR_INIT);
    rule.addSymbol(ASSIGN_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 55: ForInit -> /* empty */
    rule.setLeft(FOR_INIT);
    rule.addSymbol(); // empty
    addProductionRule(rule);
    rule.reset();

    // Rule 56: ExprOpt -> Expr
    rule.setLeft(EXPR_OPT);
    rule.addSymbol(EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 57: ExprOpt -> /* empty */
    rule.setLeft(EXPR_OPT);
    rule.addSymbol(); // empty
    addProductionRule(rule);
    rule.reset();

    // Rule 58: ForUpdate -> AssignExpr
    rule.setLeft(FOR_UPDATE);
    rule.addSymbol(ASSIGN_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 59: ForUpdate -> /* empty */
    rule.setLeft(FOR_UPDATE);
    rule.addSymbol(); // empty
    addProductionRule(rule);
    rule.reset();

    // Rule 60: ReturnStmt -> KEYWORD_RET ExprOpt SEMICOLON
    rule.setLeft(RETURN_STMT);
    rule.addSymbol(KEYWORD_RET).addSymbol(EXPR_OPT).addSymbol(SEMICOLON);
    addProductionRule(rule);
    rule.reset();

    // Rule 61: ExprStmt -> Expr SEMICOLON
    rule.setLeft(EXPR_STMT);
    rule.addSymbol(EXPR).addSymbol(SEMICOLON);
    addProductionRule(rule);
    rule.reset();

    // Rule 62: ExprList -> Expr ExprTail
    rule.setLeft(EXPR_LIST);
    rule.addSymbol(EXPR).addSymbol(EXPR_TAIL);
    addProductionRule(rule);
    rule.reset();

    // Rule 63: ExprList -> /* empty */
    rule.setLeft(EXPR_LIST);
    rule.addSymbol(); // empty
    addProductionRule(rule);
    rule.reset();

    // Rule 64: ExprTail -> COMMA Expr ExprTail
    rule.setLeft(EXPR_TAIL);
    rule.addSymbol(COMMA).addSymbol(EXPR).addSymbol(EXPR_TAIL);
    addProductionRule(rule);
    rule.reset();

    // Rule 65: ExprTail -> /* empty */
    rule.setLeft(EXPR_TAIL);
    rule.addSymbol(); // empty
    addProductionRule(rule);
    rule.reset();

    // Rule 66: Expr -> UnaryExpr RelOpTail
    rule.setLeft(EXPR);
    rule.addSymbol(UNARY_EXPR).addSymbol(REL_OP_TAIL);
    addProductionRule(rule);
    rule.reset();

    // Rule 67: Expr -> PointerRefExpr
    rule.setLeft(EXPR);
    rule.addSymbol(POINTER_REF_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 68: RelOpTail -> RelOp UnaryExpr RelOpTail
    rule.setLeft(REL_OP_TAIL);
    rule.addSymbol(REL_OP).addSymbol(UNARY_EXPR).addSymbol(REL_OP_TAIL);
    addProductionRule(rule);
    rule.reset();

    // Rule 69: RelOpTail -> /* empty */
    rule.setLeft(REL_OP_TAIL);
    rule.addSymbol(); // empty
    addProductionRule(rule);
    rule.reset();

    // Rule 70: RelOp -> LESS_THAN
    rule.setLeft(REL_OP);
    rule.addSymbol(LESS_THAN);
    addProductionRule(rule);
    rule.reset();

    // Rule 71: RelOp -> GREATER_THAN
    rule.setLeft(REL_OP);
    rule.addSymbol(GREATER_THAN);
    addProductionRule(rule);
    rule.reset();

    // Rule 72: RelOp -> LESS_THAN_EQUALS
    rule.setLeft(REL_OP);
    rule.addSymbol(LESS_THAN_EQUALS);
    addProductionRule(rule);
    rule.reset();

    // Rule 73: RelOp -> GREATER_THAN_EQUALS
    rule.setLeft(REL_OP);
    rule.addSymbol(GREATER_THAN_EQUALS);
    addProductionRule(rule);
    rule.reset();

    // Rule 74: RelOp -> EQUALS_EQUALS
    rule.setLeft(REL_OP);
    rule.addSymbol(EQUALS_EQUALS);
    addProductionRule(rule);
    rule.reset();

    // Rule 75: RelOp -> BANG_EQUALS
    rule.setLeft(REL_OP);
    rule.addSymbol(BANG_EQUALS);
    addProductionRule(rule);
    rule.reset();

    // Rule 76: UnaryExpr -> UnaryOp UnaryExpr
    rule.setLeft(UNARY_EXPR);
    rule.addSymbol(UNARY_OP).addSymbol(UNARY_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 77: UnaryExpr -> PostIncrement
    rule.setLeft(UNARY_EXPR);
    rule.addSymbol(POST_INCREMENT);
    addProductionRule(rule);
    rule.reset();

    // Rule 78: UnaryExpr -> PreIncrement
    rule.setLeft(UNARY_EXPR);
    rule.addSymbol(PRE_INCREMENT);
    addProductionRule(rule);
    rule.reset();

    // Rule 79: UnaryExpr -> SimpleExpr
    rule.setLeft(UNARY_EXPR);
    rule.addSymbol(SIMPLE_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 80: PointerRefExpr -> AMPERSAND IDENTIFIER
    rule.setLeft(POINTER_REF_EXPR);
    rule.addSymbol(AMPERSAND).addSymbol(IDENTIFIER);
    addProductionRule(rule);
    rule.reset();

    // Rule 81: PointerRefExpr -> STAR IDENTIFIER
    rule.setLeft(POINTER_REF_EXPR);
    rule.addSymbol(STAR).addSymbol(IDENTIFIER);
    addProductionRule(rule);
    rule.reset();

    // Rule 82: PostIncrement -> IDENTIFIER PLUS_PLUS
    rule.setLeft(POST_INCREMENT);
    rule.addSymbol(IDENTIFIER).addSymbol(PLUS_PLUS);
    addProductionRule(rule);
    rule.reset();

    // Rule 83: PostIncrement -> IDENTIFIER MINUS_MINUS
    rule.setLeft(POST_INCREMENT);
    rule.addSymbol(IDENTIFIER).addSymbol(MINUS_MINUS);
    addProductionRule(rule);
    rule.reset();

    // Rule 84: PreIncrement -> PLUS_PLUS IDENTIFIER
    rule.setLeft(PRE_INCREMENT);
    rule.addSymbol(PLUS_PLUS).addSymbol(IDENTIFIER);
    addProductionRule(rule);
    rule.reset();

    // Rule 85: PreIncrement -> MINUS_MINUS IDENTIFIER
    rule.setLeft(PRE_INCREMENT);
    rule.addSymbol(MINUS_MINUS).addSymbol(IDENTIFIER);
    addProductionRule(rule);
    rule.reset();

    // Rule 86: UnaryOp -> MINUS
    rule.setLeft(UNARY_OP);
    rule.addSymbol(MINUS);
    addProductionRule(rule);
    rule.reset();

    // Rule 87: UnaryOp -> BANG
    rule.setLeft(UNARY_OP);
    rule.addSymbol(BANG);
    addProductionRule(rule);
    rule.reset();

    // Rule 88: SimpleExpr -> Term AddOpTail
    rule.setLeft(SIMPLE_EXPR);
    rule.addSymbol(TERM).addSymbol(ADD_OP_TAIL);
    addProductionRule(rule);
    rule.reset();

    // Rule 89: AddOpTail -> AddOp Term AddOpTail
    rule.setLeft(ADD_OP_TAIL);
    rule.addSymbol(ADD_OP).addSymbol(TERM).addSymbol(ADD_OP_TAIL);
    addProductionRule(rule);
    rule.reset();

    // Rule 90: AddOpTail -> /* empty */
    rule.setLeft(ADD_OP_TAIL);
    rule.addSymbol(); // empty
    addProductionRule(rule);
    rule.reset();

    // Rule 91: AddOp -> PLUS
    rule.setLeft(ADD_OP);
    rule.addSymbol(PLUS);
    addProductionRule(rule);
    rule.reset();

    // Rule 92: AddOp -> MINUS
    rule.setLeft(ADD_OP);
    rule.addSymbol(MINUS);
    addProductionRule(rule);
    rule.reset();

    // Rule 93: AddOp -> PIPE
    rule.setLeft(ADD_OP);
    rule.addSymbol(PIPE);
    addProductionRule(rule);
    rule.reset();

    // Rule 94: AddOp -> CARET
    rule.setLeft(ADD_OP);
    rule.addSymbol(CARET);
    addProductionRule(rule);
    rule.reset();

    // Rule 95: AddOp -> PIPE_PIPE
    rule.setLeft(ADD_OP);
    rule.addSymbol(PIPE_PIPE);
    addProductionRule(rule);
    rule.reset();

    // Rule 96: Term -> Factor MulOpTail
    rule.setLeft(TERM);
    rule.addSymbol(FACTOR).addSymbol(MUL_OP_TAIL);
    addProductionRule(rule);
    rule.reset();

    // Rule 97: MulOpTail -> MulOp Factor MulOpTail
    rule.setLeft(MUL_OP_TAIL);
    rule.addSymbol(MUL_OP).addSymbol(FACTOR).addSymbol(MUL_OP_TAIL);
    addProductionRule(rule);
    rule.reset();

    // Rule 98: MulOpTail -> /* empty */
    rule.setLeft(MUL_OP_TAIL);
    rule.addSymbol(); // empty
    addProductionRule(rule);
    rule.reset();

    // Rule 99: MulOp -> STAR
    rule.setLeft(MUL_OP);
    rule.addSymbol(STAR);
    addProductionRule(rule);
    rule.reset();

    // Rule 100: MulOp -> SLASH
    rule.setLeft(MUL_OP);
    rule.addSymbol(SLASH);
    addProductionRule(rule);
    rule.reset();

    // Rule 101: MulOp -> AMPERSAND
    rule.setLeft(MUL_OP);
    rule.addSymbol(AMPERSAND);
    addProductionRule(rule);
    rule.reset();

    // Rule 102: MulOp -> AMPERSAND_AMPERSAND
    rule.setLeft(MUL_OP);
    rule.addSymbol(AMPERSAND_AMPERSAND);
    addProductionRule(rule);
    rule.reset();

    // Rule 103: Factor -> OPEN_PAREN Expr CLOSED_PAREN
    rule.setLeft(FACTOR);
    rule.addSymbol(OPEN_PAREN).addSymbol(EXPR).addSymbol(CLOSED_PAREN);
    addProductionRule(rule);
    rule.reset();

    // Rule 104: Factor -> IDENTIFIER
    rule.setLeft(FACTOR);
    rule.addSymbol(IDENTIFIER);
    addProductionRule(rule);
    rule.reset();

    // Rule 105: Factor -> INTEGER_LITERAL
    rule.setLeft(FACTOR);
    rule.addSymbol(INTEGER_LITERAL);
    addProductionRule(rule);
    rule.reset();

    // Rule 106: Factor -> FLOAT_LITERAL
    rule.setLeft(FACTOR);
    rule.addSymbol(FLOAT_LITERAL);
    addProductionRule(rule);
    rule.reset();

    // Rule 107: Factor -> CHAR_LITERAL
    rule.setLeft(FACTOR);
    rule.addSymbol(CHAR_LITERAL);
    addProductionRule(rule);
    rule.reset();

    // Rule 108: Factor -> IDENTIFIER OPEN_PAREN ExprList CLOSED_PAREN
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
    _actionTable.addDefault(20, {REDUCE, 14}); // TypeTail -> STAR

    // State 21
    _actionTable.addDefault(21, {REDUCE, 9}); // Type -> BaseType TypeTail

    // State 22
    _actionTable.add(22, KEYWORD_INT, {SHIFT, 8});
    _actionTable.add(22, KEYWORD_FLOAT, {SHIFT, 9});
    _actionTable.add(22, KEYWORD_CHAR, {SHIFT, 10});
    _gotoTable.add(22, TYPE, 25);
    _gotoTable.add(22, BASE_TYPE, 14);

    // State 23
    _actionTable.add(23, COMMA, {SHIFT, 16});
    _actionTable.addDefault(23, {REDUCE, 7}); // ParamTail -> /* empty */
    _gotoTable.add(23, PARAM_TAIL, 26);

    // State 24
    _actionTable.add(24, CLOSED_BRACKET, {SHIFT, 27});

    // State 25
    _actionTable.add(25, OPEN_CURLY, {SHIFT, 28});

    // State 26
    _actionTable.addDefault(26, {REDUCE, 6}); // ParamTail -> COMMA Param ParamTail

    // State 27
    _actionTable.addDefault(27, {REDUCE, 13}); // TypeTail -> OPEN_BRACKET INTEGER_LITERAL CLOSED_BRACKET

    // State 28
    _actionTable.add(28, IDENTIFIER, {SHIFT, 29});
    _actionTable.add(28, OPEN_PAREN, {SHIFT, 30});
    _actionTable.add(28, KEYWORD_INT, {SHIFT, 8});
    _actionTable.add(28, KEYWORD_FLOAT, {SHIFT, 9});
    _actionTable.add(28, KEYWORD_CHAR, {SHIFT, 10});
    _actionTable.add(28, STAR, {SHIFT, 31});
    _actionTable.add(28, KEYWORD_IF, {SHIFT, 32});
    _actionTable.add(28, KEYWORD_WHILE, {SHIFT, 33});
    _actionTable.add(28, KEYWORD_FOR, {SHIFT, 34});
    _actionTable.add(28, KEYWORD_RET, {SHIFT, 35});
    _actionTable.add(28, MINUS, {SHIFT, 36});
    _actionTable.add(28, BANG, {SHIFT, 37});
    _actionTable.add(28, AMPERSAND, {SHIFT, 38});
    _actionTable.add(28, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(28, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(28, CHAR_LITERAL, {SHIFT, 41});
    _actionTable.add(28, PLUS_PLUS, {SHIFT, 42});
    _actionTable.add(28, MINUS_MINUS, {SHIFT, 43});
    _actionTable.addDefault(28, {REDUCE, 17}); // StmtList -> /* empty */
    _gotoTable.add(28, TYPE, 44);
    _gotoTable.add(28, BASE_TYPE, 14);
    _gotoTable.add(28, STMT_LIST, 45);
    _gotoTable.add(28, STMT, 46);
    _gotoTable.add(28, VAR_DECL_STMT, 47);
    _gotoTable.add(28, VAR_DECL_EXPR, 48);
    _gotoTable.add(28, ASSIGN_STMT, 49);
    _gotoTable.add(28, ASSIGN_EXPR, 50);
    _gotoTable.add(28, ASSIGN_TARGET, 51);
    _gotoTable.add(28, IF_STMT, 52);
    _gotoTable.add(28, WHILE_STMT, 53);
    _gotoTable.add(28, FOR_STMT, 54);
    _gotoTable.add(28, RETURN_STMT, 55);
    _gotoTable.add(28, EXPR_STMT, 56);
    _gotoTable.add(28, EXPR, 57);
    _gotoTable.add(28, UNARY_EXPR, 58);
    _gotoTable.add(28, POINTER_REF_EXPR, 59);
    _gotoTable.add(28, POST_INCREMENT, 60);
    _gotoTable.add(28, PRE_INCREMENT, 61);
    _gotoTable.add(28, UNARY_OP, 62);
    _gotoTable.add(28, SIMPLE_EXPR, 63);
    _gotoTable.add(28, TERM, 64);
    _gotoTable.add(28, FACTOR, 65);

    // State 29
    _actionTable.add(29, OPEN_PAREN, {SHIFT, 66});
    _actionTable.add(29, OPEN_BRACKET, {SHIFT, 67});
    _actionTable.add(29, PLUS_PLUS, {SHIFT, 68});
    _actionTable.add(29, MINUS_MINUS, {SHIFT, 69});
    _actionTable.add(29, EQUALS, {REDUCE, 35}); // AssignTarget -> IDENTIFIER
    _actionTable.add(29, PLUS_EQUALS, {REDUCE, 35});
    _actionTable.add(29, MINUS_EQUALS, {REDUCE, 35});
    _actionTable.add(29, SLASH_EQUALS, {REDUCE, 35});
    _actionTable.add(29, STAR_EQUALS, {REDUCE, 35});
    _actionTable.add(29, AMPERSAND_EQUALS, {REDUCE, 35});
    _actionTable.add(29, PIPE_EQUALS, {REDUCE, 35});
    _actionTable.add(29, CARET_EQUALS, {REDUCE, 35});
    _actionTable.add(29, TILDE_EQUALS, {REDUCE, 35});
    _actionTable.addDefault(29, {REDUCE, 104}); // Factor -> IDENTIFIER

    // State 30
    _actionTable.add(30, IDENTIFIER, {SHIFT, 70});
    _actionTable.add(30, OPEN_PAREN, {SHIFT, 30});
    _actionTable.add(30, STAR, {SHIFT, 71});
    _actionTable.add(30, MINUS, {SHIFT, 36});
    _actionTable.add(30, BANG, {SHIFT, 37});
    _actionTable.add(30, AMPERSAND, {SHIFT, 38});
    _actionTable.add(30, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(30, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(30, CHAR_LITERAL, {SHIFT, 41});
    _actionTable.add(30, PLUS_PLUS, {SHIFT, 42});
    _actionTable.add(30, MINUS_MINUS, {SHIFT, 43});
    _gotoTable.add(30, EXPR, 72);
    _gotoTable.add(30, UNARY_EXPR, 58);
    _gotoTable.add(30, POINTER_REF_EXPR, 59);
    _gotoTable.add(30, POST_INCREMENT, 60);
    _gotoTable.add(30, PRE_INCREMENT, 61);
    _gotoTable.add(30, UNARY_OP, 62);
    _gotoTable.add(30, SIMPLE_EXPR, 63);
    _gotoTable.add(30, TERM, 64);
    _gotoTable.add(30, FACTOR, 65);

    // State 31
    _actionTable.add(31, IDENTIFIER, {SHIFT, 73});

    // State 32
    _actionTable.add(32, OPEN_PAREN, {SHIFT, 74});

    // State 33
    _actionTable.add(33, OPEN_PAREN, {SHIFT, 75});

    // State 34
    _actionTable.add(34, OPEN_PAREN, {SHIFT, 76});

    // State 35
    _actionTable.add(35, IDENTIFIER, {SHIFT, 70});
    _actionTable.add(35, OPEN_PAREN, {SHIFT, 30});
    _actionTable.add(35, STAR, {SHIFT, 71});
    _actionTable.add(35, MINUS, {SHIFT, 36});
    _actionTable.add(35, BANG, {SHIFT, 37});
    _actionTable.add(35, AMPERSAND, {SHIFT, 38});
    _actionTable.add(35, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(35, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(35, CHAR_LITERAL, {SHIFT, 41});
    _actionTable.add(35, PLUS_PLUS, {SHIFT, 42});
    _actionTable.add(35, MINUS_MINUS, {SHIFT, 43});
    _actionTable.addDefault(35, {REDUCE, 57}); // ExprOpt -> /* empty */
    _gotoTable.add(35, EXPR_OPT, 77);
    _gotoTable.add(35, EXPR, 78);
    _gotoTable.add(35, UNARY_EXPR, 58);
    _gotoTable.add(35, POINTER_REF_EXPR, 59);
    _gotoTable.add(35, POST_INCREMENT, 60);
    _gotoTable.add(35, PRE_INCREMENT, 61);
    _gotoTable.add(35, UNARY_OP, 62);
    _gotoTable.add(35, SIMPLE_EXPR, 63);
    _gotoTable.add(35, TERM, 64);
    _gotoTable.add(35, FACTOR, 65);

    // State 36
    _actionTable.addDefault(36, {REDUCE, 86}); // UnaryOp -> MINUS

    // State 37
    _actionTable.addDefault(37, {REDUCE, 87}); // UnaryOp -> BANG

    // State 38
    _actionTable.add(38, IDENTIFIER, {SHIFT, 79});

    // State 39
    _actionTable.addDefault(39, {REDUCE, 105}); // Factor -> INTEGER_LITERAL

    // State 40
    _actionTable.addDefault(40, {REDUCE, 106}); // Factor -> FLOAT_LITERAL

    // State 41
    _actionTable.addDefault(41, {REDUCE, 107}); // Factor -> CHAR_LITERAL

    // State 42
    _actionTable.add(42, IDENTIFIER, {SHIFT, 80});

    // State 43
    _actionTable.add(43, IDENTIFIER, {SHIFT, 81});

    // State 44
    _actionTable.add(44, IDENTIFIER, {SHIFT, 82});

    // State 45
    _actionTable.add(45, CLOSED_CURLY, {SHIFT, 83});

    // State 46
    _actionTable.add(46, IDENTIFIER, {SHIFT, 29});
    _actionTable.add(46, OPEN_PAREN, {SHIFT, 30});
    _actionTable.add(46, KEYWORD_INT, {SHIFT, 8});
    _actionTable.add(46, KEYWORD_FLOAT, {SHIFT, 9});
    _actionTable.add(46, KEYWORD_CHAR, {SHIFT, 10});
    _actionTable.add(46, STAR, {SHIFT, 31});
    _actionTable.add(46, KEYWORD_IF, {SHIFT, 32});
    _actionTable.add(46, KEYWORD_WHILE, {SHIFT, 33});
    _actionTable.add(46, KEYWORD_FOR, {SHIFT, 34});
    _actionTable.add(46, KEYWORD_RET, {SHIFT, 35});
    _actionTable.add(46, MINUS, {SHIFT, 36});
    _actionTable.add(46, BANG, {SHIFT, 37});
    _actionTable.add(46, AMPERSAND, {SHIFT, 38});
    _actionTable.add(46, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(46, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(46, CHAR_LITERAL, {SHIFT, 41});
    _actionTable.add(46, PLUS_PLUS, {SHIFT, 42});
    _actionTable.add(46, MINUS_MINUS, {SHIFT, 43});
    _actionTable.addDefault(46, {REDUCE, 17}); // StmtList -> /* empty */
    _gotoTable.add(46, TYPE, 44);
    _gotoTable.add(46, BASE_TYPE, 14);
    _gotoTable.add(46, STMT_LIST, 84);
    _gotoTable.add(46, STMT, 46);
    _gotoTable.add(46, VAR_DECL_STMT, 47);
    _gotoTable.add(46, VAR_DECL_EXPR, 48);
    _gotoTable.add(46, ASSIGN_STMT, 49);
    _gotoTable.add(46, ASSIGN_EXPR, 50);
    _gotoTable.add(46, ASSIGN_TARGET, 51);
    _gotoTable.add(46, IF_STMT, 52);
    _gotoTable.add(46, WHILE_STMT, 53);
    _gotoTable.add(46, FOR_STMT, 54);
    _gotoTable.add(46, RETURN_STMT, 55);
    _gotoTable.add(46, EXPR_STMT, 56);
    _gotoTable.add(46, EXPR, 57);
    _gotoTable.add(46, UNARY_EXPR, 58);
    _gotoTable.add(46, POINTER_REF_EXPR, 59);
    _gotoTable.add(46, POST_INCREMENT, 60);
    _gotoTable.add(46, PRE_INCREMENT, 61);
    _gotoTable.add(46, UNARY_OP, 62);
    _gotoTable.add(46, SIMPLE_EXPR, 63);
    _gotoTable.add(46, TERM, 64);
    _gotoTable.add(46, FACTOR, 65);

    // State 47
    _actionTable.addDefault(47, {REDUCE, 18}); // Stmt -> VarDeclStmt

    // State 48
    _actionTable.add(48, SEMICOLON, {SHIFT, 85});

    // State 49
    _actionTable.addDefault(49, {REDUCE, 19}); // Stmt -> AssignStmt

    // State 50
    _actionTable.add(50, SEMICOLON, {SHIFT, 86});

    // State 51
    _actionTable.add(51, EQUALS, {SHIFT, 87});
    _actionTable.add(51, PLUS_EQUALS, {SHIFT, 88});
    _actionTable.add(51, MINUS_EQUALS, {SHIFT, 89});
    _actionTable.add(51, SLASH_EQUALS, {SHIFT, 90});
    _actionTable.add(51, STAR_EQUALS, {SHIFT, 91});
    _actionTable.add(51, AMPERSAND_EQUALS, {SHIFT, 92});
    _actionTable.add(51, PIPE_EQUALS, {SHIFT, 93});
    _actionTable.add(51, CARET_EQUALS, {SHIFT, 94});
    _actionTable.add(51, TILDE_EQUALS, {SHIFT, 95});
    _gotoTable.add(51, ASSIGN_OP, 96);

    // State 52
    _actionTable.addDefault(52, {REDUCE, 20}); // Stmt -> IfStmt

    // State 53
    _actionTable.addDefault(53, {REDUCE, 21}); // Stmt -> WhileStmt

    // State 54
    _actionTable.addDefault(54, {REDUCE, 22}); // Stmt -> ForStmt

    // State 55
    _actionTable.addDefault(55, {REDUCE, 23}); // Stmt -> ReturnStmt

    // State 56
    _actionTable.addDefault(56, {REDUCE, 24}); // Stmt -> ExprStmt

    // State 57
    _actionTable.add(57, SEMICOLON, {SHIFT, 97});

    // State 58
    _actionTable.add(58, LESS_THAN, {SHIFT, 98});
    _actionTable.add(58, GREATER_THAN, {SHIFT, 99});
    _actionTable.add(58, LESS_THAN_EQUALS, {SHIFT, 100});
    _actionTable.add(58, GREATER_THAN_EQUALS, {SHIFT, 101});
    _actionTable.add(58, EQUALS_EQUALS, {SHIFT, 102});
    _actionTable.add(58, BANG_EQUALS, {SHIFT, 103});
    _actionTable.addDefault(58, {REDUCE, 69}); // RelOpTail -> /* empty */
    _gotoTable.add(58, REL_OP_TAIL, 104);
    _gotoTable.add(58, REL_OP, 105);

    // State 59
    _actionTable.addDefault(59, {REDUCE, 67}); // Expr -> PointerRefExpr

    // State 60
    _actionTable.addDefault(60, {REDUCE, 77}); // UnaryExpr -> PostIncrement

    // State 61
    _actionTable.addDefault(61, {REDUCE, 78}); // UnaryExpr -> PreIncrement

    // State 62
    _actionTable.add(62, IDENTIFIER, {SHIFT, 70});
    _actionTable.add(62, OPEN_PAREN, {SHIFT, 30});
    _actionTable.add(62, MINUS, {SHIFT, 36});
    _actionTable.add(62, BANG, {SHIFT, 37});
    _actionTable.add(62, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(62, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(62, CHAR_LITERAL, {SHIFT, 41});
    _actionTable.add(62, PLUS_PLUS, {SHIFT, 42});
    _actionTable.add(62, MINUS_MINUS, {SHIFT, 43});
    _gotoTable.add(62, UNARY_EXPR, 106);
    _gotoTable.add(62, POST_INCREMENT, 60);
    _gotoTable.add(62, PRE_INCREMENT, 61);
    _gotoTable.add(62, UNARY_OP, 62);
    _gotoTable.add(62, SIMPLE_EXPR, 63);
    _gotoTable.add(62, TERM, 64);
    _gotoTable.add(62, FACTOR, 65);

    // State 63
    _actionTable.addDefault(63, {REDUCE, 79}); // UnaryExpr -> SimpleExpr

    // State 64
    _actionTable.add(64, MINUS, {SHIFT, 107});
    _actionTable.add(64, PLUS, {SHIFT, 108});
    _actionTable.add(64, PIPE, {SHIFT, 109});
    _actionTable.add(64, CARET, {SHIFT, 110});
    _actionTable.add(64, PIPE_PIPE, {SHIFT, 111});
    _actionTable.addDefault(64, {REDUCE, 90}); // AddOpTail -> /* empty */
    _gotoTable.add(64, ADD_OP_TAIL, 112);
    _gotoTable.add(64, ADD_OP, 113);

    // State 65
    _actionTable.add(65, STAR, {SHIFT, 114});
    _actionTable.add(65, SLASH, {SHIFT, 115});
    _actionTable.add(65, AMPERSAND, {SHIFT, 116});
    _actionTable.add(65, AMPERSAND_AMPERSAND, {SHIFT, 117});
    _actionTable.addDefault(65, {REDUCE, 98}); // MulOpTail -> /* empty */
    _gotoTable.add(65, MUL_OP_TAIL, 118);
    _gotoTable.add(65, MUL_OP, 119);

    // State 66
    _actionTable.add(66, IDENTIFIER, {SHIFT, 70});
    _actionTable.add(66, OPEN_PAREN, {SHIFT, 30});
    _actionTable.add(66, STAR, {SHIFT, 71});
    _actionTable.add(66, MINUS, {SHIFT, 36});
    _actionTable.add(66, BANG, {SHIFT, 37});
    _actionTable.add(66, AMPERSAND, {SHIFT, 38});
    _actionTable.add(66, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(66, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(66, CHAR_LITERAL, {SHIFT, 41});
    _actionTable.add(66, PLUS_PLUS, {SHIFT, 42});
    _actionTable.add(66, MINUS_MINUS, {SHIFT, 43});
    _actionTable.addDefault(66, {REDUCE, 63}); // ExprList -> /* empty */
    _gotoTable.add(66, EXPR_LIST, 120);
    _gotoTable.add(66, EXPR, 121);
    _gotoTable.add(66, UNARY_EXPR, 58);
    _gotoTable.add(66, POINTER_REF_EXPR, 59);
    _gotoTable.add(66, POST_INCREMENT, 60);
    _gotoTable.add(66, PRE_INCREMENT, 61);
    _gotoTable.add(66, UNARY_OP, 62);
    _gotoTable.add(66, SIMPLE_EXPR, 63);
    _gotoTable.add(66, TERM, 64);
    _gotoTable.add(66, FACTOR, 65);

    // State 67
    _actionTable.add(67, IDENTIFIER, {SHIFT, 70});
    _actionTable.add(67, OPEN_PAREN, {SHIFT, 30});
    _actionTable.add(67, STAR, {SHIFT, 71});
    _actionTable.add(67, MINUS, {SHIFT, 36});
    _actionTable.add(67, BANG, {SHIFT, 37});
    _actionTable.add(67, AMPERSAND, {SHIFT, 38});
    _actionTable.add(67, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(67, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(67, CHAR_LITERAL, {SHIFT, 41});
    _actionTable.add(67, PLUS_PLUS, {SHIFT, 42});
    _actionTable.add(67, MINUS_MINUS, {SHIFT, 43});
    _gotoTable.add(67, EXPR, 122);
    _gotoTable.add(67, UNARY_EXPR, 58);
    _gotoTable.add(67, POINTER_REF_EXPR, 59);
    _gotoTable.add(67, POST_INCREMENT, 60);
    _gotoTable.add(67, PRE_INCREMENT, 61);
    _gotoTable.add(67, UNARY_OP, 62);
    _gotoTable.add(67, SIMPLE_EXPR, 63);
    _gotoTable.add(67, TERM, 64);
    _gotoTable.add(67, FACTOR, 65);

    // State 68
    _actionTable.addDefault(68, {REDUCE, 82}); // PostIncrement -> IDENTIFIER PLUS_PLUS

    // State 69
    _actionTable.addDefault(69, {REDUCE, 83}); // PostIncrement -> IDENTIFIER MINUS_MINUS

    // State 70
    _actionTable.add(70, OPEN_PAREN, {SHIFT, 66});
    _actionTable.add(70, PLUS_PLUS, {SHIFT, 68});
    _actionTable.add(70, MINUS_MINUS, {SHIFT, 69});
    _actionTable.addDefault(70, {REDUCE, 104}); // Factor -> IDENTIFIER

    // State 71
    _actionTable.add(71, IDENTIFIER, {SHIFT, 123});

    // State 72
    _actionTable.add(72, CLOSED_PAREN, {SHIFT, 124});

    // State 73
    _actionTable.add(73, CLOSED_PAREN, {REDUCE, 81}); // PointerRefExpr -> STAR IDENTIFIER
    _actionTable.add(73, SEMICOLON, {REDUCE, 81});
    _actionTable.addDefault(73, {REDUCE, 37}); // AssignTarget -> STAR IDENTIFIER

    // State 74
    _actionTable.add(74, IDENTIFIER, {SHIFT, 29});
    _actionTable.add(74, OPEN_PAREN, {SHIFT, 30});
    _actionTable.add(74, STAR, {SHIFT, 31});
    _actionTable.add(74, MINUS, {SHIFT, 36});
    _actionTable.add(74, BANG, {SHIFT, 37});
    _actionTable.add(74, AMPERSAND, {SHIFT, 38});
    _actionTable.add(74, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(74, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(74, CHAR_LITERAL, {SHIFT, 41});
    _actionTable.add(74, PLUS_PLUS, {SHIFT, 42});
    _actionTable.add(74, MINUS_MINUS, {SHIFT, 43});
    _gotoTable.add(74, ASSIGN_EXPR, 125);
    _gotoTable.add(74, ASSIGN_TARGET, 51);
    _gotoTable.add(74, CONDITION_OP, 126);
    _gotoTable.add(74, EXPR, 127);
    _gotoTable.add(74, UNARY_EXPR, 58);
    _gotoTable.add(74, POINTER_REF_EXPR, 59);
    _gotoTable.add(74, POST_INCREMENT, 60);
    _gotoTable.add(74, PRE_INCREMENT, 61);
    _gotoTable.add(74, UNARY_OP, 62);
    _gotoTable.add(74, SIMPLE_EXPR, 63);
    _gotoTable.add(74, TERM, 64);
    _gotoTable.add(74, FACTOR, 65);

    // State 75
    _actionTable.add(75, IDENTIFIER, {SHIFT, 29});
    _actionTable.add(75, OPEN_PAREN, {SHIFT, 30});
    _actionTable.add(75, STAR, {SHIFT, 31});
    _actionTable.add(75, MINUS, {SHIFT, 36});
    _actionTable.add(75, BANG, {SHIFT, 37});
    _actionTable.add(75, AMPERSAND, {SHIFT, 38});
    _actionTable.add(75, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(75, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(75, CHAR_LITERAL, {SHIFT, 41});
    _actionTable.add(75, PLUS_PLUS, {SHIFT, 42});
    _actionTable.add(75, MINUS_MINUS, {SHIFT, 43});
    _gotoTable.add(75, ASSIGN_EXPR, 125);
    _gotoTable.add(75, ASSIGN_TARGET, 51);
    _gotoTable.add(75, CONDITION_OP, 128);
    _gotoTable.add(75, EXPR, 127);
    _gotoTable.add(75, UNARY_EXPR, 58);
    _gotoTable.add(75, POINTER_REF_EXPR, 59);
    _gotoTable.add(75, POST_INCREMENT, 60);
    _gotoTable.add(75, PRE_INCREMENT, 61);
    _gotoTable.add(75, UNARY_OP, 62);
    _gotoTable.add(75, SIMPLE_EXPR, 63);
    _gotoTable.add(75, TERM, 64);
    _gotoTable.add(75, FACTOR, 65);

    // State 76
    _actionTable.add(76, IDENTIFIER, {SHIFT, 129});
    _actionTable.add(76, KEYWORD_INT, {SHIFT, 8});
    _actionTable.add(76, KEYWORD_FLOAT, {SHIFT, 9});
    _actionTable.add(76, KEYWORD_CHAR, {SHIFT, 10});
    _actionTable.add(76, STAR, {SHIFT, 130});
    _actionTable.addDefault(76, {REDUCE, 55}); // ForInit -> /* empty */
    _gotoTable.add(76, TYPE, 44);
    _gotoTable.add(76, BASE_TYPE, 14);
    _gotoTable.add(76, VAR_DECL_EXPR, 131);
    _gotoTable.add(76, ASSIGN_EXPR, 132);
    _gotoTable.add(76, ASSIGN_TARGET, 51);
    _gotoTable.add(76, FOR_INIT, 133);

    // State 77
    _actionTable.add(77, SEMICOLON, {SHIFT, 134});

    // State 78
    _actionTable.addDefault(78, {REDUCE, 56}); // ExprOpt -> Expr

    // State 79
    _actionTable.addDefault(79, {REDUCE, 80}); // PointerRefExpr -> AMPERSAND IDENTIFIER

    // State 80
    _actionTable.addDefault(80, {REDUCE, 84}); // PreIncrement -> PLUS_PLUS IDENTIFIER

    // State 81
    _actionTable.addDefault(81, {REDUCE, 85}); // PreIncrement -> MINUS_MINUS IDENTIFIER

    // State 82
    _actionTable.add(82, EQUALS, {SHIFT, 135});
    _actionTable.addDefault(82, {REDUCE, 30}); // InitOpt -> /* empty */
    _gotoTable.add(82, INIT_OPT, 136);

    // State 83
    _actionTable.addDefault(83, {REDUCE, 3}); // FunctionDecl -> KEYWORD_FN IDENTIFIER OPEN_PAREN ParamList CLOSED_PAREN RIGHT_ARROW Type OPEN_CURLY StmtList CLOSED_CURLY

    // State 84
    _actionTable.addDefault(84, {REDUCE, 16}); // StmtList -> Stmt StmtList

    // State 85
    _actionTable.addDefault(85, {REDUCE, 27}); // VarDeclStmt -> VarDeclExpr SEMICOLON

    // State 86
    _actionTable.addDefault(86, {REDUCE, 33}); // AssignStmt -> AssignExpr SEMICOLON

    // State 87
    _actionTable.addDefault(87, {REDUCE, 38}); // AssignOp -> EQUALS

    // State 88
    _actionTable.addDefault(88, {REDUCE, 39}); // AssignOp -> PLUS_EQUALS

    // State 89
    _actionTable.addDefault(89, {REDUCE, 40}); // AssignOp -> MINUS_EQUALS

    // State 90
    _actionTable.addDefault(90, {REDUCE, 41}); // AssignOp -> SLASH_EQUALS

    // State 91
    _actionTable.addDefault(91, {REDUCE, 42}); // AssignOp -> STAR_EQUALS

    // State 92
    _actionTable.addDefault(92, {REDUCE, 43}); // AssignOp -> AMPERSAND_EQUALS

    // State 93
    _actionTable.addDefault(93, {REDUCE, 44}); // AssignOp -> PIPE_EQUALS

    // State 94
    _actionTable.addDefault(94, {REDUCE, 45}); // AssignOp -> CARET_EQUALS

    // State 95
    _actionTable.addDefault(95, {REDUCE, 46}); // AssignOp -> TILDE_EQUALS

    // State 96
    _actionTable.add(96, IDENTIFIER, {SHIFT, 70});
    _actionTable.add(96, OPEN_PAREN, {SHIFT, 30});
    _actionTable.add(96, STAR, {SHIFT, 71});
    _actionTable.add(96, MINUS, {SHIFT, 36});
    _actionTable.add(96, BANG, {SHIFT, 37});
    _actionTable.add(96, AMPERSAND, {SHIFT, 38});
    _actionTable.add(96, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(96, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(96, CHAR_LITERAL, {SHIFT, 41});
    _actionTable.add(96, PLUS_PLUS, {SHIFT, 42});
    _actionTable.add(96, MINUS_MINUS, {SHIFT, 43});
    _gotoTable.add(96, EXPR, 137);
    _gotoTable.add(96, UNARY_EXPR, 58);
    _gotoTable.add(96, POINTER_REF_EXPR, 59);
    _gotoTable.add(96, POST_INCREMENT, 60);
    _gotoTable.add(96, PRE_INCREMENT, 61);
    _gotoTable.add(96, UNARY_OP, 62);
    _gotoTable.add(96, SIMPLE_EXPR, 63);
    _gotoTable.add(96, TERM, 64);
    _gotoTable.add(96, FACTOR, 65);

    // State 97
    _actionTable.addDefault(97, {REDUCE, 61}); // ExprStmt -> Expr SEMICOLON

    // State 98
    _actionTable.addDefault(98, {REDUCE, 70}); // RelOp -> LESS_THAN

    // State 99
    _actionTable.addDefault(99, {REDUCE, 71}); // RelOp -> GREATER_THAN

    // State 100
    _actionTable.addDefault(100, {REDUCE, 72}); // RelOp -> LESS_THAN_EQUALS

    // State 101
    _actionTable.addDefault(101, {REDUCE, 73}); // RelOp -> GREATER_THAN_EQUALS

    // State 102
    _actionTable.addDefault(102, {REDUCE, 74}); // RelOp -> EQUALS_EQUALS

    // State 103
    _actionTable.addDefault(103, {REDUCE, 75}); // RelOp -> BANG_EQUALS

    // State 104
    _actionTable.addDefault(104, {REDUCE, 66}); // Expr -> UnaryExpr RelOpTail

    // State 105
    _actionTable.add(105, IDENTIFIER, {SHIFT, 70});
    _actionTable.add(105, OPEN_PAREN, {SHIFT, 30});
    _actionTable.add(105, MINUS, {SHIFT, 36});
    _actionTable.add(105, BANG, {SHIFT, 37});
    _actionTable.add(105, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(105, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(105, CHAR_LITERAL, {SHIFT, 41});
    _actionTable.add(105, PLUS_PLUS, {SHIFT, 42});
    _actionTable.add(105, MINUS_MINUS, {SHIFT, 43});
    _gotoTable.add(105, UNARY_EXPR, 138);
    _gotoTable.add(105, POST_INCREMENT, 60);
    _gotoTable.add(105, PRE_INCREMENT, 61);
    _gotoTable.add(105, UNARY_OP, 62);
    _gotoTable.add(105, SIMPLE_EXPR, 63);
    _gotoTable.add(105, TERM, 64);
    _gotoTable.add(105, FACTOR, 65);

    // State 106
    _actionTable.addDefault(106, {REDUCE, 76}); // UnaryExpr -> UnaryOp UnaryExpr

    // State 107
    _actionTable.addDefault(107, {REDUCE, 92}); // AddOp -> MINUS

    // State 108
    _actionTable.addDefault(108, {REDUCE, 91}); // AddOp -> PLUS

    // State 109
    _actionTable.addDefault(109, {REDUCE, 93}); // AddOp -> PIPE

    // State 110
    _actionTable.addDefault(110, {REDUCE, 94}); // AddOp -> CARET

    // State 111
    _actionTable.addDefault(111, {REDUCE, 95}); // AddOp -> PIPE_PIPE

    // State 112
    _actionTable.addDefault(112, {REDUCE, 88}); // SimpleExpr -> Term AddOpTail

    // State 113
    _actionTable.add(113, IDENTIFIER, {SHIFT, 139});
    _actionTable.add(113, OPEN_PAREN, {SHIFT, 30});
    _actionTable.add(113, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(113, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(113, CHAR_LITERAL, {SHIFT, 41});
    _gotoTable.add(113, TERM, 140);
    _gotoTable.add(113, FACTOR, 65);

    // State 114
    _actionTable.addDefault(114, {REDUCE, 99}); // MulOp -> STAR

    // State 115
    _actionTable.addDefault(115, {REDUCE, 100}); // MulOp -> SLASH

    // State 116
    _actionTable.addDefault(116, {REDUCE, 101}); // MulOp -> AMPERSAND

    // State 117
    _actionTable.addDefault(117, {REDUCE, 102}); // MulOp -> AMPERSAND_AMPERSAND

    // State 118
    _actionTable.addDefault(118, {REDUCE, 96}); // Term -> Factor MulOpTail

    // State 119
    _actionTable.add(119, IDENTIFIER, {SHIFT, 139});
    _actionTable.add(119, OPEN_PAREN, {SHIFT, 30});
    _actionTable.add(119, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(119, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(119, CHAR_LITERAL, {SHIFT, 41});
    _gotoTable.add(119, FACTOR, 141);

    // State 120
    _actionTable.add(120, CLOSED_PAREN, {SHIFT, 142});

    // State 121
    _actionTable.add(121, COMMA, {SHIFT, 143});
    _actionTable.addDefault(121, {REDUCE, 65}); // ExprTail -> /* empty */
    _gotoTable.add(121, EXPR_TAIL, 144);

    // State 122
    _actionTable.add(122, CLOSED_BRACKET, {SHIFT, 145});

    // State 123
    _actionTable.addDefault(123, {REDUCE, 81}); // PointerRefExpr -> STAR IDENTIFIER

    // State 124
    _actionTable.addDefault(124, {REDUCE, 103}); // Factor -> OPEN_PAREN Expr CLOSED_PAREN

    // State 125
    _actionTable.addDefault(125, {REDUCE, 51}); // ConditionOp -> AssignExpr

    // State 126
    _actionTable.add(126, CLOSED_PAREN, {SHIFT, 146});

    // State 127
    _actionTable.addDefault(127, {REDUCE, 50}); // ConditionOp -> Expr

    // State 128
    _actionTable.add(128, CLOSED_PAREN, {SHIFT, 147});

    // State 129
    _actionTable.add(129, OPEN_BRACKET, {SHIFT, 67});
    _actionTable.addDefault(129, {REDUCE, 35}); // AssignTarget -> IDENTIFIER

    // State 130
    _actionTable.add(130, IDENTIFIER, {SHIFT, 148});

    // State 131
    _actionTable.addDefault(131, {REDUCE, 53}); // ForInit -> VarDeclExpr

    // State 132
    _actionTable.addDefault(132, {REDUCE, 54}); // ForInit -> AssignExpr

    // State 133
    _actionTable.add(133, SEMICOLON, {SHIFT, 149});

    // State 134
    _actionTable.addDefault(134, {REDUCE, 60}); // ReturnStmt -> KEYWORD_RET ExprOpt SEMICOLON

    // State 135
    _actionTable.add(135, IDENTIFIER, {SHIFT, 70});
    _actionTable.add(135, OPEN_PAREN, {SHIFT, 30});
    _actionTable.add(135, OPEN_CURLY, {SHIFT, 150});
    _actionTable.add(135, STAR, {SHIFT, 71});
    _actionTable.add(135, MINUS, {SHIFT, 36});
    _actionTable.add(135, BANG, {SHIFT, 37});
    _actionTable.add(135, AMPERSAND, {SHIFT, 38});
    _actionTable.add(135, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(135, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(135, CHAR_LITERAL, {SHIFT, 41});
    _actionTable.add(135, PLUS_PLUS, {SHIFT, 42});
    _actionTable.add(135, MINUS_MINUS, {SHIFT, 43});
    _gotoTable.add(135, ASSIGN_VALUE, 151);
    _gotoTable.add(135, EXPR, 152);
    _gotoTable.add(135, UNARY_EXPR, 58);
    _gotoTable.add(135, POINTER_REF_EXPR, 59);
    _gotoTable.add(135, POST_INCREMENT, 60);
    _gotoTable.add(135, PRE_INCREMENT, 61);
    _gotoTable.add(135, UNARY_OP, 62);
    _gotoTable.add(135, SIMPLE_EXPR, 63);
    _gotoTable.add(135, TERM, 64);
    _gotoTable.add(135, FACTOR, 65);

    // State 136
    _actionTable.addDefault(136, {REDUCE, 28}); // VarDeclExpr -> Type IDENTIFIER InitOpt

    // State 137
    _actionTable.addDefault(137, {REDUCE, 34}); // AssignExpr -> AssignTarget AssignOp Expr

    // State 138
    _actionTable.add(138, LESS_THAN, {SHIFT, 98});
    _actionTable.add(138, GREATER_THAN, {SHIFT, 99});
    _actionTable.add(138, LESS_THAN_EQUALS, {SHIFT, 100});
    _actionTable.add(138, GREATER_THAN_EQUALS, {SHIFT, 101});
    _actionTable.add(138, EQUALS_EQUALS, {SHIFT, 102});
    _actionTable.add(138, BANG_EQUALS, {SHIFT, 103});
    _actionTable.addDefault(138, {REDUCE, 69}); // RelOpTail -> /* empty */
    _gotoTable.add(138, REL_OP_TAIL, 153);
    _gotoTable.add(138, REL_OP, 105);

    // State 139
    _actionTable.add(139, OPEN_PAREN, {SHIFT, 66});
    _actionTable.addDefault(139, {REDUCE, 104}); // Factor -> IDENTIFIER

    // State 140
    _actionTable.add(140, MINUS, {SHIFT, 107});
    _actionTable.add(140, PLUS, {SHIFT, 108});
    _actionTable.add(140, PIPE, {SHIFT, 109});
    _actionTable.add(140, CARET, {SHIFT, 110});
    _actionTable.add(140, PIPE_PIPE, {SHIFT, 111});
    _actionTable.addDefault(140, {REDUCE, 90}); // AddOpTail -> /* empty */
    _gotoTable.add(140, ADD_OP_TAIL, 154);
    _gotoTable.add(140, ADD_OP, 113);

    // State 141
    _actionTable.add(141, STAR, {SHIFT, 114});
    _actionTable.add(141, SLASH, {SHIFT, 115});
    _actionTable.add(141, AMPERSAND, {SHIFT, 116});
    _actionTable.add(141, AMPERSAND_AMPERSAND, {SHIFT, 117});
    _actionTable.addDefault(141, {REDUCE, 98}); // MulOpTail -> /* empty */
    _gotoTable.add(141, MUL_OP_TAIL, 155);
    _gotoTable.add(141, MUL_OP, 119);

    // State 142
    _actionTable.addDefault(142, {REDUCE, 108}); // Factor -> IDENTIFIER OPEN_PAREN ExprList CLOSED_PAREN

    // State 143
    _actionTable.add(143, IDENTIFIER, {SHIFT, 70});
    _actionTable.add(143, OPEN_PAREN, {SHIFT, 30});
    _actionTable.add(143, STAR, {SHIFT, 71});
    _actionTable.add(143, MINUS, {SHIFT, 36});
    _actionTable.add(143, BANG, {SHIFT, 37});
    _actionTable.add(143, AMPERSAND, {SHIFT, 38});
    _actionTable.add(143, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(143, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(143, CHAR_LITERAL, {SHIFT, 41});
    _actionTable.add(143, PLUS_PLUS, {SHIFT, 42});
    _actionTable.add(143, MINUS_MINUS, {SHIFT, 43});
    _gotoTable.add(143, EXPR, 156);
    _gotoTable.add(143, UNARY_EXPR, 58);
    _gotoTable.add(143, POINTER_REF_EXPR, 59);
    _gotoTable.add(143, POST_INCREMENT, 60);
    _gotoTable.add(143, PRE_INCREMENT, 61);
    _gotoTable.add(143, UNARY_OP, 62);
    _gotoTable.add(143, SIMPLE_EXPR, 63);
    _gotoTable.add(143, TERM, 64);
    _gotoTable.add(143, FACTOR, 65);

    // State 144
    _actionTable.addDefault(144, {REDUCE, 62}); // ExprList -> Expr ExprTail

    // State 145
    _actionTable.addDefault(145, {REDUCE, 36}); // AssignTarget -> IDENTIFIER OPEN_BRACKET Expr CLOSED_BRACKET

    // State 146
    _actionTable.add(146, IDENTIFIER, {SHIFT, 29});
    _actionTable.add(146, OPEN_PAREN, {SHIFT, 30});
    _actionTable.add(146, OPEN_CURLY, {SHIFT, 157});
    _actionTable.add(146, KEYWORD_INT, {SHIFT, 8});
    _actionTable.add(146, KEYWORD_FLOAT, {SHIFT, 9});
    _actionTable.add(146, KEYWORD_CHAR, {SHIFT, 10});
    _actionTable.add(146, STAR, {SHIFT, 31});
    _actionTable.add(146, KEYWORD_IF, {SHIFT, 32});
    _actionTable.add(146, KEYWORD_WHILE, {SHIFT, 33});
    _actionTable.add(146, KEYWORD_FOR, {SHIFT, 34});
    _actionTable.add(146, KEYWORD_RET, {SHIFT, 35});
    _actionTable.add(146, MINUS, {SHIFT, 36});
    _actionTable.add(146, BANG, {SHIFT, 37});
    _actionTable.add(146, AMPERSAND, {SHIFT, 38});
    _actionTable.add(146, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(146, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(146, CHAR_LITERAL, {SHIFT, 41});
    _actionTable.add(146, PLUS_PLUS, {SHIFT, 42});
    _actionTable.add(146, MINUS_MINUS, {SHIFT, 43});
    _gotoTable.add(146, TYPE, 44);
    _gotoTable.add(146, BASE_TYPE, 14);
    _gotoTable.add(146, STMT, 158);
    _gotoTable.add(146, BODY, 159);
    _gotoTable.add(146, VAR_DECL_STMT, 47);
    _gotoTable.add(146, VAR_DECL_EXPR, 48);
    _gotoTable.add(146, ASSIGN_STMT, 49);
    _gotoTable.add(146, ASSIGN_EXPR, 50);
    _gotoTable.add(146, ASSIGN_TARGET, 51);
    _gotoTable.add(146, IF_STMT, 52);
    _gotoTable.add(146, WHILE_STMT, 53);
    _gotoTable.add(146, FOR_STMT, 54);
    _gotoTable.add(146, RETURN_STMT, 55);
    _gotoTable.add(146, EXPR_STMT, 56);
    _gotoTable.add(146, EXPR, 57);
    _gotoTable.add(146, UNARY_EXPR, 58);
    _gotoTable.add(146, POINTER_REF_EXPR, 59);
    _gotoTable.add(146, POST_INCREMENT, 60);
    _gotoTable.add(146, PRE_INCREMENT, 61);
    _gotoTable.add(146, UNARY_OP, 62);
    _gotoTable.add(146, SIMPLE_EXPR, 63);
    _gotoTable.add(146, TERM, 64);
    _gotoTable.add(146, FACTOR, 65);

    // State 147
    _actionTable.add(147, IDENTIFIER, {SHIFT, 29});
    _actionTable.add(147, OPEN_PAREN, {SHIFT, 30});
    _actionTable.add(147, OPEN_CURLY, {SHIFT, 157});
    _actionTable.add(147, KEYWORD_INT, {SHIFT, 8});
    _actionTable.add(147, KEYWORD_FLOAT, {SHIFT, 9});
    _actionTable.add(147, KEYWORD_CHAR, {SHIFT, 10});
    _actionTable.add(147, STAR, {SHIFT, 31});
    _actionTable.add(147, KEYWORD_IF, {SHIFT, 32});
    _actionTable.add(147, KEYWORD_WHILE, {SHIFT, 33});
    _actionTable.add(147, KEYWORD_FOR, {SHIFT, 34});
    _actionTable.add(147, KEYWORD_RET, {SHIFT, 35});
    _actionTable.add(147, MINUS, {SHIFT, 36});
    _actionTable.add(147, BANG, {SHIFT, 37});
    _actionTable.add(147, AMPERSAND, {SHIFT, 38});
    _actionTable.add(147, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(147, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(147, CHAR_LITERAL, {SHIFT, 41});
    _actionTable.add(147, PLUS_PLUS, {SHIFT, 42});
    _actionTable.add(147, MINUS_MINUS, {SHIFT, 43});
    _gotoTable.add(147, TYPE, 44);
    _gotoTable.add(147, BASE_TYPE, 14);
    _gotoTable.add(147, STMT, 158);
    _gotoTable.add(147, BODY, 160);
    _gotoTable.add(147, VAR_DECL_STMT, 47);
    _gotoTable.add(147, VAR_DECL_EXPR, 48);
    _gotoTable.add(147, ASSIGN_STMT, 49);
    _gotoTable.add(147, ASSIGN_EXPR, 50);
    _gotoTable.add(147, ASSIGN_TARGET, 51);
    _gotoTable.add(147, IF_STMT, 52);
    _gotoTable.add(147, WHILE_STMT, 53);
    _gotoTable.add(147, FOR_STMT, 54);
    _gotoTable.add(147, RETURN_STMT, 55);
    _gotoTable.add(147, EXPR_STMT, 56);
    _gotoTable.add(147, EXPR, 57);
    _gotoTable.add(147, UNARY_EXPR, 58);
    _gotoTable.add(147, POINTER_REF_EXPR, 59);
    _gotoTable.add(147, POST_INCREMENT, 60);
    _gotoTable.add(147, PRE_INCREMENT, 61);
    _gotoTable.add(147, UNARY_OP, 62);
    _gotoTable.add(147, SIMPLE_EXPR, 63);
    _gotoTable.add(147, TERM, 64);
    _gotoTable.add(147, FACTOR, 65);

    // State 148
    _actionTable.addDefault(148, {REDUCE, 37}); // AssignTarget -> STAR IDENTIFIER

    // State 149
    _actionTable.add(149, IDENTIFIER, {SHIFT, 70});
    _actionTable.add(149, OPEN_PAREN, {SHIFT, 30});
    _actionTable.add(149, STAR, {SHIFT, 71});
    _actionTable.add(149, MINUS, {SHIFT, 36});
    _actionTable.add(149, BANG, {SHIFT, 37});
    _actionTable.add(149, AMPERSAND, {SHIFT, 38});
    _actionTable.add(149, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(149, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(149, CHAR_LITERAL, {SHIFT, 41});
    _actionTable.add(149, PLUS_PLUS, {SHIFT, 42});
    _actionTable.add(149, MINUS_MINUS, {SHIFT, 43});
    _actionTable.addDefault(149, {REDUCE, 57}); // ExprOpt -> /* empty */
    _gotoTable.add(149, EXPR_OPT, 161);
    _gotoTable.add(149, EXPR, 78);
    _gotoTable.add(149, UNARY_EXPR, 58);
    _gotoTable.add(149, POINTER_REF_EXPR, 59);
    _gotoTable.add(149, POST_INCREMENT, 60);
    _gotoTable.add(149, PRE_INCREMENT, 61);
    _gotoTable.add(149, UNARY_OP, 62);
    _gotoTable.add(149, SIMPLE_EXPR, 63);
    _gotoTable.add(149, TERM, 64);
    _gotoTable.add(149, FACTOR, 65);

    // State 150
    _actionTable.add(150, IDENTIFIER, {SHIFT, 70});
    _actionTable.add(150, OPEN_PAREN, {SHIFT, 30});
    _actionTable.add(150, STAR, {SHIFT, 71});
    _actionTable.add(150, MINUS, {SHIFT, 36});
    _actionTable.add(150, BANG, {SHIFT, 37});
    _actionTable.add(150, AMPERSAND, {SHIFT, 38});
    _actionTable.add(150, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(150, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(150, CHAR_LITERAL, {SHIFT, 41});
    _actionTable.add(150, PLUS_PLUS, {SHIFT, 42});
    _actionTable.add(150, MINUS_MINUS, {SHIFT, 43});
    _actionTable.addDefault(150, {REDUCE, 63}); // ExprList -> /* empty */
    _gotoTable.add(150, EXPR_LIST, 162);
    _gotoTable.add(150, EXPR, 121);
    _gotoTable.add(150, UNARY_EXPR, 58);
    _gotoTable.add(150, POINTER_REF_EXPR, 59);
    _gotoTable.add(150, POST_INCREMENT, 60);
    _gotoTable.add(150, PRE_INCREMENT, 61);
    _gotoTable.add(150, UNARY_OP, 62);
    _gotoTable.add(150, SIMPLE_EXPR, 63);
    _gotoTable.add(150, TERM, 64);
    _gotoTable.add(150, FACTOR, 65);

    // State 151
    _actionTable.addDefault(151, {REDUCE, 29}); // InitOpt -> EQUALS AssignValue

    // State 152
    _actionTable.addDefault(152, {REDUCE, 31}); // AssignValue -> Expr

    // State 153
    _actionTable.addDefault(153, {REDUCE, 68}); // RelOpTail -> RelOp UnaryExpr RelOpTail

    // State 154
    _actionTable.addDefault(154, {REDUCE, 89}); // AddOpTail -> AddOp Term AddOpTail

    // State 155
    _actionTable.addDefault(155, {REDUCE, 97}); // MulOpTail -> MulOp Factor MulOpTail

    // State 156
    _actionTable.add(156, COMMA, {SHIFT, 143});
    _actionTable.addDefault(156, {REDUCE, 65}); // ExprTail -> /* empty */
    _gotoTable.add(156, EXPR_TAIL, 163);

    // State 157
    _actionTable.add(157, IDENTIFIER, {SHIFT, 29});
    _actionTable.add(157, OPEN_PAREN, {SHIFT, 30});
    _actionTable.add(157, KEYWORD_INT, {SHIFT, 8});
    _actionTable.add(157, KEYWORD_FLOAT, {SHIFT, 9});
    _actionTable.add(157, KEYWORD_CHAR, {SHIFT, 10});
    _actionTable.add(157, STAR, {SHIFT, 31});
    _actionTable.add(157, KEYWORD_IF, {SHIFT, 32});
    _actionTable.add(157, KEYWORD_WHILE, {SHIFT, 33});
    _actionTable.add(157, KEYWORD_FOR, {SHIFT, 34});
    _actionTable.add(157, KEYWORD_RET, {SHIFT, 35});
    _actionTable.add(157, MINUS, {SHIFT, 36});
    _actionTable.add(157, BANG, {SHIFT, 37});
    _actionTable.add(157, AMPERSAND, {SHIFT, 38});
    _actionTable.add(157, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(157, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(157, CHAR_LITERAL, {SHIFT, 41});
    _actionTable.add(157, PLUS_PLUS, {SHIFT, 42});
    _actionTable.add(157, MINUS_MINUS, {SHIFT, 43});
    _actionTable.addDefault(157, {REDUCE, 17}); // StmtList -> /* empty */
    _gotoTable.add(157, TYPE, 44);
    _gotoTable.add(157, BASE_TYPE, 14);
    _gotoTable.add(157, STMT_LIST, 164);
    _gotoTable.add(157, STMT, 46);
    _gotoTable.add(157, VAR_DECL_STMT, 47);
    _gotoTable.add(157, VAR_DECL_EXPR, 48);
    _gotoTable.add(157, ASSIGN_STMT, 49);
    _gotoTable.add(157, ASSIGN_EXPR, 50);
    _gotoTable.add(157, ASSIGN_TARGET, 51);
    _gotoTable.add(157, IF_STMT, 52);
    _gotoTable.add(157, WHILE_STMT, 53);
    _gotoTable.add(157, FOR_STMT, 54);
    _gotoTable.add(157, RETURN_STMT, 55);
    _gotoTable.add(157, EXPR_STMT, 56);
    _gotoTable.add(157, EXPR, 57);
    _gotoTable.add(157, UNARY_EXPR, 58);
    _gotoTable.add(157, POINTER_REF_EXPR, 59);
    _gotoTable.add(157, POST_INCREMENT, 60);
    _gotoTable.add(157, PRE_INCREMENT, 61);
    _gotoTable.add(157, UNARY_OP, 62);
    _gotoTable.add(157, SIMPLE_EXPR, 63);
    _gotoTable.add(157, TERM, 64);
    _gotoTable.add(157, FACTOR, 65);

    // State 158
    _actionTable.addDefault(158, {REDUCE, 26}); // Body -> Stmt

    // State 159
    _actionTable.add(159, KEYWORD_ELSE, {SHIFT, 165});
    _actionTable.addDefault(159, {REDUCE, 47}); // IfStmt -> KEYWORD_IF OPEN_PAREN ConditionOp CLOSED_PAREN Body

    // State 160
    _actionTable.addDefault(160, {REDUCE, 49}); // WhileStmt -> KEYWORD_WHILE OPEN_PAREN ConditionOp CLOSED_PAREN Body

    // State 161
    _actionTable.add(161, SEMICOLON, {SHIFT, 166});

    // State 162
    _actionTable.add(162, CLOSED_CURLY, {SHIFT, 167});

    // State 163
    _actionTable.addDefault(163, {REDUCE, 64}); // ExprTail -> COMMA Expr ExprTail

    // State 164
    _actionTable.add(164, CLOSED_CURLY, {SHIFT, 168});

    // State 165
    _actionTable.add(165, IDENTIFIER, {SHIFT, 29});
    _actionTable.add(165, OPEN_PAREN, {SHIFT, 30});
    _actionTable.add(165, OPEN_CURLY, {SHIFT, 157});
    _actionTable.add(165, KEYWORD_INT, {SHIFT, 8});
    _actionTable.add(165, KEYWORD_FLOAT, {SHIFT, 9});
    _actionTable.add(165, KEYWORD_CHAR, {SHIFT, 10});
    _actionTable.add(165, STAR, {SHIFT, 31});
    _actionTable.add(165, KEYWORD_IF, {SHIFT, 32});
    _actionTable.add(165, KEYWORD_WHILE, {SHIFT, 33});
    _actionTable.add(165, KEYWORD_FOR, {SHIFT, 34});
    _actionTable.add(165, KEYWORD_RET, {SHIFT, 35});
    _actionTable.add(165, MINUS, {SHIFT, 36});
    _actionTable.add(165, BANG, {SHIFT, 37});
    _actionTable.add(165, AMPERSAND, {SHIFT, 38});
    _actionTable.add(165, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(165, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(165, CHAR_LITERAL, {SHIFT, 41});
    _actionTable.add(165, PLUS_PLUS, {SHIFT, 42});
    _actionTable.add(165, MINUS_MINUS, {SHIFT, 43});
    _gotoTable.add(165, TYPE, 44);
    _gotoTable.add(165, BASE_TYPE, 14);
    _gotoTable.add(165, STMT, 158);
    _gotoTable.add(165, BODY, 169);
    _gotoTable.add(165, VAR_DECL_STMT, 47);
    _gotoTable.add(165, VAR_DECL_EXPR, 48);
    _gotoTable.add(165, ASSIGN_STMT, 49);
    _gotoTable.add(165, ASSIGN_EXPR, 50);
    _gotoTable.add(165, ASSIGN_TARGET, 51);
    _gotoTable.add(165, IF_STMT, 52);
    _gotoTable.add(165, WHILE_STMT, 53);
    _gotoTable.add(165, FOR_STMT, 54);
    _gotoTable.add(165, RETURN_STMT, 55);
    _gotoTable.add(165, EXPR_STMT, 56);
    _gotoTable.add(165, EXPR, 57);
    _gotoTable.add(165, UNARY_EXPR, 58);
    _gotoTable.add(165, POINTER_REF_EXPR, 59);
    _gotoTable.add(165, POST_INCREMENT, 60);
    _gotoTable.add(165, PRE_INCREMENT, 61);
    _gotoTable.add(165, UNARY_OP, 62);
    _gotoTable.add(165, SIMPLE_EXPR, 63);
    _gotoTable.add(165, TERM, 64);
    _gotoTable.add(165, FACTOR, 65);

    // State 166
    _actionTable.add(166, IDENTIFIER, {SHIFT, 129});
    _actionTable.add(166, STAR, {SHIFT, 130});
    _actionTable.addDefault(166, {REDUCE, 59}); // ForUpdate -> /* empty */
    _gotoTable.add(166, ASSIGN_EXPR, 170);
    _gotoTable.add(166, ASSIGN_TARGET, 51);
    _gotoTable.add(166, FOR_UPDATE, 171);

    // State 167
    _actionTable.addDefault(167, {REDUCE, 32}); // AssignValue -> OPEN_CURLY ExprList CLOSED_CURLY

    // State 168
    _actionTable.addDefault(168, {REDUCE, 25}); // Body -> OPEN_CURLY StmtList CLOSED_CURLY

    // State 169
    _actionTable.addDefault(169, {REDUCE, 48}); // IfStmt -> KEYWORD_IF OPEN_PAREN ConditionOp CLOSED_PAREN Body KEYWORD_ELSE Body

    // State 170
    _actionTable.addDefault(170, {REDUCE, 58}); // ForUpdate -> AssignExpr

    // State 171
    _actionTable.add(171, CLOSED_PAREN, {SHIFT, 172});

    // State 172
    _actionTable.add(172, IDENTIFIER, {SHIFT, 29});
    _actionTable.add(172, OPEN_PAREN, {SHIFT, 30});
    _actionTable.add(172, OPEN_CURLY, {SHIFT, 157});
    _actionTable.add(172, KEYWORD_INT, {SHIFT, 8});
    _actionTable.add(172, KEYWORD_FLOAT, {SHIFT, 9});
    _actionTable.add(172, KEYWORD_CHAR, {SHIFT, 10});
    _actionTable.add(172, STAR, {SHIFT, 31});
    _actionTable.add(172, KEYWORD_IF, {SHIFT, 32});
    _actionTable.add(172, KEYWORD_WHILE, {SHIFT, 33});
    _actionTable.add(172, KEYWORD_FOR, {SHIFT, 34});
    _actionTable.add(172, KEYWORD_RET, {SHIFT, 35});
    _actionTable.add(172, MINUS, {SHIFT, 36});
    _actionTable.add(172, BANG, {SHIFT, 37});
    _actionTable.add(172, AMPERSAND, {SHIFT, 38});
    _actionTable.add(172, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(172, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(172, CHAR_LITERAL, {SHIFT, 41});
    _actionTable.add(172, PLUS_PLUS, {SHIFT, 42});
    _actionTable.add(172, MINUS_MINUS, {SHIFT, 43});
    _gotoTable.add(172, TYPE, 44);
    _gotoTable.add(172, BASE_TYPE, 14);
    _gotoTable.add(172, STMT, 158);
    _gotoTable.add(172, BODY, 173);
    _gotoTable.add(172, VAR_DECL_STMT, 47);
    _gotoTable.add(172, VAR_DECL_EXPR, 48);
    _gotoTable.add(172, ASSIGN_STMT, 49);
    _gotoTable.add(172, ASSIGN_EXPR, 50);
    _gotoTable.add(172, ASSIGN_TARGET, 51);
    _gotoTable.add(172, IF_STMT, 52);
    _gotoTable.add(172, WHILE_STMT, 53);
    _gotoTable.add(172, FOR_STMT, 54);
    _gotoTable.add(172, RETURN_STMT, 55);
    _gotoTable.add(172, EXPR_STMT, 56);
    _gotoTable.add(172, EXPR, 57);
    _gotoTable.add(172, UNARY_EXPR, 58);
    _gotoTable.add(172, POINTER_REF_EXPR, 59);
    _gotoTable.add(172, POST_INCREMENT, 60);
    _gotoTable.add(172, PRE_INCREMENT, 61);
    _gotoTable.add(172, UNARY_OP, 62);
    _gotoTable.add(172, SIMPLE_EXPR, 63);
    _gotoTable.add(172, TERM, 64);
    _gotoTable.add(172, FACTOR, 65);
    
    // State 173
    _actionTable.addDefault(173, {REDUCE, 52}); // ForStmt -> KEYWORD_FOR OPEN_PAREN ForInit SEMICOLON ExprOpt SEMICOLON ForUpdate CLOSED_PAREN Body
}
