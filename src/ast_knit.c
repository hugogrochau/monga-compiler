#include <stdio.h>

#include "util.h"
#include "ast_knit.h"
#include "symbol_table.h"

void handleBlock(AST_Block *block);

void handleDeclarations(AST_DeclarationElement *declarations);

void handleCommands(AST_CommandElement *commands);

void handleCommand(AST_Command *command);

void handleExpression(AST_Expression *expression);

void handleVariable(AST_Variable *variable);

void handleCall (AST_Call *call);

ST_ScopeElement *scopeStack;

void AST_knit (AST_Program *program) {
  scopeStack = ST_initScopeStack();
  ST_enterScope(scopeStack);

  handleDeclarations(program->declarations);
}

void handleDeclarations(AST_DeclarationElement *declarations) {
  AST_DeclarationElement *currentDeclaration = declarations;

  // Save declarations to symbol table
  while (currentDeclaration != NULL) {
    ST_addSymbol(scopeStack, currentDeclaration->declaration);
    currentDeclaration = currentDeclaration->next;
  }

  // Go to start of declarations again
  currentDeclaration = declarations;

  // Treat function declarations
  while (currentDeclaration != NULL) {
    if (currentDeclaration->declaration->declarationType == AST_DECLARATION_FUNCTION) {
      handleDeclarations(currentDeclaration->declaration->parameterList);
      handleBlock(currentDeclaration->declaration->block);
    }
    currentDeclaration = currentDeclaration->next;
  }
}

void handleBlock(AST_Block *block) {
  scopeStack = ST_enterScope(scopeStack);
  handleDeclarations(block->declarationVariableList);
  handleCommands(block->commandList);
}

void handleCommands(AST_CommandElement *commands) {
  AST_CommandElement *currentCommand = commands;

  while (currentCommand != NULL) {
    handleCommand(currentCommand->command);
    currentCommand = currentCommand->next;
  }
}

void handleCommand(AST_Command *command) {
  switch (command->commandType) {
    case AST_COMMAND_IF:
      handleExpression(command->command.commandIf->expression);
      handleBlock(command->command.commandIf->thenBlock);
      if (command->command.commandIf->elseBlock) {
        handleBlock(command->command.commandIf->elseBlock);
      }
      break;
    case AST_COMMAND_WHILE:
      handleExpression(command->command.commandWhile->expression);
      handleBlock(command->command.commandWhile->block);
      break;
    case AST_COMMAND_ASSIGN:
      handleVariable(command->command.commandAssign->variable);
      handleExpression(command->command.commandAssign->expression);
      break;
    case AST_COMMAND_RETURN:
      handleExpression(command->command.commandReturn->expression);
      break;
    case AST_COMMAND_CALL:
      handleCall(command->command.commandCall->call);
      break;
    case AST_COMMAND_PRINT:
      handleExpression(command->command.commandPrint->expression);
      break;
    case AST_COMMAND_BLOCK:
      handleBlock(command->command.commandBlock->block);
      break;
    default:
      error("Unknown command");
      break;
  }
}

void handleExpression(AST_Expression *expression) {
  switch (expression->expressionType) {
    case AST_EXPRESSION_VARIABLE:
      handleVariable(expression->expression.variable->variable);
      break;
    case AST_EXPRESSION_CALL:
      handleCall(expression->expression.call->call);
      break;
    case AST_EXPRESSION_NEW:
      handleExpression(expression->expression.new->expression);
      break;
    case AST_EXPRESSION_AS:
      handleExpression(expression->expression.as->expression);
      break;
    case AST_EXPRESSION_UNARY:
      handleExpression(expression->expression.unary->expression);
      break;
    case AST_EXPRESSION_BINARY:
      handleExpression(expression->expression.binary->leftExpression);
      handleExpression(expression->expression.binary->rightExpression);
      break;
    case AST_EXPRESSION_CONSTANT:
      break;
    default:
      error("Unknown expression");
      break;
  }
}

void handleVariable(AST_Variable *variable) {
  if (variable->variableType == AST_VARIABLE_SIMPLE) {
    char *variableId = variable->variable.simple->id;
    AST_Declaration *declaration = ST_findDeclaration(scopeStack, variableId);
    if (declaration == NULL) {
      error("Unknown variable %s", variableId);
    }
    variable->variable.simple->declaration = declaration;
  } else if (variable->variableType == AST_VARIABLE_ARRAY) {
    handleExpression(variable->variable.array->outerExpression);
    handleExpression(variable->variable.array->innerExpression);
  }
}

void handleCall(AST_Call *call) {
  AST_Declaration *declaration = ST_findDeclaration(scopeStack, call->id);
  call->declaration = declaration;
}
