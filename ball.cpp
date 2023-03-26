#include "ball.h"

Ball::Ball()
{
    x_pos = 0;
    y_pos = 0;
    x_change = 0;
    direction = 1;// chiều hướng sang trái, sang phải là 1
}
void Ball::setFrame_src(const std::string &file, SDL_Renderer *renderer)
{
    ball_.load(file, renderer);
    w_frame = ball_.destRect.w / 12;
    h_frame = ball_.destRect.h;
    for (int i = 0; i < 12; i++){
        frame_src[i].x = i * w_frame;
        frame_src[i].y = 0;
        frame_src[i].w = w_frame;
        frame_src[i].h = h_frame;
    }
    frame = 0;
    is_move = false;
}
void Ball::set_pos(const int &x,const int &y)
{
    x_pos = x;
    y_pos = y;
}
void Ball::renderFrame(SDL_Renderer *renderer, Map_ *map_)
{
    ball_.SetRect(BALL_WIDTH,BALL_HEIGHT,x_pos - map_->Mpos_x, y_pos);
    ball_.srcRect = frame_src[frame];
    ball_.renderTexture(renderer);
    if (is_move)
    {
        if (direction == -1){
            frame ++;
            if (frame >= 12) frame = 0;
        }
        else{
            frame--;
            if (frame < 0) frame = 11;
        }
    }
}
void Ball::Move(Map_ *map_)
{
    if (is_move)
    {
        if (direction == -1)
        {
            x_change = -BALL_SPEED;
        }
        else x_change = BALL_SPEED;

        x_pos += x_change;
        if ((x_pos < 0) || (x_pos + ball_.destRect.w > MAX_MAP_X * TILE_SIZE))
        {
            x_pos -= x_change;
            direction *= -1;
        }
        else if (Check_limited_Pos_X(map_))
        {
            direction *= -1;
        }
    }
}
bool Ball::Check_limited_Pos_X(Map_ *map_)
{
    int x_left = 0, x_right = 0;
    int y_down = 0, y_up = 0;

    x_left = (x_pos) / TILE_SIZE;
    x_right = (x_pos + ball_.destRect.w) / TILE_SIZE;
    y_down = (y_pos + ball_.destRect.h) / TILE_SIZE;
    y_up = y_pos / TILE_SIZE;
    if (y_down * TILE_SIZE - ball_.destRect.h == y_pos)
    {
        y_down -= 1;
    }
    if (x_left >= 0 && x_right <= MAX_MAP_X && y_up >= 0 && y_down <= MAX_MAP_Y)
    {
        if (x_change > 0) // di chuyển sang phải
        {
            if (map_->tileMap[y_up][x_right] > 0 || map_->tileMap[y_down][x_right] > 0 )
            {
                x_pos = x_right * TILE_SIZE - ball_.destRect.w;
                return true;
            }
        }
        else if (x_change < 0)
        {
            if (map_->tileMap[y_up][x_left] > 0 || map_->tileMap[y_down][x_left] > 0)
            {
                x_pos = (x_left + 1) * TILE_SIZE;
                return true;
            }
        }
    }
    return false;
}
