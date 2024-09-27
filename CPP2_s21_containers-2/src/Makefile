COLOR_TITLE = \033[1;36m
COLOR_SUCCESS = \033[1;32m
COLOR_FAIL = \033[0;31m
COLOR_RESET = \033[0m

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
CPPFLAGS = -lstdc++ -std=c++17
LINUX_FLAGS = -lrt -lpthread -lm -lsubunit
GCOV_FLAGS = --coverage
LIBS = -lgtest
SRC = s21_containers/vector
TEST_SRC = unit_tests.cc


OS := $(shell uname -s)
USERNAME=$(shell whoami)

ifeq ($(OS),Linux)
	OPEN_CMD = xdg-open
endif
ifeq ($(OS),Darwin)
	OPEN_CMD = open
endif

.PHONY : all test gcov_report clean rebuild clang cppcheck wvalg contacts

all : clean clang cppcheck wvalg gcov_report contacts


test: 
	@echo "$(COLOR_TITLE)Testing..$(COLOR_RESET)"
ifeq ($(OS), Darwin)
	@$(CC) $(CFLAGS) $(TEST_SRC) -o unit_test $(LIBS) $(CPPFLAGS)
else
	@$(CC) $(CFLAGS) $(TEST_SRC) -o unit_test $(LIBS) $(LINUX_FLAGS) $(CPPFLAGS)
endif
	@./unit_test
	@echo

gcov_report: clean
	@echo "$(COLOR_TITLE)Running report..$(COLOR_RESET)"
ifeq ($(OS), Darwin)
	@$(CC) $(CFLAGS) $(GCOV_FLAGS) $(TEST_SRC) -o gcov_report $(LIBS) $(CPPFLAGS)
else
	@$(CC) $(CFLAGS) $(GCOV_FLAGS) $(TEST_SRC) -o gcov_report $(LIBS) $(LINUX_FLAGS) $(CPPFLAGS)
endif
	@./gcov_report > /dev/null 2>&1
	@lcov -t "stest" -o s21_test.info -c -d ./ --no-external > /dev/null 2>&1
	@genhtml -o report s21_test.info 2>&1 | grep -E "Overall coverage rate:|lines......:|functions..:"
	@$(OPEN_CMD) ./report/index.html > /dev/null 2>&1
	@rm -rf *.gcno *.gcda *.o *.info gcov_report
	@echo "$(COLOR_TITLE)Report opening..$(COLOR_RESET)"
	@echo ""

clean :
	@rm -rf *.o *.a *.gcda *.gcno *.info unit_test gcov_report report

rebuild : clean all


# Additional functions 

clang :
	@echo "$(COLOR_TITLE)Running clang-format..$(COLOR_RESET)"
	@{                                                                                                 \
		clang-format -style="{BasedOnStyle : Google}" -n $(SRC)/* > clang_format_output.txt 2>&1;  \
		if [ -s clang_format_output.txt ]; then                                                    \
			echo "$(COLOR_FAIL)Clang-format made changes$(COLOR_RESET)";                       \
		else                                                                                       \
			echo "$(COLOR_SUCCESS)Clang-format is OK$(COLOR_RESET)";                           \
		fi;                                                                                        \
		rm -f clang_format_output.txt;                                                             \
	}
	@clang-format -style="{BasedOnStyle : Google}" -i $(SRC)/*
	@echo

cppcheck :
	@echo "$(COLOR_TITLE)Running cppcheck..$(COLOR_RESET)"
	@cppcheck --suppress=information --language=c++ $(SRC)/*
	@echo

wvalg : test
	@echo "$(COLOR_TITLE)Running valgrind..$(COLOR_RESET)"
ifeq ($(OS), Darwin)
	@leaks -atExit -- ./unit_test
else
	@valgrind --tool=memcheck --leak-check=full ./unit_test /dev/null 2>&1 | grep -E "ERROR SUMMARY" > valgrind_output.txt 2>&1
	@if grep -q "ERROR SUMMARY: 0" valgrind_output.txt; then                                                                     \
		printf "$(COLOR_SUCCESS)";                                                                                           \
		cat valgrind_output.txt;                                                                                             \
		printf "$(COLOR_RESET)";                                                                                             \
	else                                                                                                                         \
		printf "$(COLOR_FAIL)";                                                                                              \
		cat valgrind_output.txt;                                                                                             \
		printf "$(COLOR_RESET)";                                                                                             \
	fi;                                                                                                                          \
	rm -f valgrind_output.txt
endif
	@echo

contacts :
	@echo "$(COLOR_TITLE)Welcome to our GitHub profiles:$(COLOR_RESET)  https://github.com/eamanzholov  https://github.com/MaksimNikolin  https://github.com/saidkamoldev  https://github.com/TakhirBaylepesov "
