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
    void display(SDL_Renderer *renderer);

    //handle event
    bool click_play(SDL_Event &e);

    bool click_battle(SDL_Event &e);

    //if we are in menu
    bool get_active();

    //set active
    void set_active();
private:
    //menu texture
    LTexture MenuBackground;

    //play button texture
    LTexture PlayButton;

    //battle button texture
    LTexture BattleButton;

    //true if we are in menu
    bool active;
};
