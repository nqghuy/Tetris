#pragma once
#include "Game.h"
#include <thread>


class Battle{
public:
     Battle(SDL_Renderer *renderer);
     ~Battle();
     bool get_active();
     void set_active();
     void handle_event(SDL_Renderer *renderer, SDL_Event &e);
     void display(SDL_Renderer *renderer);
private:
     Game* player1;
     Game* player2;
     bool active;
};