#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : S21Matrix(3, 3) {}

S21Matrix::S21Matrix(int i, int j) : rows_(i), cols_(j) { allocMatrix(); }

S21Matrix::S21Matrix(const S21Matrix& other)
    : S21Matrix(other.rows_, other.cols_) {
  copyMatrix(other);
}
S21Matrix::S21Matrix(S21Matrix&& other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.cols_ = 0;
  other.rows_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() { destroyMatrix(); }

void S21Matrix::allocMatrix() {
  if (cols_ <= 0 || rows_ <= 0)
    throw std::out_of_range("Indexes of rows or cols out of range");

  matrix_ = new double[rows_ * cols_]{};
}

void S21Matrix::destroyMatrix() { delete[] matrix_; }

bool S21Matrix::isValid() const noexcept {
  return matrix_ != nullptr && cols_ > 0 && rows_ > 0;
}

void S21Matrix::copyMatrix(const S21Matrix& other) {
  if (other.isValid()) {
    int min_cols = std::min(cols_, other.cols_);
    int min_rows = std::min(rows_, other.rows_);
    for (int i = 0; i < min_rows; i++)
      for (int j = 0; j < min_cols; j++) (*this)(i, j) = other(i, j);
  }
}

bool S21Matrix::eqMatrix(const S21Matrix& other) const {
  if (!isValid() || !other.isValid())
    throw std::out_of_range("Non-valid matrix");

  bool isEq = true;
  if (cols_ != other.cols_ || rows_ != other.rows_)
    isEq = false;
  else {
    for (int i = 0; i < rows_ && isEq; i++)
      for (int j = 0; j < cols_ && isEq; j++)
        if (fabs((*this)(i, j) - other(i, j)) > Eps) isEq = false;
  }
  return isEq;
}

void S21Matrix::sumMatrix(const S21Matrix& other) {
  if (!isValid() || !other.isValid())
    throw std::out_of_range("Non-valid matrix");
  if (cols_ != other.cols_ || rows_ != other.rows_)
    throw std::logic_error("Dfferent matrix dimensions");

  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) (*this)(i, j) += other(i, j);
}
void S21Matrix::subMatrix(const S21Matrix& other) {
  if (!isValid() || !other.isValid())
    throw std::out_of_range("Non-valid matrix");
  if (cols_ != other.cols_ || rows_ != other.rows_)
    throw std::logic_error("Dfferent matrix dimensions");

  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) (*this)(i, j) -= other(i, j);
}
void S21Matrix::mulNumber(double num) {
  if (!isValid()) throw std::out_of_range("Non-valid matrix");

  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) (*this)(i, j) *= num;
}
void S21Matrix::mulMatrix(const S21Matrix& other) {
  if (!isValid() || !other.isValid())
    throw std::out_of_range("Non-valid matrix");
  if (cols_ != other.rows_)
    throw std::logic_error(
        "Cols of the first matrix is not equal to the number of rows of the "
        "second matrix");

  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < result.rows_; i++) {
    for (int j = 0; j < result.cols_; j++) {
      double sum = 0;
      for (int k = 0; k < cols_; k++) sum += (*this)(i, k) * other(k, j);
      result(i, j) = sum;
    }
  }
  *this = std::move(result);
}

S21Matrix S21Matrix::transpose() const {
  if (!isValid()) throw std::out_of_range("Non-valid matrix");

  S21Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) result(j, i) = (*this)(i, j);
  return result;
}

S21Matrix S21Matrix::calcComplements() const {
  if (!isValid()) throw std::out_of_range("Non-valid matrix");
  if (cols_ != rows_) throw std::logic_error("The matrix is not square");

  S21Matrix result(cols_, cols_);
  for (int i = 0; i < cols_; i++)
    for (int j = 0; j < cols_; j++)
      result(i, j) = getSubmatrix(j, i).determinant() * pow(-1, i + j);

  return result;
}

