#include "s21_sscanf_test.h"

// d opt
START_TEST(test_sscanf_d_opt_1) {
  char *str = "";
  char *format = "%d";
  int a1 = 1, a2 = 0;
  int res1 = s21_sscanf(str, format, &a1);
  int res2 = sscanf(str, format, &a2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_sscanf_d_opt_2) {
  char *str = "3134";
  char *format = "%1553424lld %2lld %1lld";
  long long a1 = 1, a2 = 0, b1 = 1, b2 = 0, c1 = 1, c2 = 0;
  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_sscanf_d_opt_3) {
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

START_TEST(test_sscanf_d_opt_4) {
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

START_TEST(test_sscanf_d_opt_5) {
  char *str = "31347483647 -14748364 33";
  char *format = "%ld %n %ld %ln %ld";
  long a1 = 1, a2 = 0, b1 = 1, b2 = 0, c1 = 1, c2 = 0;
  int n1 = -1, n2 = -2;
  long h1 = -1, h2 = -2;
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

START_TEST(test_sscanf_d_opt_6) {
  int32_t a1, a2;
  int32_t b1, b2;
  const char str[] = "12 keppa 12";
  const char fstr[] = "%d keppa %d";
  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
}
END_TEST

START_TEST(test_sscanf_d_opt_7) {
  int32_t a1, a2;
  int32_t b1, b2;
  const char str[] = "12keppa12";
  const char fstr[] = "%dkeppa%d";
  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
}
END_TEST

START_TEST(test_sscanf_d_opt_8) {
  int32_t a1, a2;
  int32_t b1 = 0, b2 = 0;
  const char str[] = "12keppa12";
  const char fstr[] = "%dkeppapos%d";
  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
}
END_TEST

START_TEST(test_sscanf_d_opt_9) {
  int32_t a1, a2;
  int32_t b1 = 80, b2 = 33;
  int32_t c1 = 55, c2 = 33;
  const char str[] = "12 % 13 % 14";
  const char fstr[] = "%d %% %d %% %d";
  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_sscanf_d_opt_10) {
  int32_t a1, a2;
  int32_t b1 = 80, b2 = 33;
  int32_t c1 = 55, c2 = 33;
  const char str[] = "12%13%14";
  const char fstr[] = "%d%%%d%%%d";
  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_sscanf_d_opt_11) {
  int32_t a1 = 1234, a2 = 33333;
  const char str[] = "%%%16";
  const char fstr[] = "%%%%%%%d";
  int32_t res1 = s21_sscanf(str, fstr, &a1);
  int32_t res2 = sscanf(str, fstr, &a2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(test_sscanf_d_opt_12) {
  int32_t a1 = 1234, a2 = 33333;
  int32_t b1 = 1234, b2 = 33333;
  const char str[] = "%%123%888";
  const char fstr[] = "%%%%%d%%%d";
  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
}
END_TEST

// i opt
START_TEST(test_sscanf_i_opt_1) {
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

// f opt
START_TEST(test_sscanf_f_opt_1) {
  float x, y;
  int result = s21_sscanf("3.14 -1.23", "%f %f", &x, &y);
  ck_assert_int_eq(result, 2);
  ck_assert_float_eq_tol(x, 3.14, 0.01);
  ck_assert_float_eq_tol(y, -1.23, 0.01);
}
END_TEST

START_TEST(test_sscanf_f_opt_2) {
  char format[100] = "%14f%3f\t%2f%1f";
  char str[100] = "1.123 -0.0021 12.00001 3.01010202";
  int o1, o2, o3, o4, s1, s2, s3, s4;
  int original = sscanf(str, format, &o1, &o2, &o3, &o4);
  int s21_func = s21_sscanf(str, format, &s1, &s2, &s3, &s4);
  ck_assert_int_eq(original, s21_func);
  ck_assert_int_eq(o1, s1);
  ck_assert_int_eq(o2, s2);
  ck_assert_int_eq(o3, s3);
  ck_assert_int_eq(o4, s4);
}
END_TEST

START_TEST(test_sscanf_f_opt_3) {
  char format[100] = "%14Lf%3Lf\t%2Lf%1Lf";
  char str[100] = "-1.1e3 0.0021 12.00001 +13.010102e2";
  long double o1, o2, o3, o4, s1, s2, s3, s4;
  int original = sscanf(str, format, &o1, &o2, &o3, &o4);
  int s21_func = s21_sscanf(str, format, &s1, &s2, &s3, &s4);
  ck_assert_int_eq(original, s21_func);
  ck_assert_int_eq(o1, s1);
  ck_assert_int_eq(o2, s2);
  ck_assert_int_eq(o3, s3);
  ck_assert_int_eq(o4, s4);
}
END_TEST

START_TEST(test_sscanf_f_opt_4) {
  char format[] = "%lf %lf %lf %lf";
  char str[] = "NAN nan -INF +inf";
  double o1, o2, o3, o4, s1, s2, s3, s4;
  int original = sscanf(str, format, &o1, &o2, &o3, &o4);
  int s21_func = s21_sscanf(str, format, &s1, &s2, &s3, &s4);
  ck_assert_int_eq(original, s21_func);
  ck_assert_double_nan(o1);
  ck_assert_double_nan(s1);
  ck_assert_double_nan(o2);
  ck_assert_double_nan(s2);
  ck_assert_double_eq(o3, s3);
  ck_assert_double_eq(o4, s4);
}
END_TEST

START_TEST(test_sscanf_f_opt_5) {
  char fstr[] = "%f%f%f%*f%f";
  char str[] = "1.111 nan inF 0 3333.3333";
  float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(a1, a2);
  ck_assert_float_nan(b1);
  ck_assert_float_infinite(c1);
  ck_assert_float_eq(d1, d2);
}
END_TEST

START_TEST(test_sscanf_f_opt_6) {
  char fstr[] = "   \n\n %f  \n\n\n \t %f     %f   =    %f";
  char str[] = "1243.567e-2 -1243.567e+20 +777e-5   =  \n    1e+1";
  float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
  ck_assert_float_eq(d1, d2);
}
END_TEST

START_TEST(test_sscanf_f_opt_7) {
  char fstr[] = "%Lf%Lf%Lf%Lf%Lf";
  char str[] = "1. .1 .  .  .  777.777 00000000.0000001 100000000000.000000001";
  long double a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0;
  long double d1 = 0, d2 = 0, e1 = 0, e2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1, &e1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2, &e2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ldouble_eq(a1, a2);
  ck_assert_ldouble_eq_tol(b1, b2, EPS);
  ck_assert_ldouble_eq(c1, c2);
  ck_assert_ldouble_eq(d1, d2);
  ck_assert_ldouble_eq(e1, e2);
}
END_TEST

START_TEST(test_sscanf_f_opt_8) {
  char fstr[] = "   \n\n %Lf  \n\n\n \t %Lf     %Lf   =    %Lf";
  char str[] = "1243.567e-2 -1243.567e+10 +777e-5   =  \n    1e+1";
  long double a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ldouble_eq_tol(b1, b2, EPS);
  ck_assert_ldouble_eq_tol(c1, c2, EPS);
  ck_assert_ldouble_eq(d1, d2);
}
END_TEST

START_TEST(test_sscanf_f_opt_9) {
  char format[] = "%f %f %f %f";
  char str[] = "NAN nan -INF +inf";
  float d1, d2;
  float q1, q2;
  float z1, z2;
  float w1, w2;
  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1, &w1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_nan(d1);
  ck_assert_float_nan(d2);
  ck_assert_float_nan(q1);
  ck_assert_float_nan(q2);
  ck_assert_float_eq(z1, z2);
}
END_TEST

START_TEST(test_sscanf_f_opt_10) {
  char format[] = "%f";
  char str[] = "Nap";
  float d1 = 0, d2 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(d1, d2);
}
END_TEST

START_TEST(test_sscanf_f_opt_11) {
  char format[] = "%f";
  char str[] = "Np";
  float d1 = 0, d2 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(d1, d2);
}
END_TEST

START_TEST(test_sscanf_f_opt_12) {
  char format[] = "%f";
  char str[] = "id";
  float d1 = 0, d2 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(d1, d2);
}
END_TEST

START_TEST(test_sscanf_f_opt_13) {
  char format[] = "%f";
  char str[] = "\r";
  float d1 = 0, d2 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(d1, d2);
}
END_TEST

START_TEST(test_sscanf_f_opt_14) {
  char format[] = "%f";
  char str[] = "\x0B";
  float d1 = 0, d2 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(d1, d2);
}
END_TEST

START_TEST(test_sscanf_f_opt_15) {
  char format[] = "%f";
  char str[] = "\f";
  float d1 = 0, d2 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(d1, d2);
}
END_TEST

// g opt
START_TEST(test_sscanf_g_opt_1) {
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

START_TEST(test_sscanf_g_opt_2) {
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

// u opt
START_TEST(test_sscanf_u_opt_1) {
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

// o opt
START_TEST(test_sscanf_o_opt_1) {
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

START_TEST(test_sscanf_o_opt_2) {
  char *str = "-09 -056 0x 0123 0714 -0123456777";
  char *format = "%lo %lo %*lo %lo";
  unsigned long a1 = 1, a2 = 0, b1 = 1, b2 = 0, c1 = 1, c2 = 0;
  int res1 = s21_sscanf(str, format, &a1, &b1, &c1);
  int res2 = sscanf(str, format, &a2, &b2, &c2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

// x opt
START_TEST(test_sscanf_x_opt_1) {
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

START_TEST(test_sscanf_x_opt_2) {
  uint32_t a1, a2;
  const char str[] = "qF";
  const char fstr[] = "%X";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

// p opt
START_TEST(test_sscanf_p_opt_1) {
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

START_TEST(test_sscanf_p_opt_2) {
  char format[] = "%p";
  char str[] = "0x0000";
  int *p1 = 0, *p2 = 0;
  int16_t res1 = s21_sscanf(str, format, &p1);
  int16_t res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(test_sscanf_p_opt_3) {
  char format[] = "%*p";
  char str[] = "0x0000";
  int *p1 = 0, *p2 = 0;
  int16_t res1 = s21_sscanf(str, format, &p1);
  int16_t res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

// s opt
START_TEST(test_sscanf_s_opt_1) {
  char *str = "   \tHello\n  \n \t\tNew World   \n";
  char *format = "%s %s %s";
  char a1[SIZE] = {0}, a2[SIZE] = {0};
  char b1[SIZE] = {0}, b2[SIZE] = {0};
  char c1[SIZE] = {0}, c2[SIZE] = {0};
  int res1 = s21_sscanf(str, format, a1, b1, c1);
  int res2 = sscanf(str, format, a2, b2, c2);
  ck_assert_str_eq(a1, a2);
  ck_assert_str_eq(b1, b2);
  ck_assert_str_eq(c1, c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_sscanf_s_opt_2) {
  char format[100] = "%s %s %s %s";
  char str[100] = "test test2 test3 test4";
  char o1[100], o2[100], o3[100], o4[100];
  char s1[100], s2[100], s3[100], s4[100];
  int original = sscanf(str, format, &o1, &o2, &o3, &o4);
  int s21_func = s21_sscanf(str, format, &s1, &s2, &s3, &s4);
  ck_assert_int_eq(original, s21_func);
  ck_assert_str_eq(o1, s1);
  ck_assert_str_eq(o2, s2);
  ck_assert_str_eq(o3, s3);
  ck_assert_str_eq(o4, s4);
}
END_TEST

START_TEST(test_sscanf_s_opt_3) {
  char s1[BUFF_SIZE] = {'\0'}, s2[BUFF_SIZE] = {'\0'};
  char s3[BUFF_SIZE] = {'\0'}, s4[BUFF_SIZE] = {'\0'};
  char s5[BUFF_SIZE] = {'\0'}, s6[BUFF_SIZE] = {'\0'};
  char s7[BUFF_SIZE] = {'\0'}, s8[BUFF_SIZE] = {'\0'};
  const char str[] = "aboba\tshlepa\tasdfasdf\tasdfasdf";
  const char fstr[] = "%s%s%s%s";
  int16_t res1 = s21_sscanf(str, fstr, s1, s2, s3, s4);
  int16_t res2 = sscanf(str, fstr, s5, s6, s7, s8);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(s1, s5);
  ck_assert_str_eq(s2, s6);
  ck_assert_str_eq(s3, s7);
  ck_assert_str_eq(s4, s8);
}
END_TEST

START_TEST(test_sscanf_s_opt_4) {
  char format[100] = "%0hs";
  char str[100] = "test test2 test3 test4";
  char o1[100], o2[100], o3[100], o4[100];
  char s1[100], s2[100], s3[100], s4[100];
  int original = sscanf(str, format, &o1, &o2, &o3, &o4);
  int s21_func = s21_sscanf(str, format, &s1, &s2, &s3, &s4);
  ck_assert_int_eq(original, s21_func);
  ck_assert_str_eq(o1, s1);
  ck_assert_str_eq(o2, s2);
  ck_assert_str_eq(o3, s3);
  ck_assert_str_eq(o4, s4);
}
END_TEST

START_TEST(test_sscanf_s_opt_5) {
  char format[100] = "%0ls";
  char str[100] = "test test2 test3 test4";
  char o1[100], o2[100], o3[100], o4[100];
  char s1[100], s2[100], s3[100], s4[100];
  int original = sscanf(str, format, &o1, &o2, &o3, &o4);
  int s21_func = s21_sscanf(str, format, &s1, &s2, &s3, &s4);
  ck_assert_int_eq(original, s21_func);
  ck_assert_str_eq(o1, s1);
  ck_assert_str_eq(o2, s2);
  ck_assert_str_eq(o3, s3);
  ck_assert_str_eq(o4, s4);
}
END_TEST

// c opt
START_TEST(test_sscanf_c_opt_1) {
  char fstr[] = "%1c %c %c %0c";
  char str[] = "z *'@";
  int16_t a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(test_sscanf_c_opt_2) {
  char fstr[] = "%#lc";
  char str[] = "z *'@";
  int16_t a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

// percent
START_TEST(test_sscanf_perc_opt_1) {
  char str[] = "";
  char format[] = "%Q";
  int p1, p2;
  int res1 = s21_sscanf(str, format, &p1);
  int res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_sscanf_perc_opt_2) {
  char *str = "%Hello% New %%World";
  char *format = "%%%s%% %s %%%%%s";
  char a1[SIZE] = {0}, a2[SIZE] = {0};
  char b1[SIZE] = {0}, b2[SIZE] = {0};
  char c1[SIZE] = {0}, c2[SIZE] = {0};
  int res1 = s21_sscanf(str, format, a1, b1, c1);
  int res2 = sscanf(str, format, a2, b2, c2);
  ck_assert_str_eq(a1, a2);
  ck_assert_str_eq(b1, b2);
  ck_assert_str_eq(c1, c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_sscanf_perc_opt_3) {
  const char str[] = "%%%";
  const char fstr[] = "%%%%%%";
  int32_t res1 = s21_sscanf(str, fstr);
  int32_t res2 = sscanf(str, fstr);
  ck_assert_int_eq(res1, res2);
}
END_TEST

// multi opts
START_TEST(test_sscanf_mult_opt_1) {
  char fstr[] = "%p   %p%%\n\n\n %p%n";
  char str[] = "0xFEDCBA9876543210 0xFFFFFFFFFFFFFFFFFF % 0x01";
  int *a1 = 0, *a2 = 0, *b1 = 0, *b2 = 0, *c1 = 0, *c2 = 0, d1 = 0, d2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(a1, a2);
  ck_assert_ptr_eq(b1, b2);
  ck_assert_ptr_eq(c1, c2);
}
END_TEST

START_TEST(test_sscanf_mult_opt_2) {
  char fstr[] = "%n%p%p%n";
  char str[] = "0xFEDCBA9876543210 0xFFFFFFFFFFFFFFFFFF1";
  int a1 = 111, a2 = 111, *b1 = 0, *b2 = 0, *c1 = 0, *c2 = 0, d1 = 0, d2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_ptr_eq(b1, b2);
  ck_assert_ptr_eq(c1, c2);
}
END_TEST

START_TEST(test_sscanf_mult_opt_3) {
  short int b1 = 0, b2 = 0;
  long int d1 = 0, d2 = 0;
  char c1 = 0, c2 = 0;
  const char str[] = "a 12 12";
  const char fstr[] = "%c %hi %li";
  int32_t res1 = s21_sscanf(str, fstr, &c1, &b1, &d1);
  int32_t res2 = sscanf(str, fstr, &c2, &b2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(test_sscanf_mult_opt_4) {
  char *str = "L   Ogewfgw sdfL";
  char *format = "%1s%1s%*s%hn%*3s%1s%n";
  char a1[SIZE] = {0}, a2[SIZE] = {0};
  char b1[SIZE] = {0}, b2[SIZE] = {0};
  char c1[SIZE] = {0}, c2[SIZE] = {0};
  short n1 = -1, n2 = -2;
  int h1 = -1, h2 = -2;
  int res1 = s21_sscanf(str, format, a1, b1, &n1, c1, &h1);
  int res2 = sscanf(str, format, a2, b2, &n2, c2, &h2);
  ck_assert_str_eq(a1, "L");
  ck_assert_str_eq(b1, "O");
  ck_assert_str_eq(c1, "L");
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(h1, h2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_sscanf_mult_opt_5) {
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

START_TEST(test_sscanf_mult_opt_6) {
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

// another
START_TEST(test_sscanf_an_opt_1) {
  char format[] = "\x0B";
  char str[] = "$\0!";
  int *p1 = 0, *p2 = 0;
  int16_t res1 = s21_sscanf(str, format, &p1);
  int16_t res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(test_sscanf_an_opt_2) {
  char format[] = "\r";
  char str[] = "$\0!";
  int *p1 = 0, *p2 = 0;
  int16_t res1 = s21_sscanf(str, format, &p1);
  int16_t res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

Suite *s21_sscanf_suite() {
  Suite *s;
  TCase *tc;

  s = suite_create(
      "////////////////////////////     sscanf_test     "
      "////////////////////////////");
  tc = tcase_create("sscanf_tc");

  tcase_add_test(tc, test_sscanf_d_opt_1);
  tcase_add_test(tc, test_sscanf_d_opt_2);
  tcase_add_test(tc, test_sscanf_d_opt_3);
  tcase_add_test(tc, test_sscanf_d_opt_4);
  tcase_add_test(tc, test_sscanf_d_opt_5);
  tcase_add_test(tc, test_sscanf_d_opt_6);
  tcase_add_test(tc, test_sscanf_d_opt_7);
  tcase_add_test(tc, test_sscanf_d_opt_8);
  tcase_add_test(tc, test_sscanf_d_opt_9);
  tcase_add_test(tc, test_sscanf_d_opt_10);
  tcase_add_test(tc, test_sscanf_d_opt_11);
  tcase_add_test(tc, test_sscanf_d_opt_12);
  tcase_add_test(tc, test_sscanf_i_opt_1);
  tcase_add_test(tc, test_sscanf_f_opt_1);
  tcase_add_test(tc, test_sscanf_f_opt_2);
  tcase_add_test(tc, test_sscanf_f_opt_3);
  tcase_add_test(tc, test_sscanf_f_opt_4);
  tcase_add_test(tc, test_sscanf_f_opt_5);
  tcase_add_test(tc, test_sscanf_f_opt_6);
  tcase_add_test(tc, test_sscanf_f_opt_7);
  tcase_add_test(tc, test_sscanf_f_opt_8);
  tcase_add_test(tc, test_sscanf_f_opt_9);
  tcase_add_test(tc, test_sscanf_f_opt_10);
  tcase_add_test(tc, test_sscanf_f_opt_11);
  tcase_add_test(tc, test_sscanf_f_opt_12);
  tcase_add_test(tc, test_sscanf_f_opt_13);
  tcase_add_test(tc, test_sscanf_f_opt_14);
  tcase_add_test(tc, test_sscanf_f_opt_15);
  tcase_add_test(tc, test_sscanf_g_opt_1);
  tcase_add_test(tc, test_sscanf_g_opt_2);
  tcase_add_test(tc, test_sscanf_u_opt_1);
  tcase_add_test(tc, test_sscanf_o_opt_1);
  tcase_add_test(tc, test_sscanf_o_opt_2);
  tcase_add_test(tc, test_sscanf_x_opt_1);
  tcase_add_test(tc, test_sscanf_x_opt_2);
  tcase_add_test(tc, test_sscanf_p_opt_1);
  tcase_add_test(tc, test_sscanf_p_opt_2);
  tcase_add_test(tc, test_sscanf_p_opt_3);
  tcase_add_test(tc, test_sscanf_s_opt_1);
  tcase_add_test(tc, test_sscanf_s_opt_2);
  tcase_add_test(tc, test_sscanf_s_opt_3);
  tcase_add_test(tc, test_sscanf_s_opt_4);
  tcase_add_test(tc, test_sscanf_s_opt_5);
  tcase_add_test(tc, test_sscanf_c_opt_1);
  tcase_add_test(tc, test_sscanf_c_opt_2);
  tcase_add_test(tc, test_sscanf_perc_opt_1);
  tcase_add_test(tc, test_sscanf_perc_opt_2);
  tcase_add_test(tc, test_sscanf_perc_opt_3);
  tcase_add_test(tc, test_sscanf_mult_opt_1);
  tcase_add_test(tc, test_sscanf_mult_opt_2);
  tcase_add_test(tc, test_sscanf_mult_opt_3);
  tcase_add_test(tc, test_sscanf_mult_opt_4);
  tcase_add_test(tc, test_sscanf_mult_opt_5);
  tcase_add_test(tc, test_sscanf_mult_opt_6);
  tcase_add_test(tc, test_sscanf_an_opt_1);
  tcase_add_test(tc, test_sscanf_an_opt_2);

  suite_add_tcase(s, tc);

  return s;
}
