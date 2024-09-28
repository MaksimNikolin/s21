#include "s21_game_of_life.h"

int board[SIZE_Y][SIZE_X];
int delay = 1000;
int seconds = 0;

void SetSpeed(int s) {
  if (s < 0)
    s = 0;
  delay = (s <= 10) ? 10 : s;
}

void UpdateCounter() { seconds++; }

void RandomInitializeBoard() {
  srand(time(NULL));
  for (int i = 0; i < SIZE_Y; i++) {
    for (int j = 0; j < SIZE_X; j++) {
      board[i][j] = rand() % 2;
    }
  }
}

int CreateMatrix(char *file_arg) {
  FILE *file = fopen(file_arg, "r");
  if (file == NULL) {
    printf("Error\n");
    return 1;
  }
  int rows, cols;
  fscanf(file, "%d %d", &rows, &cols);
  printf("%d %d \n\n", rows, cols);
  for (int i = 0; i < SIZE_Y; i++) {
    for (int j = 0; j < SIZE_X; j++) {
      char var;
      fscanf(file, "%c", &var);
      if (var == CHAR_DEAD) {
        board[i][j] = 0;
      } else if (var == CHAR_ALIVE) {
        board[i][j] = 1;
      } else {
        j--;
        continue;
      }
    }
  }
  return 0;
}

void PrintBoard() {
  printf("\033[0d\033[2J");
  for (int i = 0; i < SIZE_Y; i++) {
    for (int j = 0; j < SIZE_X; j++) {
      printf("%c", board[i][j] ? CHAR_ALIVE : CHAR_DEAD);
    }
    printf("\n");
  }
  printf("\n");
  printf("SPEED UP - press 's+ENTER'\n");
  printf("SPEED DOWN - press 'a+ENTER'\n");
  printf("\nCurrent speed - ");
}

int CountNeighbors(int x, int y) {
  int count = 0;
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      if (i == 0 && j == 0)
        continue;
      int pos_x = (x + i + SIZE_X) % SIZE_X;
      int pos_y = (y + j + SIZE_Y) % SIZE_Y;
      count += board[pos_y][pos_x];
    }
  }
  return count;
}

void UpdateBoard() {
  int next_board[SIZE_Y][SIZE_X];
  for (int i = 0; i < SIZE_Y; i++) {
    for (int j = 0; j < SIZE_X; j++) {
      int neighbors = CountNeighbors(j, i);
      if (board[i][j] == 1) {
        next_board[i][j] = (neighbors == 2 || neighbors == 3) ? 1 : 0;
      } else {
        next_board[i][j] = (neighbors == 3) ? 1 : 0;
      }
    }
  }
  memcpy(board, next_board, sizeof(board));
}

void ChooseYourDestiny(int *choice, char **file) {
  printf("              MAIN MENU\n\n");
  printf("            1.Glaiders\n");
  printf("            2.Achimsp16\n");
  printf("            3.Average\n");
  printf("            4.Angel\n");
  printf("            5.Acorn synth\n");
  printf("            6.Random initialization\n");
  printf("\nChoose your destiny: ");

  if (scanf("%d", choice) == 1 && *choice > 0 && *choice < 7) {
    const char *file_names[] = {
        "patterns/figures1.txt", "patterns/figures2.txt",
        "patterns/figures3.txt", "patterns/figures4.txt",
        "patterns/figures5.txt"};

    if (*choice >= 1 && *choice <= 5) {
      *file = malloc(strlen(file_names[*choice - 1]) + 1);
      strcpy(*file, file_names[*choice - 1]);
      CreateMatrix(*file);
    } else if (*choice == 6)
      RandomInitializeBoard();
  } else
    printf("Incorrect input\n");
}

int main() {

  int running = 1, i;
  size_t bytes_read;
  char read_buffer[READ_SIZE + 1];
  struct epoll_event event, events[MAX_EVENTS];
  int epoll_fd = epoll_create1(0);
  int choice;
  char *file = NULL;

  if (epoll_fd == -1) {
    fprintf(stderr, "Failed to create epoll file descriptor\n");
    return 1;
  }

  event.events = EPOLLIN;
  event.data.fd = 0;

  if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, 0, &event)) {
    fprintf(stderr, "Failed to add file descriptor to epoll\n");
    close(epoll_fd);
    return 1;
  }

  ChooseYourDestiny(&choice, &file);

  while (running) {

    int event_count = epoll_wait(epoll_fd, events, MAX_EVENTS, delay);
    float speed = 1000.0f / (float)delay;

    PrintBoard();
    UpdateBoard();
    UpdateCounter();

    for (i = 0; i < event_count; i++) {
      bytes_read = read(events[i].data.fd, read_buffer, READ_SIZE);
      read_buffer[bytes_read] = '\0';
      if (strncmp(read_buffer, "s\n", 2))
        SetSpeed(delay + 50);
      if (strncmp(read_buffer, "a\n", 2))
        SetSpeed(delay - 50);
      if (!strncmp(read_buffer, "stop\n", 5))
        running = 0;
    }
    printf("%.2f\n", speed);
    printf("Lifetime - %d seconds \n ", seconds);
  }

  free(file);
  return 0;
}
