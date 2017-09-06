%option noyywrap

%{
  #include "tokenizer.h"
%}

%%
  /* Whitespace */
[\t\n\r ] { };

  /* Comments */
"/*"([^*]|"*"*[^/*])*"*"*"*/" { };
"#".* { };


  /* Strings */
\".*\" { };

  /* Reserved words */
[\t\n\r ] { };
"as"  { return TK_AS; }
"char"  { return TK_CHARACTER; }
"else"  { return TK_ELSE; }
"float"  { return TK_FLOAT; }
"if"  { return TK_IF; }
"int"  { return TK_INT; }
"new"  { return TK_NEW; }
"return"  { return TK_RETURN; }
"void"  { return TK_VOID; }
"while"  { return TK_WHILE; }

  /* Operators */
"==" { return TK_EQUAL; }
"~=" { return TK_NOT_EQUAL; }
"<=" { return TK_LESS_EQUAL; }
">=" { return TK_GREATER_EQUAL; }
"&&" { return TK_LOGIC_AND; }
"||" { return TK_LOGIC_OR; }

  /* Identifiers */
[a-zA-Z_][a-zA-Z0-9_]* { return TK_ID; }

  /* Integers */
0[xX][0-9a-fA-F]+ { return TK_INTEGER_CONSTANT; }
[0-9]+ { return TK_INTEGER_CONSTANT; };

  /* ASCII characters */
. { return yytext[0]; }
%%
