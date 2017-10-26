#include <stdio.h>
#include "ast_knit.h"
#include "symbol_table.h"

void handleBlock(AST_Block *block);

void handleDeclarations(AST_DeclarationElement *declarations);

void saveDeclarations(AST_Declaration *declaration);

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

  ST_print(scopeStack);
}

void handleDeclarations(AST_DeclarationElement *declarations) {
  AST_DeclarationElement *currentDeclaration = declarations;

  while (currentDeclaration != NULL) {
    saveDeclarations(currentDeclaration->declaration);
    currentDeclaration = currentDeclaration->next;
  }

  currentDeclaration = declarations;

  while (currentDeclaration != NULL) {
    if (currentDeclaration->declaration->declarationType == AST_DECLARATION_FUNCTION) {
      handleBlock(currentDeclaration->declaration->declaration.function->block);
    }
    currentDeclaration = currentDeclaration->next;
  }
}

void saveDeclarations(AST_Declaration *declaration) {
  switch (declaration->declarationType) {
    case AST_DECLARATION_FUNCTION:
      ST_addSymbol(scopeStack, declaration->declaration.function->id, declaration);
      break;
    case AST_DECLARATION_VARIABLE:
      ST_addSymbol(scopeStack, declaration->declaration.variable->id, declaration);
      break;
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
    AST_COMMAND_IF:
      handleExpression(command->command.commandIf->expression);
      handleBlock(command->command.commandIf->thenBlock);
      if (command->command.commandIf->elseBlock) {
        handleBlock(command->command.commandIf->elseBlock);
      }
      break;
    AST_COMMAND_WHILE:
      handleExpression(command->command.commandWhile->expression);
      handleBlock(command->command.commandWhile->block);
      break;
    AST_COMMAND_ASSIGN:
      handleVariable(command->command.commandAssign->variable);
      handleExpression(command->command.commandAssign->expression);
      break;
    AST_COMMAND_RETURN:
      handleExpression(command->command.commandReturn->expression);
      break;
    AST_COMMAND_CALL:
      handleCall(command->command.commandCall->call);
      break;
    AST_COMMAND_PRINT:
      handleExpression(command->command.commandPrint->expression);
      break;
    AST_COMMAND_BLOCK:
      handleBlock(command->command.commandBlock->block);
      break;
  }
}

void handleExpression(AST_Expression *expression) {
  switch (expression->expressionType) {
    AST_EXPRESSION_VARIABLE:
      handleVariable(expression->expression.variable->variable);
      break;
    AST_EXPRESSION_PARENTHESES:
      handleExpression(expression->expression.parentheses->expression);
      break;
    AST_EXPRESSION_CALL:
      handleCall(expression->expression.call->call);
      break;
    AST_EXPRESSION_NEW:
      handleExpression(expression->expression.new->expression);
      break;
    AST_EXPRESSION_AS:
      handleExpression(expression->expression.as->expression);
      break;
    AST_EXPRESSION_UNARY:
      handleExpression(expression->expression.unary->expression);
      break;
    AST_EXPRESSION_BINARY:
      handleExpression(expression->expression.binary->leftExpression);
      handleExpression(expression->expression.binary->rightExpression);
      break;
  }
}

void handleVariable(AST_Variable *variable) {
  if (variable->variableType == AST_VARIABLE_SIMPLE) {
    AST_Declaration *declaration = ST_findDeclaration(scopeStack, variable->variable.simple->id);
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
