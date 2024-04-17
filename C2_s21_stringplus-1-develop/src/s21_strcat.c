/*
#include <stdio.h>
#include <string.h>

void add_string(char* a, const char* b) {
    printf("strcat(%s, %s) = ", a, b);
    printf("%s\n", strcat(a, b));
}

int main() {
    char str1[] = "Huc";
    char str2[] = "ker";
    add_string(str1, str2);
    return 0;
}

// Вывод: добавить строку когда i-й элемент 1й строки == \n.
Stack smashing в случаях:
1) (при\n, вет)
2) (abc\0, a)
*/

#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define s21_size_t unsigned long long
#define s21_NULL (void *)0

char *s21_strcat(char *str1, const char *str2) {
  char *res = str1;
  s21_size_t len1 = 0, len2 = 0;

  while (str1[len1] != '\0') len1++;
  while (str2[len2] != '\0') str1[len1 + len2] = str2[len2], len2++;
  str1[len1 + len2] = '\0';
  return res;
}

START_TEST(test_1) {
  char str1[] = "";
  const char str2[] = "";
  ck_assert_str_eq(s21_strcat(str1, str2), "");
}

START_TEST(test_2) {
  char str1[] = "a";
  const char str2[] = "b";
  ck_assert_str_eq(s21_strcat(str1, str2), "ab");
}

START_TEST(test_3) {
  char str1[] = "Huc";
  const char str2[] = "ker777";
  ck_assert_str_eq(s21_strcat(str1, str2), "Hucker777");
}

START_TEST(test_4) {
  char str1[] = "\n\0";
  const char str2[] = "\0";
  ck_assert_str_eq(s21_strcat(str1, str2), "\n\0\0");
}

START_TEST(test_5) {
  char str1[] = "H u c\n";
  const char str2[] = "k e r 777";
  ck_assert_str_eq(s21_strcat(str1, str2), "H u c\nk e r 777");
}

START_TEST(test_6) {
  char str1[] = "При";
  const char str2[] = "вет";
  ck_assert_str_eq(s21_strcat(str1, str2), "Привет");
}

Suite *strcat_suite() {
  Suite *suite = suite_create("strcat");
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
  Suite *suite = strcat_suite();
  SRunner *runner = srunner_create(suite);
  srunner_run_all(runner, CK_NORMAL);
  number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
