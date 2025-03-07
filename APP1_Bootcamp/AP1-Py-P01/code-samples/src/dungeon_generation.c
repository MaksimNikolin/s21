#include "dungeon_generation.h"

void generate_dungeon(dungeon_t *dungeon)
{
    init_dungeon(dungeon);
    generate_sectors(dungeon);
    generate_connections(dungeon);
    generate_rooms_geometry(dungeon);
    generate_corridors_geometry(dungeon);
}

void init_dungeon(dungeon_t *dungeon)
{
    dungeon->room_cnt = 0;

    for (int i = 0; i < ROOMS_PER_SIDE + 2; i++)
        for (int j = 0; j < ROOMS_PER_SIDE + 2; j++)
        {
            dungeon->rooms[i][j].sector = UNINITIALIZED;

            for (int k = 0; k < 4; k++)
            {
                dungeon->rooms[i][j].connections[k] = NULL;
                dungeon->rooms[i][j].doors[k].x = UNINITIALIZED;
                dungeon->rooms[i][j].doors[k].y = UNINITIALIZED;
            }

            dungeon->rooms[i][j].entities_cnt = 0;
        }
    
    for (int i = 0; i < MAX_ROOMS_NUMBER; i++)
        dungeon->sequence[i] = NULL;
    for (int i = 0; i < MAX_CORRIDORS_NUMBER; i++)
        dungeon->corridors[i].type = UNINITIALIZED;

    dungeon->corridors_cnt = 0;
}

void generate_sectors(dungeon_t *dungeon)
{
    while (dungeon->room_cnt < 3)
    {
        int sector = 0;

        for (int i = 1; i < ROOMS_PER_SIDE + 1; i++)
            for (int j = 1; j < ROOMS_PER_SIDE + 1; j++, sector++)
                if (rand() / (double)RAND_MAX < ROOM_CHANCE && 
                    dungeon->rooms[i][j].sector == UNINITIALIZED)
                {
                    dungeon->rooms[i][j].sector = sector;
                    dungeon->rooms[i][j].grid_i = i;
                    dungeon->rooms[i][j].grid_j = j;
                    dungeon->sequence[dungeon->room_cnt++] = &dungeon->rooms[i][j];
                }
    }

    qsort(dungeon->sequence, (size_t)dungeon->room_cnt, sizeof(room_t *), room_placement_comparator);
}

int room_placement_comparator(const void *r1, const void *r2)
{
    const room_t *left_room = r1;
    const room_t *right_room = r2;

    return left_room->sector - right_room->sector;
}

void generate_connections(dungeon_t *dungeon)
{
    generate_primary_connections(dungeon);
    generate_secondary_connections(dungeon);
}

void generate_primary_connections(dungeon_t *dungeon)
{
    for (int i = 1; i < ROOMS_PER_SIDE + 1; i++)
        for (int j = 1; j < ROOMS_PER_SIDE + 1; j++)
            if (dungeon->rooms[i][j].sector != UNINITIALIZED)
            {
                if (dungeon->rooms[i - 1][j].sector != UNINITIALIZED)
                    dungeon->rooms[i][j].connections[0] = &dungeon->rooms[i - 1][j];
                if (dungeon->rooms[i][j + 1].sector != UNINITIALIZED)
                    dungeon->rooms[i][j].connections[1] = &dungeon->rooms[i][j + 1];
                if (dungeon->rooms[i + 1][j].sector != UNINITIALIZED)
                    dungeon->rooms[i][j].connections[2] = &dungeon->rooms[i + 1][j];
                if (dungeon->rooms[i][j - 1].sector != UNINITIALIZED)
                    dungeon->rooms[i][j].connections[3] = &dungeon->rooms[i][j - 1];    
            }
}

