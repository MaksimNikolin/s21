#include <check.h>

#include "s21_matrix.h"

void print_logo() {
  printf("******************************************************************************************\n");
  printf("***     ********* *******   ******    *** ******* *** ********* ******* ******* **********\n");
  printf("*** **** ******* * ******* **** ********** ***** **** * ***** * ****** * ****** **********\n");
  printf("*** ***** ***** *** ****** **** *********** *** ***** ** *** ** ***** *** ***** **********\n");
  printf("*** ***** ***** *** ****** ******  ********* * ****** *** * *** ***** *** ***** **********\n");
  printf("*** ***** ****       ***** ********** ******* ******* **** **** ****       **** **********\n");
  printf("*** **** **** ******* **** ********** ******* ******* ********* *** ******* *** **********\n");
  printf("***     **** ********* **   ***     ********* ******* ********* ** ********* **        ***\n");
  printf("******************************************************************************************\n");
}

// calc complements

START_TEST(s21_calc_complements_01) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};
  s21_create_matrix(4, 3, &A);
  A.matrix[0][0] = -1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 7.0;
  A.matrix[1][0] = 1.0;
  A.matrix[1][1] = 0.0;
  A.matrix[1][2] = 0.0;
  A.matrix[2][0] = 47.0;
  A.matrix[2][1] = 13.0;
  A.matrix[2][2] = 17.0;
  A.matrix[3][0] = 22.0;
  A.matrix[3][1] = 7.0;
  A.matrix[3][2] = 1.0;
  res = s21_calc_complements(&A, &Z);
  s21_remove_matrix(&A);
  ck_assert_int_eq(res, CALCULATION_ERROR);
}
END_TEST

START_TEST(s21_calc_complements_02) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};
  s21_create_matrix(2, 2, &A);
  s21_remove_matrix(&A);
  res = s21_calc_complements(&A, &Z);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

// create matrix

START_TEST(s21_create_matrix_01) {
  int res = 0;
  matrix_t A = {0};
  res = s21_create_matrix(1, 0, &A);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

// determinant

START_TEST(s21_determinant_01) {
  int res = 0;
  double determ = 0.0;
  matrix_t A = {NULL, 0, 0};
  res = s21_determinant(&A, &determ);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_02) {
  int res = 0;
  double determ = 0.0;
  matrix_t A = {0};
  s21_create_matrix(1, 2, &A);
  res = s21_determinant(&A, &determ);
  ck_assert_int_eq(res, CALCULATION_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

// eq

START_TEST(s21_eq_matrix_01) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(3, 2, &A);
  init_matrix(10.0, &A);
  s21_create_matrix(3, 2, &B);
  init_matrix(-10.0, &B);
  res = s21_eq_matrix(&A, &B);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  ck_assert_int_eq(res, FAILURE);
}
END_TEST

// inverse

START_TEST(s21_inverse_matrix_01) {
  int res;
  matrix_t A = {0};
  matrix_t Z = {0};
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 2;
  res = s21_inverse_matrix(&A, &Z);
  ck_assert_int_eq(Z.matrix[0][0] == (1.0 / A.matrix[0][0]), 1);
  ck_assert_int_eq(res, OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&Z);
}
END_TEST

START_TEST(s21_inverse_matrix_02) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};
  s21_create_matrix(3, 3, &A);
  init_matrix(1.0, &A);
  res = s21_inverse_matrix(&A, &Z);
  ck_assert_int_eq(res, CALCULATION_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_inverse_matrix_03) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};
  s21_create_matrix(3, 2, &A);
  init_matrix(1.0, &A);
  res = s21_inverse_matrix(&A, &Z);
  ck_assert_int_eq(res, CALCULATION_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_inverse_matrix_04) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};
  s21_create_matrix(3, 3, &A);
  init_matrix(1.0, &A);
  s21_remove_matrix(&A);
  res = s21_inverse_matrix(&A, &Z);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_inverse_matrix_05) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};
  matrix_t X = {0};
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 4.0;
  A.matrix[1][1] = 5.0;
  A.matrix[1][2] = 6.0;
  A.matrix[2][0] = 8.0;
  A.matrix[2][1] = 6.0;
  A.matrix[2][2] = 9.0;
  s21_inverse_matrix(&A, &Z);
  s21_create_matrix(3, 3, &X);
  X.matrix[0][0] = -3.0 / 5.0;
  X.matrix[0][1] = 0.0;
  X.matrix[0][2] = 1.0 / 5.0;
  X.matrix[1][0] = -4.0 / 5.0;
  X.matrix[1][1] = 1.0;
  X.matrix[1][2] = -2.0 / 5.0;
  X.matrix[2][0] = 16.0 / 15.0;
  X.matrix[2][1] = -2.0 / 3.0;
  X.matrix[2][2] = 1.0 / 5.0;
  res = s21_eq_matrix(&X, &Z);
  s21_remove_matrix(&A);
  s21_remove_matrix(&X);
  s21_remove_matrix(&Z);
  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

