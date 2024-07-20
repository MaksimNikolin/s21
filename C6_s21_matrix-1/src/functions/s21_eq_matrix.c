#include "../s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int status = incorrect_matrixes(A, B) == 0;

  for (int i = 0; status == 1 && i < A->rows; i++) {
    for (int j = 0; status == 1 && j < A->columns; j++) {
      if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-06) status = FAILURE;
    }
  }

  return status;
}
