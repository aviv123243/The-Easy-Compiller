#include "parser.hpp"
#include "productionRule/productionRule.hpp"
#include "../token/token.hpp"

void Parser::initProductionRules()
{
    productionRule rule;

    // Program -> FunctionDecl Program | /* empty */
    rule.setLeft(NonTerminal::PROGRAM);
    rule.addSymbol(NonTerminal::FUNCTION_DECL).addSymbol(NonTerminal::PROGRAM);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::PROGRAM);
    rule.addSymbol(); // empty
    addProductionRule(rule);
    rule.reset();

    // FunctionDecl -> KEYWORD_FN IDENTIFIER OPEN_PAREN ParamList CLOSED_PAREN RIGHT_ARROW Type OPEN_CURLY StmtList CLOSED_CURLY
    rule.setLeft(NonTerminal::FUNCTION_DECL);
    rule.addSymbol(SyntaxKind::KEYWORD_FN)
        .addSymbol(SyntaxKind::IDENTIFIER)
        .addSymbol(SyntaxKind::OPEN_PAREN)
        .addSymbol(NonTerminal::PARAM_LIST)
        .addSymbol(SyntaxKind::CLOSED_PAREN)
        .addSymbol(SyntaxKind::RIGHT_ARROW)
        .addSymbol(NonTerminal::TYPE)
        .addSymbol(SyntaxKind::OPEN_CURLY)
        .addSymbol(NonTerminal::STMT_LIST)
        .addSymbol(SyntaxKind::CLOSED_CURLY);
    addProductionRule(rule);
    rule.reset();

    // ParamList -> Param ParamTail | /* empty */
    rule.setLeft(NonTerminal::PARAM_LIST);
    rule.addSymbol(NonTerminal::PARAM).addSymbol(NonTerminal::PARAM_TAIL);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::PARAM_LIST);
    rule.addSymbol(); // empty
    addProductionRule(rule);
    rule.reset();

    // ParamTail -> COMMA Param ParamTail | /* empty */
    rule.setLeft(NonTerminal::PARAM_TAIL);
    rule.addSymbol(SyntaxKind::COMMA).addSymbol(NonTerminal::PARAM).addSymbol(NonTerminal::PARAM_TAIL);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::PARAM_TAIL);
    rule.addSymbol(); // empty
    addProductionRule(rule);
    rule.reset();

    // Param -> Type IDENTIFIER
    rule.setLeft(NonTerminal::PARAM);
    rule.addSymbol(NonTerminal::TYPE).addSymbol(SyntaxKind::IDENTIFIER);
    addProductionRule(rule);
    rule.reset();

    // Type -> BaseType TypeTail
    rule.setLeft(NonTerminal::TYPE);
    rule.addSymbol(NonTerminal::BASE_TYPE).addSymbol(NonTerminal::TYPE_TAIL);
    addProductionRule(rule);
    rule.reset();

    // BaseType -> KEYWORD_INT | KEYWORD_FLOAT | KEYWORD_CHAR
    rule.setLeft(NonTerminal::BASE_TYPE);
    rule.addSymbol(SyntaxKind::KEYWORD_INT);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::BASE_TYPE);
    rule.addSymbol(SyntaxKind::KEYWORD_FLOAT);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::BASE_TYPE);
    rule.addSymbol(SyntaxKind::KEYWORD_CHAR);
    addProductionRule(rule);
    rule.reset();

    // TypeTail -> OPEN_BRACKET INTEGER_LITERAL CLOSED_BRACKET TypeTail | STAR TypeTail | /* empty */
    rule.setLeft(NonTerminal::TYPE_TAIL);
    rule.addSymbol(SyntaxKind::OPEN_BRACKET)
        .addSymbol(SyntaxKind::INTEGER_LITERAL)
        .addSymbol(SyntaxKind::CLOSED_BRACKET)
        .addSymbol(NonTerminal::TYPE_TAIL);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::TYPE_TAIL);
    rule.addSymbol(SyntaxKind::STAR).addSymbol(NonTerminal::TYPE_TAIL);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::TYPE_TAIL);
    rule.addSymbol(); // empty
    addProductionRule(rule);
    rule.reset();

    // StmtList -> Stmt StmtList | /* empty */
    rule.setLeft(NonTerminal::STMT_LIST);
    rule.addSymbol(NonTerminal::STMT).addSymbol(NonTerminal::STMT_LIST);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::STMT_LIST);
    rule.addSymbol(); // empty
    addProductionRule(rule);
    rule.reset();

    // Stmt -> VarDeclStmt | AssignStmt | IfStmt | WhileStmt | ForStmt | ReturnStmt | ExprStmt
    rule.setLeft(NonTerminal::STMT);
    rule.addSymbol(NonTerminal::VAR_DECL_STMT);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::STMT);
    rule.addSymbol(NonTerminal::ASSIGN_STMT);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::STMT);
    rule.addSymbol(NonTerminal::IF_STMT);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::STMT);
    rule.addSymbol(NonTerminal::WHILE_STMT);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::STMT);
    rule.addSymbol(NonTerminal::FOR_STMT);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::STMT);
    rule.addSymbol(NonTerminal::RETURN_STMT);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::STMT);
    rule.addSymbol(NonTerminal::EXPR_STMT);
    addProductionRule(rule);
    rule.reset();

    // Body -> OPEN_CURLY StmtList CLOSED_CURLY | Stmt
    rule.setLeft(NonTerminal::BODY);
    rule.addSymbol(SyntaxKind::OPEN_CURLY)
        .addSymbol(NonTerminal::STMT_LIST)
        .addSymbol(SyntaxKind::CLOSED_CURLY);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::BODY);
    rule.addSymbol(NonTerminal::STMT);
    addProductionRule(rule);
    rule.reset();

    // VarDeclExpr -> Type IDENTIFIER InitOpt
    rule.setLeft(NonTerminal::VAR_DECL_EXPR);
    rule.addSymbol(NonTerminal::TYPE)
        .addSymbol(SyntaxKind::IDENTIFIER)
        .addSymbol(NonTerminal::INIT_OPT);
    addProductionRule(rule);
    rule.reset();

    // VarDeclStmt -> VarDeclExpr SEMICOLON
    rule.setLeft(NonTerminal::VAR_DECL_STMT);
    rule.addSymbol(NonTerminal::VAR_DECL_EXPR).addSymbol(SyntaxKind::SEMICOLON);
    addProductionRule(rule);
    rule.reset();

    // InitOpt -> EQUALS Expr | /* empty */
    rule.setLeft(NonTerminal::INIT_OPT);
    rule.addSymbol(SyntaxKind::EQUALS).addSymbol(NonTerminal::EXPR);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::INIT_OPT);
    rule.addSymbol(); // empty
    addProductionRule(rule);
    rule.reset();

    // AssignExpr -> AssignTarget AssignOp Expr
    rule.setLeft(NonTerminal::ASSIGN_EXPR);
    rule.addSymbol(NonTerminal::ASSIGN_TARGET)
        .addSymbol(NonTerminal::ASSIGN_OP)
        .addSymbol(NonTerminal::EXPR);
    addProductionRule(rule);
    rule.reset();

    // AssignStmt -> AssignExpr SEMICOLON
    rule.setLeft(NonTerminal::ASSIGN_STMT);
    rule.addSymbol(NonTerminal::ASSIGN_EXPR).addSymbol(SyntaxKind::SEMICOLON);
    addProductionRule(rule);
    rule.reset();

    // AssignTarget -> IDENTIFIER | IDENTIFIER OPEN_BRACKET Expr CLOSED_BRACKET | STAR IDENTIFIER
    rule.setLeft(NonTerminal::ASSIGN_TARGET);
    rule.addSymbol(SyntaxKind::IDENTIFIER);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::ASSIGN_TARGET);
    rule.addSymbol(SyntaxKind::IDENTIFIER)
        .addSymbol(SyntaxKind::OPEN_BRACKET)
        .addSymbol(NonTerminal::EXPR)
        .addSymbol(SyntaxKind::CLOSED_BRACKET);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::ASSIGN_TARGET);
    rule.addSymbol(SyntaxKind::STAR).addSymbol(SyntaxKind::IDENTIFIER);
    addProductionRule(rule);
    rule.reset();

    // AssignOp -> EQUALS | PLUS_EQUALS | MINUS_EQUALS | SLASH_EQUALS | STAR_EQUALS | AMPERSAND_EQUALS | PIPE_EQUALS | CARET_EQUALS | TILDE_EQUALS
    rule.setLeft(NonTerminal::ASSIGN_OP);
    rule.addSymbol(SyntaxKind::EQUALS);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::ASSIGN_OP);
    rule.addSymbol(SyntaxKind::PLUS_EQUALS);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::ASSIGN_OP);
    rule.addSymbol(SyntaxKind::MINUS_EQUALS);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::ASSIGN_OP);
    rule.addSymbol(SyntaxKind::SLASH_EQUALS);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::ASSIGN_OP);
    rule.addSymbol(SyntaxKind::STAR_EQUALS);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::ASSIGN_OP);
    rule.addSymbol(SyntaxKind::AMPERSAND_EQUALS);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::ASSIGN_OP);
    rule.addSymbol(SyntaxKind::PIPE_EQUALS);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::ASSIGN_OP);
    rule.addSymbol(SyntaxKind::CARET_EQUALS);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::ASSIGN_OP);
    rule.addSymbol(SyntaxKind::TILDE_EQUALS);
    addProductionRule(rule);
    rule.reset();

    // IfStmt -> KEYWORD_IF OPEN_PAREN Expr CLOSED_PAREN Body ElseOpt
    rule.setLeft(NonTerminal::IF_STMT);
    rule.addSymbol(SyntaxKind::KEYWORD_IF)
        .addSymbol(SyntaxKind::OPEN_PAREN)
        .addSymbol(NonTerminal::EXPR)
        .addSymbol(SyntaxKind::CLOSED_PAREN)
        .addSymbol(NonTerminal::BODY)
        .addSymbol(NonTerminal::ELSE_OPT);
    addProductionRule(rule);
    rule.reset();

    // ElseOpt -> KEYWORD_ELSE Body | /* empty */
    rule.setLeft(NonTerminal::ELSE_OPT);
    rule.addSymbol(SyntaxKind::KEYWORD_ELSE).addSymbol(NonTerminal::BODY);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::ELSE_OPT);
    rule.addSymbol(); // empty
    addProductionRule(rule);
    rule.reset();

    // WhileStmt -> KEYWORD_WHILE OPEN_PAREN Expr CLOSED_PAREN Body
    rule.setLeft(NonTerminal::WHILE_STMT);
    rule.addSymbol(SyntaxKind::KEYWORD_WHILE)
        .addSymbol(SyntaxKind::OPEN_PAREN)
        .addSymbol(NonTerminal::EXPR)
        .addSymbol(SyntaxKind::CLOSED_PAREN)
        .addSymbol(NonTerminal::BODY);
    addProductionRule(rule);
    rule.reset();

    // ForStmt -> KEYWORD_FOR OPEN_PAREN ForInit SEMICOLON ExprOpt SEMICOLON ForUpdate CLOSED_PAREN Body
    rule.setLeft(NonTerminal::FOR_STMT);
    rule.addSymbol(SyntaxKind::KEYWORD_FOR)
        .addSymbol(SyntaxKind::OPEN_PAREN)
        .addSymbol(NonTerminal::FOR_INIT)
        .addSymbol(SyntaxKind::SEMICOLON)
        .addSymbol(NonTerminal::EXPR_OPT)
        .addSymbol(SyntaxKind::SEMICOLON)
        .addSymbol(NonTerminal::FOR_UPDATE)
        .addSymbol(SyntaxKind::CLOSED_PAREN)
        .addSymbol(NonTerminal::BODY);
    addProductionRule(rule);
    rule.reset();

    // ForInit -> VarDeclExpr | AssignExpr | /* empty */
    rule.setLeft(NonTerminal::FOR_INIT);
    rule.addSymbol(NonTerminal::VAR_DECL_EXPR);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::FOR_INIT);
    rule.addSymbol(NonTerminal::ASSIGN_EXPR);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::FOR_INIT);
    rule.addSymbol(); // empty
    addProductionRule(rule);
    rule.reset();

    // ExprOpt -> Expr | /* empty */
    rule.setLeft(NonTerminal::EXPR_OPT);
    rule.addSymbol(NonTerminal::EXPR);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::EXPR_OPT);
    rule.addSymbol(); // empty
    addProductionRule(rule);
    rule.reset();

    // ForUpdate -> AssignExpr | /* empty */
    rule.setLeft(NonTerminal::FOR_UPDATE);
    rule.addSymbol(NonTerminal::ASSIGN_EXPR);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::FOR_UPDATE);
    rule.addSymbol(); // empty
    addProductionRule(rule);
    rule.reset();

    // ReturnStmt -> KEYWORD_RET ExprOpt SEMICOLON
    rule.setLeft(NonTerminal::RETURN_STMT);
    rule.addSymbol(SyntaxKind::KEYWORD_RET)
        .addSymbol(NonTerminal::EXPR_OPT)
        .addSymbol(SyntaxKind::SEMICOLON);
    addProductionRule(rule);
    rule.reset();

    // ExprStmt -> Expr SEMICOLON
    rule.setLeft(NonTerminal::EXPR_STMT);
    rule.addSymbol(NonTerminal::EXPR).addSymbol(SyntaxKind::SEMICOLON);
    addProductionRule(rule);
    rule.reset();

    // ExprList -> Expr ExprTail | /* empty */
    rule.setLeft(NonTerminal::EXPR_LIST);
    rule.addSymbol(NonTerminal::EXPR).addSymbol(NonTerminal::EXPR_TAIL);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::EXPR_LIST);
    rule.addSymbol(); // empty
    addProductionRule(rule);
    rule.reset();

    // ExprTail -> COMMA Expr ExprTail | /* empty */
    rule.setLeft(NonTerminal::EXPR_TAIL);
    rule.addSymbol(SyntaxKind::COMMA).addSymbol(NonTerminal::EXPR).addSymbol(NonTerminal::EXPR_TAIL);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::EXPR_TAIL);
    rule.addSymbol(); // empty
    addProductionRule(rule);
    rule.reset();

    // Expr -> UnaryExpr RelOpTail
    rule.setLeft(NonTerminal::EXPR);
    rule.addSymbol(NonTerminal::UNARY_EXPR).addSymbol(NonTerminal::REL_OP_TAIL);
    addProductionRule(rule);
    rule.reset();

    // RelOpTail -> RelOp UnaryExpr | /* empty */
    rule.setLeft(NonTerminal::REL_OP_TAIL);
    rule.addSymbol(NonTerminal::REL_OP).addSymbol(NonTerminal::UNARY_EXPR);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::REL_OP_TAIL);
    rule.addSymbol(); // empty
    addProductionRule(rule);
    rule.reset();

    // RelOp -> LESS_THAN | GREATER_THAN | LESS_THAN_EQUALS | GREATER_THAN_EQUALS | EQUALS_EQUALS | BANG_EQUALS
    rule.setLeft(NonTerminal::REL_OP);
    rule.addSymbol(SyntaxKind::LESS_THAN);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::REL_OP);
    rule.addSymbol(SyntaxKind::GREATER_THAN);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::REL_OP);
    rule.addSymbol(SyntaxKind::LESS_THAN_EQUALS);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::REL_OP);
    rule.addSymbol(SyntaxKind::GREATER_THAN_EQUALS);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::REL_OP);
    rule.addSymbol(SyntaxKind::EQUALS_EQUALS);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::REL_OP);
    rule.addSymbol(SyntaxKind::BANG_EQUALS);
    addProductionRule(rule);
    rule.reset();

    // UnaryExpr -> UnaryOpList SimpleExpr
    rule.setLeft(NonTerminal::UNARY_EXPR);
    rule.addSymbol(NonTerminal::UNARY_OP_LIST).addSymbol(NonTerminal::SIMPLE_EXPR);
    addProductionRule(rule);
    rule.reset();

    // UnaryOpList -> UnaryOp UnaryOpList | /* empty */
    rule.setLeft(NonTerminal::UNARY_OP_LIST);
    rule.addSymbol(NonTerminal::UNARY_OP).addSymbol(NonTerminal::UNARY_OP_LIST);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::UNARY_OP_LIST);
    rule.addSymbol(); // empty
    addProductionRule(rule);
    rule.reset();

    // UnaryOp -> MINUS | BANG
    rule.setLeft(NonTerminal::UNARY_OP);
    rule.addSymbol(SyntaxKind::MINUS);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::UNARY_OP);
    rule.addSymbol(SyntaxKind::BANG);
    addProductionRule(rule);
    rule.reset();

    // SimpleExpr -> Term AddOpTail
    rule.setLeft(NonTerminal::SIMPLE_EXPR);
    rule.addSymbol(NonTerminal::TERM).addSymbol(NonTerminal::ADD_OP_TAIL);
    addProductionRule(rule);
    rule.reset();

    // AddOpTail -> AddOp Term AddOpTail | /* empty */
    rule.setLeft(NonTerminal::ADD_OP_TAIL);
    rule.addSymbol(NonTerminal::ADD_OP).addSymbol(NonTerminal::TERM).addSymbol(NonTerminal::ADD_OP_TAIL);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::ADD_OP_TAIL);
    rule.addSymbol(); // empty
    addProductionRule(rule);
    rule.reset();

    // AddOp -> PLUS | MINUS | PIPE | CARET | PIPE_PIPE
    rule.setLeft(NonTerminal::ADD_OP);
    rule.addSymbol(SyntaxKind::PLUS);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::ADD_OP);
    rule.addSymbol(SyntaxKind::MINUS);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::ADD_OP);
    rule.addSymbol(SyntaxKind::PIPE);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::ADD_OP);
    rule.addSymbol(SyntaxKind::CARET);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::ADD_OP);
    rule.addSymbol(SyntaxKind::PIPE_PIPE);
    addProductionRule(rule);
    rule.reset();

    // Term -> Factor MulOpTail
    rule.setLeft(NonTerminal::TERM);
    rule.addSymbol(NonTerminal::FACTOR).addSymbol(NonTerminal::MUL_OP_TAIL);
    addProductionRule(rule);
    rule.reset();

    // MulOpTail -> MulOp Factor MulOpTail | /* empty */
    rule.setLeft(NonTerminal::MUL_OP_TAIL);
    rule.addSymbol(NonTerminal::MUL_OP).addSymbol(NonTerminal::FACTOR).addSymbol(NonTerminal::MUL_OP_TAIL);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::MUL_OP_TAIL);
    rule.addSymbol(); // empty
    addProductionRule(rule);
    rule.reset();

    // MulOp -> STAR | SLASH | AMPERSAND | AMPERSAND_AMPERSAND
    rule.setLeft(NonTerminal::MUL_OP);
    rule.addSymbol(SyntaxKind::STAR);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::MUL_OP);
    rule.addSymbol(SyntaxKind::SLASH);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::MUL_OP);
    rule.addSymbol(SyntaxKind::AMPERSAND);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::MUL_OP);
    rule.addSymbol(SyntaxKind::AMPERSAND_AMPERSAND);
    addProductionRule(rule);
    rule.reset();

    // Factor -> OPEN_PAREN Expr CLOSED_PAREN | IDENTIFIER | INTEGER_LITERAL | FLOAT_LITERAL | CHAR_LITERAL | IDENTIFIER FunctionCallOp
    rule.setLeft(NonTerminal::FACTOR);
    rule.addSymbol(SyntaxKind::OPEN_PAREN)
        .addSymbol(NonTerminal::EXPR)
        .addSymbol(SyntaxKind::CLOSED_PAREN);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::FACTOR);
    rule.addSymbol(SyntaxKind::IDENTIFIER);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::FACTOR);
    rule.addSymbol(SyntaxKind::INTEGER_LITERAL);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::FACTOR);
    rule.addSymbol(SyntaxKind::FLOAT_LITERAL);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::FACTOR);
    rule.addSymbol(SyntaxKind::CHAR_LITERAL);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::FACTOR);
    rule.addSymbol(SyntaxKind::IDENTIFIER).addSymbol(NonTerminal::FUNCTION_CALL_OP);
    addProductionRule(rule);
    rule.reset();

    // FunctionCallOp -> OPEN_PAREN ExprList CLOSED_PAREN | /* empty */
    rule.setLeft(NonTerminal::FUNCTION_CALL_OP);
    rule.addSymbol(SyntaxKind::OPEN_PAREN)
        .addSymbol(NonTerminal::EXPR_LIST)
        .addSymbol(SyntaxKind::CLOSED_PAREN);
    addProductionRule(rule);
    rule.reset();

    rule.setLeft(NonTerminal::FUNCTION_CALL_OP);
    rule.addSymbol(); // empty
    addProductionRule(rule);
    rule.reset();
}