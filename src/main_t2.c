#include <stdio.h>
#include <stdlib.h>

#include "parser.h"
#include "tokenizer.h"

int main(void) {
  return yyparse();
}
