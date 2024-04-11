#include "Setting.h"

Setting :: Setting(){
     active = false;
}

Setting :: ~Setting(){
     
}

bool Setting :: load_media(SDL_Renderer *renderer){
     bool success = true;
     if(!LeftButton.loadFromFile(renderer, "Assets/Pictures/left_button.png")){
          cout << "failed to load left button\n";
          success = false;
     }
     if (!RightButton.loadFromFile(renderer, "Assets/Pictures/right_button.jpg")){
          cout << "failed to load right button\n";
          success = false;
     }
     if(!LevelButton.loadFromRenderedText(renderer, SettingFont, "LEVEL", {100, 100, 100, 0})){
          cout << "failed to load level button\n";
          success = false;
     }
     if(!difficulty.loadFromRenderedText(renderer, SettingFont, "EASY", LevelColor[0])){
          cout << "failed to load difficulty text texture\n";
          success = false;
     }
     if(!backButton.loadFromFile(renderer, "Assets/Pictures/Back Button.png")){
          cout << "failed to load back button\n";
          success = false;
     }
     if (!ghostTetrominoText.loadFromRenderedText(renderer, SettingFont, "GHOST PIECE", {0, 191, 255})){
          cout << "failed to load ghost tetromino text\n";
          success = false;
     }
     if(!OnText.loadFromRenderedText(renderer, SettingFont, "ON", {0, 191, 255})){
          cout << "failed to load on text";
          success = false;
     }

     if(!OffText.loadFromRenderedText(renderer, SettingFont, "OFF", {255, 0, 0})){
          cout << "failed to load Off text";
          success = false;
     }
     if(!ThemeText.loadFromRenderedText(renderer, SettingFont, "THEME", {255, 100, 100})){
          cout << "failed to load theme text\n";
          success = false;
     }
     if(!WinterText.loadFromRenderedText(renderer, SettingFont, "Winter", {0, 255, 0})){
          cout << "failed to load winter text\n";
          success = false;
     }
     if(!AutumnText.loadFromRenderedText(renderer, SettingFont, "Autumn", {255, 150, 0})){
          cout << "failed to load autumn text\n";
          success = false;
     }
     if(!EffectText.loadFromRenderedText(renderer, SettingFont, "Effect", {0, 255, 100})){
          cout << "failed to load effect text\n";
          success = false;
     }
     if(!EffectChoice.loadFromRenderedText(renderer, SettingFont, "NONE", {0, 255, 0})){
          cout << "failed to load effect choice text\n";
          success = false;
     }
     return success;
}

bool Setting :: click_up_level_button(SDL_Event &e){
    //get x, y menu rect
    SDL_Rect menuRect = {(SCREEN_WIDTH - MenuBackground.getWidth()) / 2, (SCREEN_HEIGHT - MenuBackground.getHeight()) / 2, MenuBackground.getWidth(), MenuBackground.getHeight()};

    //get x, y right Button rext
    int rightButtonX = menuRect.x + menuRect.w - RightButton.getWidth();
    int rightButtonY = menuRect.y + (menuRect.h - LevelButton.getHeight()) / 2;

    //the position of mouse
    int x, y;

    //get mouse position
    SDL_GetMouseState(&x, &y);

    //if player choses level up
    if (x >= rightButtonX && x <= rightButtonX + RightButton.getWidth() && y >= rightButtonY && y <= rightButtonY + RightButton.getHeight() && e.type == SDL_MOUSEBUTTONDOWN){
        return true;
    }
    return false;
}

bool Setting :: click_down_level_button(SDL_Event &e){
    //get x, y menu rect
    SDL_Rect menuRect = {(SCREEN_WIDTH - MenuBackground.getWidth()) / 2, (SCREEN_HEIGHT - MenuBackground.getHeight()) / 2, MenuBackground.getWidth(), MenuBackground.getHeight()};

    //get x, y leftButton rext
    int leftButtonX = menuRect.x + menuRect.w / 2 - LeftButton.getWidth() ;
    int leftButtonY = menuRect.y + (menuRect.h - LevelButton.getHeight()) / 2;

    //the position of mouse
    int x, y;

    //get mouse position
    SDL_GetMouseState(&x, &y);

    //if player choses level down
    if (x >= leftButtonX && x <= leftButtonX + LeftButton.getWidth() && y >= leftButtonY && y <= leftButtonY + LeftButton.getHeight() && e.type == SDL_MOUSEBUTTONDOWN){
        return true;
    }
    return false;
}

