#ifndef Playing_field_h
#define Playing_field_h

#include <SDL.h>
#include <iostream>
#include "Tetromino.h"
#include "Data.h"

class Well
{
public:
    Well();
    void draw(SDL_Renderer *renderer);
    int get_x();
    int get_y();
    int get_width();
    int get_height();
private:
    int width = TILE_SIZE * WIDE_CELLS;
    int height = TILE_SIZE * HEIGHT_CELLS;
    bool matrix[10][20];
    SDL_Color cell_colors[10][20];
};

#endif
