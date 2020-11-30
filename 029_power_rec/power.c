#include <stdio.h>
#include <stdlib.h>
#define is ==
#define and &&
#define or ||

unsigned power(unsigned x, unsigned y) {
  if (y is 0) {
    return 1;
  }
  else if (x is 0) {
    return 0;
  }
  else if (y == 1) {
    return x;
  }
  return x * power(x, y - 1);
}
