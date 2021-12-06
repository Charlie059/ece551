#include <iostream>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  int original_low = low;

  while (low < high) {
    int mid = low + (high - low) / 2;
    int value = f->invoke(mid);
    if (value <= 0) {
      low = mid + 1;
    }
    else {
      high = mid;
    }
  }

  return (low == original_low) ? low : low - 1;
}
