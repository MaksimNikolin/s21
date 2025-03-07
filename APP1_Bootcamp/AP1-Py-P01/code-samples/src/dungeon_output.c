#include "dungeon_output.h"

void print_map(map_t *map)
{
    for (int i = 0; i < MAP_HEIGHT; i++)
        for (int j = 0; j < MAP_WIDTH; j++)
            mvaddch(i, j, map->playground[i][j]);
}

void print_dungeon_generated(int y)
{
    int x = 0;

    mvprintw(y, x, "DUNGEON GENERATED...");
}

void print_entities_generated(int y)
{
    int x = 0;

    mvprintw(y, x, "ENTITIES GENERATED...");
}

void print_map_created(int y)
{
    int x = 0;

    mvprintw(y, x, "MAP CREATED FROM GENERATED DATA...");
}

void print_connectivity_check_result(int check_result, int y)
{
    int x = 0;

    if (check_result == CONNECTED)
        mvprintw(y, x, "ROOM GRAPH IS CONNECTED!");
    else
        mvprintw(y, x, "ROOM GRAPH IS NOT CONNECTED!");
}

void print_entity_pools(int y)
{
    int x = 0;

    mvprintw(y, x, "\"ABCDEFGHIJKLMNOPQRSTUVWXYZ\" : Enemy pool.");
    mvprintw(y + 1, x, "\"/?*$!\"                      : Item pool.");
    mvprintw(y + 2, x, "\"@\" \"|\"                      : Player and exit.");
}