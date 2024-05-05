#include <check.h>
#include <string.h>

#include "s21_sprintf_test.h"
#include "s21_sscanf_test.h"
#include "s21_string.h"
#include "s21_test_2.h"
#include "s21_test_3.h"

START_TEST(test_for_memchr) {
  const char str[20] = "website\0";
  fail_unless(memchr(str, 'i', 5) == s21_memchr(str, 'i', 5));
  fail_unless(memchr(str, 'i', 3) == s21_memchr(str, 'i', 3));
  fail_unless(memchr(str, 'a', 8) == s21_memchr(str, 'a', 8));
  fail_unless(memchr(str, '0', 15) == s21_memchr(str, '0', 15));
  const char str1[20] = "5465754..@";
  fail_unless(memchr(str1, '5', 5) == s21_memchr(str1, '5', 5));
  fail_unless(memchr(str1, '6', 3) == s21_memchr(str1, '6', 3));
  fail_unless(memchr(str1, '.', 8) == s21_memchr(str1, '.', 8));
  fail_unless(memchr(str1, '@', 15) == s21_memchr(str1, '@', 15));
  fail_unless(memchr(str1, '\0', 15) == s21_memchr(str1, '\0', 15));
}
END_TEST

START_TEST(test_for_memcmp) {
  unsigned char src[15] = "1234567890";
  unsigned char dst[15] = "1234567890";
  fail_unless(memcmp(src, dst, 10) == s21_memcmp(src, dst, 10));
  unsigned char src_2[15] = "5678901234";
  unsigned char dst_2[15] = "1234567890";
  fail_unless(memcmp(src_2, dst_2, 10) == s21_memcmp(src_2, dst_2, 10));
  fail_unless(memcmp(dst_2, src_2, 10) == s21_memcmp(dst_2, src_2, 10));
  unsigned char src_3[15] = "mgdfgjkdf";
  unsigned char dst_3[15] = "MGDFGJKDF";
  fail_unless(memcmp(src_3, dst_3, 10) == s21_memcmp(src_3, dst_3, 10));
  fail_unless(memcmp(dst_3, src_3, 10) == s21_memcmp(dst_3, src_3, 10));
  unsigned char src_4[15] = "";
  unsigned char dst_4[15] = "MGDFGJKDF";
  fail_unless(memcmp(src_4, dst_4, 10) == s21_memcmp(src_4, dst_4, 10));
  fail_unless(memcmp(dst_4, src_4, 10) == s21_memcmp(dst_4, src_4, 10));
  unsigned char src_5[15] = "";
  unsigned char dst_5[15] = "";
  fail_unless(memcmp(src_5, dst_5, 10) == s21_memcmp(src_5, dst_5, 10));
  fail_unless(memcmp(dst_5, src_5, 10) == s21_memcmp(dst_5, src_5, 10));
  fail_unless(memcmp(dst_5, src_5, 0) == s21_memcmp(dst_5, src_5, 0));
}
END_TEST

START_TEST(test_for_memcpy) {
  char str1[10] = "string";
  char str2[40] = "", str4[40] = "", str5[40] = "", str6[40] = "",
       str7[40] = "", str3[40] = "";
  memcpy(str2, str1, 6);
  s21_memcpy(str3, str1, 6);
  fail_unless(strcmp(str2, str3) == 0);
  memcpy(str4, str1, 0);
  s21_memcpy(str5, str1, 0);
  fail_unless(strcmp(str4, str5) == 0);
  memcpy(str6, str1, 1);
  s21_memcpy(str7, str1, 1);
  str6[1] = '\0';
  str7[1] = '\0';
  fail_unless(strcmp(str6, str7) == 0);
  char str8[] = "";
  memcpy(str2, str8, 1);
  s21_memcpy(str3, str8, 1);
  fail_unless(strcmp(str2, str3) == 0);
}
END_TEST

START_TEST(test_for_memset) {
  char str[] = "string";
  char str_2[] = "string";
  s21_memset(str, '*', 3);
  memset(str_2, '*', 3);
  fail_unless(strcmp(str, str_2) == 0);
  int i = 0;
  s21_memset(str, '-', 0);
  memset(str_2, '-', i);
  fail_unless(strcmp(str, str_2) == 0);
  s21_memset(str, '-', 6);
  memset(str_2, '-', 6);
  fail_unless(strcmp(str, str_2) == 0);
  s21_memset(str, '\0', 6);
  memset(str_2, '\0', 6);
  fail_unless(strcmp(str, str_2) == 0);
}
END_TEST

