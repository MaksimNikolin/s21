/*
#include <stdio.h>
#include <string.h>

void compare(const char* a, const char* b, int n) {
    printf("strncmp(\"%s\", \"%s\") = %d\n", a, b, strncmp(a, b, n));
}

int main() {
    compare("abc", "abc", 2);           // return     0
    compare("abc", "cba", 2);           // return    -2
    compare("cba", "abc", 2);           // return     2
    compare("cba", "cbc", 2);           // return     0
    compare("aac", "abcd", 2);          // return    -1
    compare("12345", "апgривет", 4);    // return  -159
    return 0;
}

// Вывод: проходит массив до значения n, если все символы равны, то ретурн 0,
// Если нет, то делаем ретурн на первый несовпавший из списка.
*/

#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define s21_size_t unsigned long long
#define s21_NULL (void *)0

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int res = 0;
  while ((*str1 || *str2) && n--)
    if (*str1++ != *str2++) {
      res = (unsigned char)*--str1 - (unsigned char)*--str2;
      break;
    }
  return res;
}

START_TEST(test_1) {
  const char *str1 = "abc";
  const char *str2 = "abc";
  s21_size_t n = 2;
  ck_assert_int_eq(s21_strncmp(str1, str2, n), 0);
}

START_TEST(test_2) {
  const char *str1 = "abc";
  const char *str2 = "cba";
  s21_size_t n = 2;
  ck_assert_int_eq(s21_strncmp(str1, str2, n), -2);
}

START_TEST(test_3) {
  const char *str1 = "cba";
  const char *str2 = "abc";
  s21_size_t n = 2;
  ck_assert_int_eq(s21_strncmp(str1, str2, n), 2);
}

START_TEST(test_4) {
  const char *str1 = "cba";
  const char *str2 = "cbc";
  s21_size_t n = 2;
  ck_assert_int_eq(s21_strncmp(str1, str2, n), 0);
}

START_TEST(test_5) {
  const char *str1 = "aac";
  const char *str2 = "abcd";
  s21_size_t n = 2;
  ck_assert_int_eq(s21_strncmp(str1, str2, n), -1);
}

START_TEST(test_6) {
  const char *str1 = "12345";
  const char *str2 = "апgривет";
  s21_size_t n = 4;
  ck_assert_int_eq(s21_strncmp(str1, str2, n), -159);
}

Suite *strncmp_suite() {
  Suite *suite = suite_create("strncmp");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_1);
  tcase_add_test(tc_core, test_2);
  tcase_add_test(tc_core, test_3);
  tcase_add_test(tc_core, test_4);
  tcase_add_test(tc_core, test_5);
  tcase_add_test(tc_core, test_6);

  suite_add_tcase(suite, tc_core);
  return suite;
}

int main() {
  int number_failed;
  Suite *suite = strncmp_suite();
  SRunner *runner = srunner_create(suite);
  srunner_run_all(runner, CK_NORMAL);
  number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
