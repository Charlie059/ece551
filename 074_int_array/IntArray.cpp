#include "IntArray.h"

#include <assert.h>

#include <ostream>

IntArray::IntArray() {
  data = NULL;
  numElements = 0;
}
IntArray::IntArray(int n) {
  data = new int[n];
  numElements = n;
}

IntArray::IntArray(const IntArray & rhs) :
    data(new int[rhs.numElements]),
    numElements(rhs.numElements) {
  for (int i = 0; i < numElements; i++) {
    data[i] = rhs.data[i];
  }
}
IntArray::~IntArray() {
  delete[] data;
}

IntArray & IntArray::operator=(const IntArray & rhs) {
  if (this != &rhs) {
    delete[] data;
    data = new int[rhs.numElements];
    numElements = rhs.numElements;
  }
}
const int & IntArray::operator[](int index) const {
}
int & IntArray::operator[](int index) {
}

int IntArray::size() const {
}

bool IntArray::operator==(const IntArray & rhs) const {
}

bool IntArray::operator!=(const IntArray & rhs) const {
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
}