#pragma once

#define ESC 27

#define DEFAULT_VIEW_DISTANCE   30.0f
#define DEFAULT_FOV     3.14159f / 3.5f
#define DEFAULT_ANGLE   0.0f

#define MOVEMENT_STEP   0.2f
#define TURN_ANGLE_STEP 0.03f

#define SEPARATOR_EPS   0.005f

#define RAY_CASTING_STEP    0.1f

#define NEAR_WALL_CHAR          0x2588
#define MEDIUM_WALL_CHAR        0x2593
#define FAR_WALL_CHAR           0x2592
#define FURTHEST_WALL_CHAR      0x2591

#define NEAR_FLOOR_CHAR         '#'
#define MEDIUM_FLOOR_CHAR       'X'
#define FAR_FLOOR_CHAR          '~'
#define FURTHEST_FLOOR_CHAR     '-'

#define SEPARATOR_CHAR          0x2591    

#define SPACE_CHAR              0xA0

#define MINIMAP_WALL_CHAR       0x2588
#define MINIMAP_CORRIDOR_CHAR   0x2591
#define MINIMAP_PLAYER_CHAR     0xA9

#define NEAR            3.0f
#define MEDIUM          2.0f
#define FAR             1.5f

#define FLOOR_NEAR      0.9f
#define FLOOR_MEDIUM    0.75f
#define FLOOR_FAR       0.5f
#define FLOOR_FURTHEST  0.25f