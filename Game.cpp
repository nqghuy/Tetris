#include "Game.h"
#include <iostream>
#include <algorithm>
using namespace std;

Game::Game(SDL_Renderer *renderer)
    : well(renderer, (SCREEN_WIDTH - TILE_SIZE * WIDE_CELLS) / 2 - 1, (SCREEN_HEIGHT - TILE_SIZE * HEIGHT_CELLS) / 2, 0),
      tetromino(Tetro_Type(rand() % 7), WIDE_CELLS / 2, 0),
      quit(true){
}

Game :: ~Game(){}

bool Game :: running()
{
    return (!quit);
}

void Game :: handleEvents(SDL_Renderer *renderer, SDL_Event &e)
{

    //handle tetromino
    if (!is_paused()){
        if(tetromino.get_active()){
            tetromino.handle_events(e, well);
            tetromino.Move(well);
        }
    }
    else{//if lose, press enter to reset game, get top score
        if (well.press_play_again(e)){
            //new top score
            int _topScore = max(well.get_current_score(), well.get_top_score());

            //reset well
            well = Well(renderer, (SCREEN_WIDTH - TILE_SIZE * WIDE_CELLS) / 2, (SCREEN_HEIGHT - TILE_SIZE * HEIGHT_CELLS) / 2, _topScore);

            //reset tetromino
            tetromino = Tetromino(tetromino.get_random_type(), WIDE_CELLS / 2 - 1, 0);
        }
        else if(well.return_home(e)){
            quit = true;
        }
    }

//    //draw
//    display(renderer);
    if (!is_paused()){
        //if the tetromino is finised
        if (!tetromino.get_active()){
            //new tetrimino
            tetromino = Tetromino(tetromino.get_random_type(), WIDE_CELLS / 2 - 1, 0);

            //if lose game
            if (tetromino.check_bottom_collision(well)){
                well.set_lose();
                Mix_PlayChannel(-1, gLoseSoundEffect, 0);
            }

            //remove all before events
            SDL_FlushEvents(SDL_USEREVENT, SDL_LASTEVENT);
        }
    }
}

void Game :: play_music()
{
    if(Mix_PlayingMusic() == 0){
        Mix_PlayMusic(gPlayingMusic, -1);
    }
}

void Game :: close_game()
{
    SDL_Quit();
    TTF_Quit();
    IMG_Quit();
}



void Game :: display(SDL_Renderer *renderer)
{
    //current time
    int currentTime;

    //after 1s, the tetromino will fall
    static int moveTime = SDL_GetTicks();
    currentTime = SDL_GetTicks();

    //free fall
    if (currentTime > moveTime){
        moveTime += 1000;
        tetromino.free_fall(well);
    }

    //draw well and tetromino
    well.draw(renderer);

    if (!well.get_lose()){
        tetromino.draw(renderer, well);
    }
    else{
        well.draw_lose_background(renderer);
    }

    //display on the screen
    SDL_RenderPresent(renderer);
}

bool Game :: is_paused()
{
    return (well.get_lose());
}

void Game :: set_active()
{
    quit = false;
    
}

