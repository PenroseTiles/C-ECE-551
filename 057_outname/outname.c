#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
#define fail exit(EXIT_SUCCESS)

struct position_t {
  char * value;
  size_t strength;
};
typedef struct position_t position_t;

struct all_positions_t {
  position_t * array;
  size_t size;
};
typedef struct all_positions_t all_positions_t;

void addValuetoCatalog(all_positions_t * catalog, char * value) {
  catalog->array = realloc(catalog->array, (1 + catalog->size) * sizeof(*catalog->array));
  catalog->size++;
  catalog->array[catalog->size - 1].value = value;
  catalog->array[catalog->size - 1].strength = 1;
}

void updateValue(all_positions_t * catalog, char * value) {
  for (size_t i = 0; i < catalog->size; i++) {
    if (strcmp(catalog->array[i].value, value) == 0) {
      catalog->array[i].strength++;
      return;
    }
  }
  addValuetoCatalog(catalog, value);
}

void keyToValue(char * key, kvarray_t) {
}

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  FILE * f = fopen(inputName, "r");
  if (f == NULL) {
    fprintf(stderr, "could not open %s\n", inputName);
    fail;
  }
  char ** allkeys = NULL;
  char * key = NULL;
  size_t keysz = 0;
  size_t length = 0;
  char * newlineptr = NULL;
  while (getline(&key, &keysz, f) >= 0) {
    newlineptr = strrchr(key, '\n');
    *newlineptr = '\0';
    allkeys = realloc(allkeys, (length + 1) * sizeof(*allkeys));
    allkeys[length] = key;
    length++;
  }
  fclose(f);
  exit(EXIT_SUCCESS);
}
*/

char * computeOutputFileName(const char * inputName) {
  size_t length;
  char * outputName;
  length = strlen(inputName);
  outputName = malloc(length + 8);

  memcpy(outputName, inputName, length);
  memcpy(outputName + length, ".counts", 8);
  return outputName;
}
