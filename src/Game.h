#ifndef Game_h
#define Game_h

#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL_image.h"
#include "../include/SDL2/SDL_mixer.h"
#include "../include/SDL2/SDL_ttf.h"
#include <iostream>
#include "Playing_field.h"
#include "Tetromino.h"
#include "Texture.h"
#include "../include/SDL2/SDL_mixer.h"
#include "Menu.h"
#include "Animation.h"

using namespace std;

//used to operate the game
class Game
{
public:
    //constructor
    Game(SDL_Renderer *renderer, GameMode _gameMode = SinglePlay, int _level = 1, bool _ghostTetromino = true);

    //destructor
    ~Game();

    //check if the game is running
    bool running();

    //handle events from queue
    void handleEvents(SDL_Renderer *renderer, SDL_Event &e);

    void handlePausedEvent(SDL_Event &e);

    //play music during the game
    void play_music();

    void display_paused_board(SDL_Renderer *renderer, Theme theme);

    //draw game
    void display(SDL_Renderer *renderer, Theme theme);

    //if game is losed and not played
    bool get_lose();

    //game is ready to play
    void set_active(int _level, bool ghostTetromino);

    //set move time equal to current time
    void set_time();

    //get current score
    int get_current_score();

    //to update if no event polled
    void update();


private:
    //true if present ghost tetromino
    bool ghostTetromino;

    int level;

    //single play or battle(player 1 or 2)
    GameMode gameMode;

    //field to play
    Well well ;

    //tetromino will be controlled
    Tetromino tetromino;

    //next tetromino
    Tetromino nextTetromino;

    //return true if quit the game
    bool quit;

    //lose game state and not play
    bool lose;

    //use to make tetromino free fall
    int moveTime;

    //count down time
    int timer;

    //true if count down time is not finished
    bool preparation;

    bool paused;
};
#endif
