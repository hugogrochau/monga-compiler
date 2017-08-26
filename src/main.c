#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"

void printTokenString(TOKEN token) {
  switch (token) {
    case TK_CHAR:
      printf("char");
      break;
    case TK_ELSE:
      printf("else");
      break;
    case TK_FLOAT:
      printf("float");
      break;
    case TK_IF:
      printf("if");
      break;
    case TK_NEW:
      printf("new");
      break;
    case TK_RETURN:
      printf("return");
      break;
    case TK_VOID:
      printf("void");
      break;
    case TK_WHILE:
      printf("while");
      break;
    default:
      printf("unknown");
  }
}

int main(void) {
  int token;

  while ( ( token = yylex() )) {
    printTokenString(token);
  }
}