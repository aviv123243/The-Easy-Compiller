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
    rule.addSymbol(KEYWORD_FN).addSymbol(IDENTIFIER).addSymbol(OPEN_PAREN).addSymbol(PARAM_LIST).addSymbol(CLOSED_PAREN).addSymbol(RIGHT_ARROW).addSymbol(TYPE).addSymbol(OPEN_CURLY).addSymbol(STMT_LIST).addSymbol(CLOSED_CURLY);
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

    // Rule 24: SimpleStmt -> Expr
    rule.setLeft(SIMPLE_STMT);
    rule.addSymbol(EXPR);
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
    rule.addSymbol(KEYWORD_IF).addSymbol(OPEN_PAREN).addSymbol(CONDITION_OP).addSymbol(CLOSED_PAREN).addSymbol(BODY);
    addProductionRule(rule);
    rule.reset();

    // Rule 45: IfStmt -> KEYWORD_IF OPEN_PAREN ConditionOp CLOSED_PAREN Body KEYWORD_ELSE Body
    rule.setLeft(IF_STMT);
    rule.addSymbol(KEYWORD_IF).addSymbol(OPEN_PAREN).addSymbol(CONDITION_OP).addSymbol(CLOSED_PAREN).addSymbol(BODY).addSymbol(KEYWORD_ELSE).addSymbol(BODY);
    addProductionRule(rule);
    rule.reset();

    // Rule 46: WhileStmt -> KEYWORD_WHILE OPEN_PAREN ConditionOp CLOSED_PAREN Body
    rule.setLeft(WHILE_STMT);
    rule.addSymbol(KEYWORD_WHILE).addSymbol(OPEN_PAREN).addSymbol(CONDITION_OP).addSymbol(CLOSED_PAREN).addSymbol(BODY);
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
    rule.addSymbol(KEYWORD_FOR).addSymbol(OPEN_PAREN).addSymbol(FOR_INIT).addSymbol(SEMICOLON).addSymbol(EXPR_OPT).addSymbol(SEMICOLON).addSymbol(FOR_UPDATE).addSymbol(CLOSED_PAREN).addSymbol(BODY);
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

    // Rule 68: Expr -> IncrementExpr
    rule.setLeft(EXPR);
    rule.addSymbol(INCREMENT_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 69: Expr -> AddressExpr
    rule.setLeft(EXPR);
    rule.addSymbol(ADDRESS_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 70: Expr -> DereferenceExpr
    rule.setLeft(EXPR);
    rule.addSymbol(DEREFERENCE_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 71: LogicalExpr -> RelationalExpr
    rule.setLeft(LOGICAL_EXPR);
    rule.addSymbol(RELATIONAL_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 72: LogicalExpr -> LogicalExpr PIPE_PIPE RelationalExpr
    rule.setLeft(LOGICAL_EXPR);
    rule.addSymbol(LOGICAL_EXPR).addSymbol(PIPE_PIPE).addSymbol(RELATIONAL_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 73: LogicalExpr -> LogicalExpr AMPERSAND_AMPERSAND RelationalExpr
    rule.setLeft(LOGICAL_EXPR);
    rule.addSymbol(LOGICAL_EXPR).addSymbol(AMPERSAND_AMPERSAND).addSymbol(RELATIONAL_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 74: RelationalExpr -> AddExpr
    rule.setLeft(RELATIONAL_EXPR);
    rule.addSymbol(ADD_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 75: RelationalExpr -> RelationalExpr EQUALS_EQUALS AddExpr
    rule.setLeft(RELATIONAL_EXPR);
    rule.addSymbol(RELATIONAL_EXPR).addSymbol(EQUALS_EQUALS).addSymbol(ADD_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 76: RelationalExpr -> RelationalExpr BANG_EQUALS AddExpr
    rule.setLeft(RELATIONAL_EXPR);
    rule.addSymbol(RELATIONAL_EXPR).addSymbol(BANG_EQUALS).addSymbol(ADD_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 77: RelationalExpr -> RelationalExpr LESS_THAN AddExpr
    rule.setLeft(RELATIONAL_EXPR);
    rule.addSymbol(RELATIONAL_EXPR).addSymbol(LESS_THAN).addSymbol(ADD_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 78: RelationalExpr -> RelationalExpr GREATER_THAN AddExpr
    rule.setLeft(RELATIONAL_EXPR);
    rule.addSymbol(RELATIONAL_EXPR).addSymbol(GREATER_THAN).addSymbol(ADD_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 79: RelationalExpr -> RelationalExpr LESS_THAN_EQUALS AddExpr
    rule.setLeft(RELATIONAL_EXPR);
    rule.addSymbol(RELATIONAL_EXPR).addSymbol(LESS_THAN_EQUALS).addSymbol(ADD_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 80: RelationalExpr -> RelationalExpr GREATER_THAN_EQUALS AddExpr
    rule.setLeft(RELATIONAL_EXPR);
    rule.addSymbol(RELATIONAL_EXPR).addSymbol(GREATER_THAN_EQUALS).addSymbol(ADD_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 81: AddExpr -> MulExpr
    rule.setLeft(ADD_EXPR);
    rule.addSymbol(MUL_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 82: AddExpr -> AddExpr PLUS MulExpr
    rule.setLeft(ADD_EXPR);
    rule.addSymbol(ADD_EXPR).addSymbol(PLUS).addSymbol(MUL_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 83: AddExpr -> AddExpr MINUS MulExpr
    rule.setLeft(ADD_EXPR);
    rule.addSymbol(ADD_EXPR).addSymbol(MINUS).addSymbol(MUL_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 84: AddExpr -> AddExpr PIPE MulExpr
    rule.setLeft(ADD_EXPR);
    rule.addSymbol(ADD_EXPR).addSymbol(PIPE).addSymbol(MUL_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 85: AddExpr -> AddExpr CARET MulExpr
    rule.setLeft(ADD_EXPR);
    rule.addSymbol(ADD_EXPR).addSymbol(CARET).addSymbol(MUL_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 86: MulExpr -> UnaryExpr
    rule.setLeft(MUL_EXPR);
    rule.addSymbol(UNARY_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 87: MulExpr -> MulExpr STAR UnaryExpr
    rule.setLeft(MUL_EXPR);
    rule.addSymbol(MUL_EXPR).addSymbol(STAR).addSymbol(UNARY_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 88: MulExpr -> MulExpr SLASH UnaryExpr
    rule.setLeft(MUL_EXPR);
    rule.addSymbol(MUL_EXPR).addSymbol(SLASH).addSymbol(UNARY_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 89: MulExpr -> MulExpr AMPERSAND UnaryExpr
    rule.setLeft(MUL_EXPR);
    rule.addSymbol(MUL_EXPR).addSymbol(AMPERSAND).addSymbol(UNARY_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 90: UnaryExpr -> PrimaryExpr
    rule.setLeft(UNARY_EXPR);
    rule.addSymbol(PRIMARY_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 91: UnaryExpr -> MINUS UnaryExpr
    rule.setLeft(UNARY_EXPR);
    rule.addSymbol(MINUS).addSymbol(UNARY_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 92: UnaryExpr -> BANG UnaryExpr
    rule.setLeft(UNARY_EXPR);
    rule.addSymbol(BANG).addSymbol(UNARY_EXPR);
    addProductionRule(rule);
    rule.reset();

    // Rule 93: IncrementExpr -> IDENTIFIER PLUS_PLUS
    rule.setLeft(INCREMENT_EXPR);
    rule.addSymbol(IDENTIFIER).addSymbol(PLUS_PLUS);
    addProductionRule(rule);
    rule.reset();

    // Rule 94: IncrementExpr -> IDENTIFIER MINUS_MINUS
    rule.setLeft(INCREMENT_EXPR);
    rule.addSymbol(IDENTIFIER).addSymbol(MINUS_MINUS);
    addProductionRule(rule);
    rule.reset();

    // Rule 95: IncrementExpr -> PLUS_PLUS IDENTIFIER
    rule.setLeft(INCREMENT_EXPR);
    rule.addSymbol(PLUS_PLUS).addSymbol(IDENTIFIER);
    addProductionRule(rule);
    rule.reset();

    // Rule 96: IncrementExpr -> MINUS_MINUS IDENTIFIER
    rule.setLeft(INCREMENT_EXPR);
    rule.addSymbol(MINUS_MINUS).addSymbol(IDENTIFIER);
    addProductionRule(rule);
    rule.reset();

    // Rule 97: AddressExpr -> AMPERSAND IDENTIFIER
    rule.setLeft(ADDRESS_EXPR);
    rule.addSymbol(AMPERSAND).addSymbol(IDENTIFIER);
    addProductionRule(rule);
    rule.reset();

    // Rule 98: DereferenceExpr -> STAR IDENTIFIER
    rule.setLeft(DEREFERENCE_EXPR);
    rule.addSymbol(STAR).addSymbol(IDENTIFIER);
    addProductionRule(rule);
    rule.reset();

    // Rule 99: PrimaryExpr -> IDENTIFIER
    rule.setLeft(PRIMARY_EXPR);
    rule.addSymbol(IDENTIFIER);
    addProductionRule(rule);
    rule.reset();

    // Rule 100: PrimaryExpr -> IDENTIFIER OPEN_BRACKET Expr CLOSED_BRACKET
    rule.setLeft(PRIMARY_EXPR);
    rule.addSymbol(IDENTIFIER).addSymbol(OPEN_BRACKET).addSymbol(EXPR).addSymbol(CLOSED_BRACKET);
    addProductionRule(rule);
    rule.reset();

    // Rule 101: PrimaryExpr -> INTEGER_LITERAL
    rule.setLeft(PRIMARY_EXPR);
    rule.addSymbol(INTEGER_LITERAL);
    addProductionRule(rule);
    rule.reset();

    // Rule 102: PrimaryExpr -> FLOAT_LITERAL
    rule.setLeft(PRIMARY_EXPR);
    rule.addSymbol(FLOAT_LITERAL);
    addProductionRule(rule);
    rule.reset();

    // Rule 103: PrimaryExpr -> CHAR_LITERAL
    rule.setLeft(PRIMARY_EXPR);
    rule.addSymbol(CHAR_LITERAL);
    addProductionRule(rule);
    rule.reset();

    // Rule 104: PrimaryExpr -> OPEN_PAREN Expr CLOSED_PAREN
    rule.setLeft(PRIMARY_EXPR);
    rule.addSymbol(OPEN_PAREN).addSymbol(EXPR).addSymbol(CLOSED_PAREN);
    addProductionRule(rule);
    rule.reset();

    // Rule 105: PrimaryExpr -> IDENTIFIER OPEN_PAREN ExprList CLOSED_PAREN
    rule.setLeft(PRIMARY_EXPR);
    rule.addSymbol(IDENTIFIER).addSymbol(OPEN_PAREN).addSymbol(EXPR_LIST).addSymbol(CLOSED_PAREN);
    addProductionRule(rule);
    rule.reset();
}

void Parser::fillTables()
{
    // State 0
    _actionTable.addDefault(0, {REDUCE, 1}); // Program -> ε
    _gotoTable.add(0, PROGRAM, 1);

    // State 1
    _actionTable.add(1, END_OF_FILE, {SHIFT, 2});
    _actionTable.add(1, KEYWORD_FN, {SHIFT, 3});
    _gotoTable.add(1, FUNCTION_DECL, 4);

    // State 2
    _actionTable.addDefault(2, {ACCEPT, 0}); // Accept state

    // State 3
    _actionTable.add(3, IDENTIFIER, {SHIFT, 5});

    // State 4
    _actionTable.addDefault(4, {REDUCE, 2}); // Program -> Program FunctionDecl

    // State 5
    _actionTable.add(5, OPEN_PAREN, {SHIFT, 6});

    // State 6
    _actionTable.add(6, KEYWORD_INT, {SHIFT, 7});
    _actionTable.add(6, KEYWORD_FLOAT, {SHIFT, 8});
    _actionTable.add(6, KEYWORD_CHAR, {SHIFT, 9});
    _actionTable.addDefault(6, {REDUCE, 4}); // ParamList -> ε
    _gotoTable.add(6, PARAM_LIST, 10);
    _gotoTable.add(6, PARAM_LIST_NON_EMPTY, 11);
    _gotoTable.add(6, PARAM, 12);
    _gotoTable.add(6, TYPE, 13);
    _gotoTable.add(6, BASE_TYPE, 14);

    // State 7
    _actionTable.addDefault(7, {REDUCE, 12}); // BaseType -> KEYWORD_INT

    // State 8
    _actionTable.addDefault(8, {REDUCE, 13}); // BaseType -> KEYWORD_FLOAT

    // State 9
    _actionTable.addDefault(9, {REDUCE, 14}); // BaseType -> KEYWORD_CHAR

    // State 10
    _actionTable.add(10, CLOSED_PAREN, {SHIFT, 15});

    // State 11
    _actionTable.add(11, COMMA, {SHIFT, 16});
    _actionTable.addDefault(11, {REDUCE, 5}); // ParamList -> ParamListNonEmpty

    // State 12
    _actionTable.addDefault(12, {REDUCE, 6}); // ParamListNonEmpty -> Param

    // State 13
    _actionTable.add(13, IDENTIFIER, {SHIFT, 17});

    // State 14
    _actionTable.add(14, OPEN_BRACKET, {SHIFT, 18});
    _actionTable.add(14, STAR, {SHIFT, 19});
    _actionTable.addDefault(14, {REDUCE, 9}); // Type -> BaseType

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
    _actionTable.addDefault(17, {REDUCE, 8}); // Param -> Type IDENTIFIER

    // State 18
    _actionTable.add(18, INTEGER_LITERAL, {SHIFT, 22});

    // State 19
    _actionTable.addDefault(19, {REDUCE, 11}); // Type -> BaseType STAR

    // State 20
    _actionTable.add(20, KEYWORD_INT, {SHIFT, 7});
    _actionTable.add(20, KEYWORD_FLOAT, {SHIFT, 8});
    _actionTable.add(20, KEYWORD_CHAR, {SHIFT, 9});
    _gotoTable.add(20, TYPE, 23);
    _gotoTable.add(20, BASE_TYPE, 14);

    // State 21
    _actionTable.addDefault(21, {REDUCE, 7}); // ParamListNonEmpty -> ParamListNonEmpty COMMA Param

    // State 22
    _actionTable.add(22, CLOSED_BRACKET, {SHIFT, 24});

    // State 23
    _actionTable.add(23, OPEN_CURLY, {SHIFT, 25});

    // State 24
    _actionTable.addDefault(24, {REDUCE, 10}); // Type -> BaseType OPEN_BRACKET INTEGER_LITERAL CLOSED_BRACKET

    // State 25
    _actionTable.addDefault(25, {REDUCE, 15}); // StmtList -> ε
    _gotoTable.add(25, STMT_LIST, 26);

    // State 26
    _actionTable.add(26, IDENTIFIER, {SHIFT, 27});
    _actionTable.add(26, OPEN_PAREN, {SHIFT, 28});
    _actionTable.add(26, OPEN_CURLY, {SHIFT, 29});
    _actionTable.add(26, CLOSED_CURLY, {SHIFT, 30});
    _actionTable.add(26, KEYWORD_INT, {SHIFT, 7});
    _actionTable.add(26, KEYWORD_FLOAT, {SHIFT, 8});
    _actionTable.add(26, KEYWORD_CHAR, {SHIFT, 9});
    _actionTable.add(26, STAR, {SHIFT, 31});
    _actionTable.add(26, KEYWORD_IF, {SHIFT, 32});
    _actionTable.add(26, KEYWORD_WHILE, {SHIFT, 33});
    _actionTable.add(26, KEYWORD_FOR, {SHIFT, 34});
    _actionTable.add(26, KEYWORD_RET, {SHIFT, 35});
    _actionTable.add(26, MINUS, {SHIFT, 36});
    _actionTable.add(26, BANG, {SHIFT, 37});
    _actionTable.add(26, AMPERSAND, {SHIFT, 38});
    _actionTable.add(26, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(26, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(26, CHAR_LITERAL, {SHIFT, 41});
    _actionTable.add(26, PLUS_PLUS, {SHIFT, 42});
    _actionTable.add(26, MINUS_MINUS, {SHIFT, 43});
    _gotoTable.add(26, TYPE, 44);
    _gotoTable.add(26, BASE_TYPE, 14);
    _gotoTable.add(26, STMT, 45);
    _gotoTable.add(26, SIMPLE_STMT, 46);
    _gotoTable.add(26, VAR_DECL_EXPR, 47);
    _gotoTable.add(26, ASSIGN_EXPR, 48);
    _gotoTable.add(26, ASSIGN_TARGET, 49);
    _gotoTable.add(26, IF_STMT, 50);
    _gotoTable.add(26, WHILE_STMT, 51);
    _gotoTable.add(26, FOR_STMT, 52);
    _gotoTable.add(26, EXPR, 53);
    _gotoTable.add(26, LOGICAL_EXPR, 54);
    _gotoTable.add(26, RELATIONAL_EXPR, 55);
    _gotoTable.add(26, ADD_EXPR, 56);
    _gotoTable.add(26, MUL_EXPR, 57);
    _gotoTable.add(26, UNARY_EXPR, 58);
    _gotoTable.add(26, INCREMENT_EXPR, 59);
    _gotoTable.add(26, ADDRESS_EXPR, 60);
    _gotoTable.add(26, DEREFERENCE_EXPR, 61);
    _gotoTable.add(26, PRIMARY_EXPR, 62);

    // State 27
    _actionTable.add(27, OPEN_PAREN, {SHIFT, 63});
    _actionTable.add(27, OPEN_BRACKET, {SHIFT, 64});
    _actionTable.add(27, PLUS_PLUS, {SHIFT, 65});
    _actionTable.add(27, MINUS_MINUS, {SHIFT, 66});
    _actionTable.add(27, EQUALS, {REDUCE, 32});
    _actionTable.add(27, PLUS_EQUALS, {REDUCE, 32});
    _actionTable.add(27, MINUS_EQUALS, {REDUCE, 32});
    _actionTable.add(27, SLASH_EQUALS, {REDUCE, 32});
    _actionTable.add(27, STAR_EQUALS, {REDUCE, 32});
    _actionTable.add(27, AMPERSAND_EQUALS, {REDUCE, 32});
    _actionTable.add(27, PIPE_EQUALS, {REDUCE, 32});
    _actionTable.add(27, CARET_EQUALS, {REDUCE, 32});
    _actionTable.add(27, TILDE_EQUALS, {REDUCE, 32});
    _actionTable.addDefault(27, {REDUCE, 99});

    // State 28
    _actionTable.add(28, IDENTIFIER, {SHIFT, 67});
    _actionTable.add(28, OPEN_PAREN, {SHIFT, 28});
    _actionTable.add(28, STAR, {SHIFT, 68});
    _actionTable.add(28, MINUS, {SHIFT, 36});
    _actionTable.add(28, BANG, {SHIFT, 37});
    _actionTable.add(28, AMPERSAND, {SHIFT, 38});
    _actionTable.add(28, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(28, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(28, CHAR_LITERAL, {SHIFT, 41});
    _actionTable.add(28, PLUS_PLUS, {SHIFT, 42});
    _actionTable.add(28, MINUS_MINUS, {SHIFT, 43});
    _gotoTable.add(28, EXPR, 69);
    _gotoTable.add(28, LOGICAL_EXPR, 54);
    _gotoTable.add(28, RELATIONAL_EXPR, 55);
    _gotoTable.add(28, ADD_EXPR, 56);
    _gotoTable.add(28, MUL_EXPR, 57);
    _gotoTable.add(28, UNARY_EXPR, 58);
    _gotoTable.add(28, INCREMENT_EXPR, 59);
    _gotoTable.add(28, ADDRESS_EXPR, 60);
    _gotoTable.add(28, DEREFERENCE_EXPR, 61);
    _gotoTable.add(28, PRIMARY_EXPR, 62);

    // State 29
    _actionTable.addDefault(29, {REDUCE, 15}); // StmtList -> ε
    _gotoTable.add(29, STMT_LIST, 70);

    // State 30
    _actionTable.addDefault(30, {REDUCE, 3}); // FunctionDecl -> KEYWORD_FN IDENTIFIER ...

    // State 31
    _actionTable.add(31, IDENTIFIER, {SHIFT, 71});

    // State 32
    _actionTable.add(32, OPEN_PAREN, {SHIFT, 72});

    // State 33
    _actionTable.add(33, OPEN_PAREN, {SHIFT, 73});

    // State 34
    _actionTable.add(34, OPEN_PAREN, {SHIFT, 74});

    // State 35
    _actionTable.add(35, IDENTIFIER, {SHIFT, 67});
    _actionTable.add(35, OPEN_PAREN, {SHIFT, 28});
    _actionTable.add(35, STAR, {SHIFT, 68});
    _actionTable.add(35, MINUS, {SHIFT, 36});
    _actionTable.add(35, BANG, {SHIFT, 37});
    _actionTable.add(35, AMPERSAND, {SHIFT, 38});
    _actionTable.add(35, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(35, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(35, CHAR_LITERAL, {SHIFT, 41});
    _actionTable.add(35, PLUS_PLUS, {SHIFT, 42});
    _actionTable.add(35, MINUS_MINUS, {SHIFT, 43});
    _actionTable.addDefault(35, {REDUCE, 53});
    _gotoTable.add(35, EXPR_OPT, 75);
    _gotoTable.add(35, EXPR, 76);
    _gotoTable.add(35, LOGICAL_EXPR, 54);
    _gotoTable.add(35, RELATIONAL_EXPR, 55);
    _gotoTable.add(35, ADD_EXPR, 56);
    _gotoTable.add(35, MUL_EXPR, 57);
    _gotoTable.add(35, UNARY_EXPR, 58);
    _gotoTable.add(35, INCREMENT_EXPR, 59);
    _gotoTable.add(35, ADDRESS_EXPR, 60);
    _gotoTable.add(35, DEREFERENCE_EXPR, 61);
    _gotoTable.add(35, PRIMARY_EXPR, 62);

    // State 36
    _actionTable.add(36, IDENTIFIER, {SHIFT, 77});
    _actionTable.add(36, OPEN_PAREN, {SHIFT, 28});
    _actionTable.add(36, MINUS, {SHIFT, 36});
    _actionTable.add(36, BANG, {SHIFT, 37});
    _actionTable.add(36, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(36, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(36, CHAR_LITERAL, {SHIFT, 41});
    _gotoTable.add(36, UNARY_EXPR, 78);
    _gotoTable.add(36, PRIMARY_EXPR, 62);

    // State 37
    _actionTable.add(37, IDENTIFIER, {SHIFT, 77});
    _actionTable.add(37, OPEN_PAREN, {SHIFT, 28});
    _actionTable.add(37, MINUS, {SHIFT, 36});
    _actionTable.add(37, BANG, {SHIFT, 37});
    _actionTable.add(37, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(37, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(37, CHAR_LITERAL, {SHIFT, 41});
    _gotoTable.add(37, UNARY_EXPR, 79);
    _gotoTable.add(37, PRIMARY_EXPR, 62);

    // State 38
    _actionTable.add(38, IDENTIFIER, {SHIFT, 80});

    // State 39
    _actionTable.addDefault(39, {REDUCE, 101}); // PrimaryExpr -> INTEGER_LITERAL

    // State 40
    _actionTable.addDefault(40, {REDUCE, 102}); // PrimaryExpr -> FLOAT_LITERAL

    // State 41
    _actionTable.addDefault(41, {REDUCE, 103}); // PrimaryExpr -> CHAR_LITERAL

    // State 42
    _actionTable.add(42, IDENTIFIER, {SHIFT, 81});

    // State 43
    _actionTable.add(43, IDENTIFIER, {SHIFT, 82});

    // State 44
    _actionTable.add(44, IDENTIFIER, {SHIFT, 83});

    // State 45
    _actionTable.addDefault(45, {REDUCE, 16}); // StmtList -> StmtList Stmt

    // State 46
    _actionTable.add(46, SEMICOLON, {SHIFT, 84});

    // State 47
    _actionTable.addDefault(47, {REDUCE, 22}); // SimpleStmt -> VarDeclExpr

    // State 48
    _actionTable.addDefault(48, {REDUCE, 23}); // SimpleStmt -> AssignExpr

    // State 49
    _actionTable.add(49, EQUALS, {SHIFT, 85});
    _actionTable.add(49, PLUS_EQUALS, {SHIFT, 86});
    _actionTable.add(49, MINUS_EQUALS, {SHIFT, 87});
    _actionTable.add(49, SLASH_EQUALS, {SHIFT, 88});
    _actionTable.add(49, STAR_EQUALS, {SHIFT, 89});
    _actionTable.add(49, AMPERSAND_EQUALS, {SHIFT, 90});
    _actionTable.add(49, PIPE_EQUALS, {SHIFT, 91});
    _actionTable.add(49, CARET_EQUALS, {SHIFT, 92});
    _actionTable.add(49, TILDE_EQUALS, {SHIFT, 93});
    _gotoTable.add(49, ASSIGN_OP, 94);

    // State 50
    _actionTable.addDefault(50, {REDUCE, 19}); // Stmt -> IfStmt

    // State 51
    _actionTable.addDefault(51, {REDUCE, 20}); // Stmt -> WhileStmt

    // State 52
    _actionTable.addDefault(52, {REDUCE, 21}); // Stmt -> ForStmt

    // State 53
    _actionTable.addDefault(53, {REDUCE, 24}); // SimpleStmt -> Expr

    // State 54
    _actionTable.add(54, PIPE_PIPE, {SHIFT, 95});
    _actionTable.add(54, AMPERSAND_AMPERSAND, {SHIFT, 96});
    _actionTable.addDefault(54, {REDUCE, 67});

    // State 55
    _actionTable.add(55, LESS_THAN, {SHIFT, 97});
    _actionTable.add(55, GREATER_THAN, {SHIFT, 98});
    _actionTable.add(55, LESS_THAN_EQUALS, {SHIFT, 99});
    _actionTable.add(55, GREATER_THAN_EQUALS, {SHIFT, 100});
    _actionTable.add(55, EQUALS_EQUALS, {SHIFT, 101});
    _actionTable.add(55, BANG_EQUALS, {SHIFT, 102});
    _actionTable.addDefault(55, {REDUCE, 71});

    // State 56
    _actionTable.add(56, MINUS, {SHIFT, 103});
    _actionTable.add(56, PLUS, {SHIFT, 104});
    _actionTable.add(56, PIPE, {SHIFT, 105});
    _actionTable.add(56, CARET, {SHIFT, 106});
    _actionTable.addDefault(56, {REDUCE, 74});

    // State 57
    _actionTable.add(57, STAR, {SHIFT, 107});
    _actionTable.add(57, SLASH, {SHIFT, 108});
    _actionTable.add(57, AMPERSAND, {SHIFT, 109});
    _actionTable.addDefault(57, {REDUCE, 81});

    // State 58
    _actionTable.addDefault(58, {REDUCE, 86}); // MulExpr -> UnaryExpr

    // State 59
    _actionTable.addDefault(59, {REDUCE, 68}); // Expr -> IncrementExpr

    // State 60
    _actionTable.addDefault(60, {REDUCE, 69}); // Expr -> AddressExpr

    // State 61
    _actionTable.addDefault(61, {REDUCE, 70}); // Expr -> DereferenceExpr

    // State 62
    _actionTable.addDefault(62, {REDUCE, 90}); // UnaryExpr -> PrimaryExpr

    // State 63
    _actionTable.add(63, IDENTIFIER, {SHIFT, 67});
    _actionTable.add(63, OPEN_PAREN, {SHIFT, 28});
    _actionTable.add(63, STAR, {SHIFT, 68});
    _actionTable.add(63, MINUS, {SHIFT, 36});
    _actionTable.add(63, BANG, {SHIFT, 37});
    _actionTable.add(63, AMPERSAND, {SHIFT, 38});
    _actionTable.add(63, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(63, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(63, CHAR_LITERAL, {SHIFT, 41});
    _actionTable.add(63, PLUS_PLUS, {SHIFT, 42});
    _actionTable.add(63, MINUS_MINUS, {SHIFT, 43});
    _actionTable.addDefault(63, {REDUCE, 63});
    _gotoTable.add(63, EXPR_LIST, 110);
    _gotoTable.add(63, EXPR_LIST_NON_EMPTY, 111);
    _gotoTable.add(63, EXPR, 112);
    _gotoTable.add(63, LOGICAL_EXPR, 54);
    _gotoTable.add(63, RELATIONAL_EXPR, 55);
    _gotoTable.add(63, ADD_EXPR, 56);
    _gotoTable.add(63, MUL_EXPR, 57);
    _gotoTable.add(63, UNARY_EXPR, 58);
    _gotoTable.add(63, INCREMENT_EXPR, 59);
    _gotoTable.add(63, ADDRESS_EXPR, 60);
    _gotoTable.add(63, DEREFERENCE_EXPR, 61);
    _gotoTable.add(63, PRIMARY_EXPR, 62);

    // State 64
    _actionTable.add(64, IDENTIFIER, {SHIFT, 67});
    _actionTable.add(64, OPEN_PAREN, {SHIFT, 28});
    _actionTable.add(64, STAR, {SHIFT, 68});
    _actionTable.add(64, MINUS, {SHIFT, 36});
    _actionTable.add(64, BANG, {SHIFT, 37});
    _actionTable.add(64, AMPERSAND, {SHIFT, 38});
    _actionTable.add(64, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(64, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(64, CHAR_LITERAL, {SHIFT, 41});
    _actionTable.add(64, PLUS_PLUS, {SHIFT, 42});
    _actionTable.add(64, MINUS_MINUS, {SHIFT, 43});
    _gotoTable.add(64, EXPR, 113);
    _gotoTable.add(64, LOGICAL_EXPR, 54);
    _gotoTable.add(64, RELATIONAL_EXPR, 55);
    _gotoTable.add(64, ADD_EXPR, 56);
    _gotoTable.add(64, MUL_EXPR, 57);
    _gotoTable.add(64, UNARY_EXPR, 58);
    _gotoTable.add(64, INCREMENT_EXPR, 59);
    _gotoTable.add(64, ADDRESS_EXPR, 60);
    _gotoTable.add(64, DEREFERENCE_EXPR, 61);
    _gotoTable.add(64, PRIMARY_EXPR, 62);

    // State 65
    _actionTable.addDefault(65, {REDUCE, 93}); // IncrementExpr -> IDENTIFIER PLUS_PLUS

    // State 66
    _actionTable.addDefault(66, {REDUCE, 94}); // IncrementExpr -> IDENTIFIER MINUS_MINUS

    // State 67
    _actionTable.add(67, OPEN_PAREN, {SHIFT, 63});
    _actionTable.add(67, OPEN_BRACKET, {SHIFT, 114});
    _actionTable.add(67, PLUS_PLUS, {SHIFT, 65});
    _actionTable.add(67, MINUS_MINUS, {SHIFT, 66});
    _actionTable.addDefault(67, {REDUCE, 99});

    // State 68
    _actionTable.add(68, IDENTIFIER, {SHIFT, 115});

    // State 69
    _actionTable.add(69, CLOSED_PAREN, {SHIFT, 116});

    // State 70
    _actionTable.add(70, IDENTIFIER, {SHIFT, 27});
    _actionTable.add(70, OPEN_PAREN, {SHIFT, 28});
    _actionTable.add(70, OPEN_CURLY, {SHIFT, 29});
    _actionTable.add(70, CLOSED_CURLY, {SHIFT, 117});
    _actionTable.add(70, KEYWORD_INT, {SHIFT, 7});
    _actionTable.add(70, KEYWORD_FLOAT, {SHIFT, 8});
    _actionTable.add(70, KEYWORD_CHAR, {SHIFT, 9});
    _actionTable.add(70, STAR, {SHIFT, 31});
    _actionTable.add(70, KEYWORD_IF, {SHIFT, 32});
    _actionTable.add(70, KEYWORD_WHILE, {SHIFT, 33});
    _actionTable.add(70, KEYWORD_FOR, {SHIFT, 34});
    _actionTable.add(70, KEYWORD_RET, {SHIFT, 35});
    _actionTable.add(70, MINUS, {SHIFT, 36});
    _actionTable.add(70, BANG, {SHIFT, 37});
    _actionTable.add(70, AMPERSAND, {SHIFT, 38});
    _actionTable.add(70, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(70, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(70, CHAR_LITERAL, {SHIFT, 41});
    _actionTable.add(70, PLUS_PLUS, {SHIFT, 42});
    _actionTable.add(70, MINUS_MINUS, {SHIFT, 43});
    _gotoTable.add(70, TYPE, 44);
    _gotoTable.add(70, BASE_TYPE, 14);
    _gotoTable.add(70, STMT, 45);
    _gotoTable.add(70, SIMPLE_STMT, 46);
    _gotoTable.add(70, VAR_DECL_EXPR, 47);
    _gotoTable.add(70, ASSIGN_EXPR, 48);
    _gotoTable.add(70, ASSIGN_TARGET, 49);
    _gotoTable.add(70, IF_STMT, 50);
    _gotoTable.add(70, WHILE_STMT, 51);
    _gotoTable.add(70, FOR_STMT, 52);
    _gotoTable.add(70, EXPR, 53);
    _gotoTable.add(70, LOGICAL_EXPR, 54);
    _gotoTable.add(70, RELATIONAL_EXPR, 55);
    _gotoTable.add(70, ADD_EXPR, 56);
    _gotoTable.add(70, MUL_EXPR, 57);
    _gotoTable.add(70, UNARY_EXPR, 58);
    _gotoTable.add(70, INCREMENT_EXPR, 59);
    _gotoTable.add(70, ADDRESS_EXPR, 60);
    _gotoTable.add(70, DEREFERENCE_EXPR, 61);
    _gotoTable.add(70, PRIMARY_EXPR, 62);

    // State 71
    _actionTable.add(71, CLOSED_PAREN, {REDUCE, 98});
    _actionTable.add(71, SEMICOLON, {REDUCE, 98});
    _actionTable.addDefault(71, {REDUCE, 34});

    // State 72
    _actionTable.add(72, IDENTIFIER, {SHIFT, 27});
    _actionTable.add(72, OPEN_PAREN, {SHIFT, 28});
    _actionTable.add(72, STAR, {SHIFT, 31});
    _actionTable.add(72, MINUS, {SHIFT, 36});
    _actionTable.add(72, BANG, {SHIFT, 37});
    _actionTable.add(72, AMPERSAND, {SHIFT, 38});
    _actionTable.add(72, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(72, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(72, CHAR_LITERAL, {SHIFT, 41});
    _actionTable.add(72, PLUS_PLUS, {SHIFT, 42});
    _actionTable.add(72, MINUS_MINUS, {SHIFT, 43});
    _gotoTable.add(72, ASSIGN_EXPR, 118);
    _gotoTable.add(72, ASSIGN_TARGET, 49);
    _gotoTable.add(72, CONDITION_OP, 119);
    _gotoTable.add(72, EXPR, 120);
    _gotoTable.add(72, LOGICAL_EXPR, 54);
    _gotoTable.add(72, RELATIONAL_EXPR, 55);
    _gotoTable.add(72, ADD_EXPR, 56);
    _gotoTable.add(72, MUL_EXPR, 57);
    _gotoTable.add(72, UNARY_EXPR, 58);
    _gotoTable.add(72, INCREMENT_EXPR, 59);
    _gotoTable.add(72, ADDRESS_EXPR, 60);
    _gotoTable.add(72, DEREFERENCE_EXPR, 61);
    _gotoTable.add(72, PRIMARY_EXPR, 62);

    // State 73
    _actionTable.add(73, IDENTIFIER, {SHIFT, 27});
    _actionTable.add(73, OPEN_PAREN, {SHIFT, 28});
    _actionTable.add(73, STAR, {SHIFT, 31});
    _actionTable.add(73, MINUS, {SHIFT, 36});
    _actionTable.add(73, BANG, {SHIFT, 37});
    _actionTable.add(73, AMPERSAND, {SHIFT, 38});
    _actionTable.add(73, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(73, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(73, CHAR_LITERAL, {SHIFT, 41});
    _actionTable.add(73, PLUS_PLUS, {SHIFT, 42});
    _actionTable.add(73, MINUS_MINUS, {SHIFT, 43});
    _gotoTable.add(73, ASSIGN_EXPR, 118);
    _gotoTable.add(73, ASSIGN_TARGET, 49);
    _gotoTable.add(73, CONDITION_OP, 121);
    _gotoTable.add(73, EXPR, 120);
    _gotoTable.add(73, LOGICAL_EXPR, 54);
    _gotoTable.add(73, RELATIONAL_EXPR, 55);
    _gotoTable.add(73, ADD_EXPR, 56);
    _gotoTable.add(73, MUL_EXPR, 57);
    _gotoTable.add(73, UNARY_EXPR, 58);
    _gotoTable.add(73, INCREMENT_EXPR, 59);
    _gotoTable.add(73, ADDRESS_EXPR, 60);
    _gotoTable.add(73, DEREFERENCE_EXPR, 61);
    _gotoTable.add(73, PRIMARY_EXPR, 62);

    // State 74
    _actionTable.add(74, IDENTIFIER, {SHIFT, 122});
    _actionTable.add(74, KEYWORD_INT, {SHIFT, 7});
    _actionTable.add(74, KEYWORD_FLOAT, {SHIFT, 8});
    _actionTable.add(74, KEYWORD_CHAR, {SHIFT, 9});
    _actionTable.add(74, STAR, {SHIFT, 123});
    _actionTable.addDefault(74, {REDUCE, 50});
    _gotoTable.add(74, TYPE, 44);
    _gotoTable.add(74, BASE_TYPE, 14);
    _gotoTable.add(74, VAR_DECL_EXPR, 124);
    _gotoTable.add(74, ASSIGN_EXPR, 125);
    _gotoTable.add(74, ASSIGN_TARGET, 49);
    _gotoTable.add(74, FOR_INIT, 126);

    // State 75
    _actionTable.addDefault(75, {REDUCE, 25}); // SimpleStmt -> KEYWORD_RET ExprOpt

    // State 76
    _actionTable.addDefault(76, {REDUCE, 54}); // ExprOpt -> Expr

    // State 77
    _actionTable.add(77, OPEN_PAREN, {SHIFT, 63});
    _actionTable.add(77, OPEN_BRACKET, {SHIFT, 114});
    _actionTable.addDefault(77, {REDUCE, 99});

    // State 78
    _actionTable.addDefault(78, {REDUCE, 91}); // UnaryExpr -> MINUS UnaryExpr

    // State 79
    _actionTable.addDefault(79, {REDUCE, 92}); // UnaryExpr -> BANG UnaryExpr

    // State 80
    _actionTable.addDefault(80, {REDUCE, 97}); // AddressExpr -> AMPERSAND IDENTIFIER

    // State 81
    _actionTable.addDefault(81, {REDUCE, 95}); // IncrementExpr -> PLUS_PLUS IDENTIFIER

    // State 82
    _actionTable.addDefault(82, {REDUCE, 96}); // IncrementExpr -> MINUS_MINUS IDENTIFIER

    // State 83
    _actionTable.add(83, EQUALS, {SHIFT, 127});
    _actionTable.addDefault(83, {REDUCE, 27});
    _gotoTable.add(83, INIT_OPT, 128);

    // State 84
    _actionTable.addDefault(84, {REDUCE, 17}); // Stmt -> SimpleStmt SEMICOLON

    // State 85
    _actionTable.addDefault(85, {REDUCE, 35}); // AssignOp -> EQUALS

    // State 86
    _actionTable.addDefault(86, {REDUCE, 36}); // AssignOp -> PLUS_EQUALS

    // State 87
    _actionTable.addDefault(87, {REDUCE, 37}); // AssignOp -> MINUS_EQUALS

    // State 88
    _actionTable.addDefault(88, {REDUCE, 38}); // AssignOp -> SLASH_EQUALS

    // State 89
    _actionTable.addDefault(89, {REDUCE, 39}); // AssignOp -> STAR_EQUALS

    // State 90
    _actionTable.addDefault(90, {REDUCE, 40}); // AssignOp -> AMPERSAND_EQUALS

    // State 91
    _actionTable.addDefault(91, {REDUCE, 41}); // AssignOp -> PIPE_EQUALS

    // State 92
    _actionTable.addDefault(92, {REDUCE, 42}); // AssignOp -> CARET_EQUALS

    // State 93
    _actionTable.addDefault(93, {REDUCE, 43}); // AssignOp -> TILDE_EQUALS

    // State 94
    _actionTable.add(94, IDENTIFIER, {SHIFT, 67});
    _actionTable.add(94, OPEN_PAREN, {SHIFT, 28});
    _actionTable.add(94, STAR, {SHIFT, 68});
    _actionTable.add(94, MINUS, {SHIFT, 36});
    _actionTable.add(94, BANG, {SHIFT, 37});
    _actionTable.add(94, AMPERSAND, {SHIFT, 38});
    _actionTable.add(94, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(94, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(94, CHAR_LITERAL, {SHIFT, 41});
    _actionTable.add(94, PLUS_PLUS, {SHIFT, 42});
    _actionTable.add(94, MINUS_MINUS, {SHIFT, 43});
    _gotoTable.add(94, EXPR, 129);
    _gotoTable.add(94, LOGICAL_EXPR, 54);
    _gotoTable.add(94, RELATIONAL_EXPR, 55);
    _gotoTable.add(94, ADD_EXPR, 56);
    _gotoTable.add(94, MUL_EXPR, 57);
    _gotoTable.add(94, UNARY_EXPR, 58);
    _gotoTable.add(94, INCREMENT_EXPR, 59);
    _gotoTable.add(94, ADDRESS_EXPR, 60);
    _gotoTable.add(94, DEREFERENCE_EXPR, 61);
    _gotoTable.add(94, PRIMARY_EXPR, 62);

    // State 95
    _actionTable.add(95, IDENTIFIER, {SHIFT, 77});
    _actionTable.add(95, OPEN_PAREN, {SHIFT, 28});
    _actionTable.add(95, MINUS, {SHIFT, 36});
    _actionTable.add(95, BANG, {SHIFT, 37});
    _actionTable.add(95, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(95, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(95, CHAR_LITERAL, {SHIFT, 41});
    _gotoTable.add(95, RELATIONAL_EXPR, 130);
    _gotoTable.add(95, ADD_EXPR, 56);
    _gotoTable.add(95, MUL_EXPR, 57);
    _gotoTable.add(95, UNARY_EXPR, 58);
    _gotoTable.add(95, PRIMARY_EXPR, 62);

    // State 96
    _actionTable.add(96, IDENTIFIER, {SHIFT, 77});
    _actionTable.add(96, OPEN_PAREN, {SHIFT, 28});
    _actionTable.add(96, MINUS, {SHIFT, 36});
    _actionTable.add(96, BANG, {SHIFT, 37});
    _actionTable.add(96, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(96, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(96, CHAR_LITERAL, {SHIFT, 41});
    _gotoTable.add(96, RELATIONAL_EXPR, 131);
    _gotoTable.add(96, ADD_EXPR, 56);
    _gotoTable.add(96, MUL_EXPR, 57);
    _gotoTable.add(96, UNARY_EXPR, 58);
    _gotoTable.add(96, PRIMARY_EXPR, 62);

    // State 97
    _actionTable.add(97, IDENTIFIER, {SHIFT, 77});
    _actionTable.add(97, OPEN_PAREN, {SHIFT, 28});
    _actionTable.add(97, MINUS, {SHIFT, 36});
    _actionTable.add(97, BANG, {SHIFT, 37});
    _actionTable.add(97, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(97, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(97, CHAR_LITERAL, {SHIFT, 41});
    _gotoTable.add(97, ADD_EXPR, 132);
    _gotoTable.add(97, MUL_EXPR, 57);
    _gotoTable.add(97, UNARY_EXPR, 58);
    _gotoTable.add(97, PRIMARY_EXPR, 62);

    // State 98
    _actionTable.add(98, IDENTIFIER, {SHIFT, 77});
    _actionTable.add(98, OPEN_PAREN, {SHIFT, 28});
    _actionTable.add(98, MINUS, {SHIFT, 36});
    _actionTable.add(98, BANG, {SHIFT, 37});
    _actionTable.add(98, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(98, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(98, CHAR_LITERAL, {SHIFT, 41});
    _gotoTable.add(98, ADD_EXPR, 133);
    _gotoTable.add(98, MUL_EXPR, 57);
    _gotoTable.add(98, UNARY_EXPR, 58);
    _gotoTable.add(98, PRIMARY_EXPR, 62);

    // State 99
    _actionTable.add(99, IDENTIFIER, {SHIFT, 77});
    _actionTable.add(99, OPEN_PAREN, {SHIFT, 28});
    _actionTable.add(99, MINUS, {SHIFT, 36});
    _actionTable.add(99, BANG, {SHIFT, 37});
    _actionTable.add(99, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(99, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(99, CHAR_LITERAL, {SHIFT, 41});
    _gotoTable.add(99, ADD_EXPR, 134);
    _gotoTable.add(99, MUL_EXPR, 57);
    _gotoTable.add(99, UNARY_EXPR, 58);
    _gotoTable.add(99, PRIMARY_EXPR, 62);

    // State 100
    _actionTable.add(100, IDENTIFIER, {SHIFT, 77});
    _actionTable.add(100, OPEN_PAREN, {SHIFT, 28});
    _actionTable.add(100, MINUS, {SHIFT, 36});
    _actionTable.add(100, BANG, {SHIFT, 37});
    _actionTable.add(100, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(100, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(100, CHAR_LITERAL, {SHIFT, 41});
    _gotoTable.add(100, ADD_EXPR, 135);
    _gotoTable.add(100, MUL_EXPR, 57);
    _gotoTable.add(100, UNARY_EXPR, 58);
    _gotoTable.add(100, PRIMARY_EXPR, 62);

    // State 101
    _actionTable.add(101, IDENTIFIER, {SHIFT, 77});
    _actionTable.add(101, OPEN_PAREN, {SHIFT, 28});
    _actionTable.add(101, MINUS, {SHIFT, 36});
    _actionTable.add(101, BANG, {SHIFT, 37});
    _actionTable.add(101, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(101, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(101, CHAR_LITERAL, {SHIFT, 41});
    _gotoTable.add(101, ADD_EXPR, 136);
    _gotoTable.add(101, MUL_EXPR, 57);
    _gotoTable.add(101, UNARY_EXPR, 58);
    _gotoTable.add(101, PRIMARY_EXPR, 62);

    // State 102
    _actionTable.add(102, IDENTIFIER, {SHIFT, 77});
    _actionTable.add(102, OPEN_PAREN, {SHIFT, 28});
    _actionTable.add(102, MINUS, {SHIFT, 36});
    _actionTable.add(102, BANG, {SHIFT, 37});
    _actionTable.add(102, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(102, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(102, CHAR_LITERAL, {SHIFT, 41});
    _gotoTable.add(102, ADD_EXPR, 137);
    _gotoTable.add(102, MUL_EXPR, 57);
    _gotoTable.add(102, UNARY_EXPR, 58);
    _gotoTable.add(102, PRIMARY_EXPR, 62);

    // State 103
    _actionTable.add(103, IDENTIFIER, {SHIFT, 77});
    _actionTable.add(103, OPEN_PAREN, {SHIFT, 28});
    _actionTable.add(103, MINUS, {SHIFT, 36});
    _actionTable.add(103, BANG, {SHIFT, 37});
    _actionTable.add(103, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(103, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(103, CHAR_LITERAL, {SHIFT, 41});
    _gotoTable.add(103, MUL_EXPR, 138);
    _gotoTable.add(103, UNARY_EXPR, 58);
    _gotoTable.add(103, PRIMARY_EXPR, 62);

    // State 104
    _actionTable.add(104, IDENTIFIER, {SHIFT, 77});
    _actionTable.add(104, OPEN_PAREN, {SHIFT, 28});
    _actionTable.add(104, MINUS, {SHIFT, 36});
    _actionTable.add(104, BANG, {SHIFT, 37});
    _actionTable.add(104, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(104, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(104, CHAR_LITERAL, {SHIFT, 41});
    _gotoTable.add(104, MUL_EXPR, 139);
    _gotoTable.add(104, UNARY_EXPR, 58);
    _gotoTable.add(104, PRIMARY_EXPR, 62);

    // State 105
    _actionTable.add(105, IDENTIFIER, {SHIFT, 77});
    _actionTable.add(105, OPEN_PAREN, {SHIFT, 28});
    _actionTable.add(105, MINUS, {SHIFT, 36});
    _actionTable.add(105, BANG, {SHIFT, 37});
    _actionTable.add(105, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(105, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(105, CHAR_LITERAL, {SHIFT, 41});
    _gotoTable.add(105, MUL_EXPR, 140);
    _gotoTable.add(105, UNARY_EXPR, 58);
    _gotoTable.add(105, PRIMARY_EXPR, 62);

    // State 106
    _actionTable.add(106, IDENTIFIER, {SHIFT, 77});
    _actionTable.add(106, OPEN_PAREN, {SHIFT, 28});
    _actionTable.add(106, MINUS, {SHIFT, 36});
    _actionTable.add(106, BANG, {SHIFT, 37});
    _actionTable.add(106, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(106, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(106, CHAR_LITERAL, {SHIFT, 41});
    _gotoTable.add(106, MUL_EXPR, 141);
    _gotoTable.add(106, UNARY_EXPR, 58);
    _gotoTable.add(106, PRIMARY_EXPR, 62);

    // State 107
    _actionTable.add(107, IDENTIFIER, {SHIFT, 77});
    _actionTable.add(107, OPEN_PAREN, {SHIFT, 28});
    _actionTable.add(107, MINUS, {SHIFT, 36});
    _actionTable.add(107, BANG, {SHIFT, 37});
    _actionTable.add(107, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(107, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(107, CHAR_LITERAL, {SHIFT, 41});
    _gotoTable.add(107, UNARY_EXPR, 142);
    _gotoTable.add(107, PRIMARY_EXPR, 62);

    // State 108
    _actionTable.add(108, IDENTIFIER, {SHIFT, 77});
    _actionTable.add(108, OPEN_PAREN, {SHIFT, 28});
    _actionTable.add(108, MINUS, {SHIFT, 36});
    _actionTable.add(108, BANG, {SHIFT, 37});
    _actionTable.add(108, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(108, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(108, CHAR_LITERAL, {SHIFT, 41});
    _gotoTable.add(108, UNARY_EXPR, 143);
    _gotoTable.add(108, PRIMARY_EXPR, 62);

    // State 109
    _actionTable.add(109, IDENTIFIER, {SHIFT, 77});
    _actionTable.add(109, OPEN_PAREN, {SHIFT, 28});
    _actionTable.add(109, MINUS, {SHIFT, 36});
    _actionTable.add(109, BANG, {SHIFT, 37});
    _actionTable.add(109, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(109, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(109, CHAR_LITERAL, {SHIFT, 41});
    _gotoTable.add(109, UNARY_EXPR, 144);
    _gotoTable.add(109, PRIMARY_EXPR, 62);

    // State 110
    _actionTable.add(110, CLOSED_PAREN, {SHIFT, 145});

    // State 111
    _actionTable.add(111, COMMA, {SHIFT, 146});
    _actionTable.addDefault(111, {REDUCE, 64});

    // State 112
    _actionTable.addDefault(112, {REDUCE, 65}); // ExprListNonEmpty -> Expr

    // State 113
    _actionTable.add(113, CLOSED_BRACKET, {SHIFT, 147});

    // State 114
    _actionTable.add(114, IDENTIFIER, {SHIFT, 67});
    _actionTable.add(114, OPEN_PAREN, {SHIFT, 28});
    _actionTable.add(114, STAR, {SHIFT, 68});
    _actionTable.add(114, MINUS, {SHIFT, 36});
    _actionTable.add(114, BANG, {SHIFT, 37});
    _actionTable.add(114, AMPERSAND, {SHIFT, 38});
    _actionTable.add(114, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(114, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(114, CHAR_LITERAL, {SHIFT, 41});
    _actionTable.add(114, PLUS_PLUS, {SHIFT, 42});
    _actionTable.add(114, MINUS_MINUS, {SHIFT, 43});
    _gotoTable.add(114, EXPR, 148);
    _gotoTable.add(114, LOGICAL_EXPR, 54);
    _gotoTable.add(114, RELATIONAL_EXPR, 55);
    _gotoTable.add(114, ADD_EXPR, 56);
    _gotoTable.add(114, MUL_EXPR, 57);
    _gotoTable.add(114, UNARY_EXPR, 58);
    _gotoTable.add(114, INCREMENT_EXPR, 59);
    _gotoTable.add(114, ADDRESS_EXPR, 60);
    _gotoTable.add(114, DEREFERENCE_EXPR, 61);
    _gotoTable.add(114, PRIMARY_EXPR, 62);

    // State 115
    _actionTable.addDefault(115, {REDUCE, 98}); // DereferenceExpr -> STAR IDENTIFIER

    // State 116
    _actionTable.addDefault(116, {REDUCE, 104}); // PrimaryExpr -> OPEN_PAREN Expr CLOSED_PAREN

    // State 117
    _actionTable.addDefault(117, {REDUCE, 18}); // Stmt -> OPEN_CURLY StmtList CLOSED_CURLY

    // State 118
    _actionTable.addDefault(118, {REDUCE, 48}); // ConditionOp -> AssignExpr

    // State 119
    _actionTable.add(119, CLOSED_PAREN, {SHIFT, 149});

    // State 120
    _actionTable.addDefault(120, {REDUCE, 47}); // ConditionOp -> Expr

    // State 121
    _actionTable.add(121, CLOSED_PAREN, {SHIFT, 150});

    // State 122
    _actionTable.add(122, OPEN_BRACKET, {SHIFT, 151});
    _actionTable.addDefault(122, {REDUCE, 32});

    // State 123
    _actionTable.add(123, IDENTIFIER, {SHIFT, 152});

    // State 124
    _actionTable.addDefault(124, {REDUCE, 51}); // ForInit -> VarDeclExpr

    // State 125
    _actionTable.addDefault(125, {REDUCE, 52}); // ForInit -> AssignExpr

    // State 126
    _actionTable.add(126, SEMICOLON, {SHIFT, 153});

    // State 127
    _actionTable.add(127, IDENTIFIER, {SHIFT, 67});
    _actionTable.add(127, OPEN_PAREN, {SHIFT, 28});
    _actionTable.add(127, OPEN_CURLY, {SHIFT, 154});
    _actionTable.add(127, STAR, {SHIFT, 68});
    _actionTable.add(127, MINUS, {SHIFT, 36});
    _actionTable.add(127, BANG, {SHIFT, 37});
    _actionTable.add(127, AMPERSAND, {SHIFT, 38});
    _actionTable.add(127, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(127, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(127, CHAR_LITERAL, {SHIFT, 41});
    _actionTable.add(127, PLUS_PLUS, {SHIFT, 42});
    _actionTable.add(127, MINUS_MINUS, {SHIFT, 43});
    _gotoTable.add(127, ASSIGN_VALUE, 155);
    _gotoTable.add(127, EXPR, 156);
    _gotoTable.add(127, LOGICAL_EXPR, 54);
    _gotoTable.add(127, RELATIONAL_EXPR, 55);
    _gotoTable.add(127, ADD_EXPR, 56);
    _gotoTable.add(127, MUL_EXPR, 57);
    _gotoTable.add(127, UNARY_EXPR, 58);
    _gotoTable.add(127, INCREMENT_EXPR, 59);
    _gotoTable.add(127, ADDRESS_EXPR, 60);
    _gotoTable.add(127, DEREFERENCE_EXPR, 61);
    _gotoTable.add(127, PRIMARY_EXPR, 62);

    // State 128
    _actionTable.addDefault(128, {REDUCE, 26}); // VarDeclExpr -> Type IDENTIFIER InitOpt

    // State 129
    _actionTable.addDefault(129, {REDUCE, 31}); // AssignExpr -> AssignTarget AssignOp Expr

    // State 130
    _actionTable.add(130, LESS_THAN, {SHIFT, 97});
    _actionTable.add(130, GREATER_THAN, {SHIFT, 98});
    _actionTable.add(130, LESS_THAN_EQUALS, {SHIFT, 99});
    _actionTable.add(130, GREATER_THAN_EQUALS, {SHIFT, 100});
    _actionTable.add(130, EQUALS_EQUALS, {SHIFT, 101});
    _actionTable.add(130, BANG_EQUALS, {SHIFT, 102});
    _actionTable.addDefault(130, {REDUCE, 72});

    // State 131
    _actionTable.add(131, LESS_THAN, {SHIFT, 97});
    _actionTable.add(131, GREATER_THAN, {SHIFT, 98});
    _actionTable.add(131, LESS_THAN_EQUALS, {SHIFT, 99});
    _actionTable.add(131, GREATER_THAN_EQUALS, {SHIFT, 100});
    _actionTable.add(131, EQUALS_EQUALS, {SHIFT, 101});
    _actionTable.add(131, BANG_EQUALS, {SHIFT, 102});
    _actionTable.addDefault(131, {REDUCE, 73});

    // State 132
    _actionTable.add(132, MINUS, {SHIFT, 103});
    _actionTable.add(132, PLUS, {SHIFT, 104});
    _actionTable.add(132, PIPE, {SHIFT, 105});
    _actionTable.add(132, CARET, {SHIFT, 106});
    _actionTable.addDefault(132, {REDUCE, 77});

    // State 133
    _actionTable.add(133, MINUS, {SHIFT, 103});
    _actionTable.add(133, PLUS, {SHIFT, 104});
    _actionTable.add(133, PIPE, {SHIFT, 105});
    _actionTable.add(133, CARET, {SHIFT, 106});
    _actionTable.addDefault(133, {REDUCE, 78});

    // State 134
    _actionTable.add(134, MINUS, {SHIFT, 103});
    _actionTable.add(134, PLUS, {SHIFT, 104});
    _actionTable.add(134, PIPE, {SHIFT, 105});
    _actionTable.add(134, CARET, {SHIFT, 106});
    _actionTable.addDefault(134, {REDUCE, 79});

    // State 135
    _actionTable.add(135, MINUS, {SHIFT, 103});
    _actionTable.add(135, PLUS, {SHIFT, 104});
    _actionTable.add(135, PIPE, {SHIFT, 105});
    _actionTable.add(135, CARET, {SHIFT, 106});
    _actionTable.addDefault(135, {REDUCE, 80});

    // State 136
    _actionTable.add(136, MINUS, {SHIFT, 103});
    _actionTable.add(136, PLUS, {SHIFT, 104});
    _actionTable.add(136, PIPE, {SHIFT, 105});
    _actionTable.add(136, CARET, {SHIFT, 106});
    _actionTable.addDefault(136, {REDUCE, 75});

    // State 137
    _actionTable.add(137, MINUS, {SHIFT, 103});
    _actionTable.add(137, PLUS, {SHIFT, 104});
    _actionTable.add(137, PIPE, {SHIFT, 105});
    _actionTable.add(137, CARET, {SHIFT, 106});
    _actionTable.addDefault(137, {REDUCE, 76});

    // State 138
    _actionTable.add(138, STAR, {SHIFT, 107});
    _actionTable.add(138, SLASH, {SHIFT, 108});
    _actionTable.add(138, AMPERSAND, {SHIFT, 109});
    _actionTable.addDefault(138, {REDUCE, 83});

    // State 139
    _actionTable.add(139, STAR, {SHIFT, 107});
    _actionTable.add(139, SLASH, {SHIFT, 108});
    _actionTable.add(139, AMPERSAND, {SHIFT, 109});
    _actionTable.addDefault(139, {REDUCE, 82});

    // State 140
    _actionTable.add(140, STAR, {SHIFT, 107});
    _actionTable.add(140, SLASH, {SHIFT, 108});
    _actionTable.add(140, AMPERSAND, {SHIFT, 109});
    _actionTable.addDefault(140, {REDUCE, 84});

    // State 141
    _actionTable.add(141, STAR, {SHIFT, 107});
    _actionTable.add(141, SLASH, {SHIFT, 108});
    _actionTable.add(141, AMPERSAND, {SHIFT, 109});
    _actionTable.addDefault(141, {REDUCE, 85});

    // State 142
    _actionTable.addDefault(142, {REDUCE, 87}); // MulExpr -> MulExpr STAR UnaryExpr

    // State 143
    _actionTable.addDefault(143, {REDUCE, 88}); // MulExpr -> MulExpr SLASH UnaryExpr

    // State 144
    _actionTable.addDefault(144, {REDUCE, 89}); // MulExpr -> MulExpr AMPERSAND UnaryExpr

    // State 145
    _actionTable.addDefault(145, {REDUCE, 105}); // PrimaryExpr -> IDENTIFIER OPEN_PAREN ExprList CLOSED_PAREN

    // State 146
    _actionTable.add(146, IDENTIFIER, {SHIFT, 67});
    _actionTable.add(146, OPEN_PAREN, {SHIFT, 28});
    _actionTable.add(146, STAR, {SHIFT, 68});
    _actionTable.add(146, MINUS, {SHIFT, 36});
    _actionTable.add(146, BANG, {SHIFT, 37});
    _actionTable.add(146, AMPERSAND, {SHIFT, 38});
    _actionTable.add(146, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(146, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(146, CHAR_LITERAL, {SHIFT, 41});
    _actionTable.add(146, PLUS_PLUS, {SHIFT, 42});
    _actionTable.add(146, MINUS_MINUS, {SHIFT, 43});
    _gotoTable.add(146, EXPR, 157);
    _gotoTable.add(146, LOGICAL_EXPR, 54);
    _gotoTable.add(146, RELATIONAL_EXPR, 55);
    _gotoTable.add(146, ADD_EXPR, 56);
    _gotoTable.add(146, MUL_EXPR, 57);
    _gotoTable.add(146, UNARY_EXPR, 58);
    _gotoTable.add(146, INCREMENT_EXPR, 59);
    _gotoTable.add(146, ADDRESS_EXPR, 60);
    _gotoTable.add(146, DEREFERENCE_EXPR, 61);
    _gotoTable.add(146, PRIMARY_EXPR, 62);

    // State 147
    _actionTable.add(147, EQUALS, {REDUCE, 33});
    _actionTable.add(147, PLUS_EQUALS, {REDUCE, 33});
    _actionTable.add(147, MINUS_EQUALS, {REDUCE, 33});
    _actionTable.add(147, SLASH_EQUALS, {REDUCE, 33});
    _actionTable.add(147, STAR_EQUALS, {REDUCE, 33});
    _actionTable.add(147, AMPERSAND_EQUALS, {REDUCE, 33});
    _actionTable.add(147, PIPE_EQUALS, {REDUCE, 33});
    _actionTable.add(147, CARET_EQUALS, {REDUCE, 33});
    _actionTable.add(147, TILDE_EQUALS, {REDUCE, 33});
    _actionTable.addDefault(147, {REDUCE, 100});

    // State 148
    _actionTable.add(148, CLOSED_BRACKET, {SHIFT, 158});

    // State 149
    _actionTable.add(149, IDENTIFIER, {SHIFT, 27});
    _actionTable.add(149, OPEN_PAREN, {SHIFT, 28});
    _actionTable.add(149, OPEN_CURLY, {SHIFT, 159});
    _actionTable.add(149, KEYWORD_INT, {SHIFT, 7});
    _actionTable.add(149, KEYWORD_FLOAT, {SHIFT, 8});
    _actionTable.add(149, KEYWORD_CHAR, {SHIFT, 9});
    _actionTable.add(149, STAR, {SHIFT, 31});
    _actionTable.add(149, KEYWORD_IF, {SHIFT, 32});
    _actionTable.add(149, KEYWORD_WHILE, {SHIFT, 33});
    _actionTable.add(149, KEYWORD_FOR, {SHIFT, 34});
    _actionTable.add(149, KEYWORD_RET, {SHIFT, 35});
    _actionTable.add(149, MINUS, {SHIFT, 36});
    _actionTable.add(149, BANG, {SHIFT, 37});
    _actionTable.add(149, AMPERSAND, {SHIFT, 38});
    _actionTable.add(149, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(149, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(149, CHAR_LITERAL, {SHIFT, 41});
    _actionTable.add(149, PLUS_PLUS, {SHIFT, 42});
    _actionTable.add(149, MINUS_MINUS, {SHIFT, 43});
    _gotoTable.add(149, TYPE, 44);
    _gotoTable.add(149, BASE_TYPE, 14);
    _gotoTable.add(149, SIMPLE_STMT, 160);
    _gotoTable.add(149, VAR_DECL_EXPR, 47);
    _gotoTable.add(149, ASSIGN_EXPR, 48);
    _gotoTable.add(149, ASSIGN_TARGET, 49);
    _gotoTable.add(149, IF_STMT, 161);
    _gotoTable.add(149, WHILE_STMT, 162);
    _gotoTable.add(149, FOR_STMT, 163);
    _gotoTable.add(149, BODY, 164);
    _gotoTable.add(149, EXPR, 53);
    _gotoTable.add(149, LOGICAL_EXPR, 54);
    _gotoTable.add(149, RELATIONAL_EXPR, 55);
    _gotoTable.add(149, ADD_EXPR, 56);
    _gotoTable.add(149, MUL_EXPR, 57);
    _gotoTable.add(149, UNARY_EXPR, 58);
    _gotoTable.add(149, INCREMENT_EXPR, 59);
    _gotoTable.add(149, ADDRESS_EXPR, 60);
    _gotoTable.add(149, DEREFERENCE_EXPR, 61);
    _gotoTable.add(149, PRIMARY_EXPR, 62);

    // State 150
    _actionTable.add(150, IDENTIFIER, {SHIFT, 27});
    _actionTable.add(150, OPEN_PAREN, {SHIFT, 28});
    _actionTable.add(150, OPEN_CURLY, {SHIFT, 159});
    _actionTable.add(150, KEYWORD_INT, {SHIFT, 7});
    _actionTable.add(150, KEYWORD_FLOAT, {SHIFT, 8});
    _actionTable.add(150, KEYWORD_CHAR, {SHIFT, 9});
    _actionTable.add(150, STAR, {SHIFT, 31});
    _actionTable.add(150, KEYWORD_IF, {SHIFT, 32});
    _actionTable.add(150, KEYWORD_WHILE, {SHIFT, 33});
    _actionTable.add(150, KEYWORD_FOR, {SHIFT, 34});
    _actionTable.add(150, KEYWORD_RET, {SHIFT, 35});
    _actionTable.add(150, MINUS, {SHIFT, 36});
    _actionTable.add(150, BANG, {SHIFT, 37});
    _actionTable.add(150, AMPERSAND, {SHIFT, 38});
    _actionTable.add(150, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(150, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(150, CHAR_LITERAL, {SHIFT, 41});
    _actionTable.add(150, PLUS_PLUS, {SHIFT, 42});
    _actionTable.add(150, MINUS_MINUS, {SHIFT, 43});
    _gotoTable.add(150, TYPE, 44);
    _gotoTable.add(150, BASE_TYPE, 14);
    _gotoTable.add(150, SIMPLE_STMT, 160);
    _gotoTable.add(150, VAR_DECL_EXPR, 47);
    _gotoTable.add(150, ASSIGN_EXPR, 48);
    _gotoTable.add(150, ASSIGN_TARGET, 49);
    _gotoTable.add(150, IF_STMT, 161);
    _gotoTable.add(150, WHILE_STMT, 162);
    _gotoTable.add(150, FOR_STMT, 163);
    _gotoTable.add(150, BODY, 165);
    _gotoTable.add(150, EXPR, 53);
    _gotoTable.add(150, LOGICAL_EXPR, 54);
    _gotoTable.add(150, RELATIONAL_EXPR, 55);
    _gotoTable.add(150, ADD_EXPR, 56);
    _gotoTable.add(150, MUL_EXPR, 57);
    _gotoTable.add(150, UNARY_EXPR, 58);
    _gotoTable.add(150, INCREMENT_EXPR, 59);
    _gotoTable.add(150, ADDRESS_EXPR, 60);
    _gotoTable.add(150, DEREFERENCE_EXPR, 61);
    _gotoTable.add(150, PRIMARY_EXPR, 62);

    // State 151
    _actionTable.add(151, IDENTIFIER, {SHIFT, 67});
    _actionTable.add(151, OPEN_PAREN, {SHIFT, 28});
    _actionTable.add(151, STAR, {SHIFT, 68});
    _actionTable.add(151, MINUS, {SHIFT, 36});
    _actionTable.add(151, BANG, {SHIFT, 37});
    _actionTable.add(151, AMPERSAND, {SHIFT, 38});
    _actionTable.add(151, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(151, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(151, CHAR_LITERAL, {SHIFT, 41});
    _actionTable.add(151, PLUS_PLUS, {SHIFT, 42});
    _actionTable.add(151, MINUS_MINUS, {SHIFT, 43});
    _gotoTable.add(151, EXPR, 166);
    _gotoTable.add(151, LOGICAL_EXPR, 54);
    _gotoTable.add(151, RELATIONAL_EXPR, 55);
    _gotoTable.add(151, ADD_EXPR, 56);
    _gotoTable.add(151, MUL_EXPR, 57);
    _gotoTable.add(151, UNARY_EXPR, 58);
    _gotoTable.add(151, INCREMENT_EXPR, 59);
    _gotoTable.add(151, ADDRESS_EXPR, 60);
    _gotoTable.add(151, DEREFERENCE_EXPR, 61);
    _gotoTable.add(151, PRIMARY_EXPR, 62);

    // State 152
    _actionTable.addDefault(152, {REDUCE, 34}); // AssignTarget -> STAR IDENTIFIER

    // State 153
    _actionTable.add(153, IDENTIFIER, {SHIFT, 67});
    _actionTable.add(153, OPEN_PAREN, {SHIFT, 28});
    _actionTable.add(153, STAR, {SHIFT, 68});
    _actionTable.add(153, MINUS, {SHIFT, 36});
    _actionTable.add(153, BANG, {SHIFT, 37});
    _actionTable.add(153, AMPERSAND, {SHIFT, 38});
    _actionTable.add(153, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(153, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(153, CHAR_LITERAL, {SHIFT, 41});
    _actionTable.add(153, PLUS_PLUS, {SHIFT, 42});
    _actionTable.add(153, MINUS_MINUS, {SHIFT, 43});
    _actionTable.addDefault(153, {REDUCE, 53});
    _gotoTable.add(153, EXPR_OPT, 167);
    _gotoTable.add(153, EXPR, 76);
    _gotoTable.add(153, LOGICAL_EXPR, 54);
    _gotoTable.add(153, RELATIONAL_EXPR, 55);
    _gotoTable.add(153, ADD_EXPR, 56);
    _gotoTable.add(153, MUL_EXPR, 57);
    _gotoTable.add(153, UNARY_EXPR, 58);
    _gotoTable.add(153, INCREMENT_EXPR, 59);
    _gotoTable.add(153, ADDRESS_EXPR, 60);
    _gotoTable.add(153, DEREFERENCE_EXPR, 61);
    _gotoTable.add(153, PRIMARY_EXPR, 62);

    // State 154
    _actionTable.add(154, IDENTIFIER, {SHIFT, 67});
    _actionTable.add(154, OPEN_PAREN, {SHIFT, 28});
    _actionTable.add(154, STAR, {SHIFT, 68});
    _actionTable.add(154, MINUS, {SHIFT, 36});
    _actionTable.add(154, BANG, {SHIFT, 37});
    _actionTable.add(154, AMPERSAND, {SHIFT, 38});
    _actionTable.add(154, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(154, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(154, CHAR_LITERAL, {SHIFT, 41});
    _actionTable.add(154, PLUS_PLUS, {SHIFT, 42});
    _actionTable.add(154, MINUS_MINUS, {SHIFT, 43});
    _actionTable.addDefault(154, {REDUCE, 63});
    _gotoTable.add(154, EXPR_LIST, 168);
    _gotoTable.add(154, EXPR_LIST_NON_EMPTY, 111);
    _gotoTable.add(154, EXPR, 112);
    _gotoTable.add(154, LOGICAL_EXPR, 54);
    _gotoTable.add(154, RELATIONAL_EXPR, 55);
    _gotoTable.add(154, ADD_EXPR, 56);
    _gotoTable.add(154, MUL_EXPR, 57);
    _gotoTable.add(154, UNARY_EXPR, 58);
    _gotoTable.add(154, INCREMENT_EXPR, 59);
    _gotoTable.add(154, ADDRESS_EXPR, 60);
    _gotoTable.add(154, DEREFERENCE_EXPR, 61);
    _gotoTable.add(154, PRIMARY_EXPR, 62);

    // State 155
    _actionTable.addDefault(155, {REDUCE, 28}); // InitOpt -> EQUALS AssignValue

    // State 156
    _actionTable.addDefault(156, {REDUCE, 29}); // AssignValue -> Expr

    // State 157
    _actionTable.addDefault(157, {REDUCE, 66}); // ExprListNonEmpty -> ExprListNonEmpty COMMA Expr

    // State 158
    _actionTable.addDefault(158, {REDUCE, 100}); // PrimaryExpr -> IDENTIFIER OPEN_BRACKET Expr CLOSED_BRACKET

    // State 159
    _actionTable.addDefault(159, {REDUCE, 15});
    _gotoTable.add(159, STMT_LIST, 169);

    // State 160
    _actionTable.add(160, SEMICOLON, {SHIFT, 170});

    // State 161
    _actionTable.addDefault(161, {REDUCE, 60}); // Body -> IfStmt

    // State 162
    _actionTable.addDefault(162, {REDUCE, 61}); // Body -> WhileStmt

    // State 163
    _actionTable.addDefault(163, {REDUCE, 62}); // Body -> ForStmt

    // State 164
    _actionTable.add(164, KEYWORD_ELSE, {SHIFT, 171});
    _actionTable.addDefault(164, {REDUCE, 44});

    // State 165
    _actionTable.addDefault(165, {REDUCE, 46}); // WhileStmt -> KEYWORD_WHILE OPEN_PAREN ConditionOp CLOSED_PAREN Body

    // State 166
    _actionTable.add(166, CLOSED_BRACKET, {SHIFT, 172});

    // State 167
    _actionTable.add(167, SEMICOLON, {SHIFT, 173});

    // State 168
    _actionTable.add(168, CLOSED_CURLY, {SHIFT, 174});

    // State 169
    _actionTable.add(169, IDENTIFIER, {SHIFT, 27});
    _actionTable.add(169, OPEN_PAREN, {SHIFT, 28});
    _actionTable.add(169, OPEN_CURLY, {SHIFT, 29});
    _actionTable.add(169, CLOSED_CURLY, {SHIFT, 175});
    _actionTable.add(169, KEYWORD_INT, {SHIFT, 7});
    _actionTable.add(169, KEYWORD_FLOAT, {SHIFT, 8});
    _actionTable.add(169, KEYWORD_CHAR, {SHIFT, 9});
    _actionTable.add(169, STAR, {SHIFT, 31});
    _actionTable.add(169, KEYWORD_IF, {SHIFT, 32});
    _actionTable.add(169, KEYWORD_WHILE, {SHIFT, 33});
    _actionTable.add(169, KEYWORD_FOR, {SHIFT, 34});
    _actionTable.add(169, KEYWORD_RET, {SHIFT, 35});
    _actionTable.add(169, MINUS, {SHIFT, 36});
    _actionTable.add(169, BANG, {SHIFT, 37});
    _actionTable.add(169, AMPERSAND, {SHIFT, 38});
    _actionTable.add(169, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(169, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(169, CHAR_LITERAL, {SHIFT, 41});
    _actionTable.add(169, PLUS_PLUS, {SHIFT, 42});
    _actionTable.add(169, MINUS_MINUS, {SHIFT, 43});
    _gotoTable.add(169, TYPE, 44);
    _gotoTable.add(169, BASE_TYPE, 14);
    _gotoTable.add(169, STMT, 45);
    _gotoTable.add(169, SIMPLE_STMT, 46);
    _gotoTable.add(169, VAR_DECL_EXPR, 47);
    _gotoTable.add(169, ASSIGN_EXPR, 48);
    _gotoTable.add(169, ASSIGN_TARGET, 49);
    _gotoTable.add(169, IF_STMT, 50);
    _gotoTable.add(169, WHILE_STMT, 51);
    _gotoTable.add(169, FOR_STMT, 52);
    _gotoTable.add(169, EXPR, 53);
    _gotoTable.add(169, LOGICAL_EXPR, 54);
    _gotoTable.add(169, RELATIONAL_EXPR, 55);
    _gotoTable.add(169, ADD_EXPR, 56);
    _gotoTable.add(169, MUL_EXPR, 57);
    _gotoTable.add(169, UNARY_EXPR, 58);
    _gotoTable.add(169, INCREMENT_EXPR, 59);
    _gotoTable.add(169, ADDRESS_EXPR, 60);
    _gotoTable.add(169, DEREFERENCE_EXPR, 61);
    _gotoTable.add(169, PRIMARY_EXPR, 62);

    // State 170
    _actionTable.addDefault(170, {REDUCE, 59}); // Body -> SimpleStmt SEMICOLON

    // State 171
    _actionTable.add(171, IDENTIFIER, {SHIFT, 27});
    _actionTable.add(171, OPEN_PAREN, {SHIFT, 28});
    _actionTable.add(171, OPEN_CURLY, {SHIFT, 159});
    _actionTable.add(171, KEYWORD_INT, {SHIFT, 7});
    _actionTable.add(171, KEYWORD_FLOAT, {SHIFT, 8});
    _actionTable.add(171, KEYWORD_CHAR, {SHIFT, 9});
    _actionTable.add(171, STAR, {SHIFT, 31});
    _actionTable.add(171, KEYWORD_IF, {SHIFT, 32});
    _actionTable.add(171, KEYWORD_WHILE, {SHIFT, 33});
    _actionTable.add(171, KEYWORD_FOR, {SHIFT, 34});
    _actionTable.add(171, KEYWORD_RET, {SHIFT, 35});
    _actionTable.add(171, MINUS, {SHIFT, 36});
    _actionTable.add(171, BANG, {SHIFT, 37});
    _actionTable.add(171, AMPERSAND, {SHIFT, 38});
    _actionTable.add(171, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(171, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(171, CHAR_LITERAL, {SHIFT, 41});
    _actionTable.add(171, PLUS_PLUS, {SHIFT, 42});
    _actionTable.add(171, MINUS_MINUS, {SHIFT, 43});
    _gotoTable.add(171, TYPE, 44);
    _gotoTable.add(171, BASE_TYPE, 14);
    _gotoTable.add(171, SIMPLE_STMT, 160);
    _gotoTable.add(171, VAR_DECL_EXPR, 47);
    _gotoTable.add(171, ASSIGN_EXPR, 48);
    _gotoTable.add(171, ASSIGN_TARGET, 49);
    _gotoTable.add(171, IF_STMT, 161);
    _gotoTable.add(171, WHILE_STMT, 162);
    _gotoTable.add(171, FOR_STMT, 163);
    _gotoTable.add(171, BODY, 176);
    _gotoTable.add(171, EXPR, 53);
    _gotoTable.add(171, LOGICAL_EXPR, 54);
    _gotoTable.add(171, RELATIONAL_EXPR, 55);
    _gotoTable.add(171, ADD_EXPR, 56);
    _gotoTable.add(171, MUL_EXPR, 57);
    _gotoTable.add(171, UNARY_EXPR, 58);
    _gotoTable.add(171, INCREMENT_EXPR, 59);
    _gotoTable.add(171, ADDRESS_EXPR, 60);
    _gotoTable.add(171, DEREFERENCE_EXPR, 61);
    _gotoTable.add(171, PRIMARY_EXPR, 62);

    // State 172
    _actionTable.addDefault(172, {REDUCE, 33}); // AssignTarget -> IDENTIFIER OPEN_BRACKET Expr CLOSED_BRACKET

    // State 173
    _actionTable.add(173, IDENTIFIER, {SHIFT, 177});
    _actionTable.add(173, STAR, {SHIFT, 123});
    _actionTable.add(173, PLUS_PLUS, {SHIFT, 42});
    _actionTable.add(173, MINUS_MINUS, {SHIFT, 43});
    _actionTable.addDefault(173, {REDUCE, 55}); // ForUpdate -> (empty)
    _gotoTable.add(173, ASSIGN_EXPR, 178);
    _gotoTable.add(173, ASSIGN_TARGET, 49);
    _gotoTable.add(173, FOR_UPDATE, 179);
    _gotoTable.add(173, INCREMENT_EXPR, 180);

    // State 174
    _actionTable.addDefault(174, {REDUCE, 30}); // AssignValue -> OPEN_CURLY ExprList CLOSED_CURLY

    // State 175
    _actionTable.addDefault(175, {REDUCE, 58}); // Body -> OPEN_CURLY StmtList CLOSED_CURLY

    // State 176
    _actionTable.addDefault(176, {REDUCE, 45}); // IfStmt -> KEYWORD_IF OPEN_PAREN ConditionOp CLOSED mascarPAREN Body KEYWORD_ELSE Body

    // State 177
    _actionTable.add(177, OPEN_BRACKET, {SHIFT, 151});
    _actionTable.add(177, PLUS_PLUS, {SHIFT, 65});
    _actionTable.add(177, MINUS_MINUS, {SHIFT, 66});
    _actionTable.addDefault(177, {REDUCE, 32}); // AssignTarget -> IDENTIFIER

    // State 178
    _actionTable.addDefault(178, {REDUCE, 56}); // ForUpdate -> AssignExpr

    // State 179
    _actionTable.add(179, CLOSED_PAREN, {SHIFT, 181});

    // State 180
    _actionTable.addDefault(180, {REDUCE, 57}); // ForUpdate -> IncrementExpr

    // State 181
    _actionTable.add(181, IDENTIFIER, {SHIFT, 27});
    _actionTable.add(181, OPEN_PAREN, {SHIFT, 28});
    _actionTable.add(181, OPEN_CURLY, {SHIFT, 159});
    _actionTable.add(181, KEYWORD_INT, {SHIFT, 7});
    _actionTable.add(181, KEYWORD_FLOAT, {SHIFT, 8});
    _actionTable.add(181, KEYWORD_CHAR, {SHIFT, 9});
    _actionTable.add(181, STAR, {SHIFT, 31});
    _actionTable.add(181, KEYWORD_IF, {SHIFT, 32});
    _actionTable.add(181, KEYWORD_WHILE, {SHIFT, 33});
    _actionTable.add(181, KEYWORD_FOR, {SHIFT, 34});
    _actionTable.add(181, KEYWORD_RET, {SHIFT, 35});
    _actionTable.add(181, MINUS, {SHIFT, 36});
    _actionTable.add(181, BANG, {SHIFT, 37});
    _actionTable.add(181, AMPERSAND, {SHIFT, 38});
    _actionTable.add(181, INTEGER_LITERAL, {SHIFT, 39});
    _actionTable.add(181, FLOAT_LITERAL, {SHIFT, 40});
    _actionTable.add(181, CHAR_LITERAL, {SHIFT, 41});
    _actionTable.add(181, PLUS_PLUS, {SHIFT, 42});
    _actionTable.add(181, MINUS_MINUS, {SHIFT, 43});
    _gotoTable.add(181, TYPE, 44);
    _gotoTable.add(181, BASE_TYPE, 14);
    _gotoTable.add(181, SIMPLE_STMT, 160);
    _gotoTable.add(181, VAR_DECL_EXPR, 47);
    _gotoTable.add(181, ASSIGN_EXPR, 48);
    _gotoTable.add(181, ASSIGN_TARGET, 49);
    _gotoTable.add(181, IF_STMT, 161);
    _gotoTable.add(181, WHILE_STMT, 162);
    _gotoTable.add(181, FOR_STMT, 163);
    _gotoTable.add(181, BODY, 182);
    _gotoTable.add(181, EXPR, 53);
    _gotoTable.add(181, LOGICAL_EXPR, 54);
    _gotoTable.add(181, RELATIONAL_EXPR, 55);
    _gotoTable.add(181, ADD_EXPR, 56);
    _gotoTable.add(181, MUL_EXPR, 57);
    _gotoTable.add(181, UNARY_EXPR, 58);
    _gotoTable.add(181, INCREMENT_EXPR, 59);
    _gotoTable.add(181, ADDRESS_EXPR, 60);
    _gotoTable.add(181, DEREFERENCE_EXPR, 61);
    _gotoTable.add(181, PRIMARY_EXPR, 62);

    // State 182
    _actionTable.addDefault(182, {REDUCE, 49}); // ForStmt -> KEYWORD_FOR OPEN_PAREN ForInit SEMICOLON ExprOpt SEMICOLON ForUpdate CLOSED_PAREN Body
}

void Parser::initFollowSets() {
    // **FOLLOW Sets for Non-Terminals**
    _followSets[NonTerminal::START] = { SyntaxKind::END_OF_FILE };
    _followSets[NonTerminal::PROGRAM] = { SyntaxKind::END_OF_FILE, SyntaxKind::KEYWORD_FN };
    _followSets[NonTerminal::FUNCTION_DECL] = { SyntaxKind::END_OF_FILE, SyntaxKind::KEYWORD_FN };
    _followSets[NonTerminal::PARAM_LIST] = { SyntaxKind::CLOSED_PAREN };
    _followSets[NonTerminal::TYPE] = { SyntaxKind::IDENTIFIER, SyntaxKind::OPEN_CURLY };
    _followSets[NonTerminal::STMT_LIST] = {
        SyntaxKind::IDENTIFIER, SyntaxKind::OPEN_PAREN, SyntaxKind::OPEN_CURLY, SyntaxKind::CLOSED_CURLY,
        SyntaxKind::INTEGER_LITERAL, SyntaxKind::STAR, SyntaxKind::KEYWORD_INT, SyntaxKind::KEYWORD_FLOAT,
        SyntaxKind::KEYWORD_CHAR, SyntaxKind::KEYWORD_RET, SyntaxKind::KEYWORD_IF, SyntaxKind::KEYWORD_WHILE,
        SyntaxKind::KEYWORD_FOR
    };
    _followSets[NonTerminal::PARAM_LIST_NON_EMPTY] = { SyntaxKind::CLOSED_PAREN, SyntaxKind::COMMA };
    _followSets[NonTerminal::PARAM] = { SyntaxKind::CLOSED_PAREN, SyntaxKind::COMMA };
    _followSets[NonTerminal::BASE_TYPE] = { SyntaxKind::IDENTIFIER, SyntaxKind::OPEN_CURLY, SyntaxKind::OPEN_BRACKET, SyntaxKind::STAR };
    _followSets[NonTerminal::STMT] = {
        SyntaxKind::IDENTIFIER, SyntaxKind::OPEN_PAREN, SyntaxKind::OPEN_CURLY, SyntaxKind::CLOSED_CURLY,
        SyntaxKind::INTEGER_LITERAL, SyntaxKind::STAR, SyntaxKind::KEYWORD_INT, SyntaxKind::KEYWORD_FLOAT,
        SyntaxKind::KEYWORD_CHAR, SyntaxKind::KEYWORD_RET, SyntaxKind::KEYWORD_IF, SyntaxKind::KEYWORD_WHILE,
        SyntaxKind::KEYWORD_FOR
    };
    _followSets[NonTerminal::SIMPLE_STMT] = { SyntaxKind::SEMICOLON };
    _followSets[NonTerminal::IF_STMT] = {
        SyntaxKind::IDENTIFIER, SyntaxKind::OPEN_PAREN, SyntaxKind::OPEN_CURLY, SyntaxKind::CLOSED_CURLY,
        SyntaxKind::INTEGER_LITERAL, SyntaxKind::STAR, SyntaxKind::KEYWORD_INT, SyntaxKind::KEYWORD_FLOAT,
        SyntaxKind::KEYWORD_CHAR, SyntaxKind::KEYWORD_RET, SyntaxKind::KEYWORD_IF, SyntaxKind::KEYWORD_ELSE,
        SyntaxKind::KEYWORD_WHILE, SyntaxKind::KEYWORD_FOR
    };
    _followSets[NonTerminal::WHILE_STMT] = {
        SyntaxKind::IDENTIFIER, SyntaxKind::OPEN_PAREN, SyntaxKind::OPEN_CURLY, SyntaxKind::CLOSED_CURLY,
        SyntaxKind::INTEGER_LITERAL, SyntaxKind::STAR, SyntaxKind::KEYWORD_INT, SyntaxKind::KEYWORD_FLOAT,
        SyntaxKind::KEYWORD_CHAR, SyntaxKind::KEYWORD_RET, SyntaxKind::KEYWORD_IF, SyntaxKind::KEYWORD_ELSE,
        SyntaxKind::KEYWORD_WHILE, SyntaxKind::KEYWORD_FOR
    };
    _followSets[NonTerminal::FOR_STMT] = {
        SyntaxKind::IDENTIFIER, SyntaxKind::OPEN_PAREN, SyntaxKind::OPEN_CURLY, SyntaxKind::CLOSED_CURLY,
        SyntaxKind::INTEGER_LITERAL, SyntaxKind::STAR, SyntaxKind::KEYWORD_INT, SyntaxKind::KEYWORD_FLOAT,
        SyntaxKind::KEYWORD_CHAR, SyntaxKind::KEYWORD_RET, SyntaxKind::KEYWORD_IF, SyntaxKind::KEYWORD_ELSE,
        SyntaxKind::KEYWORD_WHILE, SyntaxKind::KEYWORD_FOR
    };
    _followSets[NonTerminal::VAR_DECL_EXPR] = { SyntaxKind::SEMICOLON };
    _followSets[NonTerminal::ASSIGN_EXPR] = { SyntaxKind::CLOSED_PAREN, SyntaxKind::SEMICOLON };
    _followSets[NonTerminal::EXPR] = {
        SyntaxKind::CLOSED_PAREN, SyntaxKind::CLOSED_CURLY, SyntaxKind::COMMA, SyntaxKind::CLOSED_BRACKET,
        SyntaxKind::SEMICOLON
    };
    _followSets[NonTerminal::EXPR_OPT] = { SyntaxKind::SEMICOLON };
    _followSets[NonTerminal::INIT_OPT] = { SyntaxKind::SEMICOLON };
    _followSets[NonTerminal::ASSIGN_VALUE] = { SyntaxKind::SEMICOLON };
    _followSets[NonTerminal::EXPR_LIST] = { SyntaxKind::CLOSED_PAREN, SyntaxKind::CLOSED_CURLY };
    _followSets[NonTerminal::ASSIGN_TARGET] = {
        SyntaxKind::EQUALS, SyntaxKind::PLUS_EQUALS, SyntaxKind::MINUS_EQUALS, SyntaxKind::SLASH_EQUALS,
        SyntaxKind::STAR_EQUALS, SyntaxKind::AMPERSAND_EQUALS, SyntaxKind::PIPE_EQUALS, SyntaxKind::CARET_EQUALS,
        SyntaxKind::TILDE_EQUALS
    };
    _followSets[NonTerminal::ASSIGN_OP] = {
        SyntaxKind::IDENTIFIER, SyntaxKind::OPEN_PAREN, SyntaxKind::INTEGER_LITERAL, SyntaxKind::STAR
    };
    _followSets[NonTerminal::CONDITION_OP] = { SyntaxKind::CLOSED_PAREN };
    _followSets[NonTerminal::BODY] = {
        SyntaxKind::IDENTIFIER, SyntaxKind::OPEN_PAREN, SyntaxKind::OPEN_CURLY, SyntaxKind::CLOSED_CURLY,
        SyntaxKind::INTEGER_LITERAL, SyntaxKind::STAR, SyntaxKind::KEYWORD_INT, SyntaxKind::KEYWORD_FLOAT,
        SyntaxKind::KEYWORD_CHAR, SyntaxKind::KEYWORD_RET, SyntaxKind::KEYWORD_IF, SyntaxKind::KEYWORD_ELSE,
        SyntaxKind::KEYWORD_WHILE, SyntaxKind::KEYWORD_FOR
    };
    _followSets[NonTerminal::FOR_INIT] = { SyntaxKind::SEMICOLON };
    _followSets[NonTerminal::FOR_UPDATE] = { SyntaxKind::CLOSED_PAREN };
    _followSets[NonTerminal::INCREMENT_EXPR] = {
        SyntaxKind::CLOSED_PAREN, SyntaxKind::CLOSED_CURLY, SyntaxKind::COMMA, SyntaxKind::CLOSED_BRACKET,
        SyntaxKind::SEMICOLON
    };
    _followSets[NonTerminal::EXPR_LIST_NON_EMPTY] = { SyntaxKind::CLOSED_PAREN, SyntaxKind::CLOSED_CURLY, SyntaxKind::COMMA };
    _followSets[NonTerminal::LOGICAL_EXPR] = {
        SyntaxKind::CLOSED_PAREN, SyntaxKind::CLOSED_CURLY, SyntaxKind::COMMA, SyntaxKind::CLOSED_BRACKET,
        SyntaxKind::SEMICOLON
    };
    _followSets[NonTerminal::ADDRESS_EXPR] = {
        SyntaxKind::CLOSED_PAREN, SyntaxKind::CLOSED_CURLY, SyntaxKind::COMMA, SyntaxKind::CLOSED_BRACKET,
        SyntaxKind::SEMICOLON
    };
    _followSets[NonTerminal::DEREFERENCE_EXPR] = {
        SyntaxKind::CLOSED_PAREN, SyntaxKind::CLOSED_CURLY, SyntaxKind::COMMA, SyntaxKind::CLOSED_BRACKET,
        SyntaxKind::SEMICOLON
    };
    _followSets[NonTerminal::RELATIONAL_EXPR] = {
        SyntaxKind::CLOSED_PAREN, SyntaxKind::CLOSED_CURLY, SyntaxKind::COMMA, SyntaxKind::CLOSED_BRACKET,
        SyntaxKind::SEMICOLON
    };
    _followSets[NonTerminal::ADD_EXPR] = {
        SyntaxKind::CLOSED_PAREN, SyntaxKind::CLOSED_CURLY, SyntaxKind::COMMA, SyntaxKind::CLOSED_BRACKET,
        SyntaxKind::SEMICOLON
    };
    _followSets[NonTerminal::MUL_EXPR] = {
        SyntaxKind::CLOSED_PAREN, SyntaxKind::CLOSED_CURLY, SyntaxKind::COMMA, SyntaxKind::CLOSED_BRACKET,
        SyntaxKind::STAR, SyntaxKind::SEMICOLON
    };
    _followSets[NonTerminal::UNARY_EXPR] = {
        SyntaxKind::CLOSED_PAREN, SyntaxKind::CLOSED_CURLY, SyntaxKind::COMMA, SyntaxKind::CLOSED_BRACKET,
        SyntaxKind::STAR, SyntaxKind::SEMICOLON
    };
    _followSets[NonTerminal::PRIMARY_EXPR] = {
        SyntaxKind::CLOSED_PAREN, SyntaxKind::CLOSED_CURLY, SyntaxKind::COMMA, SyntaxKind::CLOSED_BRACKET,
        SyntaxKind::STAR, SyntaxKind::SEMICOLON
    };

    // **FOLLOW Sets for Terminals**
    // Common set for tokens that start expressions (used by operators)
    std::unordered_set<SyntaxKind> exprStarters = {
        SyntaxKind::IDENTIFIER, SyntaxKind::OPEN_PAREN, SyntaxKind::INTEGER_LITERAL, SyntaxKind::FLOAT_LITERAL,
        SyntaxKind::CHAR_LITERAL, SyntaxKind::STRING_LITERAL, SyntaxKind::STAR, SyntaxKind::AMPERSAND,
        SyntaxKind::BANG, SyntaxKind::PLUS_PLUS, SyntaxKind::MINUS_MINUS, SyntaxKind::MINUS
    };

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
    _followTerminalsSets[SyntaxKind::AMPERSAND] = { SyntaxKind::IDENTIFIER }; // Address-of
    _followTerminalsSets[SyntaxKind::BANG] = exprStarters; // Logical not
    _followTerminalsSets[SyntaxKind::MINUS] = exprStarters; // Unary minus

    // Increment/Decrement operators
    _followTerminalsSets[SyntaxKind::PLUS_PLUS] = {
        SyntaxKind::IDENTIFIER, SyntaxKind::CLOSED_PAREN, SyntaxKind::CLOSED_CURLY, SyntaxKind::COMMA,
        SyntaxKind::CLOSED_BRACKET, SyntaxKind::SEMICOLON
    };
    _followTerminalsSets[SyntaxKind::MINUS_MINUS] = {
        SyntaxKind::IDENTIFIER, SyntaxKind::CLOSED_PAREN, SyntaxKind::CLOSED_CURLY, SyntaxKind::COMMA,
        SyntaxKind::CLOSED_BRACKET, SyntaxKind::SEMICOLON
    };

    // Literals
    std::unordered_set<SyntaxKind> literalFollow = {
        SyntaxKind::CLOSED_PAREN, SyntaxKind::CLOSED_CURLY, SyntaxKind::COMMA, SyntaxKind::CLOSED_BRACKET,
        SyntaxKind::SEMICOLON, SyntaxKind::PLUS, SyntaxKind::MINUS, SyntaxKind::STAR, SyntaxKind::SLASH,
        SyntaxKind::PIPE, SyntaxKind::AMPERSAND, SyntaxKind::CARET, SyntaxKind::PIPE_PIPE, SyntaxKind::AMPERSAND_AMPERSAND,
        SyntaxKind::EQUALS_EQUALS, SyntaxKind::BANG_EQUALS, SyntaxKind::LESS_THAN, SyntaxKind::GREATER_THAN,
        SyntaxKind::LESS_THAN_EQUALS, SyntaxKind::GREATER_THAN_EQUALS
    };
    _followTerminalsSets[SyntaxKind::INTEGER_LITERAL] = literalFollow;
    _followTerminalsSets[SyntaxKind::FLOAT_LITERAL] = literalFollow;
    _followTerminalsSets[SyntaxKind::CHAR_LITERAL] = literalFollow;
    _followTerminalsSets[SyntaxKind::STRING_LITERAL] = literalFollow;

    // Keywords
    _followTerminalsSets[SyntaxKind::KEYWORD_FN] = { SyntaxKind::IDENTIFIER };
    _followTerminalsSets[SyntaxKind::KEYWORD_INT] = { SyntaxKind::IDENTIFIER, SyntaxKind::OPEN_CURLY, SyntaxKind::OPEN_BRACKET, SyntaxKind::STAR };
    _followTerminalsSets[SyntaxKind::KEYWORD_FLOAT] = { SyntaxKind::IDENTIFIER, SyntaxKind::OPEN_CURLY, SyntaxKind::OPEN_BRACKET, SyntaxKind::STAR };
    _followTerminalsSets[SyntaxKind::KEYWORD_CHAR] = { SyntaxKind::IDENTIFIER, SyntaxKind::OPEN_CURLY, SyntaxKind::OPEN_BRACKET, SyntaxKind::STAR };
    _followTerminalsSets[SyntaxKind::KEYWORD_RET] = exprStarters; // Followed by optional expression
    _followTerminalsSets[SyntaxKind::KEYWORD_IF] = { SyntaxKind::OPEN_PAREN };
    _followTerminalsSets[SyntaxKind::KEYWORD_ELSE] = {
        SyntaxKind::OPEN_CURLY, SyntaxKind::IDENTIFIER, SyntaxKind::KEYWORD_INT, SyntaxKind::KEYWORD_FLOAT,
        SyntaxKind::KEYWORD_CHAR, SyntaxKind::KEYWORD_RET, SyntaxKind::KEYWORD_IF, SyntaxKind::KEYWORD_WHILE,
        SyntaxKind::KEYWORD_FOR
    };
    _followTerminalsSets[SyntaxKind::KEYWORD_WHILE] = { SyntaxKind::OPEN_PAREN };
    _followTerminalsSets[SyntaxKind::KEYWORD_FOR] = { SyntaxKind::OPEN_PAREN };

    // Punctuation
    _followTerminalsSets[SyntaxKind::OPEN_PAREN] = exprStarters;
    _followTerminalsSets[SyntaxKind::CLOSED_PAREN] = {
        SyntaxKind::CLOSED_PAREN, SyntaxKind::CLOSED_CURLY, SyntaxKind::COMMA, SyntaxKind::CLOSED_BRACKET,
        SyntaxKind::SEMICOLON, SyntaxKind::PLUS, SyntaxKind::MINUS, SyntaxKind::STAR, SyntaxKind::SLASH,
        SyntaxKind::PIPE, SyntaxKind::AMPERSAND, SyntaxKind::CARET, SyntaxKind::PIPE_PIPE, SyntaxKind::AMPERSAND_AMPERSAND,
        SyntaxKind::EQUALS_EQUALS, SyntaxKind::BANG_EQUALS, SyntaxKind::LESS_THAN, SyntaxKind::GREATER_THAN,
        SyntaxKind::LESS_THAN_EQUALS, SyntaxKind::GREATER_THAN_EQUALS
    };
    _followTerminalsSets[SyntaxKind::OPEN_CURLY] = {
        SyntaxKind::IDENTIFIER, SyntaxKind::OPEN_PAREN, SyntaxKind::OPEN_CURLY, SyntaxKind::CLOSED_CURLY,
        SyntaxKind::INTEGER_LITERAL, SyntaxKind::STAR, SyntaxKind::KEYWORD_INT, SyntaxKind::KEYWORD_FLOAT,
        SyntaxKind::KEYWORD_CHAR, SyntaxKind::KEYWORD_RET, SyntaxKind::KEYWORD_IF, SyntaxKind::KEYWORD_WHILE,
        SyntaxKind::KEYWORD_FOR
    };
    _followTerminalsSets[SyntaxKind::CLOSED_CURLY] = {
        SyntaxKind::IDENTIFIER, SyntaxKind::OPEN_PAREN, SyntaxKind::OPEN_CURLY, SyntaxKind::CLOSED_CURLY,
        SyntaxKind::INTEGER_LITERAL, SyntaxKind::STAR, SyntaxKind::KEYWORD_INT, SyntaxKind::KEYWORD_FLOAT,
        SyntaxKind::KEYWORD_CHAR, SyntaxKind::KEYWORD_RET, SyntaxKind::KEYWORD_IF, SyntaxKind::KEYWORD_ELSE,
        SyntaxKind::KEYWORD_WHILE, SyntaxKind::KEYWORD_FOR
    };
    _followTerminalsSets[SyntaxKind::OPEN_BRACKET] = exprStarters;
    _followTerminalsSets[SyntaxKind::CLOSED_BRACKET] = {
        SyntaxKind::CLOSED_PAREN, SyntaxKind::CLOSED_CURLY, SyntaxKind::COMMA, SyntaxKind::CLOSED_BRACKET,
        SyntaxKind::SEMICOLON, SyntaxKind::PLUS, SyntaxKind::MINUS, SyntaxKind::STAR, SyntaxKind::SLASH,
        SyntaxKind::PIPE, SyntaxKind::AMPERSAND, SyntaxKind::CARET, SyntaxKind::PIPE_PIPE, SyntaxKind::AMPERSAND_AMPERSAND,
        SyntaxKind::EQUALS_EQUALS, SyntaxKind::BANG_EQUALS, SyntaxKind::LESS_THAN, SyntaxKind::GREATER_THAN,
        SyntaxKind::LESS_THAN_EQUALS, SyntaxKind::GREATER_THAN_EQUALS
    };
    _followTerminalsSets[SyntaxKind::COMMA] = exprStarters;
    _followTerminalsSets[SyntaxKind::SEMICOLON] = {
        SyntaxKind::IDENTIFIER, SyntaxKind::OPEN_PAREN, SyntaxKind::OPEN_CURLY, SyntaxKind::CLOSED_CURLY,
        SyntaxKind::INTEGER_LITERAL, SyntaxKind::STAR, SyntaxKind::KEYWORD_INT, SyntaxKind::KEYWORD_FLOAT,
        SyntaxKind::KEYWORD_CHAR, SyntaxKind::KEYWORD_RET, SyntaxKind::KEYWORD_IF, SyntaxKind::KEYWORD_WHILE,
        SyntaxKind::KEYWORD_FOR
    };
    _followTerminalsSets[SyntaxKind::RIGHT_ARROW] = { SyntaxKind::KEYWORD_INT, SyntaxKind::KEYWORD_FLOAT, SyntaxKind::KEYWORD_CHAR };

    // Identifier
    _followTerminalsSets[SyntaxKind::IDENTIFIER] = {
        SyntaxKind::OPEN_PAREN, SyntaxKind::OPEN_BRACKET, SyntaxKind::PLUS_PLUS, SyntaxKind::MINUS_MINUS,
        SyntaxKind::EQUALS, SyntaxKind::PLUS_EQUALS, SyntaxKind::MINUS_EQUALS, SyntaxKind::SLASH_EQUALS,
        SyntaxKind::STAR_EQUALS, SyntaxKind::AMPERSAND_EQUALS, SyntaxKind::PIPE_EQUALS, SyntaxKind::CARET_EQUALS,
        SyntaxKind::TILDE_EQUALS, SyntaxKind::CLOSED_PAREN, SyntaxKind::CLOSED_CURLY, SyntaxKind::COMMA,
        SyntaxKind::CLOSED_BRACKET, SyntaxKind::SEMICOLON, SyntaxKind::PLUS, SyntaxKind::MINUS, SyntaxKind::STAR,
        SyntaxKind::SLASH, SyntaxKind::PIPE, SyntaxKind::AMPERSAND, SyntaxKind::CARET, SyntaxKind::PIPE_PIPE,
        SyntaxKind::AMPERSAND_AMPERSAND, SyntaxKind::EQUALS_EQUALS, SyntaxKind::BANG_EQUALS, SyntaxKind::LESS_THAN,
        SyntaxKind::GREATER_THAN, SyntaxKind::LESS_THAN_EQUALS, SyntaxKind::GREATER_THAN_EQUALS
    };
}