// mult matrix

START_TEST(s21_mult_matrix_01) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t Z = {0};
  matrix_t X = {0};
  s21_create_matrix(1, 1, &A);
  init_matrix(-5.0, &A);
  s21_create_matrix(1, 1, &B);
  init_matrix(1.0, &B);
  s21_mult_matrix(&A, &B, &Z);
  s21_create_matrix(1, 1, &X);
  X.matrix[0][0] = -5.0;
  res = s21_eq_matrix(&X, &Z);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&X);
  s21_remove_matrix(&Z);
  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(s21_mult_matrix_02) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t Z = {0};
  res = s21_mult_matrix(&A, &B, &Z);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&Z);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_mult_matrix_03) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t Z = {0};
  s21_create_matrix(2, 3, &A);
  init_matrix(-5.0, &A);
  s21_create_matrix(2, 2, &B);
  init_matrix(1.0, &B);
  res = s21_mult_matrix(&A, &B, &Z);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&Z);
  ck_assert_int_eq(res, CALCULATION_ERROR);
}
END_TEST

// mult number

START_TEST(s21_mult_number_01) {
  int res = 0;
  double number = 2.0;
  matrix_t A = {0};
  matrix_t Z = {0};
  matrix_t X = {0};
  s21_create_matrix(1, 1, &A);
  init_matrix(2.0, &A);
  s21_mult_number(&A, number, &Z);
  s21_create_matrix(1, 1, &X);
  X.matrix[0][0] = 4.0;
  res = s21_eq_matrix(&X, &Z);
  s21_remove_matrix(&A);
  s21_remove_matrix(&X);
  s21_remove_matrix(&Z);
  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(s21_mult_number_02) {
  int res = 0;
  double number = 2.0;
  matrix_t A = {0};
  matrix_t Z = {0};
  s21_create_matrix(0, 0, &A);
  res = s21_mult_number(&A, number, &Z);
  s21_remove_matrix(&A);
  s21_remove_matrix(&Z);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

// sub

START_TEST(s21_sub_matrix_01) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t Z = {0};
  matrix_t X = {0};
  s21_create_matrix(4, 2, &A);
  init_matrix(4.0, &A);
  s21_create_matrix(4, 2, &B);
  init_matrix(-2.0, &B);
  s21_sub_matrix(&A, &B, &Z);
  s21_create_matrix(4, 2, &X);
  X.matrix[0][0] = 6.0;
  X.matrix[0][1] = 6.0;
  X.matrix[1][0] = 6.0;
  X.matrix[1][1] = 6.0;
  X.matrix[2][0] = 6.0;
  X.matrix[2][1] = 6.0;
  X.matrix[3][0] = 6.0;
  X.matrix[3][1] = 6.0;
  res = s21_eq_matrix(&X, &Z);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&X);
  s21_remove_matrix(&Z);
  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(s21_sub_matrix_02) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t Z = {0};
  s21_create_matrix(4, 2, &A);
  s21_create_matrix(4, 3, &B);
  res = s21_sub_matrix(&A, &B, &Z);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&Z);
  ck_assert_int_eq(res, CALCULATION_ERROR);
}
END_TEST

// sum

