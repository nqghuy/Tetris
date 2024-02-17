#include "Playing_field.h"
#include "Game.h"
#include <bits/stdc++.h>

Well :: Well (){
    memset(matrix, false, sizeof(matrix));
};

void Well :: draw (SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Rect rect = {(SCREEN_WIDTH - width) / 2, (SCREEN_HEIGHT - height) / 2, width, height};

    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int i = 0; i < WIDE_CELLS; i++){
        for (int j = 0; j < HEIGHT_CELLS; j++){
            SDL_RenderDrawPoint(renderer, i * TILE_SIZE + (SCREEN_WIDTH - width) / 2, j * TILE_SIZE + (SCREEN_HEIGHT - height) / 2);
        }
    }
}
