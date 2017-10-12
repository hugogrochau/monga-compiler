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
  declarationElement->next = NULL;

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
  parameterList->next = NULL;

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
  parameterElement->next = NULL;

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

AST_CommandElement * AST_createCommandList(AST_Command *command) {
  AST_CommandElement *commandElement = malloc(sizeof(AST_CommandElement));

  commandElement->command = command;
  commandElement->next = NULL;
  commandElement->previous = NULL;

  return commandElement;
}

AST_CommandElement * AST_appendCommandList(AST_CommandElement *commandList, AST_Command *command) {
  AST_CommandElement *commandElement = malloc(sizeof(AST_CommandElement));
  AST_CommandElement *currentElement = commandList;

  commandElement->command = command;
  commandElement->next = currentElement;

  return commandElement;
}

AST_Command * AST_createCommandIf(AST_Expression *expression, AST_Block *thenBlock) {
  AST_CommandIf *commandIf = malloc(sizeof(AST_CommandIf));
  AST_Command *command = malloc(sizeof(AST_Command));

  commandIf->commandType = AST_COMMAND_IF;
  commandIf->expression = expression;
  commandIf->thenBlock = thenBlock;
  commandIf->elseBlock = NULL;

  command->commandType = AST_COMMAND_IF;
  command->command.commandIf = commandIf;

  return command;
}

AST_Command * AST_createCommandIfElse(AST_Expression *expression, AST_Block *thenBlock, AST_Block *elseBlock) {
  AST_CommandIf *commandIf = malloc(sizeof(AST_CommandIf));
  AST_Command *command = malloc(sizeof(AST_Command));

  commandIf->commandType = AST_COMMAND_IF;
  commandIf->expression = expression;
  commandIf->thenBlock = thenBlock;
  commandIf->elseBlock = NULL;

  command->commandType = AST_COMMAND_IF;
  command->command.commandIf = commandIf;

  return command;
}

AST_Command * AST_createCommandWhile(AST_Expression *expression, AST_Block *block) {
  AST_CommandWhile *commandWhile = malloc(sizeof(AST_CommandWhile));
  AST_Command *command = malloc(sizeof(AST_Command));

  commandWhile->commandType = AST_COMMAND_WHILE;
  commandWhile->expression = expression;
  commandWhile->block = block;

  command->commandType = AST_COMMAND_WHILE;
  command->command.commandWhile = commandWhile;

  return command;
}

AST_Command * AST_createCommandAssign(AST_Variable *variable, AST_Expression *expression) {
  AST_CommandAssign *commandAssign = malloc(sizeof(AST_CommandAssign));
  AST_Command *command = malloc(sizeof(AST_Command));

  commandAssign->commandType = AST_COMMAND_ASSIGN;
  commandAssign->variable = variable;
  commandAssign->expression = expression;

  command->commandType = AST_COMMAND_ASSIGN;
  command->command.commandAssign = commandAssign;

  return command;
}

AST_Command * AST_createCommandReturnEmpty() {
  AST_CommandReturn *commandReturn = malloc(sizeof(AST_CommandReturn));
  AST_Command *command = malloc(sizeof(AST_Command));

  commandReturn->commandType = AST_COMMAND_RETURN;
  commandReturn->expression = NULL;

  command->commandType = AST_COMMAND_RETURN;
  command->command.commandReturn = commandReturn;

  return command;

}

AST_Command * AST_createCommandReturn(AST_Expression *expression) {
  AST_CommandReturn *commandReturn = malloc(sizeof(AST_CommandReturn));
  AST_Command *command = malloc(sizeof(AST_Command));

  commandReturn->commandType = AST_COMMAND_RETURN;
  commandReturn->expression = expression;

  command->commandType = AST_COMMAND_RETURN;
  command->command.commandReturn = commandReturn;

  return command;
}

AST_Command * AST_createCommandCall(AST_Call *call) {
  AST_CommandCall *commandCall = malloc(sizeof(AST_CommandCall));
  AST_Command *command = malloc(sizeof(AST_Command));

  commandCall->commandType = AST_COMMAND_CALL;
  commandCall->call = call;

  command->commandType = AST_COMMAND_CALL;
  command->command.commandCall = commandCall;

  return command;
}

AST_Command * AST_createCommandPrint(AST_Expression *expression) {
  AST_CommandPrint *commandPrint = malloc(sizeof(AST_CommandPrint));
  AST_Command *command = malloc(sizeof(AST_Command));

  commandPrint->commandType = AST_COMMAND_PRINT;
  commandPrint->expression = expression;

  command->commandType = AST_COMMAND_PRINT;
  command->command.commandPrint = commandPrint;

  return command;
}

AST_Command * AST_createCommandBlock(AST_Block *block) {
  AST_CommandBlock *commandBlock = malloc(sizeof(AST_CommandBlock));
  AST_Command *command = malloc(sizeof(AST_Command));

  commandBlock->commandType = AST_COMMAND_BLOCK;
  commandBlock->block = block;

  command->commandType = AST_COMMAND_BLOCK;
  command->command.commandBlock = commandBlock;

  return command;
}

AST_Call * AST_createCall(char *id, AST_ExpressionElement *expressionList) {
  AST_Call *call = malloc(sizeof(AST_Call));

  call->id = id;
  call->expressionList = expressionList;

  return call;
}
