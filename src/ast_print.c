#include <stdio.h>
#include <stdarg.h>

#include "ast_print.h"
#include "util.h"

void printType(int depth, AST_Type type);

void printDeclarationList(int depth, AST_DeclarationElement *declarationList);
void printDeclaration(int depth, AST_Declaration *declaration);
void printDeclarationVariable(int depth, AST_Declaration *declaration);
void printDeclarationFunction(int depth, AST_Declaration *declaration);
void printDeclarationParameter(int depth, AST_Declaration *declaration);

void printId(int depth, char *id);

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
void printExpressionVariable(int depth, AST_ExpressionVariable *expression);
void printExpressionParentheses(int depth, AST_ExpressionParentheses *expression);
void printExpressionCall(int depth, AST_ExpressionCall *expression);
void printExpressionNew(int depth, AST_ExpressionNew *expression);
void printExpressionAs(int depth, AST_ExpressionAs *expression);
void printExpressionConstant(int depth, AST_ExpressionConstant *expression);
void printExpressionUnary(int depth, AST_ExpressionUnary *expression);
void printExpressionBinary(int depth, AST_ExpressionBinary *expression);

void AST_printProgram (AST_Program *program) {
  int depth = 0;
  printLineWithDepth(depth, "[PROGRAM]");

  printDeclarationList(depth + 1, program->declarations);
}

void printType(int depth, AST_Type type) {
  switch (type) {
    case AST_VOID:
      printLineWithDepth(depth, "[TYPE (VOID)]");
      break;
    case AST_INT:
      printLineWithDepth(depth, "[TYPE (INT)]");
      break;
    case AST_FLOAT:
      printLineWithDepth(depth, "[TYPE (FLOAT)]");
      break;
    case AST_CHAR:
      printLineWithDepth(depth, "[TYPE (CHAR)]");
      break;
    case AST_ARRAY_INT:
      printLineWithDepth(depth, "[TYPE (ARRAY_INT)]");
      break;
    case AST_ARRAY_FLOAT:
      printLineWithDepth(depth, "[TYPE (ARRAY_FLOAT])");
      break;
    case AST_ARRAY_CHAR:
      printLineWithDepth(depth, "[TYPE (ARRAY_CHAR)]");
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
  printLineWithDepth(depth, "[DECLARATION]");
  switch (declaration->declarationType) {
    case AST_DECLARATION_VARIABLE:
      printDeclarationVariable(depth + 1, declaration);
      break;
    case AST_DECLARATION_FUNCTION:
      printDeclarationFunction(depth + 1, declaration);
      break;
    case AST_DECLARATION_PARAMETER:
      printDeclarationParameter(depth + 1, declaration);
      break;
    default:
      printLineWithDepth(depth + 1, "[UNKNOWN]");
      break;
  }
}

void printDeclarationVariable(int depth, AST_Declaration *declaration) {
  printLineWithDepth(depth, "[VARIABLE]");
  printId(depth + 1, declaration->id);
  printType(depth + 1, declaration->type);
}

void printDeclarationFunction(int depth, AST_Declaration *declaration) {
  printLineWithDepth(depth, "[FUNCTION]");
  printId(depth + 1, declaration->id);
  printDeclarationList(depth + 1, declaration->parameterList);
  printType(depth + 1, declaration->type);
  printBlock(depth + 1, declaration->block);
}

void printDeclarationParameter(int depth, AST_Declaration *declaration) {
  printLineWithDepth(depth, "[PARAMETER]");
  printId(depth + 1, declaration->id);
  printType(depth + 1, declaration->type);
}


void printId(int depth, char *id) {
  printLineWithDepth(depth, "[ID (%s)]", id);
}

void printBlock(int depth, AST_Block *block) {
  printLineWithDepth(depth, "[BLOCK]");
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
  printLineWithDepth(depth, "[COMMAND]");
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
      printLineWithDepth(depth + 1, "[UNKNOWN]");
      break;
  }
}

void printCommandIf(int depth, AST_CommandIf *command) {
  printLineWithDepth(depth, "[IF]");
  printExpression(depth + 1, command->expression);
  printBlock(depth + 1, command->thenBlock);
  if (command->elseBlock != NULL) {
    printBlock(depth + 1, command->elseBlock);
  }
}

void printCommandWhile(int depth, AST_CommandWhile *command) {
  printLineWithDepth(depth, "[WHILE]");
  printExpression(depth + 1, command->expression);
  printBlock(depth + 1, command->block);
}

void printCommandAssign(int depth, AST_CommandAssign *command) {
  printLineWithDepth(depth, "[ASSIGN]");
  printVariable(depth + 1, command->variable);
  printExpression(depth + 1, command->expression);
}

void printCommandReturn(int depth, AST_CommandReturn *command) {
  printLineWithDepth(depth, "[RETURN]");
  if (command->expression != NULL) {
    printExpression(depth + 1, command->expression);
  }
}
void printCommandCall(int depth, AST_CommandCall *command) {
  printCall(depth + 1, command->call);
}

void printCommandPrint(int depth, AST_CommandPrint *command) {
  printLineWithDepth(depth, "[PRINT]");
  printExpression(depth + 1, command->expression);
}

void printCommandBlock(int depth, AST_CommandBlock *command) {
  printBlock(depth + 1, command->block);
}

void printVariable(int depth, AST_Variable *variable) {
  printLineWithDepth(depth, "[VARIABLE]");
  switch (variable->variableType) {
    case AST_VARIABLE_SIMPLE:
      printId(depth + 1, variable->variable.simple->id);
      if (variable->variable.simple->declaration != NULL) {
        printDeclaration(depth + 1, variable->variable.simple->declaration);
      }
      break;
    case AST_VARIABLE_ARRAY:
      printExpression(depth + 1, variable->variable.array->outerExpression);
      printExpression(depth + 1, variable->variable.array->innerExpression);
    break;
  }
}

