#ifndef AST_CREATION_H
#define AST_CREATION_H

#include "ast_structure.h"

AST_Program * AST_createProgram(AST_DeclarationElement *declarationList);

AST_DeclarationElement * AST_createDeclarationList(AST_Declaration *declaration);

AST_DeclarationElement * AST_appendDeclaration(AST_DeclarationElement *declarationList, AST_Declaration *declaration);

AST_Declaration * AST_createDeclarationAsVariable(AST_DeclarationVariable *declaration);

AST_Declaration * AST_createDeclarationAsFunction(AST_DeclarationFunction *declaration);

AST_DeclarationVariable * AST_createDeclarationVariable(char *id, AST_Type type);

AST_Type AST_createArrayType(AST_Type type);

AST_DeclarationFunction * AST_createDeclarationFunction(char * id, AST_ParameterElement *parameterList, AST_Type type, AST_Block *block);

AST_ParameterElement * AST_createParameterList(AST_Parameter *parameter);

AST_ParameterElement * AST_appendParameter(AST_ParameterElement *parameterList, AST_Parameter *parameter);

AST_Parameter * AST_createParameter(char *id, AST_Type type);

AST_Block * AST_createBlock(AST_DeclarationElement *declarationVariableList, AST_CommandElement *commandList);

AST_DeclarationElement * AST_createDeclarationVariableList(AST_DeclarationVariable *declarationVariable);

AST_DeclarationElement * AST_appendDeclarationVariableList(AST_DeclarationElement* declarationVariableList, AST_DeclarationVariable *declarationVariable);

#endif