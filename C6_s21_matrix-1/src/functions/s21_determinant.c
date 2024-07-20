#include "../s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  if (incorrect_matrix(A) == SUCCESS) return INCORRECT_MATRIX;
  if (A->columns != A->rows) return CALCULATION_ERROR;

  if (A->rows == 1)
    *result = A->matrix[0][0];
  else
    *result = calcDeterminant(A, A->rows);

  return OK;
}
