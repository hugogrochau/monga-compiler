#include <stdio.h>

#include "code_generator.h"
#include "util.h"

void generateHeader();
void generateGlobalDeclaration(AST_Declaration *declaration);
void generateGlobalVariable(AST_Declaration *declaration);
char * getType(AST_Type type);
char * getInitialValueForType(AST_Type type);
void generateFunction(AST_Declaration *declaration);
void generateParameters(AST_DeclarationElement *parameters);
void generateParameter(AST_Declaration *parameter);

void generateBlock(int depth, AST_Block *block);

void generateVariableDeclarations(int depth, AST_DeclarationElement *variableDeclarations);
void generateVariableDeclaration(int depth, AST_Declaration *variableDeclaration);

void generateCommands(int depth, AST_CommandElement *commands);
void generateCommand(int depth, AST_Command *command);
void generateCommandPrint(int depth, AST_CommandPrint *print);

int generateExpression(int depth, AST_Expression *expression);
int generateVariable(int depth, AST_Variable *variable);
int generateVariableSimple(int depth, AST_VariableSimple *variable);
int generateVariableArray(int depth, AST_VariableArray *variable);
int generateExpressionConstant(int depth, AST_ExpressionConstant *constantExpression);
int generateExpressionBinary(int depth, AST_Type type, AST_ExpressionBinary *expression);
int generateExpressionArithmetic(int depth, AST_Type type, AST_ExpressionBinary *expression);
int generateExpressionRelational(int depth, AST_Type type, AST_ExpressionBinary *expression);

int getNextId();
int getNextLabel();
void generateId(int id);
void  generateLabel(int label);

int currentId = 0;
int currentLabel = 0;

void CG_generateCode(AST_Program *program) {
  generateHeader();

  AST_DeclarationElement *currentDeclaration = program->declarations;

  while (currentDeclaration != NULL) {
    generateGlobalDeclaration(currentDeclaration->declaration);

    currentDeclaration = currentDeclaration->next;
  }
}

void generateHeader() {
  printLineWithDepth(0, "declare i32 @printf(i8*, ...)");
  printLineWithDepth(0, "@intTemplate private unnamed_addr constant [3 x i8] c\"%%d\\00\"");
  printLineWithDepth(0, "@floatTemplate private unnamed_addr constant [3 x i8] c\"%%f\\00\"");
  printLineWithDepth(0, "@charTemplate private unnamed_addr constant [3 x i8] c\"%%c\\00\"");
  printLineWithDepth(0, "@stringTemplate private unnamed_addr constant [3 x i8] c\"%%s\\00\"");
  printLineWithDepth(0, "@addressTemplate private unnamed_addr constant [3 x i8] c\"%%p\\00\"");
  putchar('\n');
}

void generateGlobalDeclaration(AST_Declaration *declaration) {
  switch (declaration->declarationType) {
    case AST_DECLARATION_VARIABLE:
      generateGlobalVariable(declaration);
      break;
    case AST_DECLARATION_FUNCTION:
      generateFunction(declaration);
      break;
    default:
      error("Cannot generate a global declaration for an unknown declaration type");
  }
  putchar('\n');
}

void generateGlobalVariable(AST_Declaration *declaration) {
  printLineWithDepth(0, "@%s = common global %s %s",
    declaration->id,
    getType(declaration->type),
    getInitialValueForType(declaration->type)
  );
}

char * getType(AST_Type type) {
  switch (type) {
    case AST_INT:
      return "i32";
      break;
    case AST_FLOAT:
      return "float";
      break;
    case AST_CHAR:
      return "i8";
      break;
    case AST_ARRAY_INT:
      return "i32*";
      break;
    case AST_ARRAY_FLOAT:
      return "float*";
      break;
    case AST_ARRAY_CHAR:
      return "i8*";
      break;
    case AST_VOID:
      return "null";
      break;
    default:
      error("Cannot generate a llvm type for an unknown type");
      return NULL;
  }
}

char * getInitialValueForType(AST_Type type) {
  switch (type) {
    case AST_INT:
      return "0";
      break;
    case AST_FLOAT:
      return "0.0";
      break;
    case AST_CHAR:
      return "0";
      break;
    case AST_ARRAY_INT:
      return "null";
      break;
    case AST_ARRAY_FLOAT:
      return "null";
      break;
    case AST_ARRAY_CHAR:
      return "null";
      break;
    default:
      error("Cannot generate an initial value for an unknown type");
      return NULL;
  }
}

