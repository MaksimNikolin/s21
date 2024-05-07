#ifndef SRC_S21_SPRINTF_H_
#define SRC_S21_SPRINTF_H_

#include <locale.h>
#include <math.h>
#include <stdarg.h>
#include <stdint.h>

#include "s21_string.h"

#define BUFF_SIZE 1024

#define bool int
#define true 1
#define false 0

typedef struct {
  bool minus;
  bool plus;
  bool space;
  bool zero;
  bool hash;
  int precision;
  int is_precision_set;
  int width;
  char length;
  char specifier;
} flags;

int s21_sprintf(char *str, const char *format, ...);

void integer_to_string(int64_t val, char *ret, int base);
void unsigned_num_to_string(uint64_t val, char *ret, int base);
bool is_integer_specifier(char c);
bool is_all_zeroes(char *buff);
void to_upper(char *str);
void prepend_ox(char *buff, flags f);
void double_to_string(long double val, char *ret, flags f);
void prepend_mantiss(char *str, int pow, char sign);

const char *parse_flags(const char *format, flags *f);
const char *parse_width(const char *format, flags *f, va_list va);
const char *parse_precision(const char *format, flags *f, va_list va);
const char *parse_length(const char *format, flags *f);

void format_argument(flags f, char *buff, va_list va);
void parse_integer(flags, char *buff, va_list va);
void parse_unsigned_with_flags(flags f, char *buff, va_list va);
void parse_octal_with_flags(flags f, char *buff, va_list va);
void parse_hex_with_flags(flags f, char *buff, va_list va);
void parse_char_with_flags(flags f, char *buff, va_list va);
void parse_string_to_buffer(flags f, char *buff, va_list va);
void parse_pointer_to_buffer(flags f, char *buff, va_list va);
void parse_float_to_buffer(flags f, char *buff, va_list va);
void parse_mantiss_to_buffer(flags f, char *buff, va_list va);
void parse_float_g_G_to_buffer(flags f, char *buff, va_list va);

void apply_precision_format(char *buff, flags f);
void format_flags(char *buff, flags f);
void format_gG_precision(char *buff, int precision);
void format_wide_char(char *buff, wchar_t w_c);
void format_char_to_buffer(flags f, char *buff, char c);
void format_string_to_buffer(flags f, char *buff, char *str);
void format_wide_string_to_buffer(flags f, char *buff, wchar_t *wstr);

/////////////////////////////

int s21_isdigit(char c);
int s21_atoi(const char *str);
char *s21_strcpy(char *destptr, const char *srcptr);
char *s21_strcat(char *dest, const char *src);
void *s21_memmove(void *dest, const void *src, s21_size_t n);

#endif  //  SRC_S21_SPRINTF_H_