bool Setting :: click_back_button (SDL_Event &e){
    //get x, y menu rect
     SDL_Rect menuRect = {(SCREEN_WIDTH - MenuBackground.getWidth()) / 2, (SCREEN_HEIGHT - MenuBackground.getHeight()) / 2, MenuBackground.getWidth(), MenuBackground.getHeight()};

     //get x, y back Button rext
     int backButtonX = menuRect.x;
     int backButtonY = menuRect.y;
     //the position of mouse
     int x, y;

     //get mouse position
     SDL_GetMouseState(&x, &y);

     //if player choses back button
     if (x >= backButtonX && x <= backButtonX + backButton.getWidth() && y >= backButtonY && y <= backButtonY + backButton.getHeight() && e.type == SDL_MOUSEBUTTONDOWN){
          active = false;
          return true;
     }
     return false;
}

bool Setting :: click_set_ghost_piece(SDL_Event &e){
    //get x, y menu rect
    SDL_Rect menuRect = {(SCREEN_WIDTH - MenuBackground.getWidth()) / 2, (SCREEN_HEIGHT - MenuBackground.getHeight()) / 2, MenuBackground.getWidth(), MenuBackground.getHeight()};

    //left button
    int leftButtonX = menuRect.x + menuRect.w / 2 - LeftButton.getWidth(); 
    int leftButtonY = menuRect.y + (menuRect.h - LevelButton.getHeight()) / 2 + LevelButton.getHeight();

    //right button
    int rightButtonX = menuRect.x + menuRect.w - RightButton.getWidth();
    int rightButtonY = menuRect.y + (menuRect.h - LevelButton.getHeight()) / 2 + LevelButton.getHeight();
    //the position of mouse
    int x, y;

    //get mouse position
    SDL_GetMouseState(&x, &y);

    //if player choses changeing ghost tetromino
    if (x >= leftButtonX && x <= leftButtonX + LeftButton.getWidth() && y >= leftButtonY && y <= leftButtonY + LeftButton.getHeight() && e.type == SDL_MOUSEBUTTONDOWN){
        return true;
    }
    else if (x >= rightButtonX && x <= rightButtonX + RightButton.getWidth() && y >= rightButtonY && y <= rightButtonY + RightButton.getHeight() && e.type == SDL_MOUSEBUTTONDOWN){
        return true;
    }
    return false;
}

bool Setting :: click_winter_theme(SDL_Event &e){
     //get x, y menu rect
    SDL_Rect menuRect = {(SCREEN_WIDTH - MenuBackground.getWidth()) / 2, (SCREEN_HEIGHT - MenuBackground.getHeight()) / 2, MenuBackground.getWidth(), MenuBackground.getHeight()};

    //the position of mouse
    int x, y;

    //get mouse position
    SDL_GetMouseState(&x, &y);

     //if player choses changeing ghost tetromino
     
    return false;
}

bool Setting :: click_change_theme(SDL_Event &e){
     //get x, y menu rect
     SDL_Rect menuRect = {(SCREEN_WIDTH - MenuBackground.getWidth()) / 2, (SCREEN_HEIGHT - MenuBackground.getHeight()) / 2, MenuBackground.getWidth(), MenuBackground.getHeight()};

     //right button
     int rightButtonX = menuRect.x + menuRect.w - RightButton.getWidth();
     int rightButtonY = menuRect.y + (menuRect.h - LevelButton.getHeight()) / 2 + LevelButton.getHeight() * 2;

     //left button
     int leftButtonX = menuRect.x + menuRect.w / 2 - LeftButton.getWidth();
     int leftButtonY = menuRect.y + (menuRect.h - LevelButton.getHeight()) / 2 + LevelButton.getHeight() * 2;

     //the position of mouse
     int x, y;

     //get mouse position
     SDL_GetMouseState(&x, &y);

    //if player choses changeing ghost tetromino
     if (x >= rightButtonX && x <= rightButtonX + RightButton.getWidth() && y >= rightButtonY && y <= rightButtonY + RightButton.getHeight() && e.type == SDL_MOUSEBUTTONDOWN){
        return true;
     }
     else if (x >= leftButtonX && x <= leftButtonX + LeftButton.getWidth() && y >= leftButtonY && y <= leftButtonY + LeftButton.getHeight() && e.type == SDL_MOUSEBUTTONDOWN){
          return true;
     }
     return false;
}

bool Setting :: click_autumn_theme(SDL_Event &e){
     //get x, y menu rect
     SDL_Rect menuRect = {(SCREEN_WIDTH - MenuBackground.getWidth()) / 2, (SCREEN_HEIGHT - MenuBackground.getHeight()) / 2, MenuBackground.getWidth(), MenuBackground.getHeight()};

     //right button
     int rightButtonX = menuRect.x + menuRect.w - RightButton.getWidth();
     int rightButtonY = menuRect.y + (menuRect.h - LevelButton.getHeight()) / 2 + LevelButton.getHeight() * 2;
     //the position of mouse
     int x, y;

     //get mouse position
     SDL_GetMouseState(&x, &y);

    //if player choses changeing ghost tetromino
     if (x >= rightButtonX && x <= rightButtonX + RightButton.getWidth() && y >= rightButtonY && y <= rightButtonY + RightButton.getHeight() && e.type == SDL_MOUSEBUTTONDOWN){
        return true;
     }
     return false;
}

