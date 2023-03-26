#include "setting.h"

std::string music_vol;
std::string sound_vol;

int Mvol = MIX_MAX_VOLUME;
int Svol = MIX_MAX_VOLUME;

int music_vol_bar_x;
int music_vol_bar_w;

int sound_vol_bar_x;
int sound_vol_bar_w;

Setting::Setting(SDL_Renderer *renderer)
{
    button.load("image/setting.png", renderer);
    button.SetRect(TILE_SIZE * 2, TILE_SIZE * 2, 0, SCREEN_HEIGHT * 3 / 4);
    text.Set_ptsize(50);
    text.SetColor(255,255,255);
    text.SetRect(button.destRect.w, button.destRect.w / 3, button.destRect.x, button.destRect.y + button.destRect.h);
    //button.SetRect(TILE_SIZE * 3 / 2 , TILE_SIZE * 3 / 2 , 0, 0);
    board.load("image/khung.png", renderer);
    board.SetRect(SCREEN_WIDTH / 2, SCREEN_WIDTH / 2, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 - SCREEN_WIDTH/4);
    //init funct
    icon[0].load("image/back.png", renderer);
    icon[0].SetRect(TILE_SIZE, TILE_SIZE, board.destRect.x + TILE_SIZE * 2, board.destRect.y + board.destRect.h - TILE_SIZE * 3);
    func[0].Set_ptsize(40);
    func[0].SetColor(32, 32, 32);
    func[0].SetRect(TILE_SIZE, TILE_SIZE / 2, icon[0].destRect.x, icon[0].destRect.y + icon[0].destRect.h);

    icon[1].load("image/close.png", renderer);
    icon[1].SetRect(TILE_SIZE, TILE_SIZE, board.destRect.x + board.destRect.w - TILE_SIZE * 3, board.destRect.y + board.destRect.h - TILE_SIZE * 3);
    func[1].Set_ptsize(40);
    func[1].SetColor(32, 32, 32);
    func[1].SetRect(TILE_SIZE, TILE_SIZE / 2, icon[1].destRect.x, icon[1].destRect.y + icon[1].destRect.h);

    icon[2].load("image/speaker.png", renderer);
    icon[2].SetRect(TILE_SIZE, TILE_SIZE, board.destRect.x + TILE_SIZE, board.destRect.y + TILE_SIZE * 2);
    func[2].Set_ptsize(40);
    func[2].SetColor(32, 32, 32);
    func[2].SetRect(TILE_SIZE, TILE_SIZE / 2, icon[2].destRect.x, icon[2].destRect.y + icon[2].destRect.h);

    icon[3].load("image/speaker1.png", renderer);
    icon[3].SetRect(TILE_SIZE, TILE_SIZE, board.destRect.x + TILE_SIZE, board.destRect.y + TILE_SIZE * 9 / 2);
    func[3].Set_ptsize(40);
    func[3].SetColor(32, 32, 32);
    func[3].SetRect(TILE_SIZE, TILE_SIZE / 2, icon[3].destRect.x, icon[3].destRect.y + icon[3].destRect.h);


    for (int i = 0; i < 2; i++){//[0][j] là đang xét ô ở ngoài [1][j] là ô ở trong
        for (int j = 0; j < 2; j++){
            filled_rects[i][j].x = icon[j+2].destRect.x + TILE_SIZE * 2 + i * TILE_SIZE / 8;
            filled_rects[i][j].y = icon[j+2].destRect.y + TILE_SIZE / 4 + i * TILE_SIZE / 8;
            filled_rects[i][j].w = 4 * TILE_SIZE - i * TILE_SIZE / 4;
            filled_rects[i][j].h = TILE_SIZE * 3 / 4 - i * TILE_SIZE / 4;
        }
        //âm lượng hiển thị ra
        volume[i].Set_ptsize(40);
        volume[i].SetColor(32, 32, 32);
        volume[i].SetRect(TILE_SIZE, TILE_SIZE / 2, filled_rects[0][i].x + filled_rects[0][i].w + TILE_SIZE / 2, filled_rects[0][i].y);
    }
    music_vol_bar_x = filled_rects[1][0].x;
    music_vol_bar_w = filled_rects[1][0].w;

    sound_vol_bar_x = filled_rects[1][1].x;
    sound_vol_bar_w = filled_rects[1][1].w;

    Ost = loadMusic("sound/ost1.mp3");
    Click = loadSound("sound/click.wav");
    Jump = loadSound("sound/jump.wav");
    Gameover = loadSound("sound/game_over.mp3");
    YouWin = loadSound("sound/win.mp3");
    state = false;
}
void Setting::handle_setting(SDL_Event e, bool &isRunning){

    if (e.type == SDL_MOUSEBUTTONUP){
        if (e.button.button == SDL_BUTTON_LEFT)
        {
            if (state){

                    // Check if the mouse is over the music volume bar
                    if (e.button.x >= music_vol_bar_x && e.button.x <= music_vol_bar_x + music_vol_bar_w &&
                        e.button.y >= filled_rects[1][0].y && e.button.y <= filled_rects[1][0].y + filled_rects[1][0].h) {
                        playSound(Click);// sound click
                        // Calculate the volume level based on the mouse position
                        Mvol = ((float)(e.button.x - music_vol_bar_x) / music_vol_bar_w) * MIX_MAX_VOLUME;
                        // Set the music volume using the set_music_volume() function
                        set_music_volume(Mvol);
                    }

                    // Check if the mouse is over the chunk volume bar
                    if (e.button.x >= sound_vol_bar_x && e.button.x <= sound_vol_bar_x + sound_vol_bar_w &&
                        e.button.y >= filled_rects[1][1].y && e.button.y <= filled_rects[1][1].y + filled_rects[1][1].h) {
                        playSound(Click);// sound click
                        // Calculate the volume level based on the mouse position
                        Svol = ((float)(e.button.x - sound_vol_bar_x) / sound_vol_bar_w) * MIX_MAX_VOLUME;
                        // Set the chunk volume using the set_chunk_volume() function
                        set_chunk_volume(Svol);
                    }
                for (int i=0;i<2;i++)
                {
                    if ((e.button.x >= icon[i].destRect.x && e.button.x <= icon[i].destRect.x + icon[i].destRect.w)
                        && (e.button.y >= icon[i].destRect.y && e.button.y <= icon[i].destRect.y + icon[i].destRect.h + func[i].rect.h))
                    {
                        if (i == 0){
                            text.SetColor(255,255,255);
                            state = false;
                        }
                        else isRunning = false;
                        playSound(Click);// sound click
                    }
                }

            }
            else
            {
                if ((e.button.x >= button.destRect.x && e.button.x <= button.destRect.x + button.destRect.w)
                    && (e.button.y >= button.destRect.y && e.button.y <= button.destRect.y + button.destRect.h + text.rect.h))
                {
                    state = true;
                    text.SetColor(255,51,51);
                    for (int i=0;i<3;i++){
                        func[i].SetColor(32, 32, 32);
                    }
                    playSound(Click);// sound click
                }
            }
        }
    }
    else if (e.type == SDL_MOUSEMOTION){
        if (state){
            for (int i=0; i<2; i++)
            {
                if ((e.motion.x >= icon[i].destRect.x && e.motion.x <= icon[i].destRect.x + icon[i].destRect.w)
                        && (e.motion.y >= icon[i].destRect.y && e.motion.y <= icon[i].destRect.y + icon[i].destRect.h + func[i].rect.h))
                    func[i].SetColor(255,51,51);
                else
                    func[i].SetColor(32,32,32);
            }
        }
        else {
            if ((e.motion.x >= button.destRect.x && e.motion.x <= button.destRect.x + button.destRect.w)
                    && (e.motion.y >= button.destRect.y && e.motion.y <= button.destRect.y + button.destRect.h + text.rect.h))
                text.SetColor(255,51,51);
            else
                text.SetColor(255,255,255);
        }
    }
    else if (e.type == SDL_MOUSEWHEEL) {
        if (state)
        {
            if(e.wheel.mouseX >= music_vol_bar_x && e.wheel.mouseX <= music_vol_bar_x + music_vol_bar_w &&
                e.wheel.mouseY >= filled_rects[1][0].y && e.wheel.mouseY <= filled_rects[1][0].y + filled_rects[1][0].h)
            {
                if (e.wheel.y > 0) {
                    // Scrolled up
                    if (Mvol < MIX_MAX_VOLUME) {
                        Mvol += 4;
                    }
                    else Mvol = MIX_MAX_VOLUME;
                    set_music_volume(Mvol);
                }
                else if (e.wheel.y < 0) {
                    // Scrolled down
                    if (Mvol > 0) {
                        Mvol -= 4;
                    }
                    else Mvol = 0;
                    set_music_volume(Mvol);
                }
            }
            if(e.wheel.mouseX >= sound_vol_bar_x && e.wheel.mouseX <= sound_vol_bar_x + sound_vol_bar_w &&
                e.wheel.mouseY >= filled_rects[1][1].y && e.wheel.mouseY <= filled_rects[1][1].y + filled_rects[1][1].h)
            {
                if (e.wheel.y > 0) {
                    // Scrolled up
                    if (Svol < MIX_MAX_VOLUME) {
                        Svol += 4;
                    }
                    else Svol = MIX_MAX_VOLUME;
                    set_chunk_volume(Svol);
                }
                else if (e.wheel.y < 0) {
                    // Scrolled down
                    if (Svol > 0) {
                        Svol -= 4;
                    }
                    else Svol = 0;
                    set_chunk_volume(Svol);
                }
            }
        }
    }
}

