#include <stdio.h>
#include <string.h>

#include "code_generator.h"
#include "util.h"

static void generateHeader();
static void generateGlobalDeclaration(AST_Declaration *declaration);
static void generateGlobalVariable(AST_Declaration *declaration);
static void generateFunction(AST_Declaration *declaration);
static void generateParameters(AST_DeclarationElement *parameters);
static void generateParameter(AST_Declaration *parameter);

static void generateBlock(int depth, AST_Block *block);

static void generateVariableDeclarations(int depth, AST_DeclarationElement *variableDeclarations);
static void generateVariableDeclaration(int depth, AST_Declaration *variableDeclaration);

static void generateCommands(int depth, AST_CommandElement *commands);
static void generateCommand(int depth, AST_Command *command);

static void generateCommandIf(int depth, AST_CommandIf *commandIf);
static void generateCommandWhile(int depth, AST_CommandWhile *commandWhile);
static void generateCondition(int depth, AST_Expression *expression, int trueLabel, int falseLabel);
static int generateUnaryNot(int depth, AST_Expression* expression);
static int generateBooleanFromExpression(int depth, AST_Expression *expression);
static int generateRelational(int depth, AST_Expression *expression);
static int generateLogical(int depth, AST_Expression *expression);
static void generateSimpleBlock(int depth, int labelStart, int labelExit, AST_Block* block);

static void generateCommandReturn(int depth, AST_CommandReturn *returnCommand);
static void generateCommandAssign(int depth, AST_CommandAssign *assignCommand);
static void generateCommandPrint(int depth, AST_CommandPrint *print);

static int generateExpression(int depth, AST_Expression *expression);
static int generateExpressionVariable(int depth, AST_Variable *variable);
static int generateExpressionVariableSimple(int depth, AST_VariableSimple *variable);
static int generateExpressionVariableArray(int depth, AST_VariableArray *variable);
static int generateExpressionConstant(int depth, AST_ExpressionConstant *constantExpression);
static int generateExpressionUnary(int depth, AST_Expression *expression);
static int generateExpressionBinary(int depth, AST_Expression *expression);
static int generateExpressionArithmetic(int depth, AST_Expression *expression);
static int generateExpressionRelational(int depth, AST_Expression *expression);
static int generateExpressionLogical(int depth, AST_Expression *expression);
static int generateExtension(int depth, int id, AST_Type type);

static void generateId(int id);
static void generateLabel(int label);
static void generateLabelStart(int label);
static void generateFloat(float value);

static int getNextId();
static int getNextLabel();

static char * getType(AST_Type type);
static char * getInitialValueForType(AST_Type type);

int currentId = 0;
int currentLabel = 0;

void CG_generateCode(AST_Program *program) {
  generateHeader();

  AST_DeclarationElement *currentDeclaration = program->declarations;

  while (currentDeclaration != NULL) {
    generateGlobalDeclaration(currentDeclaration->declaration);

    currentDeclaration = currentDeclaration->next;
    if (currentDeclaration != NULL) {
      putchar('\n');
    }
  }
}

static void generateHeader() {
  printLineWithDepth(0, "declare i32 @printf(i8*, ...)");
  printLineWithDepth(0, "@intTemplate = private unnamed_addr constant [3 x i8] c\"%%d\\00\"");
  printLineWithDepth(0, "@floatTemplate = private unnamed_addr constant [3 x i8] c\"%%f\\00\"");
  printLineWithDepth(0, "@charTemplate = private unnamed_addr constant [3 x i8] c\"%%c\\00\"");
  printLineWithDepth(0, "@stringTemplate = private unnamed_addr constant [3 x i8] c\"%%s\\00\"");
  printLineWithDepth(0, "@addressTemplate = private unnamed_addr constant [3 x i8] c\"%%p\\00\"");
  putchar('\n');
}

static void generateGlobalDeclaration(AST_Declaration *declaration) {
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
}

