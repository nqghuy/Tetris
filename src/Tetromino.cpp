#include "Tetromino.h"
#include "Playing_field.h"
#include <cstring>
#include <math.h>
using namespace std;

Tetromino :: Tetromino (Tetro_Type _TetrominoType, int x, int y, Well &well, GameMode _gameMode)
{
    gameMode = gameMode;

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

    finalX = 0;
    finalAngle = 0;

    if (gameMode == Bot){
        this->greedy(well);
    }

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
bool Tetromino :: Rotate(Well &well)
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

    bool ok = true;

    //if collision, do not rotate
    if (this->check_bottom_collision(well) || this->check_left_collision(well) || this->check_right_collision(well)){
        for (int i = 0; i < TETRAD_SIZE; i++){
            for (int j = 0; j < TETRAD_SIZE; j++){
                TetrominoShape[i][j] = old_shape[i][j];
                angle = old_angle;
                ok = false;
            }
        }
    }
    return ok;
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
            return;
        }
    }

    //current key state, true if this key is pressed
    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

    //if key up is pressed
    if( currentKeyStates[ SDL_SCANCODE_UP ] )
    {
        //avoid repeated key
        if (!rotate){
            this->Rotate(well);
            rotate = true;
            //return;
        }
        return;
    }

    //if key up is released
    else if(rotate){
        rotate = false;
        return;
    }

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
            return;
        }
    }

    //current key state
    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

    //w is pressed
    if( currentKeyStates[ SDL_SCANCODE_W ] )
    {   
        //avoid repeated key
        if (!rotate){
            this->Rotate(well);
            rotate = true;
            //return;
        }
        //this->Rotate(well);
        //return;
    }
    
    //w is released
    else if(rotate){
        rotate = false;
        //return;
    }

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

