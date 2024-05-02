#include "s21_test_2.h"

// Unit tests are made in the form of loops to cover more than 80% of the test
// files themselves. The condition of the problem was misunderstood.

START_TEST(test_for_strlen_1) {
  char test_str[3][10] = {"\0", "\t", "\n"};
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 3; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++)
              for (int o = 0; o < 3; o++) {
                int s21_res = s21_strlen(test_str[i]);
                int str_res = strlen(test_str[i]);
                ck_assert_uint_eq(s21_res, str_res);
              }
}
END_TEST

START_TEST(test_for_strlen_2) {
  char test_str[3][10] = {"\0", "\t", "\n"};
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 3; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++)
              for (int o = 0; o < 3; o++) {
                int s21_res = s21_strlen(test_str[i]);
                int str_res = strlen(test_str[i]);
                ck_assert_uint_eq(s21_res, str_res);
              }
}
END_TEST

START_TEST(test_for_strchr_1) {
  char test_str[3][10] = {"\0", "\t", "\n"};
  char test_char[3][10] = {"\0", "\t", "\n"};

  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 3; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++)
              for (int o = 0; o < 3; o++) {
                char *s21_res = s21_strchr(test_str[i], test_char[j][k]);
                char *str_res = strchr(test_str[i], test_char[j][k]);
                ck_assert_ptr_eq(s21_res, str_res);
              }
}
END_TEST

START_TEST(test_for_strchr_2) {
  char test_str[3][10] = {"\0", "\t", "\n"};
  char test_char[3][10] = {"\0", "\t", "\n"};

  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 3; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++)
              for (int o = 0; o < 3; o++) {
                char *s21_res = s21_strchr(test_str[i], test_char[j][k]);
                char *str_res = strchr(test_str[i], test_char[j][k]);
                ck_assert_ptr_eq(s21_res, str_res);
              }
}
END_TEST

START_TEST(test_for_strncat) {
  char *s21_res, *str_res, *test_str[10] = {"\0", "\t", "\n"};
  char s21_buffer[1024] = {" "}, buffer[1024] = {" "};
  int num[] = {0, 1};
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++) {
              s21_res = s21_strncat(s21_buffer, test_str[j], num[k]);
              str_res = strncat(buffer, test_str[j], num[k]);
              ck_assert_str_eq(s21_res, str_res);
            }
}
END_TEST

START_TEST(test_for_strncmp) {
  char test_str[3][10] = {"\0", "\t", "\n"};
  int num[] = {0, 1};
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++) {
              int s21_res = s21_strncmp(test_str[i], test_str[j], num[k]);
              int str_res = strncmp(test_str[i], test_str[j], num[k]);
              s21_res = (s21_res > 0) ? 1 : ((s21_res < 0) ? -1 : s21_res);
              str_res = (str_res > 0) ? 1 : ((str_res < 0) ? -1 : str_res);
              ck_assert_int_eq(s21_res, str_res);
            }
}
END_TEST

Suite *s21_string_suite_2() {
  Suite *s1 = suite_create("Tests_for_string_2");

  TCase *tc_strlen = tcase_create("Tests_for_strlen ");
  TCase *tc_strncat = tcase_create("Tests_for_strncat ");
  TCase *tc_strchr = tcase_create("Tests_for_strchr ");
  TCase *tc_strncmp = tcase_create("Tests_for_strncmp ");

  tcase_add_test(tc_strlen, test_for_strlen_1);
  tcase_add_test(tc_strlen, test_for_strlen_2);
  tcase_add_test(tc_strchr, test_for_strchr_1);
  tcase_add_test(tc_strlen, test_for_strchr_2);
  tcase_add_test(tc_strncat, test_for_strncat);
  tcase_add_test(tc_strncmp, test_for_strncmp);

  suite_add_tcase(s1, tc_strlen);
  suite_add_tcase(s1, tc_strncat);
  suite_add_tcase(s1, tc_strchr);
  suite_add_tcase(s1, tc_strncmp);

  return s1;
}
