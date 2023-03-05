#ifndef GAME_H
#define GAME_H
#include "base_object.h"


void init(SDL_Window *&window, SDL_Renderer *&renderer);
void handleEvent(bool &isRunning, SDL_Event e);
void update();
void render(SDL_Renderer *renderer);
void clean(SDL_Window *window, SDL_Renderer *renderer);


#endif // GAME_H
