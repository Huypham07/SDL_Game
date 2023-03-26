#include "game.h"
#include "Map.h"
#include "player.h"
#include "start_game.h"
#include "endgame.h"
#include "setting.h"
#include "ball.h"
ImgObject background;
start_game *Start_;
Setting *setting_;
EndGame *endgame_;
Map_ *map_;
player *character;
Ball **list_ball;
bool check_ball_collision(Ball *B, player *P){
    int r = BALL_WIDTH / 2;
    int bx = B->x_pos + r;// tọa độ tâm của quả bóng
    int by = B->y_pos + r;
    int cx;//tọa độ điểm gần bóng nhất của player
    int cy;
        //tìm cx gần nhất
    if( bx < P->x_pos )
    {
        cx = P->x_pos;
    }
    else if( bx > P->x_pos + P->player_rect.w )
    {
        cx = P->x_pos + P->player_rect.w;
    }
    else
    {
        cx = bx;
    }
        //tìm cy gần nhất
    if( by < P->y_pos )
    {
        cy = P->y_pos;
    }
    else if( by > P->y_pos + P->player_rect.h )
    {
        cy = P->y_pos + P->player_rect.h;
    }
    else
    {
        cy = by;
    }
    //tính khoảng cách
    if ((cx-bx) * (cx-bx) + (cy-by) * (cy-by) < r * r)
    {
        B->is_move = false;
        P->stopGame();
        return true;
    }
    return false;
}
void init(SDL_Window *&window, SDL_Renderer *&renderer)
{
    initSDL(window, renderer);
    background.load("image/background.jpg", renderer);
    background.SetRect(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

    Start_ = new start_game(renderer);
    setting_ = new Setting(renderer);
    playMusic(setting_->Ost);

    character = new player();
    character->pJump = setting_->Jump;
    character->setFrame_src("image/char.png", renderer);

    endgame_ = new EndGame(renderer);

    map_ = new Map_();
    map_->Load_tileSet(renderer, "image/tileset.png");
    map_->LoadMap("image/map.txt");
    map_->LoadTrap("image/trap.txt");

    list_ball = new Ball*[2];
    for (int i=0;i<2;i++){
        list_ball[i] = new Ball();
        list_ball[i]->setFrame_src("image/ball.png", renderer);
    }
    list_ball[0]->set_pos(80 * TILE_SIZE,3 * TILE_SIZE);
    list_ball[1]->set_pos(100 * TILE_SIZE,3 * TILE_SIZE);
}

void handleEvent(bool &isRunning, SDL_Event e)
{
    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            isRunning = false;
            break;
        }
        Start_->handle_click(e,setting_);
        setting_->handle_setting(e, isRunning);
        endgame_->handle_click(e, setting_, map_, character, Start_);
        if (Start_->state && !endgame_->win_state && !endgame_->GameOver_state && !setting_->state)
        {
            for (int i=0;i<2;i++){
                list_ball[i]->is_move = true;
            }
            character->InputEvent(e);
        }
    }
    character->handleInput(map_);
    character->trap_checking(map_);
    for (int i=0;i<2;i++){
        list_ball[i]->Move(map_);
    }
}
void update()
{
    endgame_->GameOver_state = character->die;
    for (int i = 0; i<2 ; i++)
    {
        if(check_ball_collision(list_ball[i], character)) endgame_->GameOver_state = true;
    }
    endgame_->win_state = character->WinState(map_);
}
void render(SDL_Renderer *renderer)
{
    SDL_RenderClear(renderer);
    background.renderTexture(renderer);
    map_->DrawMap(renderer);
    character->renderFrame(renderer, map_);
    for (int i=0;i<2;i++)
        list_ball[i]->renderFrame(renderer, map_);
    Start_->ren_startpage(renderer, setting_);
    endgame_->render_page(renderer, setting_);
    setting_->show(renderer);
    SDL_RenderPresent(renderer);
}
void clean(SDL_Window *window, SDL_Renderer *renderer)
{
    background.Free();
    delete map_;
    delete Start_;
    delete setting_;
    delete endgame_;
    delete character;
    delete list_ball;
    quitSDL(window, renderer);
}
