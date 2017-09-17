%{

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

%start program

%%
program: definition {;}
       | definition definition {;}
;

definition: definition-variable {;}
          | definition-function {;}
;

definition-variables: definition-variable {;}
                    | definition-variable definition-variable {;}
;

definition-variable: TK_ID ':' type ';' {;}
;

type: TK_INT {;}
    | TK_CHAR {;}
    | TK_FLOAT {;}
    | TK_VOID {;}
    | type '[' ']' {;}
;

definition-function: TK_ID '(' parameters ')' ':' type block {;}
;

parameters: parameter {;}
          | parameter ',' parameter {;}
          | {;}
;

parameter: TK_ID ':' type {;}
;

block: '{' definition-variables commands '}' {;}
     | '{' definition-variables '}' {;}
     | '{' commands '}' {;}
     | '{' '}' {;}
;

commands: command {;}
        | command command {;}
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

variable: TK_ID {;}
        | expression '[' expression ']' {;}
;

expression: TK_INT_CONSTANT {;}
          | TK_FLOAT_CONSTANT {;}
          | TK_STRING {;}
          | '(' expression ')' {;}
          | call {;}
          | expression TK_AS type {;}
          | TK_NEW type '[' expression ']' {;}
          | '-' expression {;}
          | expression '+' expression {;}
          | expression '-' expression {;}
          | expression '*' expression {;}
          | expression '/' expression {;}
          | expression TK_EQUAL expression {;}
          | expression TK_NOT_EQUAL expression {;}
          | expression TK_LESS_EQUAL expression {;}
          | expression TK_GREATER_EQUAL expression {;}
          | expression '<' expression {;}
          | expression '>' expression {;}
          | '!' expression {;}
          | expression TK_LOGIC_AND expression {;}
          | expression TK_LOGIC_OR  expression {;}
;

call: TK_ID '(' expressions ')' {;}
;

expressions: expression {;}
           | expression ',' expression {;}
;
