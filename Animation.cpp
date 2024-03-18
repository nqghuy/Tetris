#include "Animation.h"
#include "Data.h"

const int snowWidth = 150;
const int snowHeight = 120;
const int leafDimension = 100;

Animation :: Animation(){
     //set position
     x = rand() % SCREEN_WIDTH;
     y = -leafDimension;

     //random wind and gravity
     windV = rand() % 3;
     gravity = rand() % 5 + 1;

     //random wind is positive or negative
     int tmp = rand() % 2 + 1;
     if (tmp % 2){
          windV = - windV;
     }


     //set default texture
     mTexture = &gLeafTexture;

     //the first angle
     angle = rand() % 180;

     //the initial frame is zero
     mFrame = 0;
     
     //the shrink ratio
     shrinkX = rand() % 5 + 1;
     shrinkY = shrinkX;

     //opacity according to shrink
     opacity = min(255 / (shrinkX) + 30, 255);

     //random rotate speed
     rotateX = rand() % 2 + 1;

     //cheat set width, height 
     width = leafDimension  / shrinkX;
     height = leafDimension / shrinkY;

     //the object is in max size so shrink it
     isShrink = true;
}

Animation :: ~Animation(){
     mTexture = NULL;
}

void Animation :: render(SDL_Renderer *renderer){
     //set opacity before rend
     mTexture->setAlphaMode(opacity);

     //destination rect
     SDL_Rect desRect = {x, y, width, height};

     //draw
     mTexture->render(renderer, x, y, NULL, &desRect, angle);

     //change mTexture
     mFrame++;

     //update position
     if ((mFrame % 4) == 0){
          y += gravity;
          angle += 1;
          
          //if object is shrinking
          if (isShrink){
               //update x position and width
               x += windV;
               width-= rotateX;

               //if object in smallest size
               if (width <= 0) {
                    isShrink = false;
               }
          }

          //if object is in large
          else{
               //new formulation
               x += windV - rotateX;

               //update width
               width += rotateX;

               //if object is in max size
               if (width >= gLeafTexture.getWidth() / shrinkX){
                    isShrink = true;
               }
          } 
     }
     if (y > SCREEN_HEIGHT || x > SCREEN_WIDTH || x + gLeafTexture.getWidth() < 0 || y + gLeafTexture.getHeight() < 0){
          *this = Animation();
     }
}