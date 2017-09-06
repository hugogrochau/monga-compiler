#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"

void printTokenString(TOKEN token) {
  if (token < 256) {
    printf("TK_ASCII (");
    putchar(token);
    putchar(')');
  } else if (token == TK_AS) {
    printf("TK_AS");
  } else if (token == TK_CHARACTER) {
    printf("TK_CHARACTER");
  } else if (token == TK_ELSE) {
    printf("TK_ELSE");
  } else if (token == TK_FLOAT) {
    printf("TK_FLOAT");
  } else if (token == TK_IF) {
    printf("TK_IF");
  } else if (token == TK_INT) {
    printf("TK_INT");
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
  } else if (token == TK_GREATER_EQUAL) {
    printf("TK_GREATER_EQUAL");
  } else if (token == TK_LESS_EQUAL) {
    printf("TK_LESS_EQUAL");
  } else if (token == TK_EQUAL) {
    printf("TK_EQUAL");
  } else if (token == TK_NOT_EQUAL) {
    printf("TK_NOT_EQUAL");
  } else if (token == TK_LOGIC_AND) {
    printf("TK_LOGIC_AND");
  } else if (token == TK_LOGIC_OR) {
    printf("TK_LOGIC_OR");
  } else if (token == TK_INTEGER_CONSTANT) {
    printf("TK_INTEGER_CONSTANT");
  }
}

int main(void) {
  int token;

  while ( ( token = yylex() )) {
    printTokenString(token);
    putchar('\n');
  }
}
