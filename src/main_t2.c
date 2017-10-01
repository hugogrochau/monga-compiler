#include <stdio.h>
#include <stdlib.h>

#include "ast_structure.h"
#include "tokenizer.h"
#include "parser.h"

AST_Program *program;

int main(void) {
  return yyparse();
}
