#include "Playing_field.h"
#include <bits/stdc++.h>

Well :: Well (int _x, int _y, int _topScore, int _level, Effect _effect, Mode _mode)
:   score(_topScore)
{
    x = _x;
    y = _y;

    level = _level; 

    //marked no tetromino unites with well
    memset(matrix, false, sizeof(matrix));

    //all initial cell colors is black
    for (int i = 0; i < WIDE_CELLS; i++){
        for (int j = 0; j < HEIGHT_CELLS; j++){
            cell_colors[i][j] = {0, 0, 0, 255};
        }
    }
    lose = false;
    filledLineFrame = 0;
    effect = _effect;
    mode = _mode;

    BoxX = BoxY = 0;
    BoxLiveTime = 20000;
    BoxStartTime = effectivenessTime = SDL_GetTicks();
    BoxActive = false;

    mystery_box = Nothing;
    type = 0;
};

Well :: ~Well()
{
    memset(matrix, 0, sizeof(matrix));
    for (int i = 0; i < WIDE_CELLS; i++){
        for (int j = 0; j < HEIGHT_CELLS; j++){
            cell_colors[i][j] = {0, 0, 0, 255};
        }
    }
}

void Well :: draw (SDL_Renderer *renderer, GameMode gameMode)
{    
    //black color
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

   //the well rect
   SDL_Rect rect = {x, y + HIDDEN_ROWS * TILE_SIZE, width, height - HIDDEN_ROWS * TILE_SIZE};
    if (mode == UpsideDown){
        gWellFrame.render(renderer, x - TILE_SIZE, y);
        rect.h -= TILE_SIZE;
    }
    else gWellFrame.render(renderer, x - TILE_SIZE, y + TILE_SIZE);

   //fill well with black
   SDL_RenderFillRect(renderer, &rect);

    //white color
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    for (int i = 0; i < WIDE_CELLS; i++){
        for (int j = HIDDEN_ROWS; j < HEIGHT_CELLS; j++){
            //if there is a tetromino uniting with the well
            if (matrix[i][j]){
                //get the tetromino color
                SDL_Color curColor = cell_colors[i][j];

                //set color
                SDL_SetRenderDrawColor(renderer, curColor.r, curColor.g, curColor.b, 255);

                if(level != MAX_LEVEL || (SDL_GetTicks() / 3000) % 2 == 0){
                    //the rect of each tile
                    SDL_Rect tileRect = {x + i * TILE_SIZE, y + j * TILE_SIZE, TILE_SIZE, TILE_SIZE};

                    if (mode == UpsideDown){
                        tileRect.y = SCREEN_HEIGHT - tileRect.y;
                    }

                    //file rect
                    SDL_RenderFillRect(renderer, &tileRect);

                    //draw black color
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderDrawRect(renderer, &tileRect);
                }

            }
            //draw white point
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawPoint(renderer, i * TILE_SIZE + x, j * TILE_SIZE + y);
        }
    }

    //draw deleting line according to effect
    if(effect == Capcut){
        draw_capcut_effect(renderer);
    }
    else if (effect == Fade){
        draw_fade_effect(renderer);
    }
    
    if (filledLineFrame == 0){
        if (get_erosion()){
            erosion();
        }
        else if (get_twist()){
            twist();
        }
        else if (get_fission()){
            fission();
        }
        else if (get_turn()){
            turn();
        }
    }
    if (BoxActive && !matrix[BoxX][BoxY]){
        this->check_box_appearance_condition();
    }
    
    if (!BoxActive){
        this->check_box_appearance_condition();
    }
    else{
        MysteryBoxTexture.render(renderer, this->get_pos_x(BoxX), this->get_pos_y(BoxY));
        if (SDL_GetTicks() - BoxStartTime >= 20000){
            BoxActive = false;
        }
    }

    //draw score
    score.draw(renderer, *this, ScoreFont);
}

