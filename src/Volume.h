#pragma once

#include "Texture.h"
#include "Data.h"

class Volume{
public:
     Volume();
     ~Volume();
     bool load_media(SDL_Renderer *renderer);
     void handle_event (SDL_Event &e);
     void display(SDL_Renderer *renderer);
     static int y_coordinate;
     static int Ball_Velocity;
private:
     LTexture Canon;
     LTexture Pedestal;
     LTexture Ball;
     LTexture VolumeText;
     bool active;
     int startTime;
     int gravity;
     bool BallActive;
     
     int ballX, ballY;
     double ballAngle;
     int ballStartTime;

};