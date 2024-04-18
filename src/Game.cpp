#include "Game.h"
#include <iostream>
#include <algorithm>
using namespace std;

Game::Game(SDL_Renderer *renderer, GameMode _gameMode, int _level, bool _ghostTetromino, Effect _effect)
    :   //initialize well
    well((SCREEN_WIDTH - TILE_SIZE * WIDE_CELLS) / 2, (SCREEN_HEIGHT - TILE_SIZE * HEIGHT_CELLS) / 2, 0, _level),

      //initialize tetromino
    tetromino(Tetro_Type(rand() % 7), WIDE_CELLS / 2 - 1, 0, well, _gameMode), quit(true),
    nextTetromino(Tetro_Type(rand() % 7), WIDE_CELLS / 2 - 1, 0, well, _gameMode), lose(false)
      {
        mode = Normal;
        gameMode = _gameMode;
        level = _level;
        ghostTetromino = _ghostTetromino;
        moveTime = SDL_GetTicks();

        //set well corresponding to game mode
        if (_gameMode == Player1){
            well = Well(SCREEN_WIDTH / 11 , (SCREEN_HEIGHT - TILE_SIZE * HEIGHT_CELLS) / 2, 0, _level, _effect, mode);
        }
        else if (_gameMode == Player2 || _gameMode == Bot){
            well = Well(SCREEN_WIDTH / 11  * 6, (SCREEN_HEIGHT - TILE_SIZE * HEIGHT_CELLS) / 2, 0, _level, _effect, mode);
        }
        if(_gameMode == Bot){
            tetromino.greedy(well);
        }

        //random next tetro type
        nextTetromino = Tetromino(nextTetromino.get_random_type(tetromino), WIDE_CELLS / 2 - 1, 0, well, _gameMode, mode);

        //count down before play
        preparation = true;
        timer = SDL_GetTicks64();

        paused = false;
        effect = _effect;
}

Game :: ~Game(){}

bool Game :: running()
{
    return (!quit);
}

void Game :: reset(){
    moveTime = SDL_GetTicks();

    preparation = true;
    timer = SDL_GetTicks();

    //new top score
    int _topScore = max(well.get_current_score(), well.get_top_score());

    //reset well
    well = Well(well.get_x(), well.get_y(), _topScore, this->level, effect, mode);

    //reset tetromino
    tetromino = Tetromino(nextTetromino.get_tetro_type(), WIDE_CELLS / 2 - 1, 0, well, gameMode, mode);
    nextTetromino = Tetromino(nextTetromino.get_random_type(tetromino), WIDE_CELLS / 2 - 1, 0, well, gameMode, mode);
}

void Game :: handlePausedEvent(SDL_Event &e){
    //mouse position
    int x, y;
    SDL_GetMouseState(&x, &y);

    //resume button position
    int resumeButtonX = (SCREEN_WIDTH  - resumeButton.getWidth()) / 2;
    int resumeButtonY = (SCREEN_HEIGHT - resumeButton.getHeight()) / 2;
    
    //home button position
    int gHomeButtonX = (SCREEN_WIDTH - gHomeButton.getWidth()) / 2 - buttonDistance;
    int gHomeButtonY = (SCREEN_HEIGHT - gHomeButton.getHeight()) / 2;

    //replay button
    int gReplayButtonX = (SCREEN_WIDTH - gHomeButton.getWidth()) / 2 + buttonDistance;
    int gReplayButtonY = (SCREEN_HEIGHT - gHomeButton.getHeight()) / 2;


    //if click resume
    if (e.type == SDL_MOUSEBUTTONDOWN && x >= resumeButtonX && x <= resumeButtonX + resumeButton.getWidth() && y >= resumeButtonY && y <= resumeButtonY + resumeButton.getHeight()){
        moveTime = SDL_GetTicks();
        set_active(level, ghostTetromino, effect, mode);
        paused = false;
    }

    //click return home
    else if (e.type == SDL_MOUSEBUTTONDOWN && x >= gHomeButtonX && x <= gHomeButtonX + gHomeButton.getWidth() && y >= gHomeButtonY && y <= gHomeButtonY + gHomeButton.getHeight()){
        quit = true;
    }

    else if (e.type == SDL_MOUSEBUTTONDOWN && x >= gReplayButtonX && x <= gReplayButtonX + gReplayButton.getWidth() && y >= gReplayButtonY && y <= gReplayButtonY + gReplayButton.getHeight()){
        reset();
        paused = false;
    }
}

void Game :: handleEvents(SDL_Renderer *renderer, SDL_Event &e)
{   
    //if game is counting down, return
    if(preparation) return;

    //if player press p, pause game
    if(e.key.keysym.sym == SDLK_p){
        paused = true;
    }

    //handle paused event
    if (paused){
        handlePausedEvent(e);
        return;
    }
    //handle tetromino
    if (!get_lose()){
        if(tetromino.get_active() && !well.isDeletingLine()){
            if(gameMode != Bot){
                tetromino.handle_events(e, well, gameMode);
                tetromino.Move(well);
            }
        }
    }

    else{//if lose, press enter to reset game, get top score
        if (well.press_play_again(e)){
            reset();
        }
        //if click return home
        else if(well.return_home(e)){
            quit = true;
        }
    }
}

