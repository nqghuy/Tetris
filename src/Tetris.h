#pragma once

#include "Game.h"
#include "Menu.h"
#include "Battle.h"
#include "Setting.h"
#include "Animation.h"
class Tetris
{
public:
    //constructor
    Tetris(int _level = 1, Theme _theme = Winter);

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

    void setting_handle_event(SDL_Event &e);

    //handle event
    void handle_events();

    void set_animation_theme();

    //show game on the screen
    void display();

    //play music during game
    void play_music();

    //free memory
    void free_texture();
    void free_music();
    void free_font();
    void free_memory();

    //close game and free memory
    void close_game();

    //load and save file
    void load_file();
    void save_file();
    
private:
    Theme theme;

    //present ghost tetromino or not
    bool ghostTetromino;

    //level in game(can be changed)
    int level;

    //the window for the game
    SDL_Window *window;

    //the renderer for the window
    SDL_Renderer *renderer;

    //game to play
    Game *game;

    Battle *battle;
    Battle *vsCom;

    //menu before playing
    Menu *menu;

    //setting ghost, level, theme, ...
    Setting *setting;

    //animation(snow or leaf)
    Animation animation[MAX_ANIMATION];

    //true if quit
    bool quit;
};