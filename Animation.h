#pragma once
#include "Texture.h"
class Animation{
public:
     //constructor
     Animation ();

     //destructor
     ~Animation();

     //draw animation
     void render(SDL_Renderer *renderer);
private:
     //main texture
     LTexture *mTexture;

     //the current position
     int x, y;

     //
     int windV, gravity;

     //current dimentsion(used to rotate animation around z axis)
     int width;
     int height;

     //rotate around y axis
     double angle;

     //calculate the frame object rend
     int mFrame;

     //the smaller(far) object is, the less opacity
     int opacity;

     //used to shrink animation
     int shrinkX;
     int shrinkY;

     //rotate around z axis
     int rotateX;

     //object is shrinking or not
     bool isShrink;
};