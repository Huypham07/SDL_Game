#ifndef SDL_FUNCTION_H
#define SDL_FUNCTION_H

#include <iostream>
#include "config.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

static SDL_Window *gWindow = NULL;
static SDL_Renderer *gRenderer = NULL;
static SDL_Event gEvent;

//INIT
void logSDLError(std::ostream &os,
                 const std::string &msg, bool fatal = false);
void initSDL(SDL_Window *&window, SDL_Renderer *&renderer);
void quitSDL(SDL_Window *window, SDL_Renderer *renderer);

//IMAGE------------------------------------------------------
SDL_Texture *loadTexture(const std::string &file, SDL_Renderer *renderer);


//MIXER------------------------------------------------------
Mix_Music *loadMusic(const std::string &file);
Mix_Chunk *loadSound(const std::string &file);
void playMusic(Mix_Music *Music);
void playSound(Mix_Chunk *sound);

#endif // SDL_FUNCTION_H


