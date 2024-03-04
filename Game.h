#ifndef Game_h
#define Game_h

#include "include/SDL2/SDL.h"
#include "include/SDL2/SDL_image.h"
#include "include/SDL2/SDL_mixer.h"
#include "include/SDL2/SDL_ttf.h"
#include <iostream>
#include "Playing_field.h"
#include "Tetromino.h"
#include "Texture.h"
#include "include/SDL2/SDL_mixer.h"
#include "Menu.h"
using namespace std;

//used to operate the game
class Game
{
public:
    //constructor
    Game(SDL_Renderer *renderer);

    //destructor
    ~Game();

    //initialize SDL and create the window
    bool init(const char *title, int x, int y, int w, int h);

    //check if the game is running
    bool running();

    //handle events from queue
    void handleEvents(SDL_Renderer *renderer, SDL_Event &e);

    //load background and music
    bool loadMedia();

    //play music during the game
    void play_music();

    //close the game
    void close_game();

    //draw game
    void display(SDL_Renderer *renderer);

    //if game is losed and not played
    bool is_paused();

    void set_active();

private:
    //field to play
    Well well ;

    //tetromino will be controlled
    Tetromino tetromino;

    //return true if quit the game
    bool quit;

    //lose game state and not play
    bool pause;
} ;
#endif
