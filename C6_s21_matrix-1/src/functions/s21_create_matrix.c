#include "../s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int status = INCORRECT_MATRIX;

  if (rows > 0 && columns > 0) {
    if ((result->matrix = (double **)calloc(rows, sizeof(double *)))) {
      result->columns = columns;
      result->rows = rows;

      for (int i = 0; i < rows; i++) {
        if (!(result->matrix[i] = (double *)calloc(columns, sizeof(double)))) {
          for (int q = 0; q < i; q++) free(result->matrix[q]);
          free(result->matrix);
          status = ALLOC_FAIL;
        }
      }

      if (status == INCORRECT_MATRIX) {
        for (int i = 0; i < rows; i++) {
          for (int j = 0; j < columns; j++) {
            result->matrix[i][j] = 0;
          }
        }
        status = OK;
      }
    } else {
      status = ALLOC_FAIL;
    }
  }

  return status;
}