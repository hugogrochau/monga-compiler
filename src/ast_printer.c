#include <stdio.h>

#include "ast_structure.h"
#include "ast_printer.h"

void printLevel(char *string, int depth) {
  for (int i = 0; i < depth; i++) {
    printf("  ");
  }
  printf(string);
  putchar('\n');
}

void printDeclaration (AST_Declaration *declaration, int depth) {
  if (declaration->type == AST_DECLARATION_VARIABLE) {
    printLevel("[DECLARATION-VARIABLE]", depth);
  } else if (declaration->type == AST_DECLARATION_FUNCTION) {
    printLevel("[DECLARATION-FUNCTION]", depth);
  } else {
    printLevel("[DECLARATION-UNKNOWN]", depth);
  }
}

void printDeclarations (AST_DeclarationElement *declarationList, int depth) {
  AST_DeclarationElement *element = declarationList;

  while (element != NULL) {
    printLevel("[DECLARATION]", depth);
    printDeclaration(element->declaration, depth + 1);
    element = element->next;
  }
}

void AST_printProgram (AST_Program *program) {
  int depth = 0;
  printLevel("[PROGRAM]", depth);

  printDeclarations(program->declarations, depth + 1);
}
