%option noyywrap

%{
  #include <string.h>
  #include "tokenizer.h"

  extern Token token;

  TokenType readToken(TokenType type) {
    token.type = type;
    return type;
  }
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
"as"  { return readToken(TK_AS); }
"char"  { return readToken(TK_CHARACTER); }
"else"  { return readToken(TK_ELSE); }
"float"  { return readToken(TK_FLOAT); }
"if"  { return readToken(TK_IF); }
"int"  { return readToken(TK_INT); }
"new"  { return readToken(TK_NEW); }
"return"  { return readToken(TK_RETURN); }
"void"  { return readToken(TK_VOID); }
"while"  { return readToken(TK_WHILE); }

  /* Operators */
"==" { return readToken(TK_EQUAL); }
"~=" { return readToken(TK_NOT_EQUAL); }
"<=" { return readToken(TK_LESS_EQUAL); }
">=" { return readToken(TK_GREATER_EQUAL); }
"&&" { return readToken(TK_LOGIC_AND); }
"||" { return readToken(TK_LOGIC_OR); }

  /* Identifiers */
[a-zA-Z_][a-zA-Z0-9_]* { return readToken(TK_ID); }

  /* Integers */
0[xX][0-9a-fA-F]+ { return readToken(TK_INTEGER_CONSTANT); }
[0-9]+ { return readToken(TK_INTEGER_CONSTANT); };

  /* ASCII characters */
. { return readToken(yytext[0]); }
%%
