#ifndef PLAYER_H
#define PLAYER_H

#include "base_object.h"
#include "map.h"

struct input
{
    int right;
    int left;
    int up;
    int down;
};
struct player_state
{
    bool stt_right;
    bool stt_left;
    bool stt_up;
    bool stt_down;

    player_state();
};
struct player
{

    SDL_Texture *mplayer;
    float x_pos;
    float y_pos;

    float x_change;
    float y_change;

    int w_frame;
    int h_frame;
    player_state current;
    input input_type;
    SDL_Rect player_rect;
    SDL_Rect frame_src[7];
    int frame;
    player();
    void load(const std::string &file,SDL_Renderer *renderer);
    void setFrame_src(const std::string &file, SDL_Renderer *renderer);
    void Gravity();
    void InputEvent(SDL_Event e);
    void Check_limited_Pos(Map_ *map_);
    void handleInput(Map_ *map_);
    void renderFrame(SDL_Renderer *renderer);

    /*
    CHANGE SOME THING WITH X,Y_CHANGE;
    ----------------
    x,y_pos+=x,y_change;
    void check_limited_Pos: (thực chất là kiểm tra vị trí update sau khi handle input, xử lý vị trí mới đó với 2 tọa độ biến x,y 1-2)

         khai báo ra 2 tọa độ đầu của frame in ra mà hình chiếm: x1,y1 x2,y2
         x2 = x1+frame.dest.w
         nếu như di chuyển sang 2 bên mà gặp ô tilemap[i][j] thì chặn lại-> khi đó x,y_change = 0;
            -> xet theo tọa độ ô của mảng 2 chiều map**
            để xét tọa độ va chạm thì

    player_rect.x = x_pos;
    player_rect.y = y_pos;  (*)

    renderFrame()-> rendercopy(mplayer, renderer, &frame_src[i], &player_rect)
                                                                    -> updated by(*)
        */
};
#endif // PLAYER_H
