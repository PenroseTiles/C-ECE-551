#include <stdio.h>
#include <stdlib.h>

#define max(a, b) a > b ? a : b

size_t maxSeq(int * array, size_t n) {
  size_t curr = 1;
  size_t maxlen = 1;
  if (n <= 1) {
    return max(n, 0);
  }
  else {
    for (size_t i = 1; i < n; i++) {
      if (array[i] > array[i - 1]) {
        curr++;
        maxlen = max(curr, maxlen);
      }
      else {
        curr = 1;
      }
    }
  }
  return maxlen;
}
