#ifndef SETTING_H_INCLUDED
#define SETTING_H_INCLUDED

#include "img_object.h"
#include "text_font.h"

struct Setting
{
    ImgObject button;
    text_font text;
    ImgObject board;
    ImgObject icon[4];
    text_font func[4];
    /*
    0: back
    1: save
    2: close app
    3: music volume
    4: sound volume
    */
    text_font volume[2];
    SDL_Rect filled_rects[2][2];
    Mix_Music *Ost;
    Mix_Chunk *Click;
    Mix_Chunk *Jump;
    Mix_Chunk *Gameover;
    Mix_Chunk *YouWin;
    bool state;
    Setting(SDL_Renderer *renderer);
    void show(SDL_Renderer *renderer);
    void handle_setting(SDL_Event e, bool &isRunning);
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
