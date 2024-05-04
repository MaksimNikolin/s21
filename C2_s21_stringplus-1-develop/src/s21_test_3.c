#include "s21_test_3.h"

START_TEST(test_for_strrchr) {
  char str1[] = "";
  int c = 'c';
  char *result_1 = s21_strrchr(str1, c);
  ck_assert_ptr_eq(result_1, s21_NULL);

  char str2[] = "sdcjhbsdj\ncsdcbsdjc";
  char *result_2 = s21_strrchr(str2, c);
  ck_assert_int_eq(result_2 - str2, strrchr(str2, c) - str2);

  char str3[] = "sdjckbsdjcjsdkc\0";
  char *result_3 = s21_strrchr(str3, c);
  ck_assert_int_eq(result_3 - str3, strrchr(str3, c) - str3);

  char str4[] = "sdcjksbdjcsdkckdjsc\n\0";
  char *result_4 = s21_strrchr(str4, c);
  ck_assert_int_eq(result_4 - str4, strrchr(str4, c) - str4);

  char str5[] = "dskjcjkbsdприветcsdjcjkdsc";
  char *result_5 = s21_strrchr(str5, c);
  ck_assert_int_eq(result_5 - str5, strrchr(str5, c) - str5);

  char str6[] = "sdkcjksdcjsdckjsdc";
  int b = 'c';
  char *result_6 = s21_strrchr(str6, b);
  ck_assert_int_eq(result_6 - str6, strrchr(str6, b) - str6);
}
END_TEST

START_TEST(test_for_strstr) {
  const char *test1_haystack = "Hello, world!";
  const char *test1_needle = "world";
  char *result1 = s21_strstr(test1_haystack, test1_needle);
  ck_assert(strcmp(result1, "world!") == 0);

  const char *test2_haystack = "Hello, world!";
  const char *test2_needle = "";
  char *result2 = s21_strstr(test2_haystack, test2_needle);
  ck_assert(strcmp(result2, "Hello, world!") == 0);

  const char *test3_haystack = "";
  const char *test3_needle = "world";
  char *result3 = s21_strstr(test3_haystack, test3_needle);
  ck_assert(result3 == NULL);

  const char *test4_haystack = "Hello, world!";
  const char *test4_needle = "foo";
  char *result4 = s21_strstr(test4_haystack, test4_needle);
  ck_assert(result4 == NULL);

  const char *test5_haystack = "Hello, world!";
  const char *test5_needle = "Hello, world!";
  char *result5 = s21_strstr(test5_haystack, test5_needle);
  ck_assert(strcmp(result5, "Hello, world!") == 0);
}
END_TEST

START_TEST(test_for_strtok) {
  char test1[] = "Hello, World!";
  char *token1 = s21_strtok(test1, " ,!");
  ck_assert(strcmp(token1, "Hello") == 0);

  token1 = s21_strtok(NULL, " ,!");
  ck_assert(strcmp(token1, "World") == 0);

  char test2[] = "";
  char *token2 = s21_strtok(test2, " ,!");
  ck_assert(token2 == NULL);

  char test3[] = ",,,";
  char *token3 = s21_strtok(test3, " ,!");
  ck_assert(token3 == NULL);

  char test4[] = "Token";
  char *token4 = s21_strtok(test4, " ,!");
  ck_assert(strcmp(token4, "Token") == 0);

  char test5[] = "One,Two,Three";
  char *token5 = s21_strtok(test5, ",");
  ck_assert(strcmp(token5, "One") == 0);
  token5 = s21_strtok(NULL, ",");
  ck_assert(strcmp(token5, "Two") == 0);
  token5 = s21_strtok(NULL, ",");
  ck_assert(strcmp(token5, "Three") == 0);

  char test6[] = ",";
  char *token = s21_strtok(test6, ",");
  ck_assert(token == NULL);
}
END_TEST

START_TEST(test_for_to_lower_1) {
  char str1[] = "ASTA LA VISTA BABY";
  char str2[] = "AREYOUYANKEE!";

  char *new_str1 = s21_to_lower(str1);
  if (new_str1 != s21_NULL) {
    ck_assert_str_eq(new_str1, "asta la vista baby");
    free(new_str1);
  }

  char *new_str2 = s21_to_lower(str2);
  if (new_str2 != s21_NULL) {
    ck_assert_str_eq(new_str2, "areyouyankee!");
    free(new_str2);
  }
}
END_TEST

START_TEST(test_for_to_lower_2) {
  char str1[] = "sdcsdc";

  char *new_str1 = s21_to_lower(str1);
  if (new_str1 != s21_NULL) {
    ck_assert_str_eq(new_str1, "asta la vista baby");
    free(new_str1);
  }
}
END_TEST

START_TEST(test_for_to_upper) {
  char str1[] = "asta la vista baby";
  char str2[] = "AreYouYankee!";

  char *new_str1 = s21_to_upper(str1);
  if (new_str1 != s21_NULL) {
    ck_assert_str_eq(new_str1, "ASTA LA VISTA BABY");
    free(new_str1);
  }

  char *new_str2 = s21_to_upper(str2);
  if (new_str2 != s21_NULL) {
    ck_assert_str_eq(new_str2, "AREYOUYANKEE!");
    free(new_str2);
  }
}
END_TEST

Suite *s21_string_suite_3() {
  Suite *s2 = suite_create("Tests_for_string_3");

  TCase *tc_strrchr = tcase_create("Tests_for_strrchr ");
  TCase *tc_strstr = tcase_create("Tests_for_strstr ");
  TCase *tc_strtok = tcase_create("Tests_for_strtok ");
  TCase *tc_to_lower = tcase_create("Tests_for_to_lower ");
  TCase *tc_to_upper = tcase_create("Tests_for_to_upper ");

  tcase_add_test(tc_strrchr, test_for_strrchr);
  tcase_add_test(tc_strstr, test_for_strstr);
  tcase_add_test(tc_strtok, test_for_strtok);
  tcase_add_test(tc_to_lower, test_for_to_lower_1);
  tcase_add_test(tc_to_lower, test_for_to_lower_2);
  tcase_add_test(tc_to_upper, test_for_to_upper);

  suite_add_tcase(s2, tc_strrchr);
  suite_add_tcase(s2, tc_strstr);
  suite_add_tcase(s2, tc_strtok);
  suite_add_tcase(s2, tc_to_lower);
  suite_add_tcase(s2, tc_to_upper);

  return s2;
}