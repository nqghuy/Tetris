#include "Tetris.h"
#include <fstream>
//detail in data.h
Mix_Music *gPlayingMusic;

Mix_Chunk *gNiceSoundEffect;

Mix_Chunk *gLoseSoundEffect;

Mix_Chunk *gDropSoundEffect;

TTF_Font *ScoreFont;

TTF_Font *SettingFont;

TTF_Font *CountDownFont;

LTexture gScoreFrame;

LTexture gWellFrame;

LTexture gLoseBackground;

LTexture gReplayButton;

LTexture gHomeButton;

LTexture gPlayer1Wins;

LTexture gPlayer2Wins;

LTexture gDraw;

LTexture gLeafTexture;

LTexture gSnowTexture;

LTexture gThreeTexture;

LTexture gTwoTexture;

LTexture gOneTexture;

LTexture MenuBackground;

LTexture gWinterBoard;

LTexture gAutumnBoard;

LTexture resumeButton;

//background game
LTexture gWinterBackground;

LTexture gAutumnBackground;

Tetris :: Tetris(int _level, Theme _theme)
:   animation()
{
    window = NULL;
    renderer = NULL;
    renderer = NULL;
    game = new Game(renderer, SinglePlay);
    menu = new Menu;
    battle = new Battle(renderer);
    vsCom = new Battle (renderer, Player1, Bot);
    level = _level;
    quit = false;
    ghostTetromino = true;
    setting = new Setting;
    theme = _theme;
    effect = None;
    for (int i = 0; i < MAX_ANIMATION; i++){
        animation[i].set_theme(_theme);
    }
}

Tetris :: ~Tetris()
{
    window = NULL;
    renderer = NULL;
    game = NULL;
    menu = NULL;
    setting = NULL;
}

bool Tetris :: init(const char *title, int x, int y, int w, int h)
{
    bool success = true;
    // initialize SDL subsystem
    if (SDL_Init(SDL_INIT_EVENTS | SDL_INIT_AUDIO) < 0)
    {
        cout << "failed to initialize sdl. SDL ERROR: " << SDL_GetError() << endl;
        success = false;
    }
    else
    {
        //create window
        window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            cout << "failed to create window. SDL ERROR: " << SDL_GetError() << endl;
            success = false;
        }
        else
        {
            //create renderer
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |  SDL_RENDERER_PRESENTVSYNC);//synchronize with screen
            //allow the rendering update with the same time the moniter update
            // allow screen not tear
            if (renderer == NULL)
            {
                cout << "failed to create renderer. SDL ERROR: " << SDL_GetError() << endl;
                success = false;
            }
            else
            {
                //set color for renderer
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

                //initialize PNG image loading
                int img_flag = IMG_INIT_PNG;
                if (!(IMG_Init(img_flag) & img_flag))
                {
                    cout << "failed to initialize img. SDL ERROR: " << SDL_GetError() << endl;
                    success = false;
                }

                //initialize SDL mixer
                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 3, 2048) < 0){
                    cout << "failed to initialize sdl mixed. ERROR: " << Mix_GetError() << endl;
                    success = false;
                }

                //initialize TTF
                if (TTF_Init() < 0){
                    cout << "failed to init true type font\n. ERROR: " << TTF_GetError() << endl;
                    success = false;
                }
            }
        }
    }
    return success;
}

