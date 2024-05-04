#include "s21_sscanf.h"

int s21_sscanf(const char *str, const char *format, ...) {
  setlocale(LC_ALL, "");
  setlocale(LC_NUMERIC, "en_US.UTF-8");
  int res = 0;
  ops options = {0, 0, 0, 0, 0, 0, 0, '\0'};
  char *tmp = malloc((s21_strlen(str) + 1) * sizeof(char));
  if (tmp) {
    tmp = s21_strcpy2(tmp, str);
    oksym(&tmp, &options);
    if (!*tmp) options.end = 1;
    tmp = s21_strcpy2(tmp - options.count, str);
    options.count = 0;
    va_list args;
    va_start(args, format);
    for (; *format; format++) {
      if (optionsin(&tmp, &options, format)) continue;
      if (options.format) {
        if ((int)*format > 47 && (int)*format < 58) {
          options.wid = options.wid * 10 + (int)*format - 48;
          continue;
        }
        res += processformat(args, &options, &tmp, format);
      } else casenon(&tmp, &options, format);
      if (isbreak(args, &options, &tmp, format)) {
        if (!res && options.end) res = -1;
        break;
      }
    }
    free(tmp - options.count);
    va_end(args);
  }
  return res;
}

long s21_atoi2(char *str, char **strlim, int base) {
  char *start = str;
  long int res = 0;
  int sign = 1;
  // while (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\r' ||
  //        *str == '\x0B' || *str == '\f') str++;
  if (*str == '+') str++;
  if (*str == '-') sign = -1, str++;
  if (base == 0 && *str == '0' && *(str + 1) == 'x') base = 16;
  else if (base == 0 && *str == '0') base = 8;
  else if (base == 0) base = 10;
  if (base == 16 && *str == '0' && *(str + 1) == 'x') str += 2;
  if (base == 10) {
    for (; *str >= '0' && *str <= '9'; str++, res *= 10) res += *str - 48;
    res /= 10;
  } else if (base == 8) {
    for (; *str >= '0' && *str <= '9'; str++, res *= 8) res += *str - 48;
    res /= 8;
  } else if (base == 16) {
    for (; (*str >= '0' && *str <= '9') || (*str >= 'A' && *str <= 'F') ||
           (*str >= 'a' && *str <= 'f');
         str++, res *= 16) {
      if (*str >= '0' && *str <= '9')
        res += *str - 48;
      else if ((*str >= 'A' && *str <= 'F')) res += +*str - 55;
      else res += +*str - 87;
    }
    res /= 16;
  }
  if (strlim) *strlim = start + (str - start);
  return sign * res;
}

unsigned long s21_atoul(char *str, char **strlim, int base) {
  return s21_atoi2(str, strlim, base);
}

float s21_atof(char *str, char **strlim) {
  char *start = str;
  float a, decplace, b;
  int sign = 1;
  while (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\r' ||
         *str == '\x0B' || *str == '\f') str++;
  if (*str == '+') str++;
  if (*str == '-') sign = -1, str++;
  for (a = 0; *str && isdigit(*str); str++) a = a * 10 + (*str - '0');
  if (*str == '.') str++;
  for (decplace = 1.; *str && isdigit(*str); str++, decplace *= 10.)
    a = a * 10. + (*str - '0');
  if (*str == 'e' || *str == 'E') {
    int esign = 1;
    if (a <= 1e-6) a = 1;
    str++;
    if (*str == '-') esign = -1, str++;
    if (*str == '+') str++;
    for (b = 0; *str && isdigit(*str); str++) b = b * 10 + (*str - '0');
    b *= esign;
  } else b = 0;
  if ((*str == 'n' || *str == 'N') && (str[1] == 'a' || str[1] == 'A') &&
      (str[2] == 'n' || str[2] == 'N')) str += 3, a = NAN * sign;
  if ((*str == 'i' || *str == 'I') && (str[1] == 'n' || str[1] == 'N') &&
      (str[2] == 'f' || str[2] == 'F')) str += 3, a = INFINITY * sign;
  if (strlim) *strlim = start + (str - start);
  return (isnan(a) || isinf(a)) ? a : (a * sign / decplace) * powl(10, b);
}