bool Setting :: click_left_change_effect(SDL_Event &e){
     //get x, y menu rect
    SDL_Rect menuRect = {(SCREEN_WIDTH - MenuBackground.getWidth()) / 2, (SCREEN_HEIGHT - MenuBackground.getHeight()) / 2, MenuBackground.getWidth(), MenuBackground.getHeight()};

    //get x, y leftButton rext
    int leftButtonX = menuRect.x + menuRect.w / 2 - LeftButton.getWidth() ;
    int leftButtonY = menuRect.y + (menuRect.h - LevelButton.getHeight()) / 2 + LevelButton.getHeight() * 3;

    //the position of mouse
    int x, y;

    //get mouse position
    SDL_GetMouseState(&x, &y);

    //if player choses level down
    if (x >= leftButtonX && x <= leftButtonX + LeftButton.getWidth() && y >= leftButtonY && y <= leftButtonY + LeftButton.getHeight() && e.type == SDL_MOUSEBUTTONDOWN){
        return true;
    }
    return false;
}

bool Setting :: click_right_change_effect(SDL_Event &e){
     //get x, y menu rect
    SDL_Rect menuRect = {(SCREEN_WIDTH - MenuBackground.getWidth()) / 2, (SCREEN_HEIGHT - MenuBackground.getHeight()) / 2, MenuBackground.getWidth(), MenuBackground.getHeight()};

    //get x, y right Button rext
    int rightButtonX = menuRect.x + menuRect.w - RightButton.getWidth();
    int rightButtonY = menuRect.y + (menuRect.h - LevelButton.getHeight()) / 2 + + LevelButton.getHeight() * 3;

    //the position of mouse
    int x, y;

    //get mouse position
    SDL_GetMouseState(&x, &y);

    //if player choses level up
    if (x >= rightButtonX && x <= rightButtonX + RightButton.getWidth() && y >= rightButtonY && y <= rightButtonY + RightButton.getHeight() && e.type == SDL_MOUSEBUTTONDOWN){
        return true;
    }
    return false;
}

void Setting :: display_level(SDL_Renderer *renderer, int level){
     difficulty.loadFromRenderedText(renderer, SettingFont, LevelText[level - 1], LevelColor[level - 1]);

     SDL_Rect menuRect = {(SCREEN_WIDTH - MenuBackground.getWidth()) / 2, (SCREEN_HEIGHT - MenuBackground.getHeight()) / 2, MenuBackground.getWidth(), MenuBackground.getHeight()};

     //draw level button
     int margin = 50;
     LevelButton.render(renderer, menuRect.x + margin, menuRect.y + (menuRect.h - LevelButton.getHeight()) / 2);

     //draw content level
     difficulty.render(renderer, menuRect.x + menuRect.w / 2  + (menuRect.w / 2 - difficulty.getWidth()) / 2 , menuRect.y + (menuRect.h - LevelButton.getHeight()) / 2);

     //draw left button(decrease level)
     LeftButton.render(renderer, menuRect.x + menuRect.w / 2 - LeftButton.getWidth() , menuRect.y + (menuRect.h - LevelButton.getHeight()) / 2);

     //draw right button(increase level)
     RightButton.render(renderer, menuRect.x + menuRect.w - RightButton.getWidth(), menuRect.y + (menuRect.h - LevelButton.getHeight()) / 2);
}

void Setting :: display_ghostTetromino(SDL_Renderer *renderer, bool ghostTetromino){
     int margin = 50;

     SDL_Rect menuRect = {(SCREEN_WIDTH - MenuBackground.getWidth()) / 2, (SCREEN_HEIGHT - MenuBackground.getHeight()) / 2, MenuBackground.getWidth(), MenuBackground.getHeight()};
 

     //draw ghost tetromino choice text
     ghostTetrominoText.render(renderer, menuRect.x + margin, menuRect.y + (menuRect.h - LevelButton.getHeight()) / 2 + LevelButton.getHeight());

     //draw on or off text
     if(ghostTetromino){
          OnText.render(renderer, menuRect.x + menuRect.w / 2 + (menuRect.w / 2 - OnText.getWidth()) / 2 , menuRect.y + (menuRect.h - LevelButton.getHeight()) / 2 + OnText.getHeight());
     }
     else
     {
          OffText.render(renderer, menuRect.x + menuRect.w / 2  + (menuRect.w / 2 - OffText.getWidth()) / 2 , menuRect.y + (menuRect.h - LevelButton.getHeight()) / 2 + OffText.getHeight());
     }

     //draw left button(change ghost piece)
     LeftButton.render(renderer, menuRect.x + menuRect.w / 2 - LeftButton.getWidth(), menuRect.y + (menuRect.h - LevelButton.getHeight()) / 2 + LevelButton.getHeight());

     //draw right button(change ghost piece)
     RightButton.render(renderer, menuRect.x + menuRect.w - RightButton.getWidth(), menuRect.y + (menuRect.h - LevelButton.getHeight()) / 2 + LevelButton.getHeight());

}

