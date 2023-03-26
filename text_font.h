#ifndef TEXT_FONT_H_INCLUDED
#define TEXT_FONT_H_INCLUDED

#include "SDL_function.h"
struct text_font
{
    SDL_Texture *texture;
    int ptsize;
    SDL_Color textColor;
    SDL_Rect rect;

    text_font();
    void Set_ptsize(const int sz) { ptsize = sz; }
    void SetColor(Uint8 red, Uint8 green, Uint8 blue);
    void load(const std::string &file, const std::string &text, SDL_Renderer *renderer);
    void SetRect(const int &w, const int &h, const int &x, const int &y);
    void renderTexture(SDL_Renderer *renderer);
    void Free();
};

#endif // TEXT_FONT_H_INCLUDED
