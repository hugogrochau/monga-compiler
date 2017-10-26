#include <stdlib.h>
#include <stdio.h>
#include "symbol_table.h"

void printSymbols(ST_SymbolElement *symbols);
void print(ST_ScopeElement *scopeStack);

ST_ScopeElement * ST_initScopeStack() {
  ST_ScopeElement *scopeStack = malloc(sizeof(ST_ScopeElement));

  scopeStack->prev = NULL;
  scopeStack->next = NULL;

  return scopeStack;
}

void ST_addSymbol(ST_ScopeElement *scopeStack, char *id, AST_Declaration *declaration) {
  ST_Symbol *symbol = malloc(sizeof(ST_Symbol));
  ST_SymbolElement *newSymbolElement = malloc(sizeof(ST_SymbolElement));

  ST_SymbolElement *oldSymbolsEnd = scopeStack->symbols;

  symbol->id = id;
  symbol->declaration = declaration;

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
  ST_ScopeElement *newStackTop = malloc(sizeof(ST_ScopeElement));

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