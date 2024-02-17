#include "Tetromino.h"
#include <iostream>

using namespace std;
tetromino :: tetromino()
{
    type = O_BLOCK;
    tetrominoColor = Tetromino_color[type];
    for (int i = 0; i < TETRAD_SIZE; i++){
        for (int j = 0; j < TETRAD_SIZE; j++){
            shape[i][j] = tetromino_shape[type][i][j];
        }
    }
}

tetromino ::~tetromino(){}

void tetromino :: draw(SDL_Renderer *renderer)
{
    for (int i = 0; i < TETRAD_SIZE; i++){
        for (int j = 0; j < TETRAD_SIZE; j++){
            if (shape[i][j]){
                SDL_SetRenderDrawColor(renderer, tetrominoColor.r, tetrominoColor. g, tetrominoColor.b, 255);
                SDL_Rect rect = {320 + i * TILE_SIZE, 400 + j * TILE_SIZE, TILE_SIZE, TILE_SIZE};
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}
