#pragma once
#include <SDL_mixer.h>
//the size of a tile(block)
const int TILE_SIZE = 36;

//the number of wide cells
const int WIDE_CELLS = 10;

//the number of height cells
const int HEIGHT_CELLS = 22;

//the number of hidden rows
const int HIDDEN_ROWS = 2;

//screen dimensions
const int SCREEN_HEIGHT = 860;
const int SCREEN_WIDTH = 1420;

//the number of tile in a tile shape matrix
const int TETRAD_SIZE = 4;

extern Mix_Music *gPlayingMusic;

extern Mix_Chunk *gNiceSoundEffect;

extern Mix_Chunk *gLoseSoundEffect;
