#include "tetris.h"

Shape CopyShape(Shape shape) {
  Shape new_shape = shape;
  char **copyshape = shape.array;
  new_shape.array = (char **)malloc(new_shape.width * sizeof(char *));
  int i, j;
  for (i = 0; i < new_shape.width; i++) {
    new_shape.array[i] = (char *)malloc(new_shape.width * sizeof(char));
    for (j = 0; j < new_shape.width; j++) {
      new_shape.array[i][j] = copyshape[i][j];
    }
  }
  return new_shape;
}

void DeleteShape(Shape shape) {
  int i;
  for (i = 0; i < shape.width; i++)
    free(shape.array[i]);
  free(shape.array);
}

int CheckPosition(Shape shape) {
  char **array = shape.array;
  int i, j;
  for (i = 0; i < shape.width; i++) {
    for (j = 0; j < shape.width; j++) {
      if ((shape.col + j < 0 || shape.col + j >= COLS ||
           shape.row + i >= ROWS)) {
        if (array[i][j])
          return FALSE;
      } else if (Table[shape.row + i][shape.col + j] && array[i][j])
        return FALSE;
    }
  }
  return TRUE;
}

void GetNewShape() {
  Shape new_shape = CopyShape(ShapesArray[rand() % 7]);
  new_shape.col = (COLS - new_shape.width) / 2;
  new_shape.row = 0;
  DeleteShape(current);
  current = new_shape;
  if (!CheckPosition(current))
    PlayMode = FALSE;
}

void RotateShape(Shape *shape) {
  Shape temp = CopyShape(*shape);
  int i, j, k, width;
  width = shape->width;
  for (i = 0; i < width; i++) {
    for (j = 0, k = width - 1; j < width; j++, k--) {
      shape->array[i][j] = temp.array[k][i];
    }
  }
  DeleteShape(temp);
}

void WriteToTable() {
  int i, j;
  for (i = 0; i < current.width; i++) {
    for (j = 0; j < current.width; j++) {
      if (current.array[i][j])
        Table[current.row + i][current.col + j] = current.array[i][j];
    }
  }
}

void LineCleanup() {
  int i, j, count = 0;
  int score_per_line[] = SCORE_FOR_LINES;
  int lines_to_remove[ROWS] = {0};
  for (i = 0; i < ROWS; i++) {
    int sum = 0;
    for (j = 0; j < COLS; j++)
      sum += Table[i][j];
    if (sum == COLS)
      lines_to_remove[count++] = i;
  }
  for (i = 0; i < count; i++) {
    int line_to_remove = lines_to_remove[i];
    for (j = line_to_remove; j >= 1; j--) {
      for (int l = 0; l < COLS; l++)
        Table[j][l] = Table[j - 1][l];
    }
    for (j = 0; j < COLS; j++)
      Table[0][j] = 0;
  }
  int total_score = 0;
  if (count < sizeof(score_per_line) / sizeof(score_per_line[0]))
    total_score = score_per_line[count];
  else
    total_score =
        score_per_line[sizeof(score_per_line) / sizeof(score_per_line[0]) - 1];
  timer -= 1000, score += total_score;
}

void PrintTable() {
  char Buffer[ROWS][COLS] = {0};
  int i, j;
  for (i = 0; i < current.width; i++) {
    for (j = 0; j < current.width; j++) {
      if (current.array[i][j])
        Buffer[current.row + i][current.col + j] = current.array[i][j];
    }
  }
  clear();
  for (i = 0; i < ROWS; i++) {
    for (j = 0; j < COLS; j++) {
      printw("%c ", (Table[i][j] + Buffer[i][j]) ? 'O' : '.');
    }
    printw("\n");
  }
  printw("\nScore: %d\n", score);

//   FILE *file = fopen(RESULTS_FILE, "r");
//     if (file == NULL) {
//         perror("Error opening file");
//         return;
//     }
//   HighScore highScore = {"No record", 0};
//     HighScore current;
//         while (fscanf(file, "Player: %99[^,], Score: %d\n", current.name, &current.score) == 2) {
//         if (current.score > highScore.score) {
//             highScore = current;
//         }
//     }
//   mvprintw(0, 22, "\nHigh score: %d\n", highScore.score);
}

void StartCountdown() {
  initscr();
  noecho();
  cbreak();
  curs_set(FALSE);
  const char *countdown_frames[4] = {
      "Go\n",
      "  *\n        **\n         *\n         *\n         *\n",
      "***\n         *\n       ***\n       *  \n       ***\n",
      "***\n         *\n       ***\n         *\n       ***\n",
  };
  for (int i = 3; i >= 0; i--) {
    clear();
    mvprintw(LINES / 2 - 10, COLS / 2 + 2, "%s", countdown_frames[i]);
    refresh();
    sleep(1);
  }
  endwin();
}

