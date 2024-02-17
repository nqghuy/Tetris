#include "Game.h"
#include "Playing_field.h"
#include  "Tetromino.h"

game :: game()
{
    window = NULL;
    renderer = NULL;
    quit = false;
}

game :: ~game()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
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

bool game :: running()
{
    return (!quit);
}

void game :: handleEvents()
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT){
            quit = true;
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        Well well;
        well.draw(renderer);

        tetromino tmp;
        tmp.draw(renderer);

        SDL_RenderPresent(renderer);
    }
}

void game :: close_game()
{
    SDL_Quit();
    TTF_Quit();
    IMG_Quit();
}
