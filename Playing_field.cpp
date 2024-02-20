#include "Playing_field.h"
#include "Game.h"
#include <bits/stdc++.h>

Well :: Well (){
    memset(matrix, false, sizeof(matrix));
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 20; j++){
            cell_colors[i][j] = {0, 0, 0, 255};
        }
    }

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
            if (matrix[i][j]){
                SDL_Color curColor = cell_colors[i][j];
                SDL_SetRenderDrawColor(renderer, curColor.r, curColor. g, curColor.b, 255);
                SDL_Rect rect = {i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE};
                SDL_RenderFillRect(renderer, &rect);

                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderDrawRect(renderer, &rect);
            }
            else{
                SDL_RenderDrawPoint(renderer, i * TILE_SIZE + (SCREEN_WIDTH - width) / 2, j * TILE_SIZE + (SCREEN_HEIGHT - height) / 2);
            }
        }
    }
}

int Well :: get_x()
{
    return (SCREEN_WIDTH - width) / 2;
}

int Well :: get_y()
{
    return (SCREEN_HEIGHT - height) / 2;
}

int Well :: get_width()
{
    return this->get_x() + width;
}

int Well :: get_height()
{
    return this->get_y() + height;
}

