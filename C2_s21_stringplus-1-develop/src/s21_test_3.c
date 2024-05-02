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
  const char *haystack = "Hello World";
  const char *needle1 = "World";
  const char *needle2 = "Earth";
  const char *needle3 = "ello";
  const char *needle4 = "llo ";
  const char *needle5 = "llo";
  const char *needle6 = "Hello World";
  const char *needle7 = "Hello";
  const char *needle8 = "";
  const char *needle9 = " ";

  ck_assert_ptr_eq(strstr(haystack, needle1), s21_strstr(haystack, needle1));
  ck_assert_ptr_null(strstr(haystack, needle2));
  ck_assert_ptr_eq(strstr(haystack, needle3), s21_strstr(haystack, needle3));
  ck_assert_ptr_eq(strstr(haystack, needle4), s21_strstr(haystack, needle4));
  ck_assert_ptr_eq(strstr(haystack, needle5), s21_strstr(haystack, needle5));
  ck_assert_ptr_eq(strstr(haystack, needle6), s21_strstr(haystack, needle6));
  ck_assert_ptr_eq(strstr(haystack, needle7), s21_strstr(haystack, needle7));
  ck_assert_ptr_eq(strstr(haystack, needle8), s21_strstr(haystack, needle8));
  ck_assert_ptr_eq(strstr(haystack, needle9), s21_strstr(haystack, needle9));
}
END_TEST

void compare_strings(char *got, char *expected) {
  ck_assert_ptr_nonnull(got);
  ck_assert_ptr_nonnull(expected);
  ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));
  ck_assert_str_eq(got, expected);
}

START_TEST(test_for_strtok_1) {
  char str[] = "Apple+Banana_Pinapple! !Watermelon=melon";
  const char delims[] = "+_! =";
  char *got = s21_strtok(str, delims);
  char *expected = strtok(str, delims);

  compare_strings(got, expected);

  while (got && expected) {
    got = s21_strtok(s21_NULL, delims);
    expected = strtok(s21_NULL, delims);
    compare_strings(got, expected);
  }
}
END_TEST

START_TEST(test_for_strtok_2) {
  const char delims[] = "+_! =";
  char *got = s21_strtok("", delims);
  ck_assert_ptr_null(got);
}
END_TEST

START_TEST(test_for_strtok_3) {
  const char delims[] = "+_! =";
  char *got = s21_strtok(s21_NULL, delims);
  ck_assert_ptr_null(got);
}
END_TEST

START_TEST(test_for_strtok_4) {
  char str[] = "+++___!!!!====";
  const char delims[] = "+_! =";
  char *got = s21_strtok(str, delims);
  for (size_t i = 0; i < s21_strlen(str); i++) {
    ck_assert_ptr_null(got);
    got = s21_strtok(s21_NULL, delims);
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

START_TEST(test_for_to_lower) {
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

Suite *s21_string_suite_3() {
  Suite *s2 = suite_create("Tests_for_string_3");

  TCase *tc_strrchr = tcase_create("Tests_for_strrchr ");
  TCase *tc_strstr = tcase_create("Tests_for_strstr ");
  TCase *tc_strtok = tcase_create("Tests_for_strtok ");
  TCase *tc_to_lower = tcase_create("Tests_for_to_lower ");
  TCase *tc_to_upper = tcase_create("Tests_for_to_upper ");

  tcase_add_test(tc_strrchr, test_for_strrchr);
  tcase_add_test(tc_strstr, test_for_strstr);
  tcase_add_test(tc_strtok, test_for_strtok_1);
  tcase_add_test(tc_strtok, test_for_strtok_2);
  tcase_add_test(tc_strtok, test_for_strtok_3);
  tcase_add_test(tc_strtok, test_for_strtok_4);
  tcase_add_test(tc_to_upper, test_for_to_upper);
  tcase_add_test(tc_to_lower, test_for_to_lower);

  suite_add_tcase(s2, tc_strrchr);
  suite_add_tcase(s2, tc_strstr);
  suite_add_tcase(s2, tc_strtok);
  suite_add_tcase(s2, tc_to_lower);
  suite_add_tcase(s2, tc_to_upper);

  return s2;
}