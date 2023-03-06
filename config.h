#ifndef _CONFIG_H_
#define _CONFIG_H_

//Game config
#define SCREEN_WIDTH            1280
#define SCREEN_HEIGHT           720
#define WINDOW_TITLE     "Trap Adventure 2"

#define TILE_SIZE               64
#define MAX_MAP_X               200
#define MAX_MAP_Y               12
//speed
#define GRAVITY_SPEED 1
#define MAX_FAIL_SPEED 4
#define PLAYER_SPEED 10

/*#define GRAVITY          2
#define Y_VELOCITY_STEP  -20

#define FRAME_STEP       0.3
*/
/* Character */
#define CHARACTER_WIDTH  45
#define CHARACTER_HEIGHT 64

#define CHARACTER_STEP   10

#define REST_INDEX       0
#define WALK_INDEX       1
#define JUMP_INDEX       2
#define ATTACK_INDEX     3

#define NUMSTATES        4




#endif /* _CONFIG_H_ */


