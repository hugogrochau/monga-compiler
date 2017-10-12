#include <stdio.h>
#include <stdarg.h>

#include "ast_printer.h"

void printLevel(int depth, char *template, ...);

void printType(int depth, AST_Type type);

void printDeclarationList (int depth, AST_DeclarationElement *declarationList);

void printDeclaration (int depth, AST_Declaration *declaration);

void printDeclarationVariable(int depth, AST_DeclarationVariable *declaration);

void printDeclarationFunction(int depth, AST_DeclarationFunction *declaration);

void printId(int depth, char *id);

void printParameterList(int depth, AST_ParameterElement *parameterList);

void printParameter(int depth, AST_Parameter *parameter);

void printBlock(int depth, AST_Block *block);

void printCommandList(int depth, AST_CommandElement *commandList);

void printCommand(int depth, AST_Command *command);

void printCommandIf(int depth, AST_CommandIf *command);

void printCommandWhile(int depth, AST_CommandWhile *command);

void printCommandAssign(int depth, AST_CommandAssign *command);

void printCommandReturn(int depth, AST_CommandReturn *command);

void printCommandCall(int depth, AST_CommandCall *command);

void printCommandPrint(int depth, AST_CommandPrint *command);

void printCommandBlock(int depth, AST_CommandBlock *command);

void printVariable(int depth, AST_Variable *variable);

void printVariableSimple(int depth, AST_VariableSimple *variable);

void printVariableArray(int depth, AST_VariableArray *variable);

void printCall(int depth, AST_Call * call);

void printExpressionList(int depth, AST_ExpressionElement *expressionList);

void printExpression(int depth, AST_Expression *expression);

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
      printLevel(depth, "[TYPE (VOID)]");
      break;
    case AST_INT:
      printLevel(depth, "[TYPE (INT)]");
      break;
    case AST_FLOAT:
      printLevel(depth, "[TYPE (FLOAT)]");
      break;
    case AST_CHAR:
      printLevel(depth, "[TYPE (CHAR)]");
      break;
    case AST_ARRAY_INT:
      printLevel(depth, "[TYPE (ARRAY_INT)]");
      break;
    case AST_ARRAY_FLOAT:
      printLevel(depth, "[TYPE (ARRAY_FLOAT])");
      break;
    case AST_ARRAY_CHAR:
      printLevel(depth, "[TYPE (ARRAY_CHAR)]");
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

void printId(int depth, char *id) {
  printLevel(depth, "[ID (%s)]", id);
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
  printLevel(depth, "[COMMAND]");
  switch(command->commandType) {
    case AST_COMMAND_IF:
      printCommandIf(depth + 1, command->command.commandIf);
      break;
    case AST_COMMAND_WHILE:
      printCommandWhile(depth + 1, command->command.commandWhile);
      break;
    case AST_COMMAND_ASSIGN:
      printCommandAssign(depth + 1, command->command.commandAssign);
      break;
    case AST_COMMAND_RETURN:
      printCommandReturn(depth + 1, command->command.commandReturn);
      break;
    case AST_COMMAND_CALL:
      printCommandCall(depth + 1, command->command.commandCall);
      break;
    case AST_COMMAND_PRINT:
      printCommandPrint(depth + 1, command->command.commandPrint);
      break;
    case AST_COMMAND_BLOCK:
      printCommandBlock(depth + 1, command->command.commandBlock);
      break;
    default:
      printLevel(depth + 1, "[UNKNOWN]");
      break;
  }
}

void printCommandIf(int depth, AST_CommandIf *command) {
  printLevel(depth, "[IF]");
  printExpression(depth + 1, command->expression);
  printBlock(depth + 1, command->thenBlock);
  if (command->elseBlock != NULL) {
    printBlock(depth + 1, command->elseBlock);
  }
}

void printCommandWhile(int depth, AST_CommandWhile *command) {
  printLevel(depth, "[WHILE]");
  printExpression(depth + 1, command->expression);
  printBlock(depth + 1, command->block);
}

void printCommandAssign(int depth, AST_CommandAssign *command) {
  printLevel(depth, "[ASSIGN]");
  printVariable(depth + 1, command->variable);
  printExpression(depth + 1, command->expression);
}

void printCommandReturn(int depth, AST_CommandReturn *command) {
  printLevel(depth, "[RETURN]");
  if (command->expression != NULL) {
    printExpression(depth + 1, command->expression);
  }
}
void printCommandCall(int depth, AST_CommandCall *command) {
  printCall(depth + 1, command->call);
}

void printCommandPrint(int depth, AST_CommandPrint *command) {
  printLevel(depth, "[PRINT]");
  printExpression(depth + 1, command->expression);
}

void printCommandBlock(int depth, AST_CommandBlock *command) {
  printBlock(depth + 1, command->block);
}

void printVariable(int depth, AST_Variable *variable) {
  printLevel(depth, "[VARIABLE]");
  switch (variable->variableType) {
    case AST_VARIABLE_SIMPLE:
      printId(depth + 1, variable->variable.simple->id);
      break;
    case AST_VARIABLE_ARRAY:
      printExpression(depth + 1, variable->variable.array->outerExpression);
      printExpression(depth + 1, variable->variable.array->innerExpression);
    break;
  }
}

void printCall(int depth, AST_Call *call) {
  printLevel(depth, "[CALL]");
  printId(depth + 1, call->id);
  printExpressionList(depth + 1, call->expressionList);
}

void printExpressionList(int depth, AST_ExpressionElement *expressionList) {
  AST_ExpressionElement *currentElement = expressionList;

  while (currentElement != NULL) {
    printExpression(depth, currentElement->expression);
    currentElement = currentElement->next;
  }
}

void printExpression(int depth, AST_Expression *expression) {
  printLevel(depth, "[EXPRESSION]");
  switch (expression->expressionType) {
    case AST_EXPRESSION_VARIABLE:
      printLevel(depth + 1, "[VARIABLE]");
      break;
    case AST_EXPRESSION_CONSTANT:
      printLevel(depth + 1, "[CONSTANT]");
      break;
    case AST_EXPRESSION_PARENTHESES:
      printLevel(depth + 1, "[PARENTHESES]");
      break;
    case AST_EXPRESSION_CALL:
      printLevel(depth + 1, "[CALL]");
      break;
    case AST_EXPRESSION_NEW:
      printLevel(depth + 1, "[NEW]");
      break;
    case AST_EXPRESSION_AS:
      printLevel(depth + 1, "[AS]");
      break;
    case AST_EXPRESSION_UNARY:
      printLevel(depth + 1, "[UNARY]");
      break;
    case AST_EXPRESSION_BINARY:
      printLevel(depth + 1, "[BINARY]");
      break;
  }
}