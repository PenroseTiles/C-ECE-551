#include "counts.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

counts_t * createCounts(void) {
  //WRITE ME
  counts_t * counts = malloc(sizeof(*counts));
  counts->array = NULL;  //malloc(sizeof(*(counts->array)));
  counts->length = 0;
  counts->unkown_freq = 0;
  return counts;
}

void addCount(counts_t * c, const char * name) {
  //WRITE ME
  //name is key here
  if (name == NULL) {
    c->unkown_freq++;
    return;
  }
  size_t length = strlen(name);
  size_t i;
  for (i = 0; i < c->length; i++) {
    if (strcmp(c->array[i].key, name) == 0) {
      c->array[i].freq++;
      return;
    }
  }
  assert(i == c->length);
  c->array = realloc(c->array, sizeof(*(c->array)) * (c->length + 1));
  c->array[c->length].key = malloc(sizeof(char) * (1 + length));
  strncpy(c->array[c->length].key, name, length + 1);
  c->array[c->length].freq = 1;
  c->length++;
  return;
}

void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (size_t i = 0; i < c->length; i++) {
    fprintf(outFile, "%s: %lu\n", c->array[i].key, c->array[i].freq);
  }
  if (c->unkown_freq > 0) {
    fprintf(outFile, "<unknown> : %lu\n", c->unkown_freq);
  }
  return;
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (size_t i = 0; i < c->length; i++) {
    free(c->array[i].key);
  }
  free(c->array);
  free(c);
}
