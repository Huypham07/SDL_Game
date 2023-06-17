#include "GameUtility.h"

std::string music_vol;
std::string sound_vol;
int Mvol_before = 0;
int Svol_before = 0;
int Mvol = MIX_MAX_VOLUME;
int Svol = MIX_MAX_VOLUME;

int music_vol_bar_x;
int music_vol_bar_w;

int sound_vol_bar_x;
int sound_vol_bar_w;

int repeat_sound = 0;

int y_fall = -SCREEN_HEIGHT;

bool red_1 = false;
bool red_2 = false;
bool red_f[2] = {false, false};
GameUtility::GameUtility(SDL_Renderer *renderer)
{
    button.load("image/setting.png", renderer);
    button.SetRect(TILE_SIZE * 2, TILE_SIZE * 2, 0, SCREEN_HEIGHT * 3 / 4);
    setting.Set_ptsize(50);
    setting.SetColor(255,255,255);
    setting.SetRect(button.destRect.w, button.destRect.w / 3, button.destRect.x, button.destRect.y + button.destRect.h);
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
    func[2].load("font/Righteous-Regular.ttf","Music",renderer);

    icon[3].load("image/speaker1.png", renderer);
    icon[3].SetRect(TILE_SIZE, TILE_SIZE, board.destRect.x + TILE_SIZE, board.destRect.y + TILE_SIZE * 9 / 2);
    func[3].Set_ptsize(40);
    func[3].SetColor(32, 32, 32);
    func[3].SetRect(TILE_SIZE, TILE_SIZE / 2, icon[3].destRect.x, icon[3].destRect.y + icon[3].destRect.h);
    func[3].load("font/Righteous-Regular.ttf","Sound",renderer);


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

    GameOver.load("image/GameOver.png", renderer);
    GameOver.SetRect(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
    is_Gameover = false;

    WinGame.load("image/Win.png",renderer);
    WinGame.SetRect(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
    is_Win = false;

    play_again.Set_ptsize(100);
    play_again.SetColor(255, 204, 153);
    play_again.SetRect(SCREEN_WIDTH * 4 / 5, TILE_SIZE, SCREEN_WIDTH / 2 - SCREEN_WIDTH * 4 / 10, SCREEN_HEIGHT / 2 + TILE_SIZE);
    play_again.load("font/PermanentMarker-Regular.ttf", "Click  anywhere  to  return  to  the  Start  Page !", renderer);

    layer_welc.load("image/welcome.png", renderer);
    layer_welc.SetRect(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
    start_but.load("image/START.png", renderer);
    start_but.SetRect(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 5, SCREEN_WIDTH / 3 - 2 * TILE_SIZE, SCREEN_HEIGHT * 3 / 4);
    start.Set_ptsize(100);
    start.SetColor(255,255,255);
    start.SetRect(start_but.destRect.w * 4 / 5, start_but.destRect.h * 4 / 5,
                 SCREEN_WIDTH / 2 - start_but.destRect.w * 2 / 5 - 2 * TILE_SIZE, start_but.destRect.y + start_but.destRect.h / 10);
    start.load("font/PermanentMarker-Regular.ttf", "START !!!", renderer);
    Tutorial.load("image/tutor.png", renderer);
    Tutorial.SetRect(6 * TILE_SIZE, 3 * TILE_SIZE, SCREEN_WIDTH - 7 * TILE_SIZE, SCREEN_HEIGHT - 3 * TILE_SIZE);

    is_open_setting = false;
    is_close_util = false;
}
void GameUtility::handle_setting(SDL_Event e, bool &isRunning, SDL_Renderer* renderer){
    if (e.type == SDL_MOUSEBUTTONUP){
        if (e.button.button == SDL_BUTTON_LEFT)
        {
            if (is_open_setting){
                    // Check nếu như chuột ở thanh music
                    if (e.button.x >= music_vol_bar_x && e.button.x <= music_vol_bar_x + music_vol_bar_w &&
                        e.button.y >= filled_rects[1][0].y && e.button.y <= filled_rects[1][0].y + filled_rects[1][0].h) {
                        playSound(Click);// sound click
                        // Tính toán âm lượng dựa trên vị trí của chuột
                        Mvol_before = Mvol;
                        Mvol = ((float)(e.button.x - music_vol_bar_x) / music_vol_bar_w) * MIX_MAX_VOLUME;
                        // Đặt lại âm lượng bằng hàm đã định nghĩa
                        set_music_volume(Mvol);
                    }
                    // Check nếu như chuột ở thanh sound
                    if (e.button.x >= sound_vol_bar_x && e.button.x <= sound_vol_bar_x + sound_vol_bar_w &&
                        e.button.y >= filled_rects[1][1].y && e.button.y <= filled_rects[1][1].y + filled_rects[1][1].h) {
                        playSound(Click);// sound click
                        // Tính toán âm lượng dựa trên vị trí của chuột
                        Svol_before = Svol;
                        Svol = ((float)(e.button.x - sound_vol_bar_x) / sound_vol_bar_w) * MIX_MAX_VOLUME;
                        // Đặt lại âm lượng bằng hàm đã định nghĩa
                        set_chunk_volume(Svol);
                    }
                for (int i=0;i<2;i++)
                {
                    if ((e.button.x >= icon[i].destRect.x && e.button.x <= icon[i].destRect.x + icon[i].destRect.w)
                        && (e.button.y >= icon[i].destRect.y && e.button.y <= icon[i].destRect.y + icon[i].destRect.h + func[i].rect.h))
                    {
                        if (i == 0){
                            if (red_2){
                                setting.SetColor(255,255,255);
                                setting.load("font/Righteous-Regular.ttf","Setting",renderer);
                                red_2 = false;
                            }

                            is_open_setting = false;
                        }
                        else isRunning = false;
                        playSound(Click);// sound click
                    }
                }
            }
            else
            {
                if ((e.button.x >= button.destRect.x && e.button.x <= button.destRect.x + button.destRect.w)
                    && (e.button.y >= button.destRect.y && e.button.y <= button.destRect.y + button.destRect.h + setting.rect.h))
                {
                    is_open_setting = true;
                    setting.SetColor(255, 106, 106);
                    setting.load("font/Righteous-Regular.ttf","Setting",renderer);
                    red_2 = true;
                    for (int i=0;i<2;i++){
                        func[i].SetColor(32, 32, 32);
                    }
                    func[0].load("font/Righteous-Regular.ttf","Back",renderer);
                    func[1].load("font/Righteous-Regular.ttf","Close",renderer);
                    playSound(Click);// sound click
                }
            }
        }
    }
    else if (e.type == SDL_MOUSEMOTION){
        if (is_open_setting){
            for (int i=0; i<2; i++)
            {
                if ((e.motion.x >= icon[i].destRect.x && e.motion.x <= icon[i].destRect.x + icon[i].destRect.w)
                        && (e.motion.y >= icon[i].destRect.y && e.motion.y <= icon[i].destRect.y + icon[i].destRect.h + func[i].rect.h))
                        {
                            if (!red_f[i]){
                                func[i].SetColor(255, 106, 106);
                                if (i==0) func[i].load("font/Righteous-Regular.ttf","Back",renderer);
                                else func[i].load("font/Righteous-Regular.ttf","Close",renderer);
                                red_f[i] = true;
                            }
                        }
                else{
                    if (red_f[i]){
                        func[i].SetColor(32,32,32);
                        if (i==0) func[i].load("font/Righteous-Regular.ttf","Back",renderer);
                        else func[i].load("font/Righteous-Regular.ttf","Close",renderer);
                        red_f[i] = false;
                    }
                }

            }
        }
        else {
            if ((e.motion.x >= button.destRect.x && e.motion.x <= button.destRect.x + button.destRect.w)
                    && (e.motion.y >= button.destRect.y && e.motion.y <= button.destRect.y + button.destRect.h + setting.rect.h))
                    {
                        if (!red_2){
                            setting.SetColor(255, 106, 106);
                            setting.load("font/Righteous-Regular.ttf","Setting",renderer);
                            red_2 = true;
                        }
                    }
            else{
                if (red_2){
                    setting.SetColor(255,255,255);
                    setting.load("font/Righteous-Regular.ttf","Setting",renderer);
                    red_2 = false;
                }
            }
        }
    }
    else if (e.type == SDL_MOUSEWHEEL) {
        if (is_open_setting)
        {
            if(e.wheel.mouseX >= music_vol_bar_x && e.wheel.mouseX <= music_vol_bar_x + music_vol_bar_w &&
                e.wheel.mouseY >= filled_rects[1][0].y && e.wheel.mouseY <= filled_rects[1][0].y + filled_rects[1][0].h)
            {
                Mvol_before = Mvol;
                if (e.wheel.y > 0) {
                    // Scrolled up
                    if (Mvol < MIX_MAX_VOLUME) {
                        Mvol += 4;
                    }
                    if (Mvol >= MIX_MAX_VOLUME) Mvol = MIX_MAX_VOLUME;
                    set_music_volume(Mvol);
                }
                else if (e.wheel.y < 0) {
                    // Scrolled down
                    if (Mvol > 0) {
                        Mvol -= 4;
                    }
                    if (Mvol <= 0) Mvol = 0;
                    set_music_volume(Mvol);
                }
            }
            if(e.wheel.mouseX >= sound_vol_bar_x && e.wheel.mouseX <= sound_vol_bar_x + sound_vol_bar_w &&
                e.wheel.mouseY >= filled_rects[1][1].y && e.wheel.mouseY <= filled_rects[1][1].y + filled_rects[1][1].h)
            {
                Svol_before = Svol;
                if (e.wheel.y > 0) {
                    // Scrolled up
                    if (Svol < MIX_MAX_VOLUME) Svol += 4;
                    if (Svol >= MIX_MAX_VOLUME) Svol = MIX_MAX_VOLUME;
                    set_chunk_volume(Svol);
                }
                else if (e.wheel.y < 0) {
                    // Scrolled down
                    if (Svol > 0) Svol -= 4;
                    if (Svol <= 0) Svol = 0;
                    set_chunk_volume(Svol);
                }
            }
        }
    }
}
void GameUtility::update_event(SDL_Event e, bool &isRunning, bool &is_start, SDL_Renderer* renderer){
    handle_setting(e, isRunning, renderer);
    if (!is_close_util && !is_open_setting){
        if (is_Gameover || is_Win)
        {
                if (e.type == SDL_MOUSEBUTTONDOWN)
                {
                        if (e.button.button == SDL_BUTTON_LEFT)
                        {
                            if ((e.button.x < button.destRect.x || e.button.x > button.destRect.x + button.destRect.w)
                                || (e.button.y < button.destRect.y || e.button.y > button.destRect.y + button.destRect.h + setting.rect.h))
                                {
                                is_start = false;
                                is_Win = false;
                                is_Gameover = false;
                                repeat_sound = 0;
                                playSound(Click);
                                }
                        }
                }
        }
        else {
                if (e.type == SDL_MOUSEBUTTONDOWN)
                {
                    if (e.button.button == SDL_BUTTON_LEFT)
                    {
                        if ((e.button.x >= start_but.destRect.x && e.button.x <= start_but.destRect.x + start_but.destRect.w)
                            && (e.button.y >= start_but.destRect.y && e.button.y <= start_but.destRect.y + start_but.destRect.h))
                        {
                        if (red_1){
                            start.SetColor(255,255,255);
                            start.load("font/PermanentMarker-Regular.ttf", "START !!!", renderer);
                            red_1 = false;
                        }
                        is_start = true;
                        playSound(Click);
                        is_close_util = true;
                        y_fall = -SCREEN_HEIGHT;
                        }
                    }
                }
                else if (e.type == SDL_MOUSEMOTION){
                    if ((e.motion.x >= start_but.destRect.x && e.motion.x <= start_but.destRect.x + start_but.destRect.w)
                            && (e.motion.y >= start_but.destRect.y && e.motion.y <= start_but.destRect.y + start_but.destRect.h)){
                                if (!red_1){
                                    start.SetColor(255, 106, 106);
                                    start.load("font/PermanentMarker-Regular.ttf", "START !!!", renderer);
                                    red_1 = true;
                                }
                            }
                    else
                    {
                        if (red_1){
                            start.SetColor(255,255,255);
                            start.load("font/PermanentMarker-Regular.ttf", "START !!!", renderer);
                            red_1 = false;
                        }

                    }
                }
        }
    }
}
void GameUtility::move_down(SDL_Renderer* renderer){
    if (is_Gameover){
        if (repeat_sound < 1){
            playSound(Gameover);
            std::cout<<"Game Over!!!"<<std::endl;
            repeat_sound ++;
        }
        GameOver.SetRect(SCREEN_WIDTH, SCREEN_HEIGHT, 0, y_fall);
        if (y_fall >= 0) {
            y_fall = 0;
            is_close_util = false;
        }
        else {
            y_fall += 8;
        }
        GameOver.renderTexture(renderer);
    }
    else if (is_Win){
        if (repeat_sound < 1){
            playSound(YouWin);
            std::cout<<"You Win!!!"<<std::endl;
            repeat_sound ++;
        }
        WinGame.SetRect(SCREEN_WIDTH, SCREEN_HEIGHT, 0, y_fall);
        if (y_fall >= 0) {
            y_fall = 0;
            is_close_util = false;
        }
        else {
            y_fall += 8;
        }
        WinGame.renderTexture(renderer);
    }
}
void GameUtility::show(SDL_Renderer *renderer){
    if (!is_close_util){
        if (is_Gameover){
            GameOver.renderTexture(renderer);
            play_again.renderTexture(renderer);
        }
        else if (is_Win){
            WinGame.renderTexture(renderer);
            play_again.renderTexture(renderer);
        }
        else{
            layer_welc.renderTexture(renderer);
            start_but.renderTexture(renderer);
            start.renderTexture(renderer);
            Tutorial.renderTexture(renderer);
        }
    }

    if (is_open_setting){
        button.SetRect(TILE_SIZE, TILE_SIZE, SCREEN_WIDTH / 2 - TILE_SIZE / 2, board.destRect.y + TILE_SIZE / 2);
        board.renderTexture(renderer);
        button.renderTexture(renderer);

        music_vol = std::to_string(Mvol*100/MIX_MAX_VOLUME) + "%";
        sound_vol = std::to_string(Svol*100/MIX_MAX_VOLUME) + "%";
        if (Mvol != Mvol_before) volume[0].load("font/Righteous-Regular.ttf",music_vol,renderer);
        if (Svol != Svol_before) volume[1].load("font/Righteous-Regular.ttf",sound_vol,renderer);
        for (int i = 0; i < 4; i++){
            icon[i].renderTexture(renderer);
            func[i].renderTexture(renderer);
        }
        volume[0].renderTexture(renderer);
        volume[1].renderTexture(renderer);

        // setup chiều dài của thanh volume
        filled_rects[1][0].w = music_vol_bar_w * Mvol / MIX_MAX_VOLUME;
        filled_rects[1][1].w = sound_vol_bar_w * Svol / MIX_MAX_VOLUME;

        SDL_SetRenderDrawColor(renderer, 119, 136, 153, 255);//xám
        SDL_RenderFillRects(renderer, filled_rects[0], 2);
        SDL_SetRenderDrawColor(renderer, 250, 193, 193, 255);//hồng
        SDL_RenderFillRects(renderer, filled_rects[1], 2);
    }
    else{
        if (!is_close_util){
            if (is_Gameover || is_Win) {
                button.SetRect(TILE_SIZE * 2, TILE_SIZE * 2, SCREEN_WIDTH / 2 - TILE_SIZE, SCREEN_HEIGHT - 3 * TILE_SIZE);
                setting.SetRect(button.destRect.w, button.destRect.w / 3, button.destRect.x, button.destRect.y + button.destRect.h);
            }
            else{
                button.SetRect(TILE_SIZE * 2, TILE_SIZE * 2, 0, SCREEN_HEIGHT * 3 / 4);
                setting.SetRect(button.destRect.w, button.destRect.w / 3, button.destRect.x, button.destRect.y + button.destRect.h);
            }
        }
        else{
            button.SetRect(TILE_SIZE, TILE_SIZE, 0, 0);
            setting.SetRect(button.destRect.w, button.destRect.w / 3, button.destRect.x, button.destRect.y + button.destRect.h);
        }
        button.renderTexture(renderer);
        setting.renderTexture(renderer);
    }
}

