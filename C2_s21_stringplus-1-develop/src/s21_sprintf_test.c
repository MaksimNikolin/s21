#include "s21_sprintf_test.h"

START_TEST(test_sprintf1) {
  char result[20];
  char assert[20];
  s21_sprintf(result, "Count: %c", 'a');
  sprintf(assert, "Count: %c", 'a');
  ck_assert_str_eq(result, assert);
}
END_TEST

START_TEST(test_sprintf2) {
  char result[20];
  char assert[20];
  char c = 'b';
  s21_sprintf(result, "Count: %c", c);
  sprintf(assert, "Count: %c", c);
  ck_assert_str_eq(result, assert);
}
END_TEST

START_TEST(test_sprintf3) {
  char result[20];
  char assert[20];
  char c = 'b';
  int a = s21_sprintf(result, "Count: %5c", c);
  int b = sprintf(assert, "Count: %5c", c);
  ck_assert_str_eq(result, assert);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_sprintf4) {
  char result[20];
  char assert[20];
  char c = 'b';
  int a = s21_sprintf(result, "Count: %-5c", c);
  int b = sprintf(assert, "Count: %-5c", c);
  ck_assert_str_eq(result, assert);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_sprintf5) {
  char result[20];
  char assert[20];
  char c = 'a';
  s21_sprintf(result, "Count: %*c", 4, c);
  sprintf(assert, "Count: %*c", 4, c);
  ck_assert_str_eq(result, assert);
}
END_TEST

START_TEST(test_sprintf6) {
  char result[20];
  char assert[20];
  long long d = 5717984;
  s21_sprintf(result, "Count: %Li 1", d);
  sprintf(assert, "Count: %Li 1", d);
  ck_assert_str_eq(result, assert);
}
END_TEST

START_TEST(test_sprintf7) {
  char result[20];
  char assert[20];
  int d = 0;
  s21_sprintf(result, "Count: %d abc", d);
  sprintf(assert, "Count: %d abc", d);
  ck_assert_str_eq(result, assert);
}
END_TEST

START_TEST(test_sprintf8) {
  char result[20];
  char assert[20];
  int d = 1;
  s21_sprintf(result, "Count: % d abc", d);
  sprintf(assert, "Count: % d abc", d);
  ck_assert_str_eq(result, assert);
}
END_TEST

START_TEST(test_sprintf9) {
  char result[20];
  char assert[20];
  int d = -1;
  s21_sprintf(result, "Count: % d abc", d);
  sprintf(assert, "Count: % d abc", d);
  ck_assert_str_eq(result, assert);
}
END_TEST

START_TEST(test_sprintf10) {
  char result[40];
  char assert[40];
  short int i = 32770;
  s21_sprintf(result, "Count: %hi end", i);
  sprintf(assert, "Count: %hi end", i);
  ck_assert_str_eq(result, assert);
}
END_TEST

START_TEST(test_sprintf11) {
  char result[40];
  char assert[40];
  int i = 327710;
  s21_sprintf(result, "Count: %5.10i end", i);
  sprintf(assert, "Count: %5.10i end", i);
  ck_assert_str_eq(result, assert);
}
END_TEST

START_TEST(test_sprintf12) {
  char result[40];
  char assert[40];
  int i = 327710;
  s21_sprintf(result, "Count: %-+10.5i end", i);
  sprintf(assert, "Count: %-+10.5i end", i);
  ck_assert_str_eq(result, assert);
}
END_TEST

START_TEST(test_sprintf13) {
  char result[40];
  char assert[40];
  float f = -123.321;
  s21_sprintf(result, "Count: %f end", f);
  sprintf(assert, "Count: %f end", f);
  ck_assert_str_eq(result, assert);
}
END_TEST

START_TEST(test_sprintf14) {
  char result[40];
  char assert[40];
  float f = 1.1234;
  s21_sprintf(result, "Count: %.*f end", 3, f);
  sprintf(assert, "Count: %.*f end", 3, f);
  ck_assert_str_eq(result, assert);
}
END_TEST

START_TEST(test_sprintf15) {
  char result[40];
  char assert[40];
  float f = -.0000001;
  s21_sprintf(result, "Count: %f end", f);
  sprintf(assert, "Count: %f end", f);
  ck_assert_str_eq(result, assert);
}
END_TEST

START_TEST(test_sprintf16) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%10Lf";
  long double val = 15.35;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf17) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.0Lf";
  long double val = 15.35;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf18) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.Lf";
  long double val = 15.35;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf19) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(
      s21_sprintf(str1, "%f%f%f%f", -999.666, 0.0001, 666.999, -100.001),
      sprintf(str2, "%f%f%f%f", -999.666, 0.0001, 666.999, -100.001));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf20) {
  char result[40];
  char assert[40];
  char *s = "none";
  s21_sprintf(result, "%.6s", s);
  sprintf(assert, "%.6s", s);
  ck_assert_str_eq(result, assert);
}
END_TEST

