COLOR_TITLE = \033[1;36m
COLOR_SUCCESS = \033[1;32m
COLOR_FAIL = \033[0;31m
COLOR_RESET = \033[0m

CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -pedantic -Wpedantic -std=c++17 -g
CHECKFLAGS = -lgtest
GCOV = --coverage

OS = $(shell uname)
REPORTDIR = report
HEADERS = s21_matrix_oop.hpp
SRC = $(wildcard functions/*.c auxiliary/*.c)
OBJ = $(patsubst %.c, %.o, $(SRC))

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXLAGS) -c $< -o $@

.PHONY : all s21_matrix_oop.a test gcov_report clean rebuild


all : s21_matrix_oop.a test clang cppcheck wvalg gcov_report contact


s21_matrix_oop.a : $(OBJ)
	@ar rcs s21_matrix_oop.a $(OBJ)
	@ranlib s21_matrix_oop.a
	@rm -rf *.o
	@echo "$(COLOR_TITLE)Static library created.$(COLOR_RESET)"
	@echo

test : s21_matrix_oop.a
	@echo "$(COLOR_TITLE)Testing..$(COLOR_RESET)"
	@$(CXX) $(GCOV) -c s21_matrix_oop.cpp
	@$(CXX) -c test.cpp $(CHECKFLAGS)
	@$(CXX) $(GCOV) -o matrix_test test.o s21_matrix_oop.o $(CHECKFLAGS)
	@./matrix_test
	@rm -rf *.o *.a *.info
	@echo

gcov_report : test
	@echo "$(COLOR_TITLE)Running report..$(COLOR_RESET)"
	@lcov -o s21_matrix_oop.info -c -d . > /dev/null 2>&1
	@genhtml -o $(REPORTDIR) s21_matrix_oop.info 2>&1 | grep -E "Overall coverage rate:|lines......:|functions..:"
	@open ./$(REPORTDIR)/index.html > /dev/null 2>&1
	@rm -rf *.gcno *.gcda *.o *.a *.info matrix_test
	@echo "$(COLOR_TITLE)Report opening..$(COLOR_RESET)"
	@echo ""

clean :
	@rm -rf *.o *.a *.gcno *.gcda *.info matrix_test matrix_oop $(REPORTDIR)

rebuild : clean all


# Additional functions

clang :
	@echo "$(COLOR_TITLE)Running clang-format..$(COLOR_RESET)"
	@{                                                                                                                   \
		clang-format -style="{BasedOnStyle : Google}" -n *.cpp *.h > clang_format_output.txt 2>&1;                 \
		if [ -s clang_format_output.txt ]; then                                                                      \
			echo "$(COLOR_FAIL)Clang-format made changes$(COLOR_RESET)";                                         \
		else                                                                                                         \
			echo "$(COLOR_SUCCESS)Clang-format is OK$(COLOR_RESET)";                                             \
		fi;                                                                                                          \
		rm -f clang_format_output.txt;                                                                               \
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
	@valgrind --tool=memcheck --leak-check=full ./matrix_test /dev/null 2>&1 | grep -E "ERROR SUMMARY" > valgrind_output.txt 2>&1
	@if  grep -q "ERROR SUMMARY: 0" valgrind_output.txt ; then                                                             \
		printf "$(COLOR_SUCCESS)";                                                                                     \
		cat valgrind_output.txt;                                                                                       \
		printf "$(COLOR_RESET)";                                                                                       \
	else                                                                                                                   \
		printf "$(COLOR_FAIL)";                                                                                        \
		cat valgrind_output.txt;                                                                                       \
		printf "$(COLOR_RESET)";                                                                                       \
	fi;                                                                                                                    \
	rm -f valgrind_output.txt;
else
	@leaks -atExit -- ./matrix_test
endif
	@echo

contact :
	@echo "$(COLOR_TITLE)==Welcome to my github: https://github.com/MaksimNikolin==$(COLOR_RESET)"
