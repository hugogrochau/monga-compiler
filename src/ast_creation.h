#ifndef AST_CREATION_H
#define AST_CREATION_H

#include "ast_structure.h"

AST_Program * AST_createProgram(AST_DeclarationElement *declarationList);

AST_DeclarationElement * AST_createDeclarationList(AST_Declaration *declaration);

AST_DeclarationElement * AST_appendDeclaration(AST_DeclarationElement *declarationList, AST_Declaration *declaration);

AST_Declaration * AST_createDeclarationVariable(AST_DeclarationVariable *declaration);

AST_Declaration * AST_createDeclarationFunction(AST_DeclarationFunction *declaration);

#endif