CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11

# Coverage flags
GFLAGS = -fprofile-arcs -ftest-coverage -lgcov

# Check.h flags
TFLAGS = -lcheck_pic -pthread -lrt -lsubunit -lgcov

# Sanitize flags
AFLAGS = -fsanitize=address -g

TEST_SRC = s21_test.c s21_test_2.c s21_test_3.c s21_sprintf_test.c s21_sscanf_test.c


all: clean test gcov_report

### STATIC LIBRARY
# Static library for Verter
s21_string.a:	
	$(CC) $(CFLAGS) -c s21_string.c -o s21_string.o -lm
	$(CC) $(CFLAGS) -c s21_strerror.c -o s21_strerror.o -lm
	$(CC) $(CFLAGS) -c s21_sprintf.c -o s21_sprintf.o -lm
	$(CC) $(CFLAGS) -c s21_sscanf.c -o s21_sscanf.o -lm
	ar rcs s21_string.a *.o
	ranlib s21_string.a
	rm *.o

# Static library for building tests
s21_test_string.a:
	$(CC) $(CFLAGS) -c s21_string.c -o s21_string.o $(GFLAGS) -lm
	$(CC) $(CFLAGS) -c s21_strerror.c -o s21_strerror.o $(GFLAGS) -lm
	$(CC) $(CFLAGS) -c s21_sprintf.c -o s21_sprintf.o $(GFLAGS) -lm
	$(CC) $(CFLAGS) -c s21_sscanf.c -o s21_sscanf.o $(GFLAGS) -lm
	ar rcs s21_test_string.a *.o
	ranlib s21_test_string.a
	rm *.o

### TESTING
# Testing for Linux
test: s21_test_string.a
	$(CC) $(CFLAGS) $(TEST_SRC) s21_test_string.a -o s21_test $(TFLAGS) -lm
	./s21_test

gcov_report: test
	@pip install gcovr > /dev/null 2>&1
	mkdir -p report
	@gcov *.gcda report/ > /dev/null 2>&1
	mv *.gcov report/ 
	~/.local/bin/gcovr -r . --html --html-details -o report/index.html --gcov-ignore-parse-errors 
	open report/index.html


# Testing for MacOS
test_macos: s21_test_string.a
	$(CC) $(CFLAGS) $(TEST_SRC) s21_test_string.a -o s21_test_macos -lcheck -lm -lpthread
	./s21_test_macos

gcov_report_macos: s21_test_macos
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html


clean:
	rm -rf *.o *.a *.gcno *.gcda *.info report *.gcov s21_test s21_test_macos

rebuild: clean all


# Additional functions
clang:
	clang-format -n -style="{BasedOnStyle: Google}" *.c *.h
	clang-format -i -style="{BasedOnStyle: Google}" *.c *.h

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c
	cppcheck *.h

wvalg:
	valgrind --tool=memcheck --leak-check=yes  ./s21_test