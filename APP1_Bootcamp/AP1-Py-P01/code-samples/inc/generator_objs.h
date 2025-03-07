#pragma once

#include "generator_consts.h"

typedef struct
{
    int x;
    int y;
} position_t;

typedef struct
{
    int type;
    int symbol;
    position_t pos;
} entity_t;

typedef struct
{
    char playground[MAP_HEIGHT][MAP_WIDTH];
    entity_t player_spawn;
    entity_t exit;
    entity_t items[MAX_ENEMIES_TOTAL];
    int items_cnt;
    entity_t enemies[MAX_ITEMS_TOTAL];
    int enemies_cnt;
} map_t;

typedef struct room
{
    int sector;
    int grid_i;
    int grid_j;
    position_t top_left;
    position_t bot_right;
    position_t doors[4]; 
    struct room *connections[4];
    entity_t entities[MAX_ENTITIES_PER_ROOM];
    int entities_cnt;
} room_t;

typedef struct
{
    int type;
    position_t points[4];
    int points_cnt;
} corridor_t;

typedef struct
{
    int room_cnt;
    int corridors_cnt;
    room_t rooms[ROOMS_PER_SIDE + 2][ROOMS_PER_SIDE + 2];
    room_t *sequence[MAX_ROOMS_NUMBER];
    corridor_t corridors[MAX_CORRIDORS_NUMBER];
} dungeon_t;