#include "s21_sprintf.h"

int s21_sprintf(char *str, const char *format, ...) {
  flags f = {0};
  va_list va;
  va_start(va, format);
  char *str_beginning = str;
  while (*format) {
    if (*format != '%') {
      *str++ = *format++;
      continue;
    } else {
      format++;
      s21_memset(&f, 0, sizeof(flags));
    }
    format = parse_flags(format, &f);
    format = parse_width(format, &f, va);
    format = parse_precision(format, &f, va);
    format = parse_length(format, &f);
    f.specifier = *format;
    format++;
    char buff[BUFF_SIZE] = {'\0'};
    format_argument(f, buff, va);
    for (int i = 0; buff[i]; i++, str++) *str = buff[i];
    if (f.specifier == 'n') {
      int *ret = va_arg(va, int *);
      if (ret) *ret = str - str_beginning;
    }
  }
  *str = '\0';
  va_end(va);
  return str - str_beginning;
}

const char *parse_flags(const char *format, flags *f) {
  while (*format == '-' || *format == '+' || *format == ' ' || *format == '0' ||
         *format == '#') {
    f->zero = (*format == '0') ? true : f->zero;
    f->minus = (*format == '-') ? true : f->minus;
    f->plus = (*format == '+') ? true : f->plus;
    f->space = (*format == ' ') ? true : f->space;
    f->hash = (*format == '#') ? true : f->hash;
    format++;
  }
  return format;
}

const char *parse_width(const char *format, flags *f, va_list va) {
  if (*format == '*')
    format++, f->width = va_arg(va, int);
  else if (s21_isdigit(*format)) {
    char tmp[BUFF_SIZE] = {'\0'};
    for (int i = 0; s21_isdigit(*format); i++, format++) tmp[i] = *format;
    f->width = s21_atoi(tmp);
  }
  return format;
}

const char *parse_precision(const char *format, flags *f, va_list va) {
  if (*format == '.') f->is_precision_set = true, format++;
  if (*format == '*')
    format++, f->precision = va_arg(va, int);
  else if (s21_isdigit(*format)) {
    char tmp[BUFF_SIZE] = {'\0'};
    for (int i = 0; s21_isdigit(*format); i++, format++) tmp[i] = *format;
    f->precision = s21_atoi(tmp);
  }
  return format;
}

const char *parse_length(const char *format, flags *f) {
  f->length = (*format == 'h' || *format == 'l' || *format == 'L') ? *format
                                                                   : f->length;
  format += (f->length != '\0') ? 1 : 0;
  return format;
}

void format_argument(flags f, char *buff, va_list va) {
  (f.specifier == 'd' || f.specifier == 'i') ? parse_integer(f, buff, va)
  : (f.specifier == 'u') ? parse_unsigned_with_flags(f, buff, va)
  : (f.specifier == 'o') ? parse_octal_with_flags(f, buff, va)
  : (f.specifier == 'x' || f.specifier == 'X')
      ? parse_hex_with_flags(f, buff, va)
  : (f.specifier == '%') ? (buff[0] = '%')
  : (f.specifier == 'c') ? parse_char_with_flags(f, buff, va)
  : (f.specifier == 's') ? parse_string_to_buffer(f, buff, va)
  : (f.specifier == 'p') ? parse_pointer_to_buffer(f, buff, va)
  : (f.specifier == 'f') ? parse_float_to_buffer(f, buff, va)
  : (f.specifier == 'e' || f.specifier == 'E')
      ? parse_mantiss_to_buffer(f, buff, va)
  : (f.specifier == 'g' || f.specifier == 'G')
      ? parse_float_g_G_to_buffer(f, buff, va)
      : 0;

  if (f.specifier == 'G' || f.specifier == 'E' || f.specifier == 'X')
    to_upper(buff);
}

void parse_integer(flags f, char *buff, va_list va) {
  int64_t val = va_arg(va, int64_t);
  val = (f.length == 0) ? (int32_t)val : (f.length == 'h') ? (int16_t)val : val;
  integer_to_string(val, buff, 10);
  apply_precision_format(buff, f);
  format_flags(buff, f);
}

