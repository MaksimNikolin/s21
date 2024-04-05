#include "s21_game_of_life.h"

void print_logo() {
  printf("*****************************************************************************************\n");
  printf("***     ********* *******   ******    *** ******* *** ********* ******* ******* *********\n");
  printf("*** **** ******* * ******* **** ********** ***** **** * ***** * ****** * ****** *********\n");
  printf("*** ***** ***** *** ****** **** *********** *** ***** ** *** ** ***** *** ***** *********\n");
  printf("*** ***** ***** *** ****** ******  ********* * ****** *** * *** ***** *** ***** *********\n");
  printf("*** ***** ****       ***** ********** ******* ******* **** **** ****       **** *********\n");
  printf("*** **** **** ******* **** ********** ******* ******* ********* *** ******* *** *********\n");
  printf("***     **** ********* **   ***     ********* ******* ********* ** ********* **       ***\n");
  printf("*****************************************************************************************\n");
}

int board[SIZE_Y][SIZE_X];  // GLOBAL VARS!
int speed = 1000;

void setSpeed(int s) {
    speed = s;

    if (s <= 10) speed = 10;
}

void random_initialize_board() {
    srand(time(NULL));
    for (int i = 0; i < SIZE_Y; i++) {
        for (int j = 0; j < SIZE_X; j++) {
            board[i][j] = rand() % 2;
        }
    }
}

int CreateMatrix(char* file_arg) {
    FILE* file = fopen(file_arg, "r");
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

void print_board() {
    printf("\033[0d\033[2J");
    for (int i = 0; i < SIZE_Y; i++) {
        for (int j = 0; j < SIZE_X; j++) {
            printf("%c", board[i][j] ? CHAR_ALIVE : CHAR_DEAD);
        }
        printf("\n");
    }
    printf("\n");
}

int count_neighbors(int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int pos_x = (x + i + SIZE_X) % SIZE_X;
            int pos_y = (y + j + SIZE_Y) % SIZE_Y;
            count += board[pos_y][pos_x];
        }
    }
    return count;
}

void update_board() {
    int next_board[SIZE_Y][SIZE_X];

    for (int i = 0; i < SIZE_Y; i++) {
        for (int j = 0; j < SIZE_X; j++) {
            int neighbors = count_neighbors(j, i);
            // Apply rules
            if (board[i][j] == 1) {
                // Any live cell with fewer than two live neighbors dies, as if by underpopulation.
                // Any live cell with two or three live neighbors lives on to the next generation.
                // Any live cell with more than three live neighbors dies, as if by overpopulation.
                next_board[i][j] = (neighbors == 2 || neighbors == 3) ? 1 : 0;
            } else {
                // Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
                next_board[i][j] = (neighbors == 3) ? 1 : 0;
            }
        }
    }

    // Copy the next_board back to the main board
    memcpy(board, next_board, sizeof(board));
}

int main() {
    print_logo();
    int running = 1, i;
    size_t bytes_read;
    char read_buffer[READ_SIZE + 1];
    struct epoll_event event, events[MAX_EVENTS];
    int epoll_fd = epoll_create1(0);
    int choice;
    char* file;

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

    printf("1.Glaiders\n");  // Different patterns
    printf("2.Achimsp16\n");
    printf("3.Average\n");
    printf("4.Angel\n");
    printf("5.Acorn synth\n");
    printf("6.Random initialization\n");

    printf("Choose your destiny: ");
    if (scanf("%d", &choice) == 1 && choice > 0 && choice < 7) {
        printf("Good choice\n");
    } else {
        printf("Incorrect input\n");
    }

    if (choice == 1) {
        file = "figures1.txt";
        CreateMatrix(file);
    }

    if (choice == 2) {
        file = "figures2.txt";
        CreateMatrix(file);
    }

    if (choice == 3) {
        file = "figures3.txt";
        CreateMatrix(file);
    }

    if (choice == 4) {
        file = "figures4.txt";
        CreateMatrix(file);
    }

    if (choice == 5) {
        file = "figures5.txt";
        CreateMatrix(file);
    }

    if (choice == 6) {
        random_initialize_board();
    }

    while (running) {
        int event_count = epoll_wait(epoll_fd, events, MAX_EVENTS, speed);

        print_board();
        update_board();

        for (i = 0; i < event_count; i++) {
            // printf("Reading file descriptor '%d' -- ", events[i].data.fd);
            bytes_read = read(events[i].data.fd, read_buffer, READ_SIZE);
            // printf("%zd bytes read.\n", bytes_read);
            read_buffer[bytes_read] = '\0';
            // printf("Read '%s'\n", read_buffer);

            if (strncmp(read_buffer, "s\n", 2)) setSpeed(speed + 50);
            if (strncmp(read_buffer, "a\n", 2)) setSpeed(speed - 50);

            if (!strncmp(read_buffer, "stop\n", 5)) running = 0;
        }
        printf("%d\n", speed);
    }

    return 0;
}
