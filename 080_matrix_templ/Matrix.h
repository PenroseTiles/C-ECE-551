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
  std::vector<T> * rows;

 public:
  Matrix() : numRows(0), numColumns(0), rows(NULL) {}
  Matrix(int r, int c) : numRows(r), numColumns(c) {
    rows = new std::vector<T>[numRows]();
    //TODO how do I create a std::vector<T> of size numColumns initialized to default values?
    for (int i = 0; i < numRows; i++) {
      rows[i] = std::vector<T>(numColumns, T());
    }
  }

  Matrix(const Matrix & rhs) : numRows(rhs.numRows), numColumns(rhs.numColumns) {
    rows = new std::vector<T>[numRows]();
    for (int i = 0; i < numRows; i++) {
      rows[i] = rhs.rows[i];
    }
    return;
  }

  ~Matrix() { delete[] rows; }

  Matrix & operator=(const Matrix & rhs) {
    if (*this == rhs) {
      return *this;
    }
    delete[] rows;
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
    rows = new std::vector<T>[numRows]();
    //std::cout << "copy assigning matrix" << std::endl;
    for (int i = 0; i < numRows; i++) {
      rows[i] = rhs.rows[i];
    }
    //std::cout << "done copying matrix" << std::endl;
    return *this;
  }

  int getRows() const { return numRows; }
  int getColumns() const { return numColumns; }
  const std::vector<T> & operator[](int index) const {
    assert(index >= 0 && index < numRows);
    return rows[index];
  }
  std::vector<T> & operator[](int index) {
    assert(index >= 0 && index < numRows);
    return rows[index];
  }

  bool operator==(const Matrix & rhs) const {
    if (numRows != rhs.numRows || numColumns != rhs.numColumns) {
      return false;
    }
    for (int i = 0; i < numRows; i++) {
      if (rows[i] != rhs.rows[i]) {
        return false;
      }
    }
    return true;
  }

  Matrix operator+(const Matrix & rhs) const {
    assert(numRows == rhs.numRows && numColumns == rhs.numColumns);
    Matrix ans(numRows, numColumns);
    for (int i = 0; i < numRows; i++) {
      ans.rows[i] = rows[i] + rhs.rows[i];
    }
    return ans;
  }
};

template<typename T>
std::ostream & operator<<(std::ostream & s, const std::vector<T> & rhs) {
  bool first = true;

  s << '{';
  for (unsigned i = 0; i < rhs.size(); i++) {
    if (first) {
      first = false;
    }
    else {
      s << ", ";
    }
    s << rhs[i];
  }
  s << '}';
  return s;
}

template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  s << "[ ";
  for (int i = 0; i < rhs.getRows(); i++) {
    s << rhs[i];
    if (i < rhs.getRows() - 1) {
      s << ",\n";
    }
  }
  s << " ]";
  return s;
}

template<typename T>
std::vector<T> operator+(std::vector<T> & lhs, std::vector<T> & rhs) {
  assert(lhs.size() == rhs.size());
  std::vector<T> ans(lhs.size(), T());
  for (unsigned i = 0; i < lhs.size(); i++) {
    ans[i] = lhs[i] + rhs[i];
  }
  return ans;
}

#endif
