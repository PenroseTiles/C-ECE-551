#include <stdio.h>
#include <stdlib.h>

#include "pair.h"
#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "cmd line arg missing\n");
    exit(EXIT_FAILURE);
  }
  pairarray_t * pairarray = readpairs(argv[1]);
  catarray_t * catarray = invertMapping(pairarray);
  print_catarray(catarray);
  freepairs(pairarray);
  free_catarray(catarray);
}
