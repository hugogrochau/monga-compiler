#include <stdlib.h>

#include "ast_creation.h"
#include "ast_structure.h"

AST_Program * AST_createProgram(AST_DeclarationElement *declarationList) {
  AST_Program *program = malloc(sizeof(AST_Program));

  program->declarations = declarationList;

  return program;
}

AST_DeclarationElement * AST_createDeclarationList(AST_Declaration *declaration) {
  AST_DeclarationElement *declarationList = malloc(sizeof(AST_DeclarationElement));

  declarationList->declaration = declaration;
  declarationList->next = NULL;

  return declarationList;
}

AST_DeclarationElement * AST_appendDeclaration(AST_DeclarationElement *declarationList, AST_Declaration *declaration) {
  AST_DeclarationElement *newElement = malloc(sizeof(AST_DeclarationElement));
  AST_DeclarationElement *currentElement = declarationList;

  newElement->declaration = declaration;

  /* Go to the end of the linked list */
  while (currentElement->next != NULL) {
    currentElement = currentElement->next;
  }

  currentElement->next = newElement;

  return declarationList;
}

AST_Declaration * AST_createDeclarationVariable(AST_DeclarationVariable *declaration) {
  AST_Declaration *newDeclaration = malloc(sizeof(AST_Declaration));

  newDeclaration->type = AST_DECLARATION_VARIABLE;
  newDeclaration->declaration.variable = declaration;

  return newDeclaration;
}

AST_Declaration * AST_createDeclarationFunction(AST_DeclarationFunction *declaration) {
  AST_Declaration *newDeclaration = malloc(sizeof(AST_Declaration));

  newDeclaration->type = AST_DECLARATION_FUNCTION;
  newDeclaration->declaration.function = declaration;

  return newDeclaration;
}
