#include "game.h"
#include "map.h"
//BaseObject welcome;
Map_ *map_;
BaseObject *player;
int cnt = 0;
void init(){
    initSDL(gWindow,gRenderer);
    //welcome.load("image/welcome.png");
    player = new BaseObject();
    player->load("image/char.png");
    player->destRect.x = 0;
    player->destRect.y = 0;
    player->frame = 6;

    map_ = new Map_();
}
void handleEvent(bool &isRunning)
{
    while (SDL_PollEvent(&gEvent)!=0)
    {
        if (gEvent.type == SDL_QUIT)
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
void render(){
    SDL_RenderClear(gRenderer);
    map_->DrawMap();
    player->renderTexture();
    SDL_RenderPresent(gRenderer);

}
void clean(){
    //welcome.Free();
    player->Free();
    quitSDL(gWindow,gRenderer);
}
