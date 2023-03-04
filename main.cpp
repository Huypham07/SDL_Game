#include <iostream>
#include "SDL_function.h"
#include "base_object.h"
#include "game.h"

int main(int argv, char* argc[])
{
    const int FPS = 60;
    const int frameDelay = 1000/FPS;

    Uint32 frameStart;
    int frameTime;

    init();
    bool isRunning = true;
    while (isRunning){
        frameStart = SDL_GetTicks();

        handleEvent(isRunning);
        update();
        render();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime){
            SDL_Delay(frameDelay - frameTime);
        }
    }
    clean();
    return 0;
}
