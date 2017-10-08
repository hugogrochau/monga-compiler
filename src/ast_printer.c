#include <stdio.h>
#include <stdarg.h>

#include "ast_printer.h"

void printLevel(int depth, char *template, ...);

void printType(int depth, AST_Type type);

void printDeclarationList (int depth, AST_DeclarationElement *declarationList);

void printDeclaration (int depth, AST_Declaration *declaration);

void printDeclarationVariable(int depth, AST_DeclarationVariable *declaration);

void printDeclarationFunction(int depth, AST_DeclarationFunction *declaration);

void printParameterList(int depth, AST_ParameterElement *parameterList);

void printParameter(int depth, AST_Parameter *parameter);

void printBlock(int depth, AST_Block *block);

void printCommandList(int depth, AST_CommandElement *commandList);

void printCommand(int depth, AST_Command *command);

void printId(int depth, char *id);

void AST_printProgram (AST_Program *program) {
  int depth = 0;
  printLevel(depth, "[PROGRAM]");

  printDeclarationList(depth + 1, program->declarations);
}

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

void printDeclarationList (int depth, AST_DeclarationElement *declarationList) {
  AST_DeclarationElement *currentElement = declarationList;

  while (currentElement != NULL) {
    printDeclaration(depth, currentElement->declaration);
    currentElement = currentElement->next;
  }
}

void printDeclaration (int depth, AST_Declaration *declaration) {
  printLevel(depth, "[DECLARATION]");
  switch (declaration->declarationType) {
    case AST_DECLARATION_VARIABLE:
      printDeclarationVariable(depth + 1, declaration->declaration.variable);
      break;
    case AST_DECLARATION_FUNCTION:
      printDeclarationFunction(depth + 1, declaration->declaration.function);
      break;
    default:
      printLevel(depth + 1, "[UNKNOWN]");
      break;
  }
}

void printDeclarationVariable(int depth, AST_DeclarationVariable *declaration) {
  printLevel(depth, "[VARIABLE]");
  printId(depth + 1, declaration->id);
  printType(depth + 1, declaration->type);
}

void printDeclarationFunction(int depth, AST_DeclarationFunction *declaration) {
  printLevel(depth, "[FUNCTION]");
  printId(depth + 1, declaration->id);
  printParameterList(depth + 1, declaration->parameterList);
  printType(depth + 1, declaration->type);
  printBlock(depth + 1, declaration->block);
}

void printParameterList(int depth, AST_ParameterElement *parameterList) {
  AST_ParameterElement *currentElement = parameterList;

  while (currentElement != NULL) {
    printParameter(depth, currentElement->parameter);
    currentElement = currentElement->next;
  }
}

void printParameter(int depth, AST_Parameter *parameter) {
  printLevel(depth, "[PARAMETER]");
  printId(depth + 1, parameter->id);
  printType(depth + 1, parameter->type);
}

void printBlock(int depth, AST_Block *block) {
  printLevel(depth, "[BLOCK]");
  printDeclarationList(depth + 1, block->declarationVariableList);
  printCommandList(depth + 1, block->commandList);
}

void printCommandList(int depth, AST_CommandElement *commandList) {
  AST_CommandElement *currentElement = commandList;

  while (currentElement != NULL) {
    printCommand(depth, currentElement->command);
    currentElement = currentElement->next;
  }
}

void printCommand(int depth, AST_Command *command) {
  switch(command->commandType) {
    case AST_COMMAND_IF:
      printLevel(depth, "[COMMAND-IF]");
      break;
    case AST_COMMAND_WHILE:
      printLevel(depth, "[COMMAND-WHILE]");
      break;
    case AST_COMMAND_ASSIGN:
      printLevel(depth, "[COMMAND-ASSIGN]");
      break;
    case AST_COMMAND_RETURN:
      printLevel(depth, "[COMMAND-RETURN]");
      break;
    case AST_COMMAND_CALL:
      printLevel(depth, "[COMMAND-CALL]");
      break;
    case AST_COMMAND_PRINT:
      printLevel(depth, "[COMMAND-PRINT]");
      break;
    case AST_COMMAND_BLOCK:
      printLevel(depth, "[COMMAND-BLOCK]");
      break;
    default:
      printLevel(depth, "[COMMAND-UNKNOWN]");
      break;
  }
}

void printId(int depth, char *id) {
  printLevel(depth, "[ID (%s)]", id);
}
