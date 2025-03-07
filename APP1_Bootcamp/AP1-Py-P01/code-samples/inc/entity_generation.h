#pragma once

#include <stdlib.h>
#include <time.h>
#include "generator_consts.h"
#include "generator_objs.h"

int check_unoccupied(room_t *room, position_t *pos);
void generate_entity_coords(room_t *room, position_t *pos);
void generate_entities(dungeon_t *dungeon);
void generate_player_pos(dungeon_t *dungeon);
void generate_exit(dungeon_t *dungeon);
void generate_enemies(dungeon_t *dungeon);
void generate_enemy(room_t *room, entity_t *enemy);
void generate_items(dungeon_t *dungeon);
void generate_item(room_t *room, entity_t *item);