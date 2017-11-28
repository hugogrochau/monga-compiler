#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H

#include "ast_structure.h"

typedef struct stringElement CG_StringElement;

struct stringElement {
  char *string;
  int id;
  int length;
  CG_StringElement *next;
  CG_StringElement *prev;
};

void CG_generateCode(AST_Program *program);

#endif
