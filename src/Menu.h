#pragma once
#include "Data.h"
#include "Texture.h"
#include "../include/SDL2/SDL.h"

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

    //if we are in menu
    bool get_active();

    //set active
    void set_active();

    void set_not_active();

private:

    //button in menu
    LTexture PlayButton;
    LTexture BattleButton;
    LTexture SettingButton;

    //true if we are in menu
    bool active;
};
