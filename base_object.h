#ifndef BASE_OBJECT_H
#define BASE_OBJECT_H

#include "SDL_function.h"

struct BaseObject
{
    BaseObject();
    SDL_Texture *p_object;
    SDL_Rect rect_;
    void SetRect(const int &x, const int &y)
    {
        rect_.x = x;
        rect_.y = y;
    }
    SDL_Rect GetRect() const
    {
        return rect_;
    }
    SDL_Texture *GetObject() const
    {
        return p_object;
    }

    void loadTexture(const std::string &file, SDL_Renderer *renderer);
    void renderTexture(SDL_Renderer *renderer,const SDL_Rect *srcRect);
    void Free();
};
#endif // BASE_OBJECT_H

