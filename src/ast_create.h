#ifndef AST_CREATE_H
#define AST_CREATE_H

#include "ast_structure.h"

AST_Program * AST_createProgram(AST_DeclarationElement *declarationList);

AST_DeclarationElement * AST_createDeclarationList(AST_Declaration *declaration);

AST_DeclarationElement * AST_appendDeclaration(AST_DeclarationElement *declarationList, AST_Declaration *declaration);

AST_Declaration * AST_createDeclarationFunction(char * id, AST_DeclarationElement *parameterList, AST_Type type, AST_Block *block);

AST_Declaration * AST_createDeclarationParameter(char *id, AST_Type type);

AST_Declaration * AST_createDeclarationVariable(char *id, AST_Type type);

AST_Type AST_createArrayType(AST_Type type);

AST_Block * AST_createBlock(AST_DeclarationElement *declarationVariableList, AST_CommandElement *commandList);

AST_CommandElement * AST_createCommandList(AST_Command *command);

AST_CommandElement * AST_appendCommand(AST_CommandElement *commandList, AST_Command *command);

AST_Command * AST_createCommandIf(AST_Expression *expression, AST_Block *thenBlock);

AST_Command * AST_createCommandIfElse(AST_Expression *expression, AST_Block *thenBlock, AST_Block *elseBlock);

AST_Command * AST_createCommandWhile(AST_Expression *expression, AST_Block *block);

AST_Command * AST_createCommandAssign(AST_Variable *variable, AST_Expression *expression);

AST_Command * AST_createCommandReturnEmpty();

AST_Command * AST_createCommandReturn(AST_Expression *expression);

AST_Command * AST_createCommandCall(AST_Call *call);

AST_Command * AST_createCommandPrint(AST_Expression *expression);

AST_Command * AST_createCommandBlock(AST_Block *block);

AST_Variable * AST_createVariableSimple(char *id);

AST_Variable * AST_createVariableArray(AST_Expression *outerExpression, AST_Expression *innerExpression);

AST_Call * AST_createCall(char *id, AST_ExpressionElement *expressionList);

AST_ExpressionElement * AST_createExpressionList(AST_Expression *expression);

AST_ExpressionElement * AST_appendExpression(AST_ExpressionElement *expressionList, AST_Expression* expression);

AST_Expression * AST_createExpressionVariable(AST_Variable *variable);

AST_Expression * AST_createExpressionParentheses(AST_Expression *expression);

AST_Expression * AST_createExpressionCall(AST_Call *call);

AST_Expression * AST_createExpressionNew(AST_Type type, AST_Expression *expression);

AST_Expression * AST_createExpressionAs(AST_Expression *expression, AST_Type type);

AST_Expression * AST_createExpressionConstant(AST_ExpressionConstantUnion constantUnion, AST_ExpressionConstantType constantType);

AST_Expression * AST_createExpressionIntConstant(int constant);

AST_Expression * AST_createExpressionFloatConstant(float constant);

AST_Expression * AST_createExpressionStringConstant(char *constant);

AST_Expression * AST_createExpressionUnary(AST_Expression *expression, AST_ExpressionUnaryType unaryType);

AST_Expression * AST_createExpressionBinary(AST_Expression *leftExpression, AST_Expression *rightExpression, AST_ExpressionBinaryType binaryType);

#endif