CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c11
GFLAGS = -fprofile-arcs -ftest-coverage
SRC = brick_game

all: test


test:
	@$(CC) $(CFLAGS) $(SRC)/tetris.c -lncurses -o s21_tetris 
	@$(SRC)/.s21_tetris

gcov_report:


clean:
	@rm -f *.o *.a *.gcno *.gcda *.info *.out *.gcov
	@rm -rf ./s21_tetris ./s21_report

rebuild: clean all


# Additional functions

clang:
	@clang-format -n -style="{BasedOnStyle: Google}" *.c */*.c *.h */*.h
	@clang-format -i -style="{BasedOnStyle: Google}" *.c */*.c *.h */*.h

cppcheck:
	@cppcheck --enable=all --suppress=missingIncludeSystem *.c */*.c
	@cppcheck *.h */*.h

wvalg:
	@valgrind --tool=memcheck --leak-check=yes  ./s21_tetris


.PHONY: all test gcov_report clean rebuild 