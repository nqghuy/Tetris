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
    //set false to able to rotate and drop
    rotate = false;
    dropped = false;

    //the first shape
    angle = 0;

    //set coordinate
    x_coordinate = x;
    y_coordinate = y;

    //default velocity
    VelX = 0;
    VelY = 0;
}

Tetromino ::~Tetromino(){}

void Tetromino :: draw(SDL_Renderer *renderer, Well &well)
{
    for (int i = 0; i < TETRAD_SIZE; i++){
        for (int j = 0; j < TETRAD_SIZE; j++){
            //if this coordinate is a block
            if (TetrominoShape[i][j]){

                //if this block do not present in well
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

void Tetromino :: draw_ghost_tetromino(SDL_Renderer *renderer, Well &well){
    //the copy of this tetromino
    Tetromino ghost = *this;

    //find the position
    while (!ghost.check_bottom_collision(well)){
        ghost.y_coordinate ++;
    }
    ghost.y_coordinate--;

    for (int i = 0; i < TETRAD_SIZE; i++){
        for (int j = 0; j < TETRAD_SIZE; j++){
            //if this coordinate is a block
            if (ghost.TetrominoShape[i][j]){

                //if this block do not present in well
                if (ghost.y_coordinate + i < HIDDEN_ROWS){
                    continue;
                }

                //rect of each tile
                SDL_Rect rect = {well.get_pos_x(ghost.x_coordinate) + j * TILE_SIZE, well.get_pos_y(ghost.y_coordinate) + i * TILE_SIZE, TILE_SIZE, TILE_SIZE};

                //color of this tetromino
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderFillRect(renderer, &rect);

                //draw border with black
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
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

//handle event for player 2
void Tetromino :: handle_event2(SDL_Event &e, Well &well){

    //if enter is pressed
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0){
        if (e.key.keysym.sym == SDLK_RETURN){
            //drop
            this->drop(well);
        }
    }

    //current key state, true if this key is pressed
    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

    //if key down is pressed
    if( currentKeyStates[ SDL_SCANCODE_DOWN ] )
    {
        if (VelY == 0){//avoid repeated key
            this->VelY = 1;
           //return;
        }
    }

    //if key down is released
    else if(VelY != 0){
        VelY = 0;
        //return;
    }

    //key right is pressed
    if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
    {
        if(VelX == 0) {
            this->VelX = 1;
            return;
        }
    }//if key right is released
    else if (VelX != 0){
        VelX = 0;
        return;
    }

    //if key up is pressed
    if( currentKeyStates[ SDL_SCANCODE_UP ] )
    {
        //avoid repeated key
        if (!rotate){
            this->Rotate(well);
            rotate = true;
            return;
        }
        return;
    }

    //if key up is released
    else if(rotate){
        rotate = false;
        return;
    }

    //if key left is pressed
    if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
    {
        if(VelX == 0) {//if not repeated key
            this->VelX = -1;
            return;
        }
    }

    //if key left is released
    else if (VelX != 0){
        VelX = 0;
        return;
    }       

    

    
}

//handle event for player1
void Tetromino :: handle_event1(SDL_Event &e, Well &well){
    //drop if press space
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0){
        if (e.key.keysym.sym == SDLK_SPACE){
            this->drop(well);
        }
    }



    //current key state
    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

    //s is pressed
    if( currentKeyStates[ SDL_SCANCODE_S ] )
    {   
        if (VelY == 0){//avoid repeated key
            this->VelY = 1;
            //return;
        }
    }
    //released
    else if(VelY != 0){
        VelY = 0;
        //return;
    }

    //key d is pressed
    if( currentKeyStates[ SDL_SCANCODE_D ] )
    {   
        //avoid repeated ky
        if(VelX == 0) {
            this->VelX = 1;
            return;
        }
    }
    //key d is released
    else if (VelX != 0){
        VelX = 0;
        return;
    }

    //w is pressed
    if( currentKeyStates[ SDL_SCANCODE_W ] )
    {   
        //avoid repeated key
        if (!rotate){
            this->Rotate(well);
            rotate = true;
            return;
        }
        return;
    }
    
    //w is released
    else if(rotate){
        rotate = false;
        return;
    }

    //a is pressed
    if( currentKeyStates[ SDL_SCANCODE_A ] )
    {
        //avoid repeated key
        if(VelX == 0) {
            this->VelX = -1;
            return;
        }
    }
    //a is released
    else if (VelX != 0){
        VelX = 0;
        return;
    }       

    

    
}

void Tetromino :: handle_events(SDL_Event &e, Well &well, GameMode gameMode){
    if (gameMode == SinglePlay || gameMode == Player1)
    {
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
    //random tetro type
    Tetro_Type newType = Tetro_Type(rand() % 7);

    //if prev and new tetro type are identicl
    if (newType == prev.TetrominoType){
        //random new tetro type to reduce the two identical tetrotype probality
        newType = Tetro_Type(rand() % 7);
    }
    return newType;
}

void Tetromino :: drop(Well &well){
    while(!this->check_bottom_collision(well)){
        y_coordinate++;
    }
    Mix_PlayChannel(-1, gDropSoundEffect, 0);
    VelX = 0;
    VelY = 0;
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
