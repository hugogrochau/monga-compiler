#include <stdlib.h>

#include "ast_structure.h"
#include "ast_knit.h"
#include "ast_type.h"
#include "code_generator.h"
#include "tokenizer.h"
#include "parser.h"

AST_Program *program;

int main(void) {
  int returnValue = yyparse();

  AST_knit(program);

  AST_type(program);

  CG_generateProgram(program);

  return returnValue;
}
