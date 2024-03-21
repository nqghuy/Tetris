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

    //load play button texture
    if (!PlayButton.loadFromFile(renderer, "Assets/Pictures/PLAYBUTTON.png")){
        cout << "failed to load play button\n";
        success = false;
    }

    if (!BattleButton.loadFromFile(renderer, "Assets/Pictures/BATTLE.png")){
        cout << "failed to load battle button\n";
        success = false;
    }

    if(!SettingButton.loadFromFile(renderer, "Assets/Pictures/SETTING.png")){
        cout << "failed to load setting button\n";
        success = false;
    }
    return success;
}

void Menu :: display(SDL_Renderer *renderer, int level, bool ghostTetromino)
{   

    //the position and dimension of menu
    SDL_Rect menuRect = {(SCREEN_WIDTH - MenuBackground.getWidth()) / 2, (SCREEN_HEIGHT - MenuBackground.getHeight()) / 2, MenuBackground.getWidth(), MenuBackground.getHeight()};

    //draw menu background
    MenuBackground.render(renderer, menuRect.x, menuRect.y);

    //draw button texture

    //draw play button
    PlayButton.render(renderer, menuRect.x + (menuRect.w - PlayButton.getWidth()) / 2, menuRect.y + (menuRect.h - PlayButton.getHeight()) / 2);

    //the battle button coordinate
    int battleButton_x = menuRect.x + (menuRect.w - PlayButton.getWidth()) / 2;
    int battleButton_y = menuRect.y + (menuRect.h - PlayButton.getHeight()) / 2 + PlayButton.getHeight() *  3 / 2;

    //draw battle button
    BattleButton.render(renderer, battleButton_x , battleButton_y);
    
    //setting button coordinate
    int settingButton_x = battleButton_x;
    int settingButton_y =  menuRect.y + (menuRect.h - PlayButton.getHeight()) / 2 + PlayButton.getHeight() *  3;

    //draw setting button
    SettingButton.render(renderer, settingButton_x, settingButton_y);
}

bool Menu:: click_play(SDL_Event &e)
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
        return true;
    }
    return false;
}

bool Menu :: click_battle(SDL_Event &e){
    //get x, y menu rect
    int menuX = (SCREEN_WIDTH - MenuBackground.getWidth()) / 2;
    int menuY = (SCREEN_HEIGHT - MenuBackground.getHeight()) / 2;

    //get x, y battle rext
    int battleButtonX = menuX + (MenuBackground.getWidth() - PlayButton.getWidth()) / 2;
    int battleButtonY = menuY + (MenuBackground.getHeight() - PlayButton.getHeight()) / 2 + PlayButton.getHeight() *  3 / 2;

    //the position of mouse
    int x, y;

    //get mouse position
    SDL_GetMouseState(&x, &y);

    //if player choses battle
    if (x >= battleButtonX && x <= battleButtonX + BattleButton.getWidth() && y >= battleButtonY && y <= battleButtonY + BattleButton.getHeight() && e.type == SDL_MOUSEBUTTONDOWN){
        active = false;
        return true;
    }
    return false;
}

bool Menu :: click_setting(SDL_Event &e){
    //get x, y menu rect
    int menuX = (SCREEN_WIDTH - MenuBackground.getWidth()) / 2;
    int menuY = (SCREEN_HEIGHT - MenuBackground.getHeight()) / 2;

    //get x, y setting rext
    int settingButtonX = menuX + (MenuBackground.getWidth() - PlayButton.getWidth()) / 2;
    int settingButtonY = menuY + (MenuBackground.getHeight() - PlayButton.getHeight()) / 2 + PlayButton.getHeight() *  3;

    //the position of mouse
    int x, y;

    //get mouse position
    SDL_GetMouseState(&x, &y);

    //if player choses setting
    if (x >= settingButtonX && x <= settingButtonX + SettingButton.getWidth() && y >= settingButtonY && y <= settingButtonY + SettingButton.getHeight() && e.type == SDL_MOUSEBUTTONDOWN){
        active = false;
        return true;
    }
    return false;
}

bool Menu :: get_active()
{
    return active;
}

void Menu :: set_active()
{
    active = true;
}

void Menu :: set_not_active(){
    active = false;
}

void Menu :: free_memory(){
    PlayButton.free();
    SettingButton.free();
    BattleButton.free();
}