#pragma once
#include "Texture.h"
#include "Data.h"
class Setting{
public:
     Setting();

     ~Setting();

     bool load_media(SDL_Renderer *renderer);

     bool click_up_level_button(SDL_Event &e);

    bool click_down_level_button(SDL_Event &e);

    bool click_back_button(SDL_Event &e);

    bool click_set_ghost_piece(SDL_Event &e);

     //if we are in menu
    bool get_active();

    //set active
    void set_active();

    void display_level(SDL_Renderer *renderer, int level);

    void display_ghostTetromino(SDL_Renderer *renderer, bool ghostTetromino);

    void display_theme(SDL_Renderer *renderer, Theme theme);

    bool click_change_theme(SDL_Event &e);

    bool click_autumn_theme(SDL_Event &e);

    bool click_winter_theme(SDL_Event &e);

    void display(SDL_Renderer *renderer, int level, bool ghostTetromino, Theme theme);

private:
    //button in setting
    LTexture RightButton;
    LTexture LeftButton;
    LTexture LevelButton;
    LTexture difficulty;
    LTexture backButton;
    LTexture ghostTetrominoText;
    LTexture OnText;
    LTexture OffText;
    LTexture ThemeText;
    LTexture WinterText;
    LTexture AutumnText;


    bool active;

};