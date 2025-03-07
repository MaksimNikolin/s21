#include "screen.h"
#include "movement.h"
#include "walker_objs.h"
#include "dungeon_generation.h"
#include "dungeon_to_map_translation.h"
#include "entity_generation.h"

/*
This is a first-person walker built on top of rogue dungeon generator.

The picture is rendered via ray casting.

+-------------------+
|            /      |
|           /     # |
| player-> @------# |
|           \     # |
|            \    # |
+-------------------+

1. Rays are cast from player's point of view from left to right.

2. If a ray hits a wall, a vertical line is drawn on the screen. The height of the line
   depends on the distance that the ray has traveled until it has hit the wall.

Implemented algorithms are described in this post:
http://ilinblog.ru/article.php?id_article=49
*/

int main(void)
{
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    srand(time(NULL));
    timeout(1);

    int key = 0;
    dungeon_t dungeon;
    screen_t screen;
    map_t map;
    player_t player;

    generate_dungeon(&dungeon);
    generate_player_pos(&dungeon);
    dungeon_to_map(&dungeon, &map);
    init_player(&player, &map.player_spawn);
    
    while ((key = getch()) != ESC)
    {
        player_movement(&map, &player, key);
        render_screen(&map, &player, &screen);
        screen_print(&screen);
    }

    endwin();

    return 0;
}