double s21_atod(char *str, char **strlim) {
  char *start = str;
  double a, decplace, b;
  int sign = 1;
  while (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\r' ||
         *str == '\x0B' || *str == '\f') str++;
  if (*str == '+') str++;
  if (*str == '-') sign = -1, str++;
  for (a = 0; *str && isdigit(*str); str++) a = a * 10 + (*str - '0');
  if (*str == '.') str++;
  for (decplace = 1.; *str && isdigit(*str); str++, decplace *= 10.)
    a = a * 10. + (*str - '0');
  if (*str == 'e' || *str == 'E') {
    int esign = 1;
    if (a <= 1e-6) a = 1;
    str++;
    if (*str == '-') esign = -1, str++;
    if (*str == '+') str++;
    for (b = 0; *str && isdigit(*str); str++) b = b * 10 + (*str - '0');
    b *= esign;
  } else b = 0;
  if ((*str == 'n' || *str == 'N') && (str[1] == 'a' || str[1] == 'A') &&
      (str[2] == 'n' || str[2] == 'N')) str += 3, a = NAN * sign;
  if ((*str == 'i' || *str == 'I') && (str[1] == 'n' || str[1] == 'N') &&
      (str[2] == 'f' || str[2] == 'F')) str += 3, a = INFINITY * sign;
  if (strlim) *strlim = start + (str - start);
  return (isnan(a) || isinf(a)) ? a : (a * sign / decplace) * powl(10, b);
}

long double s21_atold(char *str, char **strlim) {
  char *start = str;
  long double a, decplace, b;
  int sign = 1;
  // while (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\r' ||
  //        *str == '\x0B' || *str == '\f') str++;
  if (*str == '+') str++;
  if (*str == '-') sign = -1, str++;
  for (a = 0; *str && isdigit(*str); str++) a = a * 10 + (*str - '0');
  if (*str == '.') str++;
  for (decplace = 1.; *str && isdigit(*str); str++, decplace *= 10.)
    a = a * 10. + (*str - '0');
  if (*str == 'e' || *str == 'E') {
    int esign = 1;
    if (a <= 1e-6) a = 1;
    str++;
    if (*str == '-') esign = -1, str++;
    if (*str == '+') str++;
    for (b = 0; *str && isdigit(*str); str++) b = b * 10 + (*str - '0');
    b *= esign;
  } else b = 0;
  // if ((*str == 'n' || *str == 'N') && (str[1] == 'a' || str[1] == 'A') &&
  //       (str[2] == 'n' || str[2] == 'N')) str += 3, a = NAN * sign;
  if ((*str == 'i' || *str == 'I') && (str[1] == 'n' || str[1] == 'N') &&
      (str[2] == 'f' || str[2] == 'F')) str += 3, a = INFINITY * sign;
  if (strlim) *strlim = start + (str - start);
  return (isnan(a) || isinf(a)) ? a : (a * sign / decplace) * powl(10, b);
}

int opd(va_list args, ops *op, char **src, int base) {
  int res = 0;
  char *strlim;
  check_buffer(src, op);
  if (s21_atoi2(*src, s21_NULL, base) ||
      *(*src + s21_strspn2(*src, "\n\t \f\x0B\r+-")) == '0') {
    if (!op->supr) {
      res++;
      if (op->len == 1)
        *(short int *)va_arg(args, void *) = s21_atoi2(*src, &strlim, base);
      else if (op->len == 2)
        *(long int *)va_arg(args, void *) = s21_atoi2(*src, &strlim, base);
      else
        *(int *)va_arg(args, void *) = s21_atoi2(*src, &strlim, base);
    } else s21_atoi2(*src, &strlim, base);
    op->count += strlim - *src, *src = strlim;
  } else op->err = 1;
  op->format = 0;
  return res;
}

