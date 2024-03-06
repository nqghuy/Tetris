#include "Playing_field.h"
#include <bits/stdc++.h>

Well :: Well (SDL_Renderer *renderer, int _x, int _y, int _topScore)
:   score(renderer, _topScore)
{

    x = _x;
    y = _y;
    //marked no tetromino unites with well
    memset(matrix, false, sizeof(matrix));

    //all initial cell colors is black
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 20; j++){
            cell_colors[i][j] = {0, 0, 0, 255};
        }
    }
    lose = false;
};

int Well :: buttonDistance = 100;

Well :: ~Well()
{
    memset(matrix, 0, sizeof(matrix));
    for (int i = 0; i < WIDE_CELLS; i++){
        for (int j = 0; j < HEIGHT_CELLS; j++){
            cell_colors[i][j] = {0, 0, 0, 255};
        }
    }
}

void Well :: draw (SDL_Renderer *renderer)
{
    wellFrame = gWellFrame;
    loseBackground = gLoseBackground;
    replayButton = gReplayButton;
    homeButton = gHomeButton;
    
    //black color
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

   //the well rect
   SDL_Rect rect = {x, y + HIDDEN_ROWS * TILE_SIZE, width, height - HIDDEN_ROWS * TILE_SIZE};

    wellFrame.render(renderer, x - TILE_SIZE, y + TILE_SIZE);

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
                SDL_SetRenderDrawColor(renderer, curColor.r, curColor. g, curColor.b, 255);

                //the rect of each tile
                SDL_Rect tileRect = {this->get_x() + i * TILE_SIZE, this->get_y() + j * TILE_SIZE, TILE_SIZE, TILE_SIZE};

                //file rect
                SDL_RenderFillRect(renderer, &tileRect);

                //draw black color
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderDrawRect(renderer, &tileRect);
            }
            //draw white point
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawPoint(renderer, i * TILE_SIZE + (SCREEN_WIDTH - width) / 2, j * TILE_SIZE + (SCREEN_HEIGHT - height) / 2);
        }
    }
    score.draw(renderer, *this, ScoreFont);

    if(this->lose == true){
        this->draw_lose_background(renderer);
    }
}

int Well :: get_x()
{
    return (SCREEN_WIDTH - width) / 2;
}

int Well :: get_y()
{
    return (SCREEN_HEIGHT - height) / 2;
}

int Well :: get_width()
{
    return this->get_x() + width;
}

int Well :: get_height()
{
    return this->get_y() + height;
}

int Well :: get_pos_x(int PosX)
{
    return this->get_x() + PosX * TILE_SIZE;
}

int Well :: get_pos_y(int PosY)
{
    return this->get_y() + PosY * TILE_SIZE;
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


    for (int j = HEIGHT_CELLS - 1; j >= 0; j--){
        if (filled_line(j)){
            deleted_line(j);
            line++;
            j++;
            sound = true;
        }
    }

    //set score
    score.set_score(40 * (line));

    //play sound if....
    if(sound) Mix_PlayChannel(-1, gNiceSoundEffect, 0);
}

bool Well :: isBlock(int x, int y)
{
    return matrix[x][y];
}

bool Well :: filled_line(int line)
{
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

void Well :: draw_lose_background(SDL_Renderer *renderer){
    loseBackground.render(renderer, (SCREEN_WIDTH - loseBackground.getWidth()) / 2, (SCREEN_HEIGHT - loseBackground.getHeight()) / 2);
    replayButton.render(renderer, (SCREEN_WIDTH - replayButton.getWidth()) / 2, (SCREEN_HEIGHT - replayButton.getHeight()) / 2 + buttonDistance);

    homeButton.render(renderer, (SCREEN_WIDTH - replayButton.getWidth()) / 2 - buttonDistance, (SCREEN_HEIGHT - replayButton.getHeight()) / 2 + buttonDistance);
}

bool Well :: press_play_again(SDL_Event &e){
    int x, y;
    SDL_GetMouseState(&x, &y);
    
    int replayButton_x = (SCREEN_WIDTH - replayButton.getWidth()) / 2;
    int replayButton_y = (SCREEN_HEIGHT - replayButton.getHeight()) / 2 + buttonDistance;

    if (e.type == SDL_MOUSEBUTTONDOWN && x >= replayButton_x && x <= replayButton_x + replayButton.getWidth() && y >= replayButton_y && y <= replayButton_y + replayButton.getHeight()){
        return true;
    }
    return false;
}

bool Well :: return_home(SDL_Event &e){
    int x, y;
    SDL_GetMouseState(&x, &y);
    
    int homeButton_x = (SCREEN_WIDTH - replayButton.getWidth()) / 2 - buttonDistance;
    int homeButton_y = (SCREEN_HEIGHT - homeButton.getHeight()) / 2 + buttonDistance;

    if (e.type == SDL_MOUSEBUTTONDOWN && x >= homeButton_x && x <= homeButton_x + homeButton.getWidth() && y >= homeButton_y && y <= homeButton_y + homeButton.getHeight()){
        return true;
    }
    return false;
}