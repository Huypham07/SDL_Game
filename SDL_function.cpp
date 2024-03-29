#include "SDL_function.h"

void logSDLError(std::ostream &os, const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal)
    {
        SDL_Quit();
        exit(1);
    }
}
void initSDL(SDL_Window *&window, SDL_Renderer *&renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    // Initialize SDL_image
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if ((IMG_Init(imgFlags) & imgFlags) != imgFlags)
        logSDLError(std::cout, "IMG_Init", true);

    // Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        logSDLError(std::cout, "Mix_OpenAudio", true);

    // Initialize SDL_ttf
    if (TTF_Init() == -1)
    {
        printf("TTF_Init() failed: %s\n", TTF_GetError());
    }

    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr)
        logSDLError(std::cout, "CreateWindow", true);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
        logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}
void quitSDL(SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
// IMAGE------------------------------------------------------
SDL_Texture *loadTexture(const std::string &file, SDL_Renderer *renderer)
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
    return texture;
}
//-----------------------------------------------------------------------------------------
Mix_Music *loadMusic(const std::string &file)
{
    Mix_Music *music = nullptr;
    music = Mix_LoadMUS(file.c_str());
    if (music == nullptr)
    {
        logSDLError(std::cout, "MIX_LoadMUS", true);
    }
    return music;
}
Mix_Chunk *loadSound(const std::string &file)
{
    Mix_Chunk *sound = nullptr;
    sound = Mix_LoadWAV(file.c_str());
    if (sound == nullptr)
    {
        logSDLError(std::cout, "MIX_LoadMUS", true);
    }
    return sound;
}
void playMusic(Mix_Music *music)
{
    if (Mix_PlayingMusic() == 0)
    {
        // Play the music
        Mix_PlayMusic(music, -1);
    }
    // If music is being played
    else
    {
        // If the music is paused
        if (Mix_PausedMusic() == 1)
        {
            // Resume the music
            Mix_ResumeMusic();
        }
        // If the music is playing
        else
        {
            // Pause the music
            Mix_PauseMusic();
        }
    }
}
void playSound(Mix_Chunk *sound)
{
    Mix_PlayChannel(-1, sound, 0);
}
//-------------------------------------------------------------------
SDL_Texture *loadFont(const std::string &file, const std::string &text, SDL_Color textColor, const int ptsize, SDL_Renderer *renderer)
{
    SDL_Texture *texture = nullptr;
    // Open the font
    TTF_Font *gFont = TTF_OpenFont(file.c_str(), ptsize);
    if (gFont == nullptr)
    {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
    }
    else
    {
        // Render text

        SDL_Surface *textSurface = TTF_RenderText_Solid(gFont, text.c_str(), textColor);
        if (textSurface == nullptr)
        {
            printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        }
        else
        {
            // Create texture from surface pixels
            texture = SDL_CreateTextureFromSurface(renderer, textSurface);
            if (texture == nullptr)
            {
                logSDLError(std::cout, "CreateTextureFromSurface", true);
            }
            // Get rid of old surface
            SDL_FreeSurface(textSurface);
        }
    }
    return texture;
}
