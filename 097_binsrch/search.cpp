#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  while (low + 1 < high) {
    int mid = (low + high) / 2;
    int f_ans = f->invoke(mid);
    if (f_ans > 0) {
      high = mid;
    }
    else if (f_ans == 0) {
      return mid;
    }
    else {
      low = mid;
    }
  }
  return low;
}
