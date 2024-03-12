#include "Battle.h"
#include <thread>
using namespace std;
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
     // player1->set_time();
     // player2->set_time();
}

void Battle :: handle_event(SDL_Renderer *renderer, SDL_Event &e){
     player1->handleEvents(renderer, e);
     player2->handleEvents(renderer, e);
     if (!player1->running() && !player2->running()){
          active = false;
     }
}

void Battle :: display(SDL_Renderer *renderer){
     if(!player1->is_paused())     player1->update();
     if(!player2->is_paused())     player2->update();
     player2->display(renderer);
     player1->display(renderer);
     if (player1->is_paused() && player2->is_paused()){
          if (player1->get_current_score() > player2->get_current_score()){
               gPlayer1Wins.render(renderer, (SCREEN_WIDTH - gPlayer1Wins.getWidth()) / 2, (SCREEN_HEIGHT - gPlayer1Wins.getHeight()) / 2);
          }
          else if (player1->get_current_score() < player2->get_current_score()){
               gPlayer2Wins.render(renderer, (SCREEN_WIDTH - gPlayer2Wins.getWidth()) / 2, (SCREEN_HEIGHT - gPlayer2Wins.getHeight()) / 2);
          }
          else{
               gDraw.render(renderer, (SCREEN_WIDTH - gPlayer2Wins.getWidth()) / 2, (SCREEN_HEIGHT - gPlayer2Wins.getHeight()) / 2);
          }
          gReplayButton.render(renderer, (SCREEN_WIDTH - gReplayButton.getWidth()) / 2, (SCREEN_HEIGHT - gReplayButton.getHeight()) / 2 + buttonDistance);

          gHomeButton.render(renderer, (SCREEN_WIDTH - gReplayButton.getWidth()) / 2 - buttonDistance, (SCREEN_HEIGHT - gReplayButton.getHeight()) / 2 + buttonDistance);
     }
}

