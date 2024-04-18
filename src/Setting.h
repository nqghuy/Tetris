#pragma once
#include "Texture.h"
#include "Data.h"
#include "Volume.h"

class Setting{
public:
    //constructor
    Setting();

    //destructor
    ~Setting();

    //load tetxture
    bool load_media(SDL_Renderer *renderer);

    //level up
    bool click_up_level_button(SDL_Event &e);

    //level down
    bool click_down_level_button(SDL_Event &e);

    //back to the menu
    bool click_back_button(SDL_Event &e);

    //change ghost piece
    bool click_set_ghost_piece(SDL_Event &e);

    //if we are in menu
    bool get_active();

    //set active
    void set_active();

    //show mode setting
    void display_mode(SDL_Renderer *renderer, Mode mode);

    //show level setting
    void display_level(SDL_Renderer *renderer, int level);

    //show ghost tetromino setting
    void display_ghostTetromino(SDL_Renderer *renderer, bool ghostTetromino);

    //show theme setting
    void display_theme(SDL_Renderer *renderer, Theme theme);

    //show effect setting
    void display_effect(SDL_Renderer *renderer, Effect effect);

    //change theme
    bool click_change_theme(SDL_Event &e);
    bool click_autumn_theme(SDL_Event &e);
    bool click_winter_theme(SDL_Event &e);

    //change effect
    bool click_right_change_effect(SDL_Event &e);
    bool click_left_change_effect(SDL_Event &e);

    //change mode
    bool click_right_change_mode(SDL_Event &e);
    bool click_left_change_mode(SDL_Event &e);
    
    //display all
    void display(SDL_Renderer *renderer, int level, bool ghostTetromino, Theme theme, Effect effect, Mode mode);

    //show bold button if mouse is in any button
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
    LTexture ModeText;
    LTexture ModeChoice;

    Volume volume;

    int TextX;
    int LeftButtonX;
    int RightButtonX;
    int y_coordinate;

    bool active;

};