bool Tetris :: load_texture(){
    bool success = true;
     //load background
    if (!gWinterBackground.loadFromFile(renderer, "Assets/Pictures/Winter.jpg", {150, 255, 255})){
        cout << "failed to load background";
        success = false;
    }

    if(!gAutumnBackground.loadFromFile(renderer, "Assets/Pictures/Autumn.png", {0, 255, 255})){
        cout << "failed to load autumn background\n";
        success = false;
    }

    //lose picture
    if(!gLoseBackground.loadFromFile(renderer, "Assets/Pictures/lose.jpg")){
        cout << "failed to load lose texture\n";
        success = false;
    }

    //replay button
    if(!gReplayButton.loadFromFile(renderer, "Assets/Pictures/replayButton.jpg")){
        cout << "failed to load button texture\n";
        success = false;
    }
    //home button
    if(!gHomeButton.loadFromFile(renderer, "Assets/Pictures/home.png")){
        cout << "failed to load home button\n";
        success = false;
    }
    if(!resumeButton.loadFromFile(renderer, "Assets/Pictures/resume.png")){
        cout << "failed to load resume button\n";
        success = false;
    }

    //load frame
    if(!gWellFrame.loadFromFile(renderer, "Assets/Pictures/frame.png"))
    {
        cout << "failed to load media\n";
        success = false;
    }
    if (!gScoreFrame.loadFromFile(renderer, "Assets/Pictures/score_frame.png")){
        cout << "failed to load score frame\n";
        success = false;
    }
    if(!gSnowTexture.loadFromFile(renderer, "Assets/Pictures/snow.png")){
        cout << "failed to load snow texture\n";
        success = false;
    }
    if (!gLeafTexture.loadFromFile(renderer, "Assets/Pictures/leaf.png", {255, 255, 255})){
        cout << "failed to load leaf texture\n";
        success = false;
    }
    if(!gThreeTexture.loadFromRenderedText(renderer, CountDownFont, "3", {255, 0, 0})){
        cout << "failed to load 3 texture";
        success = false;
    }
    if(!gTwoTexture.loadFromRenderedText(renderer, CountDownFont, "2", {0, 255, 0})){
        cout << "failed to load 2 texture";
        success = false;
    }
    if(!gOneTexture.loadFromRenderedText(renderer, CountDownFont, "1", {255, 255, 255})){
        cout << "failed to load 1 texture";
        success = false;
    }

    if(!gAutumnBoard.loadFromFile(renderer, "Assets/Pictures/autumn_board.jpg")){
        cout << "failed to load autumn board\n";
        success = false;
    }

    if(!gWinterBoard.loadFromFile(renderer, "Assets/Pictures/winter_board.jpg", {100, 200, 170})){
        cout << "failed to load winter board\n";
        success = false;
    }

    //load menu background
    if (!MenuBackground.loadFromFile(renderer, "Assets/Pictures/menu.png", {195, 195, 195})){
        cout << "failed to load menu background\n";
        success = false;
    }

    if(!battle->load_media(renderer)){
        cout << "failed to load battle texture\n";
    }
    //load menu media
    if(!menu->load_media(renderer)){
        cout << "failed to load menu media\n";
        success = false;
    }
    if(!setting->load_media(renderer)){
        cout << "failed to load setting media\n";
        success = false;
    }
    
    return success;
}

bool Tetris :: load_music(){
    bool success = true;

    //load music and sound effects
    gPlayingMusic = Mix_LoadMUS("Assets/Music/Music.mp3");
    if (gPlayingMusic == NULL){
        cout << "failed to load music\n";
        success = false;
    }
    gNiceSoundEffect = Mix_LoadWAV("Assets/Music/nice.mp3");
    if(gNiceSoundEffect == NULL){
        cout << "failed to load nice sound effects";
        success = false;
    }
    gLoseSoundEffect = Mix_LoadWAV("Assets/Music/oh_oh.mp3");
    if (gLoseSoundEffect == NULL){
        cout << "failed to load oh_oh sound effects";
        success = false;
    }
    gDropSoundEffect = Mix_LoadWAV("Assets/Music/drop.mp3");
    if (gDropSoundEffect == NULL){
        cout << "failed to laod drop sound effect\n";
        success = false;
    }
    return success;
}

bool Tetris :: load_font(){
    bool success = true;

    //load font
    ScoreFont = TTF_OpenFont("Assets/Font/montserrat/MontserratAlternates-Black.otf", 28);
    if (ScoreFont == NULL){
        cout << "failed to load font\n";
        success = false;
    }

    SettingFont = TTF_OpenFont("Assets/Font/Cormorant_Garamond/CormorantGaramond-Bold.ttf", 28);
    if (SettingFont == NULL){
        cout << "failed to load setting font\n" << TTF_GetError();
        success = false;
    }

    CountDownFont = TTF_OpenFont("Assets/Font/123_GO.ttf", 50);{
        if (CountDownFont == NULL){
            cout << "failed to load count down font\n" << TTF_GetError();
            success = false;
        }
    }
    return success;
}

bool Tetris :: load_media()
{
    bool success = true;

    if(!load_font()){
        cout << "failed to load font\n";
        success = false;
    }

    if(!load_texture()){
        cout << "failed to load texture\n";
        success = false;
    }
    
    if(!load_music()){
        cout << "failed to load music\n";
        success = false;
    }

    return success;
}

bool Tetris :: running()
{
    return !quit;
}

