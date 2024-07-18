#include "s21_sprintf_test.h"

START_TEST(simple_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "This is a simple value %d";
  int val = 69;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(precise_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.5i";
  int val = 69;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(width_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%5d";
  int val = 69;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(minus_width_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%-5i";
  int val = 69;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(plus_width_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%+12d";
  int val = 69;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(padding_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%012i";
  int val = 69;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(star_width_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%0*d";
  int val = 69;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, 5, val),
                             sprintf(str2, format, 5, val));
}
END_TEST

START_TEST(star_precision_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%0.*i";
  int val = 69;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, 5, val),
                             sprintf(str2, format, 5, val));
}
END_TEST

START_TEST(many_flags_many_ints) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%0.*i %d %4.*i %013d %d";
  int val = 69;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(
                s21_sprintf(str1, format, 5, val, -10431, 13, 5311, 0,
                            -581813581),
                sprintf(str2, format, 5, val, -10431, 13, 5311, 0, -581813581));
}
END_TEST

START_TEST(flags_long_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%+5.31li";
  long int val = 698518581899;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(flags_short_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%-16.9hi";
  short int val = 6958;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(flags_another_long_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%0.*ld";
  long val = 8581385185;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, 5, val),
                             sprintf(str2, format, 5, val));
}
END_TEST

START_TEST(zero_precision_zero_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.0d";
  int val = 0;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(space_flag_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "% d";
  int val = 0;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(unsigned_val) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%u";
  unsigned int val = 14140;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(unsigned_val_width) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%15u";
  unsigned int val = 14140;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(unsigned_val_flags) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%-16u";
  unsigned int val = 14140;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(unsigned_val_precision) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.51u";
  unsigned int val = 14140;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(unsigned_val_many_flags) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "% 5.51u";
  unsigned int val = 14140;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(unsigned_val_short) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%hu";
  unsigned short int val = 14140;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(unsigned_val_long) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%lu";
  unsigned long int val = 949149114140;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(unsigned_val_many) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%lu, %u, %hu, %.5u, %5.u";
  unsigned long int val = 949149114140;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(
                s21_sprintf(str1, format, val, 14, 1441, 14414, 9681),
                sprintf(str2, format, val, (unsigned)14, (unsigned short)1441,
                        (unsigned)14414, (unsigned)9681));
}
END_TEST

START_TEST(octal_width) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%15o";
  int val = 14140;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(octal_flags) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%-16o";
  int val = 14140;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(octal_precision) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.51o";
  int val = 14140;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(octal_many_flags) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%-5.51o";
  int val = 14140;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(octal_zero) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%o";
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, 0),
                             sprintf(str2, format, 0));
}
END_TEST

START_TEST(octal_hash) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%#o";
  int val = 57175;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(octal_short) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%hd";
  short int val = 14140;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(octal_long) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%lo";
  long int val = 949149114140;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(octal_many) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%lo, %o, %ho, %.5o, %5.o";
  long int val = 949149114140;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(
                s21_sprintf(str1, format, val, 14, 1441, 14414, 9681),
                sprintf(str2, format, val, (unsigned)14, (unsigned short)1441,
                        (unsigned)14414, (unsigned)9681));
}
END_TEST

START_TEST(octal) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%lo";
  long int val = 84518;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(unsigned_zero) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%u";
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, 0),
                             sprintf(str2, format, (unsigned)0));
}
END_TEST

START_TEST(hex_width) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%5x";
  unsigned val = 858158158;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(hex_flags) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%#-10x";
  unsigned val = 858158158;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(hex_precision) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.15x";
  unsigned val = 858158158;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(hex_many) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%#-10x%x%X%#x%#X%5.5x";
  unsigned val = 858158158;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(
                s21_sprintf(str1, format, val, val, val, val, val, val),
                sprintf(str2, format, val, val, val, val, val, val));
}
END_TEST

START_TEST(hex_many_flags) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%#-5.10x";
  unsigned val = 858158158;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(hex_zero) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%#x";
  unsigned val = 0;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(hex_huge) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%#x";
  unsigned val = 18571;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(hex_short) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%#hx";
  unsigned short val = 12352;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(hex_long) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%#lx";
  unsigned long val = 18571757371571;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(hex_one_longer_width) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%#2x";
  unsigned val = 1;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(hex_two_longer_width) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%#30x";
  unsigned val = 1;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(one_char) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%c";
  char val = 'X';
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(one_precision) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.5c";
  char val = 'c';
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(one_flags) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "% -5c";
  char val = 'c';
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(one_width) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%15c";
  char val = 'c';
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(one_many) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%-5.3c%c%c%c%c Hello! ABOBA";
  char val = 'c';
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val, 'c', 'a', 'b', 'b'),
                             sprintf(str2, format, val, 'c', 'a', 'b', 'b'));
}
END_TEST

