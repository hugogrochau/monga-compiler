#include <stdlib.h>

#include "ast_creation.h"
#include "ast_structure.h"

AST_Program * createProgram() {
  AST_Program *program = malloc(sizeof(AST_Program));
  program->head = NULL;

  return program;
}

AST_Program * appendDeclarationToProgram(AST_Program *program, AST_DeclarationElement *declarationElement) {
  AST_DeclarationElement *currentElement = program->head;

  if (currentElement == NULL) {
    program->head = declarationElement;
  } else {
    while (currentElement->next != NULL) {
      currentElement = currentElement->next;
    }

    currentElement->next = declarationElement;
  }

  return program;
}

AST_Program * appendDeclarationOrCreateProgram(AST_Program *program, AST_DeclarationElement *declarationElement) {
  if (program == NULL) {
    program = createProgram();
  }

  return appendDeclarationToProgram(program, declarationElement);
}
