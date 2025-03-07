#pragma once

#define UNINITIALIZED   -1

#define CONNECTED       0
#define NOT_CONNECTED   1

#define MAP_HEIGHT  30
#define MAP_WIDTH   90

#define ROOMS_PER_SIDE  3

#define MAX_ROOMS_NUMBER        ROOMS_PER_SIDE * ROOMS_PER_SIDE
#define MAX_CORRIDORS_NUMBER    12

#define SECTOR_HEIGHT   MAP_HEIGHT / ROOMS_PER_SIDE
#define SECTOR_WIDTH    MAP_WIDTH / ROOMS_PER_SIDE

#define CORNER_VERT_RANGE   (SECTOR_HEIGHT - 6) / 2
#define CORNER_HOR_RANGE    (SECTOR_WIDTH - 6) / 2

#define ROOM_CHANCE         0.5
#define SPAWN_SET_CHANCE    0.5

#define MAX_ENEMIES_PER_ROOM    5
#define MAX_ITEMS_PER_ROOM      3
#define MAX_ENTITIES_PER_ROOM   MAX_ENEMIES_PER_ROOM + MAX_ITEMS_PER_ROOM + 2
#define MAX_ENEMIES_TOTAL       MAX_ENEMIES_PER_ROOM * ROOMS_PER_SIDE * ROOMS_PER_SIDE
#define MAX_ITEMS_TOTAL         MAX_ITEMS_PER_ROOM * ROOMS_PER_SIDE * ROOMS_PER_SIDE
#define MAX_ENTITIES_TOTAL      MAX_ENEMIES_TOTAL + MAX_ITEMS_TOTAL + 2
#define ENEMY_POOL_LEN          26
#define ITEM_POOL_LEN           5

#define TOP     0
#define RIGHT   1
#define BOTTOM  2
#define LEFT    3

#define LEFT_TO_RIGHT_CORRIDOR  0
#define LEFT_TURN_CORRIDOR      1
#define RIGHT_TURN_CORRIDOR     2
#define TOP_TO_BOTTOM_CORRIDOR  3

#define UNOCCUPIED  0
#define OCCUPIED    1

#define PLAYER      0
#define PLAYER_CHAR '@'
#define EXIT        1
#define EXIT_CHAR   '|'
#define ENEMY       2
#define ITEM        3

#define WALL_CHAR       '#'
#define CORRIDOR_CHAR   '+'
#define OUTER_AREA_CHAR '.'
#define INNER_AREA_CHAR ' '
#define EMPTY_CHAR      ' '

#define IS_OUTER    0
#define IS_INNER    1
#define IS_WALL     2