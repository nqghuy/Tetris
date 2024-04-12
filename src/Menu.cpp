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

    //load button texture
    if (!PlayButton.loadFromFile(renderer, "Assets/Pictures/PLAYBUTTON.png")){
        cout << "failed to load play button\n";
        success = false;
    }
    if (!PlayButton2.loadFromFile(renderer, "Assets/Pictures/PLAYBUTTON2.png")){
        cout << "failed to load play button\n";
        success = false;
    }
    if (!BattleButton.loadFromFile(renderer, "Assets/Pictures/BATTLE.png")){
        cout << "failed to load battle button\n";
        success = false;
    }
    if (!BattleButton2.loadFromFile(renderer, "Assets/Pictures/BATTLE2.png")){
        cout << "failed to load battle button\n";
        success = false;
    }
    if(!SettingButton.loadFromFile(renderer, "Assets/Pictures/SETTING.png")){
        cout << "failed to load setting button\n";
        success = false;
    }
    if(!SettingButton2.loadFromFile(renderer, "Assets/Pictures/SETTING2.png")){
        cout << "failed to load setting button\n";
        success = false;
    }
    if(!VsComButton.loadFromFile(renderer, "Assets/Pictures/VsCom.png")){
        cout << "failed to load VsCom button\n";
        success = false;
    }
    if(!VsComButton2.loadFromFile(renderer, "Assets/Pictures/VsCom2.png")){
        cout << "failed to load VsCom button\n";
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

    int x, y;
    SDL_GetMouseState(&x, &y);

    //draw button texture

    //draw play button
    int playButtonX = (SCREEN_WIDTH - PlayButton.getWidth()) / 2;
    int playButtonY = (SCREEN_HEIGHT - PlayButton.getHeight()) / 2 - menuButtonDistance / 2;
    PlayButton.render(renderer, playButtonX, playButtonY);

    if (x >= playButtonX && x <= playButtonX + PlayButton.getWidth() & y >= playButtonY && y <= playButtonY + PlayButton.getHeight()){
        PlayButton2.render(renderer, playButtonX, playButtonY);
    }

    //the battle button coordinate
    int battleButtonX = (SCREEN_WIDTH - PlayButton.getWidth()) / 2;
    int battleButtonY = (SCREEN_HEIGHT - PlayButton.getHeight()) / 2 + menuButtonDistance /2;

    //draw battle button
    BattleButton.render(renderer, battleButtonX , battleButtonY);

    if (x >= battleButtonX && x <= battleButtonX + BattleButton.getWidth() & y >= battleButtonY && y <= battleButtonY + BattleButton.getHeight()){
        BattleButton2.render(renderer, battleButtonX, battleButtonY);
    }

    //the vs com button coordinate
    int VsComButtonX = (SCREEN_WIDTH - PlayButton.getWidth()) / 2;
    int VsComButtonY = (SCREEN_HEIGHT - PlayButton.getHeight()) / 2 + menuButtonDistance * 3 /2;
    VsComButton.render(renderer, VsComButtonX, VsComButtonY);
    if (x >= VsComButtonX && x <= VsComButtonX + VsComButton.getWidth() & y >= VsComButtonY && y <= VsComButtonY + VsComButton.getHeight()){
        VsComButton2.render(renderer, VsComButtonX, VsComButtonY);
    }

    //setting button coordinate
    int settingButtonX = (SCREEN_WIDTH - PlayButton.getWidth()) / 2;
    int settingButtonY =  (SCREEN_HEIGHT - PlayButton.getHeight()) / 2 + menuButtonDistance * 5 / 2;
    //draw setting button
    SettingButton.render(renderer, settingButtonX, settingButtonY);
    if (x >= settingButtonX && x <= settingButtonX + SettingButton.getWidth() & y >= settingButtonY && y <= settingButtonY + SettingButton.getHeight()){
        SettingButton2.render(renderer, settingButtonX, settingButtonY);
    }
}

bool Menu:: click_play(SDL_Event &e)
{   
    //get x, y PlayButton rext
    int PlayButtonX = (SCREEN_WIDTH - PlayButton.getWidth()) / 2;
    int PlayButtonY = (SCREEN_HEIGHT - PlayButton.getHeight()) / 2 - menuButtonDistance / 2;

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
    //the battle button coordinate
    int battleButtonX = (SCREEN_WIDTH - PlayButton.getWidth()) / 2;
    int battleButtonY = (SCREEN_HEIGHT - PlayButton.getHeight()) / 2 + menuButtonDistance /2;

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
    //setting button coordinate
    int settingButtonX = (SCREEN_WIDTH - PlayButton.getWidth()) / 2;
    int settingButtonY =  (SCREEN_HEIGHT - PlayButton.getHeight()) / 2 + menuButtonDistance * 5 / 2;

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

bool Menu :: click_vsCom(SDL_Event &e){
    //the vs com button coordinate
    int VsComButtonX = (SCREEN_WIDTH - PlayButton.getWidth()) / 2;
    int VsComButtonY = (SCREEN_HEIGHT - PlayButton.getHeight()) / 2 + menuButtonDistance * 3 /2;

    //the position of mouse
    int x, y;

    //get mouse position
    SDL_GetMouseState(&x, &y);

    //if player choses setting
    if (x >=  VsComButtonX && x <=  VsComButtonX + VsComButton.getWidth() && y >= VsComButtonY && y <= VsComButtonY + VsComButton.getHeight() && e.type == SDL_MOUSEBUTTONDOWN){
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