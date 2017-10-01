%{
    #include <stdio.h>
    #include "ast_structure.h"
    #include "ast_creation.h"

    extern int yylex(void);
    void yyerror(char *);

    extern int lineNumber;

    extern AST_Program *program;
%}

%token TK_AS
%token TK_CHAR
%token TK_ELSE
%token TK_FLOAT
%token TK_IF
%token TK_INT
%token TK_NEW
%token TK_RETURN
%token TK_VOID
%token TK_WHILE
%token TK_ID
%token TK_EQUAL
%token TK_NOT_EQUAL
%token TK_LESS_EQUAL
%token TK_GREATER_EQUAL
%token TK_LOGIC_AND
%token TK_LOGIC_OR
%token TK_INT_CONSTANT
%token TK_FLOAT_CONSTANT
%token TK_STRING

%union{
    AST_DeclarationType *declarationType;
    AST_DeclarationVariable *declarationVariable;
    AST_DeclarationFunction *declarationFunction;
    AST_Declaration *declaration;
    AST_DeclarationElement *declarationElement;
    AST_Program *program;
}

%type <program> program
%type <declarationElement> declaration_list
%type <declaration> declaration
%type <declarationVariable> declaration_variable
%type <declarationFunction> declaration_function

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
        $$ = AST_createDeclarationVariable($1);
    } |
    declaration_function {
        $$ = AST_createDeclarationFunction($1);
    }
;

declaration_variable: TK_ID ':' type ';' {;}
;

type: TK_INT {;}
    | TK_CHAR {;}
    | TK_FLOAT {;}
    | TK_VOID {;}
    | type '[' ']' {;}
;

declaration_function: TK_ID '(' parameter_list ')' ':' type block {;}
;

parameter_list: parameter {;}
              | parameter_list ',' parameter {;}
              | {;}
;

parameter: TK_ID ':' type {;}
;

block: '{' declaration_variable_list command_list '}' {;}
     | '{' declaration_variable_list '}' {;}
     | '{' command_list '}' {;}
     | '{' '}' {;}
;

declaration_variable_list: declaration_variable {;}
                         | declaration_variable_list declaration_variable {;}
;


command_list: command {;}
            | command_list command {;}
;

command: TK_IF expression block {;}
       | TK_IF expression block TK_ELSE block {;}
       | TK_WHILE expression block {;}
       | variable '=' expression ';' {;}
       | TK_RETURN ';' {;}
       | TK_RETURN expression ';' {;}
       | call ';' {;}
       | '@' expression ';' {;}
       | block {;}
;

call: TK_ID '(' expression_list ')' {;}
;

expression_primary: variable {;}
                  | TK_INT_CONSTANT {;}
                  | TK_FLOAT_CONSTANT {;}
                  | TK_STRING {;}
                  | '(' expression ')' {;}
                  | call {;}
                  | TK_NEW type '[' expression ']' {;}
;

variable: TK_ID {;}
        | expression_primary '[' expression ']' {;}
;

expression_list: expression {;}
               | expression_list ',' expression {;}
;

expression_postfix: expression_primary {;}
                  | expression_postfix TK_AS type {;}
;

expression_unary: expression_postfix {;}
                | '-' expression_unary {;}
                | '!' expression_unary {;}
;

expression_multiplicative: expression_unary {;}
                         | expression_multiplicative '*' expression_unary {;}
                         | expression_multiplicative '/' expression_unary {;}
;

expression_additive: expression_multiplicative {;}
                   | expression_additive '+' expression_multiplicative {;}
                   | expression_additive '-' expression_multiplicative {;}
;

expression_relational: expression_additive {;}
                     | expression_additive '<' expression_additive {;}
                     | expression_additive '>' expression_additive {;}
                     | expression_additive TK_LESS_EQUAL expression_additive {;}
                     | expression_additive TK_GREATER_EQUAL expression_additive {;}
                     | expression_additive TK_EQUAL expression_additive {;}
                     | expression_additive TK_NOT_EQUAL expression_additive {;}
;

expression_logic_and: expression_relational {;}
                    | expression_logic_and TK_LOGIC_AND expression_relational {;}
;

expression_logic_or: expression_logic_and {;}
          | expression TK_LOGIC_OR expression_logic_and {;}
;

expression: expression_logic_or;

%%
void yyerror(char *s) {
    printf("%s. On line number %d\n", s, lineNumber);
}