void integer_to_string(int64_t val, char *ret, int base) {
  char tmp[BUFF_SIZE] = {'\0'};
  int idx = BUFF_SIZE - 2;
  bool neg = val < 0 ? 1 : 0;
  val = neg ? -val : val;
  if (val == 0) tmp[idx] = '0';
  while (val > 0) {
    idx--;
    tmp[idx] = "0123456789abcdef"[val % base];
    val /= base;
  }
  for (int j = 0; tmp[idx]; idx++, j++) {
    if (neg && j == 0) ret[j++] = '-';
    ret[j] = tmp[idx];
  }
}

void apply_precision_format(char *buff, flags f) {
  char tmp[BUFF_SIZE] = {'\0'};
  int sign = 0, len = s21_strlen(buff);
  if (buff[0] == '-') tmp[0] = '-', len--, sign = 1;
  if (f.precision > len) {
    int index;
    for (index = sign; index < f.precision - len + sign; index++)
      tmp[index] = '0';
    for (int i = sign; buff[i]; i++, index++) tmp[index] = buff[i];
    s21_strcpy(buff, tmp);
  }
  if (f.is_precision_set && f.precision == 0 &&
      is_integer_specifier(f.specifier) && buff[0] == '0')
    buff[0] = '\0';
}

bool is_integer_specifier(char c) {
  char specs[] = {'d', 'i', 'o', 'u', 'x', 'X'};
  bool res = false;
  for (s21_size_t i = 0; i < sizeof(specs); i++) {
    if (specs[i] == c) {
      res = true;
      break;
    }
  }
  return res;
}

void format_flags(char *buff, flags f) {
  char tmp[BUFF_SIZE + 1] = {'\0'};
  if (f.plus && f.specifier != 'u') {
    tmp[0] = buff[0] == '-' ? buff[0] : '+';
    s21_strcpy(tmp + 1, buff[0] == '-' ? buff + 1 : buff);
    s21_strcpy(buff, tmp);
  } else if (f.space && buff[0] != '-' && f.specifier != 'u') {
    tmp[0] = ' ';
    s21_strcpy(tmp + 1, buff);
    s21_strcpy(buff, tmp);
  }
  if (f.width > (int)s21_strlen(buff)) {
    int idx = f.width - s21_strlen(buff);
    if (!f.minus) {
      s21_memset(tmp, f.zero ? '0' : ' ', idx);
      s21_strcpy(tmp + idx, buff);
    } else {
      s21_strcpy(tmp, buff);
      s21_memset(tmp + s21_strlen(tmp), ' ', idx);
    }
    s21_strcpy(buff, tmp);
  }
  if (!s21_strchr(buff, '.') && f.specifier == 'f') {
    s21_strcat(buff, ".");
  }
}

void unsigned_num_to_string(uint64_t val, char *ret, int base) {
  char buf[BUFF_SIZE + 1] = {'\0'};
  int idx = BUFF_SIZE - 1;
  if (val == 0) buf[idx] = '0', idx--;
  for (; val && idx; --idx, val /= base)
    buf[idx] = "0123456789abcdef"[val % base];
  for (int j = 0; buf[idx + 1]; idx++, j++) ret[j] = buf[idx + 1];
}

void parse_unsigned_with_flags(flags f, char *buff, va_list va) {
  uint64_t val = va_arg(va, uint64_t);
  val = (f.length == 'h')   ? (uint16_t)val
        : (f.length == 'l') ? (uint64_t)val
        : (f.length == 0)   ? (uint32_t)val
                            : val;
  unsigned_num_to_string(val, buff, 10);
  apply_precision_format(buff, f);
  format_flags(buff, f);
}

void parse_octal_with_flags(flags f, char *buff, va_list va) {
  buff[0] = '0';
  integer_to_string(va_arg(va, int64_t), buff + f.hash, 8);
  apply_precision_format(buff, f);
  format_flags(buff, f);
}

void to_upper(char *str) {
  while (*str) {
    if (*str >= 'a' && *str <= 'z') *str = *str - 'a' + 'A';
    str++;
  }
}

bool is_all_zeroes(char *buff) {
  for (int i = 0; buff[i]; i++)
    if (buff[i] != '0') return false;
  return true;
}

void parse_hex_with_flags(flags f, char *buff, va_list va) {
  uint64_t val = va_arg(va, uint64_t);
  val = (f.length == 0)     ? (uint32_t)val
        : (f.length == 'h') ? (uint16_t)val
        : (f.length == 'l') ? (uint64_t)val
                            : val;
  unsigned_num_to_string(val, buff, 16);
  apply_precision_format(buff, f);
  if (f.hash) prepend_ox(buff, f);
  format_flags(buff, f);
}

