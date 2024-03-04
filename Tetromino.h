#ifndef Tetromino_h
#define Tetromino_h
#include "Data.h"
#include "include/SDL2/SDL.h"

//avoid circular dependencies
class Well;

//types of tetromino
enum Tetro_Type{
    I_BLOCK, J_BLOCK, L_BLOCK, O_BLOCK, S_BLOCK, T_BLOCK, Z_BLOCK, TOTAL_OF_BLOCKS
};

//colors of each type
static SDL_Color Tetromino_color[TOTAL_OF_BLOCKS] =
{{0, 255, 255},
{0, 100, 255},
{255, 115, 0},
{255, 255, 0},
{0, 255, 0},
{128, 0, 255},
{255, 0, 0}};

//shape of each type (include rotated shape)
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

    {{0, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 0, 0}},


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

    {{0, 1, 0, 0},
    {0, 1, 0, 0},
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
    //constructor, x, y is the position
    Tetromino(Tetro_Type _TetrominoType, int x, int y);

    //destructor
    ~Tetromino();

    //draw tetromino in the screen
    void draw(SDL_Renderer *renderer, Well &well);

    //rotate the tetromino when up key is pressed, if collision, no rotate
    void Rotate(Well &well);

    //move down, left and right and check collision
    void Move(Well &well);

    //handle event e
    void handle_events(SDL_Event &e, Well &well);

    //check if coordinate x, y is one of the part of the shape
    bool isBlock(int x, int y);

    //return coordinate according to the well
    int get_x_axis_coor();
    int get_y_axis_coor();

    //return tetromino's color
    SDL_Color get_color();

    //check if left or right collision happens
    bool check_left_collision(Well &well);
    bool check_right_collision(Well &well);

    //check if bottom collision happens
    bool check_bottom_collision(Well &well);

    //move down every 1s
    bool free_fall(Well &well);

    //get active
    bool get_active();

    //decrease the percentage of two similar tetrads
    Tetro_Type get_random_type();
private:
    //false if cannot move down
    bool active;

    //type of tetromino
    Tetro_Type TetrominoType;

    //position according to well
    int x_coordinate, y_coordinate;

    //current velocity
    int VelX, VelY;

    //used to rotate, 0 is 0 degree, 1 is 90 degree...
    int angle;

    //color corresponding to the type
    SDL_Color TetrominoColor;

    //the shape matrix (true if is is a block
    bool TetrominoShape[TETRAD_SIZE][TETRAD_SIZE];

};

#endif // Tetromino_h



