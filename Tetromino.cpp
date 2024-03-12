#include "Tetromino.h"
#include "Playing_field.h"
using namespace std;
Tetromino :: Tetromino(Tetro_Type _TetrominoType, int x, int y)
{
    active = true;
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
    // bool check = false;

    // //if tetromino is in hidden rows, do not draw
    // for (int i = 0; i < TETRAD_SIZE; i++){
    //     if(!check){
    //         for (int j = 0; j < TETRAD_SIZE; j++){
    //             if(TetrominoShape[i][j]){
    //                 if (this->y_coordinate + i < HIDDEN_ROWS){
    //                     return;
    //                 }
    //                 else {
    //                     check = true;
    //                     break;
    //                 }
    //             }
    //         }
    //     }
    // }
    for (int i = 0; i < TETRAD_SIZE; i++){
        for (int j = 0; j < TETRAD_SIZE; j++){
            if (TetrominoShape[i][j]){
                if (this->y_coordinate + i < HIDDEN_ROWS){
                    continue;
                }
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
void Tetromino :: Rotate(Well &well)
{
    //used if not rotate
    bool old_shape[TETRAD_SIZE][TETRAD_SIZE];
    bool old_angle = angle;

    //next shape
    angle++;
    if (angle == 4){
        angle = 0;
    }

    //set new shape
    for (int i = 0; i < TETRAD_SIZE; i++){
        for (int j = 0; j < TETRAD_SIZE; j++){
            old_shape[i][j] = TetrominoShape[i][j];
            TetrominoShape[i][j] = tetromino_shape[TetrominoType * 4 + angle][i][j];

        }
    }

    //if collision, do not rotate
    if (this->check_bottom_collision(well) || this->check_left_collision(well) || this->check_right_collision(well)){
        for (int i = 0; i < TETRAD_SIZE; i++){
            for (int j = 0; j < TETRAD_SIZE; j++){
                TetrominoShape[i][j] = old_shape[i][j];
                angle = old_angle;
            }
        }
    }
}

void Tetromino :: Move(Well &well)
{
    //set new coordinate
    x_coordinate += VelX;
    y_coordinate += VelY;

    //if go to last row
    bool finished = false;

    //check collision
    while(this->check_left_collision(well) && VelX < 0){
        this->x_coordinate++;
        VelX++;
    }
    while(this->check_right_collision(well) && VelX > 0)
    {
        this->x_coordinate--;
        VelX--;
    }

    //set finised true if go to last row
    if (this->check_bottom_collision(well))
    {
        this->y_coordinate--;
        finished = true;
    }

    //Unite tetromino with well and set active
    if(finished){
        well.Unite(this);
        active = false;
    }

}

void Tetromino :: handle_event2(SDL_Event &e, Well &well){
    //when player is pressing a key
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0){
        switch (e.key.keysym.sym)
        {
        //key up: rotate
        case SDLK_UP:
            this->Rotate(well);
            break;

        //key down: increase y velocity
        case SDLK_DOWN:
            this->VelY++;
            break;

        //key right: increase x velocity
        case SDLK_RIGHT:
            this->VelX++;
            break;

        //key left: decrease x veloity
        case SDLK_LEFT:
            this->VelX--;
            break;
        
        case SDLK_RETURN:
            this->drop(well);
            break;
        }
    }
    //when player release a key
    else if (e.type == SDL_KEYUP && e.key.repeat == 0){
        switch (e.key.keysym.sym){
            //opposite to pressing a key
            case (SDLK_DOWN):
                if(VelY != 0){
                    VelY--;
                }
                break;
            case SDLK_RIGHT :
                if (VelX != 0){
                    VelX--;
                }
                break;
            case SDLK_LEFT:
                if (VelX != 0){
                    VelX++;
                }
                break;
        }
    }
}

void Tetromino :: handle_event1(SDL_Event &e, Well &well){
    //when player is pressing a key
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0){
        switch (e.key.keysym.sym)
        {
        //key up: rotate
        case SDLK_w:
            this->Rotate(well);
            break;

        //key down: increase y velocity
        case SDLK_s:
            this->VelY++;
            break;

        //key right: increase x velocity
        case SDLK_d:
            this->VelX++;
            break;

        //key left: decrease x veloity
        case SDLK_a:
            this->VelX--;
            break;
        case SDLK_SPACE:
            this->drop(well);
            break;
        }
    }
    //when player release a key
    else if (e.type == SDL_KEYUP && e.key.repeat == 0){
        switch (e.key.keysym.sym){
            //opposite to pressing a key
            case (SDLK_s):
                if(VelY != 0){
                    VelY--;
                }
                break;
            case SDLK_d:
                if (VelX != 0){
                    VelX--;
                }
                break;
            case SDLK_a:
                if (VelX != 0){
                    VelX++;
                }
                break;
        }
    }
}

void Tetromino :: handle_events(SDL_Event &e, Well &well, GameMode gameMode){
    if (gameMode == SinglePlay)
    {
        handle_event2(e, well);
    }
    else if (gameMode == Player1){
        handle_event1(e, well);
    }
    else{
        handle_event2(e, well);
    }
}

bool Tetromino :: check_left_collision(Well &well)
{
    for (int i = 0; i < TETRAD_SIZE; i++){
        for (int j = 0; j < TETRAD_SIZE; j++){
            if(this->TetrominoShape[i][j] == true){
                //left border
                int left = x_coordinate + j;

                //coordinate along the Well
                int x = this->x_coordinate + j;
                int y = this->y_coordinate + i;

                //check if collision
                if (left < 0){
                    return true;
                }
                if (well.isBlock(x, y)){
                    return true;
                }
            }
        }
    }
    return false;
}

bool Tetromino :: check_right_collision(Well &well)
{
    for (int i = 0; i < TETRAD_SIZE; i++){
        for (int j = 0; j < TETRAD_SIZE; j++){
            if(this->TetrominoShape[i][j] == true){
                //right border
                int right = x_coordinate + 1 + j;

                //coordinate along the Well
                int x = this->x_coordinate + j;
                int y = this->y_coordinate + i;

                //check if collision
                if (right > WIDE_CELLS){
                    return true;
                }
                if (well.isBlock(x, y)){
                    return true;
                }
            }
        }
    }
    return false;
}

bool Tetromino :: check_bottom_collision(Well &well)
{
    for (int i = 0; i < TETRAD_SIZE; i++){
        for (int j = 0; j < TETRAD_SIZE; j++){
            if (TetrominoShape[i][j])
            {
                //bottom border
                int bottom = this->y_coordinate + i;

                //coordinate along the Well
                int x = this->x_coordinate + j;
                int y = this->y_coordinate + i;

                //if collision
                if (bottom >= HEIGHT_CELLS)
                {
                    return true;
                }
                if (well.isBlock(x, y)){
                    return true;
                }
            }
        }
    }
    return false;
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

void Tetromino :: free_fall(Well &well)
{
    //fall
    this->y_coordinate++;

    //marked if tetromino goes to the last row
    bool finised = false;

    //well unite tetromino and set active
    if(this->check_bottom_collision(well)){
        y_coordinate--;    
        active = false;
        well.Unite(this);
    }
}

bool Tetromino :: get_active()
{
    return active;
}


Tetro_Type Tetromino :: get_random_type(Tetromino &prev)
{
    Tetro_Type newType = Tetro_Type(rand() % 7);
    if (newType == prev.TetrominoType){
        newType = Tetro_Type(rand() % 7);
    }
    return newType;
}

void Tetromino :: drop(Well &well){
    while(!this->check_bottom_collision(well)){
        y_coordinate++;
    }
    VelX = 0;
    VelY = 0;
    // y_coordinate--;
    // well.Unite(this);
    // active = false;
}

Tetro_Type Tetromino :: get_tetro_type(){
    return TetrominoType;
}

void Tetromino :: draw (SDL_Renderer* renderer, int x, int y){
    for (int i = 0; i < TETRAD_SIZE; i++){
        for (int j = 0; j < TETRAD_SIZE; j++){
            if (TetrominoShape[i][j]){
                //color of this tetromino
                SDL_SetRenderDrawColor(renderer, TetrominoColor.r, TetrominoColor. g, TetrominoColor.b, 255);

                //rect of each tile
                SDL_Rect rect = {x + j * TILE_SIZE, y + i * TILE_SIZE, TILE_SIZE, TILE_SIZE};

                //fill rect
                SDL_RenderFillRect(renderer, &rect);

                //draw border with black
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderDrawRect(renderer, &rect);
            }
        }
    }
}
