#ifndef MAP_H
#define MAP_H

#include "game.h"

struct Map_
{
    SDL_Rect src,dest;

    BaseObject tileSet[8];

    int Map[20][12];

    Map_();
    void Load_tileSet(SDL_Renderer *renderer);
    void LoadMap(const char* file);
    void DrawMap(SDL_Renderer *renderer);

};

#endif // MAP_H
