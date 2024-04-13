#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#define _GNU_SOURCE
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define SIZE 1024
#define MAX_MATCHES 20

typedef struct {
  int e, i, v, c, l, n, h, s, f, o, err;
} Flags;

typedef struct {
  char *path;
  int count_files;
  int count_pattern;
} Grep_values;

void print_logo();
int parser(int argc, char *argv[], Flags *flag, Grep_values *value, char pattern[SIZE][SIZE]);
int find_pattern(int opt_ind, char *argv[], char patterns[SIZE][SIZE]);
void grep(Grep_values value, Flags flag, char pattern[SIZE][SIZE]);
void f_flag(char *path, char pattern[SIZE][SIZE], Grep_values *value);
void c_l_flags(Grep_values value, Flags flag, int count_match_lines);
void o_flag(char *start_point, regex_t preg);
void print_strings(Grep_values value, Flags flag, int count_lines, char *string);

#endif
