#ifndef SRC_BRICK_GAME_TETRIS_BACKEND_H
#define SRC_BRICK_GAME_TETRIS_BACKEND_H

#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "../../gui/cli/frontend.h"

#define HIGHSCORE_FILE "high_scores.txt"
#define WIDTH 10
#define HEIGHT 20
#define SIDEBAR_WIDTH 20
#define NUM_PIECES 7
#define PIECE_SIZE 4

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
  bool game_over;
} GameInfo_t;

typedef struct {
  int x, y;
  int rotation;
  int type;
} Piece;

typedef struct {
  int type;
  int rotation;
} NextPiece_t;

extern const int tetrominos[NUM_PIECES][4][4][4];
extern GameInfo_t game;
extern Piece current_piece;
extern NextPiece_t next_piece;

void LoadHighScore();
void SaveHighScore();
void InitGame();
void UserInput(UserAction_t action, bool hold);
GameInfo_t UpdateCurrentState();
void Cleanup();
void NewPiece();
bool CheckCollision(int x, int y, int rotation);
void PlacePiece();
void ClearLines();
void RotatePiece();
void MovePiece(int dx, int dy);
void DropPiece();
void SpawnNewPiece();

#endif  // SRC_BRICK_GAME_TETRIS_BACKEND_H
