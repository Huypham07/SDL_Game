#include "game.h"
#include "map.h"
#include "player.h"
//BaseObject welcome;
BaseObject background;
Map_ *map_;
player character;

int cnt = 0;
void init(SDL_Window *&window, SDL_Renderer *&renderer)
{
    initSDL(window,renderer);
    background.load("image/background.png",renderer);
    background.destRect.w = SCREEN_WIDTH;
    background.destRect.h = SCREEN_HEIGHT;
    map_ = new Map_();
    map_->Load_tileSet(renderer, "image/tileset.png");
    map_->LoadMap("image/map.dat");
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
        character.InputEvent(e);

    }
}
void update()
{
    character.handleInput(map_);
}
void render(SDL_Renderer *renderer)
{
    SDL_RenderClear(renderer);
    background.renderTexture(renderer);
    map_->DrawMap(renderer);
    character.renderFrame(renderer);
    SDL_RenderPresent(renderer);

}
void clean(SDL_Window *window, SDL_Renderer *renderer)
{
    //welcome.Free();
    quitSDL(window,renderer);
}
