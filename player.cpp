#include "player.h"
status::status(){
    stt_right = false;
    stt_left = false;
    stt_up = false;
    stt_down = false;
}
player::player(){
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
void player::setFrame_src(const std::string &file, SDL_Renderer *renderer){
    load(file, renderer);
    w_frame /=7;
    h_frame /=6;
    for (int i=0;i<7;i++){
        frame_src[i].x = i * w_frame;
        frame_src[i].y = 0;
        frame_src[i].w = w_frame;
        frame_src[i].h = h_frame;
    }
    frame = 0;

}
void player::InputEvent(SDL_Event e){
    if (e.type == SDL_KEYDOWN){
        switch (e.key.keysym.sym)
        {
        case SDLK_RIGHT:
            {
                std::cout<<"move to the right"<<std::endl;
                current.stt_right = true;
                current.stt_left = false;
                current.stt_up = false;
                current.stt_down = false;
                input_type.right = 1;
            }
            break;
        case SDLK_LEFT:
            {
                std::cout<<"move to the left"<<std::endl;
                current.stt_right = false;
                current.stt_left = true;
                current.stt_up = false;
                current.stt_down = false;
                input_type.left = 1;
            }
            break;
        case SDLK_DOWN:
            {
                std::cout<<"sit down"<<std::endl;
                current.stt_right = false;
                current.stt_left = false;
                current.stt_up = false;
                current.stt_down = true;
                input_type.down = 1;
            }
            break;
        case SDLK_UP:
            {
                std::cout<<"jump"<<std::endl;
                current.stt_right = false;
                current.stt_left = false;
                current.stt_up = true;
                current.stt_down = false;
                input_type.up = 1;
            }
            break;
        }

    }
    else if (e.type == SDL_KEYUP){
//                switch (e.key.keysym.sym)
//        {
//        case SDLK_RIGHT:
//            {
//                current.stt_right = false;
//                input_type.right = 0;
//            }
//            break;
//        case SDLK_LEFT:
//            {
//                current.stt_left = false;
//                input_type.left = 0;
//            }
//            break;
//        case SDLK_DOWN:
//            {
//                current.stt_down = false;
//                input_type.down = 0;
//            }
//            break;
//        case SDLK_UP:
//            {
//                current.stt_up = false;
//                input_type.up = 0;
//            }
//            break;
//        }

    }
}
void player::handleInput(){
    if (current.stt_right == true || current.stt_left == true
        || current.stt_up == true || current.stt_down == true){
            frame++;
        }
    else frame = 0;
}
void player::renderFrame(SDL_Renderer *renderer){
    if (current.stt_right == true){
        for (int i=0;i<6;i++){
            frame_src[i].y = 2 * h_frame;
        }
        if (frame >= 6) frame = 0;
    }
    else if (current.stt_left == true){
        for (int i=0;i<6;i++){
            frame_src[i].y = 3* h_frame;
        }
        if (frame >= 6) frame = 0;
    }
    else if (current.stt_up == true){
        for (int i=0;i<3;i++){
            frame_src[i].y = 4*h_frame;
        }
        if (frame >=3) frame = 0;
    }
    else if (current.stt_down == true){
        frame_src[0].y = 5*h_frame;
        frame_src[1].x = 0;
        frame_src[1].y = 0;
        if (frame >=2) frame = 0;
    }
    else {
        for (int i=0;i<7;i++){
            frame_src[i].y = 0;
        }
        if (frame>=7) frame = 0;
    }
   // if (frame >= 7) frame = 0;
    SDL_RenderCopy(renderer, mplayer, &frame_src[frame],&player_rect);
}
