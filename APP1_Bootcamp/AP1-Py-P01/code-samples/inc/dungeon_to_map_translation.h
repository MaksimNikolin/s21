#pragma once

#include "generator_consts.h"
#include "generator_objs.h"
#include "dungeon_generation.h"

void dungeon_to_map(dungeon_t *dungeon, map_t *map);
void init_map(map_t *map);
void rooms_to_map(dungeon_t *dungeon, map_t *map);
void rectangle_to_map(position_t *top, position_t *bot, map_t *map);
void fill_rectangle(position_t *top, position_t *bot, map_t *map);
void corridors_to_map(dungeon_t *dungeon, map_t *map);
void draw_horisontal_line(position_t *first_dot, position_t *second_dot, map_t *map);
void draw_vertical_line(position_t *first_dot, position_t *second_dot, map_t *map);