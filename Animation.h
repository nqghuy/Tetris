#pragma once
#include "Texture.h"
class Animation{
public:
     Animation ();
     Animation(int _x, int _y);
     // ~Animation();
     //bool get_active();
     void render(SDL_Renderer *renderer);
private:
     LTexture *mTexture;
     int x, y;
     int vX, vY;

     int width;
     int height;

     double angle;
     int mFrame;
     int windV;
     int opacity;

     int shrinkX;
     int shrinkY;

     int rotateX;
     int rotateY;
     int original_rotateX;
     int original_rotateY;

};