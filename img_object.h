#ifndef IMAGE_OBJECT_H
#define IMAGE_OBJECT_H

#include "SDL_function.h"

struct ImgObject
{
    ImgObject();
    SDL_Texture *p_object;
    SDL_Rect srcRect, destRect;

    void SetRect(const int &x, const int &y)
    {
        destRect.x = x;
        destRect.y = y;
    }
    void SetRect(const int &w, const int &h, const int &x, const int &y){
        destRect.w = w;
        destRect.h = h;
        destRect.x = x;
        destRect.y = y;
    }
    void load(const std::string &file,SDL_Renderer *renderer);
    void renderTexture(SDL_Renderer *renderer);
    void Free();
};
#endif // IMAGE_OBJECT_H

