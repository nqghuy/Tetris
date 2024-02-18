#pragma once
#include "Playing_field.h"

const int TETRAD_SIZE = 4;

enum Tetro_Type{
    I_BLOCK, J_BLOCK, L_BLOCK, O_BLOCK, S_BLOCK, T_BLOCK, Z_BLOCK, TOTAL_OF_BLOCKS
};


static SDL_Color Tetromino_color[TOTAL_OF_BLOCKS] =
{{0, 255, 255},
{0, 100, 255},
{255, 115, 0},
{255, 255, 0},
{0, 255, 0},
{128, 0, 255},
{255, 0, 0}};

static bool tetromino_shape[TOTAL_OF_BLOCKS][TETRAD_SIZE][TETRAD_SIZE] =
{
    {{0, 0, 0, 0},
    {1, 1, 1, 1},
    {0, 0, 0, 0},
    {0, 0, 0, 0}},

    {{1, 0, 0, 0},
    {1, 1, 1, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}},

    {{0, 0, 0, 1},
    {0, 1, 1, 1},
    {0, 0, 0, 0},
    {0, 0, 0, 0}},

    {{0, 0, 0, 0},
    {0, 1, 1, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0}},

    {{0, 0, 0, 0},
    {0, 0, 1, 1},
    {0, 1, 1, 0},
    {0, 0, 0, 0}},

    {{0, 1, 0, 0},
    {1, 1, 1, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}},

    {{0, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0}}
};

class Tetromino
{
public:
    Tetromino(Tetro_Type _TetrominoType, int x, int y);
    ~Tetromino();
    void draw(SDL_Renderer *renderer);
    void Rotate();
    void speed_up();
    void slow_down();
    void Move();
    int TeTroVelocity = 36;
    void handle_events(SDL_Event &e);
private:
    int PosX, PosY;
    int VelX, VelY;
    Tetro_Type TetrominoType;
    SDL_Color TetrominoColor;
    bool TetrominoShape[TETRAD_SIZE][TETRAD_SIZE];
};
