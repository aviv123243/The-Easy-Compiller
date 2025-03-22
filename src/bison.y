%token INTEGER_LITERAL FLOAT_LITERAL CHAR_LITERAL STRING_LITERAL IDENTIFIER
%token KEYWORD_IF KEYWORD_ELSE KEYWORD_WHILE KEYWORD_FOR KEYWORD_FN KEYWORD_RET
%token KEYWORD_INT KEYWORD_FLOAT KEYWORD_CHAR
%token EQUALS COMMA PLUS MINUS SLASH STAR AMPERSAND PIPE BANG SEMICOLON
%token LESS_THAN GREATER_THAN OPEN_PAREN CLOSED_PAREN OPEN_CURLY CLOSED_CURLY
%token OPEN_BRACKET CLOSED_BRACKET RIGHT_ARROW PLUS_PLUS DASH_DASH PLUS_EQUALS
%token DASH_EQUALS SLASH_EQUALS STAR_EQUALS EQUALS_EQUALS LESS_THAN_EQUALS
%token GREATER_THAN_EQUALS AMPERSAND_AMPERSAND PIPE_PIPE BANG_EQUALS END_OF_FILE

%%

Program         : FunctionDecl Program
                | /* empty */
                ;

FunctionDecl   : KEYWORD_FN IDENTIFIER OPEN_PAREN ParamList CLOSED_PAREN RIGHT_ARROW Type OPEN_CURLY StmtList CLOSED_CURLY
                ;

ParamList      : Param ParamTail
                | /* empty */
                ;
ParamTail      : COMMA Param ParamTail
                | /* empty */
                ;
Param          : Type IDENTIFIER
                ;

Type           : KEYWORD_INT
                | KEYWORD_FLOAT
                | KEYWORD_CHAR
                ;

StmtList       : Stmt StmtList
                | /* empty */
                ;

Stmt           : VarDecl
                | AssignStmt
                | IfStmt
                | WhileStmt
                | ForStmt
                | ReturnStmt
                | ExprStmt
                | "print" OPEN_PAREN ExprList CLOSED_PAREN SEMICOLON
                ;

VarDecl        : Type IDENTIFIER InitOpt SEMICOLON
                ;
InitOpt        : EQUALS Expr
                | /* empty */
                ;

AssignStmt     : IDENTIFIER EQUALS Expr SEMICOLON
                ;

IfStmt         : KEYWORD_IF OPEN_PAREN Expr CLOSED_PAREN Stmt ElseOpt
                ;
ElseOpt        : KEYWORD_ELSE Stmt
                | /* empty */
                ;

WhileStmt      : KEYWORD_WHILE OPEN_PAREN Expr CLOSED_PAREN Stmt
                ;

ForStmt        : KEYWORD_FOR OPEN_PAREN ForInit SEMICOLON ExprOpt SEMICOLON ForUpdate CLOSED_PAREN Stmt
                ;
ForInit        : VarDecl
                | AssignStmt
                | /* empty */
                ;
ExprOpt        : Expr
                | /* empty */
                ;
ForUpdate      : AssignStmt
                | /* empty */
                ;

ReturnStmt     : KEYWORD_RET Expr SEMICOLON
                ;

ExprStmt       : Expr SEMICOLON
                ;

ExprList       : Expr ExprTail
                | /* empty */
                ;
ExprTail       : COMMA Expr ExprTail
                | /* empty */
                ;

Expr           : SimpleExpr RelOpTail
                ;
RelOpTail      : RelOp SimpleExpr
                | /* empty */
                ;
RelOp          : LESS_THAN
                | GREATER_THAN
                | LESS_THAN_EQUALS
                | GREATER_THAN_EQUALS
                | EQUALS_EQUALS
                | BANG_EQUALS
                ;

SimpleExpr     : Term AddOpTail
                ;
AddOpTail      : AddOp Term AddOpTail
                | /* empty */
                ;
AddOp          : PLUS
                | MINUS
                | PIPE_PIPE
                ;

Term           : Factor MulOpTail
                ;
MulOpTail      : MulOp Factor MulOpTail
                | /* empty */
                ;
MulOp          : STAR
                | SLASH
                | AMPERSAND_AMPERSAND
                ;

Factor         : OPEN_PAREN Expr CLOSED_PAREN
                | IDENTIFIER
                | INTEGER_LITERAL
                | FLOAT_LITERAL
                | CHAR_LITERAL
                | STRING_LITERAL
                | IDENTIFIER OPEN_PAREN ExprList CLOSED_PAREN
                | UnaryOp Factor
                ;

UnaryOp        : MINUS
                | BANG
                | PLUS_PLUS
                | DASH_DASH
                ;

%%