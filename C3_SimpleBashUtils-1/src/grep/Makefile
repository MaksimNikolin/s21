CC = gcc
FLAGS = -Wall -Wextra -Werror -std=c11

all: clean s21_grep

s21_grep:
	$(CC) $(FLAGS) s21_grep.c -o s21_grep

rebuild:
	make clean
	make all
	
clean:
	rm -rf s21_grep
	rm -rf *.a *.out *.o

clang:
	clang-format -n *.c *.h
	clang-format -i *.c *.h

wvalg: s21_grep
	valgrind --tool=memcheck --leak-check=yes ./s21_grep

cppcheck: s21_grep
	cppcheck *.h
	cppcheck --enable=all --suppress=missingIncludeSystem *.c 
