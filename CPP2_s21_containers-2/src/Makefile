COLOR_TITLE = \033[1;36m
COLOR_SUCCESS = \033[1;32m
COLOR_FAIL = \033[0;31m
COLOR_RESET = \033[0m

CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -pedantic -std=c++17 -g
LINUX_FLAGS = -lrt -lpthread -lm -lsubunit
CHECKFLAGS = -lgtest
GCOVFLAGS = --coverage

REPORTDIR = report
HEADERS = s21_containers.h
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

all : test clang cppcheck wvalg gcov_report contacts

test: 
	@echo "$(COLOR_TITLE)Testing..$(COLOR_RESET)"
	@$(CXX) $(CXXFLAGS) $(CHECKFLAGS) $(TEST_SRC) -o unit_test $(LINUX_FLAGS)
	./unit_test
	@rm -f unit_test
	@echo

gcov_report: clean
	@echo "$(COLOR_TITLE)Running report..$(COLOR_RESET)"
	@$(CXX) $(CXXFLAGS) $(GCOVFLAGS) $(CHECKFLAGS) $(TEST_SRC) -o gcov_report $(LINUX_FLAGS)
	@./gcov_report
	@lcov -t "stest" -o s21_test.info -c -d . > /dev/null 2>&1
	@genhtml -o report s21_test.info 2>&1 | grep -E "Overall coverage rate:|lines......:|functions..:"
	@$(OPEN_CMD) ./report/index.html > /dev/null 2>&1
	@rm -rf *.gcno *.gcda *.o *.info gcov_report
	@echo "$(COLOR_TITLE)Report opening..$(COLOR_RESET)"
	@echo ""

clean :
	@rm -rf *.o *.a *.gcda *.gcno *.info unit_test report gcov_report valgrind_test *.dSYM

rebuild : clean all

clang :
	@echo "$(COLOR_TITLE)Running clang-format..$(COLOR_RESET)"
	@{ \
		clang-format -style="{BasedOnStyle : Google}" -n *.cpp *.h > clang_format_output.txt 2>&1; \
		if [ -s clang_format_output.txt ]; then \
			echo "$(COLOR_FAIL)Clang-format made changes$(COLOR_RESET)"; \
		else \
			echo "$(COLOR_SUCCESS)Clang-format is OK$(COLOR_RESET)"; \
		fi; \
		rm -f clang_format_output.txt; \
	}
	@clang-format -style="{BasedOnStyle : Google}" -i *.cpp *.h
	@echo

cppcheck :
	@echo "$(COLOR_TITLE)Running cppcheck..$(COLOR_RESET)"
	@cppcheck --suppress=information --language=c++ *.cpp *.h
	@echo

wvalg : test
	@echo "$(COLOR_TITLE)Running valgrind..$(COLOR_RESET)"
ifeq ($(OS),Linux)
	@valgrind --tool=memcheck --leak-check=full ./unit_test /dev/null 2>&1 | grep -E "ERROR SUMMARY" > valgrind_output.txt 2>&1
	@if grep -q "ERROR SUMMARY: 0" valgrind_output.txt; then \
		printf "$(COLOR_SUCCESS)"; \
		cat valgrind_output.txt; \
		printf "$(COLOR_RESET)"; \
	else \
		printf "$(COLOR_FAIL)"; \
		cat valgrind_output.txt; \
		printf "$(COLOR_RESET)"; \
	fi; \
	rm -f valgrind_output.txt;
else
	@leaks -atExit -- ./unit_test
endif
	@echo

contacts :
	@echo "$(COLOR_TITLE)==Welcome to our github profiles: \
		https://github.com/MaksimNikolin==$(COLOR_RESET) \
		https://github.com/eamanzholov==$(COLOR_RESET) \
		https://github.com/SaidKamol==$(COLOR_RESET)"
