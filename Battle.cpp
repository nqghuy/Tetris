#include "Battle.h"
#include <thread>
using namespace std;
Battle :: Battle(SDL_Renderer *renderer){
     player1 = new Game (renderer, Player1);
     player2 = new Game (renderer, Player2);
     active = false;
}

Battle :: ~Battle(){
     // free memory
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

     //reset move time
     player1->set_active();
     player2->set_active();
}

void Battle :: handle_event(SDL_Renderer *renderer, SDL_Event &e){
     player1->handleEvents(renderer, e);
     player2->handleEvents(renderer, e);

     //if two player lose
     if (!player1->running() && !player2->running()){
          active = false;
     }
}

void Battle :: display(SDL_Renderer *renderer){
     //update 
     if(!player1->is_paused())     player1->update();
     if(!player2->is_paused())     player2->update();

     //draw each playing field
     player2->display(renderer);
     player1->display(renderer);
     
     //if two player lose
     if (player1->is_paused() && player2->is_paused()){
          //if player 1 win
          if (player1->get_current_score() > player2->get_current_score()){
               gPlayer1Wins.render(renderer, (SCREEN_WIDTH - gPlayer1Wins.getWidth()) / 2, (SCREEN_HEIGHT - gPlayer1Wins.getHeight()) / 2);
          }
          
          //if player 2 win
          else if (player1->get_current_score() < player2->get_current_score()){
               gPlayer2Wins.render(renderer, (SCREEN_WIDTH - gPlayer2Wins.getWidth()) / 2, (SCREEN_HEIGHT - gPlayer2Wins.getHeight()) / 2);
          }

          //draw
          else{
               gDraw.render(renderer, (SCREEN_WIDTH - gPlayer2Wins.getWidth()) / 2, (SCREEN_HEIGHT - gPlayer2Wins.getHeight()) / 2);
          }

          //draw replay button and home button
          gReplayButton.render(renderer, (SCREEN_WIDTH - gReplayButton.getWidth()) / 2, (SCREEN_HEIGHT - gReplayButton.getHeight()) / 2 + buttonDistance);

          gHomeButton.render(renderer, (SCREEN_WIDTH - gReplayButton.getWidth()) / 2 - buttonDistance, (SCREEN_HEIGHT - gReplayButton.getHeight()) / 2 + buttonDistance);
     }
}

void Battle :: set_level(int _level){
     player1->set_level(_level);
     player2->set_level(_level);
}
