#include "Game.h"
#include <iostream>
using namespace std;
Mix_Music *gPlayingMusic;

Mix_Chunk *gNiceSoundEffect;

Mix_Chunk *gLoseSoundEffect;

TTF_Font *ScoreFont;

game::game()
    : well(renderer, (SCREEN_WIDTH - TILE_SIZE * WIDE_CELLS) / 2, (SCREEN_HEIGHT - TILE_SIZE * HEIGHT_CELLS) / 2),
      tetromino(Tetro_Type(rand() % 7), WIDE_CELLS / 2, 0),
      window(nullptr),
      renderer(nullptr),
      quit(false){
}


game :: ~game()
{

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    window = NULL;
    renderer = NULL;
}

bool game :: init(const char *title, int x, int y, int w, int h)
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

bool game :: loadMedia()
{
    bool success = true;
    if (!background.loadFromFile(renderer, "Assets/Pictures/background4.png")){
        cout << "failed to load background";
        success = false;
    }
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
    ScoreFont = TTF_OpenFont("Assets/Font/montserrat/MontserratAlternates-Black.otf", 28);
    if (ScoreFont == NULL){
        cout << "failed to load font\n";
    }
    return success;
}

bool game :: running()
{
    return (!quit);
}

void game :: handleEvents()
{
    //event to be handled
    SDL_Event e;

    //current time
    int currentTime;

    //after 1s, the tetromino will fall
    static int moveTime = SDL_GetTicks();
    currentTime = SDL_GetTicks();
        if (currentTime > moveTime){
            moveTime += 1000;
            tetromino.free_fall(well);
        }
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT){
            quit = true;
        }
        //handle tetromino
        if (!is_paused()){
            if(tetromino.get_active()){
                tetromino.handle_events(e, well);
                tetromino.Move(well);
            }
        }
        else{
            if (e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.sym == SDLK_RETURN){
                well = Well(renderer, (SCREEN_WIDTH - TILE_SIZE * WIDE_CELLS) / 2, (SCREEN_HEIGHT - TILE_SIZE * HEIGHT_CELLS) / 2);
                tetromino = Tetromino(tetromino.get_random_type(), WIDE_CELLS / 2, 0);
            }
        }
    }

    display();
    if (!is_paused()){
        if (!tetromino.get_active()){
            tetromino = Tetromino(tetromino.get_random_type(), WIDE_CELLS / 2, 0);
            moveTime += 1000;
            if (tetromino.check_bottom_collision(well)){
                well.set_lose();
                Mix_PlayChannel(-1, gLoseSoundEffect, 0);
            }
            SDL_FlushEvents(SDL_USEREVENT, SDL_LASTEVENT);
        }

    }
}

void game :: play_music()
{
    if(Mix_PlayingMusic() == 0){
        Mix_PlayMusic(gPlayingMusic, -1);
    }
}

void game :: close_game()
{
    background.free();
    SDL_Quit();
    TTF_Quit();
    IMG_Quit();
}

void game :: display()
{
    //clear screen
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    background.render(renderer, 0, 0);

    //draw well and tetromino
    well.draw(renderer);

    if (!well.get_lose()){
        tetromino.draw(renderer, well);
    }

    //display on the screen
    SDL_RenderPresent(renderer);
}

bool game :: is_paused()
{
    return (well.get_lose());
}
