#pragma once

#include "Game.h"
#include "Menu.h"
#include "Battle.h"

class Tetris
{
public:
    //constructor
    Tetris(int _level = 1);

    //destructor
    ~Tetris();

    //initialize sdl, window, etc
    bool init(const char *title, int x, int y, int w, int h);

    //load pictures, music, ...
    bool load_media();

    bool load_texture();

    bool load_music();

    bool load_font();

    //if game is running
    bool running();

    void menu_handle_event(SDL_Event &e);

    //handle event
    void handle_events();

    //show game on the screen
    void display();

    //play music during game
    void play_music();

    //close game and free memory
    void close_game();
    
private:
    //present ghost tetromino or not
    bool ghostTetromino;

    //level in game(can be changed)
    int level;

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

    Animation animation[20];

    //true if quit
    bool quit;
};
