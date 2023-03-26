#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#include "img_object.h"
#include "Map.h"

struct Ball
{
    ImgObject ball_;

    int x_pos;
    int y_pos;

    int x_change;

    int w_frame;
    int h_frame;
    int direction;
    bool is_move;
    SDL_Rect frame_src[12];
    int frame;

    Ball();
    void setFrame_src(const std::string &file, SDL_Renderer *renderer);
    void set_pos(const int &x,const int &y);
    bool Check_limited_Pos_X(Map_ *map_);
    void Move(Map_ *map_);
    void renderFrame(SDL_Renderer *renderer, Map_ *map_);
};
#endif // BALL_H_INCLUDED
