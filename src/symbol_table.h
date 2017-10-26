#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "ast_structure.h"

typedef struct scopeElement ST_ScopeElement;

typedef struct symbolElement ST_SymbolElement;

typedef struct symbol ST_Symbol;

struct scopeElement {
  ST_SymbolElement *symbols;
  ST_ScopeElement *next;
  ST_ScopeElement *prev;
};

struct symbolElement {
  ST_Symbol *symbol;
  ST_SymbolElement *next;
  ST_SymbolElement *prev;
};

struct symbol {
  char *id;
  AST_Declaration *declaration;
};

ST_ScopeElement * ST_initScopeStack();

void ST_addSymbol(ST_ScopeElement *scopeStack, char *id, AST_Declaration *declaration);

ST_ScopeElement * ST_enterScope(ST_ScopeElement *scopeStack);

void ST_leaveScope(ST_ScopeElement *scopeStack);

AST_Declaration * ST_findDeclaration(ST_ScopeElement *scopeStack, char *id);

void ST_print(ST_ScopeElement *scopeStack);

#endif
