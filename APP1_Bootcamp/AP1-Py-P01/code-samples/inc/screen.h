#pragma once

#include "generator_objs.h"
#include "generator_consts.h"
#include "walker_objs.h"

cchar_t ch_to_wch(int ch);
void render_screen(map_t *map, player_t *player, screen_t *screen);
void refresh_screen(map_t *map, player_t* player, screen_t *screen);
void clear_screen(screen_t *screen);
void init_ray(ray_t *ray, player_t *player, int render_column_index);
void cast_ray(ray_t *ray, map_t *map, player_t *player);
int check_texture_separator_hit(ray_t *ray, player_t *player);
int compare_vectors(const void *v1, const void *v2);
short select_wall_char(ray_t *ray, player_t *player);
void draw_screen_column(screen_t *screen, int wall_top, int wall_bottom, short wall_char, int x);
void draw_minimap(map_t *map, player_t* player, screen_t *screen);
void screen_print(screen_t* screen);