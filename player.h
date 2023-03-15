#ifndef PLAYER_H
#define PLAYER_H

#include "img_object.h"
#include "map.h"

struct player_state
{
    bool stt_right;
    bool stt_left;
    bool stt_up;
    bool stt_down;

    player_state();
};
struct player
{

    SDL_Texture *mplayer;
    int x_pos;
    int y_pos;

    int x_change;
    int y_change;

    int w_frame;
    int h_frame;

    bool jump_valid;
    player_state current;
    SDL_Rect player_rect;
    SDL_Rect frame_src[6];
    int frame;

    player();
    void load(const std::string &file,SDL_Renderer *renderer);
    void setFrame_src(const std::string &file, SDL_Renderer *renderer);
    void Gravity();
    void InputEvent(SDL_Event e);
    void Check_limited_Pos_X(Map_ *map_);
    void Check_limited_Pos_Y(Map_ *map_);
    void handleInput(Map_ *map_);
    void renderFrame(SDL_Renderer *renderer);

};
#endif // PLAYER_H
