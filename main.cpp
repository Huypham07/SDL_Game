#include <iostream>
#include "SDL_function.h"
#include "base_object.h"
BaseObject welcome;

int main(int argv, char* argc[])
{
    initSDL(gWindow,gRenderer);

    welcome.loadTexture("image/welcome.png",gRenderer);

    bool quit = false;
    while (!quit){
        while (SDL_PollEvent(&gEvent)!=0){
            if (gEvent.type == SDL_QUIT){
                quit = true;
                break;
            }
            else if (gEvent.type == SDL_KEYDOWN){
                quit = true;
                break;
            }
        }
        SDL_RenderClear(gRenderer);
        welcome.renderTexture(gRenderer, NULL);
        SDL_RenderPresent(gRenderer);

        SDL_Delay(50);
    }
    quitSDL(gWindow,gRenderer);
    return 0;
}