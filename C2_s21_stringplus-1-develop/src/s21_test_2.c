#include "s21_test_2.h"

START_TEST(test_for_strlen) {
  char *s1 = "0123456789";
  ck_assert_msg(s21_strlen(s1) == strlen(s1), "1st strlen test failed");

  char *s2 = "";
  ck_assert_msg(s21_strlen(s2) == strlen(s2), "2nd strlen test failed");

  char *s3 = "amogus";
  ck_assert_msg(s21_strlen(s3) == strlen(s3), "3rd strlen test failed");

  char *s4 = "shrek";
  ck_assert_msg(s21_strlen(s4) == strlen(s4), "4rth strlen test failed");

  char *s5 = "is love";
  ck_assert_msg(s21_strlen(s5) == strlen(s5), "5th strlen test failed");
}
END_TEST

START_TEST(test_for_strchr) {
  char *str1 = "TEST";
  char *str2 = "strchr";
  char *str3 = "function";
  char *str4 = "";
  char *str5 = "amogus";
  ck_assert_str_eq(s21_strchr(str1, 'E'), strchr(str1, 'E'));
  ck_assert_str_eq(s21_strchr(str3, 'i'), strchr(str3, 'i'));
  ck_assert_str_eq(s21_strchr(str5, 'a'), strchr(str5, 'a'));
  ck_assert_str_eq(s21_strchr(str1, 'E'), strchr(str1, 'E'));
  ck_assert_ptr_eq(s21_strchr(str2, 'E'), strchr(str2, 'E'));
  ck_assert_str_eq(s21_strchr(str3, 'i'), strchr(str3, 'i'));
  ck_assert_ptr_eq(s21_strchr(str4, ' '), strchr(str4, ' '));
  ck_assert_str_eq(s21_strchr(str5, 'a'), strchr(str5, 'a'));
}
END_TEST

START_TEST(test_for_strncat) {
  char str1[25] = "TEST";
  char str2[8] = "strncat";
  char str3[35] = "function";
  char str4[1] = "";
  char str5[30] = "amogus";

  s21_strncat(str1, str2, 3);
  ck_assert_msg(!memcmp(str1, "TESTstr", 8), "1st strncat test failed");

  s21_strncat(str1, str4, 3);
  ck_assert_msg(!memcmp(str1, "TESTstr", 8), "2nd strncat test failed");

  s21_strncat(str2, str4, 1);
  ck_assert_msg(!memcmp(str2, "strncat", 8), "3rd strncat test failed");

  s21_strncat(str5, str3, 3);
  ck_assert_msg(!memcmp(str5, "amogusfun", 10), "4rth strncat test failed");
}
END_TEST

START_TEST(test_for_strncmp) {
  char t1[100] = "Sample Text";
  char t2[100] = "Sample Text Plus Some Text";
  ck_assert_msg(!s21_strncmp(t1, t2, 10) && !strncmp(t1, t2, 10),
                "1st strncmp test failed");

  ck_assert_msg(s21_strncmp(t1, t2, 14) < 0 && strncmp(t1, t2, 14) < 0,
                "2nd strncmp test failed");
  char t3[100] = "";
  char t4[100] = "A";
  ck_assert_msg(s21_strncmp(t3, t4, 0) == 0 && strncmp(t3, t4, 0) == 0,
                "3rd strncmp test failed");
  ck_assert_msg(s21_strncmp(t3, t4, 1) < 0 && strncmp(t3, t4, 1) < 0,
                "3rd strncmp test failed");
  char t5[100] = "ShrekAmogus";
  char t6[100] = "Shr";
  ck_assert_msg(s21_strncmp(t5, t6, 5) > 0 && strncmp(t5, t6, 5) > 0,
                "4rth strncmp test failed");
  ck_assert_msg(s21_strncmp(t5, t6, 0) == 0 && strncmp(t5, t6, 0) == 0,
                "5th strncmp test failed");
  char t7[100] = "";
  char t8[100] = "";
  ck_assert(s21_strncmp(t7, t8, 0) == 0);
}
END_TEST

Suite *s21_string_suite_2() {
  Suite *s1 = suite_create(
      "////////////////////////////  string_part2_test  "
      "////////////////////////////");

  TCase *tc_strlen = tcase_create("Tests_for_strlen ");
  TCase *tc_strncat = tcase_create("Tests_for_strncat ");
  TCase *tc_strchr = tcase_create("Tests_for_strchr ");
  TCase *tc_strncmp = tcase_create("Tests_for_strncmp ");

  tcase_add_test(tc_strlen, test_for_strlen);
  tcase_add_test(tc_strchr, test_for_strchr);
  tcase_add_test(tc_strncat, test_for_strncat);
  tcase_add_test(tc_strncmp, test_for_strncmp);

  suite_add_tcase(s1, tc_strlen);
  suite_add_tcase(s1, tc_strncat);
  suite_add_tcase(s1, tc_strchr);
  suite_add_tcase(s1, tc_strncmp);

  return s1;
}
