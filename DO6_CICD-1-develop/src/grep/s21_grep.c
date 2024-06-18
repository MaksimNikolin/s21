#include "s21_grep.h"

void f_flag(char *path, char pattern[SIZE][SIZE], Grep_values *value) {
  char *line = NULL;
  size_t len = 0;

  if (access(path, F_OK) == 0) {
    FILE *filename;
    ssize_t read;
    filename = fopen(path, "rb");
    while ((read = getline(&line, &len, filename)) != -1) {
      if (line[0] != '\n' && line[read - 1] == '\n') line[read - 1] = '\0';
      strcpy(pattern[value->count_pattern], line);
      value->count_pattern++;
    }
    fclose(filename);
    if (line) free(line);
  } else
    printf("error file");
}

void c_l_flags(Grep_values value, Flags flag, int count_match_lines) {
  if (value.count_files > 0 && !flag.h) {
    if (count_match_lines > 0 && flag.n) printf("%s:", value.path);
  }
  if (flag.n && !flag.l && !flag.v && value.count_files == 1)
    printf("%s:", value.path);
  if (flag.n && !flag.l && !flag.v && value.count_files == 2)
    printf("%s:", value.path);
  if (!flag.n && !flag.l && flag.v && value.count_files == 1)
    printf("%s:", value.path);
  if (!flag.n && !flag.l && flag.v && value.count_files == 2)
    printf("%s:", value.path);
  if (!flag.n && !flag.l && !flag.v && value.count_files == 1)
    printf("%s:", value.path);
  if (!flag.n && !flag.l && !flag.v && value.count_files == 2)
    printf("%s:", value.path);
  if (!flag.l) {
    printf("%d\n", count_match_lines);
  } else {
    if (count_match_lines > 1) printf("%s\n", value.path);
  }
}

void o_flag(char *string, regex_t preg) {
  regmatch_t pmatch[1];
  while (regexec(&preg, string, 1, pmatch, 0) == 0) {
    for (int j = 0; j < pmatch->rm_eo; j++) {
      if (j >= pmatch->rm_so) printf("%c", string[j]);
      string[j] = 127;
    }
    printf("\n");
  }
}

void print_strings(Grep_values value, Flags flag, int count_lines,
                   char *string) {
  if (value.count_files > 0 && !flag.h) printf("%s:", value.path);
  if (flag.n) printf("%d:", count_lines);
  if (!flag.o) printf("%s", string);
}

int parser(int argc, char *argv[], Flags *flag, Grep_values *value,
           char patterns[SIZE][SIZE]) {
  int opt = 0;
  while ((opt = getopt_long(argc, argv, "e:ivclnhsf:o", NULL, NULL)) != -1) {
    if (opt == 'e') {
      while (*patterns[value->count_pattern] != 0)
        value->count_pattern = value->count_pattern + 1;
      strcpy(patterns[value->count_pattern], optarg);
      value->count_pattern = value->count_pattern + 1;
      flag->e = 1;
    } else if ((opt == 'i') ? (flag->i = 1) : 0) {
    } else if ((opt == 'v') ? (flag->v = 1) : 0) {
    } else if ((opt == 'c') ? (flag->c = 1) : 0) {
    } else if ((opt == 'l') ? (flag->l = 1) : 0) {
    } else if ((opt == 'n') ? (flag->n = 1) : 0) {
    } else if ((opt == 'h') ? (flag->h = 1) : 0) {
    } else if ((opt == 's') ? (flag->s = 1) : 0) {
    } else if (opt == 'f') {
      while (*patterns[value->count_pattern] != 0)
        value->count_pattern = value->count_pattern + 1;
      f_flag(optarg, patterns, value);
      flag->f = 1;
    } else if ((opt == 'o') ? (flag->o = 1) : 0) {
    }
  }
  return optind;
}

int find_pattern(int opt_ind, char *argv[], char patterns[SIZE][SIZE]) {
  int file_location = 0;
  if (*patterns[0] == 0) {
    file_location = opt_ind + 1;
    strcpy(patterns[0], argv[optind]);
  } else
    file_location = opt_ind;
  return file_location;
}

void grep(Grep_values value, Flags flag, char pattern[SIZE][SIZE]) {
  regex_t preg;

  if (flag.v || flag.c || flag.l) flag.o = 0;
  if (access(value.path, F_OK) == 0) {
    int count_lines = 0, count_match_lines = 0, comp_flag = REG_EXTENDED,
        stop = 0;
    FILE *filename;
    char string[SIZE] = " ";
    filename = fopen(value.path, "rb");
    if (value.count_pattern == 0 && !flag.e && !flag.f) value.count_pattern = 1;
    if (flag.i) comp_flag = REG_ICASE;
    while ((fgets(string, SIZE, filename)) && (stop == 0)) {
      int findline = 0, pattern_no_match = 0;
      count_lines++;
      if (strchr(string, '\n') == NULL) strcat(string, "\n");
      for (int i = 0; i < value.count_pattern; i++) {
        int match = 0;
        regcomp(&preg, pattern[i], comp_flag | REG_NEWLINE);
        int rgx_res = regexec(&preg, string, 0, NULL, 0);
        if (rgx_res == 0 && !flag.v) match = 1;
        if (rgx_res == REG_NOMATCH && flag.v) {
          pattern_no_match++;
          if (pattern_no_match == value.count_pattern) match = 1;
        }
        if (flag.l && !flag.c && match == 1) {
          printf("%s\n", value.path);
          match = 0, stop = 1;
        }
        if (flag.c && match == 1) {
          count_match_lines++, match = 0;
        }
        if (findline == 0 && match == 1) {
          print_strings(value, flag, count_lines, string);
          findline++;
        }
        if (flag.o) o_flag(string, preg);
        regfree(&preg);
      }
    }
    if (flag.c) c_l_flags(value, flag, count_match_lines);
    fclose(filename);
  } else if (!flag.s) {
    fprintf(stderr, "s21_grep: %s: No such file or directory\n", value.path);
  }
}

int main(int argc, char *argv[]) {
  char patterns[SIZE][SIZE] = {0};
  int opt_ind = 0;
  Flags option = {0};
  Grep_values value = {0};
  regex_t regex;
  opt_ind = parser(argc, argv, &option, &value, patterns);
  if (argc >= 3 && option.err != 1 && opt_ind != argc) {
    int file_location = 0;
    file_location = find_pattern(opt_ind, argv, patterns);
    for (int i = 0; i < value.count_pattern; i++) {  // for label incorr args
      int reti = regcomp(&regex, patterns[i],
                         REG_EXTENDED | (option.i ? REG_ICASE : 0));
      if (reti) {
        regfree(&regex);
        fprintf(stderr, "s21_grep: Trailing backslash\n");
        exit(0);
      }
      regfree(&regex);
    }
    while (file_location < argc) {
      if (argv[file_location + 1] != NULL) {
        value.count_files = value.count_files + 1;
      }
      value.path = argv[file_location];
      grep(value, option, patterns);
      file_location++;
    }
  }
}