void Well :: draw_fade_effect(SDL_Renderer* renderer){
    //is deleting line
    if(filledLineFrame != 0) {
        filledLineFrame--;
        //if finish
        if(filledLineFrame == 0){
            for (int i : filledLine)
            deleted_line(i);
        }
    }

    if (filledLineFrame != 0){
        for (int line : filledLine){
            for (int i = 0; i < WIDE_CELLS; i++){
                //get the tetromino color
                SDL_Color curColor = cell_colors[i][line];

                if (((33 - filledLineFrame) / 3) >= i){
                    //set color
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

                    //the rect of each tile
                    SDL_Rect tileRect = {x + i * TILE_SIZE, y + line * TILE_SIZE, TILE_SIZE, TILE_SIZE};

                    if (mode == UpsideDown){
                        tileRect.y = SCREEN_HEIGHT - tileRect.y;
                    }

                    //file rect
                    SDL_RenderFillRect(renderer, &tileRect);

                    if (mode == UpsideDown){
                        lineText[filledLine.size() - 1].render(renderer, x + (width - lineText[filledLine.size() - 1].getWidth()) / 2, SCREEN_HEIGHT - y - line * TILE_SIZE);
                    }
                    else {
                        lineText[filledLine.size() - 1].render(renderer, x + (width - lineText[filledLine.size() - 1].getWidth()) / 2, y + line * TILE_SIZE);
                    }
                    
                    if ((33 - filledLineFrame) <= 3 * i + 6 ){
                        //shrink the block
                        int dimension = TILE_SIZE / (max(1, (33 - 3 * i - filledLineFrame) % 7));
                        int centerX = x + i * TILE_SIZE + TILE_SIZE / 2;
                        int centerY = y + line * TILE_SIZE + TILE_SIZE / 2;

                        if (mode == UpsideDown){
                            centerY = SCREEN_HEIGHT - centerY + TILE_SIZE;
                        }

                        int newx = centerX - dimension / 2;
                        int newy = centerY - dimension / 2;

                        //new tile rect is shrinked
                        SDL_Rect newTileRect = {newx, newy, dimension, dimension};

                        //draw
                        SDL_SetRenderDrawColor(renderer, curColor.r, curColor.g, curColor.b, 255);
                        SDL_RenderFillRect(renderer, &newTileRect);

                        //draw black color border
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
                        SDL_RenderDrawRect(renderer, &newTileRect);
                    }
                }
                else{
                    //if the block is not deleting
                    SDL_SetRenderDrawColor(renderer, curColor.r, curColor.g, curColor.b, 255);

                    //the rect of each tile
                    SDL_Rect tileRect = {x + i * TILE_SIZE, y + line * TILE_SIZE, TILE_SIZE, TILE_SIZE};

                    if (mode == UpsideDown){
                        tileRect.y = SCREEN_HEIGHT - tileRect.y;
                    }

                    //file rect
                    SDL_RenderFillRect(renderer, &tileRect);

                    //draw black color
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderDrawRect(renderer, &tileRect);

                }
            }
        }

        MysteryBoxType.loadFromRenderedText(renderer, SettingFont, MysteryBoxTypeText[type], {255, 0, 0});
        if (type != 0 && SDL_GetTicks() - BoxStartTime <= 1500){
            MysteryBoxType.render(renderer, x + (width - MysteryBoxType.getWidth()) / 2, y + (height - MysteryBoxType.getHeight()) / 2);

            int ScanY = height - (height - y) / 33 * (33 - filledLineFrame);
            int ScanOpacity = 200 / 33 * (filledLineFrame);
            ScanTexture.setAlphaMode(ScanOpacity);
            ScanTexture.render(renderer, x , ScanY);
        }
    }

    if(filledLineFrame == 1){
        for (int i : filledLine){
            deleted_line(i);
        }
        filledLineFrame--;

        //clear line vector
        filledLine.clear();
    }
}

