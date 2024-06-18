#include "s21_cat.h"

void cat_flags(int argc, char* argv[], struct flags* flag) {
  int options = 0, long_index = 0;
  struct option long_flags[] = {{"number-nonblank", 0, 0, 'b'},
                                {"number", 0, 0, 'n'},
                                {"squeeze-blank", 0, 0, 's'},
                                {0, 0, 0, 0}};

  while ((options = getopt_long(argc, argv, "bnsveEtT", long_flags,
                                &long_index)) != -1) {
    /****/ if ((options == 'b') ? (flag->b = !(flag->n = 0)) : 0) {
    } else if ((options == 'n') ? (flag->n = 1) : 0) {
    } else if ((options == 's') ? (flag->s = 1) : 0) {
    } else if ((options == 'v') ? (flag->v = 1) : 0) {
    } else if ((options == 'e') ? (flag->v = flag->e = 1) : 0) {
    } else if ((options == 'E') ? (flag->e = 1) : 0) {
    } else if ((options == 't') ? (flag->v = flag->t = 1) : 0) {
    } else if ((options == 'T') ? (flag->t = 1) : 0) {
    }
  }
}

void open_file(int argc, char* argv[], struct flags flag) {
  int argv_index = 1, lines_count = 1, prev_ch = 1;
  while (*argv[argv_index] == '-') {
    argv_index++;
  }
  for (; argv_index < argc; argv_index++) {
    FILE* file = NULL;
    file = fopen(argv[argv_index], "rb");
    if (file == NULL) {
      fprintf(stderr, "cat: %s: No such file or directory\n", argv[argv_index]);
      continue;
    }
    use_flags(file, flag, &lines_count, &prev_ch);
    fclose(file);
  }
}

void use_flags(FILE* file, struct flags flag, int* lines_count, int* prev_ch) {
  char ch;
  int new_line = 1;
  while ((ch = fgetc(file)) != EOF) {
    if (flag.s) {
      if (ch == '\n') {
        (*prev_ch)++;
        if ((*prev_ch) >= 3) {
          continue;
        }
      } else
        (*prev_ch) = 0;
    }
    if (flag.b) {
      if (new_line) {
        if (ch != '\n') {
          printf("%6d\t", (*lines_count)++);
          new_line = 0;
        }
      }
      if (ch == '\n') new_line = 1;
    }
    if (flag.n && !flag.b) {
      if (new_line) {
        printf("%6d\t", (*lines_count)++);
        new_line = 0;
      }
      if (ch == '\n') new_line = 1;
    }
    if (flag.e) {
      if (ch == '\n') printf("$");
    }
    if (flag.t) {
      if (ch == '\t') {
        printf("^");
        ch = 'I';
      }
    }
    if (flag.v) {
      if (ch == 0)
        printf("^@");
      else if (ch == 127)
        printf("^?");
      else if (ch < 0)
        if (ch + 128 < 32)
          printf("M-^%c", ch + 128 + 64);
        else
          printf("M-%c", ch + 128);
      else if (ch < 32 && ch != 9 && ch != 10 && ch != 13)
        printf("^%c", ch + 64);
      else
        putchar(ch);
    } else
      putchar(ch);
  }
}

int main(int argc, char* argv[]) {
  struct flags flag = {0};
  cat_flags(argc, argv, &flag);
  open_file(argc, argv, flag);
  return 0;
}
