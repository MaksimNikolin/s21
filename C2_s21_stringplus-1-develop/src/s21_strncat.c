/*
#include <stdio.h>
#include <string.h>

void add_string(char* a, const char* b, size_t n) {
    printf("%s\n", strncat(a, b, n));
}

int main() {
    char str1[] = "при\n\0";
    char str2[] = "вет\n\0";
    int n = 2;
    add_string(str1, str2, n);
    return 0;
}

// Вывод: добавить строку когда i-й элемент 1й строки == \n
// Stuck smashing:
//  1) (abc\n, def)
//  2) (abc\0, def)
//  3) (, )
*/

#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define s21_size_t unsigned long long
#define s21_NULL (void *)0

char *s21_strncat(char *str1, const char *str2, s21_size_t n) {
  char *res = str1;
  s21_size_t len1 = 0, len2 = 0;

  while (str1[len1] != '\0') len1++;
  while (str2[len2] != '\0' && len2 < n) str1[len1 + len2] = str2[len2], len2++;
  str1[len1 + len2] = '\0';
  return res;
}

START_TEST(test_1) {
  char str1[] = "";
  const char str2[] = "";
  s21_size_t n = 100;
  ck_assert_str_eq(s21_strncat(str1, str2, n), "");
}

START_TEST(test_2) {
  char str1[] = "abc";
  const char str2[] = "def";
  s21_size_t n = 100;
  ck_assert_str_eq(s21_strncat(str1, str2, n), "abcdef");
}

START_TEST(test_3) {
  char str1[] = "abc";
  const char str2[] = "def\n";
  s21_size_t n = 100;
  ck_assert_str_eq(s21_strncat(str1, str2, n), "abcdef\n");
}

START_TEST(test_4) {
  char str1[] = "abc\n";
  const char str2[] = "def\n";
  s21_size_t n = 100;
  ck_assert_str_eq(s21_strncat(str1, str2, n), "abc\ndef\n");
}

START_TEST(test_5) {
  char str1[] = "abc";
  const char str2[] = "def\0";
  s21_size_t n = 100;
  ck_assert_str_eq(s21_strncat(str1, str2, n), "abcdef\0");
}

START_TEST(test_6) {
  char str1[] = "abc\0";
  const char str2[] = "\0";
  s21_size_t n = 100;
  ck_assert_str_eq(s21_strncat(str1, str2, n), "abc\0");
}

START_TEST(test_7) {
  char str1[] = "12\n3\0";
  const char str2[] = "12\n3\0";
  s21_size_t n = 100;
  ck_assert_str_eq(s21_strncat(str1, str2, n), "12\n312\n3");
}

START_TEST(test_8) {
  char str1[] = "123\n\0";
  const char str2[] = "123\n\0";
  s21_size_t n = 100;
  ck_assert_str_eq(s21_strncat(str1, str2, n), "123\n123\n");
}

START_TEST(test_9) {
  char str1[] = "при\n\0";
  const char str2[] = "вет\n\0";
  s21_size_t n = 100;
  ck_assert_str_eq(s21_strncat(str1, str2, n), "при\nвет\n");
}

START_TEST(test_10) {
  char str1[] = "abc";
  const char str2[] = "def";
  s21_size_t n = 2;
  ck_assert_str_eq(s21_strncat(str1, str2, n), "abcde");
}

START_TEST(test_11) {
  char str1[] = "abc";
  const char str2[] = "def\n";
  s21_size_t n = 2;
  ck_assert_str_eq(s21_strncat(str1, str2, n), "abcde");
}

START_TEST(test_12) {
  char str1[] = "abc\n";
  const char str2[] = "def\n";
  s21_size_t n = 2;
  ck_assert_str_eq(s21_strncat(str1, str2, n), "abc\nde");
}

START_TEST(test_13) {
  char str1[] = "abc";
  const char str2[] = "def\0";
  s21_size_t n = 2;
  ck_assert_str_eq(s21_strncat(str1, str2, n), "abcde");
}

START_TEST(test_14) {
  char str1[] = "abc\0";
  const char str2[] = "\0";
  s21_size_t n = 2;
  ck_assert_str_eq(s21_strncat(str1, str2, n), "abc");
}

START_TEST(test_15) {
  char str1[] = "12\n3\0";
  const char str2[] = "12\n3\0";
  s21_size_t n = 2;
  ck_assert_str_eq(s21_strncat(str1, str2, n), "12\n312");
}

START_TEST(test_16) {
  char str1[] = "123\n\0";
  const char str2[] = "123\n\0";
  s21_size_t n = 2;
  ck_assert_str_eq(s21_strncat(str1, str2, n), "123\n12");
}

START_TEST(test_17) {
  char str1[] = "при\n\0";
  const char str2[] = "вет\n\0";
  s21_size_t n = 2;
  ck_assert_str_eq(s21_strncat(str1, str2, n), "при\nв");
}

Suite *strncat_suite() {
  Suite *suite = suite_create("strncat");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_1);
  tcase_add_test(tc_core, test_2);
  tcase_add_test(tc_core, test_3);
  tcase_add_test(tc_core, test_4);
  tcase_add_test(tc_core, test_5);
  tcase_add_test(tc_core, test_6);
  tcase_add_test(tc_core, test_7);
  tcase_add_test(tc_core, test_8);
  tcase_add_test(tc_core, test_9);
  tcase_add_test(tc_core, test_10);
  tcase_add_test(tc_core, test_11);
  tcase_add_test(tc_core, test_12);
  tcase_add_test(tc_core, test_13);
  tcase_add_test(tc_core, test_14);
  tcase_add_test(tc_core, test_15);
  tcase_add_test(tc_core, test_16);
  tcase_add_test(tc_core, test_17);

  suite_add_tcase(suite, tc_core);
  return suite;
}

int main() {
  int number_failed;
  Suite *suite = strncat_suite();
  SRunner *runner = srunner_create(suite);
  srunner_run_all(runner, CK_NORMAL);
  number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
