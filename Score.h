#pragma once
#include "Texture.h"

class Well;
class Score
{
public:
    Score(SDL_Renderer *renderer);
    ~Score();
    void set_score(int addScore);
    void set_top_score(int newTopScore);
    void draw(SDL_Renderer *renderer, Well &well, TTF_Font *scoreFont);
private:
    LTexture PromptCurrentScore;
    LTexture PromptTopScore;
    LTexture currentScoreTexture;
    LTexture topScoreTexture;
    int topScore;
    int currentScore;
};


