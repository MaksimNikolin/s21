#include "../s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int status = incorrect_matrix(A);

  if (status == 0) {
    if ((status = s21_create_matrix(A->rows, A->columns, result)) == 0) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++)
          result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }

  return status;
}