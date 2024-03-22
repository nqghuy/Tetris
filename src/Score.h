#pragma once
#include "Texture.h"

class Well;
class Score
{
public:
    //constructor
    Score(SDL_Renderer *renderer, int topScore);

    //destructor
    ~Score();

    //change current score
    void set_score(int addScore);

    //change top score
    void set_top_score(int newTopScore);

    //set current score to load file
    void set_current_score(int _currentScore);

    //draw score frame and contents
    void draw(SDL_Renderer *renderer, Well &well, TTF_Font *scoreFont);

    //get top score
    int get_top_score();

    //get current score
    int get_current_score();
private:
    //brick score frame texture
    LTexture scoreFrame;

    //"Score"
    LTexture PromptCurrentScore;

    //"TOP SCORE"
    LTexture PromptTopScore;

    //score texture
    LTexture currentScoreTexture;
    LTexture topScoreTexture;

    //score
    int topScore;
    int currentScore;
};


