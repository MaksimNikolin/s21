#ifndef SRC_BRICK_GAME_TETRIS_H_
#define SRC_BRICK_GAME_TETRIS_H_

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#define ROWS 20
#define COLS 10
#define TRUE 1
#define FALSE 0
#define MAX_LEVELS 10
#define INITIAL_TIMER 550000
#define TIMER_DECREASE 50000
#define SCORE_TRESHOLD 600
#define SCORE_FOR_LINES                                                        \
  { 0, 100, 300, 700, 1500 }
#define MAX_NAME_LENGTH 100
#define RESULTS_FILE "game_results.txt"

int timer = INITIAL_TIMER;
int PlayMode = TRUE;
int paused = FALSE;
int score = FALSE;
int choice;

char Table[ROWS][COLS] = {0};

typedef struct {
  char **array;
  int width, row, col;
} Shape;

Shape current;

const Shape ShapesArray[7] = {
    {(char *[]){(char[]){0, 1, 1}, (char[]){1, 1, 0}, (char[]){0, 0, 0}}, 3},
    {(char *[]){(char[]){1, 1, 0}, (char[]){0, 1, 1}, (char[]){0, 0, 0}}, 3},
    {(char *[]){(char[]){0, 1, 0}, (char[]){1, 1, 1}, (char[]){0, 0, 0}}, 3},
    {(char *[]){(char[]){0, 0, 1}, (char[]){1, 1, 1}, (char[]){0, 0, 0}}, 3},
    {(char *[]){(char[]){1, 0, 0}, (char[]){1, 1, 1}, (char[]){0, 0, 0}}, 3},
    {(char *[]){(char[]){1, 1}, (char[]){1, 1}}, 2},
    {(char *[]){(char[]){0, 0, 0, 0}, (char[]){1, 1, 1, 1},
                (char[]){0, 0, 0, 0}, (char[]){0, 0, 0, 0}},
     4},
};

const int score_thresholds[MAX_LEVELS] = {
    SCORE_TRESHOLD * 1,  SCORE_TRESHOLD * 2, SCORE_TRESHOLD * 3,
    SCORE_TRESHOLD * 4,  SCORE_TRESHOLD * 5, SCORE_TRESHOLD * 6,
    SCORE_TRESHOLD * 7,  SCORE_TRESHOLD * 8, SCORE_TRESHOLD * 9,
    SCORE_TRESHOLD * 10,
};

const int timer_decreases[MAX_LEVELS] = {
    TIMER_DECREASE * 1,  TIMER_DECREASE * 2, TIMER_DECREASE * 3,
    TIMER_DECREASE * 4,  TIMER_DECREASE * 5, TIMER_DECREASE * 6,
    TIMER_DECREASE * 7,  TIMER_DECREASE * 8, TIMER_DECREASE * 9,
    TIMER_DECREASE * 10,
};

typedef struct {
    char name[100];
    int score;
} HighScore;

#endif // SRC_BRICK_GAME_TETRIS_H_
