#include <stdio.h>

#include "ast_structure.h"
#include "ast_printer.h"

void printDeclaration (AST_Declaration *declaration) {
  if (declaration->type == AST_DECLARATION_VARIABLE) {
    printf("VARIABLE]\n");
  } else if (declaration->type == AST_DECLARATION_FUNCTION) {
    printf("FUNCTION]\n");
  } else {
    printf("UNKNOWN]\n");
  }
}

void printDeclarations (AST_DeclarationElement *declarationList) {
  AST_DeclarationElement *element = declarationList;
  while (element != NULL) {
    printf("[DECLARATION-");
    printDeclaration(element->declaration);
    element = element->next;
  }
}

void AST_printProgram (AST_Program *program) {
  printf("[PROGRAM]\n");
  printDeclarations(program->declarations);
}