void printCall(int depth, AST_Call *call) {
  printLineWithDepth(depth, "[CALL]");
  printId(depth + 1, call->id);
  if (call->declaration != NULL) {
    printDeclaration(depth + 1, call->declaration);
  }
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
  printLineWithDepth(depth, "[EXPRESSION]");
  switch (expression->expressionType) {
    case AST_EXPRESSION_VARIABLE:
      printExpressionVariable(depth + 1, expression->expression.variable);
      break;
    case AST_EXPRESSION_PARENTHESES:
      printExpressionParentheses(depth + 1, expression->expression.parentheses);
      break;
    case AST_EXPRESSION_CALL:
      printExpressionCall(depth + 1, expression->expression.call);
      break;
    case AST_EXPRESSION_NEW:
      printExpressionNew(depth + 1, expression->expression.new);
      break;
    case AST_EXPRESSION_AS:
      printExpressionAs(depth + 1, expression->expression.as);
      break;
    case AST_EXPRESSION_CONSTANT:
      printExpressionConstant(depth + 1, expression->expression.constant);
      break;
    case AST_EXPRESSION_UNARY:
      printExpressionUnary(depth + 1, expression->expression.unary);
      break;
    case AST_EXPRESSION_BINARY:
      printExpressionBinary(depth + 1, expression->expression.binary);
      break;
  }
}

void printExpressionVariable(int depth, AST_ExpressionVariable *expression) {
  printVariable(depth, expression->variable);
}

void printExpressionParentheses(int depth, AST_ExpressionParentheses *expression) {
  printLineWithDepth(depth, "[PARENTHESES]");
  printExpression(depth + 1, expression->expression);
}

void printExpressionCall(int depth, AST_ExpressionCall *expression) {
  printCall(depth + 1, expression->call);
}

void printExpressionNew(int depth, AST_ExpressionNew *expression) {
  printLineWithDepth(depth, "[NEW]");
  printType(depth + 1, expression->type);
  printExpression(depth + 1, expression->expression);
}

void printExpressionAs(int depth, AST_ExpressionAs *expression) {
  printLineWithDepth(depth, "[AS]");
  printExpression(depth + 1, expression->expression);
  printType(depth + 1, expression->type);
}

void printExpressionConstant(int depth, AST_ExpressionConstant *expression) {
  printLineWithDepth(depth, "[CONSTANT]");
  switch (expression->constantType) {
    case AST_EXPRESSION_CONSTANT_INT:
      printLineWithDepth(depth + 1, "[INT (%d)]", expression->constant.i);
      break;
    case AST_EXPRESSION_CONSTANT_FLOAT:
      printLineWithDepth(depth + 1, "[FLOAT (%.2f)]", expression->constant.f);
      break;
    case AST_EXPRESSION_CONSTANT_STRING:
      printLineWithDepth(depth + 1, "[STRING (%s)]", expression->constant.s);
      break;
  }
}

void printExpressionUnary(int depth, AST_ExpressionUnary *expression) {
  printLineWithDepth(depth, "[UNARY]");
  switch (expression->unaryType) {
    case AST_EXPRESSION_UNARY_MINUS:
      printLineWithDepth(depth + 1, "[MINUS]");
      break;
    case AST_EXPRESSION_UNARY_NOT:
      printLineWithDepth(depth + 1, "[NOT]");
      break;
  }
  printExpression(depth + 1, expression->expression);
}

void printExpressionBinary(int depth, AST_ExpressionBinary *expression) {
  printLineWithDepth(depth, "[BINARY]");
  switch (expression->binaryType) {
    case AST_EXPRESSION_BINARY_MULTIPLICATION:
      printLineWithDepth(depth + 1, "[MULTIPLICATION]");
      break;
    case AST_EXPRESSION_BINARY_DIVISION:
    printLineWithDepth(depth + 1, "[DIVISION]");
      break;
    case AST_EXPRESSION_BINARY_PLUS:
    printLineWithDepth(depth + 1, "[PLUS]");
      break;
    case AST_EXPRESSION_BINARY_MINUS:
    printLineWithDepth(depth + 1, "[MINUS]");
      break;
    case AST_EXPRESSION_BINARY_LESS:
    printLineWithDepth(depth + 1, "[LESS]");
      break;
    case AST_EXPRESSION_BINARY_GREATER:
    printLineWithDepth(depth + 1, "[GREATER]");
      break;
    case AST_EXPRESSION_BINARY_LESS_EQUAL:
    printLineWithDepth(depth + 1, "[LESS_EQUAL]");
      break;
    case AST_EXPRESSION_BINARY_GREATER_EQUAL:
    printLineWithDepth(depth + 1, "[GREATER_EQUAL]");
      break;
    case AST_EXPRESSION_BINARY_EQUAL:
    printLineWithDepth(depth + 1, "[EQUAL]");
      break;
    case AST_EXPRESSION_BINARY_NOT_EQUAL:
      printLineWithDepth(depth + 1, "[NOT_EQUAL]");
      break;
    case AST_EXPRESSION_BINARY_LOGIC_AND:
      printLineWithDepth(depth + 1, "[LOGIC_AND]");
      break;
    case AST_EXPRESSION_BINARY_LOGIC_OR:
      printLineWithDepth(depth + 1, "[LOGIC_OR]");
      break;
  }
  printExpression(depth + 1, expression->leftExpression);
  printExpression(depth + 1, expression->rightExpression);
}