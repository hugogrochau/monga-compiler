#include <stdlib.h>

#include "ast_structure.h"
#include "ast_knit.h"
#include "tokenizer.h"
#include "parser.h"

AST_Program *program;

int main(void) {
  int returnValue = yyparse();

  AST_knit(program);

  return returnValue;
}
