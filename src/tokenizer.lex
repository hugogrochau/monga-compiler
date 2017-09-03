%option noyywrap

%{
  #include "tokenizer.h"
%}

%%
[\t\n\r ] { };
"char"  { return TK_CHAR; }
"else"  { return TK_ELSE; }
"float"  { return TK_FLOAT; }
"if"  { return TK_IF; }
"new"  { return TK_NEW; }
"return"  { return TK_RETURN; }
"void"  { return TK_VOID; }
"while"  { return TK_WHILE; }

[a-zA-Z_][a-zA-Z0-9_]* { return TK_ID; }

. { return yytext[0]; }
%%