START_TEST(one_many_flags) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%-5.3c";
  char val = 'c';
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(string) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%s";
  char *val = "I LOVE STRINGS AND TESTS AND SCHOOL21 NO JOKE";
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(string_precision) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.15s";
  char *val = "I LOVE STRINGS AND TESTS AND SCHOOL21 NO JOKE";
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(string_width) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%15s";
  char *val = "69 IS MY FAVORITE NUMBER";
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(string_flags) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%-15.9s";
  char *val = "69 IS MY FAVORITE NUMBER";
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(string_long) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%s";
  char *val =
      "69 IS MY FAVORITE NUMBER THIS IS SUPPOSED TO BE A VERY LONG STRING";
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(string_many) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%s%s%s%s";
  char *val =
      "69 IS MY FAVORITE NUMBER THIS IS SUPPOSED TO BE A VERY LONG STRING";
  char *s1 = "";
  char *s2 = "87418347813748913749871389480913";
  char *s3 = "HAHAABOBASUCKER";
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val, s1, s2, s3),
                             sprintf(str2, format, val, s1, s2, s3));
}
END_TEST

START_TEST(ptr) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%p";
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, format),
                             sprintf(str2, format, format));
}
END_TEST

START_TEST(ptr_width) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%15p";
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, format),
                             sprintf(str2, format, format));
}
END_TEST

START_TEST(ptr_precision) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.5p";
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, format),
                             sprintf(str2, format, format));
}
END_TEST

START_TEST(null_ptr) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%s";
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, "(null)"),
                             sprintf(str2, format, "(null)"));
}
END_TEST

START_TEST(string_width_huge) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *val = "kjafdiuhfjahfjdahf";
  char *format = "%120s";
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(n_specifier) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  int ret = 0;
  char *format = "Hello, my sexy little aboba abobushka abobina %n";
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, &ret),
                             sprintf(str2, format, &ret));
}
END_TEST

START_TEST(float_precision) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%Lf";
  long double val = 513515.131513115151351;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(float_width) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%10Lf";
  long double val = 15.35;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(float_precision_zero) {
  char str1[100], str2[100];
  float val = 123.0f;
  const char *format = "%f";
  int s21_ret = s21_sprintf(str1, format, val);
  int sprintf_ret = snprintf(str2, sizeof(str2), format, val);
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++) ck_assert_int_eq(s21_ret, sprintf_ret);
}
END_TEST

START_TEST(float_precision_empty) {
  char str1[100], str2[100];
  float val = 123.0f;
  const char *format = "%.1f";
  int s21_ret = s21_sprintf(str1, format, val);
  int sprintf_ret = snprintf(str2, sizeof(str2), format, val);
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++) ck_assert_int_eq(s21_ret, sprintf_ret);
}
END_TEST

START_TEST(float_precision_huge) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.15Lf";
  long double val = 15.35;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(float_precision_huge_negative) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.15Lf";
  long double val = -15.35581134;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(float_huge) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%Lf";
  long double val = 72537572375.1431341;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(float_flags) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "% f";
  float val = 0;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(float_many) {
  char str1[1000], str2[1000];
  float val = 123.456f, val1 = -123.456f, val2 = 789.0f, val3 = -789.0f,
        val4 = 0.0f, val5 = 1234567.0f;
  const char *format = "%f %f %f %f %f %f";
  int s21_ret = s21_sprintf(str1, format, val, val1, val2, val3, val4, val5);
  int sprintf_ret = sprintf(str2, format, val, val1, val2, val3, val4, val5);
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++) ck_assert_int_eq(s21_ret, sprintf_ret);
}
END_TEST

START_TEST(e_precision) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.12Le";
  long double val = 15.35;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(e_precision_zero) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.0Le";
  long double val = 15.35;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(e_precision_empty) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.Le";
  long double val = 15.000009121;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(e_precision_huge) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.15Le";
  long double val = 0.000000000000000123;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(e_precision_huge_negative) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.15Le";
  long double val = -15.35581134;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(e_huge) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%Le";
  long double val = 72537572375.1431341;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(e_flags) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%015E";
  float val = 0;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(e_width) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%15e";
  float val = 0;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(e_many) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "% .0e %.le %Le %e %le %Le";
  float val = 0;
  double val1 = 0;
  long double val2 = 3515315.153151;
  float val3 = 5.5;
  double val4 = 0.094913941;
  long double val5 = 95919539159.53151351131;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(
                s21_sprintf(str1, format, val, val1, val2, val3, val4, val5),
                sprintf(str2, format, val, val1, val2, val3, val4, val5));
}
END_TEST

START_TEST(E_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.17LE";
  long double val = 4134121;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, format, val),
                             sprintf(str2, format, val));
}
END_TEST

START_TEST(all_empty) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, "abc"), sprintf(str2, "abc"));
}
END_TEST

START_TEST(empty_format_and_parameters) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, "abc"), sprintf(str2, "abc"));
}
END_TEST

START_TEST(test_one_char) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, "%c", '\t'),
                             sprintf(str2, "%c", '\t'));
}
END_TEST

START_TEST(test_many_char) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(
                s21_sprintf(str1, "%c%c%c%c%c", '\t', '\n', '0', 'S', 's'),
                sprintf(str2, "%c%c%c%c%c", '\t', '\n', '0', 'S', 's'));
}
END_TEST

START_TEST(test_one_string) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, "%s", "Drop Sega PLS"),
                             sprintf(str2, "%s", "Drop Sega PLS"));
}
END_TEST