START_TEST(test_for_strncpy) {
  char str1[] = "string";
  char str2[40] = "";
  char str3[40] = "";
  char str4[40] = "", str5[40] = "", str6[40] = "";
  strncpy(str2, str1, 5);
  s21_strncpy(str3, str1, 5);
  fail_unless(strcmp(str2, str3) == 0);
  s21_strncpy(str4, str1, 30);
  strncpy(str5, str1, 30);
  fail_unless(strcmp(str4, str5) == 0);
  int i = 0;
  fail_unless(strncpy(str6, str1, i) == s21_strncpy(str6, str1, 0));
  char str7[] = "";
  strncpy(str2, str7, 5);
  s21_strncpy(str3, str7, 5);
  fail_unless(strcmp(str2, str3) == 0);
}
END_TEST

START_TEST(test_for_strcspn) {
  char str[30] = "string";
  char str_2[] = "ar";
  fail_unless(strcspn(str, str_2) == s21_strcspn(str, str_2));
  char str_3[] = "ajk";
  fail_unless(strcspn(str, str_3) == s21_strcspn(str, str_3));
  char str_4[] = "mg";
  fail_unless(strcspn(str, str_4) == s21_strcspn(str, str_4));
  char str_5[] = "";
  fail_unless(strcspn(str, str_5) == s21_strcspn(str, str_5));
  fail_unless(strcspn(str_5, str) == s21_strcspn(str_5, str));
}
END_TEST

START_TEST(test_for_strpbrk) {
  char str[30] = "string";
  char str_1[] = "ar";
  fail_unless(strpbrk(str, str_1) == s21_strpbrk(str, str_1));
  char str_2[] = "ajk";
  fail_unless(strpbrk(str, str_2) == s21_strpbrk(str, str_2));
  char str_3[] = "mg";
  fail_unless(strpbrk(str, str_3) == s21_strpbrk(str, str_3));
  char str_4[] = "";
  fail_unless(strpbrk(str, str_4) == s21_strpbrk(str, str_4));
}
END_TEST

START_TEST(test_for_strerror) {
  ck_assert_str_eq(s21_strerror(_i), strerror(_i));

  for (int i = -1000; i < 135; i++) {
    char *got = s21_strerror(i);
    char *expected = strerror(i);
    ck_assert_str_eq(got, expected);
  }
}
END_TEST

START_TEST(test_for_insert_1) {
  char *src = "Hello!!";
  char *str = " World!";
  char *new_str = s21_insert(src, str, 5);
  if (new_str) {
    ck_assert_str_eq(new_str, "Hello World!!!");
    free(new_str);
  }
  new_str = s21_insert(src, "", 40);
  ck_assert(new_str == s21_NULL);
  new_str = s21_insert(src, str, -1);
  ck_assert(new_str == s21_NULL);
}
END_TEST

START_TEST(test_for_insert_2) {
  const char *src = s21_NULL;
  const char *str = "Hello world!";
  s21_size_t start_index = 0;
  char *result = s21_insert(src, str, start_index);
  ck_assert(result == s21_NULL);
}
END_TEST

START_TEST(test_for_insert_3) {
  const char *src = "Hello ";
  const char *str = NULL;
  s21_size_t start_index = 0;
  char *result = s21_insert(src, str, start_index);
  ck_assert(result == NULL);
}
END_TEST

START_TEST(test_for_insert_4) {
  const char *src = "Hello ";
  const char *str = "";
  s21_size_t start_index = 0;
  char *result = s21_insert(src, str, start_index);
  ck_assert(strcmp(result, "Hello ") == 0);
  free(result);
}
END_TEST

START_TEST(test_for_trim_1) {
  char str_trim[] = "\n  ! Hello World ! ,, \n\0";
  char test1[] = "\n !\0";
  char test2[] = "\n !,Hd\0";

  char *str = s21_trim(str_trim, test1);
  if (str) {
    ck_assert_str_eq(str, "Hello World ! ,,\0");
    free(str);
  }

  str = s21_trim(str_trim, test2);
  if (str) {
    ck_assert_str_eq(str, "ello Worl\0");
    free(str);
  }
}
END_TEST

// START_TEST(test_for_trim_2) {
//   char str_trim[100] = "\n !\0";
//   char test1[100] = "\n !\0";
//   char test2[100] = "\n !\0";

//   char *str = s21_trim(str_trim, test1);
//   if (str) {
//     ck_assert_str_eq(str, "Hello World ! ,,\0");

//   }

//   str = s21_trim(str_trim, test2);
//   if (str) {
//     ck_assert_str_eq(str, "ello Worl\0");

//   }
// }
// END_TEST

