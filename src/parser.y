%{
    #include <stdio.h>
    #include "ast_structure.h"
    #include "ast_create.h"
    #include "util.h"

    extern int yylex(void);
    void yyerror(char *);

    extern int lineNumber;

    extern AST_Program *program;
%}

%union{
    int i;
    float f;
    char *s;
    AST_Type type;
    AST_Program *program;
    AST_Block *block;
    AST_DeclarationElement *declarationElement;
    AST_Declaration *declaration;
    AST_DeclarationType *declarationType;
    AST_CommandElement *commandElement;
    AST_Command *command;
    AST_ExpressionElement *expressionElement;
    AST_Expression *expression;
    AST_Call *call;
    AST_Variable *variable;
}

%token TK_AS
%token TK_ELSE
%token TK_IF
%token TK_NEW
%token TK_RETURN
%token TK_WHILE
%token TK_EQUAL
%token TK_NOT_EQUAL
%token TK_LESS_EQUAL
%token TK_GREATER_EQUAL
%token TK_LOGIC_AND
%token TK_LOGIC_OR

%token <type> TK_CHAR
%token <type> TK_INT
%token <type> TK_FLOAT
%token <type> TK_VOID

%token <s> TK_ID

%token <i> TK_INT_CONSTANT
%token <f> TK_FLOAT_CONSTANT
%token <s> TK_STRING

%type <type> type
%type <program> program
%type <block> block
%type <declarationElement> declaration_list declaration_variable_list parameter_list parameter_list_non_empty
%type <declaration> declaration declaration_variable declaration_function parameter
%type <commandElement> command_list
%type <command> command
%type <call> call
%type <expressionElement> expression_list expression_list_non_empty
%type <expression> expression_primary expression_postfix expression_unary expression_multiplicative expression_additive expression_relational expression_logic_and expression_logic_or expression
%type <variable> variable

%start program

%%
program:
    declaration_list {
        program = AST_createProgram($1);
        $$ = program;
    }
;

declaration_list:
    declaration_list declaration {
        $$ = AST_appendDeclaration($1, $2);
    } |
    declaration {
        $$ = AST_createDeclarationList($1);
    }
;

declaration:
    declaration_variable {
        $$ = $1;
    } |
    declaration_function {
        $$ = $1;
    }
;

declaration_variable:
    TK_ID ':' type ';' {
        $$ = AST_createDeclarationVariable($1, $3);
    }
;

type:
    TK_INT {
        $$ = AST_INT;
    } |
    TK_CHAR {
        $$ = AST_CHAR;
    } |
    TK_FLOAT {
        $$ = AST_FLOAT;
    } |
    TK_VOID {
        $$ = AST_VOID;
    } |
    type '[' ']' {
        $$ = AST_createArrayType($1);
    }
;

declaration_function:
    TK_ID '(' parameter_list ')' ':' type block {
        $$ = AST_createDeclarationFunction($1, $3, $6, $7);
    }
;

parameter_list:
    parameter_list_non_empty {
        $$ = $1;
    } |
    %empty {
        $$ = NULL;
    }
;

parameter_list_non_empty:
    parameter {
        $$ = AST_createDeclarationList($1);
    } |
    parameter_list_non_empty ',' parameter {
        $$ = AST_appendDeclaration($1, $3);
    }
;

parameter:
    TK_ID ':' type {
        $$ = AST_createDeclarationParameter($1, $3);
    }
;

block:
    '{' declaration_variable_list command_list '}' {
        $$ = AST_createBlock($2, $3);
    }
;

declaration_variable_list:
    declaration_variable_list declaration_variable {
        if ($1 == NULL) {
            $$ = AST_createDeclarationList($2);
        } else {
            $$ = AST_appendDeclaration($1, $2);
        }
    } |
    %empty {
        $$ = NULL;
    }
;

command_list:
    command command_list {
        if ($2 == NULL) {
            $$ = AST_createCommandList($1);
        } else {
            $$ = AST_appendCommand($2, $1);
        }
    } |
    %empty {
        $$ = NULL;
    }
;

command:
    TK_IF expression block TK_ELSE block {
        $$ = AST_createCommandIfElse($2, $3, $5);
    } |
    TK_IF expression block {
        $$ = AST_createCommandIf($2, $3);
    } |
    TK_WHILE expression block {
        $$ = AST_createCommandWhile($2, $3);
    } |
    variable '=' expression ';' {
        $$ = AST_createCommandAssign($1, $3);
    } |
    TK_RETURN ';' {
        $$ = AST_createCommandReturnEmpty();
    } |
    TK_RETURN expression ';' {
        $$ = AST_createCommandReturn($2);
    } |
    call ';' {
        $$ = AST_createCommandCall($1);
    } |
    '@' expression ';' {
        $$ = AST_createCommandPrint($2);
    } |
    block {
        $$ = AST_createCommandBlock($1);
    }