START_TEST(test_many_string) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(
                s21_sprintf(str1, "%s%s%s%s%s", "Drop", " ", "Sega", " ",
                            "PLS"),
                sprintf(str2, "%s%s%s%s%s", "Drop", " ", "Sega", " ", "PLS"));
}
END_TEST

START_TEST(test_one_dec) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, "%d", 666),
                             sprintf(str2, "%d", 666));
}
END_TEST

START_TEST(test_many_dec) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, "%d%d%d%d", -999, 0, 666, -100),
                             sprintf(str2, "%d%d%d%d", -999, 0, 666, -100));
}
END_TEST

START_TEST(test_one_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, "%i", -0),
                             sprintf(str2, "%i", -0));
}
END_TEST

START_TEST(test_many_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, "%i%i%i%i", -999, 0, 666, -100),
                             sprintf(str2, "%i%i%i%i", -999, 0, 666, -100));
}
END_TEST

START_TEST(test_one_float) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, "%f", 0.0001),
                             sprintf(str2, "%f", 0.0001));
}
END_TEST

START_TEST(test_many_float) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(
                s21_sprintf(str1, "%f%f%f%f", -999.666, 0.0001, 666.999,
                            -100.001),
                sprintf(str2, "%f%f%f%f", -999.666, 0.0001, 666.999, -100.001));
}
END_TEST

START_TEST(test_one_unsigned_dec) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, "%u", 100),
                             sprintf(str2, "%u", (unsigned)100));
}
END_TEST

START_TEST(test_many_unsigned_dec) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(
                s21_sprintf(str1, "%u%u%u%u", 999, 0, 666, 100),
                sprintf(str2, "%u%u%u%u", (unsigned)999, (unsigned)0,
                        (unsigned)666, (unsigned)100));
}
END_TEST

START_TEST(test_one_char_with_alignment_left) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, "%8c", '\t'),
                             sprintf(str2, "%8c", '\t'));
}
END_TEST

START_TEST(test_one_char_with_alignment_right) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, "%-8c", '\t'),
                             sprintf(str2, "%-8c", '\t'));
}
END_TEST

START_TEST(test_many_char_with_alignment) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(
                s21_sprintf(str1, "%3c%-11c%10c%-2c%c", '\t', '\n', '0', 'S',
                            's'),
                sprintf(str2, "%3c%-11c%10c%-2c%c", '\t', '\n', '0', 'S', 's'));
}
END_TEST

// START HEX TEST
START_TEST(test_one_hex_lower) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++) {
            ck_assert_int_eq(s21_sprintf(str1, "%x", (unsigned)INT32_MIN),
                             sprintf(str2, "%x", (unsigned)INT32_MIN));
            ck_assert_int_eq(s21_sprintf(str1, "%x", 0),
                             sprintf(str2, "%x", 0));
            ck_assert_int_eq(s21_sprintf(str1, "%x", INT32_MAX),
                             sprintf(str2, "%x", INT32_MAX));
          }
}
END_TEST

START_TEST(test_one_hex_upper) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++) {
            ck_assert_int_eq(s21_sprintf(str1, "%X", (unsigned)INT32_MIN),
                             sprintf(str2, "%X", (unsigned)INT32_MIN));
            ck_assert_int_eq(s21_sprintf(str1, "%X", 0),
                             sprintf(str2, "%x", 0));
            ck_assert_int_eq(s21_sprintf(str1, "%X", INT32_MAX),
                             sprintf(str2, "%X", INT32_MAX));
          }
}
END_TEST

START_TEST(test_many_hex_lower) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, "%x%x%x%x%x", 12340987, 135, 0,
                                         -1230, -123213123),
                             sprintf(str2, "%x%x%x%x%x", 12340987, 135, 0,
                                     -1230, -123213123));
}
END_TEST

START_TEST(test_many_hex_upper) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, "%X%X%X%X%X", 12340987, 135, 0,
                                         -1230, -123213123),
                             sprintf(str2, "%X%X%X%X%X", 12340987, 135, 0,
                                     -1230, -123213123));
}
END_TEST
// END HEX TEST

// START HEX WITH ALIGNMENT
START_TEST(test_one_hex_lower_with_alignment_left) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++) {
            ck_assert_int_eq(s21_sprintf(str1, "%-3x", (unsigned)INT32_MIN),
                             sprintf(str2, "%-3x", (unsigned)INT32_MIN));
            ck_assert_int_eq(s21_sprintf(str1, "%-3x", 0),
                             sprintf(str2, "%-3x", 0));
            ck_assert_int_eq(s21_sprintf(str1, "%-3x", INT32_MAX),
                             sprintf(str2, "%-3x", INT32_MAX));
          }
}
END_TEST

START_TEST(test_one_hex_lower_with_alignment_right) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++) {
            ck_assert_int_eq(s21_sprintf(str1, "%13x", (unsigned)INT32_MIN),
                             sprintf(str2, "%13x", (unsigned)INT32_MIN));
            ck_assert_int_eq(s21_sprintf(str1, "%13x", 0),
                             sprintf(str2, "%13x", 0));
            ck_assert_int_eq(s21_sprintf(str1, "%13x", INT32_MAX),
                             sprintf(str2, "%13x", INT32_MAX));
          }
}
END_TEST

