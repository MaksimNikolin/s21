#include "dungeon_generation.h"
#include "entity_generation.h"
#include "dungeon_to_map_translation.h"
#include "dungeon_output.h"
#include "connectivity_checker.h"

/*
This is a simple rogue dungeon generator.


The process of level creation consists of 3 main stages:

1. Dungeon generation.
    generate_dungeon() function is resposible for room number, their placement and size,
    as well as corridors generation.

2. Entity generation.
    generate_entities() function sets the spawn- and exit points and populates the
    dungeon with enemies and items.

3. Generated data to map translation.
    dungeon_to_map() function builds the map_t structure, using the results of previous
    two stages. 
    The said structure contains a printable representation of the dungeon as a char-type
    matrix, arrays of enemies and items, and player and exit data.


 check_connectivity() function performs a depth-first search and concludes if there
 are any unreacheble rooms or not

 print_map() function displays the matrix of the map structure built in stage 3
 of dungeon generation.
*/

int main(void)
{
    srand(time(NULL));

    dungeon_t dungeon;
    map_t map;
    int check_result;

    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);

    generate_dungeon(&dungeon);
    print_dungeon_generated(MAP_HEIGHT + 5);
    generate_entities(&dungeon);
    print_entities_generated(MAP_HEIGHT + 6);
    dungeon_to_map(&dungeon, &map);
    print_map_created(MAP_HEIGHT + 7);
    check_result = check_connectivity(&dungeon);
    print_connectivity_check_result(check_result, MAP_HEIGHT + 9);
    print_entity_pools(MAP_HEIGHT + 11);
    print_map(&map);

    getch();
    endwin();

    return 0;
}