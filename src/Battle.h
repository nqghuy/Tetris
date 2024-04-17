#pragma once
#include "Game.h"
#include <thread>


class Battle{
public:
     //constructor
     Battle(SDL_Renderer *renderer, GameMode gameMode1 = Player1, GameMode gameMode2 = Player2);

     //destructor
     ~Battle();

     bool load_media(SDL_Renderer *renderer);

     //get active
     bool get_active();

     //ready to battle
     void set_active(int _level, bool _ghostTetromino, Effect _effect, Mode _mode);

     //handle event
     void handle_event(SDL_Renderer *renderer, SDL_Event &e);

     //draw on the screen
     void display(SDL_Renderer *renderer, Theme theme);

     void free_memory();

     //load and save file
     void save_file(fstream &saveFile);
     void load_file(fstream &saveFile);
     
private:
     //player
     Game* player1;
     Game* player2;

     //true if a battle exist
     bool active;
};