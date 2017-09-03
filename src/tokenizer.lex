%option noyywrap

%{
  #include "tokenizer.h"
%}

%%
  /* Whitespace */
[\t\n\r ] { };

  /* Reserved word */
[\t\n\r ] { };
"as"  { return TK_AS; }
"char"  { return TK_CHAR; }
"else"  { return TK_ELSE; }
"float"  { return TK_FLOAT; }
"if"  { return TK_IF; }
"int"  { return TK_INT; }
"new"  { return TK_NEW; }
"return"  { return TK_RETURN; }
"void"  { return TK_VOID; }
"while"  { return TK_WHILE; }

  /* Operator */
"==" { return TK_EQUAL; }
"~=" { return TK_NOT_EQUAL; }
"<=" { return TK_LESS_EQUAL; }
">=" { return TK_GREATER_EQUAL; }
"&&" { return TK_LOGIC_AND; }
"||" { return TK_LOGIC_OR; }

  /* Identifier */
[a-zA-Z_][a-zA-Z0-9_]* { return TK_ID; }

  /* ASCII character */
. { return yytext[0]; }
%%
