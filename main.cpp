#include "game.h"

using namespace std;

bool check_ball_collision(Ball *B, player *P);
int main(int argc, char* argv[])
{
    SDL_Window *gwindow = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Event e;
    bool start = false;

    initSDL(gwindow,renderer);

    ImgObject background;
    background.load("image/background.jpg", renderer);
    background.SetRect(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

    GameUtility* GameUtil = new GameUtility(renderer);
    playMusic(GameUtil->Ost);

    player* character = new player();
    character->pJump = GameUtil->Jump;
    character->setFrame_src("image/char.png", renderer);

    Map_* map_ = new Map_();
    map_->Load_tileSet(renderer, "image/tileset.png");
    map_->LoadMap("image/map.txt");
    map_->LoadTrap("image/trap.txt");

    vector<Ball*>list_ball(2);
    for (int i=0;i<2;i++){
        list_ball[i] = new Ball();
        list_ball[i]->setFrame_src("image/ball.png", renderer);
    }

    bool is_running = true;
    cout<<"Start Game!"<<endl;
    while (is_running)
    {
        while (SDL_PollEvent(&e)!=0)
        {
            if (e.type == SDL_QUIT)
            {
                is_running = false;
                cout<<"Out Game!"<<endl;
                break;
            }
            GameUtil->update_event(e, is_running, start, renderer);
            if (GameUtil->is_close_util && !GameUtil->is_open_setting){
                for (int i=0;i<2;i++){
                    list_ball[i]->is_move = true;
                }
                if (!character->die && !character->WinState(map_)) character->InputEvent(e);
            }
        }
        SDL_RenderClear(renderer);
        background.renderTexture(renderer);
            if (!start)
            {
                map_->LoadTrap("image/trap.txt");
                character->Restart();
                list_ball[0]->set_pos(80 * TILE_SIZE,3 * TILE_SIZE);
                list_ball[1]->set_pos(100 * TILE_SIZE,3 * TILE_SIZE);

                start = true;
            }

        if (GameUtil->is_close_util) {
            map_->DrawMap(renderer);
            character->handleInput(map_);
            character->trap_checking(map_);
            map_->DrawMap(renderer);
            for (int i=0;i<2;i++){
                list_ball[i]->Move(map_);
            }
//
            for (int i = 0; i<2 ; i++)
            {
                if(check_ball_collision(list_ball[i], character)) {
                    GameUtil->is_Gameover = true;
                }
            }
            GameUtil->is_Gameover = character->die;
            GameUtil->is_Win = character->WinState(map_);

            character->renderFrame(renderer, map_);
            for (int i=0;i<2;i++)
                list_ball[i]->renderFrame(renderer, map_);
            if (GameUtil->is_Gameover||GameUtil->is_Win){
                    GameUtil->move_down(renderer);
            }

        }
        GameUtil->show(renderer);
        SDL_RenderPresent(renderer);
        SDL_Delay(7);

    }
    //free
    background.Free();
    Mix_FreeMusic(GameUtil->Ost);
    Mix_FreeChunk(GameUtil->Click);
    Mix_FreeChunk(GameUtil->Jump);
    Mix_FreeChunk(GameUtil->Gameover);
    delete character;
    delete GameUtil;
    delete map_;
    quitSDL(gwindow,renderer);
    return 0;
}
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
        P->die = true;
        P->stopGame();
        return true;
    }
    return false;
}
