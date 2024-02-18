#include "Tetromino.h"
#include <iostream>
#include "Game.h"
using namespace std;
Tetromino :: Tetromino(Tetro_Type _TetrominoType, int x, int y)
{
    TetrominoType = _TetrominoType;
    TetrominoColor = Tetromino_color[TetrominoType];
    for (int i = 0; i < TETRAD_SIZE; i++){
        for (int j = 0; j < TETRAD_SIZE; j++){
            TetrominoShape[i][j] = tetromino_shape[TetrominoType][i][j];
        }
    }
    PosX = x;
    PosY = y;
    VelX = 0;
    VelY = 0;
}

Tetromino ::~Tetromino(){}

void Tetromino :: draw(SDL_Renderer *renderer)
{
    for (int i = 0; i < TETRAD_SIZE; i++){
        for (int j = 0; j < TETRAD_SIZE; j++){
            if (TetrominoShape[i][j]){
                SDL_SetRenderDrawColor(renderer, TetrominoColor.r, TetrominoColor. g, TetrominoColor.b, 255);
                SDL_Rect rect = {PosX + i * TILE_SIZE, PosY + j * TILE_SIZE, TILE_SIZE, TILE_SIZE};
                SDL_RenderFillRect(renderer, &rect);
                SDL_RenderDrawRect(renderer, &rect);
            }
        }
    }
}

void Tetromino :: Rotate()
{

    bool initial_shape[TETRAD_SIZE][TETRAD_SIZE];
    for (int i = 0; i < TETRAD_SIZE; i++){
        for (int j = 0; j < TETRAD_SIZE; j++){
            initial_shape[i][j] = TetrominoShape[i][j];
        }
    }
    for (int i = 0; i < TETRAD_SIZE; i++){
        for (int j = 0; j < TETRAD_SIZE; j++){
            TetrominoShape[i][j] = initial_shape[j][i];
        }
    }
    for (int i = 0; i < TETRAD_SIZE; i++){
        for (int j = 0; j < TETRAD_SIZE; j++){
            TetrominoShape[j][TETRAD_SIZE - i - 1] = initial_shape[i][j];
        }
    }
}

void Tetromino :: speed_up(){
    VelY += TeTroVelocity;
}

void Tetromino :: slow_down()
{
    VelY -= TeTroVelocity;
}

void Tetromino :: Move()
{
    PosX += VelX;
    PosY += VelY;
}

void Tetromino :: handle_events(SDL_Event &e){
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0){
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
            this->Rotate();
            break;
        case (SDLK_DOWN):
            this->speed_up();
            break;
        }
    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0){
        switch (e.key.keysym.sym){
            case (SDLK_DOWN):
                this->slow_down();
                break;
        }
    }
    this->Move();
}
