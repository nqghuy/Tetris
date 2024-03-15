#pragma once
#include "Data.h"
#include "Texture.h"
#include "include/SDL2/SDL.h"

class Menu
{
public:
    //constructor
    Menu();

    //destructor
    ~Menu();

    //load menu and button texture
    bool load_media(SDL_Renderer *renderer);

    //display into screen
    void display(SDL_Renderer *renderer, int level, bool ghostTetromino);

    //handle event
    bool click_play(SDL_Event &e);

    bool click_battle(SDL_Event &e);
    
    bool click_setting(SDL_Event &e);

    bool click_up_level_button(SDL_Event &e);

    bool click_down_level_button(SDL_Event &e);

    bool click_back_button(SDL_Event &e);

    bool click_set_ghost_piece(SDL_Event &e);

    //if we are in menu
    bool get_active();

    //set active
    void set_active();

    //chose setting
    void set_in_setting();

    //exit setting
    void set_not_in_setting();

    //return in setting or not
    bool check_in_setting();
private:
    bool inSetting;

    //menu texture
    LTexture MenuBackground;

    //button in menu
    LTexture PlayButton;
    LTexture BattleButton;
    LTexture SettingButton;

    //button in setting
    LTexture RightButton;
    LTexture LeftButton;
    LTexture LevelButton;
    LTexture difficulty;
    LTexture backButton;
    LTexture ghostTetrominoText;
    LTexture OnText;
    LTexture OffText;

    

    //true if we are in menu
    bool active;
};
