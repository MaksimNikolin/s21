#include "s21_sscanf_test.h"

/*-----CHAR-----*/

START_TEST(test_empty_all) {
  char str[] = "";
  char format[] = "";
  int p1, p2;

  int res1 = s21_sscanf(str, format, &p1);
  int res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_wrong_spec) {
  char str[] = "";
  char format[] = "%Q";
  int p1, p2;

  int res1 = s21_sscanf(str, format, &p1);
  int res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_empty_str1) {
  char *str = "";
  char *format = "%d";
  int a1 = 1, a2 = 0;

  int res1 = s21_sscanf(str, format, &a1);
  int res2 = sscanf(str, format, &a2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_empty_str2) {
  char *str = "       ";
  char *format = "%d";
  int a1 = 1, a2 = 0;

  int res1 = s21_sscanf(str, format, &a1);
  int res2 = sscanf(str, format, &a2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_char_no_space_s) {
  char *str = "Lol";
  char *format = "%c%c%c";
  char a1 = 1, a2 = 0, b1 = 1, b2 = 0, c1 = 1, c2 = 0;

  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_char_with_space_s) {
  char *str = "  L  o   l ";
  char *format = "%c%c%c";
  char a1 = 1, a2 = 0, b1 = 1, b2 = 0, c1 = 1, c2 = 0;

  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_char_with_space_sf) {
  char *str = "  L  o   l ";
  char *format = "%c %c %c";
  char a1 = 1, a2 = 0, b1 = 1, b2 = 0, c1 = 1, c2 = 0;

  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_char_skip1) {
  char *str = "d   r awLOL";
  char *format = "%*c %*c%*c%*c%*c %c %c %c";
  char a1 = 1, a2 = 0, b1 = 1, b2 = 0, c1 = 1, c2 = 0;

  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_char_skip2) {
  char *str = "      ab\ncb   dbe";
  char *format = "%*c %c %*c %c %*c %c";
  char a1 = 1, a2 = 0, b1 = 1, b2 = 0, c1 = 1, c2 = 0;

  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_char_special) {
  char *str = "/n/t//";
  char *format = "%c%c%c";
  char a1 = 1, a2 = 0, b1 = 1, b2 = 0, c1 = 1, c2 = 0;

  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

/*-----INT_D-----*/
START_TEST(test_int_d_simple) {
  char *str = "11 -22 33";
  char *format = "%d %d %d";
  int a1 = 1, a2 = 0, b1 = 1, b2 = 0, c1 = 1, c2 = 0;

  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_int_d_partial_scan) {
  char *str = "11 -22 -e33";
  char *format = "%d %d %d";
  int a1 = 1, a2 = 0, b1 = 1, b2 = 0, c1 = 1, c2 = 0;

  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_int_d_short) {
  char *str = "11 22 33";
  char *format = "%hd %hd %hd";
  short a1 = 1, a2 = 0, b1 = 1, b2 = 0, c1 = 1, c2 = 0;

  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_int_d_long) {
  char *str = "31347483647 -14748364 33";
  char *format = "%ld %ld %ld";
  long a1 = 1, a2 = 0, b1 = 1, b2 = 0, c1 = 1, c2 = 0;

  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_int_d_long_long) {
  char *str = " \t 31347483647 -31347483647 33   ";
  char *format = "%lld %lld %lld";
  long long a1 = 1, a2 = 0, b1 = 1, b2 = 0, c1 = 1, c2 = 0;

  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_int_d_width_parse) {
  char *str = "\n\t31347483647 -31347483647 33   ";
  char *format = "%5d %d %4d";
  int a1 = 1, a2 = 0, b1 = 1, b2 = 0, c1 = 1, c2 = 0;

  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_int_d_width_skip) {
  char *str = "    31347483647 -31347483647 33  \n ";
  char *format = "%*5d %d %*4d %d %d";
  int a1 = 1, a2 = 0, b1 = 1, b2 = 0, c1 = 1, c2 = 0;

  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_int_d_long_long_w) {
  char *str = " \t 3134";
  char *format = "%1lld %2lld %1lld";
  long long a1 = 1, a2 = 0, b1 = 1, b2 = 0, c1 = 1, c2 = 0;

  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_int_d_huge_width) {
  char *str = "3134";
  char *format = "%1553424lld %2lld %1lld";
  long long a1 = 1, a2 = 0, b1 = 1, b2 = 0, c1 = 1, c2 = 0;

  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_int_d_multi_type) {
  char *str = "   \t-214748364884545      \n-0 45+645 \n+0";
  char *format = "%lld %2ld %*2d %d %hd";
  long long a1 = 1, a2 = 0;
  long b1 = 1, b2 = 0;
  int c1 = 1, c2 = 0;
  short d1 = 1, d2 = 0;

  int res1 = s21_sscanf(str, format, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, format, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_int_d_long_long_overflow) {
  char *str =
      " \t-99999999999999999999999 \n9223372036854775806 "
      "\n99999999999999999999999";
  char *format = "%lld %lld %lld";
  long long a1 = 1, a2 = 0, b1 = 1, b2 = 0, c1 = 1, c2 = 0;

  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_int_i_simple) {
  char *str = "11 07 -0x6";
  char *format = "%lli %lli %lli";
  long long a1 = 1, a2 = 0, b1 = 1, b2 = 0, c1 = 1, c2 = 0;

  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_int_i_dec) {
  char *str = "   115    -20 \n -0";
  char *format = "%3lli %lli %lli";
  long long a1 = 1, a2 = 0, b1 = 1, b2 = 0, c1 = 1, c2 = 0;

  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_int_i_oct) {
  char *str = "\t 010762 \t -0 -0455";
  char *format = "%*2lli %lli %lli %lli";
  long long a1 = 1, a2 = 0, b1 = 1, b2 = 0, c1 = 1, c2 = 0;

  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_int_i_hex) {
  char *str = "\t 0x10x7a62 \t -0x4 -0XAbCdEF";
  char *format = "%*3lli %lli %lli %lli";
  long long a1 = 1, a2 = 0, b1 = 1, b2 = 0, c1 = 1, c2 = 0;

  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_int_i_hex_zeroes) {
  char *str = "\t 0x \t 0X -0x";
  char *format = "%lli %lli %lli";
  long long a1 = 1, a2 = 0, b1 = 1, b2 = 0, c1 = 1, c2 = 0;

  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  sscanf(str, format, &a2, &b2, &c2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(res1, 3);
}
END_TEST

START_TEST(test_int_i_all_sys) {
  char *str = "   \t-0214      \n-00 45+645 \n+0xf0A";
  char *format = "%lli %2li %*2d %i %hi";
  long long a1 = 1, a2 = 0;
  long b1 = 1, b2 = 0;
  int c1 = 1, c2 = 0;
  short d1 = 1, d2 = 0;

  int res1 = s21_sscanf(str, format, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, format, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

/*-----FLOAT_ALL-----*/

START_TEST(test_float_simple) {
  char *str = "0.0 -648.059 88888.88888";
  char *format = "%f %f %f";
  float a1 = 1, a2 = 0, b1 = 1, b2 = 0, c1 = 1, c2 = 0;

  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_float_size_diff) {
  char *str = "0.15618811 -6485345345643.032452342359 88888.888e-108";
  char *format = "%f %le %LE";
  float a1 = 1, a2 = 0;
  double b1 = 1, b2 = 0;
  long double c1 = 1, c2 = 0;
  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_float_epsilon) {
  char *str = "0.0e10 -.033414E17 8885235275478e-18";
  char *format = "%g %lG %Lf";
  float a1 = 1, a2 = 0;
  double b1 = 1, b2 = 0;
  long double c1 = 1, c2 = 0;
  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_float_dots) {
  char *str = ". . .";
  char *format = "%g %lG %Lf";
  float a1 = 1, a2 = 0;
  double b1 = 1, b2 = 0;
  long double c1 = 1, c2 = 0;
  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_float_zero_dots) {
  char *str = " \n-.0 -.0 +.0";
  char *format = "%g %lG %Lf";
  float a1 = 1, a2 = 0;
  double b1 = 1, b2 = 0;
  long double c1 = 1, c2 = 0;
  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_float_skip) {
  char *str = "0.0e10 -.033414E17 8885235275478e-18 9889 0315 798.35";
  char *format = "%*g %*lG %f %le %*lf %Lg";
  float a1 = 1, a2 = 0;
  double b1 = 1, b2 = 0;
  long double c1 = 1, c2 = 0;
  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_float_width) {
  char *str = "0.5e10 -.033414E17 8885235275478e-18 9889 0315 798.35";
  char *format = "%5f %*g %*4lG  %le %*lf %1Lg";
  float a1 = 1, a2 = 0;
  double b1 = 1, b2 = 0;
  long double c1 = 1, c2 = 0;
  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_float_nan) {
  char *str = "NaNinfnaN NAN3 ";
  char *format = "%f %*g %lG %Le";
  float a1 = 1, a2 = 0;
  double b1 = 1, b2 = 0;
  long double c1 = 1, c2 = 0;
  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_float_nan(b1);
  ck_assert_float_nan(b2);
  ck_assert_float_nan(b1);
  ck_assert_float_nan(b2);
  ck_assert_float_nan(b1);
  ck_assert_float_nan(b2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_float_inf) {
  char *str = "iNfInitYinf 3iNf";
  char *format = "%f  %3lG %*1g %Lf";
  float a1 = 1, a2 = 0;
  double b1 = 1, b2 = 0;
  long double c1 = 1, c2 = 0;
  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_ldouble_infinite(a1);
  ck_assert_ldouble_infinite(a2);
  ck_assert_ldouble_infinite(b1);
  ck_assert_ldouble_infinite(b2);
  ck_assert_ldouble_infinite(c1);
  ck_assert_ldouble_infinite(c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_float_nan_inf) {
  char *str =
      "inftnan -.033414E17 Nan nan 8885235275478e-18 inFiniTy 9889 0315 798.35";
  char *format = "%3f %*c %*g %*lG Nan %le %*lf %Lg";
  float a1 = 1, a2 = 0;
  double b1 = 1, b2 = 0;
  long double c1 = 1, c2 = 0;
  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_ldouble_infinite(a1);
  ck_assert_ldouble_infinite(a2);
  ck_assert_float_nan(b1);
  ck_assert_float_nan(b2);
  ck_assert_ldouble_infinite(c1);
  ck_assert_ldouble_infinite(c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

/*-----UNSIGNED-----*/
START_TEST(test_uint_dec_simple) {
  char *str = "16498 8196516519 0123456777";
  char *format = "%u %u %u";
  unsigned int a1 = 1, a2 = 0, b1 = 1, b2 = 0, c1 = 1, c2 = 0;

  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_uint_dec_neg) {
  char *str = "16498 -8196516519 -0123456777";
  char *format = "%u %u %u";
  unsigned int a1 = 1, a2 = 0, b1 = 1, b2 = 0, c1 = 1, c2 = 0;

  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_uint_dec_max) {
  char *str = "0 18446744073709551615 459494";
  char *format = "%llu %llu %llu";
  unsigned long long a1 = 1, a2 = 0, b1 = 1, b2 = 0, c1 = 1, c2 = 0;

  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_uint_dec_overflow) {
  char *str = "0 18446744073709551615 184467440737095516157878";
  char *format = "%llu %llu %llu";
  unsigned long long a1 = 1, a2 = 0, b1 = 1, b2 = 0, c1 = 1, c2 = 0;

  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_uint_dec_skip_width) {
  char *str = "0 18446744073709551615 184467440737095516157878";
  char *format = "%*u %*9lu %llu %*19llu %1llu %llu";
  unsigned long long a1 = 1, a2 = 0, b1 = 1, b2 = 0, c1 = 1, c2 = 0;

  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_uint_dec_short) {
  char *str = "-1215 6896 89849 16181 89651685425989 598";
  char *format = "%*hu %*9lu %hu %*19llu %hu %1hu";
  unsigned short a1 = 1, a2 = 0, b1 = 1, b2 = 0, c1 = 1, c2 = 0;

  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

/*-----OCTAL-----*/

START_TEST(test_uint_octal_simple) {
  char *str = "0 0123 -0123456777";
  char *format = "%o %o %o";
  unsigned int a1 = 1, a2 = 0, b1 = 1, b2 = 0, c1 = 1, c2 = 0;

  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_uint_octal_skip_width) {
  char *str = "-0 -056 00123 0714 -0123456777";
  char *format = "%*lo %lo %lo %*lo %lo";
  unsigned long a1 = 1, a2 = 0, b1 = 1, b2 = 0, c1 = 1, c2 = 0;

  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_uint_octal_x) {
  char *str = "-0x -056 0x 0123 0714 -0123456777";
  char *format = "%lo %lo %*lo %lo";
  unsigned long a1 = 1, a2 = 0, b1 = 1, b2 = 0, c1 = 1, c2 = 0;

  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_uint_octal_fail) {
  char *str = "-09 -056 0x 0123 0714 -0123456777";
  char *format = "%lo %lo %*lo %lo";
  unsigned long a1 = 1, a2 = 0, b1 = 1, b2 = 0, c1 = 1, c2 = 0;

  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

/*-----HEX-----*/

START_TEST(test_uint_hex_simple) {
  char *str = "0x123456789 0xAbCdeF 0xA4fb68";
  char *format = "%lx %lX %lx";
  unsigned long a1 = 1, a2 = 0, b1 = 1, b2 = 0, c1 = 1, c2 = 0;

  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_uint_hex_x) {
  char *str = "-0X1a2b9 0xAbCdeF -0xA4fb68";
  char *format = "%x %X %X";
  unsigned a1 = 1, a2 = 0, b1 = 1, b2 = 0, c1 = 1, c2 = 0;

  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_uint_hex_no_x) {
  char *str = "-1a2b9 5AbCdeF -0A4fb68";
  char *format = "%hX %hx %hx";
  unsigned short a1 = 1, a2 = 0, b1 = 1, b2 = 0, c1 = 1, c2 = 0;

  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_uint_hex_skip) {
  char *str = "-0x1a2b9 0X5AbCdeF -0x0A4fb68";
  char *format = "%*4X %llx %3llX %*x %llx";
  unsigned long long a1 = 1, a2 = 0, b1 = 1, b2 = 0, c1 = 1, c2 = 0;

  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_uint_hex_fail) {
  char *str = "-1a2b9 5GbCdeF -0t4fb68";
  char *format = "%hX %hx %hx";
  unsigned short a1 = 1, a2 = 0, b1 = 1, b2 = 0, c1 = 1, c2 = 0;

  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

/*-----POINTER-----*/

START_TEST(test_pointer_simple) {
  char *str = "0xAAAA 0xFFFF 0xBC431";
  char *format = "%p %p %p";
  void *a1 = NULL, *a2 = NULL, *b1 = NULL, *b2 = NULL, *c1 = NULL, *c2 = NULL;

  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_ptr_eq(a1, a2);
  ck_assert_ptr_eq(b1, b2);
  ck_assert_ptr_eq(c1, c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_pointer_no_x) {
  char *str = "AAAA -FFFF -BC431";
  char *format = "%p %p %p";
  void *a1 = NULL, *a2 = NULL, *b1 = NULL, *b2 = NULL, *c1 = NULL, *c2 = NULL;

  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_ptr_eq(a1, a2);
  ck_assert_ptr_eq(b1, b2);
  ck_assert_ptr_eq(c1, c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_pointer_full) {
  char *str = "0X123456789 -0xabCdEF -0x987654321fcDbA";
  char *format = "%p %p %p";
  void *a1 = NULL, *a2 = NULL, *b1 = NULL, *b2 = NULL, *c1 = NULL, *c2 = NULL;

  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_ptr_eq(a1, a2);
  ck_assert_ptr_eq(b1, b2);
  ck_assert_ptr_eq(c1, c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_pointer_fail) {
  char *str = "0X1R23456789 -0xabCdEF -0x987654321fcDbA";
  char *format = "%p %p %p";
  void *a1 = NULL, *a2 = NULL, *b1 = NULL, *b2 = NULL, *c1 = NULL, *c2 = NULL;

  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_ptr_eq(a1, a2);
  ck_assert_ptr_eq(b1, b2);
  ck_assert_ptr_eq(c1, c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

/*-----STRING-----*/

START_TEST(test_string_simple) {
  char *str = "Hello New World";
  char *format = "%s %s %s";
  char a1[SIZE] = {0};
  char a2[SIZE] = {0};
  char b1[SIZE] = {0};
  char b2[SIZE] = {0};
  char c1[SIZE] = {0};
  char c2[SIZE] = {0};

  int res1 = s21_sscanf(str, format, a1, b1, c1);
  int res2 = sscanf(str, format, a2, b2, c2);
  ck_assert_str_eq(a1, a2);
  ck_assert_str_eq(b1, b2);
  ck_assert_str_eq(c1, c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_string_spaces) {
  char *str = "   \tHello\n  \n \t\tNew World   \n";
  char *format = "%s %s %s";
  char a1[SIZE] = {0};
  char a2[SIZE] = {0};
  char b1[SIZE] = {0};
  char b2[SIZE] = {0};
  char c1[SIZE] = {0};
  char c2[SIZE] = {0};

  int res1 = s21_sscanf(str, format, a1, b1, c1);
  int res2 = sscanf(str, format, a2, b2, c2);
  ck_assert_str_eq(a1, a2);
  ck_assert_str_eq(b1, b2);
  ck_assert_str_eq(c1, c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_string_skip) {
  char *str = "Hello dirty beautiful trash World";
  char *format = "%s %*s %s %*s %s";
  char a1[SIZE] = {0};
  char a2[SIZE] = {0};
  char b1[SIZE] = {0};
  char b2[SIZE] = {0};
  char c1[SIZE] = {0};
  char c2[SIZE] = {0};

  int res1 = s21_sscanf(str, format, a1, b1, c1);
  int res2 = sscanf(str, format, a2, b2, c2);
  ck_assert_str_eq(a1, a2);
  ck_assert_str_eq(b1, b2);
  ck_assert_str_eq(c1, c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_string_width) {
  char *str = "Hiskipp dirty XDmy trash dear";
  char *format = "%2s %*s %*s %*2s %s %*s %89s";
  char a1[SIZE] = {0};
  char a2[SIZE] = {0};
  char b1[SIZE] = {0};
  char b2[SIZE] = {0};
  char c1[SIZE] = {0};
  char c2[SIZE] = {0};

  int res1 = s21_sscanf(str, format, a1, b1, c1);  ///////////////////
  int res2 = sscanf(str, format, a2, b2, c2);
  ck_assert_str_eq(a1, a2);
  ck_assert_str_eq(b1, b2);
  ck_assert_str_eq(c1, c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_string_together) {
  char *str = "Hello New World";
  char *format = "%s%s%s";
  char a1[SIZE] = {0};
  char a2[SIZE] = {0};
  char b1[SIZE] = {0};
  char b2[SIZE] = {0};
  char c1[SIZE] = {0};
  char c2[SIZE] = {0};

  int res1 = s21_sscanf(str, format, a1, b1, c1);
  int res2 = sscanf(str, format, a2, b2, c2);
  ck_assert_str_eq(a1, a2);
  ck_assert_str_eq(b1, b2);
  ck_assert_str_eq(c1, c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_string_together_width) {
  char *str = "HelloNewWorld";
  char *format = "%5s%3s%76s";
  char a1[SIZE] = {0};
  char a2[SIZE] = {0};
  char b1[SIZE] = {0};
  char b2[SIZE] = {0};
  char c1[SIZE] = {0};
  char c2[SIZE] = {0};

  int res1 = s21_sscanf(str, format, a1, b1, c1);
  int res2 = sscanf(str, format, a2, b2, c2);
  ck_assert_str_eq(a1, "Hello");
  ck_assert_str_eq(b1, "New");
  ck_assert_str_eq(c1, "World");
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_string_single_char) {
  char *str = "L   Ogewfgw sdfL";
  char *format = "%1s%1s%*s%*3s%1s";
  char a1[SIZE] = {0};
  char a2[SIZE] = {0};
  char b1[SIZE] = {0};
  char b2[SIZE] = {0};
  char c1[SIZE] = {0};
  char c2[SIZE] = {0};

  int res1 = s21_sscanf(str, format, a1, b1, c1);  //////////////////
  int res2 = sscanf(str, format, a2, b2, c2);
  ck_assert_str_eq(a1, "L");
  ck_assert_str_eq(b1, "O");
  ck_assert_str_eq(c1, "L");
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_string_skip_identical) {
  char *str = " Skip Hello LOL new xd world!";
  char *format = " Skip %s LOL %s xd %s";
  char a1[SIZE] = {0};
  char a2[SIZE] = {0};
  char b1[SIZE] = {0};
  char b2[SIZE] = {0};
  char c1[SIZE] = {0};
  char c2[SIZE] = {0};

  int res1 = s21_sscanf(str, format, a1, b1, c1);
  int res2 = sscanf(str, format, a2, b2, c2);
  ck_assert_str_eq(a1, a2);
  ck_assert_str_eq(b1, b2);
  ck_assert_str_eq(c1, c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

/*-----NUMBER-----*/

START_TEST(test_number_str) {
  char *str = "L   Ogewfgw sdfL";
  char *format = "%1s%1s%*s%hn%*3s%1s%n";
  char a1[SIZE] = {0};
  char a2[SIZE] = {0};
  char b1[SIZE] = {0};
  char b2[SIZE] = {0};
  char c1[SIZE] = {0};
  char c2[SIZE] = {0};
  short n1 = -1;
  short n2 = -2;
  int h1 = -1;
  int h2 = -2;

  int res1 = s21_sscanf(str, format, a1, b1, &n1, c1, &h1);  ////////////////
  int res2 = sscanf(str, format, a2, b2, &n2, c2, &h2);
  ck_assert_str_eq(a1, "L");
  ck_assert_str_eq(b1, "O");
  ck_assert_str_eq(c1, "L");
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(h1, h2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_number_d) {
  char *str = "31347483647 -14748364 33";
  char *format = "%ld %n %ld %ln %ld";
  long a1 = 1, a2 = 0, b1 = 1, b2 = 0, c1 = 1, c2 = 0;
  int n1 = -1;
  int n2 = -2;
  long h1 = -1;
  long h2 = -2;

  int res1 = s21_sscanf(str, format, &a1, &n1, &b1, &h1, &c1);
  int res2 = sscanf(str, format, &a2, &n2, &b2, &h2, &c2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(h1, h2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_number_only_n) {
  char *str = "This how to find n";
  char *format = "This how to %n find n %lln";
  int n1 = -1;
  int n2 = -2;
  long long h1 = -1;
  long long h2 = -2;

  int res1 = s21_sscanf(str, format, &n1, &h1);
  int res2 = sscanf(str, format, &n2, &h2);
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(h1, h2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_number_empty) {
  char *str = "           t";
  char *format = "%n";
  int n1 = -1;
  int n2 = -2;
  int res1 = s21_sscanf(str, format, &n1);
  int res2 = sscanf(str, format, &n2);
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

/*-----PERCENT-----*/

START_TEST(test_percent_n) {
  char *str = "%%          % t";
  char *format = "%%%n%% %%%n";
  int n1 = -1;
  int n2 = -2;
  int h1 = -1;
  int h2 = -2;

  int res1 = s21_sscanf(str, format, &n1, &h1);
  int res2 = sscanf(str, format, &n2, &h2);
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(h1, h2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_percent_str) {
  char *str = "%Hello% New %%World";
  char *format = "%%%s%% %s %%%%%s";
  char a1[SIZE] = {0};
  char a2[SIZE] = {0};
  char b1[SIZE] = {0};
  char b2[SIZE] = {0};
  char c1[SIZE] = {0};
  char c2[SIZE] = {0};

  int res1 = s21_sscanf(str, format, a1, b1, c1);
  int res2 = sscanf(str, format, a2, b2, c2);
  ck_assert_str_eq(a1, a2);
  ck_assert_str_eq(b1, b2);
  ck_assert_str_eq(c1, c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

/*-----COMPLEX-----*/

START_TEST(test_complex_pattern_1) {
  char *str =
      "Values: A = 56.7654645 inf = InFint octal = 06732 hex = "
      "0x49FAB29";
  char *format = "Values: %c %*c %lf %s = %3lG%*s %s%*c%*c%*c %o %90s %*c %Lx";
  char a1 = 56;
  char a2 = 55;
  double b1 = 1;
  double b2 = 0;
  char c1[SIZE] = {0};
  char c2[SIZE] = {0};
  double d1 = 1;
  double d2 = 0;
  char e1[SIZE] = {0};
  char e2[SIZE] = {0};
  unsigned int f1 = 1;
  unsigned int f2 = 0;
  char g1[SIZE] = {0};
  char g2[SIZE] = {0};
  unsigned long long h1 = 1;
  unsigned long long h2 = 0;

  int res1 = s21_sscanf(str, format, &a1, &b1, c1, &d1, &e1, &f1, g1,
                        &h1);  ////////////////
  int res2 = sscanf(str, format, &a2, &b2, c2, &d2, &e2, &f2, g2, &h2);
  ck_assert_int_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_str_eq(c1, c2);
  ck_assert_ldouble_infinite(d1);
  ck_assert_ldouble_infinite(d2);
  ck_assert_str_eq(e1, e2);
  ck_assert_int_eq(f1, f2);
  ck_assert_str_eq(g1, g2);
  ck_assert_int_eq(h1, h2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

Suite *s21_sscanf_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("sscanf_test");

  /* Core test case */
  tc = tcase_create("sscanf_tc");

  tcase_add_test(tc, test_empty_all);
  tcase_add_test(tc, test_wrong_spec);

  // char
  tcase_add_test(tc, test_empty_str1);
  tcase_add_test(tc, test_empty_str2);
  tcase_add_test(tc, test_char_no_space_s);
  tcase_add_test(tc, test_char_with_space_s);
  tcase_add_test(tc, test_char_with_space_sf);
  tcase_add_test(tc, test_char_skip1);
  tcase_add_test(tc, test_char_skip2);
  tcase_add_test(tc, test_char_special);

  // int d
  tcase_add_test(tc, test_int_d_simple);
  tcase_add_test(tc, test_int_d_partial_scan);
  tcase_add_test(tc, test_int_d_short);
  tcase_add_test(tc, test_int_d_long);
  tcase_add_test(tc, test_int_d_long_long);
  tcase_add_test(tc, test_int_d_width_parse);
  tcase_add_test(tc, test_int_d_width_skip);
  tcase_add_test(tc, test_int_d_long_long_w);
  tcase_add_test(tc, test_int_d_huge_width);
  tcase_add_test(tc, test_int_d_multi_type);
  tcase_add_test(tc, test_int_d_long_long_overflow);

  // int i
  tcase_add_test(tc, test_int_i_simple);
  tcase_add_test(tc, test_int_i_dec);
  tcase_add_test(tc, test_int_i_oct);
  tcase_add_test(tc, test_int_i_hex);
  tcase_add_test(tc, test_int_i_hex_zeroes);
  tcase_add_test(tc, test_int_i_all_sys);

  // float f e E g G
  tcase_add_test(tc, test_float_simple);
  tcase_add_test(tc, test_float_size_diff);
  tcase_add_test(tc, test_float_epsilon);
  tcase_add_test(tc, test_float_dots);
  tcase_add_test(tc, test_float_zero_dots);
  tcase_add_test(tc, test_float_skip);
  tcase_add_test(tc, test_float_width);
  tcase_add_test(tc, test_float_nan);
  tcase_add_test(tc, test_float_inf);
  tcase_add_test(tc, test_float_nan_inf);

  // unsigned dec
  tcase_add_test(tc, test_uint_dec_simple);
  tcase_add_test(tc, test_uint_dec_neg);
  tcase_add_test(tc, test_uint_dec_max);
  tcase_add_test(tc, test_uint_dec_overflow);
  tcase_add_test(tc, test_uint_dec_skip_width);
  tcase_add_test(tc, test_uint_dec_short);

  // unsigned octal
  tcase_add_test(tc, test_uint_octal_simple);
  tcase_add_test(tc, test_uint_octal_skip_width);
  tcase_add_test(tc, test_uint_octal_x);
  tcase_add_test(tc, test_uint_octal_fail);

  // unsigned hex
  tcase_add_test(tc, test_uint_hex_simple);
  tcase_add_test(tc, test_uint_hex_x);
  tcase_add_test(tc, test_uint_hex_no_x);
  tcase_add_test(tc, test_uint_hex_skip);
  tcase_add_test(tc, test_uint_hex_fail);

  // pointer
  tcase_add_test(tc, test_pointer_simple);
  tcase_add_test(tc, test_pointer_no_x);
  tcase_add_test(tc, test_pointer_full);
  tcase_add_test(tc, test_pointer_fail);

  // string
  tcase_add_test(tc, test_string_simple);
  tcase_add_test(tc, test_string_spaces);
  tcase_add_test(tc, test_string_skip);
  tcase_add_test(tc, test_string_width);
  tcase_add_test(tc, test_string_together);
  tcase_add_test(tc, test_string_together_width);
  tcase_add_test(tc, test_string_single_char);
  tcase_add_test(tc, test_string_skip_identical);

  // number
  tcase_add_test(tc, test_number_str);
  tcase_add_test(tc, test_number_d);
  tcase_add_test(tc, test_number_only_n);
  tcase_add_test(tc, test_number_empty);

  // percent
  tcase_add_test(tc, test_percent_n);
  tcase_add_test(tc, test_percent_str);

  // complex
  tcase_add_test(tc, test_complex_pattern_1);

  suite_add_tcase(s, tc);

  return s;
}
