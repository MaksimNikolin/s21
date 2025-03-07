#pragma once

#include "generator_consts.h"
#include "generator_objs.h"
#include <stdio.h>

int check_connectivity(dungeon_t *rooms);
int depth_first_search(room_t *cur, int *visited);