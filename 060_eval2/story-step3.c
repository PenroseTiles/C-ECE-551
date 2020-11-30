#include <stdio.h>
#include <stdlib.h>

#include "pair.h"
#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "cmd line arg missing\n");
    exit(EXIT_FAILURE);
  }
  pairarray_t * pairarray = readpairs(argv[1]);
  FILE * f = fopen(argv[2], "r");
  catarray_t * catarray = invertMapping(pairarray);
  substitute_file(f, catarray, 0);
  freepairs(pairarray);
  free_catarray(catarray);
  fclose(f);
}