START_TEST(test_one_hex_upper_with_alignment_left) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++) {
            ck_assert_int_eq(s21_sprintf(str1, "%-60X", INT32_MIN),
                             sprintf(str2, "%-60X", (unsigned)INT32_MIN));
            ck_assert_int_eq(s21_sprintf(str1, "%-60X", 0),
                             sprintf(str2, "%-60X", 0));
            ck_assert_int_eq(s21_sprintf(str1, "%-60X", INT32_MAX),
                             sprintf(str2, "%-60X", INT32_MAX));
          }
}
END_TEST

START_TEST(test_one_hex_upper_with_alignment_right) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++) {
            ck_assert_int_eq(s21_sprintf(str1, "%7X", (unsigned)INT32_MIN),
                             sprintf(str2, "%7X", (unsigned)INT32_MIN));
            ck_assert_int_eq(s21_sprintf(str1, "%7X", 0),
                             sprintf(str2, "%7X", 0));
            ck_assert_int_eq(s21_sprintf(str1, "%7X", INT32_MAX),
                             sprintf(str2, "%7X", INT32_MAX));
          }
}
END_TEST

START_TEST(test_many_hex_lower_with_alignment) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, "%2x%-7x%9x%11x%0x", 12340987,
                                         100, 0, 1, -666999),
                             sprintf(str2, "%2x%-7x%9x%11x%0x", 12340987, 100,
                                     0, 1, -666999));
}
END_TEST

START_TEST(test_many_hex_upper_with_alignment) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            ck_assert_int_eq(s21_sprintf(str1, "%2X%-7X%9X%11X%0X", 12340987,
                                         100, 0, 1, -666999),
                             sprintf(str2, "%2X%-7X%9X%11X%0X", 12340987, 100,
                                     0, 1, -666999));
}
END_TEST
// END HEX WITH ALIGNMENT

// START HEX TEST WITH #
START_TEST(test_one_hex_with_hashtag) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++) {
            ck_assert_int_eq(s21_sprintf(str1, "%#x", INT32_MIN),
                             sprintf(str2, "%#x", (unsigned)INT32_MIN));
            ck_assert_int_eq(s21_sprintf(str1, "%#x", 0),
                             sprintf(str2, "%#x", 0));
            ck_assert_int_eq(s21_sprintf(str1, "%#x", INT32_MAX),
                             sprintf(str2, "%#x", INT32_MAX));
          }
}
END_TEST

START_TEST(test_one_hex_upper_with_hashtag) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++) {
            ck_assert_int_eq(s21_sprintf(str1, "%#X", INT32_MIN),
                             sprintf(str2, "%#X", (unsigned)INT32_MIN));
            ck_assert_int_eq(s21_sprintf(str1, "%#X", 0),
                             sprintf(str2, "%#X", 0));
            ck_assert_int_eq(s21_sprintf(str1, "%#X", INT32_MAX),
                             sprintf(str2, "%#X", INT32_MAX));
          }
}
END_TEST

START_TEST(test_many_hex_lower_with_hashtag_and_alignm) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++)
              ck_assert_int_eq(s21_sprintf(str1, "%#x%#x%3x%#32x%#-1x", 87,
                                           1222224535, -13, -0, 123213123),
                               sprintf(str2, "%#x%#x%3x%#32x%#-1x", 87,
                                       1222224535, -13, -0, 123213123));
}
END_TEST

START_TEST(test_many_hex_upper_with_hashtag_and_alignm) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++)
              ck_assert_int_eq(s21_sprintf(str1, "%#X%#X%3X%#32X%#-1X", 87,
                                           1222224535, -13, -0, 123213123),
                               sprintf(str2, "%#X%#X%3X%#32X%#-1X", 87,
                                       1222224535, -13, -0, 123213123));
}
END_TEST
// END HEX TEST WITH #

// START HEX TEST with Width *
START_TEST(test_one_hex_lower_with_width_star) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++) {
              ck_assert_int_eq(s21_sprintf(str1, "%*x", 11, INT32_MIN),
                               sprintf(str2, "%*x", 11, (unsigned)INT32_MIN));
              ck_assert_int_eq(s21_sprintf(str1, "%*x", 11, 0),
                               sprintf(str2, "%*x", 11, 0));
              ck_assert_int_eq(s21_sprintf(str1, "%*x", 11, INT32_MAX),
                               sprintf(str2, "%*x", 11, INT32_MAX));
            }
}
END_TEST

START_TEST(test_one_hex_upper_with_width_star) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++) {
              ck_assert_int_eq(s21_sprintf(str1, "%*X", 11, INT32_MIN),
                               sprintf(str2, "%*X", 11, (unsigned)INT32_MIN));
              ck_assert_int_eq(s21_sprintf(str1, "%*X", 11, 0),
                               sprintf(str2, "%*X", 11, 0));
              ck_assert_int_eq(s21_sprintf(str1, "%*X", 11, INT32_MAX),
                               sprintf(str2, "%*X", 11, INT32_MAX));
            }
}
END_TEST

