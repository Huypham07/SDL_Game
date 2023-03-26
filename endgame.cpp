#include "endgame.h"

int repeat_sound = 0;

EndGame::EndGame(SDL_Renderer *renderer)
{
    GameOver.load("image/GameOver.png", renderer);
    GameOver.SetRect(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
    GameOver_state = false;

    WinGame.load("image/Win.png",renderer);
    WinGame.SetRect(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
    win_state = false;

    text.Set_ptsize(100);
    text.SetColor(255, 204, 153);
    text.SetRect(SCREEN_WIDTH * 4 / 5, TILE_SIZE, SCREEN_WIDTH / 2 - SCREEN_WIDTH * 4 / 10, SCREEN_HEIGHT / 2 + TILE_SIZE);
    text.load("font/PermanentMarker-Regular.ttf", "Click  anywhere  outside  the  Setting  to  return  to  the  Start  Page !", renderer);

}
void EndGame::handle_click(SDL_Event e, Setting *setting_, Map_ *map_, player *player_, start_game * start_game_)
{
    if (GameOver_state || win_state)
    {
        if (!setting_->state)
        {
            if (e.type == SDL_MOUSEBUTTONUP)
            {
                    if (e.button.button == SDL_BUTTON_LEFT)
                    {
                        if ((e.button.x < setting_->button.destRect.x || e.button.x > setting_->button.destRect.x + setting_->button.destRect.w)
                            || (e.button.y < setting_->button.destRect.y || e.button.y > setting_->button.destRect.y + setting_->button.destRect.h + setting_->text.rect.h))
                            {
                            start_game_->state = false;
                            win_state = false;
                            GameOver_state = false;
                            player_->Restart();
                            map_->LoadTrap("image/trap.txt");
                            repeat_sound = 0;
                            playSound(setting_->Click);
                            }
                    }
            }
        }
    }
}
void EndGame::render_page(SDL_Renderer *renderer, Setting *setting_)
{
    if (win_state)
    {
        if (repeat_sound < 1){
            playSound(setting_->YouWin);
            std::cout<<"You Win!!!"<<std::endl;
            repeat_sound ++;
        }
        setting_->button.SetRect(TILE_SIZE * 2, TILE_SIZE * 2, SCREEN_WIDTH / 2 - TILE_SIZE, SCREEN_HEIGHT - 3 * TILE_SIZE);
        setting_->text.SetRect(setting_->button.destRect.w, setting_->button.destRect.w / 3, setting_->button.destRect.x, setting_->button.destRect.y + setting_->button.destRect.h);
        WinGame.renderTexture(renderer);
        text.renderTexture(renderer);
    }
    if (GameOver_state)
    {
        if (repeat_sound < 1){
            playSound(setting_->Gameover);
            std::cout<<"Game Over!!!"<<std::endl;
            repeat_sound ++;
        }
        setting_->button.SetRect(TILE_SIZE * 2, TILE_SIZE * 2, SCREEN_WIDTH / 2 - TILE_SIZE, SCREEN_HEIGHT - 3 * TILE_SIZE);
        setting_->text.SetRect(setting_->button.destRect.w, setting_->button.destRect.w / 3, setting_->button.destRect.x, setting_->button.destRect.y + setting_->button.destRect.h);
        GameOver.renderTexture(renderer);
        text.renderTexture(renderer);
    }
}