void prepend_ox(char *buff, flags f) {
  if (!is_all_zeroes(buff) || f.specifier == 'p') {
    s21_memmove(buff + 2, buff, s21_strlen(buff));
    buff[0] = '0', buff[1] = 'x';
  }
}

void parse_char_with_flags(flags f, char *buff, va_list va) {
  if (f.length == 'l') {
    wchar_t w_c = va_arg(va, wchar_t);
    format_wide_char(buff, w_c);
  } else {
    char c = va_arg(va, int);
    format_char_to_buffer(f, buff, c);
  }
}

void format_wide_char(char *buff, wchar_t w_c) {
  s21_memset(buff, '\0', BUFF_SIZE);
  if (buff[0] != 0) wcstombs(buff, &w_c, BUFF_SIZE);
}

void format_char_to_buffer(flags f, char *buff, char c) {
  if (!f.minus && f.width) {
    for (int i = 0; i < f.width; i++) {
      buff[i] = ' ';
      if (i == f.width - 1) buff[i] = c;
    }
  } else if (f.width) {
    buff[0] = c;
    for (int i = 1; i < f.width; i++) buff[i] = ' ';
  } else
    buff[0] = c;
}

void parse_string_to_buffer(flags f, char *buff, va_list va) {
  if (f.length == 'l') {
    wchar_t *wstr = va_arg(va, wchar_t *);
    format_wide_string_to_buffer(f, buff, wstr);
  } else {
    char *str = va_arg(va, char *);
    format_string_to_buffer(f, buff, str);
  }
}

void format_string_to_buffer(flags f, char *buff, char *str) {
  char tmp[BUFF_SIZE] = {'\0'};
  s21_strcpy(tmp, str);
  if (f.is_precision_set && (s21_size_t)f.precision < s21_strlen(tmp))
    tmp[f.precision] = '\0';
  int shift = f.width - s21_strlen(tmp), len = s21_strlen(tmp);
  if (f.minus && shift > 0) {
    s21_strcpy(buff, tmp);
    s21_memset(buff + len, ' ', shift);
  } else if (shift > 0) {
    s21_memset(buff, ' ', shift);
    s21_strcpy(buff + shift, tmp);
  } else
    s21_strcpy(buff, tmp);
}

void format_wide_string_to_buffer(flags f, char *buff, wchar_t *wstr) {
  char tmp[BUFF_SIZE] = {'\0'};
  char str[BUFF_SIZE] = {'\0'};
  wcstombs(str, wstr, BUFF_SIZE);
  s21_strcpy(tmp, str);
  if (f.is_precision_set && (s21_size_t)f.precision < s21_strlen(tmp))
    tmp[f.precision] = '\0';
  int shift = f.width - s21_strlen(tmp);
  int len = s21_strlen(tmp);
  if (f.minus && shift > 0) {
    s21_strcpy(buff, tmp);
    s21_memset(buff + len, ' ', shift);
  } else if (shift > 0) {
    s21_memset(buff, ' ', shift);
    s21_strcpy(buff + shift, tmp);
  } else {
    s21_strcpy(buff, tmp);
  }
}

void parse_pointer_to_buffer(flags f, char *buff, va_list va) {
  unsigned_num_to_string(va_arg(va, uint64_t), buff, 16);
  apply_precision_format(buff, f);
  prepend_ox(buff, f);
  format_flags(buff, f);
}

void parse_float_to_buffer(flags f, char *buff, va_list va) {
  long double val = 0;
  if (f.length == 'L')
    val = va_arg(va, long double);
  else
    val = va_arg(va, double);
  if (!f.is_precision_set) f.precision = 6;
  double_to_string(val, buff, f);
  format_flags(buff, f);
}

