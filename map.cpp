#include "map.h"

Map_::Map_()
{

}
void Map_::Load_tileSet(SDL_Renderer *renderer){
    for (int i=0; i<8; i++)
    {
        tileSet[i].load("image/tileset.png", renderer);
    }
}
void Map_::LoadMap(const char* file)
{
    freopen(file, "r", stdin);
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            std::cin >> Map[i][j];
        }
    }
}
void Map_::DrawMap(SDL_Renderer *renderer)
{
    int type = 0;

    for (int j=0;j<20;j++){
        for (int i=0;i<12;i++){
            type = Map[j][i];
            switch (type)
            {
            case 0:
                tileSet[0].renderTexture(renderer);
                break;
            }
        }
    }
}
