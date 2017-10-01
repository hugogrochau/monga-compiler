#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "parser.h"

typedef enum yytokentype TokenType;

typedef union tokenData {
  long l;
  double d;
  char *s;
} TokenData;

typedef struct token {
  TokenType type;
  TokenData data;
} Token;

int lineNumber;

#endif