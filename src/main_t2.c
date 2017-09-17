#include <stdio.h>
#include <stdlib.h>

#include "parser.h"
#include "tokenizer.h"

Token token;

int main(void) {
  return yyparse();
}
