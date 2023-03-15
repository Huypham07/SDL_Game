#include "map.h"
#include <fstream>
Map_::Map_()
{}
void Map_::Load_tileSet(SDL_Renderer *renderer, const std::string &file)
{
    for (int i=0; i<11; i++)
    {
        tileSet[i].load(file, renderer);
        tileSet[i].destRect.w = TILE_SIZE;
        tileSet[i].destRect.h = TILE_SIZE;
        tileSet[i].srcRect.w /=11;
        tileSet[i].srcRect.x = i*tileSet[i].srcRect.w;
        tileSet[i].srcRect.y = 0;
    }
}
void Map_::LoadMap(const std::string &file)
{
    std::ifstream file_map;
    file_map.open(file,std::ios::in);
    while (!file_map.eof())
    {
        if (file_map)
        {
            for (int i = 0; i < MAX_MAP_Y; i++)
            {
                for (int j = 0; j < MAX_MAP_X; j++)
                {
                    file_map >> tileMap[i][j];
                }
            }
        }
    }
    file_map.close();
    start_x = 0;
}
void Map_::DrawMap(SDL_Renderer *renderer)
{
    int x1 = 0;
    int x2 = 0;
    int y1 = 0;
    int y2 = 0;
    int map_x = 0;
    int map_y = 0;

    map_x = start_x/TILE_SIZE;
    x1 = (start_x % TILE_SIZE) * -1;
    x2 = x1 + SCREEN_WIDTH;
    if (x1 != 0) x2+= TILE_SIZE;
    y1 = 0;
    y2 = SCREEN_HEIGHT;

    for (int i=y1; i<=y2; i+=TILE_SIZE)
    {
        map_x = start_x/TILE_SIZE;
        for (int j=x1; j<x2; j+=TILE_SIZE)
        {
            int val = tileMap[map_y][map_x];
            if (val > 0)
            {
                tileSet[val-1].SetRect(j,i);
                tileSet[val-1].renderTexture(renderer);
            }
            map_x ++;
        }
        map_y ++;
    }

}
