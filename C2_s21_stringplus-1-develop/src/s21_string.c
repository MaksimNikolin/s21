#include "s21_string.h"

void print_logo() {
  printf("******************************************************************************************\n");
  printf("***     ********* *******   ******    *** ******* *** ********* ******* ******* **********\n");
  printf("*** **** ******* * ******* **** ********** ***** **** * ***** * ****** * ****** **********\n");
  printf("*** ***** ***** *** ****** **** *********** *** ***** ** *** ** ***** *** ***** **********\n");
  printf("*** ***** ***** *** ****** ******  ********* * ****** *** * *** ***** *** ***** **********\n");
  printf("*** ***** ****       ***** ********** ******* ******* **** **** ****       **** **********\n");
  printf("*** **** **** ******* **** ********** ******* ******* ********* *** ******* *** **********\n");
  printf("***     **** ********* **   ***     ********* ******* ********* ** ********* **        ***\n");
  printf("******************************************************************************************\n");
}

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char *s = (const unsigned char *)str;
  unsigned char uc = (unsigned char)c;
  for (s21_size_t i = 0; i < n; ++i) {
    if (s[i] == uc) {
      return (void *)(s + i);
    }
  }
  return s21_NULL;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *s1 = (const unsigned char *)str1;
  const unsigned char *s2 = (const unsigned char *)str2;
  for (s21_size_t i = 0; i < n; ++i) {
    if (s1[i] != s2[i]) {
      return s1[i] - s2[i];
    }
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
  while (n > 0 && *src != '\0') {
    *dest++ = *src++;
    --n;
  }
  while (n > 0) {
    *dest++ = '\0';
    --n;
  }
  return start;
}

s21_size_t s21_strcspn(const char *str, const char *reject) {
  const char *s;
  const char *r;
  s21_size_t count = 0;
  for (s = str; *s != '\0'; ++s) {
    for (r = reject; *r != '\0'; ++r) {
      if (*s == *r) {
        return count;
      }
    }
    ++count;
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

char *s21_strdup(const char *str) {
  s21_size_t len = 0;
  const char *s;
  for (s = str; *s != '\0'; ++s) {
    ++len;
  }
  char *dup = (char *)malloc(len + 1);
  if (dup == s21_NULL) return s21_NULL;
  for (s21_size_t i = 0; i <= len; ++i) {
    dup[i] = str[i];
  }
  return dup;
}

char *s21_strchr(const char *str, int c) {
  int i = 0;
  while (str[i] && str[i] != c) i++;
  return c == str[i] ? (char *)str + i : s21_NULL;
}

void *s21_trim(const char *src, const char *trim_chars) {
  if (!src || !trim_chars) return s21_strdup("");
  s21_size_t src_len = s21_strlen(src);
  s21_size_t start = 0;
  while (src[start] != '\0' && s21_strchr(trim_chars, src[start]) != s21_NULL)
    start++;
  s21_size_t end = src_len;
  while (end > start && s21_strchr(trim_chars, src[end - 1]) != s21_NULL) end--;
  char *trimmed_str = s21_strdup(src + start);
  if (!trimmed_str) return s21_NULL;
  trimmed_str[end - start] = '\0';
  return trimmed_str;
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

void *s21_to_upper(const char *str) {
  char *res = s21_NULL;
  int length = 0;
  length = (int)s21_strlen(str);
  res = (char *)calloc(length + 1, sizeof(char));
  if (res != s21_NULL) {
    for (int i = 0; i < length; i++) {
      if (str[i] >= 'a' && str[i] <= 'z') {
        res[i] = str[i] - (char)('a' - 'A');
      } else {
        res[i] = str[i];
      }
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
      } else {
        res[i] = str[i];
      }
    }
  }
  return res;
}

char *s21_strtok(char *str, const char *delim) {
  static char *next_token = s21_NULL;
  char *token_start;

  if (str != s21_NULL) {
    next_token = str;
  } else {
    if (next_token == s21_NULL) {
      return s21_NULL;
    }
  }

  while (*next_token != '\0' && s21_strchr(delim, *next_token) != s21_NULL) {
    next_token++;
  }

  if (*next_token == '\0') {
    return s21_NULL;
  }

  token_start = next_token;

  while (*next_token != '\0' && s21_strchr(delim, *next_token) == s21_NULL) {
    next_token++;
  }

  if (*next_token == '\0') {
    next_token = s21_NULL;
  } else {
    *next_token = '\0';
    next_token++;
  }

  return token_start;
}

void computeLPSArray(const char *needle, int *lps) {
  int len = 0;
  lps[0] = 0;

  for (int i = 1; needle[i] != '\0'; i++) {
    while (len > 0 && needle[i] != needle[len]) len = lps[len - 1];
    if (needle[i] == needle[len]) len++;
    lps[i] = len;
  }
}

char *s21_strstr(const char *haystack, const char *needle) {
  if (*needle == '\0') return (char *)haystack;
  int m = s21_strlen(needle);
  int n = s21_strlen(haystack);

  int *lps = (int *)malloc(sizeof(int) * m);

  computeLPSArray(needle, lps);

  for (int i = 0, j = 0; i < n;) {
    if (needle[j] == haystack[i]) {
      j++;
      i++;
    }
    if (j == m) {
      free(lps);
      return (char *)(haystack + i - j);
    }
    if (i < n && needle[j] != haystack[i]) {
      if (j != 0)
        j = lps[j - 1];
      else
        i++;
    }
  }

  free(lps);
  return s21_NULL;
}

char *s21_strrchr(const char *str, int c) {
  const char *last_occurrence = s21_NULL;

  while (*str++) {
    if (*str == (char)c) last_occurrence = str;
  }

  return (char *)last_occurrence;
}
