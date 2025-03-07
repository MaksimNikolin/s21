#include "screen.h"

#include <math.h>
#include <stdlib.h>

#include "walker_objs.h"
#include "movement.h"

cchar_t ch_to_wch(int ch)
{
    cchar_t wch = {0, {ch}, 0};
    return wch;
}

void render_screen(map_t *map, player_t* player, screen_t *screen)
{
    refresh_screen(map, player, screen);
    draw_minimap(map, player, screen);
}

void refresh_screen(map_t *map, player_t* player, screen_t *screen)
{
    clear_screen(screen);

    for (int x = 0; x < SCRN_W; x++)
    {
        ray_t ray;

        init_ray(&ray, player, x);
        cast_ray(&ray, map, player);

        int wall_top = (float)(SCRN_H/2.0) - SCRN_H / ((float)ray.distance_to_wall); 
        int wall_bottom = SCRN_H - wall_top;
        short wall_char = select_wall_char(&ray, player);

        draw_screen_column(screen, wall_top, wall_bottom, wall_char, x);
    }
}

void clear_screen(screen_t *screen)
{
    for (int i = 0; i < SCRN_H; i++)
        for (int j = 0; j < SCRN_W; j++)
            screen->screen[i][j] = SPACE_CHAR;
}

void init_ray(ray_t *ray, player_t *player, int render_column_index)
{
    ray->cast_angle = (player->view_angle + player->fov / 2.0f) - \
                        ((float)render_column_index / (float)SCRN_W) * player->fov;
    
    ray->distance_to_wall = 0.0f;
    ray->wall_hit = 0;
    ray->cast_angle_sin = sinf(ray->cast_angle);
    ray->cast_angle_cos = cosf(ray->cast_angle);
    ray->texture_separator_hit = 0;
}

void cast_ray(ray_t *ray, map_t *map, player_t *player)
{
    while(!ray->wall_hit && ray->distance_to_wall < player->view_distance)
    {
        ray->distance_to_wall += RAY_CASTING_STEP;

        int next_x = (int)(player->pos.x + ray->cast_angle_sin * ray->distance_to_wall);
        int next_y = (int)(player->pos.y + ray->cast_angle_cos * ray->distance_to_wall);

        if (next_x < 0 || next_x >= MAP_WIDTH || next_y < 0 || next_y >= MAP_HEIGHT)
        {
            ray->wall_hit = 1;
            ray->distance_to_wall = player->view_distance;
        }
        else if (map->playground[next_y][next_x] == WALL_CHAR || map->playground[next_y][next_x] == OUTER_AREA_CHAR)
        {
            ray->wall_hit = 1;
            if (check_texture_separator_hit(ray, player))
                ray->texture_separator_hit = 1;
        }
    }
}

int check_texture_separator_hit(ray_t *ray, player_t *player)
{
    separator_vector_t vectors[4];
    int index = 0;
    int next_x = (int)(player->pos.x + ray->cast_angle_sin * ray->distance_to_wall);
    int next_y = (int)(player->pos.y + ray->cast_angle_cos * ray->distance_to_wall);
    int separator_hit = 0;
    
    for (int separator_x = 0; separator_x < 2; separator_x++)
        for (int separator_y = 0; separator_y < 2; separator_y++)
        {
            float vector_x = (float)next_x + separator_x - player->pos.x;
            float vector_y = (float)next_y + separator_y - player->pos.y;
            float length = sqrt(vector_x * vector_x + vector_y * vector_y);

            vectors[index].length = length;
            vectors[index++].dot_product = (ray->cast_angle_sin * vector_x / length) + (ray->cast_angle_cos * vector_y / length);
        }
    
    qsort((void *)vectors, 4, sizeof(separator_vector_t), compare_vectors);

    if (acos(vectors[0].dot_product) < SEPARATOR_EPS)
        separator_hit = 1;
    if (acos(vectors[1].dot_product) < SEPARATOR_EPS)
        separator_hit = 1;
    
    return separator_hit;
}

int compare_vectors(const void *v1, const void *v2)
{
    return ((separator_vector_t *)v1)->length - ((separator_vector_t *)v2)->length;
}

short select_wall_char(ray_t *ray, player_t *player)
{
    short wall_char;

    if (ray->distance_to_wall <= player->view_distance / NEAR)
        wall_char = NEAR_WALL_CHAR;
    else if (ray->distance_to_wall < player->view_distance / MEDIUM)   
        wall_char = MEDIUM_WALL_CHAR;
    else if (ray->distance_to_wall < player->view_distance / FAR)   
        wall_char = FAR_WALL_CHAR;
    else if (ray->distance_to_wall < player->view_distance)          
        wall_char = FURTHEST_WALL_CHAR;
    else
        wall_char = SPACE_CHAR;

    if (ray->texture_separator_hit)
        wall_char = SEPARATOR_CHAR;
    
    return wall_char;
}

void draw_screen_column(screen_t *screen, int wall_top, int wall_bottom, short wall_char, int x)
{
    for (int y = 0; y < SCRN_H; y++)
    {   
        if (y <= wall_top)
            screen->screen[y][x] = SPACE_CHAR;
        else if(y > wall_top && y <= wall_bottom)
            screen->screen[y][x] = wall_char;
        else
        {
            float gradient = ((float)y - SCRN_H / 2.0) / ((float)SCRN_H / 2.0);
            short floor_char = SPACE_CHAR;

            if (gradient > FLOOR_NEAR)
                floor_char = NEAR_FLOOR_CHAR;
            else if (gradient > FLOOR_MEDIUM)
                floor_char = MEDIUM_FLOOR_CHAR;
            else if (gradient > FLOOR_FAR)
                floor_char = FAR_FLOOR_CHAR;
            else if (gradient > FLOOR_FURTHEST)
                floor_char = FURTHEST_FLOOR_CHAR;

            screen->screen[y][x] = floor_char;
        }
    }
}

void draw_minimap(map_t *map, player_t* player, screen_t *screen)
{
    for (int i = 0; i < MAP_HEIGHT; i++)
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            char cur_char = map->playground[i][j];
            short place_char = SPACE_CHAR;

            if (cur_char == SPACE_CHAR || cur_char == OUTER_AREA_CHAR)
                place_char = SPACE_CHAR;
            else if (cur_char == WALL_CHAR)
                place_char = MINIMAP_WALL_CHAR;
            else if (cur_char == CORRIDOR_CHAR)
                place_char = MINIMAP_CORRIDOR_CHAR;

            screen->screen[i][j] = place_char;
        }

    int player_x = player->pos.x;
    int player_y = player->pos.y;

    screen->screen[player_y][player_x] = MINIMAP_PLAYER_CHAR;
}

void screen_print(screen_t* screen)
{
    for (int i = 0; i < SCRN_H; i++)
        for (int j = 0; j < SCRN_W; j++)
        {
            cchar_t wch = ch_to_wch(screen->screen[i][j]);
            mvadd_wch(i, j, &wch);
        }
}