#include "stdio.h"
#include "stdlib.h"

unsigned power(unsigned x, unsigned y);

void helper(unsigned x, unsigned y, unsigned expected_ans) {
  if (power(x, y) != expected_ans) {
    return exit(EXIT_FAILURE);
  }
}

int main() {
  helper(0, 0, 1);
  helper(-1, 0, 1);
  helper(1, 0, 1);
  helper(2, 0, 1);
  helper(2, 2, 4);
  helper(2, 30, 1073741824);
  //  helper(-1, -1, -1);
  helper(-0, -0, 1);
  helper(-0, 0, 1);
  helper(1, 2, 1);
  helper(1, 999999999, 1);
  // helper(1, -999999999, 1);
  helper(999999999, 1, 999999999);
  return EXIT_SUCCESS;
}
