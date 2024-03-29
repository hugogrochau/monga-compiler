%option noyywrap
%option nounput
%option noinput

D			[0-9]
XD		[0-9a-fA-F]
E			[Ee][+-]?{D}+

%{
  #include <string.h>

  #include "util.h"
  #include "ast_structure.h"
  #include "tokenizer.h"

  int lineNumber = 1;

  char *escapeString(char *inString) {
    char *outString = safeMalloc((strlen(inString) + 1) * sizeof(char));
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

  void saveId() {
    char *idBuffer = safeMalloc(strlen(yytext) * sizeof(char));
    yylval.s = strcpy(idBuffer, yytext);
  }

  void saveIntConstant() {
    // hexadecimal
    if (yytext[0] == '0' && (yytext[1] == 'x' || yytext[1] == 'X')) {
      yylval.i = strtol(yytext, NULL, 0);
    // decimals (including those starting with 0)
    } else {
      yylval.i = strtol(yytext, NULL, 10);
    }
  }

  void saveFloatConstant() {
    yylval.f = strtod(yytext, NULL);
  }

  void saveStringConstant() {
    yylval.s = escapeString(yytext);
  }

  TokenType readToken(TokenType type) {
    return type;
  }
%}

%%
  /* Whitespace */
[\t\r ] { };
\n { lineNumber++; };

  /* Comments */
"#"[^\n]*\n { };

  /* Strings */
\"(\\[^\n]|[^"\n])*\" { saveStringConstant(); return readToken(TK_STRING); };

  /* Reserved words */
"as"  { return readToken(TK_AS); }
"char"  { return readToken(TK_CHAR); }
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
[a-zA-Z_][a-zA-Z0-9_]* { saveId(); return readToken(TK_ID); }

  /* Integers */
0[xX][0-9a-fA-F]+ { saveIntConstant(); return readToken(TK_INT_CONSTANT); }
[0-9]+ { saveIntConstant(); return readToken(TK_INT_CONSTANT); };

  /* Floats */
0[xX]{XD}*"."{XD}+ { saveFloatConstant(); return readToken(TK_FLOAT_CONSTANT); }
0[xX]{XD}+"."{XD}* { saveFloatConstant(); return readToken(TK_FLOAT_CONSTANT); }
{D}+{E} { saveFloatConstant(); return readToken(TK_FLOAT_CONSTANT); }
{D}*"."{D}+({E})?	{ saveFloatConstant(); return readToken(TK_FLOAT_CONSTANT); }
{D}+"."{D}*({E})?	{ saveFloatConstant(); return readToken(TK_FLOAT_CONSTANT); }

  /* ASCII characters */
. { return readToken(yytext[0]); }
%%
