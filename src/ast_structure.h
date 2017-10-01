#ifndef AST_STRUCTURE_H
#define AST_STRUCTURE_H

typedef enum declarationType {
  AST_DECLARATION_VARIABLE,
  AST_DECLARATION_FUNCTION
} AST_DeclarationType;

typedef struct declarationVariable {
  AST_DeclarationType type;
  char *id;
} AST_DeclarationVariable;

typedef struct declarationFunction {
  AST_DeclarationType type;
  char *id;
} AST_DeclarationFunction;

typedef struct declaration {
  AST_DeclarationType type;
  union {
    AST_DeclarationVariable *variable;
    AST_DeclarationFunction *function;
  } declaration;
} AST_Declaration;

typedef struct declarationElement {
  AST_Declaration *declaration;
  struct declarationElement *next;
} AST_DeclarationElement;

typedef struct program {
  AST_DeclarationElement *declarations;
} AST_Program;

#endif
