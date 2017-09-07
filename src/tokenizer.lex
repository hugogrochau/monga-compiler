%option noyywrap

D			[0-9]
XD		[0-9a-fA-F]
E			[Ee][+-]?{D}+

%{
  #include <string.h>
  #include "tokenizer.h"

  extern Token token;

  char *escapeString(char *inString) {
    char *outString = malloc((strlen(inString) + 1) * sizeof(char));
    // skip first "
    int inIndex = 1;
    int outIndex = 0;
    while (inString[inIndex] && inString[inIndex] != '"') {
      if (inString[inIndex] == '\\') {
        switch(inString[inIndex + 1]) {
          case 'a':
            outString[outIndex] = '\a';
            break;
          case 'b':
            outString[outIndex] = '\b';
            break;
          case 'f':
            outString[outIndex] = '\f';
            break;
          case 'n':
            outString[outIndex] = '\n';
            break;
          case 'r':
            outString[outIndex] = '\r';
            break;
          case 't':
            outString[outIndex] = '\t';
            break;
          case 'v':
            outString[outIndex] = '\v';
            break;
          case '\\':
            outString[outIndex] = '\\';
            break;
          case '"':
            outString[outIndex] = '"';
            break;
        }
        outIndex++;
        inIndex += 2;
      } else {
        outString[outIndex] = inString[inIndex];
        outIndex++;
        inIndex++;
      }
    }
    outString[outIndex] = '\0';
    return outString;
  }

  TokenType readToken(TokenType type) {
    token.type = type;

    switch (type) {
      case TK_ID:
        token.data.s = yytext;
        break;
      case TK_INTEGER_CONSTANT:
        // hexadecimal
        if (yytext[0] == '0' && (yytext[1] == 'x' || yytext[1] == 'X')) {
          token.data.l = strtol(yytext, NULL, 0);
        } else {
          token.data.l = strtol(yytext, NULL, 10);
        }
        break;
      case TK_FLOAT_CONSTANT:
        token.data.d = strtod(yytext, NULL);
        break;
      case TK_STRING:
        token.data.s = escapeString(yytext);
        break;
    }

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
\"(\\.|[^"])*\" { return readToken(TK_STRING); };

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

  /* Floats */
0[xX]{XD}+ { return readToken(TK_FLOAT_CONSTANT); }
0[xX]{XD}*"."{XD}+ { return readToken(TK_FLOAT_CONSTANT); }
0[xX]{XD}+"."{XD}* { return readToken(TK_FLOAT_CONSTANT); }
{D}+{E} { return readToken(TK_FLOAT_CONSTANT); }
{D}*"."{D}+({E})?	{ return readToken(TK_FLOAT_CONSTANT); }
{D}+"."{D}*({E})?	{ return readToken(TK_FLOAT_CONSTANT); }

  /* ASCII characters */
. { return readToken(yytext[0]); }
%%
