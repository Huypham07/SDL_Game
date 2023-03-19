#include "start_game.h"

start_game::start_game(SDL_Renderer *renderer){
    state = false;
    layer_welc.load("image/welcome.png",renderer);
    layer_welc.SetRect(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
    start_but.load("image/START.png",renderer);
    start_but.SetRect(SCREEN_WIDTH/3, SCREEN_HEIGHT/5, SCREEN_WIDTH/3, SCREEN_HEIGHT*3/4);
}
void start_game::handle_click(SDL_Event e){
    if (e.type == SDL_MOUSEBUTTONDOWN){
        if (e.button.button == SDL_BUTTON_LEFT){
            if ((e.button.x >= start_but.destRect.x && e.button.x <= start_but.destRect.x + start_but.destRect.w)
                &&(e.button.y >= start_but.destRect.y && e.button.y <= start_but.destRect.y + start_but.destRect.h))
                    state = true;
        }
    }
}