void Tetris :: play_music()
{
    if (!menu->get_active() && !setting->get_active()){
        //play music when starting playing game
        if(Mix_PlayingMusic() == 0){
            Mix_PlayMusic(gPlayingMusic, -1);
        }
    }
    else{
        if(Mix_PlayingMusic()){
            Mix_PlayMusic(gPlayingMusic, -1);
        }
    }
}

void Tetris :: handle_events()
{
    //event to be handled
    SDL_Event e;

    if (SDL_PollEvent(&e) != 0)
    {
        //if player quit the game
        if (e.type == SDL_QUIT){
            save_file();
            quit = true;
        }

        //handle menu
        if (menu->get_active()){
            this->menu_handle_event(e);
        }
        
        else if(setting->get_active()){
            this->setting_handle_event(e);
        }

        //if single play is running
        else if (game->running()){
            game->handleEvents(renderer, e);

            //if game is not running
            if(!game->running()){

                //menu is active
                menu->set_active();
                game = new Game (renderer);
            }
        }

        else if(vsCom->get_active()){
            vsCom->handle_event(renderer, e);
            //battle is running => menu
            if (!vsCom->get_active()){
                menu->set_active();
                vsCom = new Battle(renderer, Player1, Bot);
            }
        }

        //battle is running
        else {
            battle->handle_event(renderer, e);

            //battle is running => menu
            if (!battle->get_active()){
                menu->set_active();
                battle = new Battle(renderer);
            }
        }
    }
}

void Tetris :: set_animation_theme(){
    for (int i = 0; i < MAX_ANIMATION; i++){
        animation[i].set_theme(theme);
    }
}

void Tetris :: display()
{
    //clear screen
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    //show background
    if(theme == Autumn){
        gAutumnBackground.render(renderer, 0, 0);
    }
    else gWinterBackground.render(renderer, 0, 0);

    //show animation
    for (int i = 0; i < MAX_ANIMATION; i++){
        animation[i].render(renderer);
    }

    //if not play, show menu
    if (menu->get_active()){
        menu->display(renderer);
    }

    //show setting
    else if(setting->get_active()){
        setting->display(renderer, level, ghostTetromino, theme, effect);
    }

    //show game
    else if(game->running()) {
        if(!game->get_lose()){
            game->update();
        }
        game->display(renderer, theme);
    }

    //display vscom 
    else if (vsCom->get_active()){
        vsCom->display(renderer, theme);
    }

    //display battle
    else battle->display(renderer, theme);
    // gRedTexture.render(renderer, SCREEN_WIDTH / 2 + 50, SCREEN_HEIGHT / 2 + 50);
    //present into screen
    SDL_RenderPresent(renderer);
}

void Tetris :: free_texture(){
    //free score texture
    gWellFrame.free();
    gScoreFrame.free();

    gLoseBackground.free();

    //free button
    gReplayButton.free();
    gHomeButton.free();
    resumeButton.free();

    //free battle
    gPlayer1Wins.free();
    gPlayer2Wins.free();
    gDraw.free();

    //free background and animation
    gLeafTexture.free();
    gSnowTexture.free();
    MenuBackground.free();
    gWinterBackground.free();
    gAutumnBackground.free();


    //free preparation
    gThreeTexture.free();
    gTwoTexture.free();
    gOneTexture.free();

    //free board
    gWinterBoard.free();
    gAutumnBoard.free();

}

void Tetris :: free_music(){
    //free music
    gPlayingMusic = NULL;
    gNiceSoundEffect = NULL;
    gLoseSoundEffect = NULL;
    gDropSoundEffect = NULL;
    Mix_FreeMusic(gPlayingMusic);
    Mix_FreeChunk(gNiceSoundEffect);
    Mix_FreeChunk(gLoseSoundEffect);
    Mix_FreeChunk(gDropSoundEffect);
}

void Tetris :: free_font(){
    //free font
    ScoreFont = NULL;
    SettingFont = NULL;
    CountDownFont = NULL;
    TTF_CloseFont(ScoreFont);
    TTF_CloseFont(SettingFont);
    TTF_CloseFont(CountDownFont);
}

void Tetris :: free_memory(){
    free_texture();
    free_music();
    free_font();
}

void Tetris :: close_game(){
    free_memory();
    menu->free_memory();
    battle->free_memory();

    //destroy renderer and window
    SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );

    //quit sdl
	TTF_Quit();
	IMG_Quit();
	Mix_Quit();
	SDL_Quit();
}