void Setting::show(SDL_Renderer *renderer){

    if (state){
        button.SetRect(TILE_SIZE, TILE_SIZE, SCREEN_WIDTH / 2 - TILE_SIZE / 2, board.destRect.y + TILE_SIZE / 2);
        board.renderTexture(renderer);
        button.renderTexture(renderer);
        func[0].load("font/Righteous-Regular.ttf","Back",renderer);
        func[1].load("font/Righteous-Regular.ttf","Close",renderer);
        func[2].load("font/Righteous-Regular.ttf","Music",renderer);
        func[3].load("font/Righteous-Regular.ttf","Sound",renderer);
        music_vol = std::to_string(Mvol*100/MIX_MAX_VOLUME) + "%";
        sound_vol = std::to_string(Svol*100/MIX_MAX_VOLUME) + "%";
        volume[0].load("font/Righteous-Regular.ttf",music_vol,renderer);
        volume[1].load("font/Righteous-Regular.ttf",sound_vol,renderer);
        for (int i = 0; i < 4; i++){
            icon[i].renderTexture(renderer);
            func[i].renderTexture(renderer);
        }
        volume[0].renderTexture(renderer);
        volume[1].renderTexture(renderer);

        filled_rects[1][0].w = music_vol_bar_w * Mvol / MIX_MAX_VOLUME;
        filled_rects[1][1].w = sound_vol_bar_w * Svol / MIX_MAX_VOLUME;

        SDL_SetRenderDrawColor(renderer, 119, 136, 153, 255);//xám
        SDL_RenderFillRects(renderer, filled_rects[0], 2);
        SDL_SetRenderDrawColor(renderer, 250, 193, 193, 255);//hồng
        SDL_RenderFillRects(renderer, filled_rects[1], 2);


    }
    else{
        button.renderTexture(renderer);
        text.load("font/Righteous-Regular.ttf","Setting",renderer);
        text.renderTexture(renderer);
    }
}

