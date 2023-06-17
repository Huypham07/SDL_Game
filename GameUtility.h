#ifndef SETTING_H_INCLUDED
#define SETTING_H_INCLUDED

#include "img_object.h"
#include "text_font.h"

struct GameUtility
{
    //setting
    ImgObject button;
    text_font setting;
    ImgObject board;
    ImgObject icon[4];
    text_font func[4];
    text_font volume[2];
    SDL_Rect filled_rects[2][2];
    Mix_Music *Ost;
    Mix_Chunk *Click;
    Mix_Chunk *Jump;
    Mix_Chunk *Gameover;
    Mix_Chunk *YouWin;
    bool is_open_setting;
    //util
    bool is_close_util;
    bool is_Gameover;
    bool is_Win;
    ImgObject GameOver;
    ImgObject WinGame;
    text_font play_again;

    ImgObject layer_welc;
    ImgObject start_but;
    ImgObject Tutorial;
    text_font start;

    GameUtility(SDL_Renderer *renderer);
    void handle_setting(SDL_Event e, bool &isRunning, SDL_Renderer* renderer);
    void update_event(SDL_Event e, bool &isRunning, bool& is_start, SDL_Renderer* renderer);
    void move_down(SDL_Renderer* renderer);
    void show(SDL_Renderer *renderer);

        // Function to control the volume of Mix_Music object
    void set_music_volume(int volume) {
        // Set the volume of Mix_Music object
        Mix_VolumeMusic(volume);
    }
        // Function to control the volume of Mix_Chunk objects
    void set_chunk_volume(int volume) {
        // Set the volume of each Mix_Chunk object
        Mix_VolumeChunk(Click, volume);
        Mix_VolumeChunk(Jump, volume);
        Mix_VolumeChunk(Gameover, volume);
        Mix_VolumeChunk(YouWin, volume);
    }

};
#endif // SETTING_H_INCLUDED