START_TEST(test_many_hex_lower_with_width_star_and_align_and_hashtag) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++)
              ck_assert_int_eq(
                  s21_sprintf(str1, "%#*x%*x%-12x%3x%*x", 9, 127312897, 0, -1,
                              199, -123978, 3, -1251),
                  sprintf(str2, "%#*x%*x%-12x%3x%*x", 9, 127312897, -0, -1, 199,
                          -123978, 3, -1251));
}
END_TEST

START_TEST(test_many_hex_upper_with_width_star) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++)
              ck_assert_int_eq(
                  s21_sprintf(str1, "%#*X%*X%-12X%3X%*X", 9, 127312897, 0, -1,
                              199, -123978, 3, -1251),
                  sprintf(str2, "%#*X%*X%-12X%3X%*X", 9, 127312897, 0, -1, 199,
                          -123978, 3, -1251));
}
END_TEST
// END HEX TEST WITH Width *

// START HEX TEST WITH precision
START_TEST(test_one_hex_lower_with_precision) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  int a = s21_sprintf(str1, "%*.6x", 11, 0);
  int b = sprintf(str2, "%*.6x", 11, 0);
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++) ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_one_hex_upper_with_precision) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  int a = s21_sprintf(str1, "%*.6X", 11, INT32_MIN);
  int b = sprintf(str2, "%*.6X", 11, (unsigned)INT32_MIN);
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++) ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_many_hex_lower_with_precision_and_other) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  int a = s21_sprintf(
      str1, "%#3.*x%#3x%-7.*x%#-1.8x%4.3x%#2.15x%*.*x%*.1x%3x%-1x", 3, 126714,
      4444444, 0, 6423235, 0, 666, 999, 13, 5, 419, 9, 41, -41, 33);
  int b = sprintf(str2, "%#3.*x%#3x%-7.*x%#-1.8x%4.3x%#2.15x%*.*x%*.1x%3x%-1x",
                  3, 126714, 4444444, 0, 6423235, 0, 666, 999, 13, 5, 419, 9,
                  41, -41, 33);
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++) ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_many_hex_upper_with_precision_and_other) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++)
              ck_assert_int_eq(
                  s21_sprintf(
                      str1,
                      "%#3.*X%#3x%-7.*X%#-1.8X%4.3X%#2.15x%*.*X%*.1X%3X%-1X", 3,
                      -126714, 4444444, 0, 6423235, 0, 666, 999, 13, 5, -419, 9,
                      41, -41, 33),
                  sprintf(
                      str2,
                      "%#3.*X%#3x%-7.*X%#-1.8X%4.3X%#2.15x%*.*X%*.1X%3X%-1X", 3,
                      -126714, 4444444, 0, 6423235, 0, 666, 999, 13, 5, -419, 9,
                      41, -41, 33));
}
END_TEST
// END HEX TEST WITH precision

// START HEX TEST WITH Length
START_TEST(test_one_hex_lower_with_length) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++) {
              ck_assert_int_eq(s21_sprintf(str1, "%hx", -11),
                               sprintf(str2, "%hx", (unsigned short)-11));
              ck_assert_int_eq(s21_sprintf(str1, "%hx", 0),
                               sprintf(str2, "%hx", (unsigned short)0));
              ck_assert_int_eq(s21_sprintf(str1, "%hx", 11),
                               sprintf(str2, "%hx", (unsigned short)11));
              long unsigned int val = INT32_MAX;
              ck_assert_int_eq(s21_sprintf(str1, "%lx", val),
                               sprintf(str2, "%lx", val));
              long unsigned int v = 0;
              ck_assert_int_eq(s21_sprintf(str1, "%lx", v),
                               sprintf(str2, "%lx", v));
            }
}
END_TEST

START_TEST(test_one_hex_upper_with_length) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++) {
              ck_assert_int_eq(s21_sprintf(str1, "%hx", -11),
                               sprintf(str2, "%hx", (unsigned short)-11));
              ck_assert_int_eq(s21_sprintf(str1, "%hx", 0),
                               sprintf(str2, "%hx", (unsigned short)0));
              ck_assert_int_eq(s21_sprintf(str1, "%hx", 11),
                               sprintf(str2, "%hx", (unsigned short)11));
              long unsigned int val = INT32_MAX;
              ck_assert_int_eq(s21_sprintf(str1, "%lx", val),
                               sprintf(str2, "%lx", val));
              long unsigned int v = 0;
              ck_assert_int_eq(s21_sprintf(str1, "%lx", v),
                               sprintf(str2, "%lx", v));
            }
}
END_TEST

START_TEST(test_sprintf_1) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%10ld";
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++)
              ck_assert_int_eq(s21_sprintf(str1, format, 1),
                               sprintf(str2, format, 1));
}
END_TEST

START_TEST(test_sprintf_2) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%1.1f";
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++)
              ck_assert_int_eq(s21_sprintf(str1, format, 1.1),
                               sprintf(str2, format, 1.1));
}
END_TEST