double S21Matrix::determinant() const {
  if (!isValid()) throw std::out_of_range("Non-valid matrix");
  if (cols_ != rows_) throw std::logic_error("The matrix is not square");

  double detA = 0;
  if (cols_ == 1)
    detA = (*this)(0, 0);
  else if (cols_ == 2)
    detA = (*this)(0, 0) * (*this)(1, 1) - (*this)(0, 1) * (*this)(1, 0);
  else if (cols_ > 2) {
    for (int i = 0; i < rows_; i++)
      detA += pow(-1, i) * getSubmatrix(i, 0).determinant() * (*this)(0, i);
  }
  return detA;
}

S21Matrix S21Matrix::inverseMatrix() const {
  double detA = determinant();
  if (detA == 0) throw std::logic_error("Matrix determinant is 0");

  S21Matrix result(cols_, cols_);
  if (cols_ == 1)
    result(0, 0) = 1. / (*this)(0, 0);
  else {
    result = calcComplements().transpose();
    result.mulNumber(1. / detA);
  }
  return result;
}
void S21Matrix::setCols(int new_cols) {
  if (new_cols <= 0) throw std::out_of_range("Indexes of cols out of range");
  if (new_cols != cols_) {
    S21Matrix tmp(rows_, new_cols);
    tmp.copyMatrix(*this);
    *this = std::move(tmp);
  }
}
void S21Matrix::setRows(int new_rows) {
  if (new_rows <= 0) throw std::out_of_range("Indexes of rows out of range");
  if (new_rows != rows_) {
    S21Matrix tmp(new_rows, cols_);
    tmp.copyMatrix(*this);
    *this = std::move(tmp);
  }
}

int S21Matrix::getCols() const noexcept { return cols_; }
int S21Matrix::getRows() const noexcept { return rows_; }

double& S21Matrix::operator()(int i, int j) {
  if (!isValid() || i >= rows_ || j >= cols_ || i < 0 || j < 0)
    throw std::out_of_range("Indexes of rows or cols out of range");
  return matrix_[i * cols_ + j];
}

const double& S21Matrix::operator()(int i, int j) const {
  if (!isValid() || i >= rows_ || j >= cols_ || i < 0 || j < 0)
    throw std::out_of_range("Indexes of rows or cols out of range");

  return matrix_[i * cols_ + j];
}

bool S21Matrix::operator==(S21Matrix other) const { return eqMatrix(other); }

bool S21Matrix::operator!=(S21Matrix other) const { return !eqMatrix(other); }

S21Matrix& S21Matrix::operator=(S21Matrix&& other) noexcept {
  std::swap(cols_, other.cols_);
  std::swap(rows_, other.rows_);
  std::swap(matrix_, other.matrix_);

  return *this;
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (!other.isValid()) throw std::out_of_range("Non-valid matrix");
  if (this != &other) {
    S21Matrix tmp(other);
    *this = std::move(tmp);
  }
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix temp(*this);
  temp.sumMatrix(other);
  return temp;
}
S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix temp(*this);
  temp.subMatrix(other);
  return temp;
}
S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix temp(*this);
  temp.mulMatrix(other);
  return temp;
}

S21Matrix S21Matrix::operator*(double number) const {
  S21Matrix temp(*this);
  temp.mulNumber(number);
  return temp;
}

S21Matrix operator*(const double number, const S21Matrix& other) {
  S21Matrix temp(other);
  temp.mulNumber(number);
  return temp;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  sumMatrix(other);
  return *this;
}
S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  subMatrix(other);
  return *this;
}
S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  mulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(double number) {
  mulNumber(number);
  return *this;
}

S21Matrix S21Matrix::getSubmatrix(int k, int l) const {
  int n = 0;
  S21Matrix result(rows_ - 1, cols_ - 1);
  for (int i = 0; i < rows_; i++) {
    if (i == l) continue;
    for (int j = 0; j < cols_; j++) {
      if (j == k) continue;
      result(n / result.cols_, n % result.cols_) = (*this)(i, j);
      n++;
    }
  }
  return result;
}