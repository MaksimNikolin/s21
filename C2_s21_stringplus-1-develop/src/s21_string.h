#ifndef SRC_S21_STRING_H_
#define SRC_S21_STRING_H_

#include <stdio.h>
#include <stdlib.h>

#define s21_size_t unsigned long long
#define s21_NULL (void *)0
#define s21_bool int

void *s21_memchr(const void *str, int c, s21_size_t n);                       // yonnrose
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strerror(int errnum);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);
int firstindex(const char *src, const char *totrim, int start);
int lastindex(const char *src, const char *totrim, int end);

s21_size_t s21_strlen(const char *str);                                       // daisymal
char *s21_strncat(char *str1, const char *str2, s21_size_t n);
char *s21_strchr(const char *str, int c);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);

void *s21_to_upper(const char *str);                                          // kokoschl
void *s21_to_lower(const char *str);
char *s21_strtok(char *str, const char *delim);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strrchr(const char *str, int c);

#include "s21_sprintf.h"                                                      // ilynpois
#include "s21_sscanf.h"

#endif  // SRC_S21_STRING_H_
