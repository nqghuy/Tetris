#pragma once

#include "Game.h"
#include "Menu.h"
#include "Battle.h"

class Tetris
{
public:
    //constructor
    Tetris();

    //destructor
    ~Tetris();

    //initialize sdl, window, etc
    bool init(const char *title, int x, int y, int w, int h);

    //load pictures, music, ...
    bool load_media();

    //if game is running
    bool running();

    //handle event
    void handle_events();

    //show game on the screen
    void display();

    //play music during game
    void play_music();

    //close game and free memory
    void close_game();
    
private:
    //the window for the game
    SDL_Window *window;

    //the renderer for the window
    SDL_Renderer *renderer;

    //background game
    LTexture background;

    //game to play
    Game *game;

    Battle *battle;

    //menu before playing
    Menu *menu;

    //true if quit
    bool quit;
};
