%{
#include <stdio.h>
#include <graphviz/cgraph.h>
int yylex(void);
void yyerror(char const *);
%}

%define lr.type ielr

/* Token declarations */
%token KEYWORD_FN IDENTIFIER OPEN_PAREN CLOSED_PAREN RIGHT_ARROW OPEN_CURLY CLOSED_CURLY
%token COMMA KEYWORD_INT KEYWORD_FLOAT KEYWORD_CHAR OPEN_BRACKET CLOSED_BRACKET STAR
%token SEMICOLON EQUALS PLUS_EQUALS MINUS_EQUALS SLASH_EQUALS STAR_EQUALS
%token AMPERSAND_EQUALS PIPE_EQUALS CARET_EQUALS TILDE_EQUALS KEYWORD_IF
%token KEYWORD_ELSE KEYWORD_WHILE KEYWORD_FOR KEYWORD_RET LESS_THAN GREATER_THAN
%token LESS_THAN_EQUALS GREATER_THAN_EQUALS EQUALS_EQUALS BANG_EQUALS MINUS BANG
%token PLUS PIPE CARET PIPE_PIPE SLASH AMPERSAND AMPERSAND_AMPERSAND
%token INTEGER_LITERAL FLOAT_LITERAL CHAR_LITERAL PLUS_PLUS MINUS_MINUS

/* Precedence declarations */
%left PIPE_PIPE
%left AMPERSAND_AMPERSAND
%left PIPE CARET
%left AMPERSAND
%left EQUALS_EQUALS BANG_EQUALS
%left LESS_THAN GREATER_THAN LESS_THAN_EQUALS GREATER_THAN_EQUALS
%left PLUS MINUS
%left STAR SLASH
%right UNARY   /* For unary operators */
%nonassoc THEN
%nonassoc KEYWORD_ELSE

%%

Program:
    /* empty */
    | Program FunctionDecl
    ;

FunctionDecl:
    KEYWORD_FN IDENTIFIER OPEN_PAREN ParamList CLOSED_PAREN RIGHT_ARROW Type OPEN_CURLY StmtList CLOSED_CURLY
    ;

ParamList:
    /* empty */
    | ParamListNonEmpty
    ;

ParamListNonEmpty:
    Param
    | ParamListNonEmpty COMMA Param
    ;

Param:
    Type IDENTIFIER
    ;

Type:
    BaseType
    | BaseType OPEN_BRACKET INTEGER_LITERAL CLOSED_BRACKET
    | BaseType STAR
    ;

BaseType:
    KEYWORD_INT
    | KEYWORD_FLOAT
    | KEYWORD_CHAR
    ;

StmtList:
    /* empty */
    | StmtList Stmt
    ;

Stmt:
    SimpleStmt SEMICOLON
    | OPEN_CURLY StmtList CLOSED_CURLY
    | IfStmt
    | WhileStmt
    | ForStmt
    ;

SimpleStmt:
    VarDeclExpr
    | AssignExpr 
    | IDENTIFIER OPEN_PAREN ExprList CLOSED_PAREN  /* Function call */
    | KEYWORD_RET ExprOpt
    ;

VarDeclExpr:
    Type IDENTIFIER InitOpt
    ;

InitOpt:
    /* empty */
    | EQUALS AssignValue
    ;

AssignValue:
    Expr
    | OPEN_CURLY ExprList CLOSED_CURLY
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
    KEYWORD_IF OPEN_PAREN ConditionOp CLOSED_PAREN Body %prec THEN
    | KEYWORD_IF OPEN_PAREN ConditionOp CLOSED_PAREN Body KEYWORD_ELSE Body
    ;

WhileStmt:
    KEYWORD_WHILE OPEN_PAREN ConditionOp CLOSED_PAREN Body
    ;

ConditionOp:
    Expr
    | AssignExpr
    ;

ForStmt:
    KEYWORD_FOR OPEN_PAREN ForInit SEMICOLON ExprOpt SEMICOLON ForUpdate CLOSED_PAREN Body
    ;

ForInit:
    /* empty */
    | VarDeclExpr
    | AssignExpr
    ;

ExprOpt:
    /* empty */
    | Expr
    ;

ForUpdate:
    /* empty */
    | AssignExpr
    | IncrementExpr
    ;

Body:
    OPEN_CURLY StmtList CLOSED_CURLY
    | SimpleStmt SEMICOLON
    | IfStmt
    | WhileStmt
    | ForStmt
    ;

ExprList:
    /* empty */
    | ExprListNonEmpty
    ;

ExprListNonEmpty:
    Expr
    | ExprListNonEmpty COMMA Expr
    ;

Expr:
    LogicalExpr
    | AddressExpr
    
    ;

LogicalExpr:
    RelationalExpr
    | LogicalExpr PIPE_PIPE RelationalExpr
    | LogicalExpr AMPERSAND_AMPERSAND RelationalExpr
    ;

RelationalExpr:
    AddExpr
    | RelationalExpr EQUALS_EQUALS AddExpr
    | RelationalExpr BANG_EQUALS AddExpr
    | RelationalExpr LESS_THAN AddExpr
    | RelationalExpr GREATER_THAN AddExpr
    | RelationalExpr LESS_THAN_EQUALS AddExpr
    | RelationalExpr GREATER_THAN_EQUALS AddExpr
    ;

AddExpr:
    MulExpr
    | AddExpr PLUS MulExpr
    | AddExpr MINUS MulExpr
	| AddExpr PIPE MulExpr
    | AddExpr CARET MulExpr
    ;

MulExpr:
    UnaryExpr
    | MulExpr STAR UnaryExpr
    | MulExpr SLASH UnaryExpr
	| MulExpr AMPERSAND UnaryExpr
    ;

UnaryExpr:
    PrimaryExpr
    | MINUS UnaryExpr %prec UNARY
    | BANG UnaryExpr %prec UNARY
    ;

IncrementExpr:
    IDENTIFIER PLUS_PLUS
    | IDENTIFIER MINUS_MINUS
    | PLUS_PLUS IDENTIFIER
    | MINUS_MINUS IDENTIFIER
    ;

/* Split pointer expressions into two distinct types */
AddressExpr:
    AMPERSAND IDENTIFIER
    ;

DereferenceExpr:
    STAR IDENTIFIER
    ;

PrimaryExpr:
    IDENTIFIER
    | IDENTIFIER OPEN_BRACKET Expr CLOSED_BRACKET  /* Array access */
    | INTEGER_LITERAL
    | FLOAT_LITERAL
    | CHAR_LITERAL
    | OPEN_PAREN Expr CLOSED_PAREN
    | IDENTIFIER OPEN_PAREN ExprList CLOSED_PAREN  /* Function call */
	| DereferenceExpr
	| IncrementExpr

    ;

%%

void yyerror(char const *s) {
    fprintf(stderr, "%s\n", s);
}