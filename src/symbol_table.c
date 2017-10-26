#include <stdlib.h>
#include "symbol_table.h"

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

  if (oldSymbolsEnd != NULL) {
    newSymbolElement->prev = oldSymbolsEnd;
  } else {
    newSymbolElement->prev = NULL;
  }
  newSymbolElement->next = NULL;

  oldSymbolsEnd->next = newSymbolElement;

  scopeStack->symbols = newSymbolElement;
}

void ST_enterScope(ST_ScopeElement *scopeStack) {
  ST_ScopeElement *oldStackTop = scopeStack;
  ST_ScopeElement *newStackTop = malloc(sizeof(ST_ScopeElement));
  ST_SymbolElement *symbols = malloc(sizeof(ST_SymbolElement));

  symbols->prev = NULL;
  symbols->next = NULL;

  newStackTop->prev = oldStackTop;
  newStackTop->next = NULL;
  newStackTop->symbols = symbols;

  oldStackTop->next = newStackTop;

  scopeStack = newStackTop;
}

void ST_leaveScope(ST_ScopeElement *scopeStack) {
  ST_ScopeElement *oldStackTop = scopeStack;
  ST_ScopeElement *newStackTop = scopeStack->prev;
  ST_SymbolElement *currentSymbol = scopeStack->symbols;
  ST_SymbolElement *nextSymbol;

  while (currentSymbol->next != NULL) {
    nextSymbol = currentSymbol->next;
    free(currentSymbol);
    currentSymbol = nextSymbol;
  }

  newStackTop->next = NULL;
  free(oldStackTop);
}