void Well :: draw_capcut_effect(SDL_Renderer *renderer){
    //is deleting line
    if(filledLineFrame != 0) {
        filledLineFrame--;
        if(filledLineFrame == 0){
            //is finish
            for (int i : filledLine)
            deleted_line(i);
        }
    }
    if (filledLineFrame != 0){
        for (int line : filledLine){
            for (int i = 0; i < WIDE_CELLS; i++){
                if ((filledLineFrame / 8) % 2 == 0){
                    //get the tetromino color
                    SDL_Color curColor = cell_colors[i][line];

                    //set color
                    SDL_SetRenderDrawColor(renderer, max(curColor.r - 50,0 ) , max(curColor.g - 50, 0), max(curColor.b - 50, 0), 50);

                    //the rect of each tile
                    SDL_Rect tileRect = {x + i * TILE_SIZE, y + line * TILE_SIZE, TILE_SIZE, TILE_SIZE};
                    if (mode == UpsideDown){
                        tileRect.y = SCREEN_HEIGHT - tileRect.y;
                    }

                    //file rect
                    SDL_RenderFillRect(renderer, &tileRect);

                    //draw black color
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
                    SDL_RenderDrawRect(renderer, &tileRect);
                }
                else{
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

                    //the rect of each tile
                    SDL_Rect tileRect = {x + i * TILE_SIZE, y + line * TILE_SIZE, TILE_SIZE, TILE_SIZE};

                    if (mode == UpsideDown){
                        tileRect.y = SCREEN_HEIGHT - tileRect.y;
                    }

                    //file rect
                    SDL_RenderFillRect(renderer, &tileRect);

                    //draw black color
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderDrawRect(renderer, &tileRect);

                    if (mode == UpsideDown){
                        lineText[filledLine.size() - 1].render(renderer, x + (width - lineText[filledLine.size() - 1].getWidth()) / 2,SCREEN_HEIGHT - y - line * TILE_SIZE);

                    }
                    else{
                        lineText[filledLine.size() - 1].render(renderer, x + (width - lineText[filledLine.size() - 1].getWidth()) / 2, y + line * TILE_SIZE);
                    }
                }
            }
        }
        MysteryBoxType.loadFromRenderedText(renderer, SettingFont, MysteryBoxTypeText[type], {255, 0, 0});
        if (type != 0 && SDL_GetTicks() - BoxStartTime <= 1500){
            MysteryBoxType.render(renderer, x + (width - MysteryBoxType.getWidth()) / 2, y + (height - MysteryBoxType.getHeight()) / 2);

            int ScanY = height - (height - y) / 33 * (33 - filledLineFrame);
            int ScanOpacity = 200 / 33 * (filledLineFrame);
            ScanTexture.setAlphaMode(ScanOpacity);
            ScanTexture.render(renderer, x , ScanY);
        }
    }
    
    if(filledLineFrame == 1){
        for (int i : filledLine){
            deleted_line(i);
        }
        filledLineFrame--;
        filledLine.clear();
    }
}

void Well :: set_level(int _level){
    level = _level;
}

int Well :: get_x()
{
    return x;
}

int Well :: get_y()
{
    return y;
}

int Well :: get_right_border(){
    return this->get_x() + width;
}

int Well :: get_bottom_border(){
    return this->get_y() + height;
}

int Well :: get_width()
{
    return width;
}

int Well :: get_height()
{
    return height;
}

int Well :: get_pos_x(int PosX)
{
    return x + PosX * TILE_SIZE;
}

int Well :: get_pos_y(int PosY)
{
    return y + PosY * TILE_SIZE;
}

void Well :: Unite(Tetromino *t)
{
    for (int i = 0; i < TETRAD_SIZE; i++){
        for (int j = 0; j < TETRAD_SIZE; j++){
            if (t->isBlock(i, j))
            {
                //the coordinate along the Well
                int x = t->get_x_axis_coor() + j;
                int y = t->get_y_axis_coor() + i;

                //update cell x, y and color
                matrix[x][y] = true;
                cell_colors[x][y] = t->get_color();
            }
        }
    }
    //play sound when delete line(s)
    bool sound = false;

    //line count to get score
    int line = 0;

    //check each row
    for (int j = 0; j <= HEIGHT_CELLS - 1; j++){
        if (filled_line(j)){
            if (effect != None){
                filledLineFrame = 33;
                filledLine.push_back(j);
                if (j == BoxY){
                    BoxActive = false;
                    mystery_box = Mystery_Box(rand() % (MAX_MYSTERY_BOX_TYPE - 1) + 1);
                   
                    type = mystery_box;
                    effectivenessTime = SDL_GetTicks();
                }
            }
            else{
                deleted_line(j);
                j--;
            }
            line++;
            sound = true;
        }
    }

    //set score
    score.set_score(20 * (line) * (line + 1) * level);

    //play sound if....
    if(sound) Mix_PlayChannel(-1, gNiceSoundEffect, 0);
}

bool Well :: isBlock(int x, int y)
{
    return matrix[x][y];
}

bool Well :: filled_line(int line)
{
    //check if line is fulled
    for (int i = 0; i < WIDE_CELLS; i++)
    {
        if (!matrix[i][line])
        {
            return false;
        }
    }
    return true;
}

void Well :: deleted_line(int line)
{
    //delete the full line
    for (int j = line; j >= 1; j--)
    {
        for (int i = 0; i < WIDE_CELLS; i++){
            matrix[i][j] = matrix[i][j - 1];
            cell_colors[i][j] = cell_colors[i][j - 1];
        }   
    }
    if (line == BoxY && effect == None){
        BoxActive = false;
        mystery_box = Mystery_Box(rand() % (MAX_MYSTERY_BOX_TYPE - 1) + 1);
        type = mystery_box;
        effectivenessTime = SDL_GetTicks();
    }
    if (line >= BoxY){
        BoxY++;
    }
    if (!matrix[BoxX][BoxY]){
        BoxActive = false;
    }
}

bool Well :: get_lose()
{
    return lose;
}

