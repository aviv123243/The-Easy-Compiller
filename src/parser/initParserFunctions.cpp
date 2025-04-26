#include "parser.hpp"
#include "productionRule/productionRule.hpp"
#include "../token/token.hpp"
void Parser::initProductionRules()
{
    productionRule rule;

    // Rule 0: $accept -> Program $end
    rule.setLeft(START);
    rule.addSymbol(PROGRAM).addSymbol(END_OF_FILE);
    addProductionRule(rule);
    rule.reset();

    // Rule 1: Program -> ε
    rule.setLeft(PROGRAM);
    rule.addSymbol(); // empty
    addProductionRule(rule);
    rule.reset();

    // Rule 2: Program -> Program FunctionDecl
    rule.setLeft(PROGRAM);
    rule.addSymbol(PROGRAM).addSymbol(FUNCTION_DECL);
    addProductionRule(rule);
    rule.reset();

    // Rule 3: FunctionDecl -> KEYWORD_FN IDENTIFIER OPEN_PAREN ParamList CLOSED_PAREN RIGHT_ARROW Type OPEN_CURLY StmtList CLOSED_CURLY
    rule.setLeft(FUNCTION_DECL);
    rule.addSymbol(KEYWORD_FN).addSymbol(IDENTIFIER).addSymbol(OPEN_PAREN)
        .addSymbol(PARAM_LIST).addSymbol(CLOSED_PAREN).addSymbol(RIGHT_ARROW)
        .addSymbol(TYPE).addSymbol(OPEN_CURLY).addSymbol(STMT_LIST).addSymbol(CLOSED_CURLY);
    addProductionRule(rule);
    rule.reset();

    // Rule 4: ParamList -> ε
    rule.setLeft(PARAM_LIST);
    rule.addSymbol(); // empty
    addProductionRule(rule);
    rule.reset();

    // Rule 5: ParamList -> ParamListNonEmpty
    rule.setLeft(PARAM_LIST);
    rule.addSymbol(PARAM_LIST_NON_EMPTY);
    addProductionRule(rule);
    rule.reset();

    // Rule 6: ParamListNonEmpty -> Param
    rule.setLeft(PARAM_LIST_NON_EMPTY);
    rule.addSymbol(PARAM);
    addProductionRule(rule);
    rule.reset();

    // Rule 7: ParamListNonEmpty -> ParamListNonEmpty COMMA Param
    rule.setLeft(PARAM_LIST_NON_EMPTY);
    rule.addSymbol(PARAM_LIST_NON_EMPTY).addSymbol(COMMA).addSymbol(PARAM);
    addProductionRule(rule);
    rule.reset();

    // Rule 8: Param -> Type IDENTIFIER
    rule.setLeft(PARAM);
    rule.addSymbol(TYPE).addSymbol(IDENTIFIER);
    addProductionRule(rule);
    rule.reset();

    // Rule 9: Type -> BaseType
    rule.setLeft(TYPE);
    rule.addSymbol(BASE_TYPE);
    addProductionRule(rule);
    rule.reset();

    // Rule 10: Type -> BaseType OPEN_BRACKET INTEGER_LITERAL CLOSED_BRACKET
    rule.setLeft(TYPE);
    rule.addSymbol(BASE_TYPE).addSymbol(OPEN_BRACKET).addSymbol(INTEGER_LITERAL).addSymbol(CLOSED_BRACKET);
    addProductionRule(rule);
    rule.reset();

    // Rule 11: Type -> BaseType STAR
    rule.setLeft(TYPE);
    rule.addSymbol(BASE_TYPE).addSymbol(STAR);
    addProductionRule(rule);
    rule.reset();

    // Rule 12: BaseType -> KEYWORD_INT
    rule.setLeft(BASE_TYPE);
    rule.addSymbol(KEYWORD_INT);
    addProductionRule(rule);
    rule.reset();

    // Rule 13: BaseType -> KEYWORD_FLOAT
    rule.setLeft(BASE_TYPE);
    rule.addSymbol(KEYWORD_FLOAT);
    addProductionRule(rule);
    rule.reset();

    // Rule 14: BaseType -> KEYWORD_CHAR
    rule.setLeft(BASE_TYPE);
    rule.addSymbol(KEYWORD_CHAR);
    addProductionRule(rule);
    rule.reset();

    // Rule 15: StmtList -> ε
    rule.setLeft(STMT_LIST);
    rule.addSymbol(); // empty
    addProductionRule(rule);
    rule.reset();

    // Rule 16: StmtList -> StmtList Stmt
    rule.setLeft(STMT_LIST);
    rule.addSymbol(STMT_LIST).addSymbol(STMT);
    addProductionRule(rule);
    rule.reset();

    // Rule 17: Stmt -> SimpleStmt SEMICOLON
    rule.setLeft(STMT);
    rule.addSymbol(SIMPLE_STMT).addSymbol(SEMICOLON);
    addProductionRule(rule);
    rule.reset();

    // Rule 18: Stmt -> OPEN_CURLY StmtList CLOSED_CURLY
    rule.setLeft(STMT);
    rule.addSymbol(OPEN_CURLY).addSymbol(STMT_LIST).addSymbol(CLOSED_CURLY);
    addProductionRule(rule);
    rule.reset();

    // Rule 19: Stmt -> IfStmt
    rule.setLeft(STMT);
    rule.addSymbol(IF_STMT);
    addProductionRule(rule);
    rule.reset();

    // Rule 20: Stmt -> WhileStmt
    rule.setLeft(STMT);
    rule.addSymbol(WHILE_STMT);
    addProductionRule(rule);
    rule.reset();

    // Rule 21: Stmt -> ForStmt
    rule.setLeft(STMT);
    rule.addSymbol(FOR_STMT);
    addProductionRule(rule);
    rule.reset();

    // Rule 22: SimpleStmt -> VarDeclExpr
    rule.setLeft(SIMPLE_STMT);
    rule.addSymbol(VAR_DECL_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 23: SimpleStmt -> AssignExpr
    rule.setLeft(SIMPLE_STMT);
    rule.addSymbol(ASSIGN_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 24: SimpleStmt -> IDENTIFIER OPEN_PAREN ExprList CLOSED_PAREN
    rule.setLeft(SIMPLE_STMT);
    rule.addSymbol(IDENTIFIER).addSymbol(OPEN_PAREN).addSymbol(EXPR_LIST).addSymbol(CLOSED_PAREN);
    addProductionRule(rule);
    rule.reset();

    // Rule 25: SimpleStmt -> KEYWORD_RET ExprOpt
    rule.setLeft(SIMPLE_STMT);
    rule.addSymbol(KEYWORD_RET).addSymbol(EXPR_OPT);
    addProductionRule(rule);
    rule.reset();

    // Rule 26: VarDeclExpr -> Type IDENTIFIER InitOpt
    rule.setLeft(VAR_DECL_EXPR);
    rule.addSymbol(TYPE).addSymbol(IDENTIFIER).addSymbol(INIT_OPT);
    addProductionRule(rule);
    rule.reset();

    // Rule 27: InitOpt -> ε
    rule.setLeft(INIT_OPT);
    rule.addSymbol(); // empty
    addProductionRule(rule);
    rule.reset();

    // Rule 28: InitOpt -> EQUALS AssignValue
    rule.setLeft(INIT_OPT);
    rule.addSymbol(EQUALS).addSymbol(ASSIGN_VALUE);
    addProductionRule(rule);
    rule.reset();

    // Rule 29: AssignValue -> Expr
    rule.setLeft(ASSIGN_VALUE);
    rule.addSymbol(EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 30: AssignValue -> OPEN_CURLY ExprList CLOSED_CURLY
    rule.setLeft(ASSIGN_VALUE);
    rule.addSymbol(OPEN_CURLY).addSymbol(EXPR_LIST).addSymbol(CLOSED_CURLY);
    addProductionRule(rule);
    rule.reset();

    // Rule 31: AssignExpr -> AssignTarget AssignOp Expr
    rule.setLeft(ASSIGN_EXPR);
    rule.addSymbol(ASSIGN_TARGET).addSymbol(ASSIGN_OP).addSymbol(EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 32: AssignTarget -> IDENTIFIER
    rule.setLeft(ASSIGN_TARGET);
    rule.addSymbol(IDENTIFIER);
    addProductionRule(rule);
    rule.reset();

    // Rule 33: AssignTarget -> IDENTIFIER OPEN_BRACKET Expr CLOSED_BRACKET
    rule.setLeft(ASSIGN_TARGET);
    rule.addSymbol(IDENTIFIER).addSymbol(OPEN_BRACKET).addSymbol(EXPR).addSymbol(CLOSED_BRACKET);
    addProductionRule(rule);
    rule.reset();

    // Rule 34: AssignTarget -> STAR IDENTIFIER
    rule.setLeft(ASSIGN_TARGET);
    rule.addSymbol(STAR).addSymbol(IDENTIFIER);
    addProductionRule(rule);
    rule.reset();

    // Rule 35: AssignOp -> EQUALS
    rule.setLeft(ASSIGN_OP);
    rule.addSymbol(EQUALS);
    addProductionRule(rule);
    rule.reset();

    // Rule 36: AssignOp -> PLUS_EQUALS
    rule.setLeft(ASSIGN_OP);
    rule.addSymbol(PLUS_EQUALS);
    addProductionRule(rule);
    rule.reset();

    // Rule 37: AssignOp -> MINUS_EQUALS
    rule.setLeft(ASSIGN_OP);
    rule.addSymbol(MINUS_EQUALS);
    addProductionRule(rule);
    rule.reset();

    // Rule 38: AssignOp -> SLASH_EQUALS
    rule.setLeft(ASSIGN_OP);
    rule.addSymbol(SLASH_EQUALS);
    addProductionRule(rule);
    rule.reset();

    // Rule 39: AssignOp -> STAR_EQUALS
    rule.setLeft(ASSIGN_OP);
    rule.addSymbol(STAR_EQUALS);
    addProductionRule(rule);
    rule.reset();

    // Rule 40: AssignOp -> AMPERSAND_EQUALS
    rule.setLeft(ASSIGN_OP);
    rule.addSymbol(AMPERSAND_EQUALS);
    addProductionRule(rule);
    rule.reset();

    // Rule 41: AssignOp -> PIPE_EQUALS
    rule.setLeft(ASSIGN_OP);
    rule.addSymbol(PIPE_EQUALS);
    addProductionRule(rule);
    rule.reset();

    // Rule 42: AssignOp -> CARET_EQUALS
    rule.setLeft(ASSIGN_OP);
    rule.addSymbol(CARET_EQUALS);
    addProductionRule(rule);
    rule.reset();

    // Rule 43: AssignOp -> TILDE_EQUALS
    rule.setLeft(ASSIGN_OP);
    rule.addSymbol(TILDE_EQUALS);
    addProductionRule(rule);
    rule.reset();

    // Rule 44: IfStmt -> KEYWORD_IF OPEN_PAREN ConditionOp CLOSED_PAREN Body
    rule.setLeft(IF_STMT);
    rule.addSymbol(KEYWORD_IF).addSymbol(OPEN_PAREN).addSymbol(CONDITION_OP)
        .addSymbol(CLOSED_PAREN).addSymbol(BODY);
    addProductionRule(rule);
    rule.reset();

    // Rule 45: IfStmt -> KEYWORD_IF OPEN_PAREN ConditionOp CLOSED_PAREN Body KEYWORD_ELSE Body
    rule.setLeft(IF_STMT);
    rule.addSymbol(KEYWORD_IF).addSymbol(OPEN_PAREN).addSymbol(CONDITION_OP)
        .addSymbol(CLOSED_PAREN).addSymbol(BODY).addSymbol(KEYWORD_ELSE).addSymbol(BODY);
    addProductionRule(rule);
    rule.reset();

    // Rule 46: WhileStmt -> KEYWORD_WHILE OPEN_PAREN ConditionOp CLOSED_PAREN Body
    rule.setLeft(WHILE_STMT);
    rule.addSymbol(KEYWORD_WHILE).addSymbol(OPEN_PAREN).addSymbol(CONDITION_OP)
        .addSymbol(CLOSED_PAREN).addSymbol(BODY);
    addProductionRule(rule);
    rule.reset();

    // Rule 47: ConditionOp -> Expr
    rule.setLeft(CONDITION_OP);
    rule.addSymbol(EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 48: ConditionOp -> AssignExpr
    rule.setLeft(CONDITION_OP);
    rule.addSymbol(ASSIGN_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 49: ForStmt -> KEYWORD_FOR OPEN_PAREN ForInit SEMICOLON ExprOpt SEMICOLON ForUpdate CLOSED_PAREN Body
    rule.setLeft(FOR_STMT);
    rule.addSymbol(KEYWORD_FOR).addSymbol(OPEN_PAREN).addSymbol(FOR_INIT).addSymbol(SEMICOLON)
        .addSymbol(EXPR_OPT).addSymbol(SEMICOLON).addSymbol(FOR_UPDATE).addSymbol(CLOSED_PAREN).addSymbol(BODY);
    addProductionRule(rule);
    rule.reset();

    // Rule 50: ForInit -> ε
    rule.setLeft(FOR_INIT);
    rule.addSymbol(); // empty
    addProductionRule(rule);
    rule.reset();

    // Rule 51: ForInit -> VarDeclExpr
    rule.setLeft(FOR_INIT);
    rule.addSymbol(VAR_DECL_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 52: ForInit -> AssignExpr
    rule.setLeft(FOR_INIT);
    rule.addSymbol(ASSIGN_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 53: ExprOpt -> ε
    rule.setLeft(EXPR_OPT);
    rule.addSymbol(); // empty
    addProductionRule(rule);
    rule.reset();

    // Rule 54: ExprOpt -> Expr
    rule.setLeft(EXPR_OPT);
    rule.addSymbol(EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 55: ForUpdate -> ε
    rule.setLeft(FOR_UPDATE);
    rule.addSymbol(); // empty
    addProductionRule(rule);
    rule.reset();

    // Rule 56: ForUpdate -> AssignExpr
    rule.setLeft(FOR_UPDATE);
    rule.addSymbol(ASSIGN_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 57: ForUpdate -> IncrementExpr
    rule.setLeft(FOR_UPDATE);
    rule.addSymbol(INCREMENT_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 58: Body -> OPEN_CURLY StmtList CLOSED_CURLY
    rule.setLeft(BODY);
    rule.addSymbol(OPEN_CURLY).addSymbol(STMT_LIST).addSymbol(CLOSED_CURLY);
    addProductionRule(rule);
    rule.reset();

    // Rule 59: Body -> SimpleStmt SEMICOLON
    rule.setLeft(BODY);
    rule.addSymbol(SIMPLE_STMT).addSymbol(SEMICOLON);
    addProductionRule(rule);
    rule.reset();

    // Rule 60: Body -> IfStmt
    rule.setLeft(BODY);
    rule.addSymbol(IF_STMT);
    addProductionRule(rule);
    rule.reset();

    // Rule 61: Body -> WhileStmt
    rule.setLeft(BODY);
    rule.addSymbol(WHILE_STMT);
    addProductionRule(rule);
    rule.reset();

    // Rule 62: Body -> ForStmt
    rule.setLeft(BODY);
    rule.addSymbol(FOR_STMT);
    addProductionRule(rule);
    rule.reset();

    // Rule 63: ExprList -> ε
    rule.setLeft(EXPR_LIST);
    rule.addSymbol(); // empty
    addProductionRule(rule);
    rule.reset();

    // Rule 64: ExprList -> ExprListNonEmpty
    rule.setLeft(EXPR_LIST);
    rule.addSymbol(EXPR_LIST_NON_EMPTY);
    addProductionRule(rule);
    rule.reset();

    // Rule 65: ExprListNonEmpty -> Expr
    rule.setLeft(EXPR_LIST_NON_EMPTY);
    rule.addSymbol(EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 66: ExprListNonEmpty -> ExprListNonEmpty COMMA Expr
    rule.setLeft(EXPR_LIST_NON_EMPTY);
    rule.addSymbol(EXPR_LIST_NON_EMPTY).addSymbol(COMMA).addSymbol(EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 67: Expr -> LogicalExpr
    rule.setLeft(EXPR);
    rule.addSymbol(LOGICAL_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 68: Expr -> AddressExpr
    rule.setLeft(EXPR);
    rule.addSymbol(ADDRESS_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 69: LogicalExpr -> RelationalExpr
    rule.setLeft(LOGICAL_EXPR);
    rule.addSymbol(RELATIONAL_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 70: LogicalExpr -> LogicalExpr PIPE_PIPE RelationalExpr
    rule.setLeft(LOGICAL_EXPR);
    rule.addSymbol(LOGICAL_EXPR).addSymbol(PIPE_PIPE).addSymbol(RELATIONAL_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 71: LogicalExpr -> LogicalExpr AMPERSAND_AMPERSAND RelationalExpr
    rule.setLeft(LOGICAL_EXPR);
    rule.addSymbol(LOGICAL_EXPR).addSymbol(AMPERSAND_AMPERSAND).addSymbol(RELATIONAL_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 72: RelationalExpr -> AddExpr
    rule.setLeft(RELATIONAL_EXPR);
    rule.addSymbol(ADD_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 73: RelationalExpr -> RelationalExpr EQUALS_EQUALS AddExpr
    rule.setLeft(RELATIONAL_EXPR);
    rule.addSymbol(RELATIONAL_EXPR).addSymbol(EQUALS_EQUALS).addSymbol(ADD_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 74: RelationalExpr -> RelationalExpr BANG_EQUALS AddExpr
    rule.setLeft(RELATIONAL_EXPR);
    rule.addSymbol(RELATIONAL_EXPR).addSymbol(BANG_EQUALS).addSymbol(ADD_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 75: RelationalExpr -> RelationalExpr LESS_THAN AddExpr
    rule.setLeft(RELATIONAL_EXPR);
    rule.addSymbol(RELATIONAL_EXPR).addSymbol(LESS_THAN).addSymbol(ADD_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 76: RelationalExpr -> RelationalExpr GREATER_THAN AddExpr
    rule.setLeft(RELATIONAL_EXPR);
    rule.addSymbol(RELATIONAL_EXPR).addSymbol(GREATER_THAN).addSymbol(ADD_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 77: RelationalExpr -> RelationalExpr LESS_THAN_EQUALS AddExpr
    rule.setLeft(RELATIONAL_EXPR);
    rule.addSymbol(RELATIONAL_EXPR).addSymbol(LESS_THAN_EQUALS).addSymbol(ADD_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 78: RelationalExpr -> RelationalExpr GREATER_THAN_EQUALS AddExpr
    rule.setLeft(RELATIONAL_EXPR);
    rule.addSymbol(RELATIONAL_EXPR).addSymbol(GREATER_THAN_EQUALS).addSymbol(ADD_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 79: AddExpr -> MulExpr
    rule.setLeft(ADD_EXPR);
    rule.addSymbol(MUL_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 80: AddExpr -> AddExpr PLUS MulExpr
    rule.setLeft(ADD_EXPR);
    rule.addSymbol(ADD_EXPR).addSymbol(PLUS).addSymbol(MUL_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 81: AddExpr -> AddExpr MINUS MulExpr
    rule.setLeft(ADD_EXPR);
    rule.addSymbol(ADD_EXPR).addSymbol(MINUS).addSymbol(MUL_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 82: AddExpr -> AddExpr PIPE MulExpr
    rule.setLeft(ADD_EXPR);
    rule.addSymbol(ADD_EXPR).addSymbol(PIPE).addSymbol(MUL_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 83: AddExpr -> AddExpr CARET MulExpr
    rule.setLeft(ADD_EXPR);
    rule.addSymbol(ADD_EXPR).addSymbol(CARET).addSymbol(MUL_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 84: MulExpr -> UnaryExpr
    rule.setLeft(MUL_EXPR);
    rule.addSymbol(UNARY_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 85: MulExpr -> MulExpr STAR UnaryExpr
    rule.setLeft(MUL_EXPR);
    rule.addSymbol(MUL_EXPR).addSymbol(STAR).addSymbol(UNARY_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 86: MulExpr -> MulExpr SLASH UnaryExpr
    rule.setLeft(MUL_EXPR);
    rule.addSymbol(MUL_EXPR).addSymbol(SLASH).addSymbol(UNARY_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 87: MulExpr -> MulExpr AMPERSAND UnaryExpr
    rule.setLeft(MUL_EXPR);
    rule.addSymbol(MUL_EXPR).addSymbol(AMPERSAND).addSymbol(UNARY_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 88: UnaryExpr -> PrimaryExpr
    rule.setLeft(UNARY_EXPR);
    rule.addSymbol(PRIMARY_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 89: UnaryExpr -> MINUS UnaryExpr
    rule.setLeft(UNARY_EXPR);
    rule.addSymbol(MINUS).addSymbol(UNARY_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 90: UnaryExpr -> BANG UnaryExpr
    rule.setLeft(UNARY_EXPR);
    rule.addSymbol(BANG).addSymbol(UNARY_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 91: IncrementExpr -> IDENTIFIER PLUS_PLUS
    rule.setLeft(INCREMENT_EXPR);
    rule.addSymbol(IDENTIFIER).addSymbol(PLUS_PLUS);
    addProductionRule(rule);
    rule.reset();

    // Rule 92: IncrementExpr -> IDENTIFIER MINUS_MINUS
    rule.setLeft(INCREMENT_EXPR);
    rule.addSymbol(IDENTIFIER).addSymbol(MINUS_MINUS);
    addProductionRule(rule);
    rule.reset();

    // Rule 93: IncrementExpr -> PLUS_PLUS IDENTIFIER
    rule.setLeft(INCREMENT_EXPR);
    rule.addSymbol(PLUS_PLUS).addSymbol(IDENTIFIER);
    addProductionRule(rule);
    rule.reset();

    // Rule 94: IncrementExpr -> MINUS_MINUS IDENTIFIER
    rule.setLeft(INCREMENT_EXPR);
    rule.addSymbol(MINUS_MINUS).addSymbol(IDENTIFIER);
    addProductionRule(rule);
    rule.reset();

    // Rule 95: AddressExpr -> AMPERSAND IDENTIFIER
    rule.setLeft(ADDRESS_EXPR);
    rule.addSymbol(AMPERSAND).addSymbol(IDENTIFIER);
    addProductionRule(rule);
    rule.reset();

    // Rule 96: DereferenceExpr -> STAR IDENTIFIER
    rule.setLeft(DEREFERENCE_EXPR);
    rule.addSymbol(STAR).addSymbol(IDENTIFIER);
    addProductionRule(rule);
    rule.reset();

    // Rule 97: PrimaryExpr -> IDENTIFIER
    rule.setLeft(PRIMARY_EXPR);
    rule.addSymbol(IDENTIFIER);
    addProductionRule(rule);
    rule.reset();

    // Rule 98: PrimaryExpr -> IDENTIFIER OPEN_BRACKET Expr CLOSED_BRACKET
    rule.setLeft(PRIMARY_EXPR);
    rule.addSymbol(IDENTIFIER).addSymbol(OPEN_BRACKET).addSymbol(EXPR).addSymbol(CLOSED_BRACKET);
    addProductionRule(rule);
    rule.reset();

    // Rule 99: PrimaryExpr -> INTEGER_LITERAL
    rule.setLeft(PRIMARY_EXPR);
    rule.addSymbol(INTEGER_LITERAL);
    addProductionRule(rule);
    rule.reset();

    // Rule 100: PrimaryExpr -> FLOAT_LITERAL
    rule.setLeft(PRIMARY_EXPR);
    rule.addSymbol(FLOAT_LITERAL);
    addProductionRule(rule);
    rule.reset();

    // Rule 101: PrimaryExpr -> CHAR_LITERAL
    rule.setLeft(PRIMARY_EXPR);
    rule.addSymbol(CHAR_LITERAL);
    addProductionRule(rule);
    rule.reset();

    // Rule 102: PrimaryExpr -> OPEN_PAREN Expr CLOSED_PAREN
    rule.setLeft(PRIMARY_EXPR);
    rule.addSymbol(OPEN_PAREN).addSymbol(EXPR).addSymbol(CLOSED_PAREN);
    addProductionRule(rule);
    rule.reset();

    // Rule 103: PrimaryExpr -> IDENTIFIER OPEN_PAREN ExprList CLOSED_PAREN
    rule.setLeft(PRIMARY_EXPR);
    rule.addSymbol(IDENTIFIER).addSymbol(OPEN_PAREN).addSymbol(EXPR_LIST).addSymbol(CLOSED_PAREN);
    addProductionRule(rule);
    rule.reset();

    // Rule 104: PrimaryExpr -> DereferenceExpr
    rule.setLeft(PRIMARY_EXPR);
    rule.addSymbol(DEREFERENCE_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 105: PrimaryExpr -> IncrementExpr
    rule.setLeft(PRIMARY_EXPR);
    rule.addSymbol(INCREMENT_EXPR);
    addProductionRule(rule);
    rule.reset();
}


void Parser::fillTables() {
    // State 0
    _actionTable.addDefault(0, {REDUCE, 1});
    _gotoTable.add(0, PROGRAM, 1);

    // State 1
    _actionTable.add(1, END_OF_FILE, {SHIFT, 2});
    _actionTable.add(1, KEYWORD_FN, {SHIFT, 3});
    _gotoTable.add(1, FUNCTION_DECL, 4);

    // State 2
    _actionTable.addDefault(2, {ACCEPT, 0});

    // State 3
    _actionTable.add(3, IDENTIFIER, {SHIFT, 5});

    // State 4
    _actionTable.addDefault(4, {REDUCE, 2});

    // State 5
    _actionTable.add(5, OPEN_PAREN, {SHIFT, 6});

    // State 6
    _actionTable.add(6, KEYWORD_INT, {SHIFT, 7});
    _actionTable.add(6, KEYWORD_FLOAT, {SHIFT, 8});
    _actionTable.add(6, KEYWORD_CHAR, {SHIFT, 9});
    _actionTable.addDefault(6, {REDUCE, 4});
    _gotoTable.add(6, PARAM_LIST, 10);
    _gotoTable.add(6, PARAM_LIST_NON_EMPTY, 11);
    _gotoTable.add(6, PARAM, 12);
    _gotoTable.add(6, TYPE, 13);
    _gotoTable.add(6, BASE_TYPE, 14);

    // State 7
    _actionTable.addDefault(7, {REDUCE, 12});

    // State 8
    _actionTable.addDefault(8, {REDUCE, 13});

    // State 9
    _actionTable.addDefault(9, {REDUCE, 14});

    // State 10
    _actionTable.add(10, CLOSED_PAREN, {SHIFT, 15});

    // State 11
    _actionTable.add(11, COMMA, {SHIFT, 16});
    _actionTable.addDefault(11, {REDUCE, 5});

    // State 12
    _actionTable.addDefault(12, {REDUCE, 6});

    // State 13
    _actionTable.add(13, IDENTIFIER, {SHIFT, 17});

    // State 14
    _actionTable.add(14, OPEN_BRACKET, {SHIFT, 18});
    _actionTable.add(14, STAR, {SHIFT, 19});
    _actionTable.addDefault(14, {REDUCE, 9});

    // State 15
    _actionTable.add(15, RIGHT_ARROW, {SHIFT, 20});

    // State 16
    _actionTable.add(16, KEYWORD_INT, {SHIFT, 7});
    _actionTable.add(16, KEYWORD_FLOAT, {SHIFT, 8});
    _actionTable.add(16, KEYWORD_CHAR, {SHIFT, 9});
    _gotoTable.add(16, PARAM, 21);
    _gotoTable.add(16, TYPE, 13);
    _gotoTable.add(16, BASE_TYPE, 14);

    // State 17
    _actionTable.addDefault(17, {REDUCE, 8});

    // State 18
    _actionTable.add(18, INTEGER_LITERAL, {SHIFT, 22});

    // State 19
    _actionTable.addDefault(19, {REDUCE, 11});

    // State 20
    _actionTable.add(20, KEYWORD_INT, {SHIFT, 7});
    _actionTable.add(20, KEYWORD_FLOAT, {SHIFT, 8});
    _actionTable.add(20, KEYWORD_CHAR, {SHIFT, 9});
    _gotoTable.add(20, TYPE, 23);
    _gotoTable.add(20, BASE_TYPE, 14);

    // State 21
    _actionTable.addDefault(21, {REDUCE, 7});

    // State 22
    _actionTable.add(22, CLOSED_BRACKET, {SHIFT, 24});

    // State 23
    _actionTable.add(23, OPEN_CURLY, {SHIFT, 25});

    // State 24
    _actionTable.addDefault(24, {REDUCE, 10});

    // State 25
    _actionTable.addDefault(25, {REDUCE, 15});
    _gotoTable.add(25, STMT_LIST, 26);

    // State 26
    _actionTable.add(26, IDENTIFIER, {SHIFT, 27});
    _actionTable.add(26, OPEN_CURLY, {SHIFT, 28});
    _actionTable.add(26, CLOSED_CURLY, {SHIFT, 29});
    _actionTable.add(26, KEYWORD_INT, {SHIFT, 7});
    _actionTable.add(26, KEYWORD_FLOAT, {SHIFT, 8});
    _actionTable.add(26, KEYWORD_CHAR, {SHIFT, 9});
    _actionTable.add(26, STAR, {SHIFT, 30});
    _actionTable.add(26, KEYWORD_IF, {SHIFT, 31});
    _actionTable.add(26, KEYWORD_WHILE, {SHIFT, 32});
    _actionTable.add(26, KEYWORD_FOR, {SHIFT, 33});
    _actionTable.add(26, KEYWORD_RET, {SHIFT, 34});
    _gotoTable.add(26, TYPE, 35);
    _gotoTable.add(26, BASE_TYPE, 14);
    _gotoTable.add(26, STMT, 36);
    _gotoTable.add(26, SIMPLE_STMT, 37);
    _gotoTable.add(26, VAR_DECL_EXPR, 38);
    _gotoTable.add(26, ASSIGN_EXPR, 39);
    _gotoTable.add(26, ASSIGN_TARGET, 40);
    _gotoTable.add(26, IF_STMT, 41);
    _gotoTable.add(26, WHILE_STMT, 42);
    _gotoTable.add(26, FOR_STMT, 43);

    // State 27
    _actionTable.add(27, OPEN_PAREN, {SHIFT, 44});
    _actionTable.add(27, OPEN_BRACKET, {SHIFT, 45});
    _actionTable.addDefault(27, {REDUCE, 32});

    // State 28
    _actionTable.addDefault(28, {REDUCE, 15});
    _gotoTable.add(28, STMT_LIST, 46);

    // State 29
    _actionTable.addDefault(29, {REDUCE, 3});

    // State 30
    _actionTable.add(30, IDENTIFIER, {SHIFT, 47});

    // State 31
    _actionTable.add(31, OPEN_PAREN, {SHIFT, 48});

    // State 32
    _actionTable.add(32, OPEN_PAREN, {SHIFT, 49});

    // State 33
    _actionTable.add(33, OPEN_PAREN, {SHIFT, 50});

    // State 34
    _actionTable.add(34, IDENTIFIER, {SHIFT, 51});
    _actionTable.add(34, OPEN_PAREN, {SHIFT, 52});
    _actionTable.add(34, STAR, {SHIFT, 53});
    _actionTable.add(34, MINUS, {SHIFT, 54});
    _actionTable.add(34, BANG, {SHIFT, 55});
    _actionTable.add(34, AMPERSAND, {SHIFT, 56});
    _actionTable.add(34, INTEGER_LITERAL, {SHIFT, 57});
    _actionTable.add(34, FLOAT_LITERAL, {SHIFT, 58});
    _actionTable.add(34, CHAR_LITERAL, {SHIFT, 59});
    _actionTable.add(34, PLUS_PLUS, {SHIFT, 60});
    _actionTable.add(34, MINUS_MINUS, {SHIFT, 61});
    _actionTable.addDefault(34, {REDUCE, 53});
    _gotoTable.add(34, EXPR_OPT, 62);
    _gotoTable.add(34, EXPR, 63);
    _gotoTable.add(34, LOGICAL_EXPR, 64);
    _gotoTable.add(34, RELATIONAL_EXPR, 65);
    _gotoTable.add(34, ADD_EXPR, 66);
    _gotoTable.add(34, MUL_EXPR, 67);
    _gotoTable.add(34, UNARY_EXPR, 68);
    _gotoTable.add(34, INCREMENT_EXPR, 69);
    _gotoTable.add(34, ADDRESS_EXPR, 70);
    _gotoTable.add(34, DEREFERENCE_EXPR, 71);
    _gotoTable.add(34, PRIMARY_EXPR, 72);

    // State 35
    _actionTable.add(35, IDENTIFIER, {SHIFT, 73});

    // State 36
    _actionTable.addDefault(36, {REDUCE, 16});

    // State 37
    _actionTable.add(37, SEMICOLON, {SHIFT, 74});

    // State 38
    _actionTable.addDefault(38, {REDUCE, 22});

    // State 39
    _actionTable.addDefault(39, {REDUCE, 23});

    // State 40
    _actionTable.add(40, EQUALS, {SHIFT, 75});
    _actionTable.add(40, PLUS_EQUALS, {SHIFT, 76});
    _actionTable.add(40, MINUS_EQUALS, {SHIFT, 77});
    _actionTable.add(40, SLASH_EQUALS, {SHIFT, 78});
    _actionTable.add(40, STAR_EQUALS, {SHIFT, 79});
    _actionTable.add(40, AMPERSAND_EQUALS, {SHIFT, 80});
    _actionTable.add(40, PIPE_EQUALS, {SHIFT, 81});
    _actionTable.add(40, CARET_EQUALS, {SHIFT, 82});
    _actionTable.add(40, TILDE_EQUALS, {SHIFT, 83});
    _gotoTable.add(40, ASSIGN_OP, 84);

    // State 41
    _actionTable.addDefault(41, {REDUCE, 19});

    // State 42
    _actionTable.addDefault(42, {REDUCE, 20});

    // State 43
    _actionTable.addDefault(43, {REDUCE, 21});

    // State 44
    _actionTable.add(44, IDENTIFIER, {SHIFT, 51});
    _actionTable.add(44, OPEN_PAREN, {SHIFT, 52});
    _actionTable.add(44, STAR, {SHIFT, 53});
    _actionTable.add(44, MINUS, {SHIFT, 54});
    _actionTable.add(44, BANG, {SHIFT, 55});
    _actionTable.add(44, AMPERSAND, {SHIFT, 56});
    _actionTable.add(44, INTEGER_LITERAL, {SHIFT, 57});
    _actionTable.add(44, FLOAT_LITERAL, {SHIFT, 58});
    _actionTable.add(44, CHAR_LITERAL, {SHIFT, 59});
    _actionTable.add(44, PLUS_PLUS, {SHIFT, 60});
    _actionTable.add(44, MINUS_MINUS, {SHIFT, 61});
    _actionTable.addDefault(44, {REDUCE, 63});
    _gotoTable.add(44, EXPR_LIST, 85);
    _gotoTable.add(44, EXPR_LIST_NON_EMPTY, 86);
    _gotoTable.add(44, EXPR, 87);
    _gotoTable.add(44, LOGICAL_EXPR, 64);
    _gotoTable.add(44, RELATIONAL_EXPR, 65);
    _gotoTable.add(44, ADD_EXPR, 66);
    _gotoTable.add(44, MUL_EXPR, 67);
    _gotoTable.add(44, UNARY_EXPR, 68);
    _gotoTable.add(44, INCREMENT_EXPR, 69);
    _gotoTable.add(44, ADDRESS_EXPR, 70);
    _gotoTable.add(44, DEREFERENCE_EXPR, 71);
    _gotoTable.add(44, PRIMARY_EXPR, 72);

    // State 45
    _actionTable.add(45, IDENTIFIER, {SHIFT, 51});
    _actionTable.add(45, OPEN_PAREN, {SHIFT, 52});
    _actionTable.add(45, STAR, {SHIFT, 53});
    _actionTable.add(45, MINUS, {SHIFT, 54});
    _actionTable.add(45, BANG, {SHIFT, 55});
    _actionTable.add(45, AMPERSAND, {SHIFT, 56});
    _actionTable.add(45, INTEGER_LITERAL, {SHIFT, 57});
    _actionTable.add(45, FLOAT_LITERAL, {SHIFT, 58});
    _actionTable.add(45, CHAR_LITERAL, {SHIFT, 59});
    _actionTable.add(45, PLUS_PLUS, {SHIFT, 60});
    _actionTable.add(45, MINUS_MINUS, {SHIFT, 61});
    _gotoTable.add(45, EXPR, 88);
    _gotoTable.add(45, LOGICAL_EXPR, 64);
    _gotoTable.add(45, RELATIONAL_EXPR, 65);
    _gotoTable.add(45, ADD_EXPR, 66);
    _gotoTable.add(45, MUL_EXPR, 67);
    _gotoTable.add(45, UNARY_EXPR, 68);
    _gotoTable.add(45, INCREMENT_EXPR, 69);
    _gotoTable.add(45, ADDRESS_EXPR, 70);
    _gotoTable.add(45, DEREFERENCE_EXPR, 71);
    _gotoTable.add(45, PRIMARY_EXPR, 72);

    // State 46
    _actionTable.add(46, IDENTIFIER, {SHIFT, 27});
    _actionTable.add(46, OPEN_CURLY, {SHIFT, 28});
    _actionTable.add(46, CLOSED_CURLY, {SHIFT, 89});
    _actionTable.add(46, KEYWORD_INT, {SHIFT, 7});
    _actionTable.add(46, KEYWORD_FLOAT, {SHIFT, 8});
    _actionTable.add(46, KEYWORD_CHAR, {SHIFT, 9});
    _actionTable.add(46, STAR, {SHIFT, 30});
    _actionTable.add(46, KEYWORD_IF, {SHIFT, 31});
    _actionTable.add(46, KEYWORD_WHILE, {SHIFT, 32});
    _actionTable.add(46, KEYWORD_FOR, {SHIFT, 33});
    _actionTable.add(46, KEYWORD_RET, {SHIFT, 34});
    _gotoTable.add(46, TYPE, 35);
    _gotoTable.add(46, BASE_TYPE, 14);
    _gotoTable.add(46, STMT, 36);
    _gotoTable.add(46, SIMPLE_STMT, 37);
    _gotoTable.add(46, VAR_DECL_EXPR, 38);
    _gotoTable.add(46, ASSIGN_EXPR, 39);
    _gotoTable.add(46, ASSIGN_TARGET, 40);
    _gotoTable.add(46, IF_STMT, 41);
    _gotoTable.add(46, WHILE_STMT, 42);
    _gotoTable.add(46, FOR_STMT, 43);

    // State 47
    _actionTable.addDefault(47, {REDUCE, 34});

    // State 48
    _actionTable.add(48, IDENTIFIER, {SHIFT, 90});
    _actionTable.add(48, OPEN_PAREN, {SHIFT, 52});
    _actionTable.add(48, STAR, {SHIFT, 91});
    _actionTable.add(48, MINUS, {SHIFT, 54});
    _actionTable.add(48, BANG, {SHIFT, 55});
    _actionTable.add(48, AMPERSAND, {SHIFT, 56});
    _actionTable.add(48, INTEGER_LITERAL, {SHIFT, 57});
    _actionTable.add(48, FLOAT_LITERAL, {SHIFT, 58});
    _actionTable.add(48, CHAR_LITERAL, {SHIFT, 59});
    _actionTable.add(48, PLUS_PLUS, {SHIFT, 60});
    _actionTable.add(48, MINUS_MINUS, {SHIFT, 61});
    _gotoTable.add(48, ASSIGN_EXPR, 92);
    _gotoTable.add(48, ASSIGN_TARGET, 40);
    _gotoTable.add(48, CONDITION_OP, 93);
    _gotoTable.add(48, EXPR, 94);
    _gotoTable.add(48, LOGICAL_EXPR, 64);
    _gotoTable.add(48, RELATIONAL_EXPR, 65);
    _gotoTable.add(48, ADD_EXPR, 66);
    _gotoTable.add(48, MUL_EXPR, 67);
    _gotoTable.add(48, UNARY_EXPR, 68);
    _gotoTable.add(48, INCREMENT_EXPR, 69);
    _gotoTable.add(48, ADDRESS_EXPR, 70);
    _gotoTable.add(48, DEREFERENCE_EXPR, 71);
    _gotoTable.add(48, PRIMARY_EXPR, 72);

    // State 49
    _actionTable.add(49, IDENTIFIER, {SHIFT, 90});
    _actionTable.add(49, OPEN_PAREN, {SHIFT, 52});
    _actionTable.add(49, STAR, {SHIFT, 91});
    _actionTable.add(49, MINUS, {SHIFT, 54});
    _actionTable.add(49, BANG, {SHIFT, 55});
    _actionTable.add(49, AMPERSAND, {SHIFT, 56});
    _actionTable.add(49, INTEGER_LITERAL, {SHIFT, 57});
    _actionTable.add(49, FLOAT_LITERAL, {SHIFT, 58});
    _actionTable.add(49, CHAR_LITERAL, {SHIFT, 59});
    _actionTable.add(49, PLUS_PLUS, {SHIFT, 60});
    _actionTable.add(49, MINUS_MINUS, {SHIFT, 61});
    _gotoTable.add(49, ASSIGN_EXPR, 92);
    _gotoTable.add(49, ASSIGN_TARGET, 40);
    _gotoTable.add(49, CONDITION_OP, 95);
    _gotoTable.add(49, EXPR, 94);
    _gotoTable.add(49, LOGICAL_EXPR, 64);
    _gotoTable.add(49, RELATIONAL_EXPR, 65);
    _gotoTable.add(49, ADD_EXPR, 66);
    _gotoTable.add(49, MUL_EXPR, 67);
    _gotoTable.add(49, UNARY_EXPR, 68);
    _gotoTable.add(49, INCREMENT_EXPR, 69);
    _gotoTable.add(49, ADDRESS_EXPR, 70);
    _gotoTable.add(49, DEREFERENCE_EXPR, 71);
    _gotoTable.add(49, PRIMARY_EXPR, 72);

    // State 50
    _actionTable.add(50, IDENTIFIER, {SHIFT, 96});
    _actionTable.add(50, KEYWORD_INT, {SHIFT, 7});
    _actionTable.add(50, KEYWORD_FLOAT, {SHIFT, 8});
    _actionTable.add(50, KEYWORD_CHAR, {SHIFT, 9});
    _actionTable.add(50, STAR, {SHIFT, 30});
    _actionTable.addDefault(50, {REDUCE, 50});
    _gotoTable.add(50, TYPE, 35);
    _gotoTable.add(50, BASE_TYPE, 14);
    _gotoTable.add(50, VAR_DECL_EXPR, 97);
    _gotoTable.add(50, ASSIGN_EXPR, 98);
    _gotoTable.add(50, ASSIGN_TARGET, 40);
    _gotoTable.add(50, FOR_INIT, 99);

    // State 51
    _actionTable.add(51, OPEN_PAREN, {SHIFT, 100});
    _actionTable.add(51, OPEN_BRACKET, {SHIFT, 101});
    _actionTable.add(51, PLUS_PLUS, {SHIFT, 102});
    _actionTable.add(51, MINUS_MINUS, {SHIFT, 103});
    _actionTable.addDefault(51, {REDUCE, 97});

    // State 52
    _actionTable.add(52, IDENTIFIER, {SHIFT, 51});
    _actionTable.add(52, OPEN_PAREN, {SHIFT, 52});
    _actionTable.add(52, STAR, {SHIFT, 53});
    _actionTable.add(52, MINUS, {SHIFT, 54});
    _actionTable.add(52, BANG, {SHIFT, 55});
    _actionTable.add(52, AMPERSAND, {SHIFT, 56});
    _actionTable.add(52, INTEGER_LITERAL, {SHIFT, 57});
    _actionTable.add(52, FLOAT_LITERAL, {SHIFT, 58});
    _actionTable.add(52, CHAR_LITERAL, {SHIFT, 59});
    _actionTable.add(52, PLUS_PLUS, {SHIFT, 60});
    _actionTable.add(52, MINUS_MINUS, {SHIFT, 61});
    _gotoTable.add(52, EXPR, 104);
    _gotoTable.add(52, LOGICAL_EXPR, 64);
    _gotoTable.add(52, RELATIONAL_EXPR, 65);
    _gotoTable.add(52, ADD_EXPR, 66);
    _gotoTable.add(52, MUL_EXPR, 67);
    _gotoTable.add(52, UNARY_EXPR, 68);
    _gotoTable.add(52, INCREMENT_EXPR, 69);
    _gotoTable.add(52, ADDRESS_EXPR, 70);
    _gotoTable.add(52, DEREFERENCE_EXPR, 71);
    _gotoTable.add(52, PRIMARY_EXPR, 72);

    // State 53
    _actionTable.add(53, IDENTIFIER, {SHIFT, 105});

    // State 54
    _actionTable.add(54, IDENTIFIER, {SHIFT, 51});
    _actionTable.add(54, OPEN_PAREN, {SHIFT, 52});
    _actionTable.add(54, STAR, {SHIFT, 53});
    _actionTable.add(54, MINUS, {SHIFT, 54});
    _actionTable.add(54, BANG, {SHIFT, 55});
    _actionTable.add(54, INTEGER_LITERAL, {SHIFT, 57});
    _actionTable.add(54, FLOAT_LITERAL, {SHIFT, 58});
    _actionTable.add(54, CHAR_LITERAL, {SHIFT, 59});
    _actionTable.add(54, PLUS_PLUS, {SHIFT, 60});
    _actionTable.add(54, MINUS_MINUS, {SHIFT, 61});
    _gotoTable.add(54, UNARY_EXPR, 106);
    _gotoTable.add(54, INCREMENT_EXPR, 69);
    _gotoTable.add(54, DEREFERENCE_EXPR, 71);
    _gotoTable.add(54, PRIMARY_EXPR, 72);

    // State 55
    _actionTable.add(55, IDENTIFIER, {SHIFT, 51});
    _actionTable.add(55, OPEN_PAREN, {SHIFT, 52});
    _actionTable.add(55, STAR, {SHIFT, 53});
    _actionTable.add(55, MINUS, {SHIFT, 54});
    _actionTable.add(55, BANG, {SHIFT, 55});
    _actionTable.add(55, INTEGER_LITERAL, {SHIFT, 57});
    _actionTable.add(55, FLOAT_LITERAL, {SHIFT, 58});
    _actionTable.add(55, CHAR_LITERAL, {SHIFT, 59});
    _actionTable.add(55, PLUS_PLUS, {SHIFT, 60});
    _actionTable.add(55, MINUS_MINUS, {SHIFT, 61});
    _gotoTable.add(55, UNARY_EXPR, 107);
    _gotoTable.add(55, INCREMENT_EXPR, 69);
    _gotoTable.add(55, DEREFERENCE_EXPR, 71);
    _gotoTable.add(55, PRIMARY_EXPR, 72);

    // State 56
    _actionTable.add(56, IDENTIFIER, {SHIFT, 108});

    // State 57
    _actionTable.addDefault(57, {REDUCE, 99});

    // State 58
    _actionTable.addDefault(58, {REDUCE, 100});

    // State 59
    _actionTable.addDefault(59, {REDUCE, 101});

    // State 60
    _actionTable.add(60, IDENTIFIER, {SHIFT, 109});

    // State 61
    _actionTable.add(61, IDENTIFIER, {SHIFT, 110});

    // State 62
    _actionTable.addDefault(62, {REDUCE, 25});

    // State 63
    _actionTable.addDefault(63, {REDUCE, 54});

    // State 64
    _actionTable.add(64, PIPE_PIPE, {SHIFT, 111});
    _actionTable.add(64, AMPERSAND_AMPERSAND, {SHIFT, 112});
    _actionTable.addDefault(64, {REDUCE, 67});

    // State 65
    _actionTable.add(65, LESS_THAN, {SHIFT, 113});
    _actionTable.add(65, GREATER_THAN, {SHIFT, 114});
    _actionTable.add(65, LESS_THAN_EQUALS, {SHIFT, 115});
    _actionTable.add(65, GREATER_THAN_EQUALS, {SHIFT, 116});
    _actionTable.add(65, EQUALS_EQUALS, {SHIFT, 117});
    _actionTable.add(65, BANG_EQUALS, {SHIFT, 118});
    _actionTable.addDefault(65, {REDUCE, 69});

    // State 66
    _actionTable.add(66, MINUS, {SHIFT, 119});
    _actionTable.add(66, PLUS, {SHIFT, 120});
    _actionTable.add(66, PIPE, {SHIFT, 121});
    _actionTable.add(66, CARET, {SHIFT, 122});
    _actionTable.addDefault(66, {REDUCE, 72});

    // State 67
    _actionTable.add(67, STAR, {SHIFT, 123});
    _actionTable.add(67, SLASH, {SHIFT, 124});
    _actionTable.add(67, AMPERSAND, {SHIFT, 125});
    _actionTable.addDefault(67, {REDUCE, 79});

    // State 68
    _actionTable.addDefault(68, {REDUCE, 84});

    // State 69
    _actionTable.addDefault(69, {REDUCE, 105});

    // State 70
    _actionTable.addDefault(70, {REDUCE, 68});

    // State 71
    _actionTable.addDefault(71, {REDUCE, 104});

    // State 72
    _actionTable.addDefault(72, {REDUCE, 88});

    // State 73
    _actionTable.add(73, EQUALS, {SHIFT, 126});
    _actionTable.addDefault(73, {REDUCE, 27});
    _gotoTable.add(73, INIT_OPT, 127);

    // State 74
    _actionTable.addDefault(74, {REDUCE, 17});

    // State 75
    _actionTable.addDefault(75, {REDUCE, 35});

    // State 76
    _actionTable.addDefault(76, {REDUCE, 36});

    // State 77
    _actionTable.addDefault(77, {REDUCE, 37});

    // State 78
    _actionTable.addDefault(78, {REDUCE, 38});

    // State 79
    _actionTable.addDefault(79, {REDUCE, 39});

    // State 80
    _actionTable.addDefault(80, {REDUCE, 40});

    // State 81
    _actionTable.addDefault(81, {REDUCE, 41});

    // State 82
    _actionTable.addDefault(82, {REDUCE, 42});

    // State 83
    _actionTable.addDefault(83, {REDUCE, 43});

    // State 84
    _actionTable.add(84, IDENTIFIER, {SHIFT, 51});
    _actionTable.add(84, OPEN_PAREN, {SHIFT, 52});
    _actionTable.add(84, STAR, {SHIFT, 53});
    _actionTable.add(84, MINUS, {SHIFT, 54});
    _actionTable.add(84, BANG, {SHIFT, 55});
    _actionTable.add(84, AMPERSAND, {SHIFT, 56});
    _actionTable.add(84, INTEGER_LITERAL, {SHIFT, 57});
    _actionTable.add(84, FLOAT_LITERAL, {SHIFT, 58});
    _actionTable.add(84, CHAR_LITERAL, {SHIFT, 59});
    _actionTable.add(84, PLUS_PLUS, {SHIFT, 60});
    _actionTable.add(84, MINUS_MINUS, {SHIFT, 61});
    _gotoTable.add(84, EXPR, 128);
    _gotoTable.add(84, LOGICAL_EXPR, 64);
    _gotoTable.add(84, RELATIONAL_EXPR, 65);
    _gotoTable.add(84, ADD_EXPR, 66);
    _gotoTable.add(84, MUL_EXPR, 67);
    _gotoTable.add(84, UNARY_EXPR, 68);
    _gotoTable.add(84, INCREMENT_EXPR, 69);
    _gotoTable.add(84, ADDRESS_EXPR, 70);
    _gotoTable.add(84, DEREFERENCE_EXPR, 71);
    _gotoTable.add(84, PRIMARY_EXPR, 72);

    // State 85
    _actionTable.add(85, CLOSED_PAREN, {SHIFT, 129});

    // State 86
    _actionTable.add(86, COMMA, {SHIFT, 130});
    _actionTable.addDefault(86, {REDUCE, 64});

    // State 87
    _actionTable.addDefault(87, {REDUCE, 65});

    // State 88
    _actionTable.add(88, CLOSED_BRACKET, {SHIFT, 131});

    // State 89
    _actionTable.addDefault(89, {REDUCE, 18});

    // State 90
    _actionTable.add(90, OPEN_PAREN, {SHIFT, 100});
    _actionTable.add(90, OPEN_BRACKET, {SHIFT, 132});
    _actionTable.add(90, PLUS_PLUS, {SHIFT, 102});
    _actionTable.add(90, MINUS_MINUS, {SHIFT, 103});
    _actionTable.add(90, EQUALS, {REDUCE, 32});
    _actionTable.add(90, PLUS_EQUALS, {REDUCE, 32});
    _actionTable.add(90, MINUS_EQUALS, {REDUCE, 32});
    _actionTable.add(90, SLASH_EQUALS, {REDUCE, 32});
    _actionTable.add(90, STAR_EQUALS, {REDUCE, 32});
    _actionTable.add(90, AMPERSAND_EQUALS, {REDUCE, 32});
    _actionTable.add(90, PIPE_EQUALS, {REDUCE, 32});
    _actionTable.add(90, CARET_EQUALS, {REDUCE, 32});
    _actionTable.add(90, TILDE_EQUALS, {REDUCE, 32});
    _actionTable.addDefault(90, {REDUCE, 97});

    // State 91
    _actionTable.add(91, IDENTIFIER, {SHIFT, 133});

    // State 92
    _actionTable.addDefault(92, {REDUCE, 48});

    // State 93
    _actionTable.add(93, CLOSED_PAREN, {SHIFT, 134});

    // State 94
    _actionTable.addDefault(94, {REDUCE, 47});

    // State 95
    _actionTable.add(95, CLOSED_PAREN, {SHIFT, 135});

    // State 96
    _actionTable.add(96, OPEN_BRACKET, {SHIFT, 45});
    _actionTable.addDefault(96, {REDUCE, 32});

    // State 97
    _actionTable.addDefault(97, {REDUCE, 51});

    // State 98
    _actionTable.addDefault(98, {REDUCE, 52});

    // State 99
    _actionTable.add(99, SEMICOLON, {SHIFT, 136});

    // State 100
    _actionTable.add(100, IDENTIFIER, {SHIFT, 51});
    _actionTable.add(100, OPEN_PAREN, {SHIFT, 52});
    _actionTable.add(100, STAR, {SHIFT, 53});
    _actionTable.add(100, MINUS, {SHIFT, 54});
    _actionTable.add(100, BANG, {SHIFT, 55});
    _actionTable.add(100, AMPERSAND, {SHIFT, 56});
    _actionTable.add(100, INTEGER_LITERAL, {SHIFT, 57});
    _actionTable.add(100, FLOAT_LITERAL, {SHIFT, 58});
    _actionTable.add(100, CHAR_LITERAL, {SHIFT, 59});
    _actionTable.add(100, PLUS_PLUS, {SHIFT, 60});
    _actionTable.add(100, MINUS_MINUS, {SHIFT, 61});
    _actionTable.addDefault(100, {REDUCE, 63});
    _gotoTable.add(100, EXPR_LIST, 137);
    _gotoTable.add(100, EXPR_LIST_NON_EMPTY, 86);
    _gotoTable.add(100, EXPR, 87);
    _gotoTable.add(100, LOGICAL_EXPR, 64);
    _gotoTable.add(100, RELATIONAL_EXPR, 65);
    _gotoTable.add(100, ADD_EXPR, 66);
    _gotoTable.add(100, MUL_EXPR, 67);
    _gotoTable.add(100, UNARY_EXPR, 68);
    _gotoTable.add(100, INCREMENT_EXPR, 69);
    _gotoTable.add(100, ADDRESS_EXPR, 70);
    _gotoTable.add(100, DEREFERENCE_EXPR, 71);
    _gotoTable.add(100, PRIMARY_EXPR, 72);

    // State 101
    _actionTable.add(101, IDENTIFIER, {SHIFT, 51});
    _actionTable.add(101, OPEN_PAREN, {SHIFT, 52});
    _actionTable.add(101, STAR, {SHIFT, 53});
    _actionTable.add(101, MINUS, {SHIFT, 54});
    _actionTable.add(101, BANG, {SHIFT, 55});
    _actionTable.add(101, AMPERSAND, {SHIFT, 56});
    _actionTable.add(101, INTEGER_LITERAL, {SHIFT, 57});
    _actionTable.add(101, FLOAT_LITERAL, {SHIFT, 58});
    _actionTable.add(101, CHAR_LITERAL, {SHIFT, 59});
    _actionTable.add(101, PLUS_PLUS, {SHIFT, 60});
    _actionTable.add(101, MINUS_MINUS, {SHIFT, 61});
    _gotoTable.add(101, EXPR, 138);
    _gotoTable.add(101, LOGICAL_EXPR, 64);
    _gotoTable.add(101, RELATIONAL_EXPR, 65);
    _gotoTable.add(101, ADD_EXPR, 66);
    _gotoTable.add(101, MUL_EXPR, 67);
    _gotoTable.add(101, UNARY_EXPR, 68);
    _gotoTable.add(101, INCREMENT_EXPR, 69);
    _gotoTable.add(101, ADDRESS_EXPR, 70);
    _gotoTable.add(101, DEREFERENCE_EXPR, 71);
    _gotoTable.add(101, PRIMARY_EXPR, 72);

    // State 102
    _actionTable.addDefault(102, {REDUCE, 91});

    // State 103
    _actionTable.addDefault(103, {REDUCE, 92});

    // State 104
    _actionTable.add(104, CLOSED_PAREN, {SHIFT, 139});

    // State 105
    _actionTable.addDefault(105, {REDUCE, 96});

    // State 106
    _actionTable.addDefault(106, {REDUCE, 89});

    // State 107
    _actionTable.addDefault(107, {REDUCE, 90});

    // State 108
    _actionTable.addDefault(108, {REDUCE, 95});

    // State 109
    _actionTable.addDefault(109, {REDUCE, 93});

    // State 110
    _actionTable.addDefault(110, {REDUCE, 94});

    // State 111
    _actionTable.add(111, IDENTIFIER, {SHIFT, 51});
    _actionTable.add(111, OPEN_PAREN, {SHIFT, 52});
    _actionTable.add(111, STAR, {SHIFT, 53});
    _actionTable.add(111, MINUS, {SHIFT, 54});
    _actionTable.add(111, BANG, {SHIFT, 55});
    _actionTable.add(111, INTEGER_LITERAL, {SHIFT, 57});
    _actionTable.add(111, FLOAT_LITERAL, {SHIFT, 58});
    _actionTable.add(111, CHAR_LITERAL, {SHIFT, 59});
    _actionTable.add(111, PLUS_PLUS, {SHIFT, 60});
    _actionTable.add(111, MINUS_MINUS, {SHIFT, 61});
    _gotoTable.add(111, RELATIONAL_EXPR, 140);
    _gotoTable.add(111, ADD_EXPR, 66);
    _gotoTable.add(111, MUL_EXPR, 67);
    _gotoTable.add(111, UNARY_EXPR, 68);
    _gotoTable.add(111, INCREMENT_EXPR, 69);
    _gotoTable.add(111, DEREFERENCE_EXPR, 71);
    _gotoTable.add(111, PRIMARY_EXPR, 72);

    // State 112
    _actionTable.add(112, IDENTIFIER, {SHIFT, 51});
    _actionTable.add(112, OPEN_PAREN, {SHIFT, 52});
    _actionTable.add(112, STAR, {SHIFT, 53});
    _actionTable.add(112, MINUS, {SHIFT, 54});
    _actionTable.add(112, BANG, {SHIFT, 55});
    _actionTable.add(112, INTEGER_LITERAL, {SHIFT, 57});
    _actionTable.add(112, FLOAT_LITERAL, {SHIFT, 58});
    _actionTable.add(112, CHAR_LITERAL, {SHIFT, 59});
    _actionTable.add(112, PLUS_PLUS, {SHIFT, 60});
    _actionTable.add(112, MINUS_MINUS, {SHIFT, 61});
    _gotoTable.add(112, RELATIONAL_EXPR, 141);
    _gotoTable.add(112, ADD_EXPR, 66);
    _gotoTable.add(112, MUL_EXPR, 67);
    _gotoTable.add(112, UNARY_EXPR, 68);
    _gotoTable.add(112, INCREMENT_EXPR, 69);
    _gotoTable.add(112, DEREFERENCE_EXPR, 71);
    _gotoTable.add(112, PRIMARY_EXPR, 72);

    // State 113
    _actionTable.add(113, IDENTIFIER, {SHIFT, 51});
    _actionTable.add(113, OPEN_PAREN, {SHIFT, 52});
    _actionTable.add(113, STAR, {SHIFT, 53});
    _actionTable.add(113, MINUS, {SHIFT, 54});
    _actionTable.add(113, BANG, {SHIFT, 55});
    _actionTable.add(113, INTEGER_LITERAL, {SHIFT, 57});
    _actionTable.add(113, FLOAT_LITERAL, {SHIFT, 58});
    _actionTable.add(113, CHAR_LITERAL, {SHIFT, 59});
    _actionTable.add(113, PLUS_PLUS, {SHIFT, 60});
    _actionTable.add(113, MINUS_MINUS, {SHIFT, 61});
    _gotoTable.add(113, ADD_EXPR, 142);
    _gotoTable.add(113, MUL_EXPR, 67);
    _gotoTable.add(113, UNARY_EXPR, 68);
    _gotoTable.add(113, INCREMENT_EXPR, 69);
    _gotoTable.add(113, DEREFERENCE_EXPR, 71);
    _gotoTable.add(113, PRIMARY_EXPR, 72);

    // State 114
    _actionTable.add(114, IDENTIFIER, {SHIFT, 51});
    _actionTable.add(114, OPEN_PAREN, {SHIFT, 52});
    _actionTable.add(114, STAR, {SHIFT, 53});
    _actionTable.add(114, MINUS, {SHIFT, 54});
    _actionTable.add(114, BANG, {SHIFT, 55});
    _actionTable.add(114, INTEGER_LITERAL, {SHIFT, 57});
    _actionTable.add(114, FLOAT_LITERAL, {SHIFT, 58});
    _actionTable.add(114, CHAR_LITERAL, {SHIFT, 59});
    _actionTable.add(114, PLUS_PLUS, {SHIFT, 60});
    _actionTable.add(114, MINUS_MINUS, {SHIFT, 61});
    _gotoTable.add(114, ADD_EXPR, 143);
    _gotoTable.add(114, MUL_EXPR, 67);
    _gotoTable.add(114, UNARY_EXPR, 68);
    _gotoTable.add(114, INCREMENT_EXPR, 69);
    _gotoTable.add(114, DEREFERENCE_EXPR, 71);
    _gotoTable.add(114, PRIMARY_EXPR, 72);

    // State 115
    _actionTable.add(115, IDENTIFIER, {SHIFT, 51});
    _actionTable.add(115, OPEN_PAREN, {SHIFT, 52});
    _actionTable.add(115, STAR, {SHIFT, 53});
    _actionTable.add(115, MINUS, {SHIFT, 54});
    _actionTable.add(115, BANG, {SHIFT, 55});
    _actionTable.add(115, INTEGER_LITERAL, {SHIFT, 57});
    _actionTable.add(115, FLOAT_LITERAL, {SHIFT, 58});
    _actionTable.add(115, CHAR_LITERAL, {SHIFT, 59});
    _actionTable.add(115, PLUS_PLUS, {SHIFT, 60});
    _actionTable.add(115, MINUS_MINUS, {SHIFT, 61});
    _gotoTable.add(115, ADD_EXPR, 144);
    _gotoTable.add(115, MUL_EXPR, 67);
    _gotoTable.add(115, UNARY_EXPR, 68);
    _gotoTable.add(115, INCREMENT_EXPR, 69);
    _gotoTable.add(115, DEREFERENCE_EXPR, 71);
    _gotoTable.add(115, PRIMARY_EXPR, 72);

    // State 116
    _actionTable.add(116, IDENTIFIER, {SHIFT, 51});
    _actionTable.add(116, OPEN_PAREN, {SHIFT, 52});
    _actionTable.add(116, STAR, {SHIFT, 53});
    _actionTable.add(116, MINUS, {SHIFT, 54});
    _actionTable.add(116, BANG, {SHIFT, 55});
    _actionTable.add(116, INTEGER_LITERAL, {SHIFT, 57});
    _actionTable.add(116, FLOAT_LITERAL, {SHIFT, 58});
    _actionTable.add(116, CHAR_LITERAL, {SHIFT, 59});
    _actionTable.add(116, PLUS_PLUS, {SHIFT, 60});
    _actionTable.add(116, MINUS_MINUS, {SHIFT, 61});
    _gotoTable.add(116, ADD_EXPR, 145);
    _gotoTable.add(116, MUL_EXPR, 67);
    _gotoTable.add(116, UNARY_EXPR, 68);
    _gotoTable.add(116, INCREMENT_EXPR, 69);
    _gotoTable.add(116, DEREFERENCE_EXPR, 71);
    _gotoTable.add(116, PRIMARY_EXPR, 72);

    // State 117
    _actionTable.add(117, IDENTIFIER, {SHIFT, 51});
    _actionTable.add(117, OPEN_PAREN, {SHIFT, 52});
    _actionTable.add(117, STAR, {SHIFT, 53});
    _actionTable.add(117, MINUS, {SHIFT, 54});
    _actionTable.add(117, BANG, {SHIFT, 55});
    _actionTable.add(117, INTEGER_LITERAL, {SHIFT, 57});
    _actionTable.add(117, FLOAT_LITERAL, {SHIFT, 58});
    _actionTable.add(117, CHAR_LITERAL, {SHIFT, 59});
    _actionTable.add(117, PLUS_PLUS, {SHIFT, 60});
    _actionTable.add(117, MINUS_MINUS, {SHIFT, 61});
    _gotoTable.add(117, ADD_EXPR, 146);
    _gotoTable.add(117, MUL_EXPR, 67);
    _gotoTable.add(117, UNARY_EXPR, 68);
    _gotoTable.add(117, INCREMENT_EXPR, 69);
    _gotoTable.add(117, DEREFERENCE_EXPR, 71);
    _gotoTable.add(117, PRIMARY_EXPR, 72);

    // State 118
    _actionTable.add(118, IDENTIFIER, {SHIFT, 51});
    _actionTable.add(118, OPEN_PAREN, {SHIFT, 52});
    _actionTable.add(118, STAR, {SHIFT, 53});
    _actionTable.add(118, MINUS, {SHIFT, 54});
    _actionTable.add(118, BANG, {SHIFT, 55});
    _actionTable.add(118, INTEGER_LITERAL, {SHIFT, 57});
    _actionTable.add(118, FLOAT_LITERAL, {SHIFT, 58});
    _actionTable.add(118, CHAR_LITERAL, {SHIFT, 59});
    _actionTable.add(118, PLUS_PLUS, {SHIFT, 60});
    _actionTable.add(118, MINUS_MINUS, {SHIFT, 61});
    _gotoTable.add(118, ADD_EXPR, 147);
    _gotoTable.add(118, MUL_EXPR, 67);
    _gotoTable.add(118, UNARY_EXPR, 68);
    _gotoTable.add(118, INCREMENT_EXPR, 69);
    _gotoTable.add(118, DEREFERENCE_EXPR, 71);
    _gotoTable.add(118, PRIMARY_EXPR, 72);

    // State 119
    _actionTable.add(119, IDENTIFIER, {SHIFT, 51});
    _actionTable.add(119, OPEN_PAREN, {SHIFT, 52});
    _actionTable.add(119, STAR, {SHIFT, 53});
    _actionTable.add(119, MINUS, {SHIFT, 54});
    _actionTable.add(119, BANG, {SHIFT, 55});
    _actionTable.add(119, INTEGER_LITERAL, {SHIFT, 57});
    _actionTable.add(119, FLOAT_LITERAL, {SHIFT, 58});
    _actionTable.add(119, CHAR_LITERAL, {SHIFT, 59});
    _actionTable.add(119, PLUS_PLUS, {SHIFT, 60});
    _actionTable.add(119, MINUS_MINUS, {SHIFT, 61});
    _gotoTable.add(119, MUL_EXPR, 148);
    _gotoTable.add(119, UNARY_EXPR, 68);
    _gotoTable.add(119, INCREMENT_EXPR, 69);
    _gotoTable.add(119, DEREFERENCE_EXPR, 71);
    _gotoTable.add(119, PRIMARY_EXPR, 72);

    // State 120
    _actionTable.add(120, IDENTIFIER, {SHIFT, 51});
    _actionTable.add(120, OPEN_PAREN, {SHIFT, 52});
    _actionTable.add(120, STAR, {SHIFT, 53});
    _actionTable.add(120, MINUS, {SHIFT, 54});
    _actionTable.add(120, BANG, {SHIFT, 55});
    _actionTable.add(120, INTEGER_LITERAL, {SHIFT, 57});
    _actionTable.add(120, FLOAT_LITERAL, {SHIFT, 58});
    _actionTable.add(120, CHAR_LITERAL, {SHIFT, 59});
    _actionTable.add(120, PLUS_PLUS, {SHIFT, 60});
    _actionTable.add(120, MINUS_MINUS, {SHIFT, 61});
    _gotoTable.add(120, MUL_EXPR, 149);
    _gotoTable.add(120, UNARY_EXPR, 68);
    _gotoTable.add(120, INCREMENT_EXPR, 69);
    _gotoTable.add(120, DEREFERENCE_EXPR, 71);
    _gotoTable.add(120, PRIMARY_EXPR, 72);

    // State 121
    _actionTable.add(121, IDENTIFIER, {SHIFT, 51});
    _actionTable.add(121, OPEN_PAREN, {SHIFT, 52});
    _actionTable.add(121, STAR, {SHIFT, 53});
    _actionTable.add(121, MINUS, {SHIFT, 54});
    _actionTable.add(121, BANG, {SHIFT, 55});
    _actionTable.add(121, INTEGER_LITERAL, {SHIFT, 57});
    _actionTable.add(121, FLOAT_LITERAL, {SHIFT, 58});
    _actionTable.add(121, CHAR_LITERAL, {SHIFT, 59});
    _actionTable.add(121, PLUS_PLUS, {SHIFT, 60});
    _actionTable.add(121, MINUS_MINUS, {SHIFT, 61});
    _gotoTable.add(121, MUL_EXPR, 150);
    _gotoTable.add(121, UNARY_EXPR, 68);
    _gotoTable.add(121, INCREMENT_EXPR, 69);
    _gotoTable.add(121, DEREFERENCE_EXPR, 71);
    _gotoTable.add(121, PRIMARY_EXPR, 72);

    // State 122
    _actionTable.add(122, IDENTIFIER, {SHIFT, 51});
    _actionTable.add(122, OPEN_PAREN, {SHIFT, 52});
    _actionTable.add(122, STAR, {SHIFT, 53});
    _actionTable.add(122, MINUS, {SHIFT, 54});
    _actionTable.add(122, BANG, {SHIFT, 55});
    _actionTable.add(122, INTEGER_LITERAL, {SHIFT, 57});
    _actionTable.add(122, FLOAT_LITERAL, {SHIFT, 58});
    _actionTable.add(122, CHAR_LITERAL, {SHIFT, 59});
    _actionTable.add(122, PLUS_PLUS, {SHIFT, 60});
    _actionTable.add(122, MINUS_MINUS, {SHIFT, 61});
    _gotoTable.add(122, MUL_EXPR, 151);
    _gotoTable.add(122, UNARY_EXPR, 68);
    _gotoTable.add(122, INCREMENT_EXPR, 69);
    _gotoTable.add(122, DEREFERENCE_EXPR, 71);
    _gotoTable.add(122, PRIMARY_EXPR, 72);

    // State 123
    _actionTable.add(123, IDENTIFIER, {SHIFT, 51});
    _actionTable.add(123, OPEN_PAREN, {SHIFT, 52});
    _actionTable.add(123, STAR, {SHIFT, 53});
    _actionTable.add(123, MINUS, {SHIFT, 54});
    _actionTable.add(123, BANG, {SHIFT, 55});
    _actionTable.add(123, INTEGER_LITERAL, {SHIFT, 57});
    _actionTable.add(123, FLOAT_LITERAL, {SHIFT, 58});
    _actionTable.add(123, CHAR_LITERAL, {SHIFT, 59});
    _actionTable.add(123, PLUS_PLUS, {SHIFT, 60});
    _actionTable.add(123, MINUS_MINUS, {SHIFT, 61});
    _gotoTable.add(123, UNARY_EXPR, 152);
    _gotoTable.add(123, INCREMENT_EXPR, 69);
    _gotoTable.add(123, DEREFERENCE_EXPR, 71);
    _gotoTable.add(123, PRIMARY_EXPR, 72);

    // State 124
    _actionTable.add(124, IDENTIFIER, {SHIFT, 51});
    _actionTable.add(124, OPEN_PAREN, {SHIFT, 52});
    _actionTable.add(124, STAR, {SHIFT, 53});
    _actionTable.add(124, MINUS, {SHIFT, 54});
    _actionTable.add(124, BANG, {SHIFT, 55});
    _actionTable.add(124, INTEGER_LITERAL, {SHIFT, 57});
    _actionTable.add(124, FLOAT_LITERAL, {SHIFT, 58});
    _actionTable.add(124, CHAR_LITERAL, {SHIFT, 59});
    _actionTable.add(124, PLUS_PLUS, {SHIFT, 60});
    _actionTable.add(124, MINUS_MINUS, {SHIFT, 61});
    _gotoTable.add(124, UNARY_EXPR, 153);
    _gotoTable.add(124, INCREMENT_EXPR, 69);
    _gotoTable.add(124, DEREFERENCE_EXPR, 71);
    _gotoTable.add(124, PRIMARY_EXPR, 72);

    // State 125
    _actionTable.add(125, IDENTIFIER, {SHIFT, 51});
    _actionTable.add(125, OPEN_PAREN, {SHIFT, 52});
    _actionTable.add(125, STAR, {SHIFT, 53});
    _actionTable.add(125, MINUS, {SHIFT, 54});
    _actionTable.add(125, BANG, {SHIFT, 55});
    _actionTable.add(125, INTEGER_LITERAL, {SHIFT, 57});
    _actionTable.add(125, FLOAT_LITERAL, {SHIFT, 58});
    _actionTable.add(125, CHAR_LITERAL, {SHIFT, 59});
    _actionTable.add(125, PLUS_PLUS, {SHIFT, 60});
    _actionTable.add(125, MINUS_MINUS, {SHIFT, 61});
    _gotoTable.add(125, UNARY_EXPR, 154);
    _gotoTable.add(125, INCREMENT_EXPR, 69);
    _gotoTable.add(125, DEREFERENCE_EXPR, 71);
    _gotoTable.add(125, PRIMARY_EXPR, 72);

    // State 126
    _actionTable.add(126, IDENTIFIER, {SHIFT, 51});
    _actionTable.add(126, OPEN_PAREN, {SHIFT, 52});
    _actionTable.add(126, OPEN_CURLY, {SHIFT, 155});
    _actionTable.add(126, STAR, {SHIFT, 53});
    _actionTable.add(126, MINUS, {SHIFT, 54});
    _actionTable.add(126, BANG, {SHIFT, 55});
    _actionTable.add(126, AMPERSAND, {SHIFT, 56});
    _actionTable.add(126, INTEGER_LITERAL, {SHIFT, 57});
    _actionTable.add(126, FLOAT_LITERAL, {SHIFT, 58});
    _actionTable.add(126, CHAR_LITERAL, {SHIFT, 59});
    _actionTable.add(126, PLUS_PLUS, {SHIFT, 60});
    _actionTable.add(126, MINUS_MINUS, {SHIFT, 61});
    _gotoTable.add(126, ASSIGN_VALUE, 156);
    _gotoTable.add(126, EXPR, 157);
    _gotoTable.add(126, LOGICAL_EXPR, 64);
    _gotoTable.add(126, RELATIONAL_EXPR, 65);
    _gotoTable.add(126, ADD_EXPR, 66);
    _gotoTable.add(126, MUL_EXPR, 67);
    _gotoTable.add(126, UNARY_EXPR, 68);
    _gotoTable.add(126, INCREMENT_EXPR, 69);
    _gotoTable.add(126, ADDRESS_EXPR, 70);
    _gotoTable.add(126, DEREFERENCE_EXPR, 71);
    _gotoTable.add(126, PRIMARY_EXPR, 72);

    // State 127
    _actionTable.addDefault(127, {REDUCE, 26});

    // State 128
    _actionTable.addDefault(128, {REDUCE, 31});

    // State 129
    _actionTable.addDefault(129, {REDUCE, 24});

    // State 130
    _actionTable.add(130, IDENTIFIER, {SHIFT, 51});
    _actionTable.add(130, OPEN_PAREN, {SHIFT, 52});
    _actionTable.add(130, STAR, {SHIFT, 53});
    _actionTable.add(130, MINUS, {SHIFT, 54});
    _actionTable.add(130, BANG, {SHIFT, 55});
    _actionTable.add(130, AMPERSAND, {SHIFT, 56});
    _actionTable.add(130, INTEGER_LITERAL, {SHIFT, 57});
    _actionTable.add(130, FLOAT_LITERAL, {SHIFT, 58});
    _actionTable.add(130, CHAR_LITERAL, {SHIFT, 59});
    _actionTable.add(130, PLUS_PLUS, {SHIFT, 60});
    _actionTable.add(130, MINUS_MINUS, {SHIFT, 61});
    _gotoTable.add(130, EXPR, 158);
    _gotoTable.add(130, LOGICAL_EXPR, 64);
    _gotoTable.add(130, RELATIONAL_EXPR, 65);
    _gotoTable.add(130, ADD_EXPR, 66);
    _gotoTable.add(130, MUL_EXPR, 67);
    _gotoTable.add(130, UNARY_EXPR, 68);
    _gotoTable.add(130, INCREMENT_EXPR, 69);
    _gotoTable.add(130, ADDRESS_EXPR, 70);
    _gotoTable.add(130, DEREFERENCE_EXPR, 71);
    _gotoTable.add(130, PRIMARY_EXPR, 72);

    // State 131
    _actionTable.addDefault(131, {REDUCE, 33});

    // State 132
    _actionTable.add(132, IDENTIFIER, {SHIFT, 51});
    _actionTable.add(132, OPEN_PAREN, {SHIFT, 52});
    _actionTable.add(132, STAR, {SHIFT, 53});
    _actionTable.add(132, MINUS, {SHIFT, 54});
    _actionTable.add(132, BANG, {SHIFT, 55});
    _actionTable.add(132, AMPERSAND, {SHIFT, 56});
    _actionTable.add(132, INTEGER_LITERAL, {SHIFT, 57});
    _actionTable.add(132, FLOAT_LITERAL, {SHIFT, 58});
    _actionTable.add(132, CHAR_LITERAL, {SHIFT, 59});
    _actionTable.add(132, PLUS_PLUS, {SHIFT, 60});
    _actionTable.add(132, MINUS_MINUS, {SHIFT, 61});
    _gotoTable.add(132, EXPR, 159);
    _gotoTable.add(132, LOGICAL_EXPR, 64);
    _gotoTable.add(132, RELATIONAL_EXPR, 65);
    _gotoTable.add(132, ADD_EXPR, 66);
    _gotoTable.add(132, MUL_EXPR, 67);
    _gotoTable.add(132, UNARY_EXPR, 68);
    _gotoTable.add(132, INCREMENT_EXPR, 69);
    _gotoTable.add(132, ADDRESS_EXPR, 70);
    _gotoTable.add(132, DEREFERENCE_EXPR, 71);
    _gotoTable.add(132, PRIMARY_EXPR, 72);

    // State 133
    _actionTable.add(133, EQUALS, {REDUCE, 34});
    _actionTable.add(133, PLUS_EQUALS, {REDUCE, 34});
    _actionTable.add(133, MINUS_EQUALS, {REDUCE, 34});
    _actionTable.add(133, SLASH_EQUALS, {REDUCE, 34});
    _actionTable.add(133, STAR_EQUALS, {REDUCE, 34});
    _actionTable.add(133, AMPERSAND_EQUALS, {REDUCE, 34});
    _actionTable.add(133, PIPE_EQUALS, {REDUCE, 34});
    _actionTable.add(133, CARET_EQUALS, {REDUCE, 34});
    _actionTable.add(133, TILDE_EQUALS, {REDUCE, 34});
    _actionTable.addDefault(133, {REDUCE, 96});

    // State 134
    _actionTable.add(134, IDENTIFIER, {SHIFT, 27});
    _actionTable.add(134, OPEN_CURLY, {SHIFT, 160});
    _actionTable.add(134, KEYWORD_INT, {SHIFT, 7});
    _actionTable.add(134, KEYWORD_FLOAT, {SHIFT, 8});
    _actionTable.add(134, KEYWORD_CHAR, {SHIFT, 9});
    _actionTable.add(134, STAR, {SHIFT, 30});
    _actionTable.add(134, KEYWORD_IF, {SHIFT, 31});
    _actionTable.add(134, KEYWORD_WHILE, {SHIFT, 32});
    _actionTable.add(134, KEYWORD_FOR, {SHIFT, 33});
    _actionTable.add(134, KEYWORD_RET, {SHIFT, 34});
    _gotoTable.add(134, TYPE, 35);
    _gotoTable.add(134, BASE_TYPE, 14);
    _gotoTable.add(134, SIMPLE_STMT, 161);
    _gotoTable.add(134, VAR_DECL_EXPR, 38);
    _gotoTable.add(134, ASSIGN_EXPR, 39);
    _gotoTable.add(134, ASSIGN_TARGET, 40);
    _gotoTable.add(134, IF_STMT, 162);
    _gotoTable.add(134, WHILE_STMT, 163);
    _gotoTable.add(134, FOR_STMT, 164);
    _gotoTable.add(134, BODY, 165);

    // State 135
    _actionTable.add(135, IDENTIFIER, {SHIFT, 27});
    _actionTable.add(135, OPEN_CURLY, {SHIFT, 160});
    _actionTable.add(135, KEYWORD_INT, {SHIFT, 7});
    _actionTable.add(135, KEYWORD_FLOAT, {SHIFT, 8});
    _actionTable.add(135, KEYWORD_CHAR, {SHIFT, 9});
    _actionTable.add(135, STAR, {SHIFT, 30});
    _actionTable.add(135, KEYWORD_IF, {SHIFT, 31});
    _actionTable.add(135, KEYWORD_WHILE, {SHIFT, 32});
    _actionTable.add(135, KEYWORD_FOR, {SHIFT, 33});
    _actionTable.add(135, KEYWORD_RET, {SHIFT, 34});
    _gotoTable.add(135, TYPE, 35);
    _gotoTable.add(135, BASE_TYPE, 14);
    _gotoTable.add(135, SIMPLE_STMT, 161);
    _gotoTable.add(135, VAR_DECL_EXPR, 38);
    _gotoTable.add(135, ASSIGN_EXPR, 39);
    _gotoTable.add(135, ASSIGN_TARGET, 40);
    _gotoTable.add(135, IF_STMT, 162);
    _gotoTable.add(135, WHILE_STMT, 163);
    _gotoTable.add(135, FOR_STMT, 164);
    _gotoTable.add(135, BODY, 166);

    // State 136
    _actionTable.add(136, IDENTIFIER, {SHIFT, 51});
    _actionTable.add(136, OPEN_PAREN, {SHIFT, 52});
    _actionTable.add(136, STAR, {SHIFT, 53});
    _actionTable.add(136, MINUS, {SHIFT, 54});
    _actionTable.add(136, BANG, {SHIFT, 55});
    _actionTable.add(136, AMPERSAND, {SHIFT, 56});
    _actionTable.add(136, INTEGER_LITERAL, {SHIFT, 57});
    _actionTable.add(136, FLOAT_LITERAL, {SHIFT, 58});
    _actionTable.add(136, CHAR_LITERAL, {SHIFT, 59});
    _actionTable.add(136, PLUS_PLUS, {SHIFT, 60});
    _actionTable.add(136, MINUS_MINUS, {SHIFT, 61});
    _actionTable.addDefault(136, {REDUCE, 53});
    _gotoTable.add(136, EXPR_OPT, 167);
    _gotoTable.add(136, EXPR, 63);
    _gotoTable.add(136, LOGICAL_EXPR, 64);
    _gotoTable.add(136, RELATIONAL_EXPR, 65);
    _gotoTable.add(136, ADD_EXPR, 66);
    _gotoTable.add(136, MUL_EXPR, 67);
    _gotoTable.add(136, UNARY_EXPR, 68);
    _gotoTable.add(136, INCREMENT_EXPR, 69);
    _gotoTable.add(136, ADDRESS_EXPR, 70);
    _gotoTable.add(136, DEREFERENCE_EXPR, 71);
    _gotoTable.add(136, PRIMARY_EXPR, 72);

    // State 137
    _actionTable.add(137, CLOSED_PAREN, {SHIFT, 168});

    // State 138
    _actionTable.add(138, CLOSED_BRACKET, {SHIFT, 169});

    // State 139
    _actionTable.addDefault(139, {REDUCE, 102});

    // State 140
    _actionTable.add(140, LESS_THAN, {SHIFT, 113});
    _actionTable.add(140, GREATER_THAN, {SHIFT, 114});
    _actionTable.add(140, LESS_THAN_EQUALS, {SHIFT, 115});
    _actionTable.add(140, GREATER_THAN_EQUALS, {SHIFT, 116});
    _actionTable.add(140, EQUALS_EQUALS, {SHIFT, 117});
    _actionTable.add(140, BANG_EQUALS, {SHIFT, 118});
    _actionTable.addDefault(140, {REDUCE, 70});

    // State 141
    _actionTable.add(141, LESS_THAN, {SHIFT, 113});
    _actionTable.add(141, GREATER_THAN, {SHIFT, 114});
    _actionTable.add(141, LESS_THAN_EQUALS, {SHIFT, 115});
    _actionTable.add(141, GREATER_THAN_EQUALS, {SHIFT, 116});
    _actionTable.add(141, EQUALS_EQUALS, {SHIFT, 117});
    _actionTable.add(141, BANG_EQUALS, {SHIFT, 118});
    _actionTable.addDefault(141, {REDUCE, 71});

    // State 142
    _actionTable.add(142, MINUS, {SHIFT, 119});
    _actionTable.add(142, PLUS, {SHIFT, 120});
    _actionTable.add(142, PIPE, {SHIFT, 121});
    _actionTable.add(142, CARET, {SHIFT, 122});
    _actionTable.addDefault(142, {REDUCE, 75});

    // State 143
    _actionTable.add(143, MINUS, {SHIFT, 119});
    _actionTable.add(143, PLUS, {SHIFT, 120});
    _actionTable.add(143, PIPE, {SHIFT, 121});
    _actionTable.add(143, CARET, {SHIFT, 122});
    _actionTable.addDefault(143, {REDUCE, 76});

    // State 144
    _actionTable.add(144, MINUS, {SHIFT, 119});
    _actionTable.add(144, PLUS, {SHIFT, 120});
    _actionTable.add(144, PIPE, {SHIFT, 121});
    _actionTable.add(144, CARET, {SHIFT, 122});
    _actionTable.addDefault(144, {REDUCE, 77});

    // State 145
    _actionTable.add(145, MINUS, {SHIFT, 119});
    _actionTable.add(145, PLUS, {SHIFT, 120});
    _actionTable.add(145, PIPE, {SHIFT, 121});
    _actionTable.add(145, CARET, {SHIFT, 122});
    _actionTable.addDefault(145, {REDUCE, 78});

    // State 146
    _actionTable.add(146, MINUS, {SHIFT, 119});
    _actionTable.add(146, PLUS, {SHIFT, 120});
    _actionTable.add(146, PIPE, {SHIFT, 121});
    _actionTable.add(146, CARET, {SHIFT, 122});
    _actionTable.addDefault(146, {REDUCE, 73});

    // State 147
    _actionTable.add(147, MINUS, {SHIFT, 119});
    _actionTable.add(147, PLUS, {SHIFT, 120});
    _actionTable.add(147, PIPE, {SHIFT, 121});
    _actionTable.add(147, CARET, {SHIFT, 122});
    _actionTable.addDefault(147, {REDUCE, 74});

    // State 148
    _actionTable.add(148, STAR, {SHIFT, 123});
    _actionTable.add(148, SLASH, {SHIFT, 124});
    _actionTable.add(148, AMPERSAND, {SHIFT, 125});
    _actionTable.addDefault(148, {REDUCE, 81});

    // State 149
    _actionTable.add(149, STAR, {SHIFT, 123});
    _actionTable.add(149, SLASH, {SHIFT, 124});
    _actionTable.add(149, AMPERSAND, {SHIFT, 125});
    _actionTable.addDefault(149, {REDUCE, 80});

    // State 150
    _actionTable.add(150, STAR, {SHIFT, 123});
    _actionTable.add(150, SLASH, {SHIFT, 124});
    _actionTable.add(150, AMPERSAND, {SHIFT, 125});
    _actionTable.addDefault(150, {REDUCE, 82});

    // State 151
    _actionTable.add(151, STAR, {SHIFT, 123});
    _actionTable.add(151, SLASH, {SHIFT, 124});
    _actionTable.add(151, AMPERSAND, {SHIFT, 125});
    _actionTable.addDefault(151, {REDUCE, 83});

    // State 152
    _actionTable.addDefault(152, {REDUCE, 85});

    // State 153
    _actionTable.addDefault(153, {REDUCE, 86});

    // State 154
    _actionTable.addDefault(154, {REDUCE, 87});

    // State 155
    _actionTable.add(155, IDENTIFIER, {SHIFT, 51});
    _actionTable.add(155, OPEN_PAREN, {SHIFT, 52});
    _actionTable.add(155, STAR, {SHIFT, 53});
    _actionTable.add(155, MINUS, {SHIFT, 54});
    _actionTable.add(155, BANG, {SHIFT, 55});
    _actionTable.add(155, AMPERSAND, {SHIFT, 56});
    _actionTable.add(155, INTEGER_LITERAL, {SHIFT, 57});
    _actionTable.add(155, FLOAT_LITERAL, {SHIFT, 58});
    _actionTable.add(155, CHAR_LITERAL, {SHIFT, 59});
    _actionTable.add(155, PLUS_PLUS, {SHIFT, 60});
    _actionTable.add(155, MINUS_MINUS, {SHIFT, 61});
    _actionTable.addDefault(155, {REDUCE, 63});
    _gotoTable.add(155, EXPR_LIST, 170);
    _gotoTable.add(155, EXPR_LIST_NON_EMPTY, 86);
    _gotoTable.add(155, EXPR, 87);
    _gotoTable.add(155, LOGICAL_EXPR, 64);
    _gotoTable.add(155, RELATIONAL_EXPR, 65);
    _gotoTable.add(155, ADD_EXPR, 66);
    _gotoTable.add(155, MUL_EXPR, 67);
    _gotoTable.add(155, UNARY_EXPR, 68);
    _gotoTable.add(155, INCREMENT_EXPR, 69);
    _gotoTable.add(155, ADDRESS_EXPR, 70);
    _gotoTable.add(155, DEREFERENCE_EXPR, 71);
    _gotoTable.add(155, PRIMARY_EXPR, 72);

    // State 156
    _actionTable.addDefault(156, {REDUCE, 28});

    // State 157
    _actionTable.addDefault(157, {REDUCE, 29});

    // State 158
    _actionTable.addDefault(158, {REDUCE, 66});

    // State 159
    _actionTable.add(159, CLOSED_BRACKET, {SHIFT, 171});

    // State 160
    _actionTable.addDefault(160, {REDUCE, 15});
    _gotoTable.add(160, STMT_LIST, 172);

    // State 161
    _actionTable.add(161, SEMICOLON, {SHIFT, 173});

    // State 162
    _actionTable.addDefault(162, {REDUCE, 60});

    // State 163
    _actionTable.addDefault(163, {REDUCE, 61});

    // State 164
    _actionTable.addDefault(164, {REDUCE, 62});

    // State 165
    _actionTable.add(165, KEYWORD_ELSE, {SHIFT, 174});
    _actionTable.addDefault(165, {REDUCE, 44});

    // State 166
    _actionTable.addDefault(166, {REDUCE, 46});

    // State 167
    _actionTable.add(167, SEMICOLON, {SHIFT, 175});

    // State 168
    _actionTable.addDefault(168, {REDUCE, 103});

    // State 169
    _actionTable.addDefault(169, {REDUCE, 98});

    // State 170
    _actionTable.add(170, CLOSED_CURLY, {SHIFT, 176});

    // State 171
    _actionTable.add(171, EQUALS, {REDUCE, 33});
    _actionTable.add(171, PLUS_EQUALS, {REDUCE, 33});
    _actionTable.add(171, MINUS_EQUALS, {REDUCE, 33});
    _actionTable.add(171, SLASH_EQUALS, {REDUCE, 33});
    _actionTable.add(171, STAR_EQUALS, {REDUCE, 33});
    _actionTable.add(171, AMPERSAND_EQUALS, {REDUCE, 33});
    _actionTable.add(171, PIPE_EQUALS, {REDUCE, 33});
    _actionTable.add(171, CARET_EQUALS, {REDUCE, 33});
    _actionTable.add(171, TILDE_EQUALS, {REDUCE, 33});
    _actionTable.addDefault(171, {REDUCE, 98});

    // State 172
    _actionTable.add(172, IDENTIFIER, {SHIFT, 27});
    _actionTable.add(172, OPEN_CURLY, {SHIFT, 28});
    _actionTable.add(172, CLOSED_CURLY, {SHIFT, 177});
    _actionTable.add(172, KEYWORD_INT, {SHIFT, 7});
    _actionTable.add(172, KEYWORD_FLOAT, {SHIFT, 8});
    _actionTable.add(172, KEYWORD_CHAR, {SHIFT, 9});
    _actionTable.add(172, STAR, {SHIFT, 30});
    _actionTable.add(172, KEYWORD_IF, {SHIFT, 31});
    _actionTable.add(172, KEYWORD_WHILE, {SHIFT, 32});
    _actionTable.add(172, KEYWORD_FOR, {SHIFT, 33});
    _actionTable.add(172, KEYWORD_RET, {SHIFT, 34});
    _gotoTable.add(172, TYPE, 35);
    _gotoTable.add(172, BASE_TYPE, 14);
    _gotoTable.add(172, STMT, 36);
    _gotoTable.add(172, SIMPLE_STMT, 37);
    _gotoTable.add(172, VAR_DECL_EXPR, 38);
    _gotoTable.add(172, ASSIGN_EXPR, 39);
    _gotoTable.add(172, ASSIGN_TARGET, 40);
    _gotoTable.add(172, IF_STMT, 41);
    _gotoTable.add(172, WHILE_STMT, 42);
    _gotoTable.add(172, FOR_STMT, 43);

    // State 173
    _actionTable.addDefault(173, {REDUCE, 59});

    // State 174
    _actionTable.add(174, IDENTIFIER, {SHIFT, 27});
    _actionTable.add(174, OPEN_CURLY, {SHIFT, 160});
    _actionTable.add(174, KEYWORD_INT, {SHIFT, 7});
    _actionTable.add(174, KEYWORD_FLOAT, {SHIFT, 8});
    _actionTable.add(174, KEYWORD_CHAR, {SHIFT, 9});
    _actionTable.add(174, STAR, {SHIFT, 30});
    _actionTable.add(174, KEYWORD_IF, {SHIFT, 31});
    _actionTable.add(174, KEYWORD_WHILE, {SHIFT, 32});
    _actionTable.add(174, KEYWORD_FOR, {SHIFT, 33});
    _actionTable.add(174, KEYWORD_RET, {SHIFT, 34});
    _gotoTable.add(174, TYPE, 35);
    _gotoTable.add(174, BASE_TYPE, 14);
    _gotoTable.add(174, SIMPLE_STMT, 161);
    _gotoTable.add(174, VAR_DECL_EXPR, 38);
    _gotoTable.add(174, ASSIGN_EXPR, 39);
    _gotoTable.add(174, ASSIGN_TARGET, 40);
    _gotoTable.add(174, IF_STMT, 162);
    _gotoTable.add(174, WHILE_STMT, 163);
    _gotoTable.add(174, FOR_STMT, 164);
    _gotoTable.add(174, BODY, 178);

    // State 175
    _actionTable.add(175, IDENTIFIER, {SHIFT, 179});
    _actionTable.add(175, STAR, {SHIFT, 30});
    _actionTable.add(175, PLUS_PLUS, {SHIFT, 60});
    _actionTable.add(175, MINUS_MINUS, {SHIFT, 61});
    _actionTable.addDefault(175, {REDUCE, 55});
    _gotoTable.add(175, ASSIGN_EXPR, 180);
    _gotoTable.add(175, ASSIGN_TARGET, 40);
    _gotoTable.add(175, FOR_UPDATE, 181);
    _gotoTable.add(175, INCREMENT_EXPR, 182);

    // State 176
    _actionTable.addDefault(176, {REDUCE, 30});

    // State 177
    _actionTable.addDefault(177, {REDUCE, 58});

    // State 178
    _actionTable.addDefault(178, {REDUCE, 45});

    // State 179
    _actionTable.add(179, OPEN_BRACKET, {SHIFT, 45});
    _actionTable.add(179, PLUS_PLUS, {SHIFT, 102});
    _actionTable.add(179, MINUS_MINUS, {SHIFT, 103});
    _actionTable.addDefault(179, {REDUCE, 32});

    // State 180
    _actionTable.addDefault(180, {REDUCE, 56});

    // State 181
    _actionTable.add(181, CLOSED_PAREN, {SHIFT, 183});

    // State 182
    _actionTable.addDefault(182, {REDUCE, 57});

    // State 183
    _actionTable.add(183, IDENTIFIER, {SHIFT, 27});
    _actionTable.add(183, OPEN_CURLY, {SHIFT, 160});
    _actionTable.add(183, KEYWORD_INT, {SHIFT, 7});
    _actionTable.add(183, KEYWORD_FLOAT, {SHIFT, 8});
    _actionTable.add(183, KEYWORD_CHAR, {SHIFT, 9});
    _actionTable.add(183, STAR, {SHIFT, 30});
    _actionTable.add(183, KEYWORD_IF, {SHIFT, 31});
    _actionTable.add(183, KEYWORD_WHILE, {SHIFT, 32});
    _actionTable.add(183, KEYWORD_FOR, {SHIFT, 33});
    _actionTable.add(183, KEYWORD_RET, {SHIFT, 34});
    _gotoTable.add(183, TYPE, 35);
    _gotoTable.add(183, BASE_TYPE, 14);
    _gotoTable.add(183, SIMPLE_STMT, 161);
    _gotoTable.add(183, VAR_DECL_EXPR, 38);
    _gotoTable.add(183, ASSIGN_EXPR, 39);
    _gotoTable.add(183, ASSIGN_TARGET, 40);
    _gotoTable.add(183, IF_STMT, 162);
    _gotoTable.add(183, WHILE_STMT, 163);
    _gotoTable.add(183, FOR_STMT, 164);
    _gotoTable.add(183, BODY, 184);

    // State 184
    _actionTable.addDefault(184, {REDUCE, 49});

}


void Parser::initFollowSets()
{
    // **FOLLOW Sets for Non-Terminals**
    _followSets[NonTerminal::START] = {SyntaxKind::END_OF_FILE};
    _followSets[NonTerminal::PROGRAM] = {SyntaxKind::END_OF_FILE, SyntaxKind::KEYWORD_FN};
    _followSets[NonTerminal::FUNCTION_DECL] = {SyntaxKind::END_OF_FILE, SyntaxKind::KEYWORD_FN};
    _followSets[NonTerminal::PARAM_LIST] = {SyntaxKind::CLOSED_PAREN};
    _followSets[NonTerminal::TYPE] = {SyntaxKind::IDENTIFIER, SyntaxKind::OPEN_CURLY};
    _followSets[NonTerminal::STMT_LIST] = {
        SyntaxKind::IDENTIFIER, SyntaxKind::OPEN_PAREN, SyntaxKind::OPEN_CURLY, SyntaxKind::CLOSED_CURLY,
        SyntaxKind::INTEGER_LITERAL, SyntaxKind::STAR, SyntaxKind::KEYWORD_INT, SyntaxKind::KEYWORD_FLOAT,
        SyntaxKind::KEYWORD_CHAR, SyntaxKind::KEYWORD_RET, SyntaxKind::KEYWORD_IF, SyntaxKind::KEYWORD_WHILE,
        SyntaxKind::KEYWORD_FOR};
    _followSets[NonTerminal::PARAM_LIST_NON_EMPTY] = {SyntaxKind::CLOSED_PAREN, SyntaxKind::COMMA};
    _followSets[NonTerminal::PARAM] = {SyntaxKind::CLOSED_PAREN, SyntaxKind::COMMA};
    _followSets[NonTerminal::BASE_TYPE] = {SyntaxKind::IDENTIFIER, SyntaxKind::OPEN_CURLY, SyntaxKind::OPEN_BRACKET, SyntaxKind::STAR};
    _followSets[NonTerminal::STMT] = {
        SyntaxKind::IDENTIFIER, SyntaxKind::OPEN_PAREN, SyntaxKind::OPEN_CURLY, SyntaxKind::CLOSED_CURLY,
        SyntaxKind::INTEGER_LITERAL, SyntaxKind::STAR, SyntaxKind::KEYWORD_INT, SyntaxKind::KEYWORD_FLOAT,
        SyntaxKind::KEYWORD_CHAR, SyntaxKind::KEYWORD_RET, SyntaxKind::KEYWORD_IF, SyntaxKind::KEYWORD_WHILE,
        SyntaxKind::KEYWORD_FOR};
    _followSets[NonTerminal::SIMPLE_STMT] = {SyntaxKind::SEMICOLON};
    _followSets[NonTerminal::IF_STMT] = {
        SyntaxKind::IDENTIFIER, SyntaxKind::OPEN_PAREN, SyntaxKind::OPEN_CURLY, SyntaxKind::CLOSED_CURLY,
        SyntaxKind::INTEGER_LITERAL, SyntaxKind::STAR, SyntaxKind::KEYWORD_INT, SyntaxKind::KEYWORD_FLOAT,
        SyntaxKind::KEYWORD_CHAR, SyntaxKind::KEYWORD_RET, SyntaxKind::KEYWORD_IF, SyntaxKind::KEYWORD_ELSE,
        SyntaxKind::KEYWORD_WHILE, SyntaxKind::KEYWORD_FOR};
    _followSets[NonTerminal::WHILE_STMT] = {
        SyntaxKind::IDENTIFIER, SyntaxKind::OPEN_PAREN, SyntaxKind::OPEN_CURLY, SyntaxKind::CLOSED_CURLY,
        SyntaxKind::INTEGER_LITERAL, SyntaxKind::STAR, SyntaxKind::KEYWORD_INT, SyntaxKind::KEYWORD_FLOAT,
        SyntaxKind::KEYWORD_CHAR, SyntaxKind::KEYWORD_RET, SyntaxKind::KEYWORD_IF, SyntaxKind::KEYWORD_ELSE,
        SyntaxKind::KEYWORD_WHILE, SyntaxKind::KEYWORD_FOR};
    _followSets[NonTerminal::FOR_STMT] = {
        SyntaxKind::IDENTIFIER, SyntaxKind::OPEN_PAREN, SyntaxKind::OPEN_CURLY, SyntaxKind::CLOSED_CURLY,
        SyntaxKind::INTEGER_LITERAL, SyntaxKind::STAR, SyntaxKind::KEYWORD_INT, SyntaxKind::KEYWORD_FLOAT,
        SyntaxKind::KEYWORD_CHAR, SyntaxKind::KEYWORD_RET, SyntaxKind::KEYWORD_IF, SyntaxKind::KEYWORD_ELSE,
        SyntaxKind::KEYWORD_WHILE, SyntaxKind::KEYWORD_FOR};
    _followSets[NonTerminal::VAR_DECL_EXPR] = {SyntaxKind::SEMICOLON};
    _followSets[NonTerminal::ASSIGN_EXPR] = {SyntaxKind::CLOSED_PAREN, SyntaxKind::SEMICOLON};
    _followSets[NonTerminal::EXPR] = {
        SyntaxKind::CLOSED_PAREN, SyntaxKind::CLOSED_CURLY, SyntaxKind::COMMA, SyntaxKind::CLOSED_BRACKET,
        SyntaxKind::SEMICOLON};
    _followSets[NonTerminal::EXPR_OPT] = {SyntaxKind::SEMICOLON};
    _followSets[NonTerminal::INIT_OPT] = {SyntaxKind::SEMICOLON};
    _followSets[NonTerminal::ASSIGN_VALUE] = {SyntaxKind::SEMICOLON};
    _followSets[NonTerminal::EXPR_LIST] = {SyntaxKind::CLOSED_PAREN, SyntaxKind::CLOSED_CURLY};
    _followSets[NonTerminal::ASSIGN_TARGET] = {
        SyntaxKind::EQUALS, SyntaxKind::PLUS_EQUALS, SyntaxKind::MINUS_EQUALS, SyntaxKind::SLASH_EQUALS,
        SyntaxKind::STAR_EQUALS, SyntaxKind::AMPERSAND_EQUALS, SyntaxKind::PIPE_EQUALS, SyntaxKind::CARET_EQUALS,
        SyntaxKind::TILDE_EQUALS};
    _followSets[NonTerminal::ASSIGN_OP] = {
        SyntaxKind::IDENTIFIER, SyntaxKind::OPEN_PAREN, SyntaxKind::INTEGER_LITERAL, SyntaxKind::STAR};
    _followSets[NonTerminal::CONDITION_OP] = {SyntaxKind::CLOSED_PAREN};
    _followSets[NonTerminal::BODY] = {
        SyntaxKind::IDENTIFIER, SyntaxKind::OPEN_PAREN, SyntaxKind::OPEN_CURLY, SyntaxKind::CLOSED_CURLY,
        SyntaxKind::INTEGER_LITERAL, SyntaxKind::STAR, SyntaxKind::KEYWORD_INT, SyntaxKind::KEYWORD_FLOAT,
        SyntaxKind::KEYWORD_CHAR, SyntaxKind::KEYWORD_RET, SyntaxKind::KEYWORD_IF, SyntaxKind::KEYWORD_ELSE,
        SyntaxKind::KEYWORD_WHILE, SyntaxKind::KEYWORD_FOR};
    _followSets[NonTerminal::FOR_INIT] = {SyntaxKind::SEMICOLON};
    _followSets[NonTerminal::FOR_UPDATE] = {SyntaxKind::CLOSED_PAREN};
    _followSets[NonTerminal::INCREMENT_EXPR] = {
        SyntaxKind::CLOSED_PAREN, SyntaxKind::CLOSED_CURLY, SyntaxKind::COMMA, SyntaxKind::CLOSED_BRACKET,
        SyntaxKind::SEMICOLON};
    _followSets[NonTerminal::EXPR_LIST_NON_EMPTY] = {SyntaxKind::CLOSED_PAREN, SyntaxKind::CLOSED_CURLY, SyntaxKind::COMMA};
    _followSets[NonTerminal::LOGICAL_EXPR] = {
        SyntaxKind::CLOSED_PAREN, SyntaxKind::CLOSED_CURLY, SyntaxKind::COMMA, SyntaxKind::CLOSED_BRACKET,
        SyntaxKind::SEMICOLON};
    _followSets[NonTerminal::ADDRESS_EXPR] = {
        SyntaxKind::CLOSED_PAREN, SyntaxKind::CLOSED_CURLY, SyntaxKind::COMMA, SyntaxKind::CLOSED_BRACKET,
        SyntaxKind::SEMICOLON};
    _followSets[NonTerminal::DEREFERENCE_EXPR] = {
        SyntaxKind::CLOSED_PAREN, SyntaxKind::CLOSED_CURLY, SyntaxKind::COMMA, SyntaxKind::CLOSED_BRACKET,
        SyntaxKind::SEMICOLON};
    _followSets[NonTerminal::RELATIONAL_EXPR] = {
        SyntaxKind::CLOSED_PAREN, SyntaxKind::CLOSED_CURLY, SyntaxKind::COMMA, SyntaxKind::CLOSED_BRACKET,
        SyntaxKind::SEMICOLON};
    _followSets[NonTerminal::ADD_EXPR] = {
        SyntaxKind::CLOSED_PAREN, SyntaxKind::CLOSED_CURLY, SyntaxKind::COMMA, SyntaxKind::CLOSED_BRACKET,
        SyntaxKind::SEMICOLON};
    _followSets[NonTerminal::MUL_EXPR] = {
        SyntaxKind::CLOSED_PAREN, SyntaxKind::CLOSED_CURLY, SyntaxKind::COMMA, SyntaxKind::CLOSED_BRACKET,
        SyntaxKind::STAR, SyntaxKind::SEMICOLON};
    _followSets[NonTerminal::UNARY_EXPR] = {
        SyntaxKind::CLOSED_PAREN, SyntaxKind::CLOSED_CURLY, SyntaxKind::COMMA, SyntaxKind::CLOSED_BRACKET,
        SyntaxKind::STAR, SyntaxKind::SEMICOLON};
    _followSets[NonTerminal::PRIMARY_EXPR] = {
        SyntaxKind::CLOSED_PAREN, SyntaxKind::CLOSED_CURLY, SyntaxKind::COMMA, SyntaxKind::CLOSED_BRACKET,
        SyntaxKind::STAR, SyntaxKind::SEMICOLON};

    // **FOLLOW Sets for Terminals**
    // Common set for tokens that start expressions (used by operators)
    std::unordered_set<SyntaxKind> exprStarters = {
        SyntaxKind::IDENTIFIER, SyntaxKind::OPEN_PAREN, SyntaxKind::INTEGER_LITERAL, SyntaxKind::FLOAT_LITERAL,
        SyntaxKind::CHAR_LITERAL, SyntaxKind::STRING_LITERAL, SyntaxKind::STAR, SyntaxKind::AMPERSAND,
        SyntaxKind::BANG, SyntaxKind::PLUS_PLUS, SyntaxKind::MINUS_MINUS, SyntaxKind::MINUS};

    // Binary operators (e.g., +, -, *, /, ||, &&, ==, etc.)
    _followTerminalsSets[SyntaxKind::PIPE_PIPE] = exprStarters;
    _followTerminalsSets[SyntaxKind::AMPERSAND_AMPERSAND] = exprStarters;
    _followTerminalsSets[SyntaxKind::PLUS] = exprStarters;
    _followTerminalsSets[SyntaxKind::MINUS] = exprStarters;
    _followTerminalsSets[SyntaxKind::PIPE] = exprStarters;
    _followTerminalsSets[SyntaxKind::CARET] = exprStarters;
    _followTerminalsSets[SyntaxKind::SLASH] = exprStarters;
    _followTerminalsSets[SyntaxKind::STAR] = exprStarters;
    _followTerminalsSets[SyntaxKind::EQUALS_EQUALS] = exprStarters;
    _followTerminalsSets[SyntaxKind::BANG_EQUALS] = exprStarters;
    _followTerminalsSets[SyntaxKind::LESS_THAN] = exprStarters;
    _followTerminalsSets[SyntaxKind::GREATER_THAN] = exprStarters;
    _followTerminalsSets[SyntaxKind::LESS_THAN_EQUALS] = exprStarters;
    _followTerminalsSets[SyntaxKind::GREATER_THAN_EQUALS] = exprStarters;

    // Assignment operators (e.g., =, +=, -=, etc.)
    _followTerminalsSets[SyntaxKind::EQUALS] = exprStarters;
    _followTerminalsSets[SyntaxKind::PLUS_EQUALS] = exprStarters;
    _followTerminalsSets[SyntaxKind::MINUS_EQUALS] = exprStarters;
    _followTerminalsSets[SyntaxKind::SLASH_EQUALS] = exprStarters;
    _followTerminalsSets[SyntaxKind::STAR_EQUALS] = exprStarters;
    _followTerminalsSets[SyntaxKind::AMPERSAND_EQUALS] = exprStarters;
    _followTerminalsSets[SyntaxKind::PIPE_EQUALS] = exprStarters;
    _followTerminalsSets[SyntaxKind::CARET_EQUALS] = exprStarters;
    _followTerminalsSets[SyntaxKind::TILDE_EQUALS] = exprStarters;

    // Unary operators
    _followTerminalsSets[SyntaxKind::AMPERSAND] = {SyntaxKind::IDENTIFIER}; // Address-of
    _followTerminalsSets[SyntaxKind::BANG] = exprStarters;                  // Logical not
    _followTerminalsSets[SyntaxKind::MINUS] = exprStarters;                 // Unary minus

    // Increment/Decrement operators
    _followTerminalsSets[SyntaxKind::PLUS_PLUS] = {
        SyntaxKind::IDENTIFIER, SyntaxKind::CLOSED_PAREN, SyntaxKind::CLOSED_CURLY, SyntaxKind::COMMA,
        SyntaxKind::CLOSED_BRACKET, SyntaxKind::SEMICOLON};
    _followTerminalsSets[SyntaxKind::MINUS_MINUS] = {
        SyntaxKind::IDENTIFIER, SyntaxKind::CLOSED_PAREN, SyntaxKind::CLOSED_CURLY, SyntaxKind::COMMA,
        SyntaxKind::CLOSED_BRACKET, SyntaxKind::SEMICOLON};

    // Literals
    std::unordered_set<SyntaxKind> literalFollow = {
        SyntaxKind::CLOSED_PAREN, SyntaxKind::CLOSED_CURLY, SyntaxKind::COMMA, SyntaxKind::CLOSED_BRACKET,
        SyntaxKind::SEMICOLON, SyntaxKind::PLUS, SyntaxKind::MINUS, SyntaxKind::STAR, SyntaxKind::SLASH,
        SyntaxKind::PIPE, SyntaxKind::AMPERSAND, SyntaxKind::CARET, SyntaxKind::PIPE_PIPE, SyntaxKind::AMPERSAND_AMPERSAND,
        SyntaxKind::EQUALS_EQUALS, SyntaxKind::BANG_EQUALS, SyntaxKind::LESS_THAN, SyntaxKind::GREATER_THAN,
        SyntaxKind::LESS_THAN_EQUALS, SyntaxKind::GREATER_THAN_EQUALS};
    _followTerminalsSets[SyntaxKind::INTEGER_LITERAL] = literalFollow;
    _followTerminalsSets[SyntaxKind::FLOAT_LITERAL] = literalFollow;
    _followTerminalsSets[SyntaxKind::CHAR_LITERAL] = literalFollow;
    _followTerminalsSets[SyntaxKind::STRING_LITERAL] = literalFollow;

    // Keywords
    _followTerminalsSets[SyntaxKind::KEYWORD_FN] = {SyntaxKind::IDENTIFIER};
    _followTerminalsSets[SyntaxKind::KEYWORD_INT] = {SyntaxKind::IDENTIFIER, SyntaxKind::OPEN_CURLY, SyntaxKind::OPEN_BRACKET, SyntaxKind::STAR};
    _followTerminalsSets[SyntaxKind::KEYWORD_FLOAT] = {SyntaxKind::IDENTIFIER, SyntaxKind::OPEN_CURLY, SyntaxKind::OPEN_BRACKET, SyntaxKind::STAR};
    _followTerminalsSets[SyntaxKind::KEYWORD_CHAR] = {SyntaxKind::IDENTIFIER, SyntaxKind::OPEN_CURLY, SyntaxKind::OPEN_BRACKET, SyntaxKind::STAR};
    _followTerminalsSets[SyntaxKind::KEYWORD_RET] = exprStarters; // Followed by optional expression
    _followTerminalsSets[SyntaxKind::KEYWORD_IF] = {SyntaxKind::OPEN_PAREN};
    _followTerminalsSets[SyntaxKind::KEYWORD_ELSE] = {
        SyntaxKind::OPEN_CURLY, SyntaxKind::IDENTIFIER, SyntaxKind::KEYWORD_INT, SyntaxKind::KEYWORD_FLOAT,
        SyntaxKind::KEYWORD_CHAR, SyntaxKind::KEYWORD_RET, SyntaxKind::KEYWORD_IF, SyntaxKind::KEYWORD_WHILE,
        SyntaxKind::KEYWORD_FOR};
    _followTerminalsSets[SyntaxKind::KEYWORD_WHILE] = {SyntaxKind::OPEN_PAREN};
    _followTerminalsSets[SyntaxKind::KEYWORD_FOR] = {SyntaxKind::OPEN_PAREN};

    // Punctuation
    _followTerminalsSets[SyntaxKind::OPEN_PAREN] = exprStarters;
    _followTerminalsSets[SyntaxKind::CLOSED_PAREN] = {
        SyntaxKind::CLOSED_PAREN, SyntaxKind::CLOSED_CURLY, SyntaxKind::COMMA, SyntaxKind::CLOSED_BRACKET,
        SyntaxKind::SEMICOLON, SyntaxKind::PLUS, SyntaxKind::MINUS, SyntaxKind::STAR, SyntaxKind::SLASH,
        SyntaxKind::PIPE, SyntaxKind::AMPERSAND, SyntaxKind::CARET, SyntaxKind::PIPE_PIPE, SyntaxKind::AMPERSAND_AMPERSAND,
        SyntaxKind::EQUALS_EQUALS, SyntaxKind::BANG_EQUALS, SyntaxKind::LESS_THAN, SyntaxKind::GREATER_THAN,
        SyntaxKind::LESS_THAN_EQUALS, SyntaxKind::GREATER_THAN_EQUALS};
    _followTerminalsSets[SyntaxKind::OPEN_CURLY] = {
        SyntaxKind::IDENTIFIER, SyntaxKind::OPEN_PAREN, SyntaxKind::OPEN_CURLY, SyntaxKind::CLOSED_CURLY,
        SyntaxKind::INTEGER_LITERAL, SyntaxKind::STAR, SyntaxKind::KEYWORD_INT, SyntaxKind::KEYWORD_FLOAT,
        SyntaxKind::KEYWORD_CHAR, SyntaxKind::KEYWORD_RET, SyntaxKind::KEYWORD_IF, SyntaxKind::KEYWORD_WHILE,
        SyntaxKind::KEYWORD_FOR};
    _followTerminalsSets[SyntaxKind::CLOSED_CURLY] = {
        SyntaxKind::IDENTIFIER, SyntaxKind::OPEN_PAREN, SyntaxKind::OPEN_CURLY, SyntaxKind::CLOSED_CURLY,
        SyntaxKind::INTEGER_LITERAL, SyntaxKind::STAR, SyntaxKind::KEYWORD_INT, SyntaxKind::KEYWORD_FLOAT,
        SyntaxKind::KEYWORD_CHAR, SyntaxKind::KEYWORD_RET, SyntaxKind::KEYWORD_IF, SyntaxKind::KEYWORD_ELSE,
        SyntaxKind::KEYWORD_WHILE, SyntaxKind::KEYWORD_FOR};
    _followTerminalsSets[SyntaxKind::OPEN_BRACKET] = exprStarters;
    _followTerminalsSets[SyntaxKind::CLOSED_BRACKET] = {
        SyntaxKind::CLOSED_PAREN, SyntaxKind::CLOSED_CURLY, SyntaxKind::COMMA, SyntaxKind::CLOSED_BRACKET,
        SyntaxKind::SEMICOLON, SyntaxKind::PLUS, SyntaxKind::MINUS, SyntaxKind::STAR, SyntaxKind::SLASH,
        SyntaxKind::PIPE, SyntaxKind::AMPERSAND, SyntaxKind::CARET, SyntaxKind::PIPE_PIPE, SyntaxKind::AMPERSAND_AMPERSAND,
        SyntaxKind::EQUALS_EQUALS, SyntaxKind::BANG_EQUALS, SyntaxKind::LESS_THAN, SyntaxKind::GREATER_THAN,
        SyntaxKind::LESS_THAN_EQUALS, SyntaxKind::GREATER_THAN_EQUALS};
    _followTerminalsSets[SyntaxKind::COMMA] = exprStarters;
    _followTerminalsSets[SyntaxKind::SEMICOLON] = {
        SyntaxKind::IDENTIFIER, SyntaxKind::OPEN_PAREN, SyntaxKind::OPEN_CURLY, SyntaxKind::CLOSED_CURLY,
        SyntaxKind::INTEGER_LITERAL, SyntaxKind::STAR, SyntaxKind::KEYWORD_INT, SyntaxKind::KEYWORD_FLOAT,
        SyntaxKind::KEYWORD_CHAR, SyntaxKind::KEYWORD_RET, SyntaxKind::KEYWORD_IF, SyntaxKind::KEYWORD_WHILE,
        SyntaxKind::KEYWORD_FOR};
    _followTerminalsSets[SyntaxKind::RIGHT_ARROW] = {SyntaxKind::KEYWORD_INT, SyntaxKind::KEYWORD_FLOAT, SyntaxKind::KEYWORD_CHAR};

    // Identifier
    _followTerminalsSets[SyntaxKind::IDENTIFIER] = {
        SyntaxKind::OPEN_PAREN, SyntaxKind::OPEN_BRACKET, SyntaxKind::PLUS_PLUS, SyntaxKind::MINUS_MINUS,
        SyntaxKind::EQUALS, SyntaxKind::PLUS_EQUALS, SyntaxKind::MINUS_EQUALS, SyntaxKind::SLASH_EQUALS,
        SyntaxKind::STAR_EQUALS, SyntaxKind::AMPERSAND_EQUALS, SyntaxKind::PIPE_EQUALS, SyntaxKind::CARET_EQUALS,
        SyntaxKind::TILDE_EQUALS, SyntaxKind::CLOSED_PAREN, SyntaxKind::CLOSED_CURLY, SyntaxKind::COMMA,
        SyntaxKind::CLOSED_BRACKET, SyntaxKind::SEMICOLON, SyntaxKind::PLUS, SyntaxKind::MINUS, SyntaxKind::STAR,
        SyntaxKind::SLASH, SyntaxKind::PIPE, SyntaxKind::AMPERSAND, SyntaxKind::CARET, SyntaxKind::PIPE_PIPE,
        SyntaxKind::AMPERSAND_AMPERSAND, SyntaxKind::EQUALS_EQUALS, SyntaxKind::BANG_EQUALS, SyntaxKind::LESS_THAN,
        SyntaxKind::GREATER_THAN, SyntaxKind::LESS_THAN_EQUALS, SyntaxKind::GREATER_THAN_EQUALS};
}