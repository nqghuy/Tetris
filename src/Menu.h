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
    void display(SDL_Renderer *renderer);

    //display button
    void display_Play_button(SDL_Renderer *renderer);
    void display_Battle_button(SDL_Renderer *renderer);
    void display_VsCom_button(SDL_Renderer *renderer);
    void display_Setting_button(SDL_Renderer *renderer);


    //handle event
    bool click_play(SDL_Event &e);
    bool click_battle(SDL_Event &e);
    bool click_setting(SDL_Event &e);
    bool click_vsCom(SDL_Event &e);
    bool click_About(SDL_Event &e);

    //if we are in menu
    bool get_active();

    //set active
    void set_active();

    //player are not in menu
    void set_not_active();

    //free memory
    void free_memory();

private:
    TTF_Font *menuFont;

    //button in menu
    LTexture PlayButton;
    LTexture PlayButton2;

    LTexture BattleButton;
    LTexture BattleButton2;

    LTexture SettingButton;
    LTexture SettingButton2;

    LTexture VsComButton;
    LTexture VsComButton2;

    LTexture About;

    //true if we are in menu
    bool active;

    int menuXCoordinate;
    int menuYCoordinate;
};
