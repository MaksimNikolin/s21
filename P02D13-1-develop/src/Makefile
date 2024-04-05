CC = gcc
FLAGS = -Wall -Wextra -Werror -std=c11
BUILD = s21_game_of_life.c

all: clean s21_game_of_life

s21_game_of_life:
	$(CC) $(FLAGS) $(BUILD) -o s21_game_of_life

clang:
	clang-format -n *.c *.h
	clang-format -i *.c *.h

rebuild:
	make clean
	make all
	
clean:
	rm -rf s21_game_of_life
	rm -rf *.a *.out *.o
	clear