int opu(va_list args, ops *op, char **src, int base) {
  int res = 0;
  char *strlim;
  check_buffer(src, op);
  if (s21_atoul(*src, s21_NULL, base) ||
      *(*src + s21_strspn2(*src, "\n\t \f\x0B\r+")) == '0') {
    if (!op->supr) {
      if (s21_atoul(*src, s21_NULL, base) || **src == '0') res++;
      if (op->len == 1)
        *(short unsigned *)va_arg(args, void *) =
            s21_atoul(*src, &strlim, base);
      else if (op->len == 2)
        *(long unsigned *)va_arg(args, void *) = s21_atoul(*src, &strlim, base);
      else
        *(unsigned *)va_arg(args, void *) = s21_atoul(*src, &strlim, base);
    } else s21_atoul(*src, &strlim, base);
    op->count += strlim - *src;
    *src = strlim;
  } else op->err = 1;
  op->format = 0;
  return res;
}

int opf(va_list args, ops *op, char **src) {
  int res = 0;
  char *strlim;
  check_buffer(src, op);
  if (fabs(s21_atod(*src, s21_NULL)) >= 1e-100 ||
      isnan(s21_atod(*src, s21_NULL)) ||
      *(*src + s21_strspn2(*src, "\n\t \f\x0B\r+-")) == '0') {
    if (!op->supr) {
      res++;
      if (op->len == 3)
        *(long double *)va_arg(args, void *) = s21_atold(*src, &strlim);
      else if (op->len == 2)
        *(double *)va_arg(args, void *) = s21_atod(*src, &strlim);
      else
        *(float *)va_arg(args, void *) = s21_atof(*src, &strlim);
    } else s21_atof(*src, &strlim);
    op->count += strlim - *src, *src = strlim;
  } else op->err = 1;
  op->format = 0;
  return res;
}

int opp(va_list args, ops *op, char **src) {
  int res = 0;
  char *strlim;
  if (s21_atoul(*src, s21_NULL, 16) ||
      *(*src + s21_strspn2(*src, "\n\t \f\x0B\r+-")) == '0') {
    check_buffer(src, op);
    if (!op->supr) {
      if (s21_atoul(*src, s21_NULL, 16) || **src == '0') res++;
      *(void **)va_arg(args, void **) = (void *)s21_atoul(*src, &strlim, 16);
    } else s21_atoul(*src, &strlim, 16);
    op->count += strlim - *src, *src = strlim;
  } else op->err = 1;
  op->format = 0;
  return res;
}

int opc(va_list args, ops *op, char **src) {
  int res = 0;
  if (!op->wid) op->wid = 2;
  if (!op->supr) {
    res++;
    if (op->len == 2)
      mbtowc((wchar_t *)va_arg(args, wchar_t *), *src, op->wid);
    else
    *(char *)va_arg(args, char *) = **src;
  }
  // if (**src < 0 && op->len == 2) (*src)++, op->count++;
  (*src)++, op->count++, op->format = 0;
  return res;
}

int opst(va_list args, ops *op, char **src) {
  int res = 0;
  char *new_str = malloc(sizeof(char));
  if (new_str) {
    oksym(src, op);
    int i = 0;
    for (; **src && **src != ' ' && **src != '\n' && **src != '\t' &&
           **src != '\r' && **src != '\x0B' && **src != '\f' &&
           (op->wid == 0 || i < op->wid);
         i++, (*src)++) {
      new_str[i] = **src;
      new_str = realloc(new_str, (i + 2) * sizeof(char));
      if (!new_str) exit(0);
    }
    new_str[i] = '\0';
    int k = s21_strlen(new_str) + 1;
    va_list tmp_list;
    va_copy(tmp_list, args);
    for (int j = 0; j < k; j++) {
      if (!op->supr) {
        if (!op->len) *((char *)va_arg(tmp_list, char *) + j) = new_str[j];
        if (j + 1 < k) va_end(tmp_list), va_copy(tmp_list, args);
      }
    }
    va_end(args);
    va_copy(args, tmp_list);
    if (op->len == 2 && !op->supr)
      mbstowcs((wchar_t *)va_arg(args, wchar_t *), new_str, k);
    free(new_str);
    if (!op->supr) res++;
    op->count += k - 1, op->format = 0, va_end(tmp_list);
  }
  return res;
}

