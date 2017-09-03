%option noyywrap

  /* Numeral excluding 0 */
FLOAT_N [1-9]
  /* Numeral including 0 */
FLOAT_D [0-9]
  /* Exponent part */
FLOAT_E ([eE][+\-]?{FLOAT_D}+)
  /* Valid remaining float content */
FLOAT_L (0|({FLOAT_N}{FLOAT_D}*))
  /* Whole float constant */
FLOAT ((({FLOAT_L}"."{FLOAT_D}*)|("."{FLOAT_D}+){FLOAT_E}?))|({FLOAT_L}{FLOAT_E})

%{
  #include "tokenizer.h"
%}

%%
  /* Whitespace */
[\t\n\r ] { };

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

  /* Floats */
{FLOAT_L} { return TK_FLOAT_CONSTANT; }

  /* Integers */
0[xX][0-9a-fA-F]+ { return TK_INTEGER_CONSTANT; }
[0-9]+ { return TK_INTEGER_CONSTANT; };


  /* ASCII characters */
. { return yytext[0]; }
%%
