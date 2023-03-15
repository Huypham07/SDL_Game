#include "game.h"
#include "Map.h"
#include "player.h"

ImgObject background;
ImgObject welcome;
Map_ *map_;
player character;

bool Start_state = false;

void init(SDL_Window *&window, SDL_Renderer *&renderer)
{
    initSDL(window,renderer);
    background.load("image/background.jpg",renderer);
    background.SetRect(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
    welcome.load("image/welcome.png",renderer);
    welcome.SetRect(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
    map_ = new Map_();
    map_->Load_tileSet(renderer, "image/tileset.png");
    map_->LoadMap("image/map.txt");
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
            if (!Start_state)
            {
                if (e.button.button == SDL_BUTTON_LEFT)
                {
                    Start_state = true;
                }
            }
        }
        if (Start_state) character.InputEvent(e);

    }
    character.handleInput(map_);
}
void update()
{

}
void render(SDL_Renderer *renderer)
{
    SDL_RenderClear(renderer);
    if (!Start_state)
    {
        welcome.renderTexture(renderer);
    }
    else{
        background.renderTexture(renderer);
        map_->DrawMap(renderer);
        character.renderFrame(renderer);
    }
    SDL_RenderPresent(renderer);
}
void clean(SDL_Window *window, SDL_Renderer *renderer)
{
    welcome.Free();
    background.Free();
    SDL_DestroyTexture(character.mplayer);
    quitSDL(window,renderer);
}
