#include <assert.h>

#include <cmath>
#include <cstdio>
#include <cstdlib>

#include "function.h"
class CountedIntFn : public Function<int, int> {
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n),
      f(fn),
      mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

int binarySearchForZero(Function<int, int> * f, int low, int high);

void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  int n = 1;
  if (high > low)
    n = log2(high - low) + 1;

  CountedIntFn * wrap_func = new CountedIntFn(n, f, mesg);
  int ans = binarySearchForZero(wrap_func, low, high);
  assert(ans == expected_ans);
}

class sthFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return arg; }
};

int main() {
  sthFunction * sth = new sthFunction();
  check(sth, -2, 4, 0, "ok");
  check(sth, -6, -1, -2, "all negative\n");
  check(sth, 2, 10, 2, "all positive\n");
  check(sth, 0, 4, 0, "inclusive zero\n");
  check(sth, -4, 0, -1, "exclusive zero\n");
  return EXIT_SUCCESS;
}
