#include "Playing_field.h"
#include "Game.h"

Well :: Well (){};

void Well :: draw (SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Rect rect = {(SCREEN_WIDTH - width) / 2, (SCREEN_HEIGHT - height) / 2, width, height};
    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int i = 0; i < SCREEN_WIDTH - width; i++){
        for (int j = 0; j < SCREEN_HEIGHT - height; j++){
            SDL_RenderDrawPoint(renderer, i * blockDimension, j * blockDimension);
        }
    }
}
