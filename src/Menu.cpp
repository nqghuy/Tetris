#include "Menu.h"

Menu :: Menu()
{
    active = true;
    menuXCoordinate = 0;
}

Menu :: ~Menu()
{
    MenuBackground.free();
    PlayButton.free();
    PlayButton2.free();
    BattleButton.free();
    BattleButton2.free();
    SettingButton.free();
    SettingButton2.free();
    VsComButton.free();
    VsComButton2.free();
    About.free();
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
    if (!About.loadFromRenderedText(renderer, SettingFont, "About", {0, 0, 0})){
        cout << "failed to load about me text\n";
        success = false;
    }
    menuXCoordinate = (SCREEN_WIDTH - PlayButton.getWidth()) / 2;
    menuYCoordinate = (SCREEN_HEIGHT - PlayButton.getHeight()) / 2;
    return success;
}

void Menu :: display_Play_button(SDL_Renderer *renderer){
    int x, y;
    SDL_GetMouseState(&x, &y);

    //draw play button
    int playButtonX = menuXCoordinate;
    int playButtonY = menuYCoordinate - menuButtonDistance / 2;
    PlayButton.render(renderer, playButtonX, playButtonY);

    //if the mouse is in the play button 
    if (x >= playButtonX && x <= playButtonX + PlayButton.getWidth() & y >= playButtonY && y <= playButtonY + PlayButton.getHeight()){
        PlayButton2.render(renderer, playButtonX, playButtonY);
    }
}

void Menu :: display_Battle_button(SDL_Renderer *renderer){
    int x, y;
    SDL_GetMouseState(&x, &y);

    //the battle button coordinate
    int battleButtonX = menuXCoordinate;
    int battleButtonY = menuYCoordinate + menuButtonDistance /2;

    //draw battle button
    BattleButton.render(renderer, battleButtonX , battleButtonY);

    //if the mouse is in battle button
    if (x >= battleButtonX && x <= battleButtonX + BattleButton.getWidth() & y >= battleButtonY && y <= battleButtonY + BattleButton.getHeight()){
        BattleButton2.render(renderer, battleButtonX, battleButtonY);
    }
}

void Menu :: display_VsCom_button(SDL_Renderer *renderer){
    int x, y;
    SDL_GetMouseState(&x, &y);
    
    //the vs com button coordinate
    int VsComButtonX = menuXCoordinate;
    int VsComButtonY = menuYCoordinate + menuButtonDistance * 3 / 2;

    VsComButton.render(renderer, VsComButtonX, VsComButtonY);
    if (x >= VsComButtonX && x <= VsComButtonX + VsComButton.getWidth() & y >= VsComButtonY && y <= VsComButtonY + VsComButton.getHeight()){
        VsComButton2.render(renderer, VsComButtonX, VsComButtonY);
    }
}

void Menu :: display_Setting_button(SDL_Renderer *renderer){
    int x, y;
    SDL_GetMouseState(&x, &y);

    //setting button coordinate
    int settingButtonX = menuXCoordinate;
    int settingButtonY =  menuYCoordinate + menuButtonDistance * 5 / 2;
    //draw setting button
    SettingButton.render(renderer, settingButtonX, settingButtonY);
    if (x >= settingButtonX && x <= settingButtonX + SettingButton.getWidth() & y >= settingButtonY && y <= settingButtonY + SettingButton.getHeight()){
        SettingButton2.render(renderer, settingButtonX, settingButtonY);
    }

}

void Menu :: display(SDL_Renderer *renderer)
{   

    //the position and dimension of menu
    SDL_Rect menuRect = {(SCREEN_WIDTH - MenuBackground.getWidth()) / 2, (SCREEN_HEIGHT - MenuBackground.getHeight()) / 2, MenuBackground.getWidth(), MenuBackground.getHeight()};

    //draw menu background
    MenuBackground.render(renderer, menuRect.x, menuRect.y);

    //display button    
    display_Play_button(renderer);
    display_Battle_button(renderer);
    display_Setting_button(renderer);
    display_VsCom_button(renderer);

    //display "About"
    About.render(renderer, 0, SCREEN_HEIGHT - About.getHeight());
}

bool Menu:: click_play(SDL_Event &e)
{   
    //get x, y PlayButton rext
    int PlayButtonX = menuXCoordinate;
    int PlayButtonY = menuYCoordinate - menuButtonDistance / 2;

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
    int battleButtonX = menuXCoordinate;
    int battleButtonY = menuYCoordinate + menuButtonDistance /2;

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
    int settingButtonX = menuXCoordinate;
    int settingButtonY =  menuYCoordinate + menuButtonDistance * 5 / 2;

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
    int VsComButtonX = menuXCoordinate;
    int VsComButtonY = menuYCoordinate + menuButtonDistance * 3 /2;

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

bool Menu :: click_About(SDL_Event &e){
    //get mouse position
    int x, y;
    SDL_GetMouseState(&x, &y);
    
    //click about
    if (e.type == SDL_MOUSEBUTTONDOWN && x >= 0 && x <= About.getWidth() && y >= SCREEN_HEIGHT - About.getHeight() && y <= SCREEN_HEIGHT){
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
    MenuBackground.free();
    PlayButton.free();
    PlayButton2.free();
    BattleButton.free();
    BattleButton2.free();
    SettingButton.free();
    SettingButton2.free();
    VsComButton.free();
    VsComButton2.free();
    About.free();
}