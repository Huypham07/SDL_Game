#include "game.h"

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
SDL_Event gEvent;

int main(int argv, char* argc[])
{

    const int FPS = 30;
    const int frameDelay = 1000/FPS;

    Uint32 frameStart;
    int frameTime;

    init(gWindow,gRenderer);
    bool isRunning = true;
    while (isRunning)
    {
        frameStart = SDL_GetTicks();

        handleEvent(isRunning, gEvent);
        update();
        render(gRenderer);

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    clean(gWindow, gRenderer);
    return 0;
}
