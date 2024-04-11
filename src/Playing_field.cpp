#include "Playing_field.h"
#include <bits/stdc++.h>

Well :: Well (SDL_Renderer *renderer, int _x, int _y, int _topScore, int _level)
:   score(renderer, _topScore)
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

    gWellFrame.render(renderer, x - TILE_SIZE, y + TILE_SIZE);

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

                //the rect of each tile
                SDL_Rect tileRect = {x + i * TILE_SIZE, y + j * TILE_SIZE, TILE_SIZE, TILE_SIZE};

                //file rect
                SDL_RenderFillRect(renderer, &tileRect);

                //draw black color
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderDrawRect(renderer, &tileRect);
            }
            //draw white point
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawPoint(renderer, i * TILE_SIZE + x, j * TILE_SIZE + y);
        }
    }
    // if(filledLineFrame != 0) {
    //     filledLineFrame--;
    //     if(filledLineFrame == 0){
    //         for (int i : filledLine)
    //         deleted_line(i);
    //     }
    // }
    // if (filledLineFrame != 0){
    //     for (int line : filledLine){
    //         for (int i = 0; i < WIDE_CELLS; i++){
    //             if ((filledLineFrame / 8) % 2 == 0){
    //                 //get the tetromino color
    //                 SDL_Color curColor = cell_colors[i][line];

    //                 //set color
    //                 SDL_SetRenderDrawColor(renderer, max(curColor.r - 50,0 ) , max(curColor.g - 50, 0), max(curColor.b - 50, 0), 50);

    //                 //the rect of each tile
    //                 SDL_Rect tileRect = {x + i * TILE_SIZE, y + line * TILE_SIZE, TILE_SIZE, TILE_SIZE};

    //                 //file rect
    //                 SDL_RenderFillRect(renderer, &tileRect);

    //                 //draw black color
    //                 SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
    //                 SDL_RenderDrawRect(renderer, &tileRect);
    //             }
    //             else{
    //                 SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    //                 //the rect of each tile
    //                 SDL_Rect tileRect = {x + i * TILE_SIZE, y + line * TILE_SIZE, TILE_SIZE, TILE_SIZE};

    //                 //file rect
    //                 SDL_RenderFillRect(renderer, &tileRect);

    //                 //draw black color
    //                 SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    //                 SDL_RenderDrawRect(renderer, &tileRect);

    //             }
    //         }
    //     }
    // }
    // if(filledLineFrame == 1){
    //     for (int i : filledLine){
    //         deleted_line(i);
    //     }
    //     filledLineFrame--;
    //     filledLine.clear();
    // }
    draw_fade_effect(renderer);
    score.draw(renderer, *this, ScoreFont);
}

void Well :: draw_fade_effect(SDL_Renderer* renderer){
    if(filledLineFrame != 0) {
        filledLineFrame--;
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

                    //file rect
                    SDL_RenderFillRect(renderer, &tileRect);

                    if ((33 - filledLineFrame) <= 3 * i + 6 ){
                        int dimension = TILE_SIZE / (max(1, (33 - 3 * i - filledLineFrame) % 7));
                        int centerX = x + i * TILE_SIZE + TILE_SIZE / 2;
                        int centerY = y + line * TILE_SIZE + TILE_SIZE / 2;
                        int newx = centerX - dimension / 2;
                        int newy = centerY - dimension / 2;
                        SDL_Rect newTileRect = {newx, newy, dimension, dimension};

                        SDL_SetRenderDrawColor(renderer, curColor.r, curColor.g, curColor.b, 255);
                        SDL_RenderFillRect(renderer, &newTileRect);

                        //draw black color
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
                        SDL_RenderDrawRect(renderer, &newTileRect);
                        // SDL_Delay(100);
                    }

                }
                else{
                    SDL_SetRenderDrawColor(renderer, curColor.r, curColor.g, curColor.b, 255);

                    //the rect of each tile
                    SDL_Rect tileRect = {x + i * TILE_SIZE, y + line * TILE_SIZE, TILE_SIZE, TILE_SIZE};

                    //file rect
                    SDL_RenderFillRect(renderer, &tileRect);

                    //draw black color
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderDrawRect(renderer, &tileRect);

                }
            }
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
            filledLineFrame = 33;
            filledLine.push_back(j);
            // deleted_line(j);
            line++;
            // j++;
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
    return filledLineFrame;
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