START_TEST(test_sprintf_3) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%8.3c";
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++)
              ck_assert_int_eq(s21_sprintf(str1, format, 'a'),
                               sprintf(str2, format, 'a'));
}
END_TEST

START_TEST(test_sprintf_4) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%+5.5d aboba";
  int val = 10000;
  int a = s21_sprintf(str1, format, val);
  int b = sprintf(str2, format, val);
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++) ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_sprintf_5) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%7.7f";
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++)
              ck_assert_int_eq(s21_sprintf(str1, format, 11.123456),
                               sprintf(str2, format, 11.123456));
}
END_TEST

START_TEST(test_sprintf_6) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%7.4s";
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++)
              ck_assert_int_eq(s21_sprintf(str1, format, "aboba floppa"),
                               sprintf(str2, format, "aboba floppa"));
}
END_TEST

START_TEST(test_sprintf_7) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%6.6u";
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++)
              ck_assert_int_eq(s21_sprintf(str1, format, 12341151),
                               sprintf(str2, format, 12341151));
}
END_TEST

START_TEST(test_sprintf_8) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%li%ld%lu";
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++)
              ck_assert_int_eq(
                  s21_sprintf(str1, format, 666666666666, 777, 111),
                  sprintf(str2, format, 666666666666, 777, 111));
}
END_TEST

START_TEST(test_sprintf_9) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%hi%hd%hu";
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++)
              ck_assert_int_eq(s21_sprintf(str1, format, 666, -777, 111),
                               sprintf(str2, format, 666, -777, 111));
}
END_TEST

START_TEST(g_large) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%g";
  double hex = 5131.43141;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++)
              ck_assert_int_eq(s21_sprintf(str1, format, hex),
                               sprintf(str2, format, hex));
}
END_TEST

START_TEST(g_small) {
  char str1[100];
  char str2[100];
  char format[] = "%g";
  double hex = 5.00123;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++)
              ck_assert_int_eq(s21_sprintf(str1, format, hex),
                               sprintf(str2, format, hex));
}
END_TEST

START_TEST(g_precision) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%.2g";
  double hex = 51.43141;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++)
              ck_assert_int_eq(s21_sprintf(str1, format, hex),
                               sprintf(str2, format, hex));
}
END_TEST

START_TEST(g_precision_zero) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%.0g";
  double hex = 0.123000;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++)
              ck_assert_int_eq(s21_sprintf(str1, format, hex),
                               sprintf(str2, format, hex));
}
END_TEST

START_TEST(g_precision_missing) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%.g";
  double hex = 0.123000;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++)
              ck_assert_int_eq(s21_sprintf(str1, format, hex),
                               sprintf(str2, format, hex));
}
END_TEST

START_TEST(g_many_zeroes_in_front) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%.g";
  double hex = 0.4;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++)
              ck_assert_int_eq(s21_sprintf(str1, format, hex),
                               sprintf(str2, format, hex));
}
END_TEST

START_TEST(g_one_zero) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%g";
  double hex = 1.00001;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++)
              ck_assert_int_eq(s21_sprintf(str1, format, hex),
                               sprintf(str2, format, hex));
}
END_TEST

START_TEST(g_zero) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%.5g";
  double hex = 41.001341;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++)
              ck_assert_int_eq(s21_sprintf(str1, format, hex),
                               sprintf(str2, format, hex));
}
END_TEST

START_TEST(g_mantiss) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%g";
  double hex = 1.000006;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++)
              ck_assert_int_eq(s21_sprintf(str1, format, hex),
                               sprintf(str2, format, hex));
}
END_TEST

START_TEST(g_mantiss_flags) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%5.8g";
  double hex = 1.0000005;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++)
              ck_assert_int_eq(s21_sprintf(str1, format, hex),
                               sprintf(str2, format, hex));
}
END_TEST

START_TEST(g_short_no_mantiss) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%g";
  double hex = 1.00005;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++)
              ck_assert_int_eq(s21_sprintf(str1, format, hex),
                               sprintf(str2, format, hex));
}
END_TEST

START_TEST(LG) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%LG";
  long double hex = 1.000006;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++)
              ck_assert_int_eq(s21_sprintf(str1, format, hex),
                               sprintf(str2, format, hex));
}
END_TEST

START_TEST(g_many) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%LG";
  char format2[] = "%g %G";
  char format3[] = "%.5g";
  long double hex = 1111.111;
  double hex1 = 41.001341;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++) {
              ck_assert_int_eq(s21_sprintf(str1, format, hex),
                               sprintf(str2, format, hex));
              ck_assert_int_eq(s21_sprintf(str1, format2, hex1, hex1),
                               sprintf(str2, format2, hex1, hex1));
              ck_assert_int_eq(s21_sprintf(str1, format3, hex1),
                               sprintf(str2, format3, hex1));
            }
}
END_TEST

START_TEST(wide_char) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "This is a simple wide char %lc";
  unsigned long w = L'Ф';
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++) {
              s21_sprintf(str1, format, w);
              sprintf(str2, format, w);
              ck_assert_str_eq(str1, str2);
            }
}
END_TEST