START_TEST(test_sprintf21) {
  char result[40];
  char assert[40];
  char *s = "stroka s probelom";
  s21_sprintf(result, "%5.6s", s);
  sprintf(assert, "%5.6s", s);
  ck_assert_str_eq(result, assert);
}
END_TEST

START_TEST(test_sprintf22) {
  char result[40];
  char assert[40];
  char *s = "stroka s probelom";
  s21_sprintf(result, "%-5.6s", s);
  sprintf(assert, "%-5.6s", s);
  ck_assert_str_eq(result, assert);
}
END_TEST

START_TEST(test_sprintf23) {
  char result[40];
  char assert[40];
  wchar_t s[] = L"wide chars: ";
  s21_sprintf(result, "%-5.6ls", s);
  sprintf(assert, "%-5.6ls", s);
  ck_assert_str_eq(result, assert);
}
END_TEST

START_TEST(test_sprintf24) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%-15.9s";
  char *val = "21R DSADA SDHASDOAMDSA sdas8d7nasd 111";
  s21_sprintf(str1, format, val), sprintf(str2, format, val);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf25) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%s";
  char *val = "ADibsy8 ndASN) dun8AWn dA 9sDNsa NAID saDYBU DSnaJ Sd";
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf26) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%s%s%s%s";
  char *val = "ADibsy8 ndASN) dun8AWn dA 9sDNsa NAID saDYBU DSnaJ Sd";
  char *s1 = "";
  char *s2 = "87418347813748913749871389480913";
  char *s3 = "HAHAABOBASUCKER";
  ck_assert_int_eq(s21_sprintf(str1, format, val, s1, s2, s3),
                   sprintf(str2, format, val, s1, s2, s3));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf27) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "wchar: %ls";
  wchar_t w[] = L"à";
  int a = s21_sprintf(str1, format, w);
  int b = sprintf(str2, format, w);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_sprintf28) {
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

START_TEST(test_sprintf29) {
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

START_TEST(test_sprintf30) {
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

START_TEST(test_sprintf31) {
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

START_TEST(test_sprintf33) {
  char result[40];
  char assert[40];
  unsigned int u = 2147483647;
  s21_sprintf(result, "Count: %u abc", u);
  sprintf(assert, "Count: %u abc", u);
  ck_assert_str_eq(result, assert);
}
END_TEST

START_TEST(test_sprintf34) {
  char result[40];
  char assert[40];
  unsigned int u = -2147483648;
  s21_sprintf(result, "Count: %u abc", u);
  sprintf(assert, "Count: %u abc", u);
  ck_assert_str_eq(result, assert);
}
END_TEST

START_TEST(test_sprintf35) {
  char result[40];
  char assert[40];
  unsigned long int u = 214748364912;
  s21_sprintf(result, "Count: %lu abc", u);
  sprintf(assert, "Count: %lu abc", u);
  ck_assert_str_eq(result, assert);
}
END_TEST

START_TEST(test_sprintf36) {
  char result[40];
  char assert[40];
  unsigned long int u = -9223372036854775807;
  s21_sprintf(result, "Count: %lu abc", u);
  sprintf(assert, "Count: %lu abc", u);
  ck_assert_str_eq(result, assert);
}
END_TEST

START_TEST(test_sprintf37) {
  char result[40];
  char assert[40];
  unsigned long int u = 9223372036854775807;
  s21_sprintf(result, "Count: %lu abc", u);
  sprintf(assert, "Count: %lu abc", u);
  ck_assert_str_eq(result, assert);
}
END_TEST

START_TEST(test_sprintf38) {
  char result[40];
  char assert[40];
  unsigned short int u = 32767;
  s21_sprintf(result, "Count: %hu abc", u);
  sprintf(assert, "Count: %hu abc", u);
  ck_assert_str_eq(result, assert);
}
END_TEST

START_TEST(test_sprintf39) {
  char result[40];
  char assert[40];
  unsigned short int u = 32770;
  s21_sprintf(result, "Count: %hu end", u);
  sprintf(assert, "Count: %hu end", u);
  ck_assert_str_eq(result, assert);
}
END_TEST

START_TEST(test_sprintf40) {
  char result[40];
  char assert[40];
  unsigned int u = 327710;
  s21_sprintf(result, "Count: %11.10u end", u);
  sprintf(assert, "Count: %11.10u end", u);
  ck_assert_str_eq(result, assert);
}
END_TEST

START_TEST(test_sprintf41) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%g";
  double hex = 0.50300;
  ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf42) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%.g";
  double hex = 0.0004;
  s21_sprintf(str1, format, hex);
  sprintf(str2, format, hex);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf43) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%g";
  double hex = 0;
  s21_sprintf(str1, format, hex);
  sprintf(str2, format, hex);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf44) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%.5g";
  double hex = 0;
  s21_sprintf(str1, format, hex);
  sprintf(str2, format, hex);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf45) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%5g";
  double hex = 0.0000005;
  s21_sprintf(str1, format, hex);
  sprintf(str2, format, hex);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf46) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%5.8g";
  double hex = 0.0000005;
  s21_sprintf(str1, format, hex);
  sprintf(str2, format, hex);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf47) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%g";
  double hex = 0.005;
  s21_sprintf(str1, format, hex);
  sprintf(str2, format, hex);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf48) {
  char str1[BUFF_SIZE] = {'\0'};
  char str2[BUFF_SIZE] = {'\0'};
  char format[] = "%LG";
  long double hex = 0.000005;
  s21_sprintf(str1, format, hex);
  sprintf(str2, format, hex);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf49) {
  char str1[BUFF_SIZE] = {'\0'};
  char str2[BUFF_SIZE] = {'\0'};
  char format[] = "%LG %g %G %Lg %.5g";
  long double hex = 0.000005;
  double hex1 = 41.1341;
  double hex2 = 848.9000;
  long double hex3 = 0.0843;
  double hex4 = 0.0005;
  double hex5 = 0.8481481;
  s21_sprintf(str1, format, hex, hex1, hex2, hex3, hex4, hex5);
  sprintf(str2, format, hex, hex1, hex2, hex3, hex4, hex5);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf50) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.17Le";
  long double val = 15.35;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf51) {
  char str1[BUFF_SIZE] = {'\0'};
  char str2[BUFF_SIZE] = {'\0'};
  char *format = "%015E";
  float val = 0;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf52) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%15e";
  float val = 0;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf53) {
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

START_TEST(test_sprintf54) {
  char str1[BUFF_SIZE] = {'\0'};
  char str2[BUFF_SIZE] = {'\0'};
  char *format = "%.17LE";
  long double val = 4134121;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf55) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  ck_assert_int_eq(s21_sprintf(str1, "abc"), sprintf(str2, "abc"));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf56) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  ck_assert_int_eq(s21_sprintf(str1, "abc"), sprintf(str2, "abc"));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf57) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%15o";
  int val = 14140;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf58) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%-16o";
  int val = 14140;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf59) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.51o";
  int val = 14140;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf60) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%-5.51o";
  int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf61) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.15x";
  unsigned val = 858158158;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf62) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%#-5.10x";
  unsigned val = 858158158;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf63) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%#x";
  unsigned val = 0;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf64) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%#x";
  unsigned val = 18571;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf65) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%#hx";
  unsigned short val = 12352;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf66) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%#lx";
  unsigned long val = 18571757371571;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf67) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%#2x";
  unsigned val = 1;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf68) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%#30x";
  unsigned val = 1;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf69) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%p";
  s21_sprintf(str1, format, format);
  sprintf(str2, format, format);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf70) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%15p";
  s21_sprintf(str1, format, format);
  sprintf(str2, format, format);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf71) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.5p";
  s21_sprintf(str1, format, format);
  sprintf(str2, format, format);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf72) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%p";
  char *ptr = "(nil)";
  s21_sprintf(str1, format, ptr);
  sprintf(str2, format, ptr);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf73) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  int ret = 0;
  char *format = "How many chars written before n %n";
  s21_sprintf(str1, format, &ret);
  sprintf(str2, format, &ret);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf74) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  int n1;
  int n2;
  s21_sprintf(str1, "%d%n", 123, &n1);
  sprintf(str2, "%d%n", 123, &n2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf75) {
  char str1[200];
  char str2[200];
  char *str3 = "%G TEST %.G TEST %4G TEST %4.G TEST %5.10G!";
  double num = 76.756589367;
  sprintf(str1, str3, num, num, num, num, num);
  s21_sprintf(str2, str3, num, num, num, num, num);
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf76) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %+- 14G!test: %+ 10G!test: % +25G!";
  double num = -365789.34;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf77) {
  char str1[400];
  char str2[400];
  char *str3 = "test: % 14G!test: % -27G!test: %- 19G!";
  double num = 365789.34;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf78) {
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

START_TEST(test_sprintf79) {
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

START_TEST(test_sprintf81) {
  char str1[100] = "";
  char str2[100] = "";
  char *str3 = "%%Test %d Test";
  int a = 12;
  ck_assert_int_eq(sprintf(str1, str3, a), s21_sprintf(str2, str3, a));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf82) {
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

Suite *s21_sprintf_suite() {
  Suite *s2 = suite_create(
      "////////////////////////////    sprintf_test    "
      "////////////////////////////");
  TCase *tc = tcase_create("sprintf_tc");

  // ilynpois

  tcase_add_test(tc, test_sprintf1);
  tcase_add_test(tc, test_sprintf2);
  tcase_add_test(tc, test_sprintf3);
  tcase_add_test(tc, test_sprintf4);
  tcase_add_test(tc, test_sprintf5);
  tcase_add_test(tc, test_sprintf6);
  tcase_add_test(tc, test_sprintf7);
  tcase_add_test(tc, test_sprintf8);
  tcase_add_test(tc, test_sprintf9);
  tcase_add_test(tc, test_sprintf10);
  tcase_add_test(tc, test_sprintf11);
  tcase_add_test(tc, test_sprintf12);
  tcase_add_test(tc, test_sprintf13);
  tcase_add_test(tc, test_sprintf14);
  tcase_add_test(tc, test_sprintf15);
  tcase_add_test(tc, test_sprintf16);
  tcase_add_test(tc, test_sprintf17);
  tcase_add_test(tc, test_sprintf18);
  tcase_add_test(tc, test_sprintf19);
  tcase_add_test(tc, test_sprintf20);
  tcase_add_test(tc, test_sprintf21);
  tcase_add_test(tc, test_sprintf22);
  tcase_add_test(tc, test_sprintf23);
  tcase_add_test(tc, test_sprintf24);
  tcase_add_test(tc, test_sprintf25);
  tcase_add_test(tc, test_sprintf26);
  tcase_add_test(tc, test_sprintf27);
  tcase_add_test(tc, test_sprintf28);
  tcase_add_test(tc, test_sprintf29);
  tcase_add_test(tc, test_sprintf30);
  tcase_add_test(tc, test_sprintf31);
  tcase_add_test(tc, test_sprintf33);
  tcase_add_test(tc, test_sprintf34);
  tcase_add_test(tc, test_sprintf35);
  tcase_add_test(tc, test_sprintf36);
  tcase_add_test(tc, test_sprintf37);
  tcase_add_test(tc, test_sprintf38);
  tcase_add_test(tc, test_sprintf39);
  tcase_add_test(tc, test_sprintf40);
  tcase_add_test(tc, test_sprintf41);
  tcase_add_test(tc, test_sprintf42);
  tcase_add_test(tc, test_sprintf43);
  tcase_add_test(tc, test_sprintf44);
  tcase_add_test(tc, test_sprintf45);
  tcase_add_test(tc, test_sprintf46);
  tcase_add_test(tc, test_sprintf47);
  tcase_add_test(tc, test_sprintf48);
  tcase_add_test(tc, test_sprintf49);
  tcase_add_test(tc, test_sprintf50);
  tcase_add_test(tc, test_sprintf51);
  tcase_add_test(tc, test_sprintf52);
  tcase_add_test(tc, test_sprintf53);
  tcase_add_test(tc, test_sprintf54);
  tcase_add_test(tc, test_sprintf55);
  tcase_add_test(tc, test_sprintf56);
  tcase_add_test(tc, test_sprintf57);
  tcase_add_test(tc, test_sprintf58);
  tcase_add_test(tc, test_sprintf59);
  tcase_add_test(tc, test_sprintf60);
  tcase_add_test(tc, test_sprintf61);
  tcase_add_test(tc, test_sprintf62);
  tcase_add_test(tc, test_sprintf63);
  tcase_add_test(tc, test_sprintf64);
  tcase_add_test(tc, test_sprintf65);
  tcase_add_test(tc, test_sprintf66);
  tcase_add_test(tc, test_sprintf67);
  tcase_add_test(tc, test_sprintf68);
  tcase_add_test(tc, test_sprintf69);
  tcase_add_test(tc, test_sprintf70);
  tcase_add_test(tc, test_sprintf71);
  tcase_add_test(tc, test_sprintf72);
  tcase_add_test(tc, test_sprintf73);
  tcase_add_test(tc, test_sprintf74);

  // daisymal

  tcase_add_test(tc, test_sprintf75);
  tcase_add_test(tc, test_sprintf76);
  tcase_add_test(tc, test_sprintf77);
  tcase_add_test(tc, test_sprintf78);
  tcase_add_test(tc, test_sprintf79);
  tcase_add_test(tc, test_sprintf81);
  tcase_add_test(tc, test_sprintf82);

  suite_add_tcase(s2, tc);

  return s2;
}