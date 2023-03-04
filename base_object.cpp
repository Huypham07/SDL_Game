#include "base_object.h"

BaseObject::BaseObject()
{
    p_object = NULL;

}

void BaseObject::load(const std::string &file)
{
    p_object = loadTexture(file, gRenderer);
}

void BaseObject::renderTexture()
{
    SDL_RenderCopy(gRenderer, p_object,&srcRect,&destRect);
}

void BaseObject::Free()
{
    SDL_DestroyTexture(p_object);
    p_object = NULL;

}

