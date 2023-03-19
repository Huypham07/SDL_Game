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
    jump_valid = false;
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
    w_frame /=6;
    h_frame /=10;
    for (int i=0; i<6; i++)
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
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_RIGHT:
        {
            current.stt_right = true;
            x_change += PLAYER_SPEED;
            std::cout<<"move to the right"<<std::endl;
        }
        break;
        case SDLK_LEFT:
        {
            current.stt_left = true;
            x_change -= PLAYER_SPEED;
            std::cout<<"move to the left"<<std::endl;
        }
        break;
        case SDLK_DOWN:
        {
            if (jump_valid)
            {
                std::cout<<"sit down"<<std::endl;
                current.stt_down = true;
            }
        }
        break;
        case SDLK_SPACE:
        {
            if (jump_valid)
            {
                std::cout<<"jump"<<std::endl;
                current.stt_up = true;
                current.stt_down = false;
                y_change -= JUMP_HIGH;
                jump_valid = false;
            }
        }
        break;
        }

    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)// vật dịch chuyển ít hay nhiều là do keyup
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_RIGHT:
        {
            current.stt_right = false;
            x_change -= PLAYER_SPEED;
        }
        break;
        case SDLK_LEFT:
        {
            current.stt_left = false;
            x_change += PLAYER_SPEED;
        }
        break;
        case SDLK_DOWN:
        {
            current.stt_down = false;
        }
        break;
        case SDLK_SPACE:
        {
            current.stt_up = false;
            y_change += JUMP_HIGH;
        }
        break;
        }

    }
}
void player::Check_limited_Pos_X(Map_ *map_)
{
    int x_left = 0, x_right = 0;
    int y_down = 0, y_up = 0;

    x_left = (x_pos )/TILE_SIZE; // tọa độ để check nếu di chuyển sang trái
    x_right = (x_pos + player_rect.w )/TILE_SIZE; // tọa độ để check nếu di chuyển sang phải
    y_down = (y_pos + player_rect.h)/TILE_SIZE;
    y_up = y_pos / TILE_SIZE;
    if (y_down * TILE_SIZE - player_rect.h == y_pos)
    {
        y_down-=1;
    }//chỉ cần xét trường hợp y_up vì nếu bằng thì tọa độ y_up chính bằng tọa độ y của tile đang cần xét, và chỉ cần lấy down -1 vì chiều dài nhân vật bằng với tile_size
    if (x_left >= 0 && x_right <= MAX_MAP_X && y_up >= 0 && y_down <= MAX_MAP_Y)
    {
        if (x_change > 0)  // di chuyển sang phải
        {
            if ((map_->trap[y_up][x_right] == 1 && map_->tileMap[y_up][x_right] > 0)
                    || (map_->trap[y_down][x_right] == 1 && map_->tileMap[y_down][x_right] > 0)) // check ô ngay sau ô x_right
            {

                x_pos = x_right * TILE_SIZE - player_rect.w ; // x_pos được gán cho tọa độ của ô x_right (ô đang xét) trừ đi phần chiều ngang của frame
                // điều này đảm bảo cứ đến ô nào mà check ô tiếp theo là khác blank thì sẽ tự điều chỉnh lượng x_change
            }
        }
        else if (x_change < 0)
        {
            if ((map_->trap[y_up][x_left] == 1 && map_->tileMap[y_up][x_left] > 0)
                    || (map_->trap[y_down][x_left] == 1 && map_->tileMap[y_down][x_left] > 0))
            {
                x_pos = (x_left+1) * TILE_SIZE ;
            }
        }
    }
}
void player::Check_limited_Pos_Y(Map_ *map_)
{
    int x_left = 0, x_right = 0;
    int y_down = 0, y_up = 0;

    x_left = (x_pos ) / TILE_SIZE; // tọa độ để check nếu di chuyển sang trái
    x_right = (x_pos + player_rect.w )/TILE_SIZE; // tọa độ để check nếu di chuyển sang phải
    y_down = (y_pos + player_rect.h)/TILE_SIZE;
    y_up = (y_pos) / TILE_SIZE;
    if (x_right * TILE_SIZE - player_rect.w == x_pos) x_right-=1;
    // do chiều rộng nhân vật nhỏ hơn tile_size
    if (x_left >= 0 && x_right <= MAX_MAP_X && y_up >= 0 && y_down <= MAX_MAP_Y)
    {
        if (y_change > 0)  // xuống
        {
            if ((map_->trap[y_down][x_left] == 1 && map_->tileMap[y_down][x_left] > 0)
                    || (map_->trap[y_down][x_right] == 1 && map_->tileMap[y_down][x_right] > 0))
            {
                y_pos = y_down * TILE_SIZE - player_rect.h;
                jump_valid = true;
            }
        }
        else if (y_change < 0) // lên
        {
            if ((map_->trap[y_up][x_left] == 1 && map_->tileMap[y_up][x_left] > 0)
                    || (map_->trap[y_up][x_right] == 1 && map_->tileMap[y_up][x_right] > 0))
            {
                y_pos = (y_up+1) * TILE_SIZE;
            }
        }
    }
}
void player::handleInput(Map_ *map_)
{
    Gravity();
    x_pos += x_change;
    if ((x_pos < 0) || (x_pos + player_rect.w > MAX_MAP_X*TILE_SIZE))
    {
        x_pos -= x_change;
    }
    else Check_limited_Pos_X(map_);
    y_pos += y_change;
    if ((y_pos < 0) || (y_pos + player_rect.h > MAX_MAP_Y*TILE_SIZE))
    {
        y_pos -= y_change;
    }
    else Check_limited_Pos_Y(map_);
    map_->Mpos_x = x_pos - SCREEN_WIDTH/2;
    if (map_->Mpos_x < 0) map_->Mpos_x = 0;
    if (map_->Mpos_x + SCREEN_WIDTH > MAX_MAP_X * TILE_SIZE) map_->Mpos_x = MAX_MAP_X * TILE_SIZE - SCREEN_WIDTH;
    player_rect.x = x_pos - map_->Mpos_x;
    player_rect.y = y_pos;
}
void player::renderFrame(SDL_Renderer *renderer, Map_ *map_)
{
    if (current.stt_down== false && current.stt_up== false && current.stt_left == false && current.stt_right == false)
    {
        if (trap_checking(map_))
        {
            if ( frame_src[0].y == h_frame || frame_src[0].y == 3 * h_frame || frame_src[0].y == 5 * h_frame || frame_src[0].y == 7 * h_frame)
            {
                for (int i=0;i<6;i++){
                    frame_src[i].y = 9 * h_frame;
                }
            }
            else
            {
                for (int i=0;i<6;i++){
                    frame_src[i].y = 8 * h_frame;
                }
            }
        }
        else
        {
            if ( frame_src[0].y == h_frame || frame_src[0].y == 3 * h_frame || frame_src[0].y == 5 * h_frame || frame_src[0].y == 7 * h_frame)
            {
                if (jump_valid)
                {
                    for (int i=0; i< 6; i++)
                    {
                        frame_src[i].y = h_frame;
                    }
                }
                else
                {
                    for (int i=0; i< 6; i++)
                    {
                        frame_src[i].y = 5 * h_frame;
                    }
                }
            }
            else
            {
                if (jump_valid)
                {
                    for (int i=0; i< 6; i++)
                    {
                        frame_src[i].y = 0;
                    }
                }
                else
                {
                    for (int i=0; i< 6; i++)
                    {
                        frame_src[i].y = 4 * h_frame;
                    }
                }
            }

        }
    }
    else if (current.stt_right)
    {
        if (jump_valid)
        {
            for (int i=0; i<6; i++)
            {
                frame_src[i].y = 2 * h_frame;
            }
        }
        else
        {
            for (int i=0; i<6; i++)
            {
                frame_src[i].y = 4 * h_frame;
            }
        }
    }
    else if (current.stt_left)
    {
        if (jump_valid)
        {
            for (int i=0; i<6; i++)
            {
                frame_src[i].y = 3* h_frame;
            }
        }
        else
        {
            for (int i=0; i<6; i++)
            {
                frame_src[i].y = 5 * h_frame;
            }
        }
    }
    else if (current.stt_down)
    {
        if (frame_src[0].y == h_frame || frame_src[0].y == 3 * h_frame || frame_src[0].y == 7 * h_frame)
        {
            for (int i=0; i<6; i++)
            {
                frame_src[i].y = 7* h_frame;
            }
        }
        else
        {
            for (int i=0; i<6; i++)
            {
                frame_src[i].y = 6 * h_frame;
            }
        }
    }
    else if (current.stt_up)
    {
        if (frame_src[0].y == h_frame || frame_src[0].y == 3 * h_frame || frame_src[0].y == 5 * h_frame || frame_src[0].y == 7 * h_frame)
        {
            for (int i=0; i<6; i++)
            {
                frame_src[i].y = 5 * h_frame;
            }
        }
        else
        {
            for (int i=0; i<6; i++)
            {
                frame_src[i].y = 4 * h_frame;
            }
        }
    }
    if (frame >= 6) frame = 0;
    SDL_RenderCopy(renderer, mplayer, &frame_src[frame],&player_rect);
    frame++;
}
bool player::trap_checking(Map_ *map_)
{
    int x_left = 0, x_right = 0;
    int y_down = 0, y_up = 0;

    x_left = (x_pos )/TILE_SIZE;
    x_right = (x_pos + player_rect.w )/TILE_SIZE;
    y_down = (y_pos + player_rect.h)/TILE_SIZE;
    y_up = y_pos / TILE_SIZE;

    //check phai
    if ((map_->tileMap[y_up][x_right] == 2 && map_->trap[y_up][x_right] == 1) ||
            (map_->tileMap[y_down][x_right] == 2 && map_->trap[y_down][x_right] == 1))
    {
        if (x_right * TILE_SIZE <= x_pos + player_rect.w)
        {
            x_change = 0;
            y_change = 0;
            current.stt_up = false;
            current.stt_right = false;
            current.stt_left = false;
            current.stt_down = false;
            return true;
        }
    }
    //check trai
    if ((map_->tileMap[y_up][x_left-1] == 2 && map_->trap[y_up][x_left-1] == 1) ||
            (map_->tileMap[y_down][x_left-1] == 2 && map_->trap[y_down][x_left-1] == 1))
    {
        if (x_left * TILE_SIZE >= x_pos)
        {
            x_change = 0;
            y_change = 0;
            current.stt_up = false;
            current.stt_right = false;
            current.stt_left = false;
            current.stt_down = false;
            return true;
        }
    }
    //check tren
    if ((map_->tileMap[y_up-1][x_left] == 2 && map_->trap[y_up-1][x_left] == 1) ||
            (map_->tileMap[y_up-1][x_right] == 2 && map_->trap[y_up-1][x_right] == 1))
    {
        if (y_up * TILE_SIZE >= y_pos)
        {
            x_change = 0;
            y_change = 0;
            current.stt_up = false;
            current.stt_right = false;
            current.stt_left = false;
            current.stt_down = false;
            return true;
        }
    }
    //check dưới
    if ((map_->tileMap[y_down][x_left] == 2 && map_->trap[y_down][x_left] == 1) ||
            (map_->tileMap[y_down][x_right] == 2 && map_->trap[y_down][x_right] == 1))
    {
        if (y_down * TILE_SIZE <= y_pos + player_rect.h)
        {
            x_change = 0;
            y_change = 0;
            current.stt_up = false;
            current.stt_right = false;
            current.stt_left = false;
            current.stt_down = false;
            return true;
        }
    }
    return false;
}
bool player::WinState(Map_ *map_)
{
    if (player_rect.x + player_rect.w > map_->Win_flag.destRect.x)
    {
        x_change = 0;
        y_change = 0;
        current.stt_up = false;
        current.stt_right = false;
        current.stt_left = false;
        current.stt_down = false;
        return true;
    }
    return false;
}
void player::Restart(){
    x_pos = 0;
    y_pos = 0;
}