static void generateGlobalVariable(AST_Declaration *declaration) {
  printLineWithDepth(0, "@%s = global %s %s",
    declaration->id,
    getType(declaration->type),
    getInitialValueForType(declaration->type)
  );
}

static void generateFunction(AST_Declaration *declaration) {
  print("define %s @%s (",
    getType(declaration->type),
    declaration->id
  );

  generateParameters(declaration->parameterList);

  print(") {");
  putchar('\n');

  generateBlock(1, declaration->block);

  if (declaration->type == AST_VOID) {
    printWithDepth(1, "ret void");
    putchar('\n');
  }

  print("}");
  putchar('\n');
}

static void generateParameters(AST_DeclarationElement *parameters) {
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

static void generateParameter(AST_Declaration *parameter) {
  int id = getNextId();
  parameter->tmp = id;

  print(getType(parameter->type));
  print(" ");
  generateId(id);
}

static void generateBlock(int depth, AST_Block *block) {
  generateVariableDeclarations(depth, block->declarationVariableList);

  generateCommands(depth, block->commandList);
}


static void generateVariableDeclarations(int depth, AST_DeclarationElement *variableDeclarations) {
  AST_DeclarationElement *currentVariableDeclaration = variableDeclarations;

  while (currentVariableDeclaration != NULL) {
    generateVariableDeclaration(depth, currentVariableDeclaration->declaration);

    currentVariableDeclaration = currentVariableDeclaration->next;
  }
}

static void generateVariableDeclaration(int depth, AST_Declaration *variableDeclaration) {
  int id = getNextId();
  variableDeclaration->tmp = id;

  printWithDepth(depth, "");
  generateId(id);
  print(" = alloca %s",
    getType(variableDeclaration->type)
  );
  putchar('\n');
}

static void generateCommands(int depth, AST_CommandElement *commands) {
  AST_CommandElement *currentCommand = commands;

  while (currentCommand != NULL) {
    generateCommand(depth, currentCommand->command);

    currentCommand = currentCommand->next;
  }
}

static void generateCommand(int depth, AST_Command *command) {
  switch (command->commandType) {
    case AST_COMMAND_IF:
      generateCommandIf(depth, command->command.commandIf);
      break;
    case AST_COMMAND_WHILE:
      generateCommandWhile(depth, command->command.commandWhile);
      break;
    case AST_COMMAND_ASSIGN:
      generateCommandAssign(depth, command->command.commandAssign);
      break;
    case AST_COMMAND_RETURN:
      generateCommandReturn(depth, command->command.commandReturn);
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
}

static void generateCommandIf(int depth, AST_CommandIf *commandIf) {
  int trueLabel = getNextLabel();
  int exitLabel = getNextLabel();
  int falseLabel;

  // if else
  if (commandIf->elseBlock != NULL) {
    falseLabel = getNextLabel();
    generateCondition(depth, commandIf->expression, trueLabel, falseLabel);
    generateSimpleBlock(depth, trueLabel, exitLabel, commandIf->thenBlock);
    generateSimpleBlock(depth, falseLabel, exitLabel, commandIf->elseBlock);
  // just if
  } else {
    generateCondition(depth, commandIf->expression, trueLabel, exitLabel);
    generateSimpleBlock(depth, trueLabel, exitLabel, commandIf->thenBlock);
  }

  generateLabelStart(exitLabel);
}
static void generateCommandWhile(int depth, AST_CommandWhile *commandWhile) {
  int bodyLabel = getNextLabel();
  int exitLabel = getNextLabel();

  generateCondition(depth, commandWhile->expression, bodyLabel, exitLabel);

  generateLabelStart(bodyLabel);

  generateBlock(depth, commandWhile->block);

  generateCondition(depth, commandWhile->expression, bodyLabel, exitLabel);

  generateLabelStart(exitLabel);
}

static void generateCondition(int depth, AST_Expression *expression, int trueLabel, int falseLabel) {
  int booleanId;

  switch (expression->expressionType) {
    case AST_EXPRESSION_UNARY:
      switch (expression->expression.unary->unaryType) {
        case AST_EXPRESSION_UNARY_NOT:
          booleanId = generateUnaryNot(depth, expression);
        break;
        default:
          booleanId = generateBooleanFromExpression(depth, expression);
        break;
      }
    case AST_EXPRESSION_BINARY:
      switch (expression->expression.binary->binaryType) {
        case AST_EXPRESSION_BINARY_LESS:
        case AST_EXPRESSION_BINARY_GREATER:
        case AST_EXPRESSION_BINARY_LESS_EQUAL:
        case AST_EXPRESSION_BINARY_GREATER_EQUAL:
        case AST_EXPRESSION_BINARY_EQUAL:
        case AST_EXPRESSION_BINARY_NOT_EQUAL:
          booleanId = generateRelational(depth, expression);
          break;
        case AST_EXPRESSION_BINARY_LOGIC_OR:
        case AST_EXPRESSION_BINARY_LOGIC_AND:
          booleanId = generateLogical(depth, expression);
          break;
        default:
          booleanId = generateBooleanFromExpression(depth, expression);
          break;
      }
      break;
    default:
      booleanId = generateBooleanFromExpression(depth, expression);
      break;
  }

  printWithDepth(depth, "br i1 ");
  generateId(booleanId);
  print(", label ");
  generateLabel(trueLabel);
  print(", label ");
  generateLabel(falseLabel);
  putchar('\n');
}

static int generateUnaryNot(int depth, AST_Expression* expression) {
  AST_ExpressionUnary* expressionUnary = expression->expression.unary;
  int expressionId = generateExpression(depth, expressionUnary->expression);
  int booleanId = getNextId();
  int returnedId = getNextId();

  printWithDepth(depth, "");
  generateId(booleanId);
  print(" = ");
  switch (expressionUnary->expression->type) {
    case AST_INT:
      print("icmp ne");
      break;
    case AST_FLOAT:
      print("fcmp one");
      break;
    default:
      break;
  }
  print(" %s ", getType(expressionUnary->expression->type));
  generateId(expressionId);
  print(", %s", getInitialValueForType(expressionUnary->expression->type));
  putchar('\n');

  printWithDepth(depth, "");
  generateId(returnedId);
  print(" = xor i1 ");
  generateId(booleanId);
  print(", true");
  putchar('\n');

  return returnedId;
}

static int generateBooleanFromExpression(int depth, AST_Expression *expression) {
  int expressionId = generateExpression(depth, expression);
  int booleanId = getNextId();

  printWithDepth(depth, "");
  generateId(booleanId);
  print(" = icmp ne i32 ");
  generateId(expressionId);
  print(", 0");
  putchar('\n');

  return booleanId;
}

static int generateRelational(int depth, AST_Expression *expression) {
  AST_ExpressionBinary *binaryExpression = expression->expression.binary;

  int leftId = generateExpression(depth, binaryExpression->leftExpression);
  int rightId = generateExpression(depth, binaryExpression->rightExpression);
  int booleanId = getNextId();

  printWithDepth(depth, "");
  generateId(booleanId);
  print(" = ");

  switch (binaryExpression->leftExpression->type) {
    case AST_INT:
      print("icmp ");
      switch (binaryExpression->binaryType) {
        case AST_EXPRESSION_BINARY_LESS:
          print("slt");
          break;
        case AST_EXPRESSION_BINARY_GREATER:
          print("sgt");
          break;
        case AST_EXPRESSION_BINARY_LESS_EQUAL:
          print("sle");
          break;
        case AST_EXPRESSION_BINARY_GREATER_EQUAL:
          print("sge");
          break;
        case AST_EXPRESSION_BINARY_EQUAL:
          print("eq");
          break;
        case AST_EXPRESSION_BINARY_NOT_EQUAL:
          print("ne");
          break;
        default:
          break;
      }
      break;
    case AST_FLOAT:
      print("fcmp ");
      switch (binaryExpression->binaryType) {
        case AST_EXPRESSION_BINARY_LESS:
          print("olt");
          break;
        case AST_EXPRESSION_BINARY_GREATER:
          print("ogt");
          break;
        case AST_EXPRESSION_BINARY_LESS_EQUAL:
          print("ole");
          break;
        case AST_EXPRESSION_BINARY_GREATER_EQUAL:
          print("oge");
          break;
        case AST_EXPRESSION_BINARY_EQUAL:
          print("oeq");
          break;
        case AST_EXPRESSION_BINARY_NOT_EQUAL:
          print("one");
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }

  print(" %s ", getType(binaryExpression->leftExpression->type));
  generateId(leftId);
  print(", ");
  generateId(rightId);
  putchar('\n');

  return booleanId;
}

static int generateLogical(int depth, AST_Expression *expression) {
  AST_ExpressionBinary *binaryExpression = expression->expression.binary;
  int trueLabel = getNextLabel();
  int rightExpressionLabel = getNextLabel();
  int falseLabel = getNextLabel();
  int resultLabel = getNextLabel();
  int returnedId = getNextId();

  switch (binaryExpression->binaryType) {
    case AST_EXPRESSION_BINARY_LOGIC_AND:
      generateCondition(depth, binaryExpression->leftExpression, rightExpressionLabel, falseLabel);
      break;
    case AST_EXPRESSION_BINARY_LOGIC_OR:
      generateCondition(depth, binaryExpression->leftExpression, trueLabel, rightExpressionLabel);
      break;
    default:
      break;
  }

  generateSimpleBlock(depth, trueLabel, resultLabel, NULL);

  generateLabelStart(rightExpressionLabel);
  generateCondition(depth, binaryExpression->rightExpression, trueLabel, falseLabel);

  generateSimpleBlock(depth, falseLabel, resultLabel, NULL);

  generateLabelStart(resultLabel);
  printWithDepth(depth, "");
  generateId(returnedId);
  print(" = phi i1 [1, ");
  generateLabel(trueLabel);
  print("], [0, ");
  generateLabel(falseLabel);
  print("]");
  putchar('\n');

  return returnedId;
}

static void generateSimpleBlock(int depth, int labelStart, int labelExit, AST_Block* block) {
  generateLabelStart(labelStart);
  if (block != NULL) {
    generateBlock(depth, block);
  }
  printWithDepth(depth, "br label ");
  generateLabel(labelExit);
  putchar('\n');
}

static void generateCommandAssign(int depth, AST_CommandAssign *assignCommand) {
  AST_Declaration *variableDeclaration = assignCommand->variable->variable.simple->declaration;

  int expressionId = generateExpression(depth, assignCommand->expression);

  printWithDepth(depth, "store %s ", getType(assignCommand->expression->type));
  generateId(expressionId);
  print(", %s* ", getType(variableDeclaration->type));
  // global
  if (variableDeclaration->tmp == -1) {
    print("@%s", variableDeclaration->id);
  } else {
    generateId(variableDeclaration->tmp);
  }
  putchar('\n');
}

static void generateCommandReturn(int depth, AST_CommandReturn *returnCommand) {
  int expressionId = generateExpression(depth, returnCommand->expression);

  printWithDepth(depth, "ret %s ", getType(returnCommand->expression->type));
  generateId(expressionId);
  putchar('\n');
}

static void generateCommandPrint(int depth, AST_CommandPrint *printCommand) {
  int expressionId = generateExpression(depth, printCommand->expression);
  int doubleId;

  switch (printCommand->expression->type) {
    case AST_CHAR:
    case AST_INT:
      printWithDepth(depth, "call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@intTemplate, i32 0, i32 0), i32 ");
      generateId(expressionId);
      print(")");
      break;
    case AST_FLOAT:
      doubleId = getNextId();
      printWithDepth(depth, "");
      generateId(doubleId);
      print(" = fpext float ");
      generateId(expressionId);
      print(" to double");
      putchar('\n');

      printWithDepth(depth, "call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8] *@floatTemplate, i32 0, i32 0), double ");
      generateId(doubleId);
      print(")");
      break;
    default:
      break;
  }
  putchar('\n');
}

static int generateExpression(int depth, AST_Expression *expression) {
  int id;

  switch (expression->expressionType) {
    case AST_EXPRESSION_VARIABLE:
      id = generateExpressionVariable(depth, expression->expression.variable->variable);
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
      id = generateExpressionUnary(depth, expression);
      break;
    case AST_EXPRESSION_BINARY:
      id = generateExpressionBinary(depth, expression);
      break;
    default:
      id = -1;
      error("Cannot generate an expression for an unknown expression type");
  }

  putchar('\n');

  return id;
}

static int generateExpressionVariable(int depth, AST_Variable *variable) {
  switch (variable->variableType) {
    case AST_VARIABLE_SIMPLE:
      return generateExpressionVariableSimple(depth, variable->variable.simple);
      break;
    case AST_VARIABLE_ARRAY:
      return generateExpressionVariableArray(depth, variable->variable.array);
      break;
    default:
      error("Cannot generate a variable expression for an unknown variable type");
      return -1;
  }
}

static int generateExpressionVariableSimple(int depth, AST_VariableSimple *variable) {
  int id = getNextId();
  int variableId;

  printWithDepth(depth, "");

  if (variable->declaration->tmp == -1) {
    // global
    variableId = getNextId();

    generateId(variableId);
    print(" = getelementptr %s, %s* @%s, i64 0",
      getType(variable->declaration->type),
      getType(variable->declaration->type),
      variable->declaration->id
    );
    putchar('\n');
    printWithDepth(depth, "");
  } else {
    // local
    variableId = variable->declaration->tmp;
  }

  generateId(id);
  print(" = load %s, %s* ",
    getType(variable->declaration->type),
    getType(variable->declaration->type)
  );
  generateId(variableId);

  return id;
}

static int generateExpressionVariableArray(int depth, AST_VariableArray *variable) {
  return getNextId();
}

static int generateExpressionConstant(int depth, AST_ExpressionConstant *constantExpression) {
  int id = getNextId();

  printWithDepth(depth, "");
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
      print(" = fadd %s %s, ",
        getType(AST_FLOAT),
        getInitialValueForType(AST_FLOAT)
      );
      generateFloat(constantExpression->constant.f);
      break;
    case AST_EXPRESSION_CONSTANT_STRING:
      break;
    default:
      error("Cannot generate a constant expression for an unknown constant type");
  }

  return id;
}

static int generateExpressionUnary(int depth, AST_Expression *expression) {
  AST_ExpressionUnary* expressionUnary = expression->expression.unary;
  int expressionId = generateExpression(depth, expressionUnary->expression);
  int returnedId;
  int booleanId;

  switch (expressionUnary->unaryType) {
    case AST_EXPRESSION_UNARY_MINUS:
      returnedId = getNextId();
      printWithDepth(depth, "");
      generateId(returnedId);
      print(" = ");
      switch (expression->type) {
        case AST_INT:
          print("sub nsw");
          break;
        case AST_FLOAT:
          print("fsub");
          break;
        default:
          break;
      }
      print(" %s %s, ",
        getType(expression->type),
        getInitialValueForType(expression->type));
      generateId(expressionId);
    break;
    case AST_EXPRESSION_UNARY_NOT:
      booleanId = generateUnaryNot(depth, expression);
      returnedId = generateExtension(depth, booleanId, expression->type);
    break;
  }

  return returnedId;
}

static int generateExpressionBinary(int depth, AST_Expression *expression) {
  AST_ExpressionBinary *binaryExpression = expression->expression.binary;

  switch (binaryExpression->binaryType) {
    case AST_EXPRESSION_BINARY_MULTIPLICATION:
    case AST_EXPRESSION_BINARY_DIVISION:
    case AST_EXPRESSION_BINARY_PLUS:
    case AST_EXPRESSION_BINARY_MINUS:
      return generateExpressionArithmetic(depth, expression);
      break;
    case AST_EXPRESSION_BINARY_LESS:
    case AST_EXPRESSION_BINARY_GREATER:
    case AST_EXPRESSION_BINARY_LESS_EQUAL:
    case AST_EXPRESSION_BINARY_GREATER_EQUAL:
    case AST_EXPRESSION_BINARY_EQUAL:
    case AST_EXPRESSION_BINARY_NOT_EQUAL:
      return generateExpressionRelational(depth, expression);
      break;
    case AST_EXPRESSION_BINARY_LOGIC_AND:
    case AST_EXPRESSION_BINARY_LOGIC_OR:
      return generateExpressionLogical(depth, expression);
    default:
      error("Cannot generate an expression for a unknown expression type");
      return -1;
  }
}

static int generateExpressionArithmetic(int depth, AST_Expression *expression) {
  AST_ExpressionBinary *binaryExpression = expression->expression.binary;
  int leftId = generateExpression(depth, binaryExpression->leftExpression);
  int rightId = generateExpression(depth, binaryExpression->rightExpression);
  int id = getNextId();

  printWithDepth(depth, "");
  generateId(id);
  print(" = ");

  switch (binaryExpression->leftExpression->type) {
    case AST_INT:
      switch (binaryExpression->binaryType) {
        case AST_EXPRESSION_BINARY_MULTIPLICATION:
          print("mul");
          break;
        case AST_EXPRESSION_BINARY_DIVISION:
          print("sdiv");
          break;
        case AST_EXPRESSION_BINARY_PLUS:
          print("add");
          break;
        case AST_EXPRESSION_BINARY_MINUS:
          print("sub");
          break;
        default:
          break;
      }
    break;
    case AST_FLOAT:
      switch (binaryExpression->binaryType) {
        case AST_EXPRESSION_BINARY_MULTIPLICATION:
          print("fmul");
          break;
        case AST_EXPRESSION_BINARY_DIVISION:
          print("fdiv");
          break;
        case AST_EXPRESSION_BINARY_PLUS:
          print("fadd");
          break;
        case AST_EXPRESSION_BINARY_MINUS:
          print("fsub");
          break;
        default:
          break;
      }
    break;
    default:
    break;
  }

  print(" %s ", getType(expression->type));
  generateId(leftId);
  print(", ");
  generateId(rightId);

  return id;
}

static int generateExpressionRelational(int depth, AST_Expression *expression) {
  int booleanId = generateRelational(depth, expression);

  return generateExtension(depth, booleanId, expression->type);
}

static int generateExpressionLogical(int depth, AST_Expression *expression) {
  int booleanId = generateLogical(depth, expression);

  return generateExtension(depth, booleanId, expression->type);
}

static int generateExtension(int depth, int id, AST_Type type) {
  int extendedId = getNextId();

  printWithDepth(depth, "");
  generateId(extendedId);
  print(" = ");
  print("zext i1 ");
  generateId(id);
  print(" to i32");

  return extendedId;
}

static void generateId(int id) {
  print("%%t%d", id);
}

static void generateLabel(int label) {
  print("%%l%d", label);
}

static void generateLabelStart(int label) {
  print("l%d:", label);
  putchar('\n');
}

static void generateFloat(float value) {
  int i;
  double doubleValue = value;
  unsigned char buffer[sizeof(double)];

  memcpy(buffer, &doubleValue, sizeof(double));

  print("0x");
  for(i = sizeof(double) - 1; i >= 0; i--) {
    print("%02X", buffer[i]);
  }
}

static int getNextId() {
  ++currentId;
  return currentId;
}

static int getNextLabel() {
  ++currentLabel;
  return currentLabel;
}

static char * getType(AST_Type type) {
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
      return "void";
      break;
    default:
      error("Cannot generate a llvm type for an unknown type");
      return NULL;
  }
}

static char * getInitialValueForType(AST_Type type) {
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
