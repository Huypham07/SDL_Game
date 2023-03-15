#ifndef MAP_H
#define MAP_H

#include "game.h"

struct Map_
{
    int start_x;

    ImgObject tileSet[11];
    int tileMap[MAX_MAP_Y][MAX_MAP_X];

    Map_();
    void Load_tileSet(SDL_Renderer *renderer, const std::string &file);
    void LoadMap(const std::string &file);
    void DrawMap(SDL_Renderer *renderer);

};

#endif // MAP_H
