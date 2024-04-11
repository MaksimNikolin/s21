CC = gcc
CFLAGS = -Wall -Werror -Wextra
C11 = -std=c11

all: rebuild

build: s21_grep

s21_grep:
	$(CC) $(CFLAGS) $(C11) s21_grep.c -o s21_grep

clean:
	rm -rf s21_grep

rebuild: clean build
