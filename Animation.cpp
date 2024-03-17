#include "Animation.h"
#include "Data.h"

Animation :: Animation(){
     x = rand() % SCREEN_WIDTH;
     y = 0;
     vX = 0;
     vY = rand() % 5;
     mTexture = &gLeafTexture;

     angle = rand() % 180;
     mFrame = 0;
     windV = rand() % 3;
     int tmp = rand() % 2;
     if (tmp % 2){
          windV = - windV;
     }
     shrinkX = rand() % 5 + 1;
     shrinkY = shrinkX;
     opacity = min(255 / (shrinkX) + rand() % 20, 255);
     rotateX = rand() % 3 + 1;
     // rotateY = rand() % 3 + 1;
     original_rotateX = rotateX;
     // original_rotateY = rotateY;

     width = 101 / shrinkX;
}

Animation :: Animation(int _x, int _y){
     x = _x;
     y = _y;
     mTexture = &gLeafTexture;
     mFrame = 0;
}

// bool Animation :: get_active(){
//      return mFrame < 20;
// }

void Animation :: render(SDL_Renderer *renderer){
     gLeafTexture.setAlphaMode(opacity);

     // if (width < 0 || height < 0 || width < gLeafTexture.getWidth() || height < gLeafTexture.getHeight()){
     //      rotate = -rotate;
     // }
     //gLeafTexture.getWidth() =101
     //gLeafTexture.getHeight() = 105;

     height = gLeafTexture.getHeight() / shrinkY;

     while(width <= 0){
          width += abs(rotateX);
          rotateX = -abs(rotateX);
     }
      while(width >= 101/shrinkX){
          width -= abs(rotateX);
          rotateX = abs(rotateX);
     }
     SDL_Rect desRect = {x, y, width, height};

     gLeafTexture.render(renderer, x, y, NULL, &desRect, angle);

     mFrame++;
     if ((mFrame % 4) == 0){
          y += vY;
          angle += 1;
          x += windV;
          width  -= rotateX;
     }
     if (y > SCREEN_HEIGHT || x > SCREEN_WIDTH || x + gLeafTexture.getWidth() < 0 || y + gLeafTexture.getHeight() < 0){
          x = rand() % SCREEN_WIDTH;
          y = 0;
          vX = 0;
          vY = rand() % 5;
          mTexture = &gLeafTexture;

          angle = rand() % 180;
          mFrame = 0;
          windV = rand() % 3;
          int tmp = rand() % 2;
          if (tmp % 2){
               windV = - windV;
          }
          shrinkX = rand() % 5 + 1;
          shrinkY = shrinkX;
          opacity = min(255 / (shrinkX) + rand() % 20, 255);
          rotateX = rand() % 3 + 1;
          rotateY = rand() % 3 + 1;
          original_rotateX = rotateX;
          original_rotateY = rotateY;

     }
}