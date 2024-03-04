#include <bits/stdc++.h>
#include "include/SDL2/SDL.h"
#include "include/SDL2/SDL_image.h"
#include "include/SDL2/SDL_mixer.h"
#include "include/SDL2/SDL_ttf.h"
#include "Data.h"
#include "Game.h"
#include "Tetris.h"
using namespace std;

int main(int argc, char *argv[])
{
    //use to random type of tetromino
    srand(time(0));

    Tetris *tetris = new Tetris;

    //check if initialize false
    if (!tetris->init("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT)){
        cout << "failed to init sdl" << endl;
    }

    if(!tetris->load_media()){
        cout << "failed to load media\n";
    }

    //game runs
    while (tetris->running()){
        tetris->handle_events();
        tetris->play_music();
        tetris->display();
    }


    //deallocate game
    tetris = NULL;
    return 0;
}
