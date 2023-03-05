#include "map.h"

Map_::Map_()
{}
void Map_::Load_tileSet(SDL_Renderer *renderer, const std::string &file)
{

    for (int i=0; i<8; i++)
    {
        tileSet[i].load(file, renderer);
        tileSet[i].destRect.w /= 8;
        tileSet[i].srcRect.x = i*TILE_SIZE;
        tileSet[i].srcRect.y = 0;
        tileSet[i].srcRect.w = TILE_SIZE;
        tileSet[i].srcRect.h = TILE_SIZE;
    }
}
void Map_::LoadMap(const char* file)
{
    freopen(file, "r", stdin);
    max_x = 0;
    max_y = 0;
    for (int i = 0; i < MAX_MAP_Y; i++)
    {
        for (int j = 0; j < MAX_MAP_X; j++)
        {
            std::cin >> tileMap[i][j];
            int val = tileMap[i][j];
            if (val>0){
                if (j > max_x) max_x = j;
                if (i > max_y) max_y = i;
            }

        }
    }
    max_x = (max_x + 1) * TILE_SIZE;
    max_y = (max_y + 1) * TILE_SIZE;

    start_x = 0;
    start_y = 0;
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
    map_y = start_y/TILE_SIZE;
    y1 = (start_y % TILE_SIZE) * -1;
    y2 = y1 + SCREEN_HEIGHT;

    for (int i=y1; i<=y2;i+=TILE_SIZE){
        map_x = start_x/TILE_SIZE;
        for (int j=x1; j<x2; j+=TILE_SIZE){
            int val = tileMap[map_y][map_x];
            if (val > 0){
                tileSet[val-1].SetRect(j,i);
                tileSet[val-1].renderTexture(renderer);
            }
            map_x ++;
        }
        map_y ++;
    }

}
