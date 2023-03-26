#include "player.h"
player_state::player_state()
{
    stt_right = false;
    stt_left = false;
    stt_up = false;
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

    die = false;
    // sound
    pJump = NULL;
}

void player::setFrame_src(const std::string &file, SDL_Renderer *renderer)
{
    mplayer = loadTexture(file, renderer);
    SDL_QueryTexture(mplayer, NULL, NULL, &w_frame, &h_frame);
    w_frame /= 6;
    h_frame /= 8;
    for (int i = 0; i < 6; i++)
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
            std::cout << "move to the right" << std::endl;
        }
        break;
        case SDLK_LEFT:
        {
            current.stt_left = true;
            x_change -= PLAYER_SPEED;
            std::cout << "move to the left" << std::endl;
        }
        break;
        case SDLK_SPACE:
        {
            if (jump_valid)
            {
                std::cout << "jump" << std::endl;
                current.stt_up = true;
                y_change -= JUMP_HIGH;
                jump_valid = false;
                playSound(pJump);
            }
        }
        break;
        }
    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0) // vật dịch chuyển ít hay nhiều là do keyup
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
        case SDLK_SPACE:
        {
            current.stt_up = false;
            y_change += JUMP_HIGH;
        }
        break;
        }
    }
}
bool player::check_index_trap(const int index)
{
    if (index == 2 || index == 4 || index == 7) return true;
    return false;
}
void player::Check_limited_Pos_X(Map_ *map_)
{
    int x_left = 0, x_right = 0;
    int y_down = 0, y_up = 0;

    x_left = (x_pos) / TILE_SIZE;                  // tọa độ để check nếu di chuyển sang trái
    x_right = (x_pos + player_rect.w) / TILE_SIZE; // tọa độ để check nếu di chuyển sang phải
    y_down = (y_pos + player_rect.h) / TILE_SIZE;
    y_up = y_pos / TILE_SIZE;
    if (y_down * TILE_SIZE - player_rect.h == y_pos)
    {
        y_down -= 1;
    } // chỉ cần xét trường hợp y_up vì nếu bằng thì tọa độ y_up chính bằng tọa độ y của tile đang cần xét, và chỉ cần lấy down -1 vì chiều dài nhân vật bằng với tile_size
    if (x_left >= 0 && x_right <= MAX_MAP_X && y_up >= 0 && y_down <= MAX_MAP_Y)
    {
        if (x_change > 0) // di chuyển sang phải
        {
            if ((map_->trap[y_up][x_right] == 1 && map_->tileMap[y_up][x_right] > 0 && !check_index_trap(map_->tileMap[y_up][x_right]))
                || (map_->trap[y_down][x_right] == 1 && map_->tileMap[y_down][x_right] > 0 && !check_index_trap(map_->tileMap[y_down][x_right]))) // check ô ngay sau ô x_right
            {
                x_pos = x_right * TILE_SIZE - player_rect.w; // x_pos được gán cho tọa độ của ô x_right (ô đang xét) trừ đi phần chiều ngang của frame
                // điều này đảm bảo cứ đến ô nào mà check ô tiếp theo là khác blank thì sẽ tự điều chỉnh lượng x_change
            }
        }
        else if (x_change < 0)
        {
            if ((map_->trap[y_up][x_left] == 1 && map_->tileMap[y_up][x_left] > 0 && !check_index_trap(map_->tileMap[y_up][x_left]))
                || (map_->trap[y_down][x_left] == 1 && map_->tileMap[y_down][x_left] > 0 && !check_index_trap(map_->tileMap[y_down][x_left])))
            {
                x_pos = (x_left + 1) * TILE_SIZE;
            }
        }
    }
}
void player::Check_limited_Pos_Y(Map_ *map_)
{
    int x_left = 0, x_right = 0;
    int y_down = 0, y_up = 0;

    x_left = (x_pos) / TILE_SIZE;                  // tọa độ để check nếu di chuyển sang trái
    x_right = (x_pos + player_rect.w) / TILE_SIZE; // tọa độ để check nếu di chuyển sang phải
    y_down = (y_pos + player_rect.h) / TILE_SIZE;
    y_up = (y_pos) / TILE_SIZE;
    if (x_right * TILE_SIZE - player_rect.w == x_pos)
        x_right -= 1;
    // do chiều rộng nhân vật nhỏ hơn tile_size
    if (x_left >= 0 && x_right <= MAX_MAP_X && y_up >= 0 && y_down <= MAX_MAP_Y)
    {
        if (y_change > 0) // xuống
        {
            if ((map_->trap[y_down][x_left] == 1 && map_->tileMap[y_down][x_left] > 0 && !check_index_trap(map_->tileMap[y_down][x_left]))
                || (map_->trap[y_down][x_right] == 1 && map_->tileMap[y_down][x_right] > 0 && !check_index_trap(map_->tileMap[y_down][x_right])))
            {
                        y_pos = y_down * TILE_SIZE - player_rect.h;
                        jump_valid = true;
            }
        }
        else if (y_change < 0) // lên
        {
            if ((map_->trap[y_up][x_left] == 1 && map_->tileMap[y_up][x_left] > 0 && !check_index_trap(map_->tileMap[y_up][x_left]))
                || (map_->trap[y_up][x_right] == 1 && map_->tileMap[y_up][x_right] > 0 && !check_index_trap(map_->tileMap[y_up][x_right])))
            {
                        y_pos = (y_up + 1) * TILE_SIZE;
            }
        }
    }
}
void player::handleInput(Map_ *map_)
{
    if (!die)
        Gravity();
    x_pos += x_change;
    if ((x_pos < 0) || (x_pos + player_rect.w > MAX_MAP_X * TILE_SIZE))
    {
        x_pos -= x_change;
    }
    else
        Check_limited_Pos_X(map_);
    y_pos += y_change;
    if ((y_pos < 0) || (y_pos + player_rect.h > MAX_MAP_Y * TILE_SIZE))
    {
        y_pos -= y_change;
    }
    else
        Check_limited_Pos_Y(map_);

    map_->Mpos_x = x_pos - SCREEN_WIDTH / 2;
    if (map_->Mpos_x < 0)
        map_->Mpos_x = 0;
    if (map_->Mpos_x + SCREEN_WIDTH > MAX_MAP_X * TILE_SIZE)
        map_->Mpos_x = MAX_MAP_X * TILE_SIZE - SCREEN_WIDTH;
    player_rect.x = x_pos - map_->Mpos_x;
    player_rect.y = y_pos;
}
void player::renderFrame(SDL_Renderer *renderer, Map_ *map_)
{
    if (current.stt_up == false && current.stt_left == false && current.stt_right == false)
    {
        if (die)
        {
            if (frame_src[0].y == h_frame || frame_src[0].y == 3 * h_frame || frame_src[0].y == 5 * h_frame || frame_src[0].y == 7 * h_frame)
            {
                for (int i = 0; i < 6; i++)
                {
                    frame_src[i].y = 7 * h_frame;
                }
            }
            else
            {
                for (int i = 0; i < 6; i++)
                {
                    frame_src[i].y = 6 * h_frame;
                }
            }
        }
        else
        {
            if (frame_src[0].y == h_frame || frame_src[0].y == 3 * h_frame || frame_src[0].y == 5 * h_frame)
            {
                if (jump_valid)
                {
                    for (int i = 0; i < 6; i++)
                    {
                        frame_src[i].y = h_frame;
                    }
                }
                else
                {
                    for (int i = 0; i < 6; i++)
                    {
                        frame_src[i].y = 5 * h_frame;
                    }
                }
            }
            else
            {
                if (jump_valid)
                {
                    for (int i = 0; i < 6; i++)
                    {
                        frame_src[i].y = 0;
                    }
                }
                else
                {
                    for (int i = 0; i < 6; i++)
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
            for (int i = 0; i < 6; i++)
            {
                frame_src[i].y = 2 * h_frame;
            }
        }
        else
        {
            for (int i = 0; i < 6; i++)
            {
                frame_src[i].y = 4 * h_frame;
            }
        }
    }
    else if (current.stt_left)
    {
        if (jump_valid)
        {
            for (int i = 0; i < 6; i++)
            {
                frame_src[i].y = 3 * h_frame;
            }
        }
        else
        {
            for (int i = 0; i < 6; i++)
            {
                frame_src[i].y = 5 * h_frame;
            }
        }
    }
    else if (current.stt_up)
    {
        if (frame_src[0].y == h_frame || frame_src[0].y == 3 * h_frame || frame_src[0].y == 5 * h_frame)
        {
            for (int i = 0; i < 6; i++)
            {
                frame_src[i].y = 5 * h_frame;
            }
        }
        else
        {
            for (int i = 0; i < 6; i++)
            {
                frame_src[i].y = 4 * h_frame;
            }
        }
    }

    SDL_RenderCopy(renderer, mplayer, &frame_src[frame], &player_rect);
    frame++;
    if (frame >= 6)
        frame = 0;
}
void player::trap_checking(Map_ *map_)
{
    int x_left = 0, x_right = 0;
    int y_down = 0, y_up = 0;

    x_left = (x_pos) / TILE_SIZE;
    x_right = (x_pos + player_rect.w) / TILE_SIZE;
    y_down = (y_pos + player_rect.h) / TILE_SIZE;
    y_up = y_pos / TILE_SIZE;
    // check trên-phải, trái
    if (check_index_trap(map_->tileMap[y_up][x_left]))
    {
        if (((y_up + 1) * TILE_SIZE >= y_pos) && ((x_left + 1) * TILE_SIZE >= x_pos + 5))
        {
            if (map_->trap[y_up][x_left] == 0) //check hint trap
                map_->trap[y_up][x_left] = 1;
            stopGame();
        }
    }
    if (check_index_trap(map_->tileMap[y_up][x_right]))
    {
        if (((y_up + 1) * TILE_SIZE >= y_pos) && (x_right * TILE_SIZE <= x_pos + player_rect.w - 5))
        {
            if (map_->trap[y_up][x_right] == 0)
                map_->trap[y_up][x_right] = 1;
            stopGame();
        }
    }

    // check dưới-phải, trái
    if (check_index_trap(map_->tileMap[y_down][x_left]))
    {
        if ((y_down * TILE_SIZE <= y_pos + player_rect.h) && ((x_left + 1) * TILE_SIZE >= x_pos + 5))
        {
            if (map_->trap[y_down][x_left] == 0)
                map_->trap[y_down][x_left] = 1;
            stopGame();
        }
    }
    if (check_index_trap(map_->tileMap[y_down][x_right]))
    {
        if ((y_down * TILE_SIZE <= y_pos + player_rect.h) && (x_right * TILE_SIZE <= x_pos + player_rect.w - 5))
        {
            if (map_->trap[y_down][x_right] == 0)
                map_->trap[y_down][x_right] = 1;
            stopGame();
        }
    }
}
bool player::WinState(Map_ *map_)
{
    if (player_rect.x + player_rect.w > map_->Win_flag.destRect.x)
    {
        stopGame();
        return true;
    }
    return false;
}
void player::Restart()
{
    x_pos = 0;
    y_pos = 0;
    die = false;
}
void player::stopGame()
{
    x_change = 0;
    y_change = 0;
    current.stt_up = false;
    current.stt_right = false;
    current.stt_left = false;
    die = true;
}
