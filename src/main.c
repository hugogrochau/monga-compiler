#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"

Token token;

void printTokenString(TokenType type) {
  if (type < 256) {
    printf("TK_ASCII (");
    putchar(token.type);
    putchar(')');
  } else if (type == TK_AS) {
    printf("TK_AS");
  } else if (type == TK_CHAR) {
    printf("TK_CHAR");
  } else if (type == TK_ELSE) {
    printf("TK_ELSE");
  } else if (type == TK_FLOAT) {
    printf("TK_FLOAT");
  } else if (type == TK_IF) {
    printf("TK_IF");
  } else if (type == TK_INT) {
    printf("TK_INT");
  } else if (type == TK_NEW) {
    printf("TK_NEW");
  } else if (type == TK_RETURN) {
    printf("TK_RETURN");
  } else if (type == TK_VOID) {
    printf("TK_VOID");
  } else if (type == TK_WHILE) {
    printf("TK_WHILE");
  } else if (type == TK_GREATER_EQUAL) {
    printf("TK_GREATER_EQUAL");
  } else if (type == TK_LESS_EQUAL) {
    printf("TK_LESS_EQUAL");
  } else if (type == TK_EQUAL) {
    printf("TK_EQUAL");
  } else if (type == TK_NOT_EQUAL) {
    printf("TK_NOT_EQUAL");
  } else if (type == TK_LOGIC_AND) {
    printf("TK_LOGIC_AND");
  } else if (type == TK_LOGIC_OR) {
    printf("TK_LOGIC_OR");
  } else if (type == TK_ID) {
    printf("TK_ID (");
    printf("%s", token.data.s);
    putchar(')');
  } else if (type == TK_INT_CONSTANT) {
    printf("TK_INT_CONSTANT (");
    printf("%ld", token.data.l);
    putchar(')');
  } else if (type == TK_FLOAT_CONSTANT) {
    printf("TK_FLOAT_CONSTANT (");
    printf("%.2f", token.data.d);
    putchar(')');
  } else if (type == TK_STRING) {
    printf("TK_STRING (");
    printf("%s", token.data.s);
    putchar(')');
  }
}

int main(void) {
  TokenType type;
  while ( type = yylex() ) {
    printTokenString(type);
    putchar('\n');
  }
}
