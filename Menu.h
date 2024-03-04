#pragma once
#include "Data.h"
#include "Texture.h"
#include "include/SDL2/SDL.h"

class Menu
{
public:
    Menu();
    ~Menu();
    bool load_media(SDL_Renderer *renderer);
    void display(SDL_Renderer *renderer);
    void handle_event(SDL_Event &e);
    bool get_active();
    void set_active();
private:
    LTexture MenuBackground;
    LTexture PlayButton;
    bool active;
};
