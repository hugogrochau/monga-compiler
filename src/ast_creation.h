#ifndef AST_CREATION_H
#define AST_CREATION_H

#include "ast_structure.h"

AST_Program * appendDeclarationOrCreateProgram(AST_Program *program, AST_DeclarationElement *head);

#endif