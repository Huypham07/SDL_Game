#include "text_font.h"

text_font::text_font()
{
    texture = nullptr;
    rect = {0, 0, 0, 0};
}
void text_font::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
    textColor.r = red;
    textColor.g = green;
    textColor.b = blue;
}
void text_font::load(const std::string &file, const std::string &text, SDL_Renderer *renderer)
{
    texture = loadFont(file, text, textColor, ptsize, renderer);
}
void text_font::SetRect(const int &w, const int &h, const int &x, const int &y)
{
    rect.w = w;
    rect.h = h;
    rect.x = x;
    rect.y = y;
}
void text_font::renderTexture(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}
void text_font::Free()
{
    SDL_DestroyTexture(texture);
    rect = {0, 0, 0, 0};
}
