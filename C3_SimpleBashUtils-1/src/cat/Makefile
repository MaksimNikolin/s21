CC = gcc
FLAGS = -Wall -Wextra -Werror -std=c11 -D_POSIX_C_SOURCE=200809L
BUILD = s21_cat.c

all: clean s21_cat

s21_cat:
	$(CC) $(FLAGS) $(BUILD) -o s21_cat

clang:
	clang-format -n *.c *.h
	clang-format -i *.c *.h

rebuild:
	make clean
	make all
	
clean:
	rm -rf s21_cat
	rm -rf *.a *.out *.o