void Tetris :: setting_handle_event(SDL_Event &e){
    setting->handle_event(e);
    //setting level, ghost piece,...
    if (setting->click_up_level_button(e)){
        if (level < MAX_LEVEL) level++;
    }
    else if (setting->click_down_level_button(e)){
        if(level > 1)   level--;
    }

    //return menu
    else if(setting->click_back_button(e)){
        menu->set_active();
    }

    //change ghost piece
    else if (setting->click_set_ghost_piece(e)){
        ghostTetromino =  !ghostTetromino;
    }

    //change theme
    else if(setting->click_change_theme(e)){
        if(theme == Winter){
            theme = Autumn;
        }
        else theme = Winter;
        for (int i = 0; i < MAX_ANIMATION; i++){
            animation[i].set_theme(theme);
        }
    }
    //change effect
    else if (setting->click_left_change_effect(e)){
        switch (effect)
        {
        case None:
            effect = Fade;
            break;
        case Capcut:
            effect = None;
            break;
        case Fade:
            effect = Capcut;
            break;
        }
    }
    else if (setting->click_right_change_effect(e)){
        switch (effect)
        {
        case None:
            effect = Capcut;
            break;
        case Capcut:
            effect = Fade;
            break;
        case Fade:
            effect = None;
            break;
        }
    }
}

void Tetris :: menu_handle_event(SDL_Event &e){
    //single play
    if(menu->click_play(e)){
        game->set_active(level, ghostTetromino, effect);
    }

    //ready to a hot battle
    else if(menu->click_battle(e)){
        battle->set_active(level, ghostTetromino, effect);
    }

    //bot is very intelligent
    else if (menu->click_vsCom(e)){
        vsCom->set_active(level, ghostTetromino, effect);
    }
    //click setting
    else if(menu->click_setting(e)){
        setting->set_active();
        menu->set_not_active();
    }
    //click "About"
    else if (menu->click_About(e)){
        SDL_OpenURL("https://github.com/nqghuy/Tetris");
    }
}

void Tetris :: load_file(){
    fstream saveFile("D:/Tetris/Tetris/Save.txt", ios :: in);

    //load theme
    string _theme;
    saveFile >> _theme;
    if (_theme == "Winter"){
        theme = Winter;
    }
    else {
        theme = Autumn;
    }
    //update animation theme
    set_animation_theme();

    saveFile.ignore();

    //load ghost tetromino
    string _ghostTetromino;

    saveFile >> _ghostTetromino;
    saveFile.ignore();

    if(_ghostTetromino == "True"){
        ghostTetromino = true;
    } 
    else ghostTetromino = false;

    //load level
    saveFile >> level;

    string _effect;

    //load effect
    saveFile >> _effect;
    if (_effect == "None"){
        effect = None;
    }
    else if (_effect == "Capcut"){
        effect = Capcut;
    }
    else if (_effect == "Fade"){
        effect = Fade;
    }

    //load state(menu, game, battle)
    string state;
    saveFile >> state;
    saveFile.ignore();
    if (state == "menu"){
        return;
    }
    else if (state == "game"){
        game->load_file(saveFile);
    }
    else if (state == "battle"){
        battle->load_file(saveFile);
    }
    saveFile.close();
}

void Tetris :: save_file(){
    //clear file before write
    fstream saveFile("D:/Tetris/Tetris/Save.txt", ios :: trunc | ios :: out);
    if (saveFile.fail()){
        cout << "cannot open file\n";
        return;
    }
    if (theme == Winter){
        saveFile << "Winter\n";
    }
    else if(theme == Autumn){
        saveFile << "Autumn\n";
    }
    else return;

    //save tetromino
    if (ghostTetromino){
        saveFile << "True\n";
    }
    else saveFile << "False\n";

    //save level
    saveFile << level << '\n';

    switch(effect){
        case None:
            saveFile << "None\n";
            break;
        case Capcut:
            saveFile << "Capcut\n";
            break;
        case Fade:
            saveFile << "Fade\n";
            break;
    }
    //save state
    if (menu->get_active() || setting->get_active()){
        saveFile << "menu\n";
    }
    else if (game->running()){
        saveFile << "game\n";
        game->save_file(saveFile);
    }
    else if (battle->get_active()){
        saveFile << "battle\n";
        battle->save_file(saveFile);
    }
    saveFile.close();

}