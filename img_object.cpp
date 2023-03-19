#include "img_object.h"

ImgObject::ImgObject()
{
    p_object = NULL;

}

void ImgObject::load(const std::string &file, SDL_Renderer *renderer)
{
    p_object = loadTexture(file, renderer);
    SDL_QueryTexture(p_object, NULL, NULL, &destRect.w,&destRect.h);
    srcRect.w = destRect.w;
    srcRect.h = destRect.h;
    srcRect.x = 0;
    srcRect.y = 0;

}

void ImgObject::renderTexture(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, p_object,&srcRect,&destRect);
}

void ImgObject::Free()
{
    SDL_DestroyTexture(p_object);
    p_object = NULL;

}

