#pragma once

#define  _XOPEN_SOURCE_EXTENDED
#define NCURSES_WIDECHAR 1

#include <curses.h>
#include <locale.h>

#define SCRN_W 450
#define SCRN_H 120

typedef struct screen
{
    short screen[SCRN_H][SCRN_W];
} screen_t;

typedef struct
{
    float x;
    float y;
} player_movement_pos_t;


typedef struct
{
    player_movement_pos_t pos;
    float view_angle;
    float fov;
    float view_distance;
} player_t;

typedef struct
{
    float length;
    float dot_product;
} separator_vector_t;

typedef struct 
{
    float cast_angle;
    float distance_to_wall;
    int wall_hit;
    float cast_angle_sin;
    float cast_angle_cos;
    int texture_separator_hit;
} ray_t;