#include "Tetris.h"

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
    level = _level;
    quit = false;
    ghostTetromino = true;
    setting = new Setting;
    theme = _theme;
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
                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
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

    if(!gAutumnBackground.loadFromFile(renderer, "Assets/Pictures/Autumn.png")){
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
    if (!gLeafTexture.loadFromFile(renderer, "Assets/Pictures/leaf.png")){
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

    if(!gWinterBoard.loadFromFile(renderer, "Assets/Pictures/winter_board.jpg", {195, 195, 195})){
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
    if (!menu->get_active()){
        game->play_music();
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

    for (int i = 0; i < MAX_ANIMATION; i++){
        animation[i].render(renderer);
    }

    //if not play, show menu
    if (menu->get_active()){
        menu->display(renderer, level, ghostTetromino);
    }

    else if(setting->get_active()){
        setting->display(renderer, level, ghostTetromino, theme);
    }

    //else show game
    else if(game->running()) {
        if(!game->get_lose()){
            game->update();
        }
        game->display(renderer, theme);
    }

    //display battle
    else battle->display(renderer, theme);
    // gRedTexture.render(renderer, SCREEN_WIDTH / 2 + 50, SCREEN_HEIGHT / 2 + 50);
    //present into screen
    SDL_RenderPresent(renderer);
}

void Tetris :: close_game(){
    //free music
    gPlayingMusic = NULL;
    gNiceSoundEffect = NULL;
    gLoseSoundEffect = NULL;
    Mix_FreeMusic(gPlayingMusic);
    Mix_FreeChunk(gNiceSoundEffect);
    Mix_FreeChunk(gLoseSoundEffect);

    //free font
    ScoreFont = NULL;
    TTF_CloseFont(ScoreFont);

    //free texture
    gWellFrame.free();
    gScoreFrame.free();
    gLoseBackground.free();
    gReplayButton.free();
    gPlayer1Wins.free();
    gPlayer2Wins.free();
    gDraw.free();

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
    //setting level, ghost piece,...
    if (setting->click_up_level_button(e)){
        if (level < MAX_LEVEL) level++;
    }
    else if (setting->click_down_level_button(e)){
        if(level > 1)   level--;
    }
    else if(setting->click_back_button(e)){
        menu->set_active();
    }
    else if (setting->click_set_ghost_piece(e)){
        ghostTetromino =  !ghostTetromino;
    }
    else if(setting->click_change_theme(e)){
        if(theme == Winter){
            theme = Autumn;
        }
        else theme = Winter;
        for (int i = 0; i < MAX_ANIMATION; i++){
            animation[i].set_theme(theme);
        }
    }
}

void Tetris :: menu_handle_event(SDL_Event &e){
    //single play
    if(menu->click_play(e)){
        game->set_active(level, ghostTetromino);
    }
    //ready to a hot battle
    else if(menu->click_battle(e)){
        battle->set_active(level, ghostTetromino);
    }
    //click setting
    else if(menu->click_setting(e)){
        setting->set_active();
        menu->set_not_active();
    }
}