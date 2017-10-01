#ifndef AST_STRUCTURE_H
#define AST_STRUCTURE_H

typedef enum type {
  AST_VOID,
  AST_INT,
  AST_FLOAT,
  AST_CHAR,
  AST_ARRAY_INT,
  AST_ARRAY_FLOAT,
  AST_ARRAY_CHAR
} AST_Type;

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

typedef union declarationUnion {
  AST_DeclarationVariable *variable;
  AST_DeclarationFunction *function;
} AST_DeclarationUnion;

typedef struct declaration {
  AST_DeclarationType type;
  AST_DeclarationUnion declaration;
} AST_Declaration;

typedef struct declarationElement {
  AST_Declaration *declaration;
  struct declarationElement *next;
} AST_DeclarationElement;

typedef struct program {
  AST_DeclarationElement *declarations;
} AST_Program;

#endif
