#include <stdlib.h>

#include "ast_creation.h"

AST_Type AST_createArrayType(AST_Type type) {
  switch (type) {
    case AST_INT:
      return AST_ARRAY_INT;
    case AST_FLOAT:
      return AST_ARRAY_FLOAT;
    case AST_CHAR:
      return AST_ARRAY_CHAR;
  }
}

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
  AST_DeclarationElement *declarationElement = malloc(sizeof(AST_DeclarationElement));
  AST_DeclarationElement *currentElement = declarationList;

  /* Go to the end of the linked list */
  while (currentElement->next != NULL) {
    currentElement = currentElement->next;
  }

  declarationElement->declaration = declaration;

  currentElement->next = declarationElement;

  return declarationList;
}

AST_Declaration * AST_createDeclarationAsVariable(AST_DeclarationVariable *declarationVariable) {
  AST_Declaration *declaration = malloc(sizeof(AST_Declaration));

  declaration->declarationType = AST_DECLARATION_VARIABLE;
  declaration->declaration.variable = declarationVariable;

  return declaration;
}

AST_Declaration * AST_createDeclarationAsFunction(AST_DeclarationFunction *declarationFunction) {
  AST_Declaration *declaration = malloc(sizeof(AST_Declaration));

  declaration->declarationType = AST_DECLARATION_FUNCTION;
  declaration->declaration.function = declarationFunction;

  return declaration;
}

AST_DeclarationVariable * AST_createDeclarationVariable(char *id, AST_Type type) {
  AST_DeclarationVariable *variableDeclaration = malloc(sizeof(AST_DeclarationVariable));

  variableDeclaration->declarationType = AST_DECLARATION_VARIABLE;
  variableDeclaration->id = id;
  variableDeclaration->type = type;

  return variableDeclaration;
}

AST_DeclarationFunction * AST_createDeclarationFunction(char * id, AST_ParameterElement *parameterList, AST_Type type, AST_Block *block) {
  AST_DeclarationFunction *functionDeclaration = malloc(sizeof(AST_DeclarationFunction));

  functionDeclaration->declarationType = AST_DECLARATION_FUNCTION;
  functionDeclaration->id = id;
  functionDeclaration->parameterList = parameterList;
  functionDeclaration->type = type;
  functionDeclaration->block = block;

  return functionDeclaration;
}

AST_ParameterElement * AST_createParameterList(AST_Parameter *parameter) {
  AST_ParameterElement *parameterList = malloc(sizeof(AST_ParameterElement));

  parameterList->parameter = parameter;

  return parameterList;

}

AST_ParameterElement * AST_appendParameter(AST_ParameterElement *parameterList, AST_Parameter *parameter) {
  AST_ParameterElement *parameterElement = malloc(sizeof(AST_ParameterElement));
  AST_ParameterElement *currentElement = parameterList;

  /* Go to the end of the linked list */
  while (currentElement->next != NULL) {
    currentElement = currentElement->next;
  }

  parameterElement->parameter = parameter;

  currentElement->next = parameterElement;

  return parameterList;
}

AST_Parameter * AST_createParameter(char *id, AST_Type type) {
  AST_Parameter *parameter = malloc(sizeof(AST_Parameter));

  parameter->id = id;
  parameter->type = type;

  return parameter;
}

AST_Block * AST_createBlock(AST_DeclarationElement *declarationVariableList, AST_CommandElement *commandList) {
  AST_Block *block = malloc(sizeof(AST_Block));

  block->declarationVariableList = declarationVariableList;
  block->commandList = commandList;

  return block;
}

AST_DeclarationElement * AST_createDeclarationVariableList(AST_DeclarationVariable *declarationVariable) {
  AST_Declaration *declaration = AST_createDeclarationAsVariable(declarationVariable);
  AST_DeclarationElement *declarationList = AST_createDeclarationList(declaration);

  return declarationList;
}

AST_DeclarationElement * AST_appendDeclarationVariableList(AST_DeclarationElement* declarationVariableList, AST_DeclarationVariable *declarationVariable) {
  AST_Declaration *declaration = AST_createDeclarationAsVariable(declarationVariable);
  AST_DeclarationElement *declarationList = AST_appendDeclaration(declarationVariableList, declaration);

  return declarationList;
}
