#include "Battle.h"
#include <thread>
using namespace std;
Battle :: Battle(SDL_Renderer *renderer, GameMode gameMode1, GameMode gameMode2){
     player1 = new Game (renderer, gameMode1);
     player2 = new Game (renderer, gameMode2);
     active = false;
}

Battle :: ~Battle(){
     // free memory
     delete player1;
     delete player2;
     player1 = NULL;
     player2 = NULL;
}

bool Battle :: load_media(SDL_Renderer *renderer){
     bool success = true;

     //load battle texture
     if (!gPlayer1Wins.loadFromFile(renderer, "Assets/Pictures/player1_win.png")){
          cout << "failed to load player1wins texture\n";
          success = false;
     }
     if (!gPlayer2Wins.loadFromFile(renderer, "Assets/Pictures/player2_win.png")){
          cout << "failed to load player2wins texture\n";
          success = false;
     }
     if(!gDraw.loadFromFile(renderer, "Assets/Pictures/draw.png"))
     {
          cout << "failed to load draw texture\n";
          success = false;
     }
     return success;
}

bool Battle :: get_active(){
     return active;
}

void Battle :: set_active(int _level, bool _ghostTetromino, Effect _effect){
     active = true;

     //reset move time
     player1->set_active(_level, _ghostTetromino, _effect);
     player2->set_active(_level, _ghostTetromino, _effect);
}

void Battle :: handle_event(SDL_Renderer *renderer, SDL_Event &e){
     player1->handleEvents(renderer, e);
     player2->handleEvents(renderer, e);

     //if two player lose
     if (!player1->running() && !player2->running()){
          active = false;
     }
}


void Battle :: display(SDL_Renderer *renderer, Theme theme){
     //update 
     if(!player1->get_lose())     player1->update();
     if(!player2->get_lose())     player2->update();

     //draw each playing field
     player2->display(renderer, theme);
     player1->display(renderer, theme);
     
     //if two player lose
     if (player1->get_lose() && player2->get_lose()){
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

void Battle :: free_memory(){
     gPlayer1Wins.free();
     gPlayer2Wins.free();
     gDraw.free();
}

void Battle :: load_file(fstream &saveFile){
     player1->load_file(saveFile);
     player2->load_file(saveFile);
}

void Battle :: save_file(fstream &saveFile){
     player1->save_file(saveFile);
     player2->save_file(saveFile);
}
