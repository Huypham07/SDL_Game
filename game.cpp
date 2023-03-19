#include "game.h"
#include "Map.h"
#include "player.h"
#include "start_game.h"
ImgObject background;
start_game *Start_;
ImgObject GameOver;
ImgObject WinGame;
Map_ *map_;
player character;

bool Start_state = false;
bool Game_over = false;
bool Win = false;

void init(SDL_Window *&window, SDL_Renderer *&renderer)
{
    initSDL(window,renderer);
    background.load("image/background.jpg",renderer);
    background.SetRect(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
    Start_ = new start_game(renderer);
    GameOver.load("image/GameOver.png",renderer);
    GameOver.SetRect(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
    WinGame.load("image/Win.png",renderer);
    WinGame.SetRect(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
    map_ = new Map_();
    map_->Load_tileSet(renderer, "image/tileset.png");
    map_->Win_flag.load("image/flag.png",renderer);
    map_->Win_flag.destRect.x = MAX_MAP_X*TILE_SIZE-2*TILE_SIZE;
    map_->LoadMap("image/map.txt");
    map_->LoadTrap("image/trap.txt");
    character.setFrame_src("image/char.png",renderer);
}

void handleEvent(bool &isRunning, SDL_Event e)
{
    while (SDL_PollEvent(&e)!=0)
    {
        if (e.type == SDL_QUIT)
        {
            isRunning = false;
            break;
        }
        else if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            if (Win || Game_over){
                if (e.button.button == SDL_BUTTON_LEFT){
                    Start_->state = false;
                    Win = false;
                    Game_over = false;
                    character.Restart();
                }
            }
        }
        if (!Start_state){
            Start_->handle_click(e);
        }
        if (Start_state && !Win && !Game_over) {
            character.InputEvent(e);
        }

    }
    character.handleInput(map_);

}
void update()
{
    Start_state = Start_->state;
    Game_over = character.trap_checking(map_);
    Win = character.WinState(map_);
}
void render(SDL_Renderer *renderer)
{
    SDL_RenderClear(renderer);

    background.renderTexture(renderer);
    map_->DrawMap(renderer);
    character.renderFrame(renderer, map_);

    if (!Start_state)
    {
        Start_->layer_welc.renderTexture(renderer);
        Start_->start_but.renderTexture(renderer);
    }
    if (Win){
        std::cout<<"You Winnn !!"<<std::endl;
        WinGame.renderTexture(renderer);
    }
    if (Game_over){
        std::cout<<"Game Over !!"<<std::endl;
        GameOver.renderTexture(renderer);
    }
    SDL_RenderPresent(renderer);
}
void clean(SDL_Window *window, SDL_Renderer *renderer)
{
//    welcome.Free();
    background.Free();
    delete map_;
    SDL_DestroyTexture(character.mplayer);
    quitSDL(window,renderer);
}
