#include <stdio.h>

#include "code_generator.h"
#include "util.h"

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

int currentId = 0;

void CG_generateCode(AST_Program *program) {
  AST_DeclarationElement *currentDeclaration = program->declarations;

  while (currentDeclaration != NULL) {
    generateGlobalDeclaration(currentDeclaration->declaration);
    putchar('\n');

    currentDeclaration = currentDeclaration->next;
  }
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
      error("Can't generate code for this type");
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
      error("Can't generate code for this type");
      return NULL;
  }
}

void generateFunction(AST_Declaration *declaration) {

  printWithDepth(0, "define %s @%s (",
    getType(declaration->type),
    declaration->id
  );

  generateParameters(declaration->parameterList);

  printWithDepth(0, ") {");
  putchar('\n');

  generateBlock(1, declaration->block);

  printWithDepth(0, "}");
  putchar('\n');
}

void generateParameters(AST_DeclarationElement *parameters) {
  AST_DeclarationElement *currentParameter = parameters;
  int parameterIndex = 0;

  while (currentParameter != NULL) {
    generateParameter(currentParameter->declaration);

    if (currentParameter->next != NULL) {
      printWithDepth(0, ", ");
    }

    ++parameterIndex;
    currentParameter = currentParameter->next;
  }
}

void generateParameter(AST_Declaration *parameter) {
  printWithDepth(0, "%s %%%s",
    getType(parameter->type),
    parameter->id
  );
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

}

int generateId() {
  ++currentId;
  return currentId;
}