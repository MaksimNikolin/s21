#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char *s = (const unsigned char *)str;
  unsigned char uc = (unsigned char)c;
  for (s21_size_t i = 0; i < n; ++i) {
    if (s[i] == uc) return (void *)(s + i);
  }
  return s21_NULL;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *s1 = (const unsigned char *)str1;
  const unsigned char *s2 = (const unsigned char *)str2;
  for (s21_size_t i = 0; i < n; ++i) {
    if (s1[i] != s2[i]) return s1[i] - s2[i];
  }
  return 0;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *destination = (char *)dest;
  const char *source = (const char *)src;
  for (s21_size_t i = 0; i < n; ++i) {
    destination[i] = source[i];
  }
  return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *s = (unsigned char *)str;
  unsigned char uc = (unsigned char)c;
  for (s21_size_t i = 0; i < n; ++i) {
    s[i] = uc;
  }
  return str;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  char *start = dest;
  while (n > 0 && *src != '\0') *dest++ = *src++, n--;
  while (n > 0) *dest++ = '\0', n--;
  return start;
}

s21_size_t s21_strcspn(const char *str, const char *reject) {
  const char *s, *r;
  s21_size_t count = 0;
  for (s = str; *s != '\0'; ++s) {
    for (r = reject; *r != '\0'; ++r) {
      if (*s == *r) return count;
    }
    count++;
  }
  return count;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  char *res = s21_NULL;
  if (s21_strcspn(str1, str2) != s21_strlen(str1) && *str1 != '\0')
    res = (char *)str1 + s21_strcspn(str1, str2);
  return res;
}

s21_size_t s21_strlen(const char *str) {
  s21_size_t len = 0;
  if (str) {
    for (int i = 0; str[i]; i++) len++;
  }
  return len;
}

char *s21_strncat(char *str1, const char *str2, s21_size_t n) {
  s21_size_t dest_len = s21_strlen(str1);
  s21_size_t i = 0;
  for (; i < n && str2[i]; i++) {
    str1[dest_len + i] = str2[i];
  }
  str1[dest_len + i] = '\0';
  return str1;
}

char *s21_strchr(const char *str, int c) {
  int i = 0;
  while (str[i] && str[i] != c) i++;
  return c == str[i] ? (char *)str + i : s21_NULL;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int res = 0;
  while ((*str1 || *str2) && n--)
    if (*str1++ != *str2++) {
      res = (unsigned char)*--str1 - (unsigned char)*--str2;
      break;
    }
  return res;
}

char *s21_strtok(char *str, const char *delim) {
  static char *result = s21_NULL;
  if (str) {
    result = str;
    while (*result && s21_strchr(delim, *result)) *result++ = '\0';
  }
  if (result != s21_NULL) {
    if (*result != '\0') {
      str = result;
      while (*result && !s21_strchr(delim, *result)) result++;
      while (*result && s21_strchr(delim, *result)) *result++ = '\0';
    } else
      str = s21_NULL;
  }
  return str;
}

char *s21_strstr(const char *str1, const char *str2) {
  char *ret = s21_NULL;
  if (str1 != s21_NULL && str2 != s21_NULL) {
    s21_size_t len = 0, check = 0;
    int stop = 0;
    while (str1[len] != '\0' && stop != 1) {
      if (str1[len] == str2[0]) {
        s21_size_t k = len;
        for (int j = 0; str2[j] != '\0'; j++) {
          if (str1[k] == str2[j]) check++;
          k++;
        }
      }
      if ((check - 1 == s21_strlen(str2) && str1[len + check - 1] == '\0') ||
          (check == s21_strlen(str2) && str1[len + check - 1] != '\0'))
        stop = 1;
      len++;
    }
    if (stop == 1) {
      ret = (char *)str1 + len - 1;
    }
  }
  if (s21_strlen(str2) == 0) ret = (char *)str1;
  return ret;
}

char *s21_strrchr(const char *str, int c) {
  char *ret = s21_NULL;
  int stop = 0;
  int i = (int)s21_strlen(str);
  while (i >= 0 && stop != 1) {
    if (c == str[i]) stop = 1;
    i--;
  }
  if (stop == 1) ret = (char *)str + i + 1;
  return ret;
}

// Special functions

void *s21_to_upper(const char *str) {
  char *res = s21_NULL;
  int length = 0;
  length = (int)s21_strlen(str);
  res = (char *)calloc(length + 1, sizeof(char));
  if (res != s21_NULL) {
    for (int i = 0; i < length; i++) {
      if (str[i] >= 'a' && str[i] <= 'z') {
        res[i] = str[i] - ('a' - 'A');
      } else
        res[i] = str[i];
    }
  }
  return res;
}

void *s21_to_lower(const char *str) {
  char *res = s21_NULL;
  int length = (int)s21_strlen(str);
  res = (char *)calloc(length + 1, sizeof(char));
  if (res != s21_NULL) {
    for (int i = 0; i < length; i++) {
      if (str[i] >= 'A' && str[i] <= 'Z') {
        res[i] = str[i] + ('a' - 'A');
      } else
        res[i] = str[i];
    }
  }
  return res;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  if (src == s21_NULL || str == s21_NULL) return s21_NULL;
  s21_size_t src_len = s21_strlen(src);
  s21_size_t str_len = s21_strlen(str);
  if (start_index > src_len) return s21_NULL;
  char *new_str = (char *)malloc((src_len + str_len + 1) * sizeof(char));
  if (new_str == s21_NULL) return s21_NULL;
  s21_memcpy(new_str, src, start_index);
  s21_memcpy(new_str + start_index, str, str_len);
  s21_memcpy(new_str + start_index + str_len, src + start_index,
             src_len - start_index);
  new_str[src_len + str_len] = '\0';
  return new_str;
}

int firstindex(const char *src, const char *totrim, int start) {
  int res = 0;
  int size = s21_strlen(totrim);
  for (int i = 0; i < size; i++) {
    if (src[start] == totrim[i]) res = 1;
  }
  return res;
}

int lastindex(const char *src, const char *totrim, int end) {
  int res = 0;
  int size = s21_strlen(totrim);
  for (int i = 0; i < size; i++) {
    if (src[end] == totrim[i]) res = 1;
  }
  return res;
}

void *s21_trim(const char *src, const char *trim_chars) {
  char *res = s21_NULL;
  if (src) {
    if (trim_chars && trim_chars[0]) {
      res = calloc(s21_strlen(src) + 1, sizeof(char));
      int start = 0, end = s21_strlen(src);
      while (firstindex(src, trim_chars, start)) start++;
      if (start != end) {
        while (lastindex(src, trim_chars, end - 1)) end--;
        int k = 0;
        for (int i = start; i < end; i++) res[k] = src[i], k++;
      } else {
        res[0] = '\0';
      }
    } else {
      res = s21_trim(src, "\t\n ");
    }
  }
  return res;
}
