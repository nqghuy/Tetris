#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "Data.h"
#include "Game.h"

using namespace std;

int main(int argc, char *argv[])
{
    //use to random type of tetromino
    srand(time(NULL));

    //initialize a game
    game *tetris = new game;

    //check if initialize false
    if (!tetris->init("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT)){
        cout << "failed to init sdl" << endl;
    }

    //game runs
    while (tetris->running()){
        tetris->handleEvents();
    }

    //close game
    tetris->close_game();

    //deallocate game
    tetris = NULL;
    return 0;
}
