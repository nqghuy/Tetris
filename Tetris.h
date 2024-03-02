#pragma once

#include "Game.h"
#include "Menu.h"

class Tetris
{
public:
    Tetris();
    ~Tetris();
    bool init(const char *title, int x, int y, int w, int h);
    bool load_media();
    bool running();
    void handle_events();
    void display();
    void play_music();
private:
    //the window for the game
    SDL_Window *window;

    //the renderer for the window
    SDL_Renderer *renderer;

    LTexture background;

    Game *game;
    Menu *menu;
    bool quit;
};
