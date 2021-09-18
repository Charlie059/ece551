#include "limits.h"
#include "stdio.h"
#include "stdlib.h"

size_t maxSeq(int * array, size_t n) {
  int buffer = INT_MIN;
  size_t max_sub_seq = 0;
  size_t current_sub_seq = 0;

  if (array == NULL) {
    return 0;
  }

  for (size_t i = 0; i < n; i++) {
    if (buffer < array[i]) {
      buffer = array[i];
      current_sub_seq += 1;
    }
    else {
      if (max_sub_seq < current_sub_seq) {
        max_sub_seq = current_sub_seq;
      }
      current_sub_seq = 1;
      buffer = array[i];
    }
  }

  if (max_sub_seq < current_sub_seq) {
    max_sub_seq = current_sub_seq;
  }
  return max_sub_seq;
}
