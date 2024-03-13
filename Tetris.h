#pragma once

#include "Game.h"
#include "Menu.h"
#include "Battle.h"

class Tetris
{
public:
    //constructor
    Tetris(Level _level = easy);

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
    Level level;

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
