#include "tetris_interface.h"
#include "../../brick_game/tetris/tetris_logic.h"

void ShowStartScreen() {
  InitGui();
  clear();
  curs_set(0);
  mvprintw(2, 6, "MAIN MENU");
  mvprintw(4, 2, "New Game   ENTER");
  mvprintw(5, 2, "Exit       ESCAPE");
  mvprintw(7, 2, "Left       LEFT");
  mvprintw(8, 2, "Right      RIGHT");
  mvprintw(9, 2, "Down       DOWN");
  mvprintw(10, 2, "Rotate     SPACE");
  mvprintw(11, 2, "Pause      P");
  refresh();
  int ch;
  while (1) {
    ch = getch();
    if (ch == '\n') {
      InitGame();
      break;
    } else if (ch == 27) {
      endwin();
      exit(0);
    }
  }
  clear();
  refresh();
}

void ShowGameOverScreen(int score) {
  clear();
  mvprintw(3, 7, "GAME OVER");
  mvprintw(5, 4, "Final Score:   %d", score);
  mvprintw(9, 4, "New Game   ENTER");
  mvprintw(10, 4, "Exit       ESCAPE");
  refresh();
  int ch;
  while (1) {
    ch = getch();
    if (ch == 27) {
      endwin();
      exit(0);
    } else if (ch == '\n') {
      game.game_over = false;
      InitGame();
      return;
    }
  }
  clear();
  refresh();
}

void InitGui() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  timeout(100);
}

void DrawGame() {
  clear();
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      mvprintw(y, 2*x, game.field[y][x] ? "0" : ".");
    }
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (tetrominos[current_piece.type][current_piece.rotation][i][j]) {
        mvprintw(current_piece.y + i, 2 * current_piece.x + 2 * j, "0");
      }
    }
  }
  mvprintw(1, 2 * WIDTH + 2, "Next:");
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (tetrominos[next_piece.type][next_piece.rotation][i][j]) {
        mvprintw(2 + i, 2 * WIDTH + 2 + j, "0");
        curs_set(0);
      }
    }
  }
  mvprintw(6, 2 * WIDTH + 2, "Level: %d", game.level);
  mvprintw(8, 2 * WIDTH + 2, "Score: %d", game.score);
  mvprintw(10, 2 * WIDTH + 2, "High Score: %d", game.high_score);
  mvprintw(18, 2 * WIDTH + 2, "%s", game.pause ? "Press 'p' to resume" : "");
  refresh();
}

int main() {
  while (1) {
    ShowStartScreen();
    timeout(100 * game.speed);
    while (game.game_over == false) {
        int ch = getch();
        if (ch == 's') UserInput(Start, false);
        else if (ch == 'p') UserInput(Pause, false);
        else if (ch == 27) UserInput(Terminate, false);
        else if (ch == KEY_LEFT) UserInput(Left, false);
        else if (ch == KEY_RIGHT) UserInput(Right, false);
        else if (ch == KEY_DOWN) UserInput(Down, false);
        else if (ch == ' ') UserInput(Action, false);
        else {}
      UpdateCurrentState();
      DrawGame();
    }
    SaveHighScore();
    Cleanup();
    ShowGameOverScreen(game.score);
  }
  return 0;
}
