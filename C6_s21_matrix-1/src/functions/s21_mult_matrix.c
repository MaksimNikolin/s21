#include "../s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = (incorrect_matrix(A) || incorrect_matrix(B));

  if (status == 0 && (status = A->columns != B->rows ? 2 : 0) == 0) {
    if ((status = s21_create_matrix(A->rows, B->columns, result)) == 0) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
          for (int k = 0; k < B->rows; k++)
            result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  }

  return status;
}
