#include "Animation.h"

const int snowWidth = 150;
const int snowHeight = 120;
const int leafDimension = 100;

Animation :: Animation(){
     theme = Autumn;

     //set position
     x = rand() % SCREEN_WIDTH;
     
     //random wind and gravity
     windV = rand() % 2;
     gravity = rand() % 4 + 1;

     //random wind is positive or negative
     int tmp = rand() % 2 + 1;
     if (tmp % 2){
          windV = - windV;
     }

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
     rotateX = rand() % 2  +1;

     //set default texture
     if (theme == Autumn){
          mTexture = &gLeafTexture;
          y = -leafDimension;
          //cheat set width, height 
          width = leafDimension  / shrinkX;
          height = leafDimension / shrinkY;

     }
     else {
          mTexture = &gSnowTexture;
          y = - snowHeight;
          width = snowWidth  / shrinkX;
          height = snowHeight / shrinkY;          
     }

     //the object is in max size so shrink it
     isShrink = true;
}

Animation :: ~Animation(){
     mTexture = NULL;
}

void Animation :: set_theme(Theme _theme){
     theme = _theme;
     if (_theme == Winter){
          mTexture = &gSnowTexture;
     }
     else mTexture = &gLeafTexture;
}

 void Animation :: reset(){
      //set position
     x = rand() % SCREEN_WIDTH;
     
     //random wind and gravity
     windV = rand() % 2;
     gravity = rand() % 4 + 1;

     //random wind is positive or negative
     int tmp = rand() % 2 + 1;
     if (tmp % 2){
          windV = - windV;
     }

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

     //set default texture
     if (theme == Autumn){
          mTexture = &gLeafTexture;
          y = -leafDimension;
          //cheat set width, height 
          width = leafDimension  / shrinkX;
          height = leafDimension / shrinkY;

     }
     else {
          mTexture = &gSnowTexture;
          y = - snowHeight;
          width = snowWidth  / shrinkX;
          height = snowHeight / shrinkY;          
     }

     //the object is in max size so shrink it
     isShrink = true;
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
     if ((mFrame % 3) == 0){
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
               if (width >= mTexture->getWidth() / shrinkX){
                    isShrink = true;
               }
          } 
     }
     if (y > SCREEN_HEIGHT || x > SCREEN_WIDTH || x + mTexture->getWidth() < 0 || y + mTexture->getHeight() < 0){
          reset();
     }
}