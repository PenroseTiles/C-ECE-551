#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define fail exit(EXIT_FAILURE)

void failWithMessage(const char * msg) {
  fprintf(stderr, "%s", msg);
  fail;
}

kvpair_t * readLine(FILE * f) {
  kvpair_t * pair = malloc(sizeof(*pair));
  char * line = NULL;
  size_t size = 0;
  char * equalsptr = NULL;
  char * newlineptr = NULL;
  size_t keylength = 0;
  size_t valuelength = 0;
  if (f == NULL) {
    failWithMessage("couldn't open file");
  }

  if (getline(&line, &size, f) >= 0) {
    equalsptr = strchr(line, '=');
    newlineptr = strchr(line, '\n');

    keylength = (equalsptr - line) / sizeof(char);
    valuelength = (newlineptr - equalsptr) / sizeof(char);

    pair->key = malloc((keylength + 1) * sizeof(char));
    strncpy(pair->key, line, keylength);

    pair->value = malloc(valuelength * sizeof(char));
    strncpy(pair->value, equalsptr + 1, valuelength - 1);

    pair->key[keylength] = '\0';
    pair->value[valuelength - 1] = '\0';

    free(line);
    size = 0;
  }
  else {
    free(pair);
    free(line);
    pair = NULL;
  }
  return pair;
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");
  kvarray_t * dict = malloc(sizeof(*dict));
  dict->length = 0;
  dict->pairs = malloc(sizeof(*dict->pairs));
  kvpair_t * pair = NULL;

  while ((pair = readLine(f)) != NULL) {
    dict->pairs = realloc(dict->pairs, (dict->length + 1) * sizeof(*dict->pairs));
    dict->pairs[dict->length] = *pair;
    dict->length++;
    free(pair);
  }
  if (fclose(f) != 0) {
    failWithMessage("could not close file");
  }
  return dict;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->length; i++) {
    free(pairs->pairs[i].key);
    free(pairs->pairs[i].value);
  }

  free(pairs->pairs);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->length; i++) {
    printf("key='%s' value='%s'\n", pairs->pairs[i].key, pairs->pairs[i].value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  size_t len = pairs->length;
  for (size_t i = 0; i < len; i++) {
    if (strcmp(pairs->pairs[i].key, key) == 0) {
      return pairs->pairs[i].value;
    }
  }
  return NULL;
}
