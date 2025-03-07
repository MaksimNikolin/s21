#pragma once

#include "generator_consts.h"
#include "generator_objs.h"
#include <stdio.h>
#include <ncurses.h>

void print_map(map_t *map);

void print_dungeon_generated(int y);
void print_entities_generated(int y);
void print_map_created(int y);
void print_connectivity_check_result(int check_result, int y);
void print_entity_pools(int y);