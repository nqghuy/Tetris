#pragma once

#include "include/SDL2/SDL.h"
#include "include/SDL2/SDL_image.h"
#include "include/SDL2/SDL_ttf.h"
#include <iostream>
#include <string>

using namespace std;

class LTexture
{
private:
    //the actual hardware texture
    SDL_Texture *mTexture;

    //image dimensions
    int mWidth;
    int mHeight;
public:
    // initialize variables
    LTexture();

    //deallocate memory
    ~LTexture() {};

    //load image from file
    bool loadFromFile(SDL_Renderer *renderer, string file, SDL_Color Color = {255, 255, 255});

    //create image from font string
    bool loadFromRenderedText(SDL_Renderer *renderer, TTF_Font *font, string textTexture, SDL_Color);

    //render texture at given point
    void render(SDL_Renderer *renderer, int, int, SDL_Rect* = NULL, SDL_Rect* rectQuad = NULL, double angle = 0, SDL_Point* center = NULL, SDL_RendererFlip = SDL_FLIP_NONE);

    //free memory
    void free();

    // set blend mode for texture
    void setBlendMode();

    //set the amount of alpha
    void setAlphaMode(Uint8 alpha);

    //increase or decrease color (r,g,b);
    void setColor(Uint8 red, Uint8 green, Uint8 blue);

    //gets image dimensions
    int getWidth();
    int getHeight();
};
