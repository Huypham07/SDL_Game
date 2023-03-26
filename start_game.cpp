#include "start_game.h"

start_game::start_game(SDL_Renderer *renderer)
{
    state = false;
    layer_welc.load("image/welcome.png", renderer);
    layer_welc.SetRect(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
    start_but.load("image/START.png", renderer);
    start_but.SetRect(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 5, SCREEN_WIDTH / 3 - 2 * TILE_SIZE, SCREEN_HEIGHT * 3 / 4);
    text.Set_ptsize(100);
    text.SetColor(255,255,255);
    text.SetRect(start_but.destRect.w * 4 / 5, start_but.destRect.h * 4 / 5,
                 SCREEN_WIDTH / 2 - start_but.destRect.w * 2 / 5 - 2 * TILE_SIZE, start_but.destRect.y + start_but.destRect.h / 10);
    Tutorial.load("image/tutor.png", renderer);
    Tutorial.SetRect(6 * TILE_SIZE, 3 * TILE_SIZE, SCREEN_WIDTH - 7 * TILE_SIZE, SCREEN_HEIGHT - 3 * TILE_SIZE);
}
void start_game::handle_click(SDL_Event e, Setting *setting_)
{
    if (!state)
    {
        if (!setting_->state)
        {
            if (e.type == SDL_MOUSEBUTTONUP)
            {
                if (e.button.button == SDL_BUTTON_LEFT)
                {
                    if ((e.button.x >= start_but.destRect.x && e.button.x <= start_but.destRect.x + start_but.destRect.w)
                        && (e.button.y >= start_but.destRect.y && e.button.y <= start_but.destRect.y + start_but.destRect.h))
                    {
                    text.SetColor(255,255,255);
                    state = true;
                    playSound(setting_->Click);
                    }
                }
            }
            else if (e.type == SDL_MOUSEMOTION){
                if ((e.motion.x >= start_but.destRect.x && e.motion.x <= start_but.destRect.x + start_but.destRect.w)
                        && (e.motion.y >= start_but.destRect.y && e.motion.y <= start_but.destRect.y + start_but.destRect.h))
                    text.SetColor(255,51,51);
                else
                {
                    text.SetColor(255,255,255);
                }
            }
        }
    }
}
void start_game::ren_startpage(SDL_Renderer *renderer, Setting *setting_)
{
    if (state)
    {
        setting_->button.SetRect(TILE_SIZE, TILE_SIZE, 0, 0);
        setting_->text.SetRect(setting_->button.destRect.w, setting_->button.destRect.w / 3, setting_->button.destRect.x, setting_->button.destRect.y + setting_->button.destRect.h);
    }
    else
    {
    setting_->button.SetRect(TILE_SIZE * 2, TILE_SIZE * 2, 0, SCREEN_HEIGHT * 3 / 4);
    setting_->text.SetRect(setting_->button.destRect.w, setting_->button.destRect.w / 3, setting_->button.destRect.x, setting_->button.destRect.y + setting_->button.destRect.h);
    layer_welc.renderTexture(renderer);
    start_but.renderTexture(renderer);
    text.load("font/PermanentMarker-Regular.ttf", "START !!!", renderer);
    text.renderTexture(renderer);
    Tutorial.renderTexture(renderer);
    }

}
