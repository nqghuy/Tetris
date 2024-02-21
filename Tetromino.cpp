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
    x_coordinate = x;
    y_coordinate = y;
    VelX = 0;
    VelY = 0;
}

Tetromino ::~Tetromino(){}

void Tetromino :: draw(SDL_Renderer *renderer, Well &well)
{
    for (int i = 0; i < TETRAD_SIZE; i++){
        for (int j = 0; j < TETRAD_SIZE; j++){
            if (TetrominoShape[i][j]){
                //color of this tetromino
                SDL_SetRenderDrawColor(renderer, TetrominoColor.r, TetrominoColor. g, TetrominoColor.b, 255);

                //rect of each tile
                SDL_Rect rect = {well.get_pos_x(this->x_coordinate) + j * TILE_SIZE, well.get_pos_y(this->y_coordinate) + i * TILE_SIZE, TILE_SIZE, TILE_SIZE};

                //fill rect
                SDL_RenderFillRect(renderer, &rect);

                //draw border with black
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderDrawRect(renderer, &rect);
            }
        }
    }
}

//rotate the tetromino by using next shape
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
    while(this->check_left_collision()){
        this->x_coordinate++;
    }
    while (this->check_right_collision()){
        x_coordinate--;
    }
    while (this->check_bottom_collision())
    {
        y_coordinate--;
    }
}

void Tetromino :: Move(Well &well)
{
    x_coordinate += VelX;
    y_coordinate += VelY;

    //check if a collision happens
    if (this->check_left_collision() || this->check_right_collision()){
        x_coordinate -= VelX;
    }
    if (this->check_bottom_collision()){
        y_coordinate -= VelY;
    }
}

void Tetromino :: handle_events(SDL_Event &e){
    //when player is pressing a key
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0){
        switch (e.key.keysym.sym)
        {
        //key up: rotate
        case SDLK_UP:
            this->Rotate();
            break;

        //key down: increase y velocity
        case SDLK_DOWN:
            VelY += TetroVelocity;
            break;

        //key right: increase x velocity
        case SDLK_RIGHT:
            VelX += TetroVelocity;
            break;

        //key left: decrease x veloity
        case SDLK_LEFT:
            VelX -= TetroVelocity;
            break;
        }
    }
    //when player release a key
    else if (e.type == SDL_KEYUP && e.key.repeat == 0){
        switch (e.key.keysym.sym){
            //opposite to pressing a key
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

bool Tetromino :: check_left_collision()
{
    for (int i = 0; i < TETRAD_SIZE; i++){
        for (int j = 0; j < TETRAD_SIZE; j++){
            if(this->TetrominoShape[i][j] == true){
                //left border
                int left = x_coordinate + j;

                //check if collision
                if (left < 0)
                    return true;
            }
        }
    }
    return false;
}

bool Tetromino :: check_right_collision()
{
    for (int i = 0; i < TETRAD_SIZE; i++){
        for (int j = 0; j < TETRAD_SIZE; j++){
            if(this->TetrominoShape[i][j] == true){
                //right border
                int right = x_coordinate + 1 + j;

                //check if collision
                if (right > WIDE_CELLS)
                    return true;
            }
        }
    }
    return false;
}

bool Tetromino :: check_bottom_collision()
{
    for (int i = 0; i < TETRAD_SIZE; i++){
        for (int j = 0; j < TETRAD_SIZE; j++){
            if (TetrominoShape[i][j])
            {
                int bottom = this->y_coordinate + i;
                if (bottom >= HEIGHT_CELLS)
                {
                    return true;
                }
            }
        }
    }
}

bool Tetromino :: isBlock(int x, int y)
{
    return this->TetrominoShape[x][y];
}

int Tetromino :: get_x_axis_coor(){
    return x_coordinate;
}

int Tetromino :: get_y_axis_coor()
{
    return y_coordinate;
}

SDL_Color Tetromino :: get_color()
{
    return TetrominoColor;
}

bool Tetromino :: free_fall()
{
    this->y_coordinate++;
    while(this->check_left_collision()){
        this->x_coordinate++;
    }
    while (this->check_right_collision()){
        x_coordinate--;
    }
    while (this->check_bottom_collision())
    {
        y_coordinate--;
    }
}

