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

void generateCommands(int depth, AST_CommandElement *commands);
void generateCommand(int depth, AST_Command *command);
void generateCommandPrint(int depth, AST_CommandPrint *print);

int generateExpression(int depth, AST_Expression *expression);

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
      error("Unknown global declaration type");
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
      error("Cannot generate code for this type");
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
      error("Cannot generate code for this type");
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
  print(getType(parameter->type));
  print(" ");
  generateId(getNextId());
}

void generateBlock(int depth, AST_Block *block) {
  generateVariableDeclarations(depth, block->declarationVariableList);

  generateCommands(depth, block->commandList);
}


void generateVariableDeclarations(int depth, AST_DeclarationElement *variableDeclarations) {
  AST_DeclarationElement *currentVariableDeclaration = variableDeclarations;

  while (currentVariableDeclaration != NULL) {
    printLineWithDepth(depth, "%%%s = alloca %s",
      currentVariableDeclaration->declaration->id,
      getType(currentVariableDeclaration->declaration->type)
    );

    currentVariableDeclaration = currentVariableDeclaration->next;
  }
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
      error("Unknown command type");
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
      error("Cannot print a void variable");
      break;
    default:
      error("Cannot print an unknown variable");
      break;
  }
  print(" ");
  generateId(expressionId);
  print(")");
}

int generateExpression(int depth, AST_Expression *expression) {
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
