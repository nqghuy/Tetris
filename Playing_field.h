#ifndef Playing_field_h
#define Playing_field_h

#include <SDL.h>
#include <iostream>
#include "Tetromino.h"
#include "Data.h"

class Well
{
public:
    //constructor
    Well();

    //destructor
    ~Well();

    //draw the well in the screen
    void draw(SDL_Renderer *renderer);

    //get the coordinate of the well rect
    int get_x();
    int get_y();

    //get the dimension of the well
    int get_width();
    int get_height();
private:
    //the dimension of the well
    int width = TILE_SIZE * WIDE_CELLS;
    int height = TILE_SIZE * HEIGHT_CELLS;

    //return true if there is a tile in this coordinates
    bool matrix[WIDE_CELLS][HEIGHT_CELLS];

    //the color corresponding to each cell
    SDL_Color cell_colors[WIDE_CELLS][HEIGHT_CELLS];
};

#endif
