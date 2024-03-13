#pragma once
#include "include/SDL2/SDL_mixer.h"
#include "include/SDL2/SDL_ttf.h"
#include "Texture.h"

//the size of a tile(block)
const int TILE_SIZE = 36;

//the number of wide cells
const int WIDE_CELLS = 10;

//the number of height cells
const int HEIGHT_CELLS = 22;

//the number of hidden rows
const int HIDDEN_ROWS = 2;

//screen dimensions
const int SCREEN_HEIGHT = 900;
const int SCREEN_WIDTH = 1520;

const int buttonDistance = 100;

//the number of tile in a tile shape matrix
const int TETRAD_SIZE = 4;

//music plays throughout the game
extern Mix_Music *gPlayingMusic;

//music plays when delete line(s)
extern Mix_Chunk *gNiceSoundEffect;

//music plays when lose
extern Mix_Chunk *gLoseSoundEffect;

//score font
extern TTF_Font *ScoreFont;

//brick well frame
extern LTexture gWellFrame;

//brick score frame
extern LTexture gScoreFrame;

//picture when lose
extern LTexture gLoseBackground;

//replay button
extern LTexture gReplayButton;

//home button
extern LTexture gHomeButton;

//appear when player 1 win
extern LTexture gPlayer1Wins;

//appear when player 2 win
extern LTexture gPlayer2Wins;

//appear when draw
extern LTexture gDraw;

enum GameMode{
     SinglePlay,
     Player1,
     Player2
};

