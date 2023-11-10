#include <gtest/gtest.h>

#include "../s21_matrix_oop.h"

TEST(CreateMatrix1, StandartConstructor) {
  S21Matrix matrix_a;
  ASSERT_TRUE(matrix_a.getCols() == 3);
  ASSERT_TRUE(matrix_a.getRows() == 3);
}

TEST(CreateMatrix2, ParamConstr) { ASSERT_NO_THROW(S21Matrix matrix(2, 2)); }

TEST(CreateMatrix3, ParamConstWithWrongSizes) {
  EXPECT_THROW(S21Matrix matrix(-1, 2), std::out_of_range);
}

TEST(CreateMatrix4, MoveConstr) {
  S21Matrix matrix_a(2, 2);
  ASSERT_NO_THROW(S21Matrix matrix_b = std::move(matrix_a));
}

TEST(CreateMatrix5, CopyConstr) {
  S21Matrix matrix_a(2, 2);
  ASSERT_NO_THROW(S21Matrix matrix_b(matrix_a));
}

TEST(eqMatrix1, EqualMatrix) {
  S21Matrix matrix_a(3, 3);
  S21Matrix matrix_b(3, 3);
  matrix_a(0, 0) = 1;
  matrix_a(0, 1) = 2;
  matrix_a(0, 2) = 3;
  matrix_a(1, 0) = 4;
  matrix_a(1, 1) = 5;
  matrix_a(1, 2) = 6;
  matrix_a(2, 0) = 7;
  matrix_a(2, 1) = 8;
  matrix_a(2, 2) = 9;
  matrix_b(0, 0) = 1;
  matrix_b(0, 1) = 2;
  matrix_b(0, 2) = 3;
  matrix_b(1, 0) = 4;
  matrix_b(1, 1) = 5;
  matrix_b(1, 2) = 6;
  matrix_b(2, 0) = 7;
  matrix_b(2, 1) = 8;
  matrix_b(2, 2) = 9;

  ASSERT_TRUE(matrix_a.eqMatrix(matrix_b));
}
TEST(eqMatrix2, NonEqualSizeOfMatrix) {
  S21Matrix matrix_a(3, 3);
  S21Matrix matrix_b(2, 2);
  ASSERT_FALSE(matrix_a == matrix_b);
}
TEST(eqMatrix3, NonEqMatrix) {
  S21Matrix matrix_a(1, 3);
  matrix_a(0, 0) = 1;
  matrix_a(0, 1) = 2;
  matrix_a(0, 2) = 3;
  S21Matrix matrix_b(2, 2);
  matrix_b(0, 0) = 1;
  matrix_b(0, 1) = 2;
  matrix_b(1, 0) = 3;
  matrix_b(1, 1) = 4;
  ASSERT_TRUE(matrix_a != matrix_b);
}

TEST(eqMatrix4, EqMatrixWithEps) {
  S21Matrix matrix_a(3, 3);
  S21Matrix matrix_b(3, 3);
  matrix_a(0, 0) = .0000007;
  matrix_a(0, 1) = 2;
  matrix_a(0, 2) = 3;
  matrix_a(1, 0) = 4;
  matrix_a(1, 1) = 5;
  matrix_a(1, 2) = 6;
  matrix_a(2, 0) = 7;
  matrix_a(2, 1) = 8;
  matrix_a(2, 2) = 9;
  matrix_b(0, 0) = .0000006;
  matrix_b(0, 1) = 2;
  matrix_b(0, 2) = 3;
  matrix_b(1, 0) = 4;
  matrix_b(1, 1) = 5;
  matrix_b(1, 2) = 6;
  matrix_b(2, 0) = 7;
  matrix_b(2, 1) = 8;
  matrix_b(2, 2) = 9;

  ASSERT_TRUE(matrix_a.eqMatrix(matrix_b));
}