;

call:
    TK_ID '(' expression_list ')' {
        $$ = AST_createCall($1, $3);
    }
;

expression_primary:
    variable {
        $$ = AST_createExpressionVariable($1);
    } |
    TK_INT_CONSTANT {
        $$ = AST_createExpressionIntConstant($1);
    } |
    TK_FLOAT_CONSTANT {
        $$ = AST_createExpressionFloatConstant($1);
    } |
    TK_STRING {
        $$ = AST_createExpressionStringConstant($1);
    } |
    '(' expression ')' {
        $$ = $2;
    } |
    call {
        $$ = AST_createExpressionCall($1);
    } |
    TK_NEW type '[' expression ']' {
        $$ = AST_createExpressionNew($2, $4);
    }
;

variable:
    TK_ID {
        $$ = AST_createVariableSimple($1);
    } |
    expression_primary '[' expression ']' {
        $$ = AST_createVariableArray($1, $3);
    }
;

expression_list:
    expression_list_non_empty {
        $$ = $1;
    } |
    %empty {
        $$ = NULL;
    }
;

expression_list_non_empty:
    expression {
        $$ = AST_createExpressionList($1);
    } |
    expression_list_non_empty ',' expression {
        $$ = AST_appendExpression($1, $3);
    }
;

expression_postfix:
    expression_primary {
        $$ = $1;
    } |
    expression_postfix TK_AS type {
        $$ = AST_createExpressionAs($1, $3);
    }
;

expression_unary:
    expression_postfix {
        $$ = $1;
    } |
    '-' expression_unary {
        $$ = AST_createExpressionUnary($2, AST_EXPRESSION_UNARY_MINUS);
    } |
    '!' expression_unary {
        $$ = AST_createExpressionUnary($2, AST_EXPRESSION_UNARY_NOT);
    }
;

expression_multiplicative:
    expression_unary {
        $$ = $1;
    } |
    expression_multiplicative '*' expression_unary {
        $$ = AST_createExpressionBinary($1, $3, AST_EXPRESSION_BINARY_MULTIPLICATION);
    } |
    expression_multiplicative '/' expression_unary {
        $$ = AST_createExpressionBinary($1, $3, AST_EXPRESSION_BINARY_DIVISION);
    }
;

expression_additive:
    expression_multiplicative {
        $$ = $1;
    } |
    expression_additive '+' expression_multiplicative {
        $$ = AST_createExpressionBinary($1, $3, AST_EXPRESSION_BINARY_PLUS);
    } |
    expression_additive '-' expression_multiplicative {
        $$ = AST_createExpressionBinary($1, $3, AST_EXPRESSION_BINARY_MINUS);
    }
;

expression_relational:
    expression_additive {
        $$ = $1;
    } |
    expression_additive '<' expression_additive {
        $$ = AST_createExpressionBinary($1, $3, AST_EXPRESSION_BINARY_LESS);
    } |
    expression_additive '>' expression_additive {
        $$ = AST_createExpressionBinary($1, $3, AST_EXPRESSION_BINARY_GREATER);
    } |
    expression_additive TK_LESS_EQUAL expression_additive {
        $$ = AST_createExpressionBinary($1, $3, AST_EXPRESSION_BINARY_LESS_EQUAL);
    } |
    expression_additive TK_GREATER_EQUAL expression_additive {
        $$ = AST_createExpressionBinary($1, $3, AST_EXPRESSION_BINARY_GREATER_EQUAL);
    } |
    expression_additive TK_EQUAL expression_additive {
        $$ = AST_createExpressionBinary($1, $3, AST_EXPRESSION_BINARY_EQUAL);
    } |
    expression_additive TK_NOT_EQUAL expression_additive {
        $$ = AST_createExpressionBinary($1, $3, AST_EXPRESSION_BINARY_NOT_EQUAL);
    }
;

expression_logic_and:
    expression_relational {
        $$ = $1;
    } |
    expression_logic_and TK_LOGIC_AND expression_relational {
        $$ = AST_createExpressionBinary($1, $3, AST_EXPRESSION_BINARY_LOGIC_AND);
    }
;

expression_logic_or:
    expression_logic_and {
        $$ = $1;
    } |
    expression TK_LOGIC_OR expression_logic_and {
        $$ = AST_createExpressionBinary($1, $3, AST_EXPRESSION_BINARY_LOGIC_OR);
    }
;

expression:
    expression_logic_or {
        $$ = $1;
    }
;

%%
void yyerror(char *s) {
    error("%s. On line number %d\n", s, lineNumber);
}