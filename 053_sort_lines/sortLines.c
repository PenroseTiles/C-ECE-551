#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void sort_lines(FILE * f) {
  char ** lines = NULL;
  char * curr = NULL;
  size_t size = 0;
  size_t index = 0;
  while (getline(&curr, &size, f) >= 0) {
    lines = realloc(lines, (index + 1) * sizeof(*lines));
    lines[index] = curr;
    curr = NULL;
    index++;
  }
  free(curr);
  sortData(lines, index);
  for (size_t i = 0; i < index; i++) {
    printf("%s\n", lines[i]);
    free(lines[i]);
  }
  free(lines);
}

int main(int argc, char ** argv) {
  FILE * f;

  if (1 == argc) {
    f = stdin;
    sort_lines(f);
  }
  else {
    for (size_t i = 0; i < argc - 1; i++) {
      f = fopen(argv[i + 1], "r");
      if (f == NULL) {
        fprintf(stderr, "could not open file %s\n", argv[i + 1]);
        exit(EXIT_FAILURE);
      }
      sort_lines(f);
      if (fclose(f) != 0) {
        fprintf(stderr, "could not close file %s\n", argv[i + 1]);
        exit(EXIT_FAILURE);
      }
    }
  }

  return EXIT_SUCCESS;
}