bool Well :: set_lose()
{
    lose = true;
}

int Well :: get_top_score()
{
    return score.get_top_score();
}

int Well :: get_current_score()
{
    return score.get_current_score();
}

bool Well :: isDeletingLine(){
    return (filledLineFrame != 0) && (mystery_box == Nothing || mystery_box == SpeedUp || mystery_box == SlowDown) ;
}

void Well :: draw_lose_background(SDL_Renderer *renderer){
    //draw lose texture in the center of the screen
    gLoseBackground.render(renderer, (SCREEN_WIDTH - gLoseBackground.getWidth()) / 2, (SCREEN_HEIGHT - gLoseBackground.getHeight()) / 2);

    //replaye button in the center of the screen
    gReplayButton.render(renderer, (SCREEN_WIDTH - gReplayButton.getWidth()) / 2, (SCREEN_HEIGHT - gReplayButton.getHeight()) / 2 + buttonDistance);

    //home button in the left of the screen
    gHomeButton.render(renderer, (SCREEN_WIDTH - gReplayButton.getWidth()) / 2 - buttonDistance, (SCREEN_HEIGHT - gReplayButton.getHeight()) / 2 + buttonDistance);
}

bool Well :: press_play_again(SDL_Event &e){
    //get mouse position
    int x, y;
    SDL_GetMouseState(&x, &y);
    
    //the x,y replay button rext
    int replayButton_x = (SCREEN_WIDTH - gReplayButton.getWidth()) / 2;
    int replayButton_y = (SCREEN_HEIGHT - gReplayButton.getHeight()) / 2 + buttonDistance;

    //if player press mouse in replay button
    if (e.type == SDL_MOUSEBUTTONDOWN && x >= replayButton_x && x <= replayButton_x + gReplayButton.getWidth() && y >= replayButton_y && y <= replayButton_y + gReplayButton.getHeight()){
        return true;
    }
    return false;
}

bool Well :: return_home(SDL_Event &e){
    //get mouse position
    int x, y;
    SDL_GetMouseState(&x, &y);
    
    //home button x, y rect
    int homeButton_x = (SCREEN_WIDTH - gReplayButton.getWidth()) / 2 - buttonDistance;
    int homeButton_y = (SCREEN_HEIGHT - gHomeButton.getHeight()) / 2 + buttonDistance;

    //press home button
    if (e.type == SDL_MOUSEBUTTONDOWN && x >= homeButton_x && x <= homeButton_x + gHomeButton.getWidth() && y >= homeButton_y && y <= homeButton_y + gHomeButton.getHeight()){
        return true;
    }
    return false;
}

void Well :: set_effect(Effect _effect){
    effect = _effect;
}

void Well :: set_mode (Mode _mode){
    mode = _mode;
}

void Well :: load_file(fstream &saveFile){
    //load postion
    saveFile >> x >> y;

    //load matrix
    for (int i = 0; i < HEIGHT_CELLS; i++){
        for (int j = 0; j < WIDE_CELLS; j++){
            int unite;
            saveFile >> unite;
            if (unite){
                matrix[j][i] = true;
            }
            else matrix[j][i] = false;
        }
    }

    //load color matrix
    for (int i = 0; i < HEIGHT_CELLS; i++){
        for (int j = 0; j < WIDE_CELLS; j++){
            int r, g, b;
            saveFile >> r >> g >> b;
            cell_colors[j][i].r = r;
            cell_colors[j][i].g = g;
            cell_colors[j][i].b = b;
        }
    }

    //load score
    int currentScore, topScore;
    saveFile >> currentScore >> topScore;
    score.set_current_score(currentScore);
    score.set_top_score(topScore);
}

void Well :: save_file(fstream &saveFile){
    //save postion
    saveFile << x << " " << y << '\n';

    //save matrix
    for (int i = 0; i < HEIGHT_CELLS; i++){
        for (int j = 0; j < WIDE_CELLS; j++){
            if (matrix[j][i]){
                saveFile << 1;
            }
            else saveFile << 0;
            if (j != WIDE_CELLS - 1){
                saveFile << " ";
            }
        }
        saveFile << '\n';
    }

    //save color
    for (int i = 0; i < HEIGHT_CELLS; i++){
        for (int j = 0; j < WIDE_CELLS; j++){
            saveFile << (int)cell_colors[j][i].r << " " <<(int) cell_colors[j][i].g << " " <<  (int)cell_colors[j][i].b;
            if (j != WIDE_CELLS - 1){
                saveFile << " ";
            }
        }
        saveFile << '\n';
    }

    //save score
    saveFile << score.get_current_score() << " " << score.get_top_score();
}

