#include "s21_sprintf_test.h"

// c opt
START_TEST(test_sprintf_c_opt_1) {
  char result[20];
  char assert[20];
  s21_sprintf(result, "Count: %c", 'a');
  sprintf(assert, "Count: %c", 'a');
  ck_assert_str_eq(result, assert);
}
END_TEST

START_TEST(test_sprintf_c_opt_2) {
  char result[20];
  char assert[20];
  char c = 'b';
  int a = s21_sprintf(result, "Count: %-5c", c);
  int b = sprintf(assert, "Count: %-5c", c);
  ck_assert_str_eq(result, assert);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_sprintf_c_opt_3) {
  char result[20];
  char assert[20];
  char c = 'a';
  s21_sprintf(result, "Count: %*c", 4, c);
  sprintf(assert, "Count: %*c", 4, c);
  ck_assert_str_eq(result, assert);
}
END_TEST

// i opt
START_TEST(test_sprintf_i_opt_1) {
  char result[20];
  char assert[20];
  long long d = 5717984;
  s21_sprintf(result, "Count: %Li 1", d);
  sprintf(assert, "Count: %Li 1", d);
  ck_assert_str_eq(result, assert);
}
END_TEST

START_TEST(test_sprintf_i_opt_2) {
  char result[40];
  char assert[40];
  short int i = 32770;
  s21_sprintf(result, "Count: %hi end", i);
  sprintf(assert, "Count: %hi end", i);
  ck_assert_str_eq(result, assert);
}
END_TEST

START_TEST(test_sprintf_i_opt_3) {
  char result[40];
  char assert[40];
  int i = 327710;
  s21_sprintf(result, "Count: %5.10i end", i);
  sprintf(assert, "Count: %5.10i end", i);
  ck_assert_str_eq(result, assert);
}
END_TEST

START_TEST(test_sprintf_i_opt_4) {
  char result[40];
  char assert[40];
  int i = 327710;
  s21_sprintf(result, "Count: %-+10.5i end", i);
  sprintf(assert, "Count: %-+10.5i end", i);
  ck_assert_str_eq(result, assert);
}
END_TEST

// d opt
START_TEST(test_sprintf_d_opt_1) {
  char result[20];
  char assert[20];
  int d = 0;
  s21_sprintf(result, "Count: %d abc", d);
  sprintf(assert, "Count: %d abc", d);
  ck_assert_str_eq(result, assert);
}
END_TEST

START_TEST(test_sprintf_d_opt_2) {
  char result[20];
  char assert[20];
  int d = -1;
  s21_sprintf(result, "Count: % d abc", d);
  sprintf(assert, "Count: % d abc", d);
  ck_assert_str_eq(result, assert);
}
END_TEST

START_TEST(test_sprintf_d_opt_3) {
  char str1[100] = "";
  char str2[100] = "";
  char *str3 = "%%Test %d Test";
  int a = 12;
  ck_assert_int_eq(sprintf(str1, str3, a), s21_sprintf(str2, str3, a));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// f opt
START_TEST(test_sprintf_f_opt_1) {
  char result[40];
  char assert[40];
  float f = -123.321;
  s21_sprintf(result, "Count: %f end", f);
  sprintf(assert, "Count: %f end", f);
  ck_assert_str_eq(result, assert);
}
END_TEST

START_TEST(test_sprintf_f_opt_2) {
  char result[40];
  char assert[40];
  float f = 1.1234;
  s21_sprintf(result, "Count: %.*f end", 3, f);
  sprintf(assert, "Count: %.*f end", 3, f);
  ck_assert_str_eq(result, assert);
}
END_TEST

START_TEST(test_sprintf_f_opt_3) {
  char result[40];
  char assert[40];
  float f = -.0000001;
  s21_sprintf(result, "Count: %f end", f);
  sprintf(assert, "Count: %f end", f);
  ck_assert_str_eq(result, assert);
}
END_TEST

START_TEST(test_sprintf_f_opt_4) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%10Lf";
  long double val = 15.35;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf_f_opt_5) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.0Lf";
  long double val = 15.35;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);
  ck_assert_str_eq(str1, str2);
}
END_TEST

// s opt
START_TEST(test_sprintf_s_opt_1) {
  char result[40];
  char assert[40];
  char *s = "none";
  s21_sprintf(result, "%.6s", s);
  sprintf(assert, "%.6s", s);
  ck_assert_str_eq(result, assert);
}
END_TEST

START_TEST(test_sprintf_s_opt_2) {
  char result[40];
  char assert[40];
  char *s = "stroka s probelom";
  s21_sprintf(result, "%-5.6s", s);
  sprintf(assert, "%-5.6s", s);
  ck_assert_str_eq(result, assert);
}
END_TEST

START_TEST(test_sprintf_s_opt_3) {
  char result[40];
  char assert[40];
  wchar_t s[] = L"wide chars: ";
  s21_sprintf(result, "%-5.6ls", s);
  sprintf(assert, "%-5.6ls", s);
  ck_assert_str_eq(result, assert);
}
END_TEST

