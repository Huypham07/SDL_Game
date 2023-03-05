#include "game.h"
#include "map.h"
//BaseObject welcome;

Map_ *map_;
BaseObject *player;
int cnt = 0;
void init(SDL_Window *&window, SDL_Renderer *&renderer){
    initSDL(window,renderer);
    //welcome.load("image/welcome.png");
    player = new BaseObject();
    player->load("image/char.png",renderer);
    player->destRect.x = 0;
    player->destRect.y = 0;
    player->frame = 6;

    map_ = new Map_();
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
    }
}
void update(){
    map_->LoadMap("image/map.txt");
    if (cnt < player->frame){
            player->srcRect.x = 80 * cnt;
            player->srcRect.y = 224;
            player->srcRect.w = 80;
            player->srcRect.h = 112;
    }
    else cnt = 0;
    player->destRect.x ++;
    player->destRect.w = player->srcRect.w;
    player->destRect.h = player->srcRect.h;
}
void render(SDL_Renderer *renderer){
    SDL_RenderClear(renderer);
    map_->DrawMap(renderer);
    player->renderTexture(renderer);
    SDL_RenderPresent(renderer);

}
void clean(SDL_Window *window, SDL_Renderer *renderer){
    //welcome.Free();
    player->Free();
    quitSDL(window,renderer);
}
