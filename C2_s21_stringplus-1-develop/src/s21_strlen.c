#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define s21_size_t unsigned long long
#define s21_NULL (void*)0

s21_size_t s21_strlen(const char* str) {
  s21_size_t i = 0;
  while (str[i] != '\0') i++;
  return i;
}

START_TEST(test_1) {
  const char* empty_string = "";
  ck_assert_int_eq(s21_strlen(empty_string), 0);
}

START_TEST(test_2) {
  const char* english_words =
      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  ck_assert_int_eq(s21_strlen(english_words), 52);
}

START_TEST(test_3) {
  const char* russian_words =
      "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя";
  ck_assert_int_eq(s21_strlen(russian_words), 132);
}

START_TEST(test_4) {
  const char* special_symbols = "!#$&()*+,-./:;<=>?@[]/\\^_`{|}~";
  ck_assert_int_eq(s21_strlen(special_symbols), 30);
}

START_TEST(test_5) {
  const char* unread_symbols = "";
  ck_assert_int_eq(s21_strlen(unread_symbols), 29);
}

START_TEST(test_6) {
  const char* asci_extended = "€ƒ„…†‡ˆ‰Š‹Œêëìíîïðñòóôõö÷øùúû";
  ck_assert_int_eq(s21_strlen(asci_extended), 65);
}

Suite* strlen_suite() {
  Suite* suite = suite_create("strlen");
  TCase* tc_core = tcase_create("Core");

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
  Suite* suite = strlen_suite();
  SRunner* runner = srunner_create(suite);
  srunner_run_all(runner, CK_NORMAL);
  number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
