#include <stdio.h>

#include "ast_structure.h"
#include "ast_printer.h"

void printDeclarations (AST_DeclarationElement *element) {
  while (element != NULL) {
    printf("[DECLARATION]");
    element = element->next;
  }
}

void AST_printProgram (AST_Program *program) {
  printf("[PROGRAM]");
  printDeclarations(program->head);
}

