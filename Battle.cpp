#include "Battle.h"

Battle :: Battle(SDL_Renderer *renderer){
     player1 = new Game (renderer, Player1);
     player2 = new Game (renderer, Player2);
     active = false;
}

Battle :: ~Battle(){
     delete player1;
     delete player2;
     player1 = NULL;
     player2 = NULL;
}

bool Battle :: get_active(){
     return active;
}

void Battle :: set_active(){
     active = true;
     player1->set_active();
     player2->set_active();
}

void Battle :: handle_event(SDL_Renderer *renderer, SDL_Event &e){
     player2->handleEvents(renderer, e);
     player1->handleEvents(renderer, e);
     if (!player1->running() && !player2->running()){
          active = false;
     }
}

void Battle :: display(SDL_Renderer *renderer){
     player2->display(renderer);
     player1->display(renderer);
}

