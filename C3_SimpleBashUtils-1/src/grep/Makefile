CC = gcc
FLAGS = -Wall -Wextra -Werror -std=c11 -D_POSIX_C_SOURCE=200809L
BUILD = s21_grep.c

all: clean s21_grep

s21_grep:
	$(CC) $(FLAGS) $(BUILD) -o s21_grep
	
clang:
	clang-format -n *.c *.h
	clang-format -i *.c *.h

rebuild:
	make clean
	make all

clean:
	rm -rf s21_grep
	rm -rf *.a *.out *.o
