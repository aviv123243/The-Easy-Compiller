%{
#include <stdio.h>
int yylex(void);
void yyerror(char const *);
%}

%define lr.default_reduction most

/* Token declarations */
%token KEYWORD_FN IDENTIFIER OPEN_PAREN CLOSED_PAREN RIGHT_ARROW OPEN_CURLY CLOSED_CURLY
%token COMMA KEYWORD_INT KEYWORD_FLOAT KEYWORD_CHAR OPEN_BRACKET CLOSED_BRACKET STAR
%token SEMICOLON EQUALS PLUS_EQUALS MINUS_EQUALS SLASH_EQUALS STAR_EQUALS
%token AMPERSAND_EQUALS PIPE_EQUALS CARET_EQUALS TILDE_EQUALS KEYWORD_IF
%token KEYWORD_ELSE KEYWORD_WHILE KEYWORD_FOR KEYWORD_RET LESS_THAN GREATER_THAN
%token LESS_THAN_EQUALS GREATER_THAN_EQUALS EQUALS_EQUALS BANG_EQUALS MINUS BANG
%token PLUS PIPE CARET PIPE_PIPE SLASH AMPERSAND AMPERSAND_AMPERSAND
%token INTEGER_LITERAL FLOAT_LITERAL CHAR_LITERAL

/* Precedence declarations */
%left PIPE_PIPE AMPERSAND_AMPERSAND
%left EQUALS_EQUALS BANG_EQUALS
%left LESS_THAN GREATER_THAN LESS_THAN_EQUALS GREATER_THAN_EQUALS
%left PLUS MINUS PIPE CARET
%left STAR SLASH AMPERSAND
/* Resolve dangling else by giving ELSE higher precedence than the if body */
%nonassoc THEN
%nonassoc KEYWORD_ELSE

%%

Program:
    FunctionDecl Program
    | /* epsilon */
    ;

FunctionDecl:
    KEYWORD_FN IDENTIFIER OPEN_PAREN ParamList CLOSED_PAREN RIGHT_ARROW Type OPEN_CURLY StmtList CLOSED_CURLY
    ;

ParamList:
    Param ParamTail
    | /* epsilon */
    ;

ParamTail:
    COMMA Param ParamTail
    | /* epsilon */
    ;

Param:
    Type IDENTIFIER
    ;

Type:
    BaseType TypeTail
    ;

BaseType:
    KEYWORD_INT
    | KEYWORD_FLOAT
    | KEYWORD_CHAR
    ;

TypeTail:
    OPEN_BRACKET INTEGER_LITERAL CLOSED_BRACKET TypeTail
    | STAR TypeTail
    | /* epsilon */
    ;

StmtList:
    Stmt StmtList
    | /* epsilon */
    ;

Stmt:
    VarDeclStmt
    | AssignStmt
    | IfStmt
    | WhileStmt
    | ForStmt
    | ReturnStmt
    | ExprStmt
    ;

Body:
    OPEN_CURLY StmtList CLOSED_CURLY
    | Stmt
    ;

VarDeclStmt:
    VarDeclExpr SEMICOLON
    ;

VarDeclExpr:
    Type IDENTIFIER InitOpt
    ;

InitOpt:
    EQUALS Expr
    | /* epsilon */
    ;

AssignStmt:
    AssignExpr SEMICOLON
    ;

AssignExpr:
    AssignTarget AssignOp Expr
    ;

AssignTarget:
    IDENTIFIER
    | IDENTIFIER OPEN_BRACKET Expr CLOSED_BRACKET
    | STAR IDENTIFIER
    ;

AssignOp:
    EQUALS
    | PLUS_EQUALS
    | MINUS_EQUALS
    | SLASH_EQUALS
    | STAR_EQUALS
    | AMPERSAND_EQUALS
    | PIPE_EQUALS
    | CARET_EQUALS
    | TILDE_EQUALS
    ;

IfStmt:
    KEYWORD_IF OPEN_PAREN Expr CLOSED_PAREN Body %prec THEN
    | KEYWORD_IF OPEN_PAREN Expr CLOSED_PAREN Body KEYWORD_ELSE Body
    ;

WhileStmt:
    KEYWORD_WHILE OPEN_PAREN Expr CLOSED_PAREN Body
    ;

ForStmt:
    KEYWORD_FOR OPEN_PAREN ForInit SEMICOLON ExprOpt SEMICOLON ForUpdate CLOSED_PAREN Body
    ;

ForInit:
    VarDeclExpr
    | AssignExpr
    | /* epsilon */
    ;

ExprOpt:
    Expr
    | /* epsilon */
    ;

ForUpdate:
    AssignExpr
    | /* epsilon */
    ;

ReturnStmt:
    KEYWORD_RET ExprOpt SEMICOLON
    ;

ExprStmt:
    Expr SEMICOLON
    ;

ExprList:
    Expr ExprTail
    | /* epsilon */
    ;

ExprTail:
    COMMA Expr ExprTail
    | /* epsilon */
    ;

Expr:
    UnaryExpr RelOpTail
    ;

RelOpTail:
    RelOp UnaryExpr RelOpTail
    | /* epsilon */
    ;

RelOp:
    LESS_THAN
    | GREATER_THAN
    | LESS_THAN_EQUALS
    | GREATER_THAN_EQUALS
    | EQUALS_EQUALS
    | BANG_EQUALS
    ;

UnaryExpr:
    UnaryOp UnaryExpr
    | SimpleExpr
    ;

UnaryOp:
    MINUS
    | BANG
    ;

SimpleExpr:
    Term AddOpTail
    ;

AddOpTail:
    AddOp Term AddOpTail
    | /* epsilon */
    ;

AddOp:
    PLUS
    | MINUS
    | PIPE
    | CARET
    | PIPE_PIPE
    ;

Term:
    Factor MulOpTail
    ;

MulOpTail:
    MulOp Factor MulOpTail
    | /* epsilon */
    ;

MulOp:
    STAR
    | SLASH
    | AMPERSAND
    | AMPERSAND_AMPERSAND
    ;

Factor:
    OPEN_PAREN Expr CLOSED_PAREN
    | IDENTIFIER
    | INTEGER_LITERAL
    | FLOAT_LITERAL
    | CHAR_LITERAL
    | IDENTIFIER OPEN_PAREN ExprList CLOSED_PAREN
    ;

%%

void yyerror(char const *s) {
    fprintf(stderr, "%s\n", s);
}