START_TEST(width_char) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "This is a simple wide char %5c";
  char w = 'c';
  int a = s21_sprintf(str1, format, w);
  int b = sprintf(str2, format, w);
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++) ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(minus_wide_char) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "This is a simple wide char %-lc";
  unsigned long w = L'Й';
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++) {
              s21_sprintf(str1, format, w);
              sprintf(str2, format, w);
              ck_assert_str_eq(str1, str2);
            }
}
END_TEST

START_TEST(wide_string) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "This is a simple wide char %ls";
  wchar_t w[] = L"ФФФФФФФ";
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++) {
              s21_sprintf(str1, format, w);
              sprintf(str2, format, w);
              ck_assert_str_eq(str1, str2);
            }
}
END_TEST

START_TEST(wide_string1) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "This is a simple wide char %.12ls";
  wchar_t w[] = L"ФФФФФФФ";
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++) {
              s21_sprintf(str1, format, w);
              sprintf(str2, format, w);
              ck_assert_str_eq(str1, str2);
            }
}
END_TEST

START_TEST(wide_string2) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "This is a simple wide char %.120ls ABOBA";
  wchar_t w[] = L"A";
  int a = s21_sprintf(str1, format, w);
  int b = sprintf(str2, format, w);
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++) ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(wide_string3) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "This is a simple wide char %-43ls";
  wchar_t w[] = L"Q";
  int a = s21_sprintf(str1, format, w);
  int b = sprintf(str2, format, w);
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++) ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(wide_string4) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "This is a simple wide char %43ls";
  wchar_t w[] = L"E";
  int a = s21_sprintf(str1, format, w);
  int b = sprintf(str2, format, w);
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++) ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(wide_char2) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  wchar_t w = L'Ф';
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 3; l++)
          for (int m = 0; m < 3; m++)
            for (int n = 0; n < 3; n++) {
              s21_sprintf(str1, "%C", w);
              sprintf(str2, "%C", w);
              ck_assert_str_eq(str1, str2);
            }
}
END_TEST

