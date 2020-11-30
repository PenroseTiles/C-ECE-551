#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define size 10
#define fail exit(EXIT_FAILURE)

void print_matrix(char arr[size][size], FILE * f) {
  for (size_t i = 0; i < 10; i++) {
    for (size_t j = 0; j < 10; j++) {
      fprintf(f, "%c", arr[i][j]);
    }
    fprintf(f, "\n");
  }
}

void read_matrix(FILE * f) {
  int ch;
  char arr[size][size];
  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size; j++) {
      ch = fgetc(f);
      switch (ch) {
        case EOF:
          fprintf(stderr, "unexpected EOF\n");
          fail;
        case '\n':
          fprintf(stderr, "incorrect format, j is %lu\n", j);
          fail;
        default:
          if (j < size) {
            arr[i][j] = ch;
            break;
          }
          else {
            fprintf(stderr, "line too long");
            fail;
          }
      }
    }
    ch = fgetc(f);
    if (ch == '\n' || (i == size - 1 && ch == EOF)) {
      continue;
    }
    else {
      fprintf(stderr, "incorrect input received");
      fail;
    }
  }
  ch = fgetc(f);
  if (ch != EOF) {
    fprintf(stderr, "too many lines");
    fail;
  }
  //now rotate

  char temp;
  //reflect horizontally
  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size / 2; j++) {
      temp = arr[i][j];
      arr[i][j] = arr[i][size - j - 1];
      arr[i][size - j - 1] = temp;
    }
  }
  //reflect along diagonal

  for (size_t i = 0; i < size; i++) {
    for (size_t j = size - 1 - i; j < size; j++) {
      temp = arr[i][j];
      arr[i][j] = arr[size - 1 - j][size - 1 - i];
      arr[size - 1 - j][size - 1 - i] = temp;
    }
  }

  print_matrix(arr, stdout);
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "argc must be 2");
    exit(EXIT_FAILURE);
  }

  char * filename = argv[1];
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "file open failed");
    exit(EXIT_FAILURE);
  }

  read_matrix(f);
  if (fclose(f) != 0) {
    fprintf(stderr, "failed to close %s\n", filename);
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
