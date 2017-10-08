#ifndef AST_STRUCTURE_H
#define AST_STRUCTURE_H

typedef enum type AST_Type;
typedef enum declarationType AST_DeclarationType;

typedef struct program AST_Program;
typedef struct declarationElement AST_DeclarationElement;
typedef struct declaration AST_Declaration;
typedef union declarationUnion AST_DeclarationUnion;
typedef struct declarationVariable AST_DeclarationVariable;
typedef struct declarationFunction AST_DeclarationFunction;
typedef struct parameterElement AST_ParameterElement;
typedef struct parameter AST_Parameter;
typedef struct block AST_Block;
typedef struct commandElement AST_CommandElement;

enum type {
  AST_VOID,
  AST_INT,
  AST_FLOAT,
  AST_CHAR,
  AST_ARRAY_INT,
  AST_ARRAY_FLOAT,
  AST_ARRAY_CHAR
};

enum declarationType {
  AST_DECLARATION_VARIABLE,
  AST_DECLARATION_FUNCTION
};

struct program {
  AST_DeclarationElement *declarations;
};

struct declaration {
  AST_DeclarationType declarationType;
  AST_DeclarationUnion declaration;
};

struct declarationElement {
  AST_Declaration *declaration;
  AST_DeclarationElement *next;
};

union declarationUnion {
  AST_DeclarationVariable *variable;
  AST_DeclarationFunction *function;
};

struct declarationVariable {
  AST_DeclarationType declarationType;
  char *id;
  AST_Type type;
};

struct declarationFunction {
  AST_DeclarationType declarationType;
  char *id;
  AST_ParameterElement *parameterList;
  AST_Type type;
  AST_Block *block;
};

struct parameterElement {
  AST_Parameter *parameter;
  AST_ParameterElement *next;
};

struct parameter {
  char *id;
  AST_Type type;
};

struct block {
  AST_DeclarationElement *declarationVariableList;
  AST_CommandElement *commandList;
};

struct commandElement {
  int foo;
};

#endif
