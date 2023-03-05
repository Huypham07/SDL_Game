#include "base_object.h"

BaseObject::BaseObject()
{
    p_object = NULL;

}

void BaseObject::load(const std::string &file, SDL_Renderer *renderer)
{
    p_object = loadTexture(file, renderer);
}

void BaseObject::renderTexture(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, p_object,&srcRect,&destRect);
}

void BaseObject::Free()
{
    SDL_DestroyTexture(p_object);
    p_object = NULL;

}

