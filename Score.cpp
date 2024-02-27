#include "Score.h"
#include <string>
#include "Playing_field.h"
Score :: Score(SDL_Renderer *renderer)
{
    topScore = 0;
    currentScore = 0;
//    PromptCurrentScore.loadFromRenderedText(renderer, font, "SCORE", {0, 0, 0, 255});
//    PromptTopScore.loadFromRenderedText(renderer, font, "TOP SCORE", {0, 0, 0, 255});
//    currentScoreTexture.loadFromRenderedText(renderer, font, "0", {0, 255, 0, 255});
//    topScoreTexture.loadFromRenderedText(renderer, font, "0", {0, 255, 0, 255});
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
    if (!PromptCurrentScore.loadFromRenderedText(renderer, scoreFont, "SCORE", {0, 0, 0, 255}))
    {
        cout << "failed to load prompt current score\n";
    }
    if (!PromptTopScore.loadFromRenderedText(renderer, scoreFont, "TOP SCORE", {0, 0, 0, 255}))
    {
        cout << "failed to load prompt top score\n";
    }
    if(!currentScoreTexture.loadFromRenderedText(renderer, scoreFont, to_string(currentScore), {0, 255, 0, 255}))
    {
        cout << "failed to load current score texture\n";
    }

    if (!topScoreTexture.loadFromRenderedText(renderer, scoreFont, "0", {0, 255, 0, 255})){
        cout << "failed to load top score texture\n";
    }

    currentScoreTexture.loadFromRenderedText(renderer, scoreFont, to_string(currentScore), {0, 0, 0, 255});
    SDL_Rect topScoreRect = {well.get_x() + 500, well.get_y(), 300, 300};
    SDL_Rect currentScoreRect = {topScoreRect.x, topScoreRect.y + 300, 300, 300};

    cout << topScoreRect.x << " " << topScoreRect.y << " " << topScoreRect.w << " " << topScoreRect.h << "\n";

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(renderer, &topScoreRect);
    SDL_RenderFillRect(renderer, &currentScoreRect);

    SDL_SetRenderDrawColor(renderer, 0, 200, 0, 255);
    SDL_RenderDrawRect(renderer, &topScoreRect);
    SDL_RenderDrawRect(renderer, &currentScoreRect);

    PromptTopScore.render(renderer, topScoreRect.x + (topScoreRect.w - PromptTopScore.getWidth()) / 2, topScoreRect.y);
    PromptCurrentScore.render(renderer, currentScoreRect.x + (currentScoreRect.w - PromptCurrentScore.getWidth()) / 2, currentScoreRect.y);

    topScoreTexture.render(renderer, topScoreRect.x + (topScoreRect.w - PromptTopScore.getWidth()) / 2, topScoreRect.y + (topScoreRect.h - topScoreTexture.getHeight()) / 2) ;
    currentScoreTexture.render(renderer, currentScoreRect. x + (currentScoreRect.w - currentScoreTexture.getWidth()) / 2, currentScoreRect.y + (currentScoreRect.h - currentScoreTexture.getHeight()) / 2 );
}

Score :: ~Score()
{
    PromptCurrentScore.free();
    PromptTopScore.free();
    currentScoreTexture.free();
    topScoreTexture.free();
}


