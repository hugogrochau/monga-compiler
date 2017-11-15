#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void error(char *template, ...) {
  va_list argumentList;
  va_start(argumentList, template);

  printf("ERROR: ");
  vprintf(template, argumentList);

  va_end(argumentList);

  exit(1);
}

void * safeMalloc(size_t size) {
  void *pointer = malloc(size);
  if (pointer != NULL) {
    return pointer;
  }
  error("Not enough memory");
  return NULL;
}

void printWithDepth(int depth, char *template, ...) {
  va_list argumentList;
  va_start(argumentList, template);

  for (int i = 0; i < depth; i++) {
    printf("  ");
  }

  vprintf(template, argumentList);
  va_end(argumentList);

  putchar('\n');
}
