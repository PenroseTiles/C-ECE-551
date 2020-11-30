#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

void test_fn(int * array, size_t size, size_t answer) {
  size_t ret = maxSeq(array, size);
  if (ret != answer) {
    exit(EXIT_FAILURE);
  }
}

int main() {
  int array1[] = {1, 2, 5, 6, 3, 9, -1};
  size_t size1 = 7;
  test_fn(array1, size1, (size_t)4);
  int array2[] = {1, 1, 1, 1};
  size_t size2 = 4;
  test_fn(array2, size2, (size_t)1);
  int array3[] = {1};
  test_fn(array3, 0, 0);
  int array4[] = {3, 3};
  test_fn(array4, 2, 1);
  int array5[] = {-2147483648, 2147483647};
  test_fn(array5, 2, 2);
  int array6[] = {1, 2, 3, 4, 3, 4, 5, 6, 7, 8};
  test_fn(array6, 10, 6);
  exit(EXIT_SUCCESS);
}
