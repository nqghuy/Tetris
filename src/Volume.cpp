#include "Volume.h"
#include <math.h>

Volume :: Volume(){
     //set default value
     active = false;
     startTime = 0;
     gravity = 60;
     BallActive = false;
     ballX = ballY = 0;
     ballAngle = 0;
}

//set static variable value
int Volume :: y_coordinate = 700;
int Volume :: Ball_Velocity = 120;

Volume :: ~Volume(){
     Canon.free();
     Pedestal.free();
     Ball.free();
     VolumeText.free();
}

bool Volume :: load_media(SDL_Renderer *renderer){
     bool success = true;
     if (!Pedestal.loadFromFile(renderer, "Assets/Pictures/pedestal.png", {239, 228, 176})){
          cout << "failed to load pedestal\n";
          success = false;
     }
     if (!Canon.loadFromFile(renderer, "Assets/Pictures/canon.png", {239, 228, 176})){
          cout << "failed to load canon\n";
          success = false;
     }
     if (!Ball.loadFromFile(renderer, "Assets/Pictures/ball.bmp", {0, 255, 255})){
          cout << "failed to load ball\n";
          success = false;
     }
     if (!VolumeText.loadFromRenderedText(renderer, SettingFont, "VOLUME", {0, 0, 0})){
          cout << "failed to load volume text\n";
     }

     //update the first position of ball
     ballX = 1.0 * SCREEN_WIDTH / 2 + Canon.getWidth() / 2;
     ballY = 1.0 * y_coordinate + Canon.getHeight() / 5;
     return success;
}

void Volume :: display(SDL_Renderer *renderer){
     //render "VOLUMe"
     VolumeText.render(renderer, (SCREEN_WIDTH - MenuBackground.getWidth()) / 2 + 50, y_coordinate);

     //the volume bar position
     int VolumeRectX = SCREEN_WIDTH / 2 + Canon.getWidth() * 1.8;
     int VolumeRectY = y_coordinate + Canon.getHeight() / 2;
     
     //the volume bar rect;
     SDL_Rect volumeRect = {VolumeRectX, VolumeRectY, 180, 5};

     //set gray color
     SDL_SetRenderDrawColor(renderer, 158, 158, 158, 255);

     //fill volume bar
     SDL_RenderFillRect(renderer, &volumeRect);

     //the first posion of ball
     double x0 = 1.0 * SCREEN_WIDTH / 2 + Canon.getWidth() / 2;
     double y0 = 1.0 * y_coordinate + Canon.getHeight() / 5;

     //if ball is moving
     if (BallActive){
          //the time ball moved
          double t = (1.0 * SDL_GetTicks() - ballStartTime) / 1000;

          //calculate x position x = x0 + v.cos(a) * t
          ballX = x0 + 1.0 * Ball_Velocity * cos(M_PI / 180 * ballAngle) * t;

          //calculate y position y = y0 + v.sin(a) * t + 1/2 * g * t^2
          ballY = y0 - 1.0 * Ball_Velocity * sin(M_PI / 180 * ballAngle) * t  + 1.0 / 2 * gravity * t * t;

          //if the ball is dropped in the volume bar
          if (ballY + Ball.getHeight() / 2 >= VolumeRectY + volumeRect.h / 2){
               //ball will not move
               BallActive = false;

               //change the volume
               Mix_Volume(-1, 1.0 * MIX_MAX_VOLUME / volumeRect.w * (ballX - VolumeRectX));
               Mix_VolumeMusic(1.0 * MIX_MAX_VOLUME / volumeRect.w * (ballX - VolumeRectX));
               // cout << 1.0 * MIX_MAX_VOLUME / volumeRect.w * (ballX - VolumeRectX) << " ";
          }
     }
     //draw ball
     Ball.render(renderer, ballX, ballY); 

     //if we are holding the canon
     if (active){
          // the angle canon
          double angle = max(1.0 * (-30), 1.0 * 45 - (1.0 * SDL_GetTicks() - startTime) / 50 );

          //draw canon
          Canon.render(renderer, SCREEN_WIDTH / 2, y_coordinate, NULL, NULL, angle);
     }
     else{
          //draw canon in default position
          Canon.render(renderer, SCREEN_WIDTH / 2, y_coordinate, NULL, NULL, 45);
     }

     //draw pedestal in final
     Pedestal.render(renderer, SCREEN_WIDTH / 2, y_coordinate);
     
}

void Volume :: handle_event(SDL_Event &e){
     int x, y;
     SDL_GetMouseState(&x, &y);

     //if we click to the canon
     if (!active){
          if (e.type == SDL_MOUSEBUTTONDOWN && x >= SCREEN_WIDTH / 2 && x <= SCREEN_WIDTH / 2 + Canon.getWidth() && y >= y_coordinate && y <= Canon.getHeight() + y_coordinate){
               active = true;
               startTime = SDL_GetTicks();
          }
     }

     //if we release to the canon
     else {
          if (e.type == SDL_MOUSEBUTTONUP && x >= SCREEN_WIDTH / 2 && x <= SCREEN_WIDTH / 2 + Canon.getWidth() && y >= y_coordinate && y <= Canon.getHeight() + y_coordinate){
               active = false;
               BallActive = true;
               ballStartTime = SDL_GetTicks();
               ballAngle = 45 - max(1.0 * (-30), 1.0 * 45 - (1.0 * SDL_GetTicks() - startTime) / 50);
          }
     }
}