void Setting :: display_theme(SDL_Renderer *renderer, Theme theme){
     int margin = 50;

     SDL_Rect menuRect = {(SCREEN_WIDTH - MenuBackground.getWidth()) / 2, (SCREEN_HEIGHT - MenuBackground.getHeight()) / 2, MenuBackground.getWidth(), MenuBackground.getHeight()};


     //draw theme
     ThemeText.render(renderer, menuRect.x + margin, menuRect.y + (menuRect.h - LevelButton.getHeight()) / 2 + LevelButton.getHeight() * 2);

     if(theme == Winter){
          WinterText.render(renderer, menuRect.x + menuRect.w / 2 + (menuRect.w / 2 - WinterText.getWidth()) / 2 , menuRect.y + (menuRect.h - LevelButton.getHeight()) / 2 + WinterText.getHeight() * 2);
     }
     else
     {
          AutumnText.render(renderer, menuRect.x + menuRect.w / 2  + (menuRect.w / 2 - AutumnText.getWidth()) / 2 , menuRect.y + (menuRect.h - LevelButton.getHeight()) / 2 + WinterText.getHeight() * 2);
     }

     //draw left button(change theme)
     LeftButton.render(renderer, menuRect.x + menuRect.w / 2 - LeftButton.getWidth(), menuRect.y + (menuRect.h - LevelButton.getHeight()) / 2 + LevelButton.getHeight() * 2);

     //draw right button(change theme)
     RightButton.render(renderer, menuRect.x + menuRect.w - RightButton.getWidth(), menuRect.y + (menuRect.h - LevelButton.getHeight()) / 2 + LevelButton.getHeight() * 2);
}

void Setting :: display_effect(SDL_Renderer *renderer, Effect effect){
     int margin = 50;

     SDL_Rect menuRect = {(SCREEN_WIDTH - MenuBackground.getWidth()) / 2, (SCREEN_HEIGHT - MenuBackground.getHeight()) / 2, MenuBackground.getWidth(), MenuBackground.getHeight()};

     //draw theme
     EffectText.render(renderer, menuRect.x + margin, menuRect.y + (menuRect.h - LevelButton.getHeight()) / 2 + LevelButton.getHeight() * 3);

     if(effect == None){
          EffectChoice.loadFromRenderedText(renderer, SettingFont, "NONE", {75, 125, 180});
     }
     else if (effect == Capcut)
     {
          EffectChoice.loadFromRenderedText(renderer, SettingFont, "CAPCUT", {200, 125, 255});
     }
     else{
          EffectChoice.loadFromRenderedText(renderer, SettingFont, "FADE", {75, 255, 100});
     }
     EffectChoice.render(renderer, menuRect.x + menuRect.w / 2  + (menuRect.w / 2 - EffectChoice.getWidth()) / 2 , menuRect.y + (menuRect.h - LevelButton.getHeight()) / 2 + EffectChoice.getHeight() * 3);


     //draw left button(change theme)
     LeftButton.render(renderer, menuRect.x + menuRect.w / 2 - LeftButton.getWidth(), menuRect.y + (menuRect.h - LevelButton.getHeight()) / 2 + LevelButton.getHeight() * 3);

     //draw right button(change theme)
     RightButton.render(renderer, menuRect.x + menuRect.w - RightButton.getWidth(), menuRect.y + (menuRect.h - LevelButton.getHeight()) / 2 + LevelButton.getHeight() * 3);
}


void Setting :: display(SDL_Renderer *renderer, int level, bool ghostTetromino, Theme theme, Effect effect){

     SDL_Rect menuRect = {(SCREEN_WIDTH - MenuBackground.getWidth()) / 2, (SCREEN_HEIGHT - MenuBackground.getHeight()) / 2, MenuBackground.getWidth(), MenuBackground.getHeight()};

     display_level(renderer, level);
     display_ghostTetromino(renderer, ghostTetromino);
     display_theme(renderer, theme);
     display_effect(renderer, effect);

     //draw back button
     backButton.render(renderer, menuRect.x, menuRect.y);
}


bool Setting :: get_active(){
     return active;
}

void Setting :: set_active(){
     active = true;
}