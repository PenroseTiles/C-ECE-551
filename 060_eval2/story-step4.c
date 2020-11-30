#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pair.h"
#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 3 && argc != 4) {
    fprintf(stderr, "usage ./a.out [-n] words.txt story.txt\n");
    exit(EXIT_FAILURE);
  }
  if (argc == 4 && strcmp("-n", argv[1]) != 0) {
    fprintf(stderr, "invalid usage");
    exit(EXIT_FAILURE);
  }
  char * word_file = argc == 3 ? argv[1] : argv[2];
  char * story_file = argc == 3 ? argv[2] : argv[3];
  int delete = argc == 3 ? 0 : 1;

  pairarray_t * pairarray = readpairs(word_file);
  catarray_t * catarray = invertMapping(pairarray);
  FILE * f_story = fopen(story_file, "r");
  if (f_story == NULL) {
    fprintf(stderr, "could not open %s\n", story_file);
    exit(EXIT_FAILURE);
  }
  substitute_file(f_story, catarray, delete);

  fclose(f_story);
  free_catarray(catarray);
  freepairs(pairarray);
}
