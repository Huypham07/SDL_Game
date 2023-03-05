#ifndef BASE_OBJECT_H
#define BASE_OBJECT_H

#include "SDL_function.h"

struct BaseObject
{
    BaseObject();
    SDL_Texture *p_object;
    //int x_pos,y_pos;
    int frame;
    SDL_Rect srcRect, destRect;

    void SetRect(const int &x, const int &y)
    {
        destRect.x = x;
        destRect.y = y;
    }

    void load(const std::string &file,SDL_Renderer *renderer);
    void renderTexture(SDL_Renderer *renderer);
    void Free();
};
#endif // BASE_OBJECT_H