void oksym(char **src, ops *op) {
  while (**src == ' ' || **src == '\n' || **src == '\t' || **src == '\r' ||
         **src == '\x0B' || **src == '\f') (*src)++, op->count++;
}

void oppe(char **src, ops *op, const char *format) {
  oksym(src, op);
  if (*format == **src) op->count++, (*src)++;
  else op->err = 1;
  op->format = 0;
}

int optionsin(char **src, ops *op, const char *format) {
  int res = 0;
  if (*format == '%' && !op->format) {
    res++, op->format = 1, op->supr = 0, op->len = 0;
    if (op->buff) *(*src + s21_strlen(*src)) = op->buff, op->buff = '\0';
    op->wid = 0;
  }
  return res;
}

void opn(va_list args, ops *op) {
  if (!op->supr) {
    if (op->len == 1) *(short int *)va_arg(args, void *) = op->count;
    else if (op->len == 2) *(long int *)va_arg(args, void *) = op->count;
    else *(int *)va_arg(args, void *) = op->count;
  }
  op->format = 0;
}

void casenon(char **src, ops *op, const char *format) {
  if (*format == ' ' || *format == '\t' || *format == '\n' || *format == '\r' ||
      *format == '\x0B') {
    while (*format == **src) (*src)++, op->count++;
  } else if (**src == *format) (*src)++, op->count++;
  else op->err = 1;
}

int isbreak(va_list args, ops *op, char **src, const char *format) {
  int res = 0;
  va_list backup;
  va_copy(backup, args);
  if ((!**src && !op->buff &&
       (s21_strstr(format, "%n") != s21_strchr(format, '%') ||
        !s21_strstr(format, "%n"))) ||
      !va_arg(backup, void *) || op->err) res = 1;
  va_end(backup);
  return res;
}

int processformat(va_list args, ops *op, char **src, const char *format) {
  int res = 0;
  char f = *format;

  return (f == 'x' || f == 'X') ? res += opu(args, op, src, 16)
       : (f == 'p')               ? res += opp(args, op, src)
       : (f == 'e' || f == 'E' || f == 'f' || f == 'g' || f == 'G') ? res += opf(args, op, src)
       : (f == 'c')               ? res += opc(args, op, src)
       : (f == 'd')               ? res += opd(args, op, src, 10)
       : (f == 'i')               ? res += opd(args, op, src, 0)
       : (f == 'o')               ? res += opu(args, op, src, 8)
       : (f == 's')               ? res += opst(args, op, src)
       : (f == 'u')               ? res += opu(args, op, src, 10)
       : (f == 'n')               ? (opn(args, op), 0)
       : (f == '%')               ? (oppe(src, op, format), 0)
       : (f == 'h')               ? (op->len = 1, 0)
       : (f == '*')               ? (op->supr = 1, 0)
       : (f == 'l')               ? (op->len = 2, 0)
       : (f == 'L')               ? (op->len = 3, 0)
       : 0;
}

void check_buffer(char **src, ops *op) {
  oksym(src, op);
  if (!op->buff && op->wid && op->wid < (int)s21_strlen(*src)) op->buff = *(*src + op->wid), *(*src + op->wid) = '\0';
}

s21_size_t s21_strspn2(const char *str, const char *keys) {
  s21_size_t strLength = s21_strlen(str), res = 0;
  for (s21_size_t x = 0; res == 0 && x < strLength; x += 1) {
    if (s21_strchr(keys, str[x]) != s21_NULL) res = x + 1;
  }
  return res;
}

char *s21_strcpy2(char *destptr, const char *srcptr) {
  int srcptrLength = s21_strlen(srcptr);
  for (int i = 0; i <= srcptrLength; i++) {
    destptr[i] = srcptr[i];
  }
  return destptr;
}
