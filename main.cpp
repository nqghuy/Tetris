#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "Game.h"

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    game *tetris = new game;
    if (!tetris->init("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT)){
        cout << "failed to init sdl" << endl;
    }
    while (tetris->running()){
        tetris->handleEvents();
    }
    tetris->close_game();
    tetris = NULL;
    return 0;
}
