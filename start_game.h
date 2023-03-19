#ifndef START_GAME_H_INCLUDED
#define START_GAME_H_INCLUDED

#include "img_object.h"
#include "setting.h"
struct start_game
{
    bool state;
    ImgObject layer_welc;
    ImgObject start_but;
    Setting setting_but;

    start_game(SDL_Renderer *renderer);
    void handle_click(SDL_Event e);
};

#endif // START_GAME_H_INCLUDED
