#include "base_object.h"

BaseObject::BaseObject()
{
    p_object = NULL;
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;
}

void BaseObject::loadTexture(const std::string &file, SDL_Renderer *renderer)
{
    SDL_Texture *texture = nullptr;
    SDL_Surface *loadedImage = IMG_Load(file.c_str());
    if (loadedImage != nullptr)
    {
        texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
        SDL_FreeSurface(loadedImage);
        if (texture == nullptr)
        {
            logSDLError(std::cout, "CreateTextureFromSurface");
        }
    }
    else
    {
        logSDLError(std::cout, "LoadBMP");
    }
    p_object = texture;
    SDL_QueryTexture(texture,NULL,NULL,&rect_.w,&rect_.h);
}

void BaseObject::renderTexture(SDL_Renderer *renderer,const SDL_Rect *srcRect)
{
    SDL_Rect dst = {rect_.x,rect_.y,rect_.w,rect_.h};

    SDL_RenderCopy(renderer, p_object, srcRect, &dst);
}

void BaseObject::Free()
{
    SDL_DestroyTexture(p_object);
    p_object = NULL;
    rect_.x=0;
    rect_.y=0;
    rect_.w=0;
    rect_.h=0;
}

