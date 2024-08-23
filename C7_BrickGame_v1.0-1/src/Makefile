SRC_DIR := src
TETRIS_DIR := brick_game/tetris
GUI_DIR := gui/cli
TESTS_DIR := tests
BUILD_DIR := build

OS := $(shell uname -o)

ifeq ($(OS), GNU/Linux)
    TEST_FLAGS = -lcheck -lm -lpthread -lrt -lsubunit
else
    TEST_FLAGS = -lcheck -lm -lpthread
endif

CC := gcc
CFLAGS := -Wall -Werror -Wextra -std=c11
LDFLAGS := -lncurses
GCOV_FLAGS := -fprofile-arcs -ftest-coverage
SOURCES := $(TETRIS_DIR)/backend.c $(GUI_DIR)/frontend.c
OBJECTS := $(TETRIS_DIR)/*.o $(GUI_DIR)/*.o
DIST_SOURCES := $(TETRIS_DIR)/* $(GUI_DIR)/* tests/* doc/* *.txt Makefile

.PHONY: all install uninstall rebuild clean dvi dist test gcov_report


all: clean install
	@./$(BUILD_DIR)/tetris
	@echo "Gaming..."


install:
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(SOURCES) -o $(BUILD_DIR)/tetris $(LDFLAGS) $(CFLAGS)
	@echo "Installed"

uninstall:
	@rm -rf $(BUILD_DIR) $(OBJECTS)

rebuild : uninstall install


clean:
	@rm -rf $(BUILD_DIR) $(OBJECTS) *.info gcov_report score.txt tetris.tar.gz

dvi:
	@open doc/index.html > /dev/null 2>&1
	@echo "Documentation opening..."

dist: clean
	@tar -czf tetris.tar.gz $(DIST_SOURCES) > /dev/null 2>&1
	@echo "Archive created"


test:
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(TETRIS_DIR)/backend.c $(TESTS_DIR)/*.c -o $(BUILD_DIR)/tetris $(LDFLAGS) $(CFLAGS) $(TEST_FLAGS)
	@./build/tetris

gcov_report: clean
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(TETRIS_DIR)/backend.c $(TESTS_DIR)/*.c -o $(BUILD_DIR)/tetris $(LDFLAGS) $(CFLAGS) $(TEST_FLAGS) $(GCOV_FLAGS)
	@./build/tetris > /dev/null 2>&1
	@lcov -t "$(TETRIS_DIR)/backend.c" -o tetris.a.info -c -d . > /dev/null 2>&1
	@lcov --extract tetris.a.info '*/backend.c' -o filtered.info > /dev/null 2>&1
	@genhtml -o gcov_report filtered.info 2>&1 | grep -E "Overall coverage rate:|lines......:|functions..:"
	@open gcov_report/index.html > /dev/null 2>&1
	@rm -rf *.gcno *.gcda
	@echo "Report opening..."


# Additional functions

clang :
	@echo "Running clang-format..."
	@{                                                                                                                   \
		clang-format -style="{BasedOnStyle : Google}" -n */*.c */*/*.c */*/*.h > clang_format_output.txt 2>&1;           \
		if [ -s clang_format_output.txt ]; then                                                                          \
			echo "Clang-format made changes";                                                                            \
		else                                                                                                             \
			echo "Clang-format is OK";                                                                                   \
		fi;                                                                                                              \
		rm -f clang_format_output.txt;                                                                                   \
		}
	@clang-format -style="{BasedOnStyle : Google}" -i */*.c */*/*.c */*/*.h
	
wvalg : clean install
	@valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all -s --track-origins=yes $(BUILD_DIR)/tetris