Suite *s21_sprintf_suite() {
  Suite *s2 = suite_create("suite_sprintf");
  TCase *tc = tcase_create("sprintf_tc");

  tcase_add_test(tc, simple_int);
  tcase_add_test(tc, precise_int);
  tcase_add_test(tc, width_int);
  tcase_add_test(tc, minus_width_int);
  tcase_add_test(tc, plus_width_int);
  tcase_add_test(tc, padding_int);
  tcase_add_test(tc, star_width_int);
  tcase_add_test(tc, star_precision_int);
  tcase_add_test(tc, many_flags_many_ints);
  tcase_add_test(tc, flags_long_int);
  tcase_add_test(tc, flags_short_int);
  tcase_add_test(tc, flags_another_long_int);
  tcase_add_test(tc, zero_precision_zero_int);
  tcase_add_test(tc, space_flag_int);
  tcase_add_test(tc, unsigned_val);
  tcase_add_test(tc, unsigned_val_width);
  tcase_add_test(tc, unsigned_val_flags);
  tcase_add_test(tc, unsigned_val_precision);
  tcase_add_test(tc, unsigned_val_many_flags);
  tcase_add_test(tc, unsigned_val_short);
  tcase_add_test(tc, unsigned_val_long);
  tcase_add_test(tc, unsigned_val_many);
  tcase_add_test(tc, octal);
  tcase_add_test(tc, octal_width);
  tcase_add_test(tc, octal_flags);
  tcase_add_test(tc, octal_precision);
  tcase_add_test(tc, octal_many_flags);
  tcase_add_test(tc, octal_short);
  tcase_add_test(tc, octal_long);
  tcase_add_test(tc, octal_many);
  tcase_add_test(tc, octal_zero);
  tcase_add_test(tc, octal_hash);
  tcase_add_test(tc, unsigned_zero);
  tcase_add_test(tc, hex_width);
  tcase_add_test(tc, hex_flags);
  tcase_add_test(tc, hex_precision);
  tcase_add_test(tc, hex_many);
  tcase_add_test(tc, hex_many_flags);
  tcase_add_test(tc, hex_zero);
  tcase_add_test(tc, hex_huge);
  tcase_add_test(tc, hex_short);
  tcase_add_test(tc, hex_long);
  tcase_add_test(tc, hex_one_longer_width);
  tcase_add_test(tc, hex_two_longer_width);
  tcase_add_test(tc, one_char);
  tcase_add_test(tc, one_precision);
  tcase_add_test(tc, one_flags);
  tcase_add_test(tc, one_width);
  tcase_add_test(tc, one_many);
  tcase_add_test(tc, one_many_flags);
  tcase_add_test(tc, string);
  tcase_add_test(tc, string_precision);
  tcase_add_test(tc, string_width);
  tcase_add_test(tc, string_flags);
  tcase_add_test(tc, string_long);
  tcase_add_test(tc, string_many);
  tcase_add_test(tc, ptr);
  tcase_add_test(tc, ptr_width);
  tcase_add_test(tc, ptr_precision);
  tcase_add_test(tc, null_ptr);
  tcase_add_test(tc, n_specifier);
  tcase_add_test(tc, string_width_huge);
  tcase_add_test(tc, float_precision);
  tcase_add_test(tc, float_width);
  tcase_add_test(tc, float_precision_zero);
  tcase_add_test(tc, float_precision_empty);
  tcase_add_test(tc, float_precision_huge);
  tcase_add_test(tc, float_precision_huge_negative);
  tcase_add_test(tc, float_huge);
  tcase_add_test(tc, float_flags);
  tcase_add_test(tc, float_many);
  tcase_add_test(tc, e_precision);
  tcase_add_test(tc, e_precision_zero);
  tcase_add_test(tc, e_precision_empty);
  tcase_add_test(tc, e_precision_huge);
  tcase_add_test(tc, e_precision_huge_negative);
  tcase_add_test(tc, e_huge);
  tcase_add_test(tc, e_many);
  tcase_add_test(tc, e_width);
  tcase_add_test(tc, e_flags);
  tcase_add_test(tc, E_int);
  tcase_add_test(tc, all_empty);
  tcase_add_test(tc, empty_format_and_parameters);
  tcase_add_test(tc, test_one_char);
  tcase_add_test(tc, test_many_char);
  tcase_add_test(tc, test_one_string);
  tcase_add_test(tc, test_many_string);
  tcase_add_test(tc, test_one_dec);
  tcase_add_test(tc, test_many_dec);
  tcase_add_test(tc, test_one_int);
  tcase_add_test(tc, test_many_int);
  tcase_add_test(tc, test_one_float);
  tcase_add_test(tc, test_many_float);
  tcase_add_test(tc, test_one_unsigned_dec);
  tcase_add_test(tc, test_many_unsigned_dec);
  tcase_add_test(tc, test_one_char_with_alignment_left);
  tcase_add_test(tc, test_one_char_with_alignment_right);
  tcase_add_test(tc, test_many_char_with_alignment);
  tcase_add_test(tc, test_one_hex_lower);
  tcase_add_test(tc, test_one_hex_upper);
  tcase_add_test(tc, test_many_hex_lower);
  tcase_add_test(tc, test_many_hex_upper);
  tcase_add_test(tc, test_one_hex_lower_with_alignment_left);
  tcase_add_test(tc, test_one_hex_lower_with_alignment_right);
  tcase_add_test(tc, test_one_hex_upper_with_alignment_left);
  tcase_add_test(tc, test_one_hex_upper_with_alignment_right);
  tcase_add_test(tc, test_many_hex_lower_with_alignment);
  tcase_add_test(tc, test_many_hex_upper_with_alignment);
  tcase_add_test(tc, test_one_hex_with_hashtag);
  tcase_add_test(tc, test_one_hex_upper_with_hashtag);
  tcase_add_test(tc, test_many_hex_lower_with_hashtag_and_alignm);
  tcase_add_test(tc, test_many_hex_upper_with_hashtag_and_alignm);
  tcase_add_test(tc, test_one_hex_lower_with_width_star);
  tcase_add_test(tc, test_one_hex_upper_with_width_star);
  tcase_add_test(tc, test_many_hex_lower_with_width_star_and_align_and_hashtag);
  tcase_add_test(tc, test_many_hex_upper_with_width_star);
  tcase_add_test(tc, test_one_hex_lower_with_precision);
  tcase_add_test(tc, test_one_hex_upper_with_precision);
  tcase_add_test(tc, test_many_hex_lower_with_precision_and_other);
  tcase_add_test(tc, test_many_hex_upper_with_precision_and_other);
  tcase_add_test(tc, test_one_hex_lower_with_length);
  tcase_add_test(tc, test_one_hex_upper_with_length);
  tcase_add_test(tc, test_sprintf_1);
  tcase_add_test(tc, test_sprintf_2);
  tcase_add_test(tc, test_sprintf_3);
  tcase_add_test(tc, test_sprintf_4);
  tcase_add_test(tc, test_sprintf_5);
  tcase_add_test(tc, test_sprintf_6);
  tcase_add_test(tc, test_sprintf_7);
  tcase_add_test(tc, test_sprintf_8);
  tcase_add_test(tc, test_sprintf_9);
  tcase_add_test(tc, g_large);
  tcase_add_test(tc, g_small);
  tcase_add_test(tc, g_precision);
  tcase_add_test(tc, g_precision_zero);
  tcase_add_test(tc, g_precision_missing);
  tcase_add_test(tc, g_many_zeroes_in_front);
  tcase_add_test(tc, g_one_zero);
  tcase_add_test(tc, g_mantiss);
  tcase_add_test(tc, g_mantiss_flags);
  tcase_add_test(tc, g_short_no_mantiss);
  tcase_add_test(tc, LG);
  tcase_add_test(tc, g_many);
  tcase_add_test(tc, g_zero);
  tcase_add_test(tc, wide_char);
  tcase_add_test(tc, width_char);
  tcase_add_test(tc, minus_wide_char);
  tcase_add_test(tc, wide_string);
  tcase_add_test(tc, wide_string1);
  tcase_add_test(tc, wide_string2);
  tcase_add_test(tc, wide_string3);
  tcase_add_test(tc, wide_string4);
  tcase_add_test(tc, wide_char2);
  suite_add_tcase(s2, tc);
  return s2;
}