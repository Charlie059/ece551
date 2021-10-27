#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>

//YOUR CODE GOES HERE!
template<typename T>
class Matrix {
 private:
  int numRows;
  int numColumns;
  std::vector<std::vector<T> > rows;

 public:
  Matrix();
  Matrix(int r, int c);
  Matrix(const Matrix & rhs);
  Matrix & operator=(const Matrix & rhs);
  int getRows() const;
  int getColumns() const;
  const std::vector<T> & operator[](int index) const;
  std::vector<T> & operator[](int index);
  bool operator==(const Matrix & rhs) const;
  Matrix operator+(const Matrix & rhs) const;

  template<typename U>
  friend std::ostream & operator<<(std::ostream & s, const Matrix<U> & rhs);
};

template<typename T>
Matrix<T>::Matrix() : numRows(0), numColumns(0), rows() {
}

template<typename T>
Matrix<T>::Matrix(int r, int c) : numRows(r), numColumns(c) {
  // resize the rows
  rows.resize(r);
  for (int i = 0; i < numRows; i++) {
    rows[i].resize(c);
  }
}

template<typename T>
Matrix<T>::Matrix(const Matrix & rhs) : numRows(rhs.numRows), numColumns(rhs.numColumns) {
  rows = rhs.rows;
}
template<typename T>

Matrix<T> & Matrix<T>::operator=(const Matrix<T> & rhs) {
  numRows = rhs.numRows;
  numColumns = rhs.numColumns;
  rows = rhs.rows;
  return *this;
}
template<typename T>
int Matrix<T>::getRows() const {
  return numRows;
}
template<typename T>
int Matrix<T>::getColumns() const {
  return numColumns;
}

template<typename T>
const std::vector<T> & Matrix<T>::operator[](int index) const {
  assert((0 <= index) && (index < numRows));
  return rows[index];
}

template<typename T>
std::vector<T> & Matrix<T>::operator[](int index) {
  assert((0 <= index) && (index < numRows));
  return rows[index];
}

template<typename T>
bool Matrix<T>::operator==(const Matrix & rhs) const {
  if ((numRows != rhs.numRows) || (numColumns != rhs.numColumns) || (rows != rhs.rows)) {
    return false;
  }
  return true;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix & rhs) const {
  assert((numRows == rhs.numRows) && (numColumns == rhs.numColumns));
  Matrix<T> ans(numRows, numColumns);
  ans.numColumns = numColumns;
  ans.numRows = numRows;
  typename std::vector<std::vector<T> > rows;

  for (int i = 0; i < numRows; i++) {
    std::vector<T> row;
    for (int j = 0; j < numColumns; j++) {
      T temp = rhs[i][j] + this->rows[i][j];
      row.push_back(temp);
    }
    rows.push_back(row);
  }
  ans.rows = rows;

  return ans;
}

template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  s << "[ ";
  typename std::vector<std::vector<T> >::const_iterator it;
  for (it = rhs.rows.begin(); it != rhs.rows.end(); ++it) {
    if (it != rhs.rows.begin()) {
      s << ",\n";
    }
    s << "{";
    typename std::vector<T>::const_iterator it_it;
    for (it_it = (*it).begin(); it_it != (*it).end(); ++it_it) {
      if (it_it != (*it).begin()) {
        s << ", ";
      }
      s << *it_it;
    }
    s << "}";
  }
  s << " ]";
  return s;
}

#endif
