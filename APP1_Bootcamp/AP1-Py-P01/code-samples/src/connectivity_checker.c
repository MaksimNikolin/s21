#include "connectivity_checker.h"

int check_connectivity(dungeon_t *rooms)
{
    int rc = CONNECTED;
    int visited[9] = { 0 };
    int visited_count = depth_first_search(rooms->sequence[0], visited);

    if (visited_count != rooms->room_cnt)
        rc = NOT_CONNECTED;
    
    return rc;
}

int depth_first_search(room_t *cur, int *visited)
{
    int visited_count = 1;

    visited[cur->sector] = 1;
    
    for (int i = 0; i < 4; i++)
        if (cur->connections[i] && !visited[cur->connections[i]->sector])
            visited_count += depth_first_search(cur->connections[i], visited);
    
    return visited_count;
}