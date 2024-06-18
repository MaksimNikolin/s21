#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include <getopt.h>
#include <stdio.h>
#include <unistd.h>

struct flags {
  int b, v, e, n, s, t;
};

void cat_flags(int argc, char* argv[], struct flags* flag);
void open_file(int argc, char* argv[], struct flags flag);
void use_flags(FILE* file, struct flags flag, int* lines_count, int* prev_ch);

#endif
