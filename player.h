#ifndef PLAYER_H
#define PLAYER_H

#include "base_object.h"

struct input
{
    int right;
    int left;
    int up;
    int down;
};
struct status
{
    bool stt_right;
    bool stt_left;
    bool stt_up;
    bool stt_down;

    status();
};
struct player
{

//    BaseObject *mPlayer;
    SDL_Texture *mplayer;
    float x_pos;
    float y_pos;

    float x_change;
    float y_change;

    int w_frame;
    int h_frame;
    status current;
    input input_type;
    SDL_Rect player_rect;
    SDL_Rect frame_src[7];
    int frame;
    player();
    void load(const std::string &file,SDL_Renderer *renderer);
    void setFrame_src(const std::string &file, SDL_Renderer *renderer);
    void InputEvent(SDL_Event e);
    void handleInput();
    void renderFrame(SDL_Renderer *renderer);
};
#endif // PLAYER_H
