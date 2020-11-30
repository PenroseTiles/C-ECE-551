#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

void check(unsigned x, unsigned y, unsigned correct) {
  if (power(x, y) == correct) {
    return;
  }
  else {
    exit(EXIT_FAILURE);
  }
}

int main() {
  check(1, 0, 1);
  check(1, 1, 1);
  check(2, 2, 4);
  check(5, 1, 5);
  check(5, 2, 25);
  check(4294967295, 1, 4294967295);
  check(2, 5, 32);
  check(10, 3, 1000);
  check(0, 10, 0);
  check(0, 0, 1);
  return EXIT_SUCCESS;
}
