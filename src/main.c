#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"

void printTokenString(TOKEN token) {
  switch (token) {
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
    default:
      printf("unknown");
  }
}

int main(void) {
  int token;

  while ( ( token = yylex() )) {
    printTokenString(token);
    putchar('\n');
  }
}