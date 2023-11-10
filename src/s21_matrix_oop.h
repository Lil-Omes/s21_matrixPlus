#ifndef S21_MATRIX_PLUS
#define S21_MATRIX_PLUS

#include <cmath>
#include <iostream>

#define Eps 1e-7

class S21Matrix {
 public:
  S21Matrix();                        // Default constructor
  S21Matrix(int i, int j);            // Parametrized constructor
  S21Matrix(const S21Matrix& other);  // Copy constructor
  S21Matrix(S21Matrix&& other);       // Move constructor
  ~S21Matrix();                       // Destructor

  bool eqMatrix(const S21Matrix& other) const;
  void sumMatrix(const S21Matrix& other);
  void subMatrix(const S21Matrix& other);
  void mulNumber(const double num);
  void mulMatrix(const S21Matrix& other);
  S21Matrix transpose() const;
  S21Matrix calcComplements() const;
  double determinant() const;
  S21Matrix inverseMatrix() const;

  void setCols(int cols);
  void setRows(int rows);
  int getCols() const noexcept;
  int getRows() const noexcept;
  double& operator()(int i, int j);
  const double& operator()(int i, int j) const;

  bool operator==(const S21Matrix other) const;
  bool operator!=(const S21Matrix other) const;
  S21Matrix& operator=(S21Matrix&& other) noexcept;
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix operator*(const S21Matrix& other) const;
  S21Matrix operator*(const double number) const;
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double number);

 private:
  int rows_ = 0, cols_ = 0;
  double* matrix_ = nullptr;
  void allocMatrix();
  void destroyMatrix();
  void copyMatrix(const S21Matrix& other);
  S21Matrix getSubmatrix(int k, int l) const;
  bool isValid() const noexcept;
};

S21Matrix operator*(const double number, const S21Matrix& other);

#endif  // S21_MATRIX_PLUS