START_TEST(s21_sum_matrix_01) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t Z = {0};
  matrix_t X = {0};
  s21_create_matrix(4, 2, &A);
  init_matrix(4.0, &A);
  s21_create_matrix(4, 2, &B);
  init_matrix(-2.0, &B);
  s21_sum_matrix(&A, &B, &Z);
  s21_create_matrix(4, 2, &X);
  X.matrix[0][0] = 2.0;
  X.matrix[0][1] = 4.0;
  X.matrix[1][0] = 6.0;
  X.matrix[1][1] = 8.0;
  X.matrix[2][0] = 10.0;
  X.matrix[2][1] = 12.0;
  X.matrix[3][0] = 14.0;
  X.matrix[3][1] = 16.0;
  res = s21_eq_matrix(&X, &Z);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&X);
  s21_remove_matrix(&Z);
  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(s21_sum_matrix_02) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t Z = {0};
  s21_create_matrix(4, 2, &A);
  s21_create_matrix(4, 3, &B);
  res = s21_sum_matrix(&A, &B, &Z);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&Z);
  ck_assert_int_eq(res, CALCULATION_ERROR);
}
END_TEST

// transpose

START_TEST(s21_transpose_01) {
  int res = 0;
  matrix_t A = {0};
  res = s21_transpose(&A, &A);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

// another funcs

START_TEST(s21_another_funcs_01) {
  matrix_t A, B;
  s21_create_matrix(2, 3, &B);
  A.rows = 2;
  A.columns = 3;
  A.matrix = NULL;
  int res = incorrect_matrixes(&A, &B);
  ck_assert_int_eq(res, 1);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_another_funcs_02) {
  matrix_t A, B;
  s21_create_matrix(2, 3, &A);
  B.rows = 0;
  B.columns = 3;
  B.matrix = NULL;
  int res = incorrect_matrixes(&A, &B);
  ck_assert_int_eq(res, 1);
  s21_remove_matrix(&A);
}
END_TEST

Suite *s21_matrix_suite() {
  Suite *s1 = suite_create(
      "////////////////////////////  Matrix_tests  "
      "////////////////////////////");

  TCase *tc_matrix = tcase_create("Tests_for_matrix ");
  suite_add_tcase(s1, tc_matrix);

  tcase_add_test(tc_matrix, s21_calc_complements_01);
  tcase_add_test(tc_matrix, s21_calc_complements_02);
  tcase_add_test(tc_matrix, s21_create_matrix_01);
  tcase_add_test(tc_matrix, s21_determinant_01);
  tcase_add_test(tc_matrix, s21_determinant_02);
  tcase_add_test(tc_matrix, s21_eq_matrix_01);
  tcase_add_test(tc_matrix, s21_inverse_matrix_01);
  tcase_add_test(tc_matrix, s21_inverse_matrix_02);
  tcase_add_test(tc_matrix, s21_inverse_matrix_03);
  tcase_add_test(tc_matrix, s21_inverse_matrix_04);
  tcase_add_test(tc_matrix, s21_inverse_matrix_05);
  tcase_add_test(tc_matrix, s21_mult_matrix_01);
  tcase_add_test(tc_matrix, s21_mult_number_01);
  tcase_add_test(tc_matrix, s21_mult_number_02);
  tcase_add_test(tc_matrix, s21_mult_matrix_02);
  tcase_add_test(tc_matrix, s21_mult_matrix_03);
  tcase_add_test(tc_matrix, s21_sub_matrix_01);
  tcase_add_test(tc_matrix, s21_sub_matrix_02);
  tcase_add_test(tc_matrix, s21_sum_matrix_01);
  tcase_add_test(tc_matrix, s21_sum_matrix_02);
  tcase_add_test(tc_matrix, s21_transpose_01);
  tcase_add_test(tc_matrix, s21_another_funcs_01);
  tcase_add_test(tc_matrix, s21_another_funcs_02);

  return s1;
}

int main() {
  Suite *s1;
  SRunner *runner1;

  s1 = s21_matrix_suite();
  runner1 = srunner_create(s1);

  srunner_set_fork_status(runner1, CK_NOFORK);
  srunner_run_all(runner1, CK_NORMAL);
  srunner_free(runner1);

  return 0;
}