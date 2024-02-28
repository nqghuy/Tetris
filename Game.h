#ifndef Game_h
#define Game_h

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Playing_field.h"
#include "Tetromino.h"
#include "Texture.h"
#include <SDL_mixer.h>

using namespace std;

//used to operate the game
class game
{
public:
    //constructor
    game();

    //destructor
    ~game();

    //initialize SDL and create the window
    bool init(const char *title, int x, int y, int w, int h);

    //check if the game is running
    bool running();

    //handle events from queue
    void handleEvents();

    //load background and music
    bool loadMedia();

    void play_music();

    //close the game
    void close_game();

    //draw game
    void display();

    //if game is losed and not played
    bool is_paused();


private:
    //background
    LTexture background;

    //field to play
    Well well ;

    //tetromino will be controlled
    Tetromino tetromino;

    //the window for the game
    SDL_Window *window;

    //the renderer for the window
    SDL_Renderer *renderer;

    //return true if quit the game
    bool quit;

    //lose game state and not play
    bool pause;
} ;
#endif