void generate_secondary_connections(dungeon_t *dungeon)
{
    for (int i = 0; i < dungeon->room_cnt - 1; i++)
    {
        room_t *cur = dungeon->sequence[i];
        room_t *next = dungeon->sequence[i + 1];

        if (cur->grid_i == next->grid_i && !next->connections[LEFT])
        {
            cur->connections[RIGHT] = next;
            next->connections[LEFT] = cur;
        }
        else if (cur->grid_i - next->grid_i == -1 && !cur->connections[BOTTOM])
        {
            if (cur->grid_j < next->grid_j && !next->connections[LEFT])
            {
                cur->connections[BOTTOM] = next;
                next->connections[LEFT] = cur;
            }
            else if (cur->grid_j > next->grid_j && !next->connections[RIGHT])
            {
                cur->connections[BOTTOM] = next;
                next->connections[RIGHT] = cur;
            }
            else if (cur->grid_j > next->grid_j && !cur->connections[BOTTOM] &&
                i < dungeon->room_cnt - 2)
            {
                cur->connections[BOTTOM] = dungeon->sequence[i + 2];
                dungeon->sequence[i + 2]->connections[RIGHT] = cur;
            }
        }
        else if (cur->grid_i - next->grid_i == -2 && !next->connections[TOP])
        {
            cur->connections[BOTTOM] = next;
            next->connections[TOP] = cur;
        }
    }
}

void generate_rooms_geometry(dungeon_t *dungeon)
{
    for (int i = 1; i < ROOMS_PER_SIDE + 1; i++)
        for (int j = 1; j < ROOMS_PER_SIDE + 1; j++)
            if (dungeon->rooms[i][j].sector != UNINITIALIZED)
            {
                generate_corners(&dungeon->rooms[i][j], (i - 1) * SECTOR_HEIGHT, (j - 1) * SECTOR_WIDTH);
                generate_doors(&dungeon->rooms[i][j]);
            }
}

void generate_corners(room_t *room, int offset_y, int offset_x)
{
    room->top_left.y = rand() % CORNER_VERT_RANGE + offset_y + 1;
    room->top_left.x = rand() % CORNER_HOR_RANGE + offset_x + 1;

    room->bot_right.y = SECTOR_HEIGHT - 1 - rand() % CORNER_VERT_RANGE + offset_y - 1;
    room->bot_right.x = SECTOR_WIDTH - 1 - rand() % CORNER_HOR_RANGE + offset_x - 1;
}

void generate_doors(room_t *room)
{
    if (room->connections[TOP])
    {
        room->doors[TOP].y = room->top_left.y;
        room->doors[TOP].x = rand() % (int)(room->bot_right.x - room->top_left.x - 1) + room->top_left.x + 1; // PupiPooo <----
    }

    if (room->connections[RIGHT])
    {
        room->doors[RIGHT].y = rand() % (int)(room->bot_right.y - room->top_left.y - 1) + room->top_left.y + 1; // PupiPAAA
        room->doors[RIGHT].x = room->bot_right.x;
    }

    if (room->connections[BOTTOM])
    {
        room->doors[BOTTOM].y = room->bot_right.y;
        room->doors[BOTTOM].x = rand() % (int)(room->bot_right.x - room->top_left.x - 1) + room->top_left.x + 1; // PUPI PIII
    }

    if (room->connections[LEFT])
    {
        room->doors[LEFT].y = rand() % (int)(room->bot_right.y - room->top_left.y - 1) + room->top_left.y + 1; // RAAAAAAAARH
        room->doors[LEFT].x = room->top_left.x;
    }
}

void generate_corridors_geometry(dungeon_t *dungeon)
{
    for (int i = 1; i < ROOMS_PER_SIDE + 1; i++)
        for (int j = 1; j < ROOMS_PER_SIDE + 1; j++)
        {   
            room_t *cur_room = &dungeon->rooms[i][j];

            if (cur_room->connections[RIGHT] && cur_room->connections[RIGHT]->connections[LEFT] == cur_room)
                generate_left_to_right_corridor(dungeon, cur_room, cur_room->connections[RIGHT], &dungeon->corridors[dungeon->corridors_cnt++]);

            if (cur_room->connections[BOTTOM])
            {
                int grid_i_diff = cur_room->grid_i - cur_room->connections[BOTTOM]->grid_i;
                int grid_j_diff = cur_room->grid_j - cur_room->connections[BOTTOM]->grid_j;

                if (grid_i_diff == -1 && grid_j_diff > 0)
                    generate_left_turn_corridor(dungeon, cur_room, cur_room->connections[BOTTOM], &dungeon->corridors[dungeon->corridors_cnt++]);
                else if (grid_i_diff == -1 && grid_j_diff < 0)
                    generate_right_turn_corridor(dungeon, cur_room, cur_room->connections[BOTTOM], &dungeon->corridors[dungeon->corridors_cnt++]);
                else
                    generate_top_to_bottom_corridor(dungeon, cur_room, cur_room->connections[BOTTOM], &dungeon->corridors[dungeon->corridors_cnt++]);
            }
        }
}

