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
    void display(SDL_Renderer *renderer, int level);

    //handle event
    bool click_play(SDL_Event &e);

    bool click_battle(SDL_Event &e);
    
    bool click_setting(SDL_Event &e);

    bool click_up_level_button(SDL_Event &e);

    bool click_down_level_button(SDL_Event &e);

    bool click_back_button(SDL_Event &e);

    //if we are in menu
    bool get_active();

    //set active
    void set_active();

    void set_in_setting();

    void set_not_in_setting();

    bool check_in_setting();
private:
    bool inSetting;

    //menu texture
    LTexture MenuBackground;

    //play button texture
    LTexture PlayButton;

    //battle button texture
    LTexture BattleButton;

    LTexture RightButton;

    LTexture LeftButton;

    LTexture LevelButton;

    LTexture difficulty;

    LTexture backButton;

    //setting button texture
    LTexture SettingButton;

    //true if we are in menu
    bool active;
};
