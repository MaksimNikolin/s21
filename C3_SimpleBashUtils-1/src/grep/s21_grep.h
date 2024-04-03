#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
  int e;
  int f;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int o;
} Flags;

void grep_flags(int argc, char* argv[], Flags* flag);
// void parse_params();
// void open_file();
// void use_flags();

#endif