START_TEST(test_sprintf_s_opt_4) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%-15.9s";
  char *val = "21R DSADA SDHASDOAMDSA sdas8d7nasd 111";
  s21_sprintf(str1, format, val), sprintf(str2, format, val);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf_s_opt_5) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "wchar: %5.12ls";
  wchar_t w[] = L"àààààà";
  int a = s21_sprintf(str1, format, w);
  int b = sprintf(str2, format, w);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_sprintf_s_opt_6) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "wchar: %120hs ABOBA";
  wchar_t w[] = L"森我爱菠萝";
  int a = s21_sprintf(str1, format, w);
  int b = sprintf(str2, format, w);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_sprintf_s_opt_7) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%-43ls";
  wchar_t w[] = L"森我爱菠萝";
  int a = s21_sprintf(str1, format, w);
  int b = sprintf(str2, format, w);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_sprintf_s_opt_8) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "wchar: %43ls";
  wchar_t w[] = L"森我爱菠萝";
  int a = s21_sprintf(str1, format, w);
  int b = sprintf(str2, format, w);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);
}
END_TEST

// u opt
START_TEST(test_sprintf_u_opt_1) {
  char result[40];
  char assert[40];
  unsigned long int u = 214748364912;
  s21_sprintf(result, "Count: %lu abc", u);
  sprintf(assert, "Count: %lu abc", u);
  ck_assert_str_eq(result, assert);
}
END_TEST

START_TEST(test_sprintf_u_opt_2) {
  char result[40];
  char assert[40];
  unsigned short int u = 32767;
  s21_sprintf(result, "Count: %hu abc", u);
  sprintf(assert, "Count: %hu abc", u);
  ck_assert_str_eq(result, assert);
}
END_TEST

START_TEST(test_sprintf_u_opt_3) {
  char str1[200];
  char str2[200];
  char *str3 = "%+u Test %+3.u Test %+5.7u TEST %+10u GOD %+.u";
  unsigned int a = 32;
  unsigned int b = 8899;
  unsigned int c = 91918;
  unsigned int d = 32311;
  unsigned int e = 3261;
  int res1 = sprintf(str1, str3, a, b, c, d, e);
  int res2 = s21_sprintf(str2, str3, a, b, c, d, e);
  ck_assert_pstr_eq(str1, str2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

// g opt
START_TEST(test_sprintf_g_opt_1) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%g";
  double hex = 0.50300;
  ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf_g_opt_2) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%.g";
  double hex = 0.0004;
  s21_sprintf(str1, format, hex);
  sprintf(str2, format, hex);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf_g_opt_3) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%g";
  double hex = 0;
  s21_sprintf(str1, format, hex);
  sprintf(str2, format, hex);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf_g_opt_4) {
  char str1[BUFF_SIZE] = {'\0'};
  char str2[BUFF_SIZE] = {'\0'};
  char format[] = "%LG";
  long double hex = 0.000005;
  s21_sprintf(str1, format, hex);
  sprintf(str2, format, hex);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf_g_opt_5) {
  char str1[200];
  char str2[200];
  char *str3 = "%G TEST %.G TEST %4G TEST %4.G TEST %5.10G!";
  double num = 76.756589367;
  sprintf(str1, str3, num, num, num, num, num);
  s21_sprintf(str2, str3, num, num, num, num, num);
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf_g_opt_6) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %+- 14G!test: %+ 10G!test: % +25G!";
  double num = -365789.34;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf_g_opt_7) {
  char str1[400];
  char str2[400];
  char *str3 = "test: % 14G!test: % -27G!test: %- 19G!";
  double num = 365789.34;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// e opt
START_TEST(test_sprintf_e_opt_1) {
  char str1[BUFF_SIZE] = {'\0'};
  char str2[BUFF_SIZE] = {'\0'};
  char *format = "%015E";
  float val = 0;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf_e_opt_2) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%15e";
  float val = 0;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf_e_opt_3) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "% .0e %.le %Le %e %le %Le";
  float val = 0;
  double val1 = 0;
  long double val2 = 3515315.153151;
  float val3 = 5.5;
  double val4 = 0.094913941;
  long double val5 = 95919539159.53151351131;
  s21_sprintf(str1, format, val, val1, val2, val3, val4, val5);
  sprintf(str2, format, val, val1, val2, val3, val4, val5);
  ck_assert_str_eq(str1, str2);
}
END_TEST

// o opt
START_TEST(test_sprintf_o_opt_1) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%15o";
  int val = 14140;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);
  ck_assert_str_eq(str1, str2);
}
END_TEST

