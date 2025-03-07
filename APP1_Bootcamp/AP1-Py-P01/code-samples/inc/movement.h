#pragma once

#include "walker_consts.h"
#include "walker_objs.h"
#include "generator_objs.h"

void init_player(player_t *player, entity_t* spawn_point);
void player_movement(map_t *map, player_t* player, int key);