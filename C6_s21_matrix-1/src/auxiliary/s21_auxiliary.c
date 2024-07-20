#include "../s21_matrix.h"

void calcMinor(double **A, double **aux, int skipRow, int skipCol, int size) {
  for (int row = 0, i = 0; row < size; row++) {
    for (int col = 0, j = 0; col < size; col++) {
      if (row != skipRow && col != skipCol) {
        aux[i][j++] = A[row][col];
        if (j == size - 1) {
          j = 0;
          i++;
        }
      }
    }
  }
}

double calcDeterminant(matrix_t *A, int size) {
  if (size == 1) return A->matrix[0][0];

  matrix_t aux = {0};
  double result = 0;

  s21_create_matrix(size, size, &aux);
  for (int sign = 1, i = 0; i < size; i++, sign *= (-1)) {
    calcMinor(A->matrix, aux.matrix, 0, i, size);
    result += sign * A->matrix[0][i] * calcDeterminant(&aux, size - 1);
  }

  s21_remove_matrix(&aux);
  return result;
}

int incorrect_matrixes(matrix_t *A, matrix_t *B) {
  int status = 1;

  if (incorrect_matrix(A) == 0) {
    if (incorrect_matrix(B) == 0)
      status = (A->rows == B->rows && A->columns == B->columns) ? 0 : 2;
  }

  return status;
}

int incorrect_matrix(matrix_t *A) {
  return (A == NULL || A->matrix == NULL || A->rows <= 0 || A->columns <= 0);
}

void init_matrix(double number, matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; number += 1.0, j++)
      A->matrix[i][j] = number;
  }
}
