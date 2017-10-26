#include <stdio.h>
#include "ast_knit.h"
#include "symbol_table.h"

void handleBlock(AST_Block *block);

void handleDeclarations(AST_DeclarationElement *declarations);

void saveDeclarations(AST_Declaration *declaration);

ST_ScopeElement *scopeStack;

void AST_knit (AST_Program *program) {
  scopeStack = ST_initScopeStack();
  ST_enterScope(scopeStack);

  handleDeclarations(program->declarations);

  ST_print(scopeStack);
}

void handleDeclarations(AST_DeclarationElement *declarations) {
  AST_DeclarationElement *currentDeclaration = declarations;

  while (currentDeclaration != NULL) {
    saveDeclarations(currentDeclaration->declaration);
    currentDeclaration = currentDeclaration->next;
  }

  currentDeclaration = declarations;

  while (currentDeclaration != NULL) {
    if (currentDeclaration->declaration->declarationType == AST_DECLARATION_FUNCTION) {
      handleBlock(currentDeclaration->declaration->declaration.function->block);
    }
    currentDeclaration = currentDeclaration->next;
  }
}

void saveDeclarations(AST_Declaration *declaration) {
  switch (declaration->declarationType) {
    case AST_DECLARATION_FUNCTION:
      ST_addSymbol(scopeStack, declaration->declaration.function->id, declaration);
      break;
    case AST_DECLARATION_VARIABLE:
      ST_addSymbol(scopeStack, declaration->declaration.variable->id, declaration);
      break;
  }
}

void handleBlock(AST_Block *block) {
  scopeStack = ST_enterScope(scopeStack);
  handleDeclarations(block->declarationVariableList);
}
