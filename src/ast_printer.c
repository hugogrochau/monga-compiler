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

void printType(AST_Type type, int depth) {
  switch (type) {
    case AST_VOID:
      printLevel("[VOID]", depth);
      break;
    case AST_INT:
      printLevel("[INT]", depth);
      break;
    case AST_FLOAT:
      printLevel("[FLOAT]", depth);
      break;
    case AST_CHAR:
      printLevel("[CHAR]", depth);
      break;
    case AST_ARRAY_INT:
      printLevel("[ARRAY_INT]", depth);
      break;
    case AST_ARRAY_FLOAT:
      printLevel("[ARRAY_FLOAT]", depth);
      break;
    case AST_ARRAY_CHAR:
      printLevel("[ARRAY_CHAR]", depth);
      break;
  }
}

void printDeclarationVariable(AST_DeclarationVariable *declaration, int depth) {
  printLevel("[VARIABLE]", depth);
  printType(declaration->type, depth);
}

void printDeclaration (AST_Declaration *declaration, int depth) {
  if (declaration->type == AST_DECLARATION_VARIABLE) {
    printLevel("[DECLARATION-VARIABLE]", depth);
    printDeclarationVariable(declaration->declaration.variable, depth + 1);
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
