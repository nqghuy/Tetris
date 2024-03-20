#include "Game.h"
#include <iostream>
#include <algorithm>
using namespace std;

Game::Game(SDL_Renderer *renderer, GameMode _gameMode, int _level, bool _ghostTetromino)
    :   //initialize ...
      well(renderer, (SCREEN_WIDTH - TILE_SIZE * WIDE_CELLS) / 2, (SCREEN_HEIGHT - TILE_SIZE * HEIGHT_CELLS) / 2, 0, _level),
    tetromino(Tetro_Type(rand() % 7), WIDE_CELLS / 2 - 1, 0), quit(true),
      nextTetromino(Tetro_Type(rand() % 7), WIDE_CELLS / 2 - 1, 0), pause(false)
      {
        gameMode = _gameMode;
        level = _level;
        ghostTetromino = _ghostTetromino;
        moveTime = SDL_GetTicks();

        //set well corresponding to game mode
        if (_gameMode == Player1){
            well = Well(renderer, SCREEN_WIDTH / 11 , (SCREEN_HEIGHT - TILE_SIZE * HEIGHT_CELLS) / 2, 0, _level);
        }
        else if (_gameMode == Player2){
            well = Well(renderer, SCREEN_WIDTH / 11  * 6, (SCREEN_HEIGHT - TILE_SIZE * HEIGHT_CELLS) / 2, 0, _level);
        }
        //random next tetro type
        nextTetromino = Tetromino(nextTetromino.get_random_type(tetromino), WIDE_CELLS / 2 - 1, 0);

        preparation = true;
        timer = SDL_GetTicks64();
}

Game :: ~Game(){}

bool Game :: running()
{
    return (!quit);
}

void Game :: handleEvents(SDL_Renderer *renderer, SDL_Event &e)
{
    if(preparation) return;

    //handle tetromino
    if (!is_paused()){
        if(tetromino.get_active()){
            tetromino.handle_events(e, well, gameMode);
            tetromino.Move(well);
        }
    }
    else{//if lose, press enter to reset game, get top score
        if (well.press_play_again(e)){
            moveTime = SDL_GetTicks();

            preparation = true;
            timer = SDL_GetTicks();

            //new top score
            int _topScore = max(well.get_current_score(), well.get_top_score());

            //reset well
            well = Well(renderer, well.get_x(), well.get_y(), _topScore, this->level);

            //reset tetromino
            tetromino = Tetromino(nextTetromino.get_tetro_type(), WIDE_CELLS / 2 - 1, 0);
            nextTetromino = Tetromino(nextTetromino.get_random_type(tetromino), WIDE_CELLS / 2 - 1, 0);
        }
        //if click return home
        else if(well.return_home(e)){
            quit = true;
        }
    }
}

void Game :: update(){
    if (preparation) return;

    //current time
    int currentTime;

    //up level if get enough score
    if (level < MAX_LEVEL && this->get_current_score() > level * 500){
        level = level++;
    }

    //after 1s, the tetromino will fall
    currentTime = SDL_GetTicks();

    //free fall
    if (currentTime > moveTime){
        moveTime += 1000 - level * 150;
        tetromino.free_fall(well);
    }

    if (!tetromino.get_active()){
        //new tetrimino
        tetromino = Tetromino(nextTetromino.get_tetro_type(), WIDE_CELLS / 2 - 1, 0);
        nextTetromino = Tetromino(nextTetromino.get_random_type(tetromino), WIDE_CELLS / 2 - 1, 0);

        //if lose game
        if (tetromino.check_bottom_collision(well)){
            well.set_lose();
            Mix_PlayChannel(-1, gLoseSoundEffect, 0);
        }

        //remove all events
        SDL_FlushEvents(SDL_USEREVENT, SDL_LASTEVENT);
    }
}

void Game :: play_music()
{   
    //play music when starting playing game
    if(Mix_PlayingMusic() == 0){
        Mix_PlayMusic(gPlayingMusic, -1);
    }
}

int Game :: get_current_score(){
    return well.get_current_score();
}


void Game :: display(SDL_Renderer *renderer)
{
    //draw next tetromino
    gScoreFrame.render(renderer, well.get_right_border(), well.get_y() + TILE_SIZE + gScoreFrame.getHeight()* 2- TILE_SIZE * 2);
    nextTetromino.draw(renderer, well.get_right_border() + TILE_SIZE  * 2, well.get_y() + TILE_SIZE + gScoreFrame.getHeight()* 2);

    //draw well and tetromino
    well.draw(renderer, gameMode);

    if (preparation && (SDL_GetTicks() - timer > 3000)){
        preparation = false;
        moveTime = SDL_GetTicks();
    }

    if (preparation){
        int countDownTime = 3000 - (SDL_GetTicks() - timer);
        if (countDownTime >= 2000){
            gThreeTexture.render(renderer, well.get_x() + (well.get_width() - gThreeTexture.getWidth()) / 2 , well.get_y() + (well.get_height() - gThreeTexture.getHeight()) / 2 );
        }
        else if (countDownTime >= 1000){
            gTwoTexture.render(renderer, well.get_x() + (well.get_width() - gThreeTexture.getWidth()) / 2 , well.get_y() + (well.get_height() - gTwoTexture.getHeight()) / 2 );
        }
        else{
            gOneTexture.render(renderer, well.get_x() + (well.get_width() - gThreeTexture.getWidth()) / 2 , well.get_y() + (well.get_height() - gOneTexture.getHeight()) / 2 );
        }
    }

    else if (!well.get_lose()){
        //draw ghost tetromino if ghost piece on
        if(ghostTetromino) tetromino.draw_ghost_tetromino(renderer, well);

        //draw tetromino
        tetromino.draw(renderer, well);
    }
    //render lose back ground if mode is single play
    //in battle, we have to wait two player finish their game
    else if (this->gameMode == SinglePlay){
        well.draw_lose_background(renderer);
    }

}

bool Game :: is_paused()
{
    return (well.get_lose());
}

void Game :: set_preparation(int _level, bool _ghostTetromino){
    timer = SDL_GetTicks();
    preparation = true;

    level = _level;
    ghostTetromino = _ghostTetromino;

    //ready to play
    quit = false;
}

void Game :: set_active(int _level, bool _ghostTetromino)
{   
    //reset move time
    moveTime = SDL_GetTicks();

    //set level and ghost tetromino
    level = _level;
    ghostTetromino = _ghostTetromino;

    //ready to play
    //quit = false;
}

void Game :: set_time(){
    moveTime = SDL_GetTicks();
}