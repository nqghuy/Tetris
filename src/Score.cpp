#include "Score.h"
#include <string>
#include "Playing_field.h"

Score :: Score(SDL_Renderer *renderer, int _topScore)
{
    topScore = _topScore;
    currentScore = 0;
}

void Score :: set_score(int addScore)
{
    currentScore += addScore;
}

void Score :: set_top_score(int newTopScore)
{
    topScore = max(topScore, newTopScore);
}

void Score :: draw(SDL_Renderer *renderer, Well &well, TTF_Font *scoreFont)
{
    //load texture
    if (!PromptCurrentScore.loadFromRenderedText(renderer, scoreFont, "SCORE", {255, 255, 255, 255}))
    {
        cout << "failed to load prompt current score\n";
    }
    if (!PromptTopScore.loadFromRenderedText(renderer, scoreFont, "TOP SCORE", {255, 255, 255, 255}))
    {
        cout << "failed to load prompt top score\n";
    }
    if(!currentScoreTexture.loadFromRenderedText(renderer, scoreFont, to_string(currentScore), {255, 255, 255, 255}))
    {
        cout << "failed to load current score texture\n";
    }

    if (!topScoreTexture.loadFromRenderedText(renderer, scoreFont, to_string(topScore), {255, 255, 255, 255})){
        cout << "failed to load top score texture\n";
    }

    //draw top score frame
    scoreFrame = gScoreFrame;

    //minimal the code
    int x = well.get_right_border();
    int y = well.get_y() + TILE_SIZE;

    //draw frame
    scoreFrame.render(renderer, x, y);

    //draw "TOP SCORE" and top score num
    PromptTopScore.render(renderer, x + (scoreFrame.getWidth() - PromptTopScore.getWidth()) / 2, y + TILE_SIZE);
    topScoreTexture.render(renderer, x + (scoreFrame.getWidth() - topScoreTexture.getWidth()) / 2, y + (scoreFrame.getHeight() - topScoreTexture.getHeight())/ 2);


    //set position for current score texture
    y += scoreFrame.getHeight()- TILE_SIZE;

    //draw current score frame
    scoreFrame.render(renderer, x, y);

    //draw "SCORE" and current score texture
    PromptCurrentScore.render(renderer, x + (scoreFrame.getWidth() - PromptCurrentScore.getWidth()) / 2, y + TILE_SIZE);
    currentScoreTexture.render(renderer, x + (scoreFrame.getWidth() - currentScoreTexture.getWidth()) / 2, y + (scoreFrame.getHeight() - currentScoreTexture.getHeight())/ 2);

}

Score :: ~Score()
{
    //free memory
    scoreFrame.free();
    PromptCurrentScore.free();
    PromptTopScore.free();
    currentScoreTexture.free();
    topScoreTexture.free();
}

int Score :: get_top_score()
{
    return topScore;
}

int Score :: get_current_score()
{
    return currentScore;
}

void Score :: set_current_score(int _currentScore){
    currentScore = _currentScore;
}

