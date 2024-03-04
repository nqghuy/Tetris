#include "Menu.h"

Menu :: Menu()
{
    active = true;
}

Menu :: ~Menu()
{
    MenuBackground.free();
    PlayButton.free();
}

bool Menu :: load_media(SDL_Renderer *renderer)
{
    bool success = true;

    //load menu background
    if (!MenuBackground.loadFromFile(renderer, "Assets/Pictures/menu.png")){
        cout << "failed to load menu background\n";
        success = false;
    }

    //load play button texture
    if (!PlayButton.loadFromFile(renderer, "Assets/Pictures/PLAYBUTTON.png")){
        cout << "failed to load play button\n";
        success = false;
    }
    return success;
}

void Menu :: display(SDL_Renderer *renderer)
{   
    //the position and dimension of menu
    SDL_Rect menuRect = {(SCREEN_WIDTH - MenuBackground.getWidth()) / 2, (SCREEN_HEIGHT - MenuBackground.getHeight()) / 2, MenuBackground.getWidth(), MenuBackground.getHeight()};

    //draw menu background
    MenuBackground.render(renderer, menuRect.x, menuRect.y);

    //draw button texture
    PlayButton.render(renderer, menuRect.x + (menuRect.w - PlayButton.getWidth()) / 2, menuRect.y + (menuRect.h - PlayButton.getHeight()) / 2);
}

void Menu:: handle_event(SDL_Event &e)
{   
    //get x, y menu rect
    int menuX = (SCREEN_WIDTH - MenuBackground.getWidth()) / 2;
    int menuY = (SCREEN_HEIGHT - MenuBackground.getHeight()) / 2;

    //get x, y PlayButton rext
    int PlayButtonX = menuX + (MenuBackground.getWidth() - PlayButton.getWidth()) / 2;
    int PlayButtonY = menuY + (MenuBackground.getHeight() - PlayButton.getHeight()) / 2;

    //the position of mouse
    int x, y;

    //get mouse position
    SDL_GetMouseState(&x, &y);

    //if player choses playing
    if (x >= PlayButtonX && x <= PlayButtonX + PlayButton.getWidth() && y >= PlayButtonY && y <= PlayButtonY + PlayButton.getHeight() && e.type == SDL_MOUSEBUTTONDOWN){
        active = false;
    }
}

bool Menu :: get_active()
{
    return active;
}

void Menu :: set_active()
{
    active = true;
}
