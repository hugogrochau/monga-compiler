#ifndef AST_STRUCTURE_H
#define AST_STRUCTURE_H

typedef enum type AST_Type;
typedef enum declarationType AST_DeclarationType;
typedef enum variableType AST_VariableType;
typedef enum commandType AST_CommandType;
typedef enum expressionType AST_ExpressionType;
typedef enum expressionConstantType AST_ExpressionConstantType;
typedef enum expressionUnaryType AST_ExpressionUnaryType;
typedef enum expressionBinaryType AST_ExpressionBinaryType;

typedef struct program AST_Program;

typedef struct declarationElement AST_DeclarationElement;
typedef struct declaration AST_Declaration;

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

typedef union variableUnion AST_VariableUnion;
typedef struct variable AST_Variable;
typedef struct variableSimple AST_VariableSimple;
typedef struct variableArray AST_VariableArray;

typedef struct call AST_Call;

typedef struct expressionElement AST_ExpressionElement;
typedef union expressionUnion AST_ExpressionUnion;
typedef struct expression AST_Expression;
typedef struct expressionVariable AST_ExpressionVariable;
typedef struct expressionParentheses AST_ExpressionParentheses;
typedef struct expressionCall AST_ExpressionCall;
typedef struct expressionNew AST_ExpressionNew;
typedef struct expressionAs AST_ExpressionAs;
typedef union expressionConstantUnion AST_ExpressionConstantUnion;
typedef struct expressionConstant AST_ExpressionConstant;
typedef struct expressionUnary AST_ExpressionUnary;
typedef struct expressionBinary AST_ExpressionBinary;

enum type {
  AST_VOID = 0,
  AST_INT,
  AST_FLOAT,
  AST_CHAR,
  AST_ARRAY_INT,
  AST_ARRAY_FLOAT,
  AST_ARRAY_CHAR
};

enum declarationType {
  AST_DECLARATION_VARIABLE,
  AST_DECLARATION_FUNCTION,
  AST_DECLARATION_PARAMETER
};

enum variableType {
  AST_VARIABLE_SIMPLE,
  AST_VARIABLE_ARRAY
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

enum expressionType {
  AST_EXPRESSION_VARIABLE,
  AST_EXPRESSION_PARENTHESES,
  AST_EXPRESSION_CALL,
  AST_EXPRESSION_NEW,
  AST_EXPRESSION_AS,

  AST_EXPRESSION_CONSTANT,
  AST_EXPRESSION_UNARY,
  AST_EXPRESSION_BINARY
};

enum expressionConstantType {
  AST_EXPRESSION_CONSTANT_INT,
  AST_EXPRESSION_CONSTANT_FLOAT,
  AST_EXPRESSION_CONSTANT_STRING
};

enum expressionUnaryType {
  AST_EXPRESSION_UNARY_MINUS,
  AST_EXPRESSION_UNARY_NOT
};

enum expressionBinaryType {
  AST_EXPRESSION_BINARY_MULTIPLICATION,
  AST_EXPRESSION_BINARY_DIVISION,
  AST_EXPRESSION_BINARY_PLUS,
  AST_EXPRESSION_BINARY_MINUS,
  AST_EXPRESSION_BINARY_LESS,
  AST_EXPRESSION_BINARY_GREATER,
  AST_EXPRESSION_BINARY_LESS_EQUAL,
  AST_EXPRESSION_BINARY_GREATER_EQUAL,
  AST_EXPRESSION_BINARY_EQUAL,
  AST_EXPRESSION_BINARY_NOT_EQUAL,
  AST_EXPRESSION_BINARY_LOGIC_AND,
  AST_EXPRESSION_BINARY_LOGIC_OR
};

struct program {
  AST_DeclarationElement *declarations;
};

struct declarationElement {
  AST_Declaration *declaration;
  AST_DeclarationElement *next;
};

struct declaration {
  AST_DeclarationType declarationType;
  char *id;
  AST_Type type;
  AST_DeclarationElement *parameterList;
  AST_Block *block;
};

struct block {
  AST_DeclarationElement *declarationVariableList;
  AST_CommandElement *commandList;
};

struct commandElement {
  AST_Command *command;
  AST_CommandElement *next;
  AST_CommandElement *prev;
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

union variableUnion {
  AST_VariableSimple *simple;
  AST_VariableArray *array;
};

struct variable {
  AST_VariableType variableType;
  AST_VariableUnion variable;
};

struct variableSimple {
  AST_VariableType variableType;
  char *id;
  AST_Declaration *declaration;
};

struct variableArray {
  AST_VariableType variableType;
  AST_Expression *outerExpression;
  AST_Expression *innerExpression;
};

struct call {
  char *id;
  AST_ExpressionElement *expressionList;
  AST_Declaration *declaration;
};

struct expressionElement {
  AST_Expression *expression;
  AST_ExpressionElement *next;
};

union expressionUnion {
  AST_ExpressionVariable *variable;
  AST_ExpressionParentheses *parentheses;
  AST_ExpressionCall *call;
  AST_ExpressionNew *new;
  AST_ExpressionAs *as;

  AST_ExpressionConstant *constant;
  AST_ExpressionUnary *unary;
  AST_ExpressionBinary *binary;
};

struct expression {
  AST_ExpressionType expressionType;
  AST_ExpressionUnion expression;
  AST_Type type;
};

struct expressionVariable {
  AST_ExpressionType expressionType;
  AST_Variable *variable;
};

struct expressionParentheses {
  AST_ExpressionType expressionType;
  AST_Expression *expression;
};

struct expressionCall {
  AST_ExpressionType expressionType;
  AST_Call *call;
};

struct expressionNew {
  AST_ExpressionType expressionType;
  AST_Type type;
  AST_Expression *expression;
};

struct expressionAs {
  AST_ExpressionType expressionType;
  AST_Expression *expression;
  AST_Type type;
};

union expressionConstantUnion {
  int i;
  float f;
  char *s;
};

struct expressionConstant {
  AST_ExpressionType expressionType;
  AST_ExpressionConstantType constantType;
  AST_ExpressionConstantUnion constant;
};

struct expressionUnary {
  AST_ExpressionType expressionType;
  AST_ExpressionUnaryType unaryType;
  AST_Expression *expression;
};

struct expressionBinary {
  AST_ExpressionType expressionType;
  AST_ExpressionBinaryType binaryType;
  AST_Expression *leftExpression;
  AST_Expression *rightExpression;
};

#endif
