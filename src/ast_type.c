#include <stdio.h>

#include "ast_type.h"
#include "util.h"
#include "ast_enum_strings.h"

void typeDeclarations(AST_DeclarationElement *declarations);
void typeBlock(AST_Block *block);
void typeCommands(AST_CommandElement *commands);
AST_Type typeCall(AST_Call *call);
void typeExpression(AST_Expression *expression);
AST_Type typeVariable(AST_Variable *variable, AST_Type type);
AST_Type getConstantType(AST_ExpressionConstant *constant);
AST_Type getArrayElementType(AST_Type type);

void AST_type (AST_Program *program) {
  typeDeclarations(program->declarations);
}

void typeDeclarations(AST_DeclarationElement *declarations) {
  AST_DeclarationElement *currentDeclaration = declarations;

  while (currentDeclaration != NULL) {
    switch (currentDeclaration->declaration->declarationType) {
      case AST_DECLARATION_FUNCTION:
        typeBlock(currentDeclaration->declaration->block);
        break;
      case AST_DECLARATION_VARIABLE:
        break;
      default:
        error("Unknown declaration type");
    }
    currentDeclaration = currentDeclaration->next;
  }
}

void typeBlock(AST_Block *block) {
  typeCommands(block->commandList);
}

void typeCommands(AST_CommandElement *commands) {
  AST_CommandElement *currentCommand = commands;

  while (currentCommand != NULL) {
    switch (currentCommand->command->commandType) {
      case AST_COMMAND_IF:
        typeExpression(currentCommand->command->command.commandIf->expression);
        typeBlock(currentCommand->command->command.commandIf->thenBlock);
        if (currentCommand->command->command.commandIf->elseBlock) {
          typeBlock(currentCommand->command->command.commandIf->elseBlock);
        }
        break;
      case AST_COMMAND_WHILE:
        typeExpression(currentCommand->command->command.commandWhile->expression);
        typeBlock(currentCommand->command->command.commandWhile->block);
        break;
      case AST_COMMAND_ASSIGN:
        typeExpression(currentCommand->command->command.commandAssign->expression);
        typeVariable(
          currentCommand->command->command.commandAssign->variable,
          currentCommand->command->command.commandAssign->expression->type
        );
        break;
      case AST_COMMAND_RETURN:
        typeExpression(currentCommand->command->command.commandReturn->expression);
        break;
      case AST_COMMAND_CALL:
        typeCall(currentCommand->command->command.commandCall->call);
        break;
      case AST_COMMAND_PRINT:
        typeExpression(currentCommand->command->command.commandPrint->expression);
        break;
      case AST_COMMAND_BLOCK:
        typeBlock(currentCommand->command->command.commandBlock->block);
        break;
      default:
        error("Unknown command type");
      }
      currentCommand = currentCommand->next;
  }
}

AST_Type typeCall(AST_Call *call) {
  AST_ExpressionElement *currentParameterExpression = call->expressionList;
  AST_DeclarationElement *currentParameterDeclaration = call->declaration->parameterList;
  int parameterNumber = 1;

  while (currentParameterExpression != NULL) {
    typeExpression(currentParameterExpression->expression);
    if (currentParameterExpression->expression->type != currentParameterDeclaration->declaration->type) {
      error("Wrong type (%s) for parameter (%d) of function (%s)",
        AST_TypeNames[currentParameterExpression->expression->type],
        parameterNumber,
        call->declaration->id
      );
    }
    currentParameterExpression = currentParameterExpression->next;
    currentParameterDeclaration = currentParameterDeclaration->next;
    ++parameterNumber;
  }

  return call->declaration->type;
}

void typeExpression(AST_Expression *expression) {
  switch(expression->expressionType) {
  case AST_EXPRESSION_VARIABLE:
    expression->type = typeVariable(expression->expression.variable->variable, -1);
    break;
  case AST_EXPRESSION_CALL:
    expression->type = typeCall(expression->expression.call->call);
    break;
  case AST_EXPRESSION_NEW:
    typeExpression(expression->expression.new->expression);
    expression->type = expression->expression.new->expression->type;
    break;
  case AST_EXPRESSION_AS:
    typeExpression(expression->expression.as->expression);
    expression->type = expression->expression.as->type;
    break;
  case AST_EXPRESSION_CONSTANT:
    expression->type = getConstantType(expression->expression.constant);
    break;
  case AST_EXPRESSION_UNARY:
    typeExpression(expression->expression.unary->expression);
    switch (expression->expression.unary->unaryType) {
      case AST_EXPRESSION_UNARY_MINUS:
        expression->type = expression->expression.unary->expression->type;
        break;
      case AST_EXPRESSION_UNARY_NOT:
        expression->type = AST_INT;
        break;
    }
    break;
  case AST_EXPRESSION_BINARY:
    typeExpression(expression->expression.binary->leftExpression);
    typeExpression(expression->expression.binary->rightExpression);
    // TODO: type casting
    if (expression->expression.binary->leftExpression->type != expression->expression.binary->rightExpression->type) {
      error("Invalid types for binary expression: (%s) and (%s)",
        AST_TypeNames[expression->expression.binary->leftExpression->type],
        AST_TypeNames[expression->expression.binary->rightExpression->type]
      );
    }
    switch (expression->expression.binary->binaryType) {
      case AST_EXPRESSION_BINARY_MULTIPLICATION:
      case AST_EXPRESSION_BINARY_DIVISION:
      case AST_EXPRESSION_BINARY_PLUS:
      case AST_EXPRESSION_BINARY_MINUS:
        expression->type = expression->expression.binary->leftExpression->type;
      break;
      default:
        expression->type = AST_INT;
    }
    break;
  }
}

AST_Type typeVariable(AST_Variable *variable, AST_Type type) {
  switch (variable->variableType) {
    case AST_VARIABLE_ARRAY:
      typeExpression(variable->variable.array->innerExpression);
      typeExpression(variable->variable.array->outerExpression);
      return getArrayElementType(variable->variable.array->outerExpression->type);
    break;
    case AST_VARIABLE_SIMPLE:
      if (type != -1 && variable->variable.simple->declaration->type != type) {
        error("Variable (%s) of type (%s) cannot be set to type (%s)",
          variable->variable.simple->id,
          AST_TypeNames[variable->variable.simple->declaration->type],
          AST_TypeNames[type]
        );
      }
      return variable->variable.simple->declaration->type;
    break;
    default:
      error("Unknown variable type");
      return -1;
  }
}

AST_Type getArrayElementType(AST_Type type) {
  switch (type) {
    case AST_ARRAY_INT:
      return AST_INT;
    case AST_ARRAY_FLOAT:
      return AST_FLOAT;
    case AST_ARRAY_CHAR:
      return AST_CHAR;
    default:
      error("Unknown array type");
      return -1;
  }
}

AST_Type getConstantType(AST_ExpressionConstant *constant) {
  switch (constant->constantType) {
    case AST_EXPRESSION_CONSTANT_FLOAT:
      return AST_FLOAT;
    case AST_EXPRESSION_CONSTANT_INT:
      return AST_INT;
    case AST_EXPRESSION_CONSTANT_STRING:
      return AST_ARRAY_CHAR;
    default:
      error("Unknown expression constant type");
      return -1;
  }
}