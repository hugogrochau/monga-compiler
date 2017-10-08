#ifndef AST_STRUCTURE_H
#define AST_STRUCTURE_H

typedef enum type AST_Type;
typedef enum declarationType AST_DeclarationType;
typedef enum commandType AST_CommandType;

typedef struct program AST_Program;

typedef struct declarationElement AST_DeclarationElement;
typedef union declarationUnion AST_DeclarationUnion;
typedef struct declaration AST_Declaration;
typedef struct declarationVariable AST_DeclarationVariable;
typedef struct declarationFunction AST_DeclarationFunction;

typedef struct parameterElement AST_ParameterElement;
typedef struct parameter AST_Parameter;

typedef struct block AST_Block;

typedef struct commandElement AST_CommandElement;
typedef union commandUnion AST_CommandUnion;
typedef struct command AST_Command;
typedef struct commandIf AST_CommandIf;
typedef struct commandWhile AST_CommandWhile;
typedef struct commandAssign AST_CommandAssign;
typedef struct commandReturn AST_CommandReturn;
typedef struct commandCall AST_CommandCall;
typedef struct commandPrint AST_CommandPrint;
typedef struct commandBlock AST_CommandBlock;

typedef struct call AST_Call;

typedef struct expressionElement AST_ExpressionElement;
typedef struct expression AST_Expression;

typedef struct variable AST_Variable;

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

enum commandType {
  AST_COMMAND_IF,
  AST_COMMAND_WHILE,
  AST_COMMAND_ASSIGN,
  AST_COMMAND_RETURN,
  AST_COMMAND_CALL,
  AST_COMMAND_PRINT,
  AST_COMMAND_BLOCK
};

struct program {
  AST_DeclarationElement *declarations;
};

struct declarationElement {
  AST_Declaration *declaration;
  AST_DeclarationElement *next;
};

union declarationUnion {
  AST_DeclarationVariable *variable;
  AST_DeclarationFunction *function;
};

struct declaration {
  AST_DeclarationType declarationType;
  AST_DeclarationUnion declaration;
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
  AST_Command *command;
  AST_CommandElement *next;
  AST_CommandElement *previous;
};

union commandUnion {
  AST_CommandIf *commandIf;
  AST_CommandWhile *commandWhile;
  AST_CommandAssign *commandAssign;
  AST_CommandReturn *commandReturn;
  AST_CommandCall *commandCall;
  AST_CommandPrint *commandPrint;
  AST_CommandBlock *commandBlock;
};

struct command {
  AST_CommandType commandType;
  AST_CommandUnion command;
};

struct commandIf {
  AST_CommandType commandType;
  AST_Expression *expression;
  AST_Block *thenBlock;
  AST_Block *elseBlock;
};

struct commandWhile {
  AST_CommandType commandType;
  AST_Expression *expression;
  AST_Block *block;
};

struct commandAssign {
  AST_CommandType commandType;
  AST_Variable *variable;
  AST_Expression *expression;
};

struct commandReturn {
  AST_CommandType commandType;
  AST_Expression *expression;
};

struct commandCall {
  AST_CommandType commandType;
  AST_Call *call;
};

struct commandPrint {
  AST_CommandType commandType;
  AST_Expression *expression;
};

struct commandBlock {
  AST_CommandType commandType;
  AST_Block *block;
};

struct call {
  char *id;
  AST_ExpressionElement *expressionList;
};

struct expressionElement {
  AST_Expression *expression;
  AST_ExpressionElement *next;
};

struct expression {
  int foo;
};

struct variable {
  int foo;
};

#endif