// x opt
START_TEST(test_sprintf_x_opt_1) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%#x";
  unsigned val = 0;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf_x_opt_2) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%#x";
  unsigned val = 18571;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf_x_opt_3) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%#hx";
  unsigned short val = 12352;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf_x_opt_4) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%#lx";
  unsigned long val = 18571757371571;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf_x_opt_5) {
  char str1[200];
  char str2[200];
  char *str3 = "%6.5X Test %.23X Test %3.X TEST %.X";
  unsigned int a = 0Xac15;
  unsigned int b = 0X7bF;
  unsigned int c = 0XFF;
  unsigned int d = 0X66;
  ck_assert_int_eq(sprintf(str1, str3, a, b, c, d),
                   s21_sprintf(str2, str3, a, b, c, d));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf_x_opt_6) {
  char str1[200];
  char str2[200];
  char *str3 = "%-10.5X Test %-.8X Test %-7X TEST %-.X";
  unsigned int a = 0Xac15;
  unsigned int b = 0X7bF;
  unsigned int c = 0XFF;
  unsigned int d = 0X2727;
  ck_assert_int_eq(sprintf(str1, str3, a, b, c, d),
                   s21_sprintf(str2, str3, a, b, c, d));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// p opt
START_TEST(test_sprintf_p_opt_1) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%p";
  s21_sprintf(str1, format, format);
  sprintf(str2, format, format);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf_p_opt_2) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.p";
  s21_sprintf(str1, format, format);
  sprintf(str2, format, format);
  ck_assert_str_eq(str1, str2);
}
END_TEST

// n opt
START_TEST(test_sprintf_n_opt_1) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  int ret = 0;
  char *format = "How many chars written before n %n";
  s21_sprintf(str1, format, &ret);
  sprintf(str2, format, &ret);
  ck_assert_str_eq(str1, str2);
}
END_TEST

// multi opts
START_TEST(test_sprintf_multi_opts_1) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  int n1, n2;
  s21_sprintf(str1, "%d%n", 123, &n1);
  sprintf(str2, "%d%n", 123, &n2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

Suite *s21_sprintf_suite() {
  Suite *s2 = suite_create(
      "////////////////////////////    sprintf_test    "
      "////////////////////////////");
  TCase *tc = tcase_create("sprintf_tc");

  tcase_add_test(tc, test_sprintf_c_opt_1);
  tcase_add_test(tc, test_sprintf_c_opt_2);
  tcase_add_test(tc, test_sprintf_c_opt_3);
  tcase_add_test(tc, test_sprintf_i_opt_1);
  tcase_add_test(tc, test_sprintf_i_opt_2);
  tcase_add_test(tc, test_sprintf_i_opt_3);
  tcase_add_test(tc, test_sprintf_i_opt_4);
  tcase_add_test(tc, test_sprintf_d_opt_1);
  tcase_add_test(tc, test_sprintf_d_opt_2);
  tcase_add_test(tc, test_sprintf_d_opt_3);
  tcase_add_test(tc, test_sprintf_f_opt_1);
  tcase_add_test(tc, test_sprintf_f_opt_2);
  tcase_add_test(tc, test_sprintf_f_opt_3);
  tcase_add_test(tc, test_sprintf_f_opt_4);
  tcase_add_test(tc, test_sprintf_f_opt_5);
  tcase_add_test(tc, test_sprintf_s_opt_1);
  tcase_add_test(tc, test_sprintf_s_opt_2);
  tcase_add_test(tc, test_sprintf_s_opt_3);
  tcase_add_test(tc, test_sprintf_s_opt_4);
  tcase_add_test(tc, test_sprintf_s_opt_5);
  tcase_add_test(tc, test_sprintf_s_opt_6);
  tcase_add_test(tc, test_sprintf_s_opt_7);
  tcase_add_test(tc, test_sprintf_s_opt_8);
  tcase_add_test(tc, test_sprintf_u_opt_1);
  tcase_add_test(tc, test_sprintf_u_opt_2);
  tcase_add_test(tc, test_sprintf_u_opt_3);
  tcase_add_test(tc, test_sprintf_g_opt_1);
  tcase_add_test(tc, test_sprintf_g_opt_2);
  tcase_add_test(tc, test_sprintf_g_opt_3);
  tcase_add_test(tc, test_sprintf_g_opt_4);
  tcase_add_test(tc, test_sprintf_g_opt_5);
  tcase_add_test(tc, test_sprintf_g_opt_6);
  tcase_add_test(tc, test_sprintf_g_opt_7);
  tcase_add_test(tc, test_sprintf_e_opt_1);
  tcase_add_test(tc, test_sprintf_e_opt_2);
  tcase_add_test(tc, test_sprintf_e_opt_3);
  tcase_add_test(tc, test_sprintf_o_opt_1);
  tcase_add_test(tc, test_sprintf_x_opt_1);
  tcase_add_test(tc, test_sprintf_x_opt_2);
  tcase_add_test(tc, test_sprintf_x_opt_3);
  tcase_add_test(tc, test_sprintf_x_opt_4);
  tcase_add_test(tc, test_sprintf_x_opt_5);
  tcase_add_test(tc, test_sprintf_x_opt_6);
  tcase_add_test(tc, test_sprintf_p_opt_1);
  tcase_add_test(tc, test_sprintf_p_opt_2);
  tcase_add_test(tc, test_sprintf_n_opt_1);
  tcase_add_test(tc, test_sprintf_multi_opts_1);
  suite_add_tcase(s2, tc);

  return s2;
}