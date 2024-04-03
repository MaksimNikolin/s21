#include "s21_grep.h"

void print_logo() {
  printf("*******************************************************************************************\n");
  printf("***     ********* *******   ******     *** ******* *** ********* ******* ******* **********\n");
  printf("*** **** ******* * ******* *****  ********* ***** **** * ***** * ****** * ****** **********\n");
  printf("*** ***** ***** *** ****** **** ************ *** ***** ** *** ** ***** *** ***** **********\n");
  printf("*** ***** ***** *** ****** *****     ******** * ****** *** * *** ***** *** ***** **********\n");
  printf("*** ***** ****       ***** *********** ******* ******* **** **** ****       **** **********\n");
  printf("*** **** **** ******* **** *********  ******** ******* ********* *** ******* *** **********\n");
  printf("***     **** ********* **   ***     ********** ******* ********* ** ********* **        ***\n");
  printf("*******************************************************************************************\n");
}

void grep_flags(int argc, char* argv[], Flags* flag) {

  int opt;
  int stop_reading_arg = 0;
  int count_e = 0, count_f = 0;

  while ((opt = getopt(argc, argv, "eivclnhsfo")) != -1) {

    switch (opt) {
      case 'e':
        flag->e = 1;
        count_e++;
        stop_reading_arg = 1;
        break;
      case 'f':
        flag->f = 1;
        count_f++;
        stop_reading_arg = 1;
        break;
      case 'i':
        flag->i = 1;
        break;
      case 'v':
        flag->v = 1;
        break;
      case 'c':
        flag->c = 1;
        break;
      case 'l':
        flag->l = 1;
        break;
      case 'n':
        flag->n = 1;
        break;
      case 'h':
        flag->h = 1;
        break;
      case 's':
        flag->s = 1;
        break;
      case 'o':
        flag->o = 1;
        break;
    }

    if (stop_reading_arg == 1) {
      stop_reading_arg = 0;
      //break;
    }
  }

  printf(
      "e - %d\nf - %d\ni - %d\nv - %d\nc - %d\nl - %d\nn - %d\nh - %d\ns - "
      "%d\no - %d\n",
      flag->e, flag->f, flag->i, flag->v, flag->c, flag->l, flag->n, flag->h,
      flag->s, flag->o);
  printf("sum_e - %d\nsum_f - %d\n", count_e, count_f);
}

int main(int argc, char* argv[]) {
  print_logo();

  Flags flag = {0};
  grep_flags(argc, argv, &flag);
  // void parse_params();
  // void open_file();
  // void use_flags();

  return 0;
}