TEST(eqMatrix5, NonEqualMatrixWithEqs) {
  S21Matrix matrix_a(3, 3);
  S21Matrix matrix_b(3, 3);
  matrix_a(0, 0) = .000007;
  matrix_a(0, 1) = 2;
  matrix_a(0, 2) = 3;
  matrix_a(1, 0) = 4;
  matrix_a(1, 1) = 5;
  matrix_a(1, 2) = 6;
  matrix_a(2, 0) = 7;
  matrix_a(2, 1) = 8;
  matrix_a(2, 2) = 9;
  matrix_b(0, 0) = .000006;
  matrix_b(0, 1) = 2;
  matrix_b(0, 2) = 3;
  matrix_b(1, 0) = 4;
  matrix_b(1, 1) = 5;
  matrix_b(1, 2) = 6;
  matrix_b(2, 0) = 7;
  matrix_b(2, 1) = 8;
  matrix_b(2, 2) = 9;

  ASSERT_FALSE(matrix_a.eqMatrix(matrix_b));
}

TEST(SumMatrix1, SumMatrixTrue) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 3.14;
  matrix_a(0, 1) = 0.56;
  matrix_a(1, 0) = -69.3;
  matrix_a(1, 1) = 0;

  matrix_b(0, 0) = -78.14;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -0.3;
  matrix_b(1, 1) = 2;

  result(0, 0) = -75;
  result(0, 1) = 0.56;
  result(1, 0) = -69.6;
  result(1, 1) = 2;
  matrix_a.sumMatrix(matrix_b);
  ASSERT_TRUE(matrix_a == result);
}
TEST(SumMatrix2, SumNonEqMatrix) {
  S21Matrix matrix_a(1, 2);
  S21Matrix matrix_b(2, 2);

  matrix_a(0, 0) = 1;
  matrix_a(0, 1) = 2;

  matrix_b(0, 0) = 1;
  matrix_b(0, 1) = 2;
  matrix_b(1, 0) = 3;
  matrix_b(1, 1) = 4;

  EXPECT_THROW(matrix_a.sumMatrix(matrix_b), std::logic_error);
}
TEST(SubMatrix1, SubMatrixTrue) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 1;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = 3;
  matrix_a(1, 1) = 4;

  matrix_b(0, 0) = 1;
  matrix_b(0, 1) = 1;
  matrix_b(1, 0) = -1;
  matrix_b(1, 1) = -1;

  result(0, 0) = 0;
  result(0, 1) = 1;
  result(1, 0) = 4;
  result(1, 1) = 5;

  matrix_a.subMatrix(matrix_b);

  ASSERT_TRUE(matrix_a == result);
}
TEST(SubMatrix2, SubNonEqMatrix) {
  S21Matrix matrix_a(1, 2);
  S21Matrix matrix_b(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3;
  matrix_b(1, 1) = 2;

  EXPECT_THROW(matrix_a.subMatrix(matrix_b), std::logic_error);
}
TEST(MulNumber1, MulNumberTrue) {
  S21Matrix matrix_a(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = -78.14;
  matrix_a(0, 1) = 0;
  matrix_a(1, 0) = -0.3;
  matrix_a(1, 1) = 2;

  result(0, 0) = -781.4;
  result(0, 1) = 0;
  result(1, 0) = -3;
  result(1, 1) = 20;

  matrix_a.mulNumber(10);

  ASSERT_TRUE(matrix_a == result);
}
TEST(MulMatrix1, MulMatrixTrue) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6.6;
  matrix_a(1, 1) = 0;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3.5;
  matrix_b(1, 1) = 2;

  result(0, 0) = -28;
  result(0, 1) = 4;
  result(1, 0) = 46.2;
  result(1, 1) = 0;

  matrix_a.mulMatrix(matrix_b);

  ASSERT_TRUE(matrix_a == result);
}
TEST(MulMatrix2, MulNonEqMatrix) {
  S21Matrix matrix_a(2, 1);
  S21Matrix matrix_b(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(1, 0) = -6.6;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3.5;
  matrix_b(1, 1) = 2;

  EXPECT_THROW(matrix_a.mulMatrix(matrix_b), std::logic_error);
}

TEST(MulMatrix3, MulNoSquareMatrix) {
  S21Matrix matrix_a(2, 1);
  S21Matrix matrix_b(1, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(1, 0) = 2;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 1;

  result(0, 0) = -21;
  result(0, 1) = 3;
  result(1, 0) = -14;
  result(1, 1) = 2;

  matrix_a.mulMatrix(matrix_b);

  ASSERT_TRUE(matrix_a == result);
}
TEST(OperatorParentheses1, MatrixGetterTrue) {
  S21Matrix matrix_a(2, 2);

  matrix_a(0, 0) = 1;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = 3;
  matrix_a(1, 1) = 4;
  ASSERT_EQ(matrix_a(0, 1), 2);
}
TEST(OperatorParentheses2, MatrixGetterNonEq) {
  S21Matrix matrix_a(2, 2);

  matrix_a(0, 0) = 1;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = 3;
  matrix_a(1, 1) = 4;
  ASSERT_NE(matrix_a(0, 1), 10);
}
TEST(OperatorParentheses3, MatrixSetterWrongIndexes) {
  S21Matrix matrix_a(2, 2);
  EXPECT_THROW(matrix_a(3, 0) = 1, std::out_of_range);
}

TEST(OperatorParentheses4, MatrixGetterWrongIndexes) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  EXPECT_THROW(matrix_b(1, 1) = matrix_a(33, 22), std::out_of_range);
}
TEST(OperatorSumMatrix1, TrueSumOperator) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 3.14;
  matrix_a(0, 1) = 0.56;
  matrix_a(1, 0) = -69.3;
  matrix_a(1, 1) = 0;

  matrix_b(0, 0) = -78.14;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -0.3;
  matrix_b(1, 1) = 2;

  result(0, 0) = -75;
  result(0, 1) = 0.56;
  result(1, 0) = -69.6;
  result(1, 1) = 2;
  matrix_a += matrix_b;
  ASSERT_TRUE(matrix_a == result);
}
TEST(OperatorSumMatrix2, OperatorSumWithNoEqSizesMatrix) {
  S21Matrix matrix_a(1, 2);
  S21Matrix matrix_b(2, 2);

  matrix_a(0, 0) = 1;
  matrix_a(0, 1) = 2;

  matrix_b(0, 0) = 1;
  matrix_b(0, 1) = 2;
  matrix_b(1, 0) = 3;
  matrix_b(1, 1) = 4;

  EXPECT_THROW(matrix_a + matrix_b, std::logic_error);
}
TEST(OperatorSubMatrix1, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 1;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = 3;
  matrix_a(1, 1) = 4;

  matrix_b(0, 0) = 1;
  matrix_b(0, 1) = 1;
  matrix_b(1, 0) = -1;
  matrix_b(1, 1) = -1;

  result(0, 0) = 0;
  result(0, 1) = 1;
  result(1, 0) = 4;
  result(1, 1) = 5;

  matrix_a -= matrix_b;

  ASSERT_TRUE(matrix_a == result);
}
TEST(OperatorSubMatrix2, False) {
  S21Matrix matrix_a(1, 2);
  S21Matrix matrix_b(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3;
  matrix_b(1, 1) = 2;

  EXPECT_THROW(matrix_a - matrix_b, std::logic_error);
}

TEST(OperatorMulNumber1, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = -78.14;
  matrix_a(0, 1) = 0;
  matrix_a(1, 0) = -0.3;
  matrix_a(1, 1) = 2;

  result(0, 0) = -781.4;
  result(0, 1) = 0;
  result(1, 0) = -3;
  result(1, 1) = 20;

  matrix_a *= 10;

  ASSERT_TRUE(matrix_a == result);
}

TEST(OperatorMulNumber2, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = -78.14;
  matrix_a(0, 1) = 0;
  matrix_a(1, 0) = -0.3;
  matrix_a(1, 1) = 2;

  result(0, 0) = -781.4;
  result(0, 1) = 0;
  result(1, 0) = -3;
  result(1, 1) = 20;

  matrix_a = matrix_a * 10;

  ASSERT_TRUE(matrix_a == result);
}

TEST(OperatorMulNumber3, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = -78.14;
  matrix_a(0, 1) = 0;
  matrix_a(1, 0) = -0.3;
  matrix_a(1, 1) = 2;

  result(0, 0) = -781.4;
  result(0, 1) = 0;
  result(1, 0) = -3;
  result(1, 1) = 20;

  matrix_a = 10 * matrix_a;

  ASSERT_TRUE(matrix_a == result);
}
TEST(OperatorMulMatrix1, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6.6;
  matrix_a(1, 1) = 0;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3.5;
  matrix_b(1, 1) = 2;

  result(0, 0) = -28;
  result(0, 1) = 4;
  result(1, 0) = 46.2;
  result(1, 1) = 0;

  matrix_a *= matrix_b;

  ASSERT_TRUE(matrix_a == result);
}
TEST(OperatorMulMatrix2, False) {
  S21Matrix matrix_a(2, 1);
  S21Matrix matrix_b(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(1, 0) = -6.6;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3.5;
  matrix_b(1, 1) = 2;

  EXPECT_THROW(matrix_a *= matrix_b, std::logic_error);
}

TEST(OperatorMulMatrix3, True) {
  S21Matrix matrix_a(2, 1);
  S21Matrix matrix_b(1, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(1, 0) = 2;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 1;

  result(0, 0) = -21;
  result(0, 1) = 3;
  result(1, 0) = -14;
  result(1, 1) = 2;

  matrix_a *= matrix_b;

  ASSERT_TRUE(matrix_a == result);
}

TEST(OperatorMulMatrix4, True) {
  S21Matrix matrix_a(2, 1);
  S21Matrix matrix_b(1, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(1, 0) = 2;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 1;

  result(0, 0) = -21;
  result(0, 1) = 3;
  result(1, 0) = -14;
  result(1, 1) = 2;

  matrix_a = matrix_a * matrix_b;

  ASSERT_TRUE(matrix_a.eqMatrix(result));
}

TEST(OperatorEqMatrix, True) {
  S21Matrix matrix_a(4, 3);
  S21Matrix matrix_b(5, 3);
  matrix_a = matrix_b;
  ASSERT_TRUE(matrix_a == matrix_b);
}

TEST(Transpose1, True) {
  S21Matrix matrix_a(4, 3);
  S21Matrix result(3, 4);

  matrix_a(0, 0) = 1;
  matrix_a(0, 1) = 2;
  matrix_a(0, 2) = 3;
  matrix_a(1, 0) = 4;
  matrix_a(1, 1) = 5;
  matrix_a(1, 2) = 6;
  matrix_a(2, 0) = 7;
  matrix_a(2, 1) = 8;
  matrix_a(2, 2) = 9;
  matrix_a(3, 0) = 10;
  matrix_a(3, 1) = 11;
  matrix_a(3, 2) = 12;

  result(0, 0) = 1;
  result(0, 1) = 4;
  result(0, 2) = 7;
  result(0, 3) = 10;
  result(1, 0) = 2;
  result(1, 1) = 5;
  result(1, 2) = 8;
  result(1, 3) = 11;
  result(2, 0) = 3;
  result(2, 1) = 6;
  result(2, 2) = 9;
  result(2, 3) = 12;
  S21Matrix res = matrix_a.transpose();
  ASSERT_TRUE(res.eqMatrix(result));
}

TEST(Inverse1, False) {
  S21Matrix matrix_a(4, 3);

  matrix_a(0, 0) = 1;
  matrix_a(0, 1) = 2;
  matrix_a(0, 2) = 3;
  matrix_a(1, 0) = 4;
  matrix_a(1, 1) = 5;
  matrix_a(1, 2) = 6;
  matrix_a(2, 0) = 7;
  matrix_a(2, 1) = 8;
  matrix_a(2, 2) = 9;
  matrix_a(3, 0) = 10;
  matrix_a(3, 1) = 11;
  matrix_a(3, 2) = 12;

  EXPECT_THROW(matrix_a.inverseMatrix(), std::logic_error);
}
TEST(Inverse2, True) {
  S21Matrix matrix_a(3, 3);
  S21Matrix result(3, 3);

  matrix_a(0, 0) = -1;
  matrix_a(0, 1) = 1;
  matrix_a(0, 2) = -7;
  matrix_a(1, 0) = 6;
  matrix_a(1, 1) = 2;
  matrix_a(1, 2) = 6;
  matrix_a(2, 0) = 3;
  matrix_a(2, 1) = 0;
  matrix_a(2, 2) = 1;

  result(0, 0) = 2;
  result(0, 1) = -1;
  result(0, 2) = 20;
  result(1, 0) = 12;
  result(1, 1) = 20;
  result(1, 2) = -36;
  result(2, 0) = -6;
  result(2, 1) = 3;
  result(2, 2) = -8;
  result *= 1. / 52;
  matrix_a = matrix_a.inverseMatrix();

  ASSERT_TRUE(matrix_a == result);
}
TEST(Inverse3, False) {
  S21Matrix matrix_a(3, 3);
  matrix_a(0, 0) = 1;
  matrix_a(0, 1) = 2;
  matrix_a(0, 2) = 3;
  matrix_a(1, 0) = 4;
  matrix_a(1, 1) = 5;
  matrix_a(1, 2) = 6;
  matrix_a(2, 0) = 7;
  matrix_a(2, 1) = 8;
  matrix_a(2, 2) = 9;

  EXPECT_THROW(matrix_a.inverseMatrix(), std::logic_error);
}

TEST(Inverse4, True) {
  S21Matrix matrix_a(1, 1);
  S21Matrix result(1, 1);

  matrix_a(0, 0) = 5;

  result(0, 0) = .2;

  matrix_a = matrix_a.inverseMatrix();

  ASSERT_TRUE(matrix_a == result);
}
TEST(Get1, True) {
  S21Matrix matrix_a(3, 3);

  ASSERT_EQ(matrix_a.getRows(), 3);
  ASSERT_EQ(matrix_a.getCols(), 3);
}
TEST(Set1, True) {
  S21Matrix matrix_a(3, 3);
  S21Matrix result(3, 2);

  matrix_a(0, 0) = 2;
  matrix_a(0, 1) = 5;
  matrix_a(0, 2) = 7;
  matrix_a(1, 0) = 6;
  matrix_a(1, 1) = 3;
  matrix_a(1, 2) = 4;
  matrix_a(2, 0) = 5;
  matrix_a(2, 1) = -2;
  matrix_a(2, 2) = -3;

  result(0, 0) = 2;
  result(0, 1) = 5;

  result(1, 0) = 6;
  result(1, 1) = 3;

  result(2, 0) = 5;
  result(2, 1) = -2;
  matrix_a.setCols(2);

  ASSERT_TRUE(matrix_a.eqMatrix(result));
}
TEST(Set2, True) {
  S21Matrix matrix_b(3, 3);
  S21Matrix result_b(2, 3);

  matrix_b(0, 0) = 2;
  matrix_b(0, 1) = 5;
  matrix_b(0, 2) = 7;
  matrix_b(1, 0) = 6;
  matrix_b(1, 1) = 3;
  matrix_b(1, 2) = 4;
  matrix_b(2, 0) = 5;
  matrix_b(2, 1) = -2;
  matrix_b(2, 2) = -3;

  result_b(0, 0) = 2;
  result_b(0, 1) = 5;
  result_b(0, 2) = 7;
  result_b(1, 0) = 6;
  result_b(1, 1) = 3;
  result_b(1, 2) = 4;

  matrix_b.setRows(2);
  ASSERT_TRUE(matrix_b.eqMatrix(result_b));
}

TEST(Set3, True) {
  S21Matrix matrix_a(3, 3);
  EXPECT_THROW(matrix_a.setCols(-2), std::out_of_range);
}

TEST(Set4, True) {
  S21Matrix matrix_a(3, 3);
  EXPECT_THROW(matrix_a.setRows(-6), std::out_of_range);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}