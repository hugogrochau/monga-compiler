#include <stdio.h>
#include <stdlib.h>

#include "ast_structure.h"
#include "ast_print.h"
#include "tokenizer.h"
#include "parser.h"

AST_Program *program;

int main(void) {
  int returnValue = yyparse();

  AST_printProgram(program);

  return returnValue;
}
