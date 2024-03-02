#include "Tetris.h"

Mix_Music *gPlayingMusic;

Mix_Chunk *gNiceSoundEffect;

Mix_Chunk *gLoseSoundEffect;

TTF_Font *ScoreFont;

LTexture gWellFrame;

LTexture gScoreFrame;

Tetris :: Tetris()
{
    window = NULL;
    renderer = NULL;
    renderer = NULL;
    game = new Game(renderer);
    menu = new Menu;
    quit = false;
}

Tetris :: ~Tetris()
{
    window = NULL;
    renderer = NULL;
    game = NULL;
    menu = NULL;
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

bool Tetris :: load_media()
{
    bool success = true;

    //load background
    if (!background.loadFromFile(renderer, "Assets/Pictures/background4.png")){
        cout << "failed to load background";
        success = false;
    }

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

    //load font
    ScoreFont = TTF_OpenFont("Assets/Font/montserrat/MontserratAlternates-Black.otf", 28);
    if (ScoreFont == NULL){
        cout << "failed to load font\n";
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
    if(!menu->load_media(renderer)){
        cout << "failed to load menu media\n";
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

    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT){
            quit = true;
        }
        if (menu->get_active()){
            menu->handle_event(e);
        }
        else{
            game->handleEvents(renderer, e);
        }
    }
    if (!menu->get_active()){
        game->set_active();
    }
}

void Tetris :: display()
{
    //clear screen
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    background.render(renderer, 0, 0);
    if (menu->get_active()){
        menu->display(renderer);
    }
    else game->display(renderer);
    SDL_RenderPresent(renderer);
}



