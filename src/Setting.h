#pragma once
#include "Texture.h"
#include "Data.h"
#include "Volume.h"

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

    void display_effect(SDL_Renderer *renderer, Effect effect);

    bool click_change_theme(SDL_Event &e);

    bool click_autumn_theme(SDL_Event &e);

    bool click_winter_theme(SDL_Event &e);

    bool click_right_change_effect(SDL_Event &e);

    bool click_left_change_effect(SDL_Event &e);

    void display(SDL_Renderer *renderer, int level, bool ghostTetromino, Theme theme, Effect effect);

    void display_bold_button(SDL_Renderer *renderer);

    void handle_event (SDL_Event &e);

private:
    //button in setting
    LTexture RightButton;
    LTexture RightButton2;
    LTexture LeftButton;
    LTexture LeftButton2;

    LTexture LevelButton;
    LTexture difficulty;
    LTexture backButton;
    LTexture ghostTetrominoText;
    LTexture OnText;
    LTexture OffText;
    LTexture ThemeText;
    LTexture WinterText;
    LTexture AutumnText;
    LTexture EffectText;
    LTexture EffectChoice;

    Volume volume;

    bool active;

};