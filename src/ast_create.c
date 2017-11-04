#include <stdlib.h>

#include "ast_create.h"
#include "util.h"

AST_Program * AST_createProgram(AST_DeclarationElement *declarationList) {
  AST_Program *program = safeMalloc(sizeof(AST_Program));

  program->declarations = declarationList;

  return program;
}

AST_DeclarationElement * AST_createDeclarationList(AST_Declaration *declaration) {
  AST_DeclarationElement *declarationList = safeMalloc(sizeof(AST_DeclarationElement));

  declarationList->declaration = declaration;
  declarationList->next = NULL;

  return declarationList;
}

AST_DeclarationElement * AST_appendDeclaration(AST_DeclarationElement *declarationList, AST_Declaration *declaration) {
  AST_DeclarationElement *declarationElement = safeMalloc(sizeof(AST_DeclarationElement));
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

AST_Declaration * AST_createDeclarationFunction(char * id, AST_DeclarationElement *parameterList, AST_Type type, AST_Block *block) {
  AST_Declaration *declaration = safeMalloc(sizeof(AST_Declaration));

  declaration->declarationType = AST_DECLARATION_FUNCTION;
  declaration->id = id;
  declaration->parameterList = parameterList;
  declaration->type = type;
  declaration->block = block;

  return declaration;
}

AST_Declaration * AST_createDeclarationParameter(char *id, AST_Type type) {
  AST_Declaration *declaration = safeMalloc(sizeof(AST_Declaration));

  declaration->declarationType = AST_DECLARATION_PARAMETER;
  declaration->id = id;
  declaration->type = type;

  return declaration;
}

AST_Declaration * AST_createDeclarationVariable(char *id, AST_Type type) {
  AST_Declaration *declaration = safeMalloc(sizeof(AST_Declaration));

  declaration->declarationType = AST_DECLARATION_VARIABLE;
  declaration->id = id;
  declaration->type = type;

  return declaration;
}

AST_Type AST_createArrayType(AST_Type type) {
  switch (type) {
    case AST_INT:
      return AST_ARRAY_INT;
    case AST_FLOAT:
      return AST_ARRAY_FLOAT;
    case AST_CHAR:
      return AST_ARRAY_CHAR;
    default:
      return type;
  }
}

AST_Block * AST_createBlock(AST_DeclarationElement *declarationVariableList, AST_CommandElement *commandList) {
  AST_Block *block = safeMalloc(sizeof(AST_Block));

  block->declarationVariableList = declarationVariableList;
  block->commandList = commandList;

  return block;
}

AST_CommandElement * AST_createCommandList(AST_Command *command) {
  AST_CommandElement *commandElement = safeMalloc(sizeof(AST_CommandElement));

  commandElement->command = command;
  commandElement->next = NULL;
  commandElement->prev = NULL;

  return commandElement;
}

AST_CommandElement * AST_appendCommand(AST_CommandElement *commandList, AST_Command *command) {
  AST_CommandElement *commandElement = safeMalloc(sizeof(AST_CommandElement));
  AST_CommandElement *currentElement = commandList;

  commandElement->command = command;
  commandElement->next = currentElement;

  return commandElement;
}

AST_Command * AST_createCommandIf(AST_Expression *expression, AST_Block *thenBlock) {
  AST_CommandIf *commandIf = safeMalloc(sizeof(AST_CommandIf));
  AST_Command *command = safeMalloc(sizeof(AST_Command));

  commandIf->commandType = AST_COMMAND_IF;
  commandIf->expression = expression;
  commandIf->thenBlock = thenBlock;
  commandIf->elseBlock = NULL;

  command->commandType = AST_COMMAND_IF;
  command->command.commandIf = commandIf;

  return command;
}

AST_Command * AST_createCommandIfElse(AST_Expression *expression, AST_Block *thenBlock, AST_Block *elseBlock) {
  AST_CommandIf *commandIf = safeMalloc(sizeof(AST_CommandIf));
  AST_Command *command = safeMalloc(sizeof(AST_Command));

  commandIf->commandType = AST_COMMAND_IF;
  commandIf->expression = expression;
  commandIf->thenBlock = thenBlock;
  commandIf->elseBlock = elseBlock;

  command->commandType = AST_COMMAND_IF;
  command->command.commandIf = commandIf;

  return command;
}

AST_Command * AST_createCommandWhile(AST_Expression *expression, AST_Block *block) {
  AST_CommandWhile *commandWhile = safeMalloc(sizeof(AST_CommandWhile));
  AST_Command *command = safeMalloc(sizeof(AST_Command));

  commandWhile->commandType = AST_COMMAND_WHILE;
  commandWhile->expression = expression;
  commandWhile->block = block;

  command->commandType = AST_COMMAND_WHILE;
  command->command.commandWhile = commandWhile;

  return command;
}

AST_Command * AST_createCommandAssign(AST_Variable *variable, AST_Expression *expression) {
  AST_CommandAssign *commandAssign = safeMalloc(sizeof(AST_CommandAssign));
  AST_Command *command = safeMalloc(sizeof(AST_Command));

  commandAssign->commandType = AST_COMMAND_ASSIGN;
  commandAssign->variable = variable;
  commandAssign->expression = expression;

  command->commandType = AST_COMMAND_ASSIGN;
  command->command.commandAssign = commandAssign;

  return command;
}

AST_Command * AST_createCommandReturnEmpty() {
  AST_CommandReturn *commandReturn = safeMalloc(sizeof(AST_CommandReturn));
  AST_Command *command = safeMalloc(sizeof(AST_Command));

  commandReturn->commandType = AST_COMMAND_RETURN;
  commandReturn->expression = NULL;

  command->commandType = AST_COMMAND_RETURN;
  command->command.commandReturn = commandReturn;

  return command;

}

AST_Command * AST_createCommandReturn(AST_Expression *expression) {
  AST_CommandReturn *commandReturn = safeMalloc(sizeof(AST_CommandReturn));
  AST_Command *command = safeMalloc(sizeof(AST_Command));

  commandReturn->commandType = AST_COMMAND_RETURN;
  commandReturn->expression = expression;

  command->commandType = AST_COMMAND_RETURN;
  command->command.commandReturn = commandReturn;

  return command;
}

AST_Command * AST_createCommandCall(AST_Call *call) {
  AST_CommandCall *commandCall = safeMalloc(sizeof(AST_CommandCall));
  AST_Command *command = safeMalloc(sizeof(AST_Command));

  commandCall->commandType = AST_COMMAND_CALL;
  commandCall->call = call;

  command->commandType = AST_COMMAND_CALL;
  command->command.commandCall = commandCall;

  return command;
}

AST_Command * AST_createCommandPrint(AST_Expression *expression) {
  AST_CommandPrint *commandPrint = safeMalloc(sizeof(AST_CommandPrint));
  AST_Command *command = safeMalloc(sizeof(AST_Command));

  commandPrint->commandType = AST_COMMAND_PRINT;
  commandPrint->expression = expression;

  command->commandType = AST_COMMAND_PRINT;
  command->command.commandPrint = commandPrint;

  return command;
}

AST_Command * AST_createCommandBlock(AST_Block *block) {
  AST_CommandBlock *commandBlock = safeMalloc(sizeof(AST_CommandBlock));
  AST_Command *command = safeMalloc(sizeof(AST_Command));

  commandBlock->commandType = AST_COMMAND_BLOCK;
  commandBlock->block = block;

  command->commandType = AST_COMMAND_BLOCK;
  command->command.commandBlock = commandBlock;

  return command;
}

AST_Variable * AST_createVariableSimple(char *id) {
  AST_Variable *variable = safeMalloc(sizeof(AST_Variable));
  AST_VariableSimple *variableSimple = safeMalloc(sizeof(AST_VariableSimple));

  variableSimple->variableType = AST_VARIABLE_SIMPLE;
  variableSimple->id = id;

  variable->variableType = AST_VARIABLE_SIMPLE;
  variable->variable.simple = variableSimple;

  return variable;
}

AST_Variable * AST_createVariableArray(AST_Expression *outerExpression, AST_Expression *innerExpression) {
  AST_Variable *variable = safeMalloc(sizeof(AST_Variable));
  AST_VariableArray *variableArray = safeMalloc(sizeof(AST_VariableArray));

  variableArray->variableType = AST_VARIABLE_ARRAY;
  variableArray->outerExpression = outerExpression;
  variableArray->innerExpression = innerExpression;

  variable->variableType = AST_VARIABLE_ARRAY;
  variable->variable.array = variableArray;

  return variable;
}

AST_Call * AST_createCall(char *id, AST_ExpressionElement *expressionList) {
  AST_Call *call = safeMalloc(sizeof(AST_Call));

  call->id = id;
  call->expressionList = expressionList;

  return call;
}

AST_ExpressionElement * AST_createExpressionList(AST_Expression *expression) {
  AST_ExpressionElement *expressionList = safeMalloc(sizeof(AST_ExpressionElement));

  expressionList->expression = expression;
  expressionList->next = NULL;

  return expressionList;
}

AST_ExpressionElement * AST_appendExpression(AST_ExpressionElement *expressionList, AST_Expression* expression) {
  AST_ExpressionElement *expressionElement = safeMalloc(sizeof(AST_ExpressionElement));
  AST_ExpressionElement *currentElement = expressionList;

  /* Go to the end of the linked list */
  while (currentElement->next != NULL) {
    currentElement = currentElement->next;
  }

  expressionElement->expression = expression;
  expressionElement->next = NULL;

  currentElement->next = expressionElement;

  return expressionList;
}

AST_Expression * AST_createExpressionVariable(AST_Variable *variable) {
  AST_Expression *expression = safeMalloc(sizeof(AST_Expression));
  AST_ExpressionVariable *expressionVariable = safeMalloc(sizeof(AST_ExpressionVariable));

  expressionVariable->expressionType = AST_EXPRESSION_VARIABLE;
  expressionVariable->variable = variable;

  expression->expressionType = AST_EXPRESSION_VARIABLE;
  expression->expression.variable = expressionVariable;

  return expression;
}

AST_Expression * AST_createExpressionParentheses(AST_Expression *expression) {
  AST_Expression *newExpression = safeMalloc(sizeof(AST_Expression));
  AST_ExpressionParentheses *expressionParentheses = safeMalloc(sizeof(AST_ExpressionParentheses));

  expressionParentheses->expressionType = AST_EXPRESSION_PARENTHESES;
  expressionParentheses->expression = expression;

  newExpression->expressionType = AST_EXPRESSION_PARENTHESES;
  newExpression->expression.parentheses = expressionParentheses;

  return newExpression;
}

AST_Expression * AST_createExpressionCall(AST_Call *call) {
  AST_Expression *expression = safeMalloc(sizeof(AST_Expression));
  AST_ExpressionCall *expressionCall = safeMalloc(sizeof(AST_ExpressionCall));

  expressionCall->expressionType = AST_EXPRESSION_CALL;
  expressionCall->call = call;

  expression->expressionType = AST_EXPRESSION_CALL;
  expression->expression.call = expressionCall;

  return expression;
}

AST_Expression * AST_createExpressionNew(AST_Type type, AST_Expression *expression) {
  AST_Expression *newExpression = safeMalloc(sizeof(AST_Expression));
  AST_ExpressionNew *expressionNew = safeMalloc(sizeof(AST_ExpressionNew));

  expressionNew->expressionType = AST_EXPRESSION_NEW;
  expressionNew->type = type;
  expressionNew->expression = expression;

  newExpression->expressionType = AST_EXPRESSION_NEW;
  newExpression->expression.new = expressionNew;

  return newExpression;
}

AST_Expression * AST_createExpressionAs(AST_Expression *expression, AST_Type type) {
  AST_Expression *newExpression = safeMalloc(sizeof(AST_Expression));
  AST_ExpressionAs *expressionAs = safeMalloc(sizeof(AST_ExpressionAs));

  expressionAs->expressionType = AST_EXPRESSION_AS;
  expressionAs->expression = expression;
  expressionAs->type = type;

  newExpression->expressionType = AST_EXPRESSION_AS;
  newExpression->expression.as = expressionAs;

  return newExpression;
}

AST_Expression * AST_createExpressionConstant(AST_ExpressionConstantUnion constantUnion, AST_ExpressionConstantType constantType) {
  AST_Expression *expression = safeMalloc(sizeof(AST_Expression));
  AST_ExpressionConstant *expressionConstant = safeMalloc(sizeof(AST_ExpressionConstant));

  expressionConstant->expressionType = AST_EXPRESSION_CONSTANT;
  expressionConstant->constantType = constantType;
  expressionConstant->constant = constantUnion;

  expression->expressionType = AST_EXPRESSION_CONSTANT;
  expression->expression.constant = expressionConstant;

  return expression;
}

AST_Expression * AST_createExpressionIntConstant(int constant) {
  AST_ExpressionConstantUnion constantUnion;

  constantUnion.i = constant;

  return AST_createExpressionConstant(constantUnion, AST_EXPRESSION_CONSTANT_INT);
}

AST_Expression * AST_createExpressionFloatConstant(float constant) {
  AST_ExpressionConstantUnion constantUnion;

  constantUnion.f = constant;

  return AST_createExpressionConstant(constantUnion, AST_EXPRESSION_CONSTANT_FLOAT);
}

AST_Expression * AST_createExpressionStringConstant(char *constant) {
  AST_ExpressionConstantUnion constantUnion;

  constantUnion.s = constant;

  return AST_createExpressionConstant(constantUnion, AST_EXPRESSION_CONSTANT_STRING);
}

AST_Expression * AST_createExpressionUnary(AST_Expression *expression, AST_ExpressionUnaryType unaryType) {
  AST_Expression *newExpression = safeMalloc(sizeof(AST_Expression));
  AST_ExpressionUnary *expressionUnary = safeMalloc(sizeof(AST_ExpressionUnary));

  expressionUnary->expressionType = AST_EXPRESSION_UNARY;
  expressionUnary->unaryType = unaryType;
  expressionUnary->expression = expression;

  newExpression->expressionType = AST_EXPRESSION_UNARY;
  newExpression->expression.unary = expressionUnary;

  return newExpression;
}

AST_Expression * AST_createExpressionBinary(AST_Expression *leftExpression, AST_Expression *rightExpression, AST_ExpressionBinaryType binaryType) {

  AST_Expression *expression = safeMalloc(sizeof(AST_Expression));
  AST_ExpressionBinary *expressionBinary = safeMalloc(sizeof(AST_ExpressionBinary));

  expressionBinary->expressionType = AST_EXPRESSION_BINARY;
  expressionBinary->binaryType = binaryType;
  expressionBinary->leftExpression = leftExpression;
  expressionBinary->rightExpression = rightExpression;

  expression->expressionType = AST_EXPRESSION_BINARY;
  expression->expression.binary = expressionBinary;

  return expression;
}
