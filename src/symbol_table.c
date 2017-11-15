#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "util.h"
#include "symbol_table.h"

void printSymbols(ST_SymbolElement *symbols);

ST_ScopeElement * ST_initScopeStack() {
  ST_ScopeElement *scopeStack = safeMalloc(sizeof(ST_ScopeElement));

  scopeStack->prev = NULL;
  scopeStack->next = NULL;

  return scopeStack;
}

void ST_addSymbol(ST_ScopeElement *scopeStack, AST_Declaration *symbol) {
  ST_SymbolElement *newSymbolElement = safeMalloc(sizeof(ST_SymbolElement));

  ST_SymbolElement *oldSymbolsEnd = scopeStack->symbols;

  newSymbolElement->symbol = symbol;

  // first symbol
  if (oldSymbolsEnd != NULL) {
    newSymbolElement->prev = oldSymbolsEnd;
    oldSymbolsEnd->next = newSymbolElement;
  } else {
    newSymbolElement->prev = NULL;
  }

  newSymbolElement->next = NULL;

  scopeStack->symbols = newSymbolElement;
}

ST_ScopeElement * ST_enterScope(ST_ScopeElement *scopeStack) {
  ST_ScopeElement *oldStackTop = scopeStack;
  ST_ScopeElement *newStackTop = safeMalloc(sizeof(ST_ScopeElement));

  newStackTop->prev = oldStackTop;
  newStackTop->next = NULL;
  newStackTop->symbols = NULL;

  oldStackTop->next = newStackTop;

  return newStackTop;
}

void ST_leaveScope(ST_ScopeElement *scopeStack) {
  ST_ScopeElement *oldStackTop = scopeStack;
  ST_ScopeElement *newStackTop = scopeStack->prev;
  ST_SymbolElement *currentSymbol = scopeStack->symbols;
  ST_SymbolElement *nextSymbol;

  while (currentSymbol != NULL) {
    nextSymbol = currentSymbol->next;
    free(currentSymbol);
    currentSymbol = nextSymbol;
  }

  newStackTop->next = NULL;
  free(oldStackTop);
}

AST_Declaration * ST_findDeclaration(ST_ScopeElement *scopeStack, char *id) {
  ST_ScopeElement *currentScope = scopeStack;
  ST_SymbolElement *currentSymbol;

  while (currentScope) {
    currentSymbol = currentScope->symbols;
    while (currentSymbol) {
      if (strcmp(currentSymbol->symbol->id, id) == 0) {
        return currentSymbol->symbol;
      }

      currentSymbol = currentSymbol->prev;
    }

    currentScope = currentScope->prev;
  }

  return NULL;
}

void ST_print(ST_ScopeElement *scopeStack) {
  ST_ScopeElement *currentScope = scopeStack;

  while (currentScope != NULL) {
    printf("[SCOPE]\n");
    printSymbols(currentScope->symbols);
    currentScope = currentScope->prev;
  }
}

void printSymbols(ST_SymbolElement *symbols) {
  ST_SymbolElement *currentSymbol = symbols;

  while (currentSymbol != NULL) {
    printf("%s\n", currentSymbol->symbol->id);
    currentSymbol = currentSymbol->prev;
  }
}