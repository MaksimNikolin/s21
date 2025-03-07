#pragma once

#include "generator_consts.h"
#include "generator_objs.h"
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>

void generate_dungeon(dungeon_t *dungeon);
void init_dungeon(dungeon_t *dungeon);
void generate_sectors(dungeon_t *dungeon);
int room_placement_comparator(const void *r1, const void *r2);
void generate_connections(dungeon_t *dungeon);
void generate_primary_connections(dungeon_t *dungeon);
void generate_secondary_connections(dungeon_t *dungeon);
void generate_rooms_geometry(dungeon_t *dungeon);
void generate_corners(room_t *room, int offset_y, int offset_x);
void generate_doors(room_t *room);
void generate_corridors_geometry(dungeon_t *dungeon);
int max(int first_num, int second_num);
int min(int first_num, int second_num);
void generate_left_to_right_corridor(dungeon_t *dungeon, room_t *left_room, room_t *right_room, corridor_t *corridor);
void generate_left_turn_corridor(dungeon_t *dungeon, room_t *top_room, room_t *bottom_left_room, corridor_t *corridor);
void generate_right_turn_corridor(dungeon_t *dungeon, room_t *top_room, room_t *bottom_right_room, corridor_t *corridor);
void generate_top_to_bottom_corridor(dungeon_t *dungeon, room_t *top_room, room_t *bottom_room, corridor_t *corridor);