int max(int first_num, int second_num)
{
    int max = first_num;
    if (second_num > first_num)
        max = second_num;

    return max;
}

int min(int first_num, int second_num)
{
    int min = first_num;
    if (second_num < first_num)
        min = second_num;

    return min;
}

void generate_left_to_right_corridor(dungeon_t *dungeon, room_t *left_room, room_t *right_room, corridor_t *corridor)
{
    corridor->type = LEFT_TO_RIGHT_CORRIDOR;
    corridor->points_cnt = 4;
    corridor->points[0] = left_room->doors[RIGHT];

    int x_min = left_room->doors[RIGHT].x;
    int x_max = right_room->doors[LEFT].x;

    for (int i = 1; i < ROOMS_PER_SIDE + 1; i++)
        if (dungeon->rooms[i][left_room->grid_j].sector != UNINITIALIZED && i != left_room->grid_i)
            x_min = max(dungeon->rooms[i][left_room->grid_j].bot_right.x, x_min);
    for (int i = 1; i < ROOMS_PER_SIDE + 1; i++)
        if (dungeon->rooms[i][right_room->grid_j].sector != UNINITIALIZED && i != right_room->grid_i)
            x_max = min(dungeon->rooms[i][right_room->grid_j].top_left.x, x_min);

    int random_center_x = ((rand() % (x_max - x_min - 1)) + 1) + (x_min);
    position_t second_point = {random_center_x, left_room->doors[RIGHT].y};
    position_t third_point  = {random_center_x, right_room->doors[LEFT].y};
    
    corridor->points[1] = second_point;
    corridor->points[2] = third_point;
    corridor->points[3] = right_room->doors[3];
}

void generate_left_turn_corridor(dungeon_t *dungeon, room_t *top_room, room_t *bottom_left_room, corridor_t *corridor)
{
    corridor->type = LEFT_TURN_CORRIDOR;
    corridor->points_cnt = 3;
    corridor->points[0] = top_room->doors[BOTTOM];

    position_t second_point = {top_room->doors[BOTTOM].x, bottom_left_room->doors[RIGHT].y};

    corridor->points[1] = second_point;
    corridor->points[2] = bottom_left_room->doors[RIGHT];
}

void generate_right_turn_corridor(dungeon_t *dungeon, room_t *top_room, room_t *bottom_right_room, corridor_t *corridor)
{
    corridor->type = RIGHT_TURN_CORRIDOR;
    corridor->points_cnt = 3;
    corridor->points[0] = top_room->doors[BOTTOM];

    position_t second_point = {top_room->doors[BOTTOM].x, bottom_right_room->doors[LEFT].y};

    corridor->points[1] = second_point;
    corridor->points[2] = bottom_right_room->doors[LEFT];
}

void generate_top_to_bottom_corridor(dungeon_t *dungeon, room_t *top_room, room_t *bottom_room, corridor_t *corridor)
{
    corridor->type = TOP_TO_BOTTOM_CORRIDOR;
    corridor->points_cnt = 4;
    corridor->points[0] = top_room->doors[BOTTOM];

    int y_min = top_room->doors[BOTTOM].y;
    int y_max = bottom_room->doors[TOP].y;

    for (int j = 1; j < ROOMS_PER_SIDE + 1; j++)
        if (dungeon->rooms[top_room->grid_i][j].sector != UNINITIALIZED)
            y_min = max(dungeon->rooms[top_room->grid_i][j].bot_right.y, y_min);
    for (int j = 1; j < ROOMS_PER_SIDE + 1; j++)
        if (dungeon->rooms[bottom_room->grid_i][j].sector != UNINITIALIZED)
            y_max = min(dungeon->rooms[bottom_room->grid_i][j].top_left.y, y_max);

    int random_center_y = ((rand() % (y_max - y_min - 1)) + 1) + (y_min);
    position_t second_point = {top_room->doors[BOTTOM].x, random_center_y};
    position_t third_point  = {bottom_room->doors[TOP].x, random_center_y};
    
    corridor->points[1] = second_point;
    corridor->points[2] = third_point;
    corridor->points[3] = bottom_room->doors[TOP];
}