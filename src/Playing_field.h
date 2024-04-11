#ifndef Playing_field_h
#define Playing_field_h

#include "../include/SDL2/SDL.h"
#include "Tetromino.h"
#include "Data.h"
#include "Score.h"
#include "fstream"
#include <vector>
class Well
{
public:
    //constructor
    Well(SDL_Renderer *renderer, int _x, int _y, int _topScore, int _level);

    //destructor
    ~Well();

    void load_media(SDL_Renderer *renderer);

    //draw the well in the screen
    void draw(SDL_Renderer *renderer, GameMode gameMode = SinglePlay);

    //get the coordinate of the well rect
    int get_x();
    int get_y();

    //get the position according to the window with the coordinate
    int get_pos_x(int PosX);
    int get_pos_y(int PosY);

    //get the dimension of the well
    int get_right_border();
    int get_bottom_border();

    int get_width();
    int get_height();

    //t will no longer be controlled
    void Unite(Tetromino *t);

    //true if there is a block in coordinate x,y
    bool isBlock(int x, int y);

    //check if a row is filled
    bool filled_line(int line);

    //deleted filled line
    void deleted_line(int line);

    //true if lose
    bool get_lose();

    //set game lose
    bool set_lose();

    //get top score
    int get_top_score();

    //get current score
    int get_current_score();

    //lose texture for single play
    void draw_lose_background(SDL_Renderer *renderer);

    //if player chose play or battle again
    bool press_play_again(SDL_Event &e);

    //come back to menu
    bool return_home(SDL_Event &e);

    //load lastest game
    void load_file(fstream &saveFile);

    //save game
    void save_file(fstream &saveFile);

    bool isDeletingLine();

    void draw_fade_effect(SDL_Renderer *renderer);
private:
    //the higher level, the faster tetro falls
    int level;

    //current and top score
    Score score;

    //the dimension of the well
    int width = TILE_SIZE * WIDE_CELLS;
    int height = TILE_SIZE * HEIGHT_CELLS;

    //the coordinate according to the window;
    int x, y;

    //return true if there is a tile in this coordinates
    bool matrix[WIDE_CELLS][HEIGHT_CELLS];

    //the color corresponding to each cell
    SDL_Color cell_colors[WIDE_CELLS][HEIGHT_CELLS];

    //cannot play
    bool lose;

    int filledLineFrame;

    vector <int> filledLine;
};

#endif