void double_to_string(long double val, char *ret, flags f) {
  char buff[BUFF_SIZE] = {'\0'};
  int idx = BUFF_SIZE - 2;
  bool neg = val < 0 ? 1 : 0;
  val = neg ? val * -1 : val;
  long double l = 0, r = modfl(val, &l);
  if (f.precision == 0) l = roundl(val), r = 0;
  char fractions[BUFF_SIZE] = {'\0'};
  for (int i = 0; i < f.precision; i++) {
    r = r * 10;
    fractions[i] = (int)r + '0';
  }
  long long right = roundl(r), left = l;
  if (!right) {
    for (int i = 0; i < f.precision; idx--, i++) buff[idx] = '0';
  } else {
    for (int i = s21_strlen(fractions); right || i > 0; right /= 10, idx--, i--)
      buff[idx] = (int)(right % 10 + 0.05) + '0';
  }
  if ((f.is_precision_set && f.precision != 0) || (int)r ||
      (!f.is_precision_set && val == 0) || s21_strlen(fractions))
    buff[idx--] = '.';
  if (!left)
    buff[idx] = '0', idx--;
  else {
    for (; left; left /= 10, idx--) buff[idx] = (int)(left % 10) + '0';
  }
  for (int i = 0; buff[idx + 1]; idx++, i++) {
    if (neg && i == 0) ret[i] = '-', i++;
    ret[i] = buff[idx + 1];
  }
}

void parse_mantiss_to_buffer(flags f, char *buff, va_list va) {
  long double val = 0;
  if (f.length == 'L')
    val = va_arg(va, long double);
  else
    val = va_arg(va, double);
  int pow = 0;
  char sign = (int)val == 0 ? '-' : '+';
  if ((int)val - val) {
    while ((int)val == 0) pow++, val *= 10;
  } else
    sign = '+';
  while ((int)val / 10 != 0) pow++, val /= 10;
  if (!f.is_precision_set) f.precision = 6;
  double_to_string(val, buff, f);
  prepend_mantiss(buff, pow, sign);
  format_flags(buff, f);
}

void prepend_mantiss(char *str, int pow, char sign) {
  int len = s21_strlen(str);
  str[len] = 'e', str[len + 1] = sign, str[len + 3] = pow % 10 + '0';
  pow /= 10;
  str[len + 2] = pow % 10 + '0', str[len + 4] = '\0';
}

void parse_float_g_G_to_buffer(flags f, char *buff, va_list va) {
  long double val = 0;
  if (f.length == 'L')
    val = va_arg(va, long double);
  else
    val = va_arg(va, double);
  if (val == 0) {
    s21_strcpy(buff, "0.0");
    return;
  }
  if (!f.is_precision_set) f.precision = 6;
  if (f.precision == 0) f.precision = 1;
  int precision = f.precision;
  double_to_string(val, buff, f);
  format_gG_precision(buff, precision);
  format_flags(buff, f);
}

void format_gG_precision(char *buff, int precision) {
  int sig_digs = 0, not_zero_found = 0;
  s21_size_t len = s21_strlen(buff);
  for (s21_size_t i = 0; i < s21_strlen(buff); i++) {
    if ((buff[i] == '0' && !not_zero_found) || buff[i] == '.')
      continue;
    else
      not_zero_found = 1;
    if (s21_isdigit(buff[i]) && not_zero_found) sig_digs++;
    if (sig_digs == precision && i + 1 < len) {
      int next = buff[i + 1] == '.' ? 2 : 1;
      buff[i] = buff[i + next] - '0' > 5 ? (char)(buff[i] + 1) : buff[i];
      buff[i + 1] = '\0';
      break;
    }
  }
}

////////////   Additional functions   ////////////

int s21_isdigit(char c) { return (c >= '0' && c <= '9'); }

int s21_atoi(const char *str) {
  int res = 0, sign = 1, overflow = 0;
  while (*str == ' ') str++;
  if (*str == '-') str++, sign = -1;
  if (*str == '+') str++;
  while (*str && *str >= '0' && *str <= '9') {
    res = res * 10 + (*str - '0');
    if (res < 0) {
      overflow = 1;
      break;
    }
    str++;
  }
  if (overflow)
    res = sign > 0 ? INT32_MAX : INT32_MIN;
  else
    res *= sign;
  return res;
}

char *s21_strcpy(char *dest, const char *src) {
  for (int i = 0; src[i]; i++) dest[i] = src[i];
  dest[s21_strlen(src)] = '\0';
  return dest;
}

char *s21_strcat(char *dest, const char *src) {
  int dest_len = s21_strlen(dest), i = 0;
  for (; src[i]; i++) dest[dest_len + i] = src[i];
  dest[dest_len + i] = '\0';
  return dest;
}

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  char *to = (char *)dest, *from = (char *)src,
       *tmp = (char *)malloc(sizeof(char) * n);
  if (tmp) {
    s21_memcpy(tmp, from, n);
    s21_memcpy(to, tmp, n);
    free(tmp);
  }
  return dest;
}
