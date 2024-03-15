#include "Menu.h"

Menu :: Menu()
{
    inSetting = false;
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

    if (!BattleButton.loadFromFile(renderer, "Assets/Pictures/BATTLE.png")){
        cout << "failed to load battle button\n";
        success = false;
    }

    if(!SettingButton.loadFromFile(renderer, "Assets/Pictures/SETTING.png")){
        cout << "failed to load setting button\n";
        success = false;
    }
    if(!LeftButton.loadFromFile(renderer, "Assets/Pictures/left_button.jpg")){
        cout << "failed to load left button\n";
        success = false;
    }
    if (!RightButton.loadFromFile(renderer, "Assets/Pictures/right_button.jpg")){
        cout << "failed to load right button\n";
        success = false;
    }
    if(!LevelButton.loadFromFile(renderer, "Assets/Pictures/Level_button.png")){
        cout << "failed to load level button\n";
        success = false;
    }
    if(!difficulty.loadFromRenderedText(renderer, SettingFont, "EASY", {100, 100, 100, 0})){
        cout << "failed to load difficulty text texture\n";
        success = false;
    }
    if(!backButton.loadFromFile(renderer, "Assets/Pictures/Back Button.png")){
        cout << "failed to load back button\n";
        success = false;
    }
    return success;
}

void Menu :: display(SDL_Renderer *renderer, int level)
{   
    difficulty.loadFromRenderedText(renderer, SettingFont, LevelText[level - 1], {100, 100, 0});

    //the position and dimension of menu
    SDL_Rect menuRect = {(SCREEN_WIDTH - MenuBackground.getWidth()) / 2, (SCREEN_HEIGHT - MenuBackground.getHeight()) / 2, MenuBackground.getWidth(), MenuBackground.getHeight()};

    //draw menu background
    MenuBackground.render(renderer, menuRect.x, menuRect.y);

    //draw button texture
    if(!inSetting){

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
    else{
        //draw level button
        LevelButton.render(renderer, menuRect.x + (menuRect.w - LevelButton.getWidth()) / 2, menuRect.y + (menuRect.h - LevelButton.getHeight()) / 2);

        //draw content level
        difficulty.render(renderer, menuRect.x + (menuRect.w - difficulty.getWidth()) / 2, menuRect.y + (menuRect.h - LevelButton.getHeight()) / 2 + LevelButton.getHeight());

        //draw left button(decrease level)
        LeftButton.render(renderer, menuRect.x + (menuRect.w - LevelButton.getWidth()) / 2 - LeftButton.getWidth() , menuRect.y + (menuRect.h - LevelButton.getHeight()) / 2 + LevelButton.getHeight());

        //draw right button(increase level)
        RightButton.render(renderer, menuRect.x + (menuRect.w - LevelButton.getWidth()) / 2 + LevelButton.getWidth(), menuRect.y + (menuRect.h - LevelButton.getHeight()) / 2 + LevelButton.getHeight());

        //draw back button
        backButton.render(renderer, menuRect.x, menuRect.y);
    }
    
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

    //get x, y PlayButton rext
    int battleButtonX = menuX + (MenuBackground.getWidth() - PlayButton.getWidth()) / 2;
    int battleButtonY = menuY + (MenuBackground.getHeight() - PlayButton.getHeight()) / 2 + PlayButton.getHeight() *  3 / 2;

    //the position of mouse
    int x, y;

    //get mouse position
    SDL_GetMouseState(&x, &y);

    //if player choses playing
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

    //get x, y PlayButton rext
    int settingButtonX = menuX + (MenuBackground.getWidth() - PlayButton.getWidth()) / 2;
    int settingButtonY = menuY + (MenuBackground.getHeight() - PlayButton.getHeight()) / 2 + PlayButton.getHeight() *  3;

    //the position of mouse
    int x, y;

    //get mouse position
    SDL_GetMouseState(&x, &y);

    //if player choses playing
    if (x >= settingButtonX && x <= settingButtonX + SettingButton.getWidth() && y >= settingButtonY && y <= settingButtonY + SettingButton.getHeight() && e.type == SDL_MOUSEBUTTONDOWN){
        inSetting = true;
        return true;
    }
    return false;
}

bool Menu :: click_up_level_button(SDL_Event &e){
    //get x, y menu rect
    SDL_Rect menuRect = {(SCREEN_WIDTH - MenuBackground.getWidth()) / 2, (SCREEN_HEIGHT - MenuBackground.getHeight()) / 2, MenuBackground.getWidth(), MenuBackground.getHeight()};

    //get x, y PlayButton rext
    int rightButtonX = menuRect.x + (menuRect.w - LevelButton.getWidth()) / 2 + LevelButton.getWidth() ;
    int rightButtonY = menuRect.y + (menuRect.h - LevelButton.getHeight()) / 2 + LevelButton.getHeight();
    //the position of mouse
    int x, y;

    //get mouse position
    SDL_GetMouseState(&x, &y);

    //if player choses playing
    if (x >= rightButtonX && x <= rightButtonX + RightButton.getWidth() && y >= rightButtonY && y <= rightButtonY + RightButton.getHeight() && e.type == SDL_MOUSEBUTTONDOWN){
        return true;
    }
    return false;
}

bool Menu :: click_down_level_button(SDL_Event &e){
    //get x, y menu rect
    SDL_Rect menuRect = {(SCREEN_WIDTH - MenuBackground.getWidth()) / 2, (SCREEN_HEIGHT - MenuBackground.getHeight()) / 2, MenuBackground.getWidth(), MenuBackground.getHeight()};

    //get x, y PlayButton rext
    int leftButtonX = menuRect.x + (menuRect.w - LevelButton.getWidth()) / 2 - LeftButton.getWidth();
    int leftButtonY = menuRect.y + (menuRect.h - LevelButton.getHeight()) / 2 + LevelButton.getHeight();
    //the position of mouse
    int x, y;

    //get mouse position
    SDL_GetMouseState(&x, &y);

    //if player choses playing
    if (x >= leftButtonX && x <= leftButtonX + LeftButton.getWidth() && y >= leftButtonY && y <= leftButtonY + LeftButton.getHeight() && e.type == SDL_MOUSEBUTTONDOWN){
        return true;
    }
    return false;
}

bool Menu :: click_back_button (SDL_Event &e){
    //get x, y menu rect
    SDL_Rect menuRect = {(SCREEN_WIDTH - MenuBackground.getWidth()) / 2, (SCREEN_HEIGHT - MenuBackground.getHeight()) / 2, MenuBackground.getWidth(), MenuBackground.getHeight()};

    //get x, y back Button rext
    int backButtonX = menuRect.x;
    int backButtonY = menuRect.y;
    //the position of mouse
    int x, y;

    //get mouse position
    SDL_GetMouseState(&x, &y);

    //if player choses playing
    if (x >= backButtonX && x <= backButtonX + backButton.getWidth() && y >= backButtonY && y <= backButtonY + backButton.getHeight() && e.type == SDL_MOUSEBUTTONDOWN){
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

void Menu :: set_in_setting(){
    inSetting = true;
}

bool Menu :: check_in_setting(){
    return inSetting;
}

void Menu::set_not_in_setting(){
    inSetting = false;
}