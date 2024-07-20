CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c11
GFLAGS = -fprofile-arcs -ftest-coverage

HEADERS = s21_matrix.h
SRC = $(wildcard functions/*.c auxiliary/*.c)

OBJ := $(patsubst %.c, %.o, $(SRC))

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@



all: s21_matrix.a test gcov_report

s21_matrix.a: $(OBJ)
	@ar rcs s21_matrix.a $(OBJ)
	@ranlib s21_matrix.a
	@rm -rf ./functions/*.o ./auxiliary/*.o
	@echo "Static library created."
	@echo

test: s21_matrix.a
	@$(CC) $(CFLAGS) tests.c s21_matrix.a -o s21_test -lcheck -lsubunit -lm
	@./s21_test
	@echo

gcov_report: s21_matrix.a
	$(CC) $(CFLAGS) $(GFLAGS) tests.c $(SRC) -o report -lcheck -lsubunit -lm
	@./report > /dev/null 2>&1
	@gcov -f *.gcda *.gcno > /dev/null 2>&1
	@lcov -t "gcov_report" -o Coverage_Report.info -c -d . > /dev/null 2>&1
	@genhtml -o ./s21_report Coverage_Report.info > /dev/null 2>&1
	@rm -f *.gcno *.gcda *.info *.gcov report
	@echo "Report created."
	@echo
	@open ./s21_report/index.html

clean:
	@rm -f *.o *.a *.gcno *.gcda *.info *.out *.gcov
	@rm -rf ./s21_test ./s21_report

rebuild: clean all


# Additional functions

clang:
	@clang-format -n -style="{BasedOnStyle: Google}" *.c *.h */*.c
	@clang-format -i -style="{BasedOnStyle: Google}" *.c *.h */*.c

cppcheck:
	@cppcheck --enable=all --suppress=missingIncludeSystem *.c */*.c
	@cppcheck *.h

wvalg:
	@valgrind --tool=memcheck --leak-check=yes  ./s21_test


.PHONY: all test gcov_report clean rebuild 
