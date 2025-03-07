#include "entity_generation.h"

static const char enemy_pool[ENEMY_POOL_LEN] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static const char item_pool[ITEM_POOL_LEN] = "/?*$!";

int check_unoccupied(room_t *room, position_t *pos)
{
    int status = UNOCCUPIED;

    for (int i = 0; i < room->entities_cnt && status == UNOCCUPIED; i++)
        if (room->entities[i].pos.x == pos->x && room->entities[i].pos.y == pos->y)
            status = OCCUPIED;
    
    return status;
}

void generate_entity_coords(room_t *room, position_t *pos)
{   
    int top_x = room->top_left.x;
    int top_y = room->top_left.y;
    int bot_x = room->bot_right.x;
    int bot_y = room->bot_right.y;

    do
    {
        pos->x = (rand() % (bot_x - top_x - 1) + 1) + top_x;
        pos->y = (rand() % (bot_y - top_y - 1) + 1) + top_y;
    }
    while (check_unoccupied(room, pos) == OCCUPIED);
}

void generate_entities(dungeon_t *dungeon)
{
   generate_player_pos(dungeon);
   generate_exit(dungeon);
   generate_enemies(dungeon);
   generate_items(dungeon); 
}

void generate_player_pos(dungeon_t *dungeon)
{
    int room_index = rand() % dungeon->room_cnt;
    room_t *spawn_room = dungeon->sequence[room_index];
    position_t player_pos;
    
    generate_entity_coords(spawn_room, &player_pos);

    entity_t player = {.type = PLAYER, .symbol = PLAYER_CHAR, .pos = player_pos};
    int cur_room_entity_cnt = dungeon->sequence[room_index]->entities_cnt;

    dungeon->sequence[room_index]->entities[cur_room_entity_cnt] = player;
    dungeon->sequence[room_index]->entities_cnt++;
}

void generate_exit(dungeon_t *dungeon)
{
    int room_index = rand() % dungeon->room_cnt;
    room_t *exit_room = dungeon->sequence[room_index];
    position_t exit_pos;
    
    generate_entity_coords(exit_room, &exit_pos);

    entity_t exit = {.type =EXIT, .symbol = EXIT_CHAR, .pos = exit_pos};
    int cur_room_entity_cnt = dungeon->sequence[room_index]->entities_cnt;

    dungeon->sequence[room_index]->entities[cur_room_entity_cnt] = exit;
    dungeon->sequence[room_index]->entities_cnt++;
}

void generate_enemies(dungeon_t *dungeon)
{
    for (int i = 0; i < dungeon->room_cnt; i++)
    {
        int enemies_cnt = rand() % MAX_ENEMIES_PER_ROOM;

        for (int j = 0; j < enemies_cnt; j++)
        {
            entity_t enemy;
            
            generate_enemy(dungeon->sequence[i], &enemy);

            int cur_room_entity_cnt = dungeon->sequence[i]->entities_cnt;

            dungeon->sequence[i]->entities[cur_room_entity_cnt] = enemy;
            dungeon->sequence[i]->entities_cnt++;
        }
    }
}

void generate_enemy(room_t *room, entity_t *enemy)
{
    enemy->type = ENEMY;
    enemy->symbol = enemy_pool[rand() % ENEMY_POOL_LEN];
    generate_entity_coords(room, &enemy->pos);
}

void generate_items(dungeon_t *dungeon)
{
    for (int i = 0; i < dungeon->room_cnt; i++)
    {
        int items_cnt = rand() % MAX_ITEMS_PER_ROOM;

        for (int j = 0; j < items_cnt; j++)
        {
            entity_t item;
            
            generate_item(dungeon->sequence[i], &item);

            int cur_room_entity_cnt = dungeon->sequence[i]->entities_cnt;

            dungeon->sequence[i]->entities[cur_room_entity_cnt] = item;
            dungeon->sequence[i]->entities_cnt++;
        }
    }
}

void generate_item(room_t *room, entity_t *item)
{
    item->type = ENEMY;
    item->symbol = item_pool[rand() % ITEM_POOL_LEN];
    generate_entity_coords(room, &item->pos);
}