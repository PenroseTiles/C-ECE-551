#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int get_highest_freq(int * freq) {
  int maxfreq = 0;
  int maxchar = 0;
  for (int i = 0; i < 26; i++) {
    if (freq[i] >= maxfreq) {
      maxfreq = freq[i];
      maxchar = i;
    }
  }
  if (maxfreq == 0) {
    return -1;
  }
  else {
    return maxchar;
  }
}

void build_histogram(int * freq, FILE * f) {
  int c;

  while ((c = fgetc(f)) != EOF) {
    //printf("%c", c);
    if (isalpha(c)) {
      c = tolower(c);
      c -= 'a';
      //c %= 26;
      freq[c] += 1;
    }
  }
  return;
}

int main(int argc, char ** argv) {
  int freq[26];
  if (argc != 2) {
    fprintf(stderr, "Please specify file name");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < 26; i++) {
    freq[i] = 0;
  }

  FILE * f = fopen(argv[1], "r");

  if (f == NULL) {
    fprintf(stderr, "Failed to open %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }
  build_histogram(freq, f);

  /*for (int i = 0; i < 26; i++) {
    printf("%d\n", freq[i]);
  }
  */
  int highest = get_highest_freq(freq);
  if (highest < 0) {
    fprintf(stderr, "EMPTY FILE");
    exit(EXIT_FAILURE);
  }

  printf("%d\n", (highest + 26 - 4) % 26);
  /*
  if (fclose(f) != 0) {
    perror("Failed to close file argv[1]");
    exit(EXIT_FAILURE);
  }
  */
  exit(EXIT_SUCCESS);
}
