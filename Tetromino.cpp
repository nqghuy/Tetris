#include "Tetromino.h"
#include <iostream>
#include "Game.h"
#include "Playing_field.h"
using namespace std;
Tetromino :: Tetromino(Tetro_Type _TetrominoType, int x, int y)
{
    TetrominoType = _TetrominoType;
    TetrominoColor = Tetromino_color[TetrominoType];
    for (int i = 0; i < TETRAD_SIZE; i++){
        for (int j = 0; j < TETRAD_SIZE; j++){
            TetrominoShape[i][j] = tetromino_shape[TetrominoType * 4 ][i][j];
        }
    }
    angle = 0;
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
                SDL_Rect rect = {PosX + j * TILE_SIZE, PosY + i * TILE_SIZE, TILE_SIZE, TILE_SIZE};
                SDL_RenderFillRect(renderer, &rect);
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderDrawRect(renderer, &rect);
            }
        }
    }
}

void Tetromino :: Rotate()
{

    angle++;
    if (angle == 4){
        angle = 0;
    }
    for (int i = 0; i < TETRAD_SIZE; i++){
        for (int j = 0; j < TETRAD_SIZE; j++){
            TetrominoShape[i][j] = tetromino_shape[TetrominoType * 4 + angle][i][j];
        }
    }
}

void Tetromino :: Move(Well &well)
{

    PosX += VelX;
    PosY += VelY;
    if (this->check_left_right_collision(well)){
        PosX -= VelX;
    }
}

void Tetromino :: handle_events(SDL_Event &e){
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0){
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
            this->Rotate();
            break;
        case SDLK_DOWN:
            VelY += TetroVelocity;
            break;
        case SDLK_RIGHT:
            VelX += TetroVelocity;
            break;
        case SDLK_LEFT:
            VelX -= TetroVelocity;
            break;
        }
    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0){
        switch (e.key.keysym.sym){
            case (SDLK_DOWN):
                VelY -= TetroVelocity;
                break;
            case SDLK_RIGHT :
                VelX -= TetroVelocity;
                break;
            case SDLK_LEFT:
                VelX += TetroVelocity;
                break;
        }
    }
}

bool Tetromino :: check_left_right_collision(Well &well)
{
    for (int i = 0; i < TETRAD_SIZE; i++){
        for (int j = 0; j < TETRAD_SIZE; j++){
            if(this->TetrominoShape[i][j] == true){
                int right = PosX + (j + 1) * TILE_SIZE;
                int left = PosX + j * TILE_SIZE;
                if (right > well.get_width() || left < well.get_x())
                    return true;
            }
        }
    }
    return false;
}

bool Tetromino :: isBlock(int x, int y)
{
    return this->TetrominoShape[x][y];
}

int Tetromino :: get_pos_x(){
    return PosX;
}

int Tetromino :: get_pos_y()
{
    return PosY;
}

SDL_Color Tetromino :: get_color()
{
    return TetrominoColor;
}


