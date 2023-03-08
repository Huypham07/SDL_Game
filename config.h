#ifndef _CONFIG_H_
#define _CONFIG_H_

//Game config
#define SCREEN_WIDTH            1280
#define SCREEN_HEIGHT           720
#define WINDOW_TITLE     "Trap Adventure 2"

#define TILE_SIZE               64
#define MAX_MAP_X               200
#define MAX_MAP_Y               12
#define BLANK_TILE              0
//speed
#define FREE_FALL 1
#define MAX_FREE_FALL 4
#define PLAYER_SPEED 5

/*
#define Y_VELOCITY_STEP  -20

#define FRAME_STEP       0.3
*/
/* Character */
#define CHARACTER_WIDTH  45
#define CHARACTER_HEIGHT 64
#define FIT_IMAGE        2
#define CHARACTER_STEP   10

#define REST_INDEX       0
#define WALK_INDEX       1
#define JUMP_INDEX       2
#define ATTACK_INDEX     3

#define NUMSTATES        4




#endif /* _CONFIG_H_ */


