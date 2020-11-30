#include <stdio.h>
#include <stdlib.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "argc should be 2. Usage: ./out filename\n");
    exit(EXIT_FAILURE);
  }

  char * line = NULL;
  size_t sz = 0;
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "could not open file %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }
  while (getline(&line, &sz, f) >= 0) {
    print_cat2(line);
  }
  if (fclose(f) != 0) {
    fprintf(stderr, "could not close file\n");
    exit(EXIT_FAILURE);
  }
  free(line);
}
