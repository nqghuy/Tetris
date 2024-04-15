#include "Volume.h"
#include <math.h>

Volume :: Volume(){
     active = false;
     startTime = 0;
     gravity = 40;
     BallActive = false;
     ballX = ballY = 0;
     ballAngle = 0;
}

int Volume :: y_coordinate = 700;
int Volume :: Ball_Velocity = 100;
Volume :: ~Volume(){
     Canon.free();
     Pedestal.free();
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
     ballX = 1.0 * SCREEN_WIDTH / 2 + Canon.getWidth() / 2;
     ballY = 1.0 * y_coordinate + Canon.getHeight() / 5;
     return success;
}

void Volume :: display(SDL_Renderer *renderer){
     VolumeText.render(renderer, (SCREEN_WIDTH - MenuBackground.getWidth()) / 2 + 50, y_coordinate);

     int VolumeRectX = SCREEN_WIDTH / 2 + Canon.getWidth() * 1.5;
     int VolumeRectY = y_coordinate + Canon.getHeight() / 2;
     
     SDL_Rect volumeRect = {VolumeRectX, VolumeRectY, 200, 5};
     SDL_SetRenderDrawColor(renderer, 158, 158, 158, 255);
     SDL_RenderFillRect(renderer, &volumeRect);

     double angle = max(1.0 * (-30), 1.0 * 45 - (1.0 * SDL_GetTicks() - startTime) / 50 );

     double x0 = 1.0 * SCREEN_WIDTH / 2 + Canon.getWidth() / 2;
     double y0 = 1.0 * y_coordinate + Canon.getHeight() / 5;
     if (BallActive){
          double t = (1.0 * SDL_GetTicks() - ballStartTime) / 1000;
          ballX = x0 + 1.0 * Ball_Velocity * cos(M_PI / 180 * ballAngle) * t;
          ballY = y0 - 1.0 * Ball_Velocity * sin(M_PI / 180 * ballAngle) * t  + 1.0 / 2 * gravity * t * t;
          if (ballY + Ball.getHeight() / 2 == VolumeRectY){
               BallActive = false;
               Mix_Volume(-1, 1.0 * MIX_MAX_VOLUME / volumeRect.w * (ballX - VolumeRectX));
               Mix_VolumeMusic(1.0 * MIX_MAX_VOLUME / volumeRect.w * (ballX - VolumeRectX));
               cout << 1.0 * MIX_MAX_VOLUME / 200 * (ballX - VolumeRectX);
          }
     }
     Ball.render(renderer, ballX, ballY); 
     if (active){
          Canon.render(renderer, SCREEN_WIDTH / 2, y_coordinate, NULL, NULL, angle);
     }
     else{
          Canon.render(renderer, SCREEN_WIDTH / 2, y_coordinate, NULL, NULL, 45);
     }
     Pedestal.render(renderer, SCREEN_WIDTH / 2, y_coordinate);
     
}

void Volume :: handle_event(SDL_Event &e){
     int x, y;
     SDL_GetMouseState(&x, &y);
     if (!active){
          if (e.type == SDL_MOUSEBUTTONDOWN && x >= SCREEN_WIDTH / 2 && x <= SCREEN_WIDTH / 2 + Canon.getWidth() && y >= y_coordinate && y <= Canon.getHeight() + y_coordinate){
               active = true;
               startTime = SDL_GetTicks();
          }
     }
     else {
          if (e.type == SDL_MOUSEBUTTONUP && x >= SCREEN_WIDTH / 2 && x <= SCREEN_WIDTH / 2 + Canon.getWidth() && y >= y_coordinate && y <= Canon.getHeight() + y_coordinate){
               active = false;
               BallActive = true;
               ballStartTime = SDL_GetTicks();
               ballAngle = 45 - max(1.0 * (-30), 1.0 * 45 - (1.0 * SDL_GetTicks() - startTime) / 50);
          }
     }
}



