#ifndef Tetromino_h
#define Tetromino_h
#include "Data.h"
#include <SDL.h>

class Well;

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

static bool tetromino_shape[TOTAL_OF_BLOCKS * 4][TETRAD_SIZE][TETRAD_SIZE] =
{
    //I_BLOCK
    {{0, 0, 0, 0},
    {1, 1, 1, 1},
    {0, 0, 0, 0},
    {0, 0, 0, 0}},

    {{0, 0, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 1, 0}},

    {{0, 0, 0, 0},
    {1, 1, 1, 1},
    {0, 0, 0, 0},
    {0, 0, 0, 0}},

    {{0, 0, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 1, 0}},


    //J_BLOCK
    {{1, 0, 0, 0},
    {1, 1, 1, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}},

    {{0, 1, 1, 0},
    {0, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 0, 0}},

    {{0, 0, 0, 0},
    {1, 1, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 0}},

    {{1, 0, 0, 0},
    {1, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 0, 0, 0}},

    //L_BLOCK
    {{0, 0, 1, 0},
    {1, 1, 1, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}},

    {{0, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0}},

    {{0, 0, 0, 0},
    {1, 1, 1, 0},
    {1, 0, 0, 0},
    {0, 0, 0, 0}},

    {{1, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 0, 0}},

    //O_BLOCK
    {{0, 0, 0, 0},
    {0, 1, 1, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0}},

    {{0, 0, 0, 0},
    {0, 1, 1, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0}},

    {{0, 0, 0, 0},
    {0, 1, 1, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0}},

    {{0, 0, 0, 0},
    {0, 1, 1, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0}},

    //S_BLOCK

    {{0, 0, 0, 0},
    {0, 1, 1, 0},
    {1, 1, 0, 0},
    {0, 0, 0, 0}},

    {{1, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 0, 0}},

    {{0, 0, 0, 0},
    {0, 1, 1, 0},
    {1, 1, 0, 0},
    {0, 0, 0, 0}},

    {{1, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 0, 0}},

    //T_BLOCK
    {{0, 0, 0, 0},
    {0, 1, 0, 0},
    {1, 1, 1, 0},
    {0, 0, 0, 0}},

    {{1, 0, 0, 0},
    {1, 1, 0, 0},
    {1, 0, 0, 0},
    {0, 0, 0, 0}},

    {{1, 1, 1, 0},
    {0, 1, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}},

    {{0, 0, 1, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 0}},

    //Z_BLOCK
    {{0, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0}},

    {{0, 1, 0, 0},
    {1, 1, 0, 0},
    {1, 0, 0, 0},
    {0, 0, 0, 0}},

    {{0, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0}},

    {{0, 1, 0, 0},
    {1, 1, 0, 0},
    {1, 0, 0, 0},
    {0, 0, 0, 0}},
};

class Tetromino
{
public:
    Tetromino(Tetro_Type _TetrominoType, int x, int y);
    ~Tetromino();
    void draw(SDL_Renderer *renderer);
    void Rotate();
    void Move(Well &well);
    void handle_events(SDL_Event &e);
    bool isBlock(int x, int y);
    int get_pos_x();
    int get_pos_y();
    SDL_Color get_color();
    bool check_left_right_collision(Well &well);
    //grid coordinate
    void Move();
    int TetroVelocity = TILE_SIZE;
private:
    Tetro_Type TetrominoType;
    int PosX, PosY;
    int VelX, VelY;
    int angle;
    SDL_Color TetrominoColor;
    bool TetrominoShape[TETRAD_SIZE][TETRAD_SIZE];
};

#endif // Tetromino_h



