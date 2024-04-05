#ifndef _SRC_GAME_OF_LIFE_H_
#define _SRC_GAME_OF_LIFE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>     // for strncmp
#include <sys/epoll.h>  // for epoll_create1(), epoll_ctl(), struct epoll_event
#include <time.h>
#include <unistd.h>

#define MAX_EVENTS 5
#define READ_SIZE 10

#define SIZE_X 80
#define SIZE_Y 25

#define CHAR_ALIVE '#'
#define CHAR_DEAD '.'

#endif  // _SRC_GAME_OF_LIFE_H_

