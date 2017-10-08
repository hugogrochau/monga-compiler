%{
    #include <stdio.h>
    #include "ast_structure.h"
    #include "ast_creation.h"

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
    AST_DeclarationVariable *declarationVariable;
    AST_DeclarationFunction *declarationFunction;
    AST_Parameter *parameter;
    AST_ParameterElement *parameterElement;
    AST_CommandElement *commandElement;
    AST_Command *command;
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
%type <declarationElement> declaration_list declaration_variable_list
%type <declaration> declaration
%type <declarationVariable> declaration_variable
%type <declarationFunction> declaration_function
%type <parameterElement> parameter_list parameter_list_non_empty
%type <parameter> parameter
%type <commandElement> command_list
%type <command> command
%type <call> call
%type <expressionElement> expression_list
%type <expression> expression expression_logic_or
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
        $$ = AST_createDeclarationAsVariable($1);
    } |
    declaration_function {
        $$ = AST_createDeclarationAsFunction($1);
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
        $$ = AST_createParameterList($1);
    } |
    parameter_list_non_empty ',' parameter {
        $$ = AST_appendParameter($1, $3);
    }
;

parameter:
    TK_ID ':' type {
        $$ = AST_createParameter($1, $3);
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
            $$ = AST_createDeclarationVariableList($2);
        } else {
            $$ = AST_appendDeclarationVariableList($1, $2);
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
            $$ = AST_appendCommandList($2, $1);
        }
    } |
    %empty {
        $$ = NULL;
    }
;

command:
    TK_IF expression block {
        $$ = AST_createCommandIf($2, $3);
    } |
    TK_IF expression block TK_ELSE block {
        $$ = AST_createCommandIfElse($2, $3, $5);
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

expression: expression_logic_or {;}
;

%%
void yyerror(char *s) {
    printf("%s. On line number %d\n", s, lineNumber);
}