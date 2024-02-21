#include "Playing_field.h"
#include "Game.h"
#include <bits/stdc++.h>

Well :: Well (int _x, int _y){
    x = _x;
    y = _y;
    //marked no tetromino unites with well
    memset(matrix, false, sizeof(matrix));

    //all initial cell colors is black
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 20; j++){
            cell_colors[i][j] = {0, 0, 0, 255};
        }
    }
};

Well :: ~Well()
{
    memset(matrix, 0, sizeof(matrix));
    for (int i = 0; i < WIDE_CELLS; i++){
        for (int j = 0; j < HEIGHT_CELLS; j++){
            cell_colors[i][j] = {0, 0, 0, 255};
        }
    }
}

void Well :: draw (SDL_Renderer *renderer)
{
    //black color
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    //the well rect
    SDL_Rect rect = {x, y, width, height};

    //fill well with black
    SDL_RenderFillRect(renderer, &rect);

    //red color
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    //draw border
    SDL_RenderDrawRect(renderer, &rect);

    //white color
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int i = 0; i < WIDE_CELLS; i++){
        for (int j = 0; j < HEIGHT_CELLS; j++){
            //if there is a tetromino uniting with the well
            if (matrix[i][j]){
                //get the tetromino color
                SDL_Color curColor = cell_colors[i][j];

                //set color
                SDL_SetRenderDrawColor(renderer, curColor.r, curColor. g, curColor.b, 255);

                //the rect of each tile
                SDL_Rect rect = {i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE};

                //file rect
                SDL_RenderFillRect(renderer, &rect);

                //draw black color
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderDrawRect(renderer, &rect);
            }
            else{
                //draw white point
                SDL_RenderDrawPoint(renderer, i * TILE_SIZE + (SCREEN_WIDTH - width) / 2, j * TILE_SIZE + (SCREEN_HEIGHT - height) / 2);
            }
        }
    }
}

int Well :: get_x()
{
    return (SCREEN_WIDTH - width) / 2;
}

int Well :: get_y()
{
    return (SCREEN_HEIGHT - height) / 2;
}

int Well :: get_width()
{
    return this->get_x() + width;
}

int Well :: get_height()
{
    return this->get_y() + height;
}

int Well :: get_pos_x(int PosX)
{
    return this->get_x() + PosX * TILE_SIZE;
}

int Well :: get_pos_y(int PosY)
{
    return this->get_y() + PosY * TILE_SIZE;
}