void ManipulateCurrent(int action) {
  Shape temp = CopyShape(current);
  if (action == 's') {
    temp.row++;
    if (CheckPosition(temp))
      current.row++;
    else {
      WriteToTable();
      LineCleanup();
      GetNewShape();
    }
  } else if (action == 'd') {
    temp.col++;
    if (CheckPosition(temp))
      current.col++;
  } else if (action == 'a') {
    temp.col--;
    if (CheckPosition(temp))
      current.col--;
  } else if (action == 'w') {
    RotateShape(&temp);
    if (CheckPosition(temp))
      RotateShape(&current);
  }
  DeleteShape(temp);
  PrintTable();
}

void RandomInitializeTable() {
  srand(time(NULL));
  if (choice == 2) {
    for (int i = 0; i < COLS; i++) {
      for (int j = ROWS - 3; j < ROWS; j++)
        Table[j][i] = rand() % 2;
    }
  }
  if (choice == 3) {
    for (int i = 0; i < COLS; i++) {
      for (int j = ROWS - 6; j < ROWS; j++)
        Table[j][i] = rand() % 2;
    }
  }
}

void SaveResultToFile(const char *playerName, int score) {
  FILE *file = fopen(RESULTS_FILE, "a");
  if (file == NULL) {
    perror("Error opening file");
    return;
  }
  fprintf(file, "Player: %s, Score: %d\n", playerName, score);
  fclose(file);
}

void ChooseYourDestiny() {
  printf("*********************************************************************"
         "********************\n");
  printf("***     ********* *******   ******    *** ******* *** ********* "
         "******* ******* *********\n");
  printf("*** **** ******* * ******* **** ********** ***** **** * ***** * "
         "****** * ****** *********\n");
  printf("*** ***** ***** *** ****** **** *********** *** ***** ** *** ** "
         "***** *** ***** *********\n");
  printf("*** ***** ***** *** ****** ******  ********* * ****** *** * *** "
         "***** *** ***** *********\n");
  printf("*** ***** ****       ***** ********** ******* ******* **** **** **** "
         "      **** *********\n");
  printf("*** **** **** ******* **** ********** ******* ******* ********* *** "
         "******* *** *********\n");
  printf("***     **** ********* **   ***     ********* ******* ********* ** "
         "********* **       ***\n");
  printf("*********************************************************************"
         "********************\n");
  printf("\n");
  printf("1. Full_clean\n");
  printf("2. 3_lines_filled\n");
  printf("3. 6_lines_filled\n");
  printf("4. Quit\n");
  printf("\n");
  printf("Choose your destiny: ");
  if (scanf("%d", &choice) == 1 && choice > 0 && choice < 4)
    StartCountdown();
  else
    exit(0);
  if (choice == 1)
    PrintTable();
  if (choice == 2 || choice == 3) {
    RandomInitializeTable();
    PrintTable();
  }
}

void PrintTableGameOver() {
  clear();
  mvprintw(4, 1, "=============");
  mvprintw(5, 1, "| GAME OVER |");
  mvprintw(6, 1, "=============");
  mvprintw(8, 3, "  _____");
  mvprintw(9, 3, " /     \\");
  mvprintw(10, 3, "|  O O  |");
  mvprintw(11, 3, "|   >   |");
  mvprintw(12, 3, "|  / \\  |");
  mvprintw(13, 3, " \\_____/");
  refresh();
  sleep(3);
}

void EnterYourName() { // ????
  clear();
  mvprintw(LINES - 2, 1, "Enter your name: ");
  refresh();
  char playerName[MAX_NAME_LENGTH];
  echo();
  curs_set(TRUE);
  mvwgetnstr(stdscr, LINES - 1, 1, playerName, MAX_NAME_LENGTH - 1);
  noecho();
  curs_set(FALSE);
  SaveResultToFile(playerName, score);
  sleep(1);
}

void UpdateGameSpeed(int score) {
  for (int i = MAX_LEVELS - 1; i >= 0; i--) {
    if (score >= score_thresholds[i]) {
      timer = INITIAL_TIMER - timer_decreases[i];
      break;
    }
  }
}

void PlayGame() {
  struct timeval before, after;
  gettimeofday(&before, NULL);
  nodelay(stdscr, TRUE);
  GetNewShape();
  PrintTable();
  while (PlayMode) {
    UpdateGameSpeed(score);
    
    char c;
    if ((c = getch()) != ERR) {
      if (c == 'q') {
        PlayMode = 0;
        endwin();
        exit(0);
      }
      if (c == 'p') {
        paused = !paused;
        if (paused) {
          mvprintw(20, 0, "Paused. Press 'p' to resume.");
          refresh();
        }
        continue;
      }
      if (!paused)
        ManipulateCurrent(c);
    }
    if (!paused) {
      gettimeofday(&after, NULL);
      double elapsed =
          ((double)after.tv_sec * 1000000 + (double)after.tv_usec) -
          ((double)before.tv_sec * 1000000 + (double)before.tv_usec);
      if (elapsed > timer) {
        before = after;
        ManipulateCurrent('s');
      }
    }
  }
}

int main() {
  ChooseYourDestiny();
  srand(time(0));
  initscr();
  PlayGame();
  PrintTableGameOver();
  EnterYourName();
  DeleteShape(current);
  endwin();
  return 0;
}