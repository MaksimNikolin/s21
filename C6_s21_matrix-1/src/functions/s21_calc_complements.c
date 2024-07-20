#include "../s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (incorrect_matrix(A) == SUCCESS) return INCORRECT_MATRIX;
  if (A->columns != A->rows) return CALCULATION_ERROR;

  s21_create_matrix(A->columns, A->rows, result);
  if (A->rows != 1) {
    matrix_t aux = {0};

    s21_create_matrix(A->rows, A->rows, &aux);
    for (int sign = 0, i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        calcMinor(A->matrix, aux.matrix, i, j, A->rows);
        sign = ((i + j) % 2 == 0) ? 1 : (-1);
        result->matrix[i][j] = sign * calcDeterminant(&aux, A->rows - 1);
      }
    }

    s21_remove_matrix(&aux);
  } else {
    result->matrix[0][0] = 1;
  }

  return OK;
}