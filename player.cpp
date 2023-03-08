#include "player.h"
player_state::player_state()
{
    stt_right = false;
    stt_left = false;
    stt_up = false;
    stt_down = false;
}
player::player()
{
    x_change = 0;
    y_change = 0;
    x_pos = 0;
    y_pos = 0;

    player_rect.x = 0;
    player_rect.y = 0;
    player_rect.w = CHARACTER_WIDTH;
    player_rect.h = CHARACTER_HEIGHT;
}
void player::load(const std::string &file, SDL_Renderer *renderer)
{
    mplayer = loadTexture(file, renderer);
    SDL_QueryTexture(mplayer, NULL, NULL,&w_frame,&h_frame);
}
void player::setFrame_src(const std::string &file, SDL_Renderer *renderer)
{
    load(file, renderer);
    w_frame /=7;
    h_frame /=6;
    for (int i=0; i<7; i++)
    {
        frame_src[i].x = i * w_frame;
        frame_src[i].y = 0;
        frame_src[i].w = w_frame;
        frame_src[i].h = h_frame;
    }
    frame = 0;

}
void player::Gravity()
{
    //x_change = 0;
    y_change += FREE_FALL;
    if (y_change >= MAX_FREE_FALL)
    {
        y_change = MAX_FREE_FALL;
    }
}
void player::InputEvent(SDL_Event e)
{
    if (e.type == SDL_KEYDOWN)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_RIGHT:
        {
            std::cout<<"move to the right"<<std::endl;
            current.stt_right = true;
            current.stt_left = false;
            current.stt_up = false;
            current.stt_down = false;
            x_change = PLAYER_SPEED;
        }
        break;
        case SDLK_LEFT:
        {
            std::cout<<"move to the left"<<std::endl;
            current.stt_right = false;
            current.stt_left = true;
            current.stt_up = false;
            current.stt_down = false;
            x_change = PLAYER_SPEED * -1;
        }
        break;
        case SDLK_DOWN:
        {
            std::cout<<"sit down"<<std::endl;
            current.stt_right = false;
            current.stt_left = false;
            current.stt_up = false;
            current.stt_down = true;
            //y_change = PLAYER_SPEED;
        }
        break;
        case SDLK_UP:
        {
            std::cout<<"jump"<<std::endl;
            current.stt_right = false;
            current.stt_left = false;
            current.stt_up = true;
            current.stt_down = false;
            y_change = JUMP_HIGH * -1;
        }
        break;
        }

    }
    else if (e.type == SDL_KEYUP)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_RIGHT:
        {
            current.stt_right = false;
            x_change = 0;
        }
        break;
        case SDLK_LEFT:
        {
            current.stt_left = false;
            x_change = 0;
        }
        break;
        case SDLK_DOWN:
        {
            current.stt_down = false;
            //y_change = 0;
        }
        break;
        case SDLK_UP:
        {
            current.stt_up = false;
            y_change = 0;
        }
        break;
        }

    }
}
void player::Check_limited_Pos(Map_ *map_)
{
    Gravity();
    int x_left = 0, x_right = 0;
    int y_down = 0, y_up = 0;

    x_left = (x_pos + x_change)/TILE_SIZE; // tọa độ để check nếu di chuyển sang trái
    x_right = (x_pos + player_rect.w + x_change)/TILE_SIZE; // tọa độ để check nếu di chuyển sang phải
    y_down = (y_pos + player_rect.h)/TILE_SIZE;
    y_up = y_pos / TILE_SIZE;
    if (y_up * TILE_SIZE == y_pos){
        y_down-=1;
    }//chỉ cần xét trường hợp y_up vì nếu bằng thì tọa độ y_up chính bằng tọa độ y của tile đang cần xét, và chỉ cần lấy down -1 vì chiều dài nhân vật bằng với tile_size
    if (x_left >= 0 && x_right <= MAX_MAP_X && y_up >= 0 && y_down <= MAX_MAP_Y)
    {
        if (x_change > 0)  // di chuyển sang phải
        {
                if (map_->tileMap[y_up][x_right] != BLANK_TILE || map_->tileMap[y_down][x_right] != BLANK_TILE) // check ô ngay sau ô x_right
                {
                    x_pos = x_right * TILE_SIZE - player_rect.w; // x_pos được gán cho tọa độ của ô x_right (ô đang xét) trừ đi phần chiều ngang của frame
                    x_change = 0;                                // điều này đảm bảo cứ đến ô nào mà check ô tiếp theo là khác blank thì sẽ tự điều chỉnh lượng x_change
                }
        }
        else if (x_change < 0)
        {
                if (map_->tileMap[y_up][x_left] != BLANK_TILE || map_->tileMap[y_down][x_left] != BLANK_TILE)
                {
                    x_pos = (x_left+1) * TILE_SIZE;
                    x_change = 0;
                }
        }
    }
    x_left = x_pos / TILE_SIZE; // tọa độ để check nếu di chuyển sang trái
    x_right = (x_pos + player_rect.w)/TILE_SIZE; // tọa độ để check nếu di chuyển sang phải
    y_down = (y_pos + player_rect.h + y_change)/TILE_SIZE;
    y_up = (y_pos + y_change) / TILE_SIZE;
    if (x_right * TILE_SIZE - player_rect.w == x_pos) x_right-=1;
    // do chiều rộng nhân vật nhỏ hơn tile_size
    if (x_left >= 0 && x_right <= MAX_MAP_X && y_up >= 0 && y_down <= MAX_MAP_Y)
    {
        if (y_change > 0)  // xuống
        {
            if (map_->tileMap[y_down][x_left] != BLANK_TILE || map_->tileMap[y_down][x_right] != BLANK_TILE)
            {
                y_pos = y_down * TILE_SIZE - player_rect.h;
                y_change = 0;
            }
        }
        else if (y_change < 0) // lên
        {
            if (map_->tileMap[y_up][x_left] != BLANK_TILE || map_->tileMap[y_up][x_right] != BLANK_TILE)
            {
                y_pos = (y_up+1) * TILE_SIZE;
                y_change = 0;
            }
        }
    }
    x_pos += x_change;
    y_pos += y_change;

    if (x_pos < 0) x_pos = 0;
    else if (x_pos > MAX_MAP_X * TILE_SIZE - player_rect.w) x_pos = MAX_MAP_X * TILE_SIZE - player_rect.w;
//    if (y_pos < 0) y_pos = 0;
//    else if (y_pos > MAX_MAP_Y * TILE_SIZE - player_rect.h) y_pos = MAX_MAP_Y * TILE_SIZE - player_rect.h;
}
void player::handleInput(Map_ *map_)
{
    Check_limited_Pos(map_);
    if (current.stt_right == true || current.stt_left == true
            || current.stt_up == true || current.stt_down == true)
    {
        frame++;
    }
    else frame = 0;
}
void player::renderFrame(SDL_Renderer *renderer)
{
    if (current.stt_right == true)
    {
        for (int i=0; i<6; i++)
        {
            frame_src[i].y = 2 * h_frame;
        }
        if (frame >= 6) frame = 0;
    }
    else if (current.stt_left == true)
    {
        for (int i=0; i<6; i++)
        {
            frame_src[i].y = 3* h_frame;
        }
        if (frame >= 6) frame = 0;
    }
    else if (current.stt_up == true)
    {
        for (int i=0; i<3; i++)
        {
            frame_src[i].y = 4*h_frame;
        }
        if (frame >=3) frame = 0;
    }
    else if (current.stt_down == true)
    {
        frame_src[0].y = 5*h_frame;
        frame_src[1].x = 0;
        frame_src[1].y = 0;
        if (frame >=2) frame = 0;
    }
    else
    {
        for (int i=0; i<7; i++)
        {
            frame_src[i].y = 0;
        }
        if (frame>=7) frame = 0;
    }
    player_rect.x = x_pos;
    player_rect.y = y_pos;
    SDL_RenderCopy(renderer, mplayer, &frame_src[frame],&player_rect);
}


