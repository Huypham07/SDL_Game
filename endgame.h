#ifndef ENDGAME_H_INCLUDED
#define ENDGAME_H_INCLUDED

#include "img_object.h"
#include "text_font.h"
#include "setting.h"
#include "player.h"
#include "start_game.h"
struct EndGame
{
    ImgObject GameOver;
    ImgObject WinGame;
    text_font text;
    bool win_state;
    bool GameOver_state;
    EndGame(SDL_Renderer *renderer);
    void handle_click(SDL_Event e, Setting *setting_, Map_ *map_, player *player_, start_game * start_game_);
    void render_page(SDL_Renderer *renderer, Setting *setting_);
};

#endif // ENDGAME_H_INCLUDED
