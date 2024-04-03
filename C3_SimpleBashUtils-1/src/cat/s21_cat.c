#include "s21_cat.h"

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

void cat_flags(int argc, char* argv[], struct flags* flag) {
  int options = 0, long_index = 0;

  struct option long_flags[] = {{"number-nonblank", 0, 0, 'b'},
                                {"number", 0, 0, 'n'},
                                {"squeeze-blank", 0, 0, 's'},
                                {0, 0, 0, 0}};

  while ((options = getopt_long(argc, argv, "bnsveEtT", long_flags,
                                &long_index)) != -1) {
    switch (options) {
      case 'b':
        flag->b = 1;
        break;
      case 'n':
        flag->n = 1;
        break;
      case 's':
        flag->s = 1;
        break;
      case 'v':
        flag->v = 1;
        break;
      case 'e':
        flag->v = 1;
        flag->e = 1;
        break;
      case 'E':
        flag->e = 1;
        break;
      case 't':
        flag->v = 1;
        flag->t = 1;
        break;
      case 'T':
        flag->t = 1;
        break;
    }
  }
  flag->n = (flag->b == 1) ? 0 : flag->n;
}

void open_file(int argc, char* argv[], struct flags flag) {
  int argv_index = 1, lines_count = 1, prev_ch = 1;

  while (*argv[argv_index] == '-') {
    argv_index++;
  }

  for (; argv_index < argc; argv_index++) {
    FILE* file = NULL;
    file = fopen(argv[argv_index], "r");

    if (file == NULL) {
      printf("cat: %s: No such file or directory\n", argv[argv_index]);
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
      } else {
        (*prev_ch) = 0;
      }
    }

    if (flag.b) {
      if (new_line) {
        if (ch != '\n') {
          printf("%6d\t", (*lines_count)++);
          new_line = 0;
        }
      }
      if (ch == '\n') {
        new_line = 1;
      }
    }

    if (flag.n && !flag.b) {
      if (new_line) {
        printf("%6d\t", (*lines_count)++);
        new_line = 0;
      }
      if (ch == '\n') {
        new_line = 1;
      }
    }

    if (flag.e) {
      if (ch == '\n') {
        printf("$");
      }
    }

    if (flag.t) {
      if (ch == '\t') {
        printf("^");
        ch = 'I';
      }
    }

    if (flag.v) {
      if (ch == 0) {
        printf("^@");
      } else if (ch == 127) {
        printf("^?");
      }

      else if (ch < 0)
        if (ch + 128 < 32)
          printf("M-^%c", ch + 128 + 64);
        else
          printf("M-%c", ch + 128);

      else if (ch > 0 && ch < 32 && ch != 9 && ch != 10 && ch != 13)
        printf("^%c", ch + 64);

      else
        putchar(ch);
    }

    else
      putchar(ch);
  }
}

int main(int argc, char* argv[]) {
  print_logo();

  struct flags flag = {0};
  cat_flags(argc, argv, &flag);
  open_file(argc, argv, flag);

  return 0;
}
