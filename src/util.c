#include <stdio.h>
#include <stdlib.h>

void error(char *message) {
  printf("ERROR: %s", message);
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