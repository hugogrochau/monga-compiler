#include <stdio.h>
#include <stdarg.h>

#include "ast_printer.h"

void printLevel(int depth, char *template, ...) {
  va_list argumentList;
  va_start(argumentList, template);

  for (int i = 0; i < depth; i++) {
    printf("  ");
  }

  vprintf(template, argumentList);
  va_end(argumentList);

  putchar('\n');
}

void printType(int depth, AST_Type type) {
  switch (type) {
    case AST_VOID:
      printLevel(depth, "[VOID]");
      break;
    case AST_INT:
      printLevel(depth, "[INT]");
      break;
    case AST_FLOAT:
      printLevel(depth, "[FLOAT]");
      break;
    case AST_CHAR:
      printLevel(depth, "[CHAR]");
      break;
    case AST_ARRAY_INT:
      printLevel(depth, "[ARRAY_INT]");
      break;
    case AST_ARRAY_FLOAT:
      printLevel(depth, "[ARRAY_FLOAT]");
      break;
    case AST_ARRAY_CHAR:
      printLevel(depth, "[ARRAY_CHAR]");
      break;
  }
}

void printId(int depth, char *id) {
  printLevel(depth, "[ID (%s)]", id);
}

void printDeclarationFunction(int depth, AST_DeclarationFunction *declaration) {
  printLevel(depth, "[FUNCTION]");
  printId(depth + 1, declaration->id);
  printType(depth + 1, declaration->type);
}

void printDeclarationVariable(int depth, AST_DeclarationVariable *declaration) {
  printLevel(depth, "[VARIABLE]");
  printId(depth + 1, declaration->id);
  printType(depth + 1, declaration->type);
}

void printDeclaration (int depth, AST_Declaration *declaration) {
  if (declaration->declarationType == AST_DECLARATION_VARIABLE) {
    printLevel(depth, "[DECLARATION-VARIABLE]");
    printDeclarationVariable(depth + 1, declaration->declaration.variable);
  } else if (declaration->declarationType == AST_DECLARATION_FUNCTION) {
    printLevel(depth, "[DECLARATION-FUNCTION]");
    printDeclarationFunction(depth + 1, declaration->declaration.function);
  } else {
    printLevel(depth, "[DECLARATION-UNKNOWN]");
  }
}

void printDeclarations (int depth, AST_DeclarationElement *declarationList) {
  AST_DeclarationElement *element = declarationList;

  while (element != NULL) {
    printLevel(depth, "[DECLARATION]");
    printDeclaration(depth + 1, element->declaration);
    element = element->next;
  }
}

void AST_printProgram (AST_Program *program) {
  int depth = 0;
  printLevel(depth, "[PROGRAM]");

  printDeclarations(depth + 1, program->declarations);
}
