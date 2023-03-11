#ifndef MAP_H
#define MAP_H

#include "game.h"

struct Map_
{
    int start_x, start_y;
    int max_x,max_y;

    BaseObject tileSet[11];
    int tileMap[MAX_MAP_Y][MAX_MAP_X];

    Map_();
    void Load_tileSet(SDL_Renderer *renderer, const std::string &file);
    void LoadMap(const char* file);
    void DrawMap(SDL_Renderer *renderer);

};

#endif // MAP_H
