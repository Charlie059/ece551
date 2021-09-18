#include "limits.h"
#include "stdio.h"
#include "stdlib.h"
size_t maxSeq(int * array, size_t n);

void helper(int test[], size_t exp_out, size_t n) {
  size_t test_output = maxSeq(test, n);

  if (test_output != exp_out) {
    printf("Fail in test\n:");
    for (size_t i = 0; i < n; i++) {
      printf("%d ", test[i]);
    }
    printf("\n");
    printf("EXP: %zu, Result: %zu\n", exp_out, test_output);
    exit(EXIT_FAILURE);
  }
}
int main() {
  int test0[] = {0};
  int test1[] = {0, 0};
  int test2[] = {0, 0, 0};
  int test3[] = {1, 2};
  int test4[] = {-1, 0, 1, 2, 3};
  int test5[] = {2, 1};
  int test6[] = {3, 2, 1};
  int test7[] = {2, 1, 3};
  int test8[] = {0, -1};
  int test9[] = {-4, -3, -1, 1};
  int test10[] = {-1, -4, 1, -3};
  int test11[] = {1, 2, 2, 2, 3};
  int test12[] = {1, -1, -2, -1, 1};
  int test13[] = {INT_MIN, 0, INT_MAX};
  int test14[] = {2, 2, 3, 3, -1, 4};
  int test15[] = {INT_MIN, INT_MAX};
  int test16[] = {1, 3, 3, 4, 4, 5};
  int test17[] = {1};
  int test18[] = {1, 1, 1, 2, 2, 3, 4, 5};

  helper(test0, 1, 1);
  helper(test1, 1, 2);
  helper(test2, 1, 3);
  helper(test3, 2, 2);
  helper(test4, 5, 5);
  helper(test5, 1, 2);
  helper(test6, 1, 3);
  helper(test7, 2, 3);
  helper(test8, 1, 2);
  helper(test9, 4, 4);
  helper(test10, 2, 4);
  helper(test11, 2, 5);
  helper(test12, 3, 5);
  helper(test13, 3, 3);
  helper(test14, 2, 6);
  helper(test15, 2, 2);
  helper(test16, 2, 6);
  helper(test17, 1, 1);
  helper(test18, 4, 8);
  helper(NULL, 0, 0);
  return EXIT_SUCCESS;
}
