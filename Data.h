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

//the distance between 2 button
const int buttonDistance = 100;

//max_level
const int MAX_LEVEL = 6;

const double PI = 3.14159265;

//the number of tile in a tile shape matrix
const int TETRAD_SIZE = 4;

//music plays throughout the game
extern Mix_Music *gPlayingMusic;

//music plays when delete line(s)
extern Mix_Chunk *gNiceSoundEffect;

//music plays when lose
extern Mix_Chunk *gLoseSoundEffect;

//sound effect when drop a tetromino
extern Mix_Chunk *gDropSoundEffect;

//score font
extern TTF_Font *ScoreFont;

//font in setting
extern TTF_Font *SettingFont;

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

//animation texture
extern LTexture gLeafTexture;

extern LTexture gSnowTexture;




enum GameMode{
     SinglePlay,
     Player1,
     Player2
};

//ascending level text 
const string LevelText[MAX_LEVEL] = {"EASY", "MEDIUM", "HARD", "ULTRA HARD", "ASIAN", "BLACK PEOPLE"};

//ascending level color
const SDL_Color LevelColor[MAX_LEVEL] = {{255, 255, 255}, {150,100, 200}, {100, 135, 237}, {177, 135, 85}, {255, 0, 0}, {0, 0, 0}};
