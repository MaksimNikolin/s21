#include "dungeon_to_map_translation.h"

void dungeon_to_map(dungeon_t *dungeon, map_t *map)
{
    init_map(map);
    rooms_to_map(dungeon, map);
    corridors_to_map(dungeon, map);
}

void init_map(map_t *map)
{
    for (int i = 0; i < MAP_HEIGHT; i++)
        for (int j = 0; j < MAP_WIDTH; j++)
            map->playground[i][j] = OUTER_AREA_CHAR;
    
    map->enemies_cnt = 0;
    map->items_cnt = 0;
}

void rooms_to_map(dungeon_t *dungeon, map_t *map)
{
    for (int i = 0; i < dungeon->room_cnt; i++)
    {
        position_t top_room_corner = dungeon->sequence[i]->top_left;
        position_t bot_room_corner = dungeon->sequence[i]->bot_right;

        rectangle_to_map(&top_room_corner, &bot_room_corner, map);
        fill_rectangle(&top_room_corner, &bot_room_corner, map);

        for (int j = 0; j < dungeon->sequence[i]->entities_cnt; j++)
        {
            entity_t cur_entity = dungeon->sequence[i]->entities[j];

            switch (cur_entity.type)
            {
                case PLAYER:
                    map->player_spawn = cur_entity;
                    break;
                case EXIT:
                    map->exit = cur_entity;
                    break;
                case ENEMY:
                    map->enemies[map->enemies_cnt++] = cur_entity;
                    break;
                case ITEM:
                    map->items[map->items_cnt++] = cur_entity;
                    break;
            }

            map->playground[(int)cur_entity.pos.y][(int)cur_entity.pos.x] = cur_entity.symbol; 
        }
    }
}

void rectangle_to_map(position_t *top, position_t *bot, map_t *map)
{
    map->playground[(int)top->y][(int)top->x] = WALL_CHAR;

    int i = top->x + 1;

    for (;i < bot->x; i++)
        map->playground[top->y][i] = WALL_CHAR;
    map->playground[top->y][i] = WALL_CHAR;

    for (int i = top->y + 1; i < bot->y; i++)
    {
        map->playground[i][top->x] = WALL_CHAR;
        map->playground[i][bot->x] = WALL_CHAR;
    }

    map->playground[bot->y][top->x] = WALL_CHAR;
    i = top->x + 1;
    for (;i < bot->x; i++)
        map->playground[bot->y][i] = WALL_CHAR;
    map->playground[bot->y][i] = WALL_CHAR;
}

void fill_rectangle(position_t *top, position_t *bot, map_t *map)
{
    for (int i = top->y + 1; i < bot->y; i++)
        for (int j = top->x + 1; j < bot->x; j++)
            map->playground[i][j] = INNER_AREA_CHAR;
}

void corridors_to_map(dungeon_t *dungeon, map_t *map)
{
    for (int i = 0; i < dungeon->corridors_cnt; i++)
    {
        switch (dungeon->corridors[i].type)
        {
            case LEFT_TO_RIGHT_CORRIDOR:
                draw_horisontal_line(&dungeon->corridors[i].points[0], &dungeon->corridors[i].points[1], map);
                draw_vertical_line(&dungeon->corridors[i].points[1], &dungeon->corridors[i].points[2], map);
                draw_horisontal_line(&dungeon->corridors[i].points[2], &dungeon->corridors[i].points[3], map);
                break;
            case LEFT_TURN_CORRIDOR:
                draw_vertical_line(&dungeon->corridors[i].points[0], &dungeon->corridors[i].points[1], map);
                draw_horisontal_line(&dungeon->corridors[i].points[1], &dungeon->corridors[i].points[2], map);
                break;
            case RIGHT_TURN_CORRIDOR:
                draw_vertical_line(&dungeon->corridors[i].points[0], &dungeon->corridors[i].points[1], map);
                draw_horisontal_line(&dungeon->corridors[i].points[1], &dungeon->corridors[i].points[2], map);
                break;
            case TOP_TO_BOTTOM_CORRIDOR:
                draw_vertical_line(&dungeon->corridors[i].points[0], &dungeon->corridors[i].points[1], map);
                draw_horisontal_line(&dungeon->corridors[i].points[1], &dungeon->corridors[i].points[2], map);
                draw_vertical_line(&dungeon->corridors[i].points[2], &dungeon->corridors[i].points[3], map);
                break;
        }
    }
}

void draw_horisontal_line(position_t *first_dot, position_t *second_dot, map_t *map)
{
    int y = first_dot->y;

    for (int x = min(first_dot->x, second_dot->x); x <= max(first_dot->x, second_dot->x); x++)
        map->playground[y][x] = CORRIDOR_CHAR;
}

void draw_vertical_line(position_t *first_dot, position_t *second_dot, map_t *map)
{
    int x = first_dot->x;
    
    for (int y = min(first_dot->y, second_dot->y); y <= max(first_dot->y, second_dot->y); y++)
        map->playground[y][x] = CORRIDOR_CHAR;
}