bool Well :: check_box_appearance_condition(){
    //check if mode is mind bender
    if (mode != MindBender){
        return false;
    }

    //contains all of blocks in well
    vector <pair <int, int>> blocks;
    for (int i = 0; i < WIDE_CELLS; i++){
        for (int j = 0; j < HEIGHT_CELLS; j++){
            if (matrix[i][j]){
                blocks.push_back({i, j});
            }
        }
    }

    //if there is enough blocks
    if (blocks.size() >= 20){
        BoxActive = true;

        //random block
        pair <int, int> coordinate = blocks[rand() % blocks.size()];
        BoxX = coordinate.first;
        BoxY = coordinate.second;
        BoxStartTime = SDL_GetTicks();
        return true;
    }
    return false;
}

bool Well :: get_speed_up(){
    return mystery_box == SpeedUp && (SDL_GetTicks() - effectivenessTime) <= 5000; 
}

bool Well :: get_slow_down(){
    return mystery_box == SlowDown && (SDL_GetTicks() - effectivenessTime) <= 5000; 
}

bool Well :: get_erosion(){
    return mystery_box == Erosion && (SDL_GetTicks() - effectivenessTime) <= 5000; 
}

bool Well :: get_twist(){
    return mystery_box == Twist && (SDL_GetTicks() - effectivenessTime) <= 5000; 
}

bool Well :: get_fission(){
    return mystery_box == Fission && (SDL_GetTicks() - effectivenessTime) <= 5000; 
}

bool Well :: get_turn(){
    return mystery_box == Turn && (SDL_GetTicks() - effectivenessTime) <= 5000; 
}

void Well :: fission(){
    //fission left side
    for (int j = 0; j < HEIGHT_CELLS; j++){
        //the first position
        int pointer = 0;

        for (int i = 0; i < WIDE_CELLS / 2; i++){
            if (matrix[i][j]){
                SDL_Color tmp = cell_colors[i][j];
                matrix[i][j] = 0;
                cell_colors [i][j] = {0, 0, 0};
                matrix[pointer][j] = true;
                cell_colors[pointer][j] = tmp;
                pointer++;
            }
        }
    }

    //fission right side
    for (int j = 0; j < HEIGHT_CELLS; j++){
        //the last position
        int pointer = WIDE_CELLS - 1;

        for (int i = WIDE_CELLS - 1; i >= WIDE_CELLS / 2; i--){
            if (matrix[i][j]){
                SDL_Color tmp = cell_colors[i][j];
                matrix[i][j] = 0;
                cell_colors [i][j] = {0, 0, 0};
                matrix[pointer][j] = true;
                cell_colors[pointer][j] = tmp;
                pointer--;
            }
        }
    }
    //change type box
    mystery_box = Nothing;
}

void Well :: twist(){
    for (int i = 0; i < WIDE_CELLS / 2; i++){
        for (int j = 0; j < HEIGHT_CELLS; j++){
            //swap blocks
            swap(matrix[i][j], matrix[WIDE_CELLS - i - 1][j]);
            swap(cell_colors[i][j], cell_colors[WIDE_CELLS - i - 1][j]);
        }
    }
    mystery_box = Nothing;
}

void Well :: erosion(){
    //contains all blocks
    vector <pair <int, int>> blocks;
    for (int i = 0; i < WIDE_CELLS; i++){
        for (int j = 0; j < HEIGHT_CELLS; j++){
            if (matrix[i][j]){
                blocks.push_back({i, j});
            }
        }
    }

    //delete random block
    for (int i = 0; i < min(5, (int)blocks.size()); i++){
        pair <int, int> block = blocks[rand() % blocks.size()];
        matrix[block.first][block.second] = false;
        cell_colors[block.first][block.second] = {0, 0, 0};

    }
    mystery_box = Nothing;
}

void Well :: turn(){
    //find highest row
    int peak_row = 0;
    for (int j = 0; j < HEIGHT_CELLS; j++){
        for (int i = 0; i < WIDE_CELLS; i++){
            if (matrix[i][j]){
                peak_row = j;
            }
        }
        if (peak_row){
            break;
        }
    }

    //turn 
    for (int j = peak_row; j <= (HEIGHT_CELLS - 1 + peak_row) / 2; j++){
        for (int i = 0; i < WIDE_CELLS; i++){
            swap(matrix[i][j], matrix[i][HEIGHT_CELLS - 1 - j + peak_row]);
            swap(cell_colors[i][j], cell_colors[i][HEIGHT_CELLS - 1 - j + peak_row]);
        }
    }
    mystery_box = Nothing;
}