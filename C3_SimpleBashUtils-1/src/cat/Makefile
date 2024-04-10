CC = gcc
FLAGS = -Wall -Wextra -Werror -std=c11
BUILD = s21_cat.c

all: clean s21_cat

s21_cat:
	$(CC) $(FLAGS) $(BUILD) -o s21_cat

rebuild:
	make clean
	make all
	
clean:
	rm -rf s21_cat
	rm -rf *.a *.out *.o

clang:
	clang-format -n *.c *.h
	clang-format -i *.c *.h

wvalg: s21_cat
	valgrind --tool=memcheck --leak-check=yes ./s21_cat

cppcheck: s21_cat
	cppcheck *.h
	cppcheck --enable=all --suppress=missingIncludeSystem *.c

testing:
	rm -rf ./s21_cat
	$(CC) $(FLAGS) s21_cat.c -o ./s21_cat