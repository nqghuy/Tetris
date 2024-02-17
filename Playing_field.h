#pragma once
#include <SDL.h>
#include <iostream>
class Well
{
public:
    Well();
    void draw(SDL_Renderer *renderer);
private:
    int width = 350;
    int height = 770;
    int wideCells = 10;
    int heighCells = 22;
    int blockDimension = 35;
};
