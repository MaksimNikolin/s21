/*
#include <stdio.h>
#include <string.h>

void compare(const char* a, const char* b) {
    printf("strcmp(\"%s\", \"%s\") = %d\n", a, b, strcmp(a, b));
}

int main() {
    compare("abc", "abc");        // return     0
    compare("abc", "cba");        // return    -2
    compare("cba", "abc");        // return     2
    compare("cba", "cbc");        // return    -2
    compare("aac", "abcd");       // return    -1
    compare("12345", "апgривет");  // return -159
    return 0;
}

// Вывод: ретурн в зависимости от первого различного вхождения.
// Символы из asci_ext чекает странно
*/

#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define s21_size_t unsigned long long
#define s21_NULL (void *)0

int s21_strcmp(const char *str1, const char *str2) {
  int res = 0;
  while (*str1 || *str2)
    if (*str1++ != *str2++) {
      res = (unsigned char)*--str1 - (unsigned char)*--str2;
      break;
    }
  return res;
}

START_TEST(test_1) {
  const char *str1 = "abc";
  const char *str2 = "abc";
  ck_assert_int_eq(s21_strcmp(str1, str2), 0);
}

START_TEST(test_2) {
  const char *str1 = "abc";
  const char *str2 = "cba";
  ck_assert_int_eq(s21_strcmp(str1, str2), -2);
}

START_TEST(test_3) {
  const char *str1 = "cba";
  const char *str2 = "abc";
  ck_assert_int_eq(s21_strcmp(str1, str2), 2);
}

START_TEST(test_4) {
  const char *str1 = "cba";
  const char *str2 = "cbc";
  ck_assert_int_eq(s21_strcmp(str1, str2), -2);
}

START_TEST(test_5) {
  const char *str1 = "aac";
  const char *str2 = "abcd";
  ck_assert_int_eq(s21_strcmp(str1, str2), -1);
}

START_TEST(test_6) {
  const char *str1 = "12345";
  const char *str2 = "апgривет";
  ck_assert_int_eq(s21_strcmp(str1, str2), -159);
}

Suite *strcmp_suite() {
  Suite *suite = suite_create("strcmp");
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
  Suite *suite = strcmp_suite();
  SRunner *runner = srunner_create(suite);
  srunner_run_all(runner, CK_NORMAL);
  number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
