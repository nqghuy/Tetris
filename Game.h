#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>

using namespace std;

const int SCREEN_HEIGHT = 800;
const int SCREEN_WIDTH = 640;

class game
{
public:
    game();
    ~game();
    bool init(const char *title, int x, int y, int w, int h);
    bool running();
    void handleEvents();
    void close_game();
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool quit;
} ;

