#pragma once
#include <SDL.h>
#include <iostream>

const int TILE_SIZE = 36;
const int WIDE_CELLS = 10;
const int HEIGHT_CELLS = 20;


class Well
{
public:
    Well();
    void draw(SDL_Renderer *renderer);
private:
    int width = TILE_SIZE * WIDE_CELLS;
    int height = TILE_SIZE * HEIGHT_CELLS;

    bool matrix[10][20];
};