void Tetromino :: bot_move(Well &well){
    if (x_coordinate < finalX){
        VelX = 1;
    }
    else if (x_coordinate > finalX){
        VelX = -1;
    }
    else{
        VelX = 0;
    }
    x_coordinate += VelX;
    if (angle < finalAngle){
        this->Rotate(well);
    }
    //if go to last row
    bool finished = false;

    //check collision
    while(this->check_left_collision(well) && VelX < 0){
        this->x_coordinate++;
        VelX ++;
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
    //drop sound effect on
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

void Tetromino :: save_file(fstream &saveFile){
    //save tetromino
    switch (TetrominoType)
    {
    case I_BLOCK:
        saveFile << "I_BLOCK\n";
        break;
    case L_BLOCK:
        saveFile << "L_BLOCK\n";
        break;
    case T_BLOCK:
        saveFile << "T_BLOCK\n";
        break;
    case Z_BLOCK:
        saveFile << "Z_BLOCK\n";
        break;
    case O_BLOCK:
        saveFile << "O_BLOCK\n";
        break;
    case J_BLOCK:
        saveFile << "J_BLOCK\n";
        break;
    case S_BLOCK:
        saveFile << "S_BLOCK\n";
        break;
    }

    //save angle, x and y coordinate
    saveFile << angle << " " << x_coordinate << " " << y_coordinate << '\n';
}

void Tetromino :: load_file(fstream &saveFile){
    //load tetromino
    string _TetrominoType;
    saveFile >> _TetrominoType;
    saveFile.ignore();
    if (_TetrominoType == "I_BLOCK"){
        TetrominoType = I_BLOCK;
    }
    else if (_TetrominoType == "L_BLOCK"){
        TetrominoType = L_BLOCK;
    }
    else if (_TetrominoType == "T_BLOCK"){
        TetrominoType = T_BLOCK;
    }
    else if (_TetrominoType == "Z_BLOCK"){
        TetrominoType = Z_BLOCK;
    }
    else if (_TetrominoType == "O_BLOCK"){
        TetrominoType = O_BLOCK;
    }
    else if (_TetrominoType == "J_BLOCK"){
        TetrominoType = J_BLOCK;
    }
    else if (_TetrominoType == "S_BLOCK"){
        TetrominoType = S_BLOCK;
    }

    //load color
    TetrominoColor = Tetromino_color[TetrominoType];

    //load angle, x and y coordinate
    saveFile >> angle >> x_coordinate >> y_coordinate;

    //shape with angle and tetro type
    for (int i = 0; i < TETRAD_SIZE; i++){
        for (int j = 0; j < TETRAD_SIZE; j++){
            TetrominoShape[i][j] = tetromino_shape[TetrominoType * 4 ][i][j];
        }
    }
}

void Tetromino :: greedy(Well& well){
    //the final expected value
    int maxExpectedValue = -1e7;

    //greedy
    for (int x = -2; x < WIDE_CELLS - 1; x++){
        for (int _angle = 0; _angle < 4; _angle++){
            //get expected value in each case
            int expectedValue = this->get_expected_value(x, _angle, well);

            //update expected value
            if (expectedValue > maxExpectedValue){
                maxExpectedValue = expectedValue;

                //update finale position
                finalX = x;
                finalAngle = _angle;
            }
        }
    }
}

void Tetromino :: set_x_coordinate(int x){
    x_coordinate = x;
}

int Tetromino :: get_expected_value(int x, int _angle, Well &well){
    //the copy of this tetromino
    Tetromino ghost = *this;

    //set the position we are considering
    ghost.set_x_coordinate(x);
    ghost.angle = max(_angle - 1, 0);

    //if cannot rotate because of collision
    if (_angle != 0 && !ghost.Rotate(well)){
        return -1e7;
    }
    if(ghost.check_left_collision(well) || ghost.check_right_collision(well)){
        return -1e7;
    }

    //set the deepest height
    while(!ghost.check_bottom_collision(well)){
        ghost.y_coordinate++;
    }
    ghost.y_coordinate--;

    //calculate the blocks in bottom row, lowest row in tetrad size
    int blockInBottomRow = 0;
    int lowestRow = 0;
    for (int i = TETRAD_SIZE - 1; i >= 0; i--){
        for (int j = 0; j < TETRAD_SIZE; j++){
            if(ghost.TetrominoShape[i][j]){
                blockInBottomRow++;
            }
        }
        if(blockInBottomRow){
            lowestRow = i;
            break;
        }
    }

    // a virtual well 
    bool virtualWell [WIDE_CELLS][HEIGHT_CELLS];
    memset(virtualWell, false, sizeof(virtualWell));

    //set value in virtual well
    for (int i = 0; i < WIDE_CELLS; i++){
        for (int j = 0; j < HEIGHT_CELLS; j++){
            virtualWell[i][j] = well.isBlock(i, j);
        }
    }

    //calculate inaccessible spaces
    int old_innaccessible_space = 0;
    for (int i = 0; i < WIDE_CELLS; i++){
        for (int j = 0; j < HEIGHT_CELLS; j++){
            if(virtualWell[i][j] == true){
                j++;
                int space_tmp = 0;
                while(j < HEIGHT_CELLS && virtualWell[i][j] == false){
                    old_innaccessible_space ++;
                    j++;
                }
                j--;
            }
        }
    }

    // //calculate inaccessible spaces
    // int inaccessibleSpace = 0;
    // for (int i = 0; i < TETRAD_SIZE; i++){
    //     for (int j = 0; j < TETRAD_SIZE; j++){
    //         if (ghost.TetrominoShape[i][j]){
    //             if ((i < TETRAD_SIZE - 1 && !ghost.TetrominoShape[i + 1][j]) || i == TETRAD_SIZE){
    //                 int row = ghost.y_coordinate + i + 1;
                    
    //                 //the number of cell that is not true(in virtual well) behind [i][j] is inaccessible
    //                 while(row < HEIGHT_CELLS && !virtualWell[ghost.x_coordinate + j][row]){
    //                     inaccessibleSpace++;
    //                     row++;
    //                 }
    //             }
    //         }
    //     }
    // }

    //unite ghost tetromino
    for (int i = 0; i < TETRAD_SIZE; i++){
        for (int j = 0; j < TETRAD_SIZE; j++){
            if (ghost.TetrominoShape[i][j])
            {
                //the coordinate along the Well
                int x = ghost.x_coordinate + j;
                int y = ghost.y_coordinate + i;

                //update cell x, y and color
                virtualWell[x][y] = true;
            }
        }
    }

    //delete filled line
    for (int i = HEIGHT_CELLS - 1; i >= 1; i--){
        bool filled = true;
        for (int j = 0; j < WIDE_CELLS ; j++){
            if (virtualWell[j][i] == false) filled = false;
        }
        if (filled){
            for (int line = i; line >= 1; line--){
                for (int k = 0; k < WIDE_CELLS; k++){
                    virtualWell[k][line] = virtualWell[k][line - 1];
                }
            }
            i++;
        }
    } 

    //calculate inaccessible spaces
    int new_innaccessible_space = 0;
    for (int i = 0; i < WIDE_CELLS; i++){
        for (int j = 0; j < HEIGHT_CELLS; j++){
            if(virtualWell[i][j] == true){
                j++;
                int space_tmp = 0;
                while(j < HEIGHT_CELLS && virtualWell[i][j] == false){
                    new_innaccessible_space++;
                    j++;
                }
                j--;
            }
        }
    }

    //the highest row which has a block in the ghost tetromino
    int highestRow = 0;

    for (int i = 0; i < TETRAD_SIZE; i++){
        bool blockInRow = false;
        for (int j = 0; j < TETRAD_SIZE; j++){
            if (ghost.TetrominoShape[i][j]){
                blockInRow = true;
                break;
            }
        }
        if (blockInRow){
            highestRow++;
        }
    }

    //the highest row which has the block in virtual well
    int highestRow2 = 20;
    for (int i = 0; i < HEIGHT_CELLS; i++){
        for (int j = 0; j < WIDE_CELLS; j++){
            if (virtualWell[j][i]){
                highestRow2 = i;
            }
        }
        if (highestRow2){
            break;
        }
    }

    //the filled row
    int filledRow = 0;
    for (int i = 0; i < HEIGHT_CELLS; i++){
        bool filled = true;
        for (int j = 0; j < WIDE_CELLS; j++){
            if (!virtualWell[j][i]){
                filled = false;
                break;
            }
        }
        if(filled){
            filledRow++;
        }
    }
    int inaccessibleSpace = max(0, new_innaccessible_space - old_innaccessible_space);
    return (ghost.y_coordinate + lowestRow) * 3 + blockInBottomRow - sqrt(inaccessibleSpace * 10) * 3 - highestRow + highestRow2 * 1.5 + filledRow * 1.5 + ghost.y_coordinate;

    // return {0, 0};
}