void generateFunction(AST_Declaration *declaration) {

  print("define %s @%s (",
    getType(declaration->type),
    declaration->id
  );

  generateParameters(declaration->parameterList);

  print(") {");
  putchar('\n');

  generateBlock(1, declaration->block);

  print("}");
  putchar('\n');
}

void generateParameters(AST_DeclarationElement *parameters) {
  AST_DeclarationElement *currentParameter = parameters;
  int parameterIndex = 0;

  while (currentParameter != NULL) {
    generateParameter(currentParameter->declaration);

    if (currentParameter->next != NULL) {
      print(", ");
    }

    ++parameterIndex;
    currentParameter = currentParameter->next;
  }
}

void generateParameter(AST_Declaration *parameter) {
  int id = getNextId();
  parameter->tmp = id;

  print(getType(parameter->type));
  print(" ");
  generateId(id);
}

void generateBlock(int depth, AST_Block *block) {
  generateVariableDeclarations(depth, block->declarationVariableList);

  generateCommands(depth, block->commandList);
}


void generateVariableDeclarations(int depth, AST_DeclarationElement *variableDeclarations) {
  AST_DeclarationElement *currentVariableDeclaration = variableDeclarations;

  while (currentVariableDeclaration != NULL) {
    generateVariableDeclaration(depth, currentVariableDeclaration->declaration);

    currentVariableDeclaration = currentVariableDeclaration->next;
  }
}

void generateVariableDeclaration(int depth, AST_Declaration *variableDeclaration) {
  printLineWithDepth(depth, "%%%s = alloca %s",
    variableDeclaration->id,
    getType(variableDeclaration->type)
  );
}

void generateCommands(int depth, AST_CommandElement *commands) {
  AST_CommandElement *currentCommand = commands;

  while (currentCommand != NULL) {
    generateCommand(depth, currentCommand->command);

    currentCommand = currentCommand->next;
  }
}

void generateCommand(int depth, AST_Command *command) {
  switch (command->commandType) {
    case AST_COMMAND_IF:
      break;
    case AST_COMMAND_WHILE:
      break;
    case AST_COMMAND_ASSIGN:
      break;
    case AST_COMMAND_RETURN:
      break;
    case AST_COMMAND_CALL:
      break;
    case AST_COMMAND_PRINT:
      generateCommandPrint(depth, command->command.commandPrint);
      break;
    case AST_COMMAND_BLOCK:
      generateBlock(depth, command->command.commandBlock->block);
      break;
    default:
      error("Cannot generate a command for an unknown command type");
  }
  putchar('\n');
}

void generateCommandPrint(int depth, AST_CommandPrint *printCommand) {
  int expressionId = generateExpression(depth, printCommand->expression);

  printWithDepth(depth, "call i32 (i8*, ...) @printf(i8* ");

  switch (printCommand->expression->type) {
    case AST_INT:
      print("@intTemplate, i32");
      break;
    case AST_FLOAT:
      print("@floatTemplate, float");
      break;
    case AST_CHAR:
      print("@charTemplate, i8");
      break;
    case AST_ARRAY_INT:
      print("@addressTemplate, i32*");
      break;
    case AST_ARRAY_FLOAT:
      print("@addressTemplate, float*");
      break;
    case AST_ARRAY_CHAR:
      print("@stringTemplate, i8*");
      break;
    case AST_VOID:
      error("Cannot generate a print command for a void variable");
      break;
    default:
      error("Cannot generate a print command for an unknown variable");
      break;
  }
  print(" ");
  generateId(expressionId);
  print(")");
}

int generateExpression(int depth, AST_Expression *expression) {
  int id = -1;

  printWithDepth(depth, "");

  switch (expression->expressionType) {
    case AST_EXPRESSION_VARIABLE:
      id = generateVariable(depth, expression->expression.variable->variable);
      break;
    case AST_EXPRESSION_CALL:
      break;
    case AST_EXPRESSION_NEW:
      break;
    case AST_EXPRESSION_AS:
      break;
    case AST_EXPRESSION_CONSTANT:
      id = generateExpressionConstant(depth, expression->expression.constant);
      break;
    case AST_EXPRESSION_UNARY:
      break;
    case AST_EXPRESSION_BINARY:
      id = generateExpressionBinary(depth, expression->type, expression->expression.binary);
      break;
    default:
      error("Cannot generate an expression for an unknown expression type");
  }

  putchar('\n');

  return id;
}

