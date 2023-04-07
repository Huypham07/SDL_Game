#include "game.h"

SDL_Window *gWindow = nullptr;
SDL_Renderer *gRenderer = nullptr;
SDL_Event gEvent;

int main(int argv, char *argc[])
{
    init(gWindow, gRenderer);
    bool isRunning = true;
    while (isRunning)
    {
        restart_game();
        handleEvent(isRunning, gEvent);
        update();
        render(gRenderer);
        SDL_Delay(5);
    }
    clean(gWindow, gRenderer);
    return 0;
}
