#ifndef START_GAME_H_INCLUDED
#define START_GAME_H_INCLUDED

#include "img_object.h"
#include "text_font.h"
#include "setting.h"
struct start_game
{
    bool state;
    ImgObject layer_welc;
    ImgObject start_but;
    ImgObject Tutorial;
    text_font text;

    start_game(SDL_Renderer *renderer);
    void ren_startpage(SDL_Renderer *renderer, Setting *setting_);
    void handle_click(SDL_Event e, Setting *setting_);
};

#endif // START_GAME_H_INCLUDED
