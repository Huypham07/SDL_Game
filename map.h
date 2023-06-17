#ifndef MAP_H
#define MAP_H

#include "img_object.h"


const int win_tile = -1;
struct Map_
{
    int Mpos_x;

    ImgObject tileSet[11];
    ImgObject Win_flag;
    int tileMap[MAX_MAP_Y][MAX_MAP_X];
    // blanktile = 0, winflag = -1, filled > 0
    int trap[MAX_MAP_Y][MAX_MAP_X];
    Map_();
    void Load_tileSet(SDL_Renderer *renderer, const std::string &file);
    void LoadMap(const std::string &file);
    void LoadTrap(const std::string &file);
    void DrawMap(SDL_Renderer *renderer);
};

#endif // MAP_H
