#include "frontend.h"

#include "../../brick_game/tetris/backend.h"

void InitColors() {
  start_color();
  init_pair(1, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(2, COLOR_CYAN, COLOR_BLACK);
  init_pair(3, COLOR_BLUE, COLOR_BLACK);
  init_pair(4, COLOR_GREEN, COLOR_BLACK);
  init_pair(5, COLOR_WHITE, COLOR_BLACK);
}

void InitGui() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  timeout(100);
}

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

void DrawBorder(int width, int height) {
  for (int x = 0; x < width; x++) {
    mvaddch(0, x, '-');
  }
  for (int x = 0; x < width; x++) {
    mvaddch(height - 1, x, '-');
  }
  for (int y = 1; y < height - 1; y++) {
    mvaddch(y, 0, '|');
    mvaddch(y, width - 1, '|');
  }
  mvaddch(0, 0, '+');
  mvaddch(0, width - 1, '+');
  mvaddch(height - 1, 0, '+');
  mvaddch(height - 1, width - 1, '+');
}

void DrawGame() {
  clear();
  int color_pair;
  if (game.level < 3)
    color_pair = 1;
  else if (game.level == 3 || game.level == 4)
    color_pair = 2;
  else if (game.level == 5 || game.level == 6)
    color_pair = 3;
  else if (game.level == 7 || game.level == 8)
    color_pair = 4;
  else
    color_pair = 5;
  InitColors();

  mvprintw(2, 2 * WIDTH + 4, "Next:");
  attron(COLOR_PAIR(color_pair));
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (tetrominos[next_piece.type][next_piece.rotation][i][j]) {
        mvprintw(3 + i, 2 * (WIDTH + j) + 5, "[");
        mvprintw(3 + i, 2 * (WIDTH + j) + 6, "]");
        curs_set(0);
      }
    }
  }

  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      if (game.field[y][x]) {
        mvprintw(y + 1, 2 * x + 1, "[");
        mvprintw(y + 1, 2 * x + 2, "]");
      } else {
        mvprintw(y + 1, 2 * x + 1, " ");
      }
    }
  }

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (tetrominos[current_piece.type][current_piece.rotation][i][j]) {
        mvprintw(current_piece.y + i + 1, 2 * current_piece.x + 2 * j + 1, "[");
        mvprintw(current_piece.y + i + 1, 2 * current_piece.x + 2 * j + 2, "]");
      }
    }
  }
  attroff(COLOR_PAIR(color_pair));

  mvprintw(8, 2 * WIDTH + 4, "LEVEL: %d", game.level);
  if (game.speed == 1)
    mvprintw(9, 2 * WIDTH + 4, "SPEED: MAX");
  else
    mvprintw(9, 2 * WIDTH + 4, "SPEED: %d", 10 - game.speed);
  mvprintw(10, 2 * WIDTH + 4, "SCORE: %d", game.score);
  mvprintw(12, 2 * WIDTH + 4, "HIGH SCORE:");
  mvprintw(13, 2 * WIDTH + 7, "%d", game.high_score);
  if (game.pause) {
    mvprintw(7, 8, "%s", "       ");
    mvprintw(8, 8, "%s", " PAUSE ");
    mvprintw(9, 8, "%s", "       ");
  }
  refresh();
}

void ShowGameOverScreen(int score) {
  clear();
  mvprintw(3, 9, "GAME OVER");
  if (score > 999)
    mvprintw(5, 5, "Final Score: %d", score);
  else
    mvprintw(5, 5, "Final Score:   %d", score);
  mvprintw(9, 5, "Main menu  ENTER");
  mvprintw(10, 5, "Exit      ESCAPE");
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

int main() {
  while (1) {
    ShowStartScreen();
    timeout(100 * game.speed);
    while (game.game_over == false) {
      DrawBorder(WIDTH * 2 + 2, HEIGHT + 2);
      int ch = getch();
      if (ch == 's')
        UserInput(Start, false);
      else if (ch == 'p')
        UserInput(Pause, false);
      else if (ch == 27)
        UserInput(Terminate, false);
      else if (ch == KEY_LEFT)
        UserInput(Left, false);
      else if (ch == KEY_RIGHT)
        UserInput(Right, false);
      else if (ch == KEY_DOWN)
        UserInput(Down, false);
      else if (ch == ' ')
        UserInput(Action, false);
      else {
      }
      UpdateCurrentState();
      DrawGame();
    }
    SaveHighScore();
    Cleanup();
    ShowGameOverScreen(game.score);
  }
  return 0;
}
