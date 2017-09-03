#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"

void printTokenString(TOKEN token) {
  if (token == TK_CHAR) {
    printf("TK_CHAR");
  } else if (token == TK_ELSE) {
    printf("TK_ELSE");
  } else if (token == TK_FLOAT) {
    printf("TK_FLOAT");
  } else if (token == TK_IF) {
    printf("TK_IF");
  } else if (token == TK_NEW) {
    printf("TK_NEW");
  } else if (token == TK_RETURN) {
    printf("TK_RETURN");
  } else if (token == TK_VOID) {
    printf("TK_VOID");
  } else if (token == TK_WHILE) {
    printf("TK_WHILE");
  } else if (token == TK_ID) {
    printf("TK_ID");
  } else if (token < 256) {
    printf("TK_ASCII (");
    putchar(token);
    putchar(')');
  }
}

int main(void) {
  int token;

  while ( ( token = yylex() )) {
    printTokenString(token);
    putchar('\n');
  }
}