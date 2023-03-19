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
    Mpos_x = 0;
}
void Map_::LoadTrap(const std::string &file)
{
    std::ifstream file_trap;
    file_trap.open(file,std::ios::in);
    while (!file_trap.eof())
    {
        if (file_trap)
        {
            for (int i = 0; i < MAX_MAP_Y; i++)
            {
                for (int j = 0; j < MAX_MAP_X; j++)
                {
                    file_trap >> trap[i][j];
                }
            }
        }
    }
    file_trap.close();
}
void Map_::DrawMap(SDL_Renderer *renderer)
{
    int x1 = 0;
    int x2 = 0;

    int index_x = 0, index_y = 0;

    x1 = (Mpos_x % TILE_SIZE) * -1;
    x2 = x1 + SCREEN_WIDTH;
    if (x1 != 0) {
        x2+= TILE_SIZE;
    }

    for (int i=0; i<=SCREEN_HEIGHT; i+=TILE_SIZE)
    {
        index_x = Mpos_x/TILE_SIZE;
        for (int j=x1; j<x2; j+=TILE_SIZE)
        {
            int val = tileMap[index_y][index_x];
            if (val > 0)
            {
                if (trap[index_y][index_x] == 1){
                    tileSet[val-1].SetRect(j,i);
                    tileSet[val-1].renderTexture(renderer);
                }

            }
            else if (val == win_tile){
                Win_flag.SetRect(TILE_SIZE, TILE_SIZE, j, i);
                Win_flag.renderTexture(renderer);
            }
            index_x ++;
        }
        index_y ++;
    }

}