START_TEST(test_for_trim_3) {
  const char *src = "Hello, world!";
  const char *expected = "Hello, world!";
  char *result = s21_trim(src, "");
  ck_assert(strcmp(result, expected) == 0);
  free(result);
}
END_TEST

START_TEST(test_for_trim_4) {
  const char *src = "   Hello, world!   ";
  const char *expected = "Hello, world!";
  char *result = s21_trim(src, NULL);
  ck_assert(strcmp(result, expected) == 0);
  free(result);
}
END_TEST

START_TEST(test_for_trim_5) {
  const char *src = s21_NULL;
  const char *trim_chars = " ";
  char *result = s21_trim(src, trim_chars);
  ck_assert(result == s21_NULL);
  free(result);
}
END_TEST

Suite *s21_string_suite() {
  Suite *s1 = suite_create("Tests_for_string");

  TCase *tc_memchr = tcase_create("Tests_for_memchr ");
  TCase *tc_memcmp = tcase_create("Tests_for_memcmp ");
  TCase *tc_memcpy = tcase_create("Tests_for_memcpy ");
  TCase *tc_memset = tcase_create("Tests_for_memset ");
  TCase *tc_strncpy = tcase_create("Tests_for_strncpy ");
  TCase *tc_strcspn = tcase_create("Tests_for_strcspn ");
  TCase *tc_strpbrk = tcase_create("Tests_for_strpbrk ");
  TCase *tc_strerror = tcase_create("Tests_for_strerror ");
  TCase *tc_insert = tcase_create("Tests_for_insert ");
  TCase *tc_trim = tcase_create("Tests_for_trim ");

  suite_add_tcase(s1, tc_memchr);
  suite_add_tcase(s1, tc_memcmp);
  suite_add_tcase(s1, tc_memcpy);
  suite_add_tcase(s1, tc_memset);
  suite_add_tcase(s1, tc_strncpy);
  suite_add_tcase(s1, tc_strcspn);
  suite_add_tcase(s1, tc_strpbrk);
  suite_add_tcase(s1, tc_strerror);
  suite_add_tcase(s1, tc_insert);
  suite_add_tcase(s1, tc_trim);

  tcase_add_test(tc_memchr, test_for_memchr);
  tcase_add_test(tc_memcmp, test_for_memcmp);
  tcase_add_test(tc_memcpy, test_for_memcpy);
  tcase_add_test(tc_memset, test_for_memset);
  tcase_add_test(tc_strncpy, test_for_strncpy);
  tcase_add_test(tc_strcspn, test_for_strcspn);
  tcase_add_test(tc_strpbrk, test_for_strpbrk);
  tcase_add_test(tc_strerror, test_for_strerror);
  tcase_add_test(tc_insert, test_for_insert_1);
  tcase_add_test(tc_insert, test_for_insert_2);
  tcase_add_test(tc_insert, test_for_insert_3);
  tcase_add_test(tc_insert, test_for_insert_4);
  tcase_add_test(tc_trim, test_for_trim_1);
  // tcase_add_test(tc_trim, test_for_trim_2);
  tcase_add_test(tc_trim, test_for_trim_3);
  tcase_add_test(tc_trim, test_for_trim_4);
  tcase_add_test(tc_trim, test_for_trim_5);
  return s1;
}

int main() {
  Suite *s, *s1, *s2, *s3, *s4;
  SRunner *runner, *runner1, *runner2, *runner3, *runner4;

  s = s21_string_suite();
  s1 = s21_string_suite_2();
  s2 = s21_string_suite_3();
  s3 = s21_sscanf_suite();
  s4 = s21_sprintf_suite();

  runner = srunner_create(s);
  runner1 = srunner_create(s1);
  runner2 = srunner_create(s2);
  runner3 = srunner_create(s3);
  runner4 = srunner_create(s4);

  srunner_set_fork_status(runner, CK_NOFORK);
  srunner_set_fork_status(runner1, CK_NOFORK);
  srunner_set_fork_status(runner2, CK_NOFORK);
  srunner_set_fork_status(runner3, CK_NOFORK);
  srunner_set_fork_status(runner4, CK_NOFORK);

  srunner_run_all(runner, CK_NORMAL);
  srunner_run_all(runner1, CK_NORMAL);
  srunner_run_all(runner2, CK_NORMAL);
  srunner_run_all(runner3, CK_NORMAL);
  srunner_run_all(runner4, CK_NORMAL);

  srunner_free(runner);
  srunner_free(runner1);
  srunner_free(runner2);
  srunner_free(runner3);
  srunner_free(runner4);

  return 0;
}