void Game :: update(){
    if (preparation) return;

    //current time
    int currentTime;

    //up level if get enough score
    if (level < MAX_LEVEL && this->get_current_score() > level * 1000){
        level++;
        well.set_level(level);
    }

    if (gameMode == Bot){
        tetromino.bot_move(well);
    }

    //after 1s, the tetromino will fall
    currentTime = SDL_GetTicks();

    //free fall
    if (currentTime > moveTime){
        if(!paused && !well.isDeletingLine()) tetromino.free_fall(well);
        if (level == 1){
            moveTime += 500;
        }
        else if (level == 2){
            moveTime += 300;
        }
        else{
            moveTime += 200;
        }
        if (well.get_speed_up()){
            moveTime -= (MAX_LEVEL - level) * 100;
        }
        else if (well.get_slow_down()){
            moveTime += level * 300;
        }
    }
    

    if (!tetromino.get_active()){
        //new tetrimino
        tetromino = Tetromino(nextTetromino.get_tetro_type(), WIDE_CELLS / 2 - 1, 0, well, gameMode, mode);
        tetromino.greedy(well);
        nextTetromino = Tetromino(nextTetromino.get_random_type(tetromino), WIDE_CELLS / 2 - 1, 0, well, gameMode, mode);

        //if lose game
        if (tetromino.check_bottom_collision(well)){
            well.set_lose();
        }

        //remove all events
        SDL_FlushEvents(SDL_USEREVENT, SDL_LASTEVENT);
    }
}

int Game :: get_current_score(){
    return well.get_current_score();
}

void Game :: display_paused_board(SDL_Renderer *renderer, Theme theme){
    //draw board by theme
    if (theme == Winter){
        gWinterBoard.render(renderer, (SCREEN_WIDTH - gWinterBoard.getWidth()) / 2, (SCREEN_HEIGHT - gWinterBoard.getHeight()) / 2);
    }
    else{
        gAutumnBoard.render(renderer, (SCREEN_WIDTH - gWinterBoard.getWidth()) / 2, (SCREEN_HEIGHT - gWinterBoard.getHeight()) / 2);
    }

    //draw resume button
    resumeButton.render(renderer, (SCREEN_WIDTH  - resumeButton.getWidth()) / 2 , (SCREEN_HEIGHT - resumeButton.getHeight()) / 2);

    //draw home button
    gHomeButton.render(renderer, (SCREEN_WIDTH - gHomeButton.getWidth()) / 2 - buttonDistance, (SCREEN_HEIGHT - gHomeButton.getHeight()) / 2);

    gReplayButton.render(renderer, (SCREEN_WIDTH - gHomeButton.getWidth()) / 2 + buttonDistance, (SCREEN_HEIGHT - gHomeButton.getHeight()) / 2);
}

void Game :: display(SDL_Renderer *renderer, Theme theme)
{
    //draw next tetromino
    gScoreFrame.render(renderer, well.get_right_border(), well.get_y() + TILE_SIZE + gScoreFrame.getHeight()* 2- TILE_SIZE * 2);
    nextTetromino.draw(renderer, well.get_right_border() + TILE_SIZE  * 2, well.get_y() + TILE_SIZE + gScoreFrame.getHeight()* 2);

    bool isDeleting = well.isDeletingLine();

    //draw well and tetromino
    well.draw(renderer, gameMode);

    if (isDeleting && !well.isDeletingLine() && gameMode == Bot){
        tetromino.greedy(well);
    }

    if(paused){
        display_paused_board(renderer, theme);
    }

    else if (!well.get_lose()){
        //draw ghost tetromino if ghost piece on
        if(ghostTetromino) tetromino.draw_ghost_tetromino(renderer, well);

        //draw tetromino
        tetromino.draw(renderer, well);
    }

    //render lose back ground if mode is single play
    //in battle, we have to wait two player finish their game
    else if (this->gameMode == SinglePlay){
        well.draw_lose_background(renderer);
    }

    //count down finish
    if (preparation && (SDL_GetTicks() - timer > 3000)){
        preparation = false;
        moveTime = SDL_GetTicks();
    }

    if (preparation){
        int countDownTime = 3000 - (SDL_GetTicks() - timer);
        if (countDownTime >= 2000){
            //draw 3
            gThreeTexture.render(renderer, well.get_x() + (well.get_width() - gThreeTexture.getWidth()) / 2 , well.get_y() + (well.get_height() - gThreeTexture.getHeight()) / 2 );
        }
            //2
        else if (countDownTime >= 1000){
            gTwoTexture.render(renderer, well.get_x() + (well.get_width() - gThreeTexture.getWidth()) / 2 , well.get_y() + (well.get_height() - gTwoTexture.getHeight()) / 2 );
        }
        else{
            //1
            gOneTexture.render(renderer, well.get_x() + (well.get_width() - gThreeTexture.getWidth()) / 2 , well.get_y() + (well.get_height() - gOneTexture.getHeight()) / 2 );
        }
    }
}

bool Game :: get_lose()
{
    return (well.get_lose());
}


void Game :: set_active(int _level, bool _ghostTetromino, Effect _effect, Mode _mode)
{   
    timer = SDL_GetTicks();
    preparation = true;

    level = _level;
    ghostTetromino = _ghostTetromino;
    mode = _mode;

    well.set_level(_level);
    effect = _effect;
    
    well.set_effect(_effect);
    well.set_mode(_mode);
    tetromino.set_mode(mode);
    nextTetromino.set_mode(mode);
    
    //ready to play
    quit = false;
}

void Game :: set_time(){
    moveTime = SDL_GetTicks();
}

void Game :: load_file(fstream &saveFile){
    tetromino.load_file(saveFile);
    nextTetromino.load_file(saveFile);
    well.load_file(saveFile);
}

void Game :: save_file(fstream &saveFile){
    tetromino.save_file(saveFile);
    nextTetromino.save_file(saveFile);
    well.save_file(saveFile);
}