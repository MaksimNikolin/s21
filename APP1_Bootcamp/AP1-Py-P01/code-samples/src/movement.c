#include "movement.h"
#include <math.h>

#include "walker_consts.h"

void init_player(player_t *player, entity_t *spawn_point)
{
    player_movement_pos_t position = {(float)spawn_point->pos.x, (float)spawn_point->pos.y};
    player->pos = position;
    player->view_distance = DEFAULT_VIEW_DISTANCE;
    player->fov = DEFAULT_FOV;
    player->view_angle = DEFAULT_ANGLE;
}

void player_movement(map_t *map, player_t* player, int key)
{
    if (key == 'w')
    {
        player->pos.x += sinf(player->view_angle) * MOVEMENT_STEP;
        player->pos.y += cosf(player->view_angle) * MOVEMENT_STEP;

        if (map->playground[(int)player->pos.y][(int)player->pos.x] == WALL_CHAR ||
            map->playground[(int)player->pos.y][(int)player->pos.x] == OUTER_AREA_CHAR)
        {
            player->pos.x -= sinf(player->view_angle) * MOVEMENT_STEP;
            player->pos.y -= cosf(player->view_angle) * MOVEMENT_STEP;
        }
    }
    else if (key == 's')
    {
        player->pos.x -= sinf(player->view_angle) * MOVEMENT_STEP;
        player->pos.y -= cosf(player->view_angle) * MOVEMENT_STEP;

        if (map->playground[(int)player->pos.y][(int)player->pos.x] == WALL_CHAR ||
            map->playground[(int)player->pos.y][(int)player->pos.x] == OUTER_AREA_CHAR)
        {
            player->pos.x += sinf(player->view_angle) * MOVEMENT_STEP;
            player->pos.y += cosf(player->view_angle) * MOVEMENT_STEP;
        }
    }
    else if (key == 'a')
        player->view_angle += (TURN_ANGLE_STEP);
    else if (key == 'd')
        player->view_angle -= (TURN_ANGLE_STEP);
}