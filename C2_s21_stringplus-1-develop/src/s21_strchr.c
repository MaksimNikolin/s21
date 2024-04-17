/*
#include <stdio.h>
#include <string.h>

int main() {
  const char str[] = "sdkcjksdcjsdckjsdc";
  int ch = 1;
  char *res = strchr(str, ch);
  printf("%s\n", res);
  return 0;
}

// Вывод: проходим по строке, если встречаем символ указываем его и все что
после него,
// если в строке символа не оказалось - увы, это segfault. Нечитаемые символы
игнорируются.
*/

#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define s21_size_t unsigned long long
#define s21_NULL (void *)0

char *s21_strchr(const char *str, int c) {
  int i = 0;
  while (str[i] && str[i] != c) i++;
  return c == str[i] ? (char *)str + i : s21_NULL;
}

START_TEST(test_1) {
  char str[] = "";
  int c = 'b';
  ck_assert_ptr_eq(s21_strchr(str, c), s21_NULL);
}

START_TEST(test_2) {
  char str[] = "sdcjhbsdj\ncsdcbsdjc";
  int c = 'b';
  ck_assert_str_eq(s21_strchr(str, c), "bsdj\ncsdcbsdjc");
}

START_TEST(test_3) {
  char str[] = "sdjckbsdjcjsdkc\0";
  int c = 'b';
  ck_assert_str_eq(s21_strchr(str, c), "bsdjcjsdkc");
}

START_TEST(test_4) {
  char str[] = "sdcjksbdjcsdkckdjsc\n\0";
  int c = 'b';
  ck_assert_str_eq(s21_strchr(str, c), "bdjcsdkckdjsc\n");
}

START_TEST(test_5) {
  char str[] = "dskjcjkbsdприветcsdjcjkdsc";
  int c = 'b';
  ck_assert_str_eq(s21_strchr(str, c), "bsdприветcsdjcjkdsc");
}

START_TEST(test_6) {
  char str[] = "sdkcjksdcjsdckjsdc";
  int c = '';
  ck_assert_str_eq(s21_strchr(str, c), "cjsdckjsdc");
}

Suite *strchr_suite() {
  Suite *suite = suite_create("strchr");
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
  Suite *suite = strchr_suite();
  SRunner *runner = srunner_create(suite);
  srunner_run_all(runner, CK_NORMAL);
  number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
