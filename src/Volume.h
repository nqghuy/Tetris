#pragma once

#include "Texture.h"
#include "Data.h"

class Volume{
public:
     //constructor
     Volume();

     //destructor
     ~Volume();

     //load texture
     bool load_media(SDL_Renderer *renderer);

     //bang bang
     void handle_event (SDL_Event &e);

     //display on the screen
     void display(SDL_Renderer *renderer);

     //the y coordinate of volume class
     static int y_coordinate;

     //ball velocity
     static int Ball_Velocity;
private:
     //texture
     LTexture Canon;
     LTexture Pedestal;
     LTexture Ball;
     LTexture VolumeText;

     //true if we hold canon
     bool active;

     // the first time we click to canon
     int startTime;

     //gravity of the ball
     int gravity;

     // if we release canon
     bool BallActive;
     
     //the position of the ball
     int ballX, ballY;

     //the angle when shotting the ball
     double ballAngle;

     //the time the ball move
     int ballStartTime;

};