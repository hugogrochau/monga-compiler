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

#endif