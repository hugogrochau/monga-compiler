#include <stdio.h>
#include <stdlib.h>

#include "ast_structure.h"
#include "tokenizer.h"

extern int yylex(void);
extern YYSTYPE yylval;
AST_Program *program;

void printTokenString(TokenType type) {
  switch (type) {
    case TK_AS:
      printf("TK_AS");
      break;
    case TK_CHAR:
      printf("TK_CHAR");
      break;
    case TK_ELSE:
      printf("TK_ELSE");
      break;
    case TK_FLOAT:
      printf("TK_FLOAT");
      break;
    case TK_IF:
      printf("TK_IF");
      break;
    case TK_INT:
      printf("TK_INT");
      break;
    case TK_NEW:
      printf("TK_NEW");
      break;
    case TK_RETURN:
      printf("TK_RETURN");
      break;
    case TK_VOID:
      printf("TK_VOID");
      break;
    case TK_WHILE:
      printf("TK_WHILE");
      break;
    case TK_GREATER_EQUAL:
      printf("TK_GREATER_EQUAL");
      break;
    case TK_LESS_EQUAL:
      printf("TK_LESS_EQUAL");
      break;
    case TK_EQUAL:
      printf("TK_EQUAL");
      break;
    case TK_NOT_EQUAL:
      printf("TK_NOT_EQUAL");
      break;
    case TK_LOGIC_AND:
      printf("TK_LOGIC_AND");
      break;
    case TK_LOGIC_OR:
      printf("TK_LOGIC_OR");
      break;
    case TK_ID:
      printf("TK_ID (");
      printf("%s", yylval.s);
      putchar(')');
      break;
    case TK_INT_CONSTANT:
      printf("TK_INT_CONSTANT (");
      printf("%ld", yylval.i);
      putchar(')');
      break;
    case TK_FLOAT_CONSTANT:
      printf("TK_FLOAT_CONSTANT (");
      printf("%.2f", yylval.f);
      putchar(')');
      break;
    case TK_STRING:
      printf("TK_STRING (");
      printf("%s", yylval.s);
      putchar(')');
      break;
    default:
      /* ASCII tokens */
      if (type < 256) {
        printf("TK_");
        putchar(type);
      } else {
        printf("UNKNOWN");
      }
      break;
  }
}

int main(void) {
  TokenType type;
  while ( type = yylex() ) {
    printTokenString(type);
    putchar('\n');
  }
}