int generateVariable(int depth, AST_Variable *variable) {
  switch (variable->variableType) {
    case AST_VARIABLE_SIMPLE:
      return generateVariableSimple(depth, variable->variable.simple);
      break;
    case AST_VARIABLE_ARRAY:
      return generateVariableArray(depth, variable->variable.array);
      break;
    default:
      error("Cannot generate a variable expression for an unknown variable type");
      return -1;
  }
}

int generateVariableSimple(int depth, AST_VariableSimple *variable) {
  int id = getNextId();
  int variableId;

  if (variable->declaration->tmp == -1) {
    // global
    variableId = getNextId();

    generateId(variableId);
    print(" = getelementptr %s, %s* @%s, i64 0",
      variable->declaration->type,
      variable->declaration->type,
      variable->declaration->id
    );
    putchar('\n');
  } else {
    // local
    variableId = variable->declaration->tmp;
  }

  generateId(id);
  print(" = load %s, %s* ",
    variable->declaration->type,
    variable->declaration->type
  );
  generateId(variableId);

  return id;
}

int generateVariableArray(int depth, AST_VariableArray *variable) {
  return getNextId();
}

int generateExpressionConstant(int depth, AST_ExpressionConstant *constantExpression) {
  int id = getNextId();
  generateId(id);

  switch (constantExpression->constantType) {
    case AST_EXPRESSION_CONSTANT_INT:
      print(" = add %s %s, %d",
        getType(AST_INT),
        getInitialValueForType(AST_INT),
        constantExpression->constant.i
      );
      break;
    case AST_EXPRESSION_CONSTANT_FLOAT:
      print(" = add %s %s, %6e",
        getType(AST_FLOAT),
        getInitialValueForType(AST_FLOAT),
        constantExpression->constant.f
      );
      break;
    case AST_EXPRESSION_CONSTANT_STRING:
      break;
    default:
      error("Cannot generate a constant expression for an unknown constant type");
  }

  return id;
}

int generateExpressionBinary(int depth, AST_Type type, AST_ExpressionBinary *expression) {
  switch (expression->binaryType) {
    case AST_EXPRESSION_BINARY_MULTIPLICATION:
    case AST_EXPRESSION_BINARY_DIVISION:
    case AST_EXPRESSION_BINARY_PLUS:
    case AST_EXPRESSION_BINARY_MINUS:
      return generateExpressionArithmetic(depth, type, expression);
      break;
    case AST_EXPRESSION_BINARY_LESS:
    case AST_EXPRESSION_BINARY_GREATER:
    case AST_EXPRESSION_BINARY_LESS_EQUAL:
    case AST_EXPRESSION_BINARY_GREATER_EQUAL:
    case AST_EXPRESSION_BINARY_EQUAL:
    case AST_EXPRESSION_BINARY_NOT_EQUAL:
    case AST_EXPRESSION_BINARY_LOGIC_AND:
    case AST_EXPRESSION_BINARY_LOGIC_OR:
      return generateExpressionRelational(depth, type, expression);
      break;
    default:
      error("Cannot generate an expression for a unknown expression type");
      return -1;
  }
}

int generateExpressionArithmetic(int depth, AST_Type type, AST_ExpressionBinary *expression) {
  int id = getNextId();
  int leftId = generateExpression(depth, expression->leftExpression);
  int rightId = generateExpression(depth, expression->rightExpression);

  generateId(id);
  print(" = ");

  switch (expression->binaryType) {
    case AST_EXPRESSION_BINARY_MULTIPLICATION:
      print("mul");
      break;
    case AST_EXPRESSION_BINARY_DIVISION:
      print("div");
      break;
    case AST_EXPRESSION_BINARY_PLUS:
      print("add");
      break;
    case AST_EXPRESSION_BINARY_MINUS:
      print("sub");
      break;
    default:
      error("Cannot generate an arithmetic expression for a non-arithmetic expression type");
  }

  print(" %s ", getType(type));
  generateId(leftId);
  print(", ");
  generateId(rightId);

  return id;
}

int generateExpressionRelational(int depth, AST_Type type, AST_ExpressionBinary *expression) {
  return getNextId();
}

int getNextId() {
  ++currentId;
  return currentId;
}

int getNextLabel() {
  ++currentLabel;
  return currentLabel;
}

void generateId(int id) {
  print("%%t%d", id);
}

void generateLabel(int label) {
  print("%%l%d", label);
}
