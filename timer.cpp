#include "timer.h"
#include "include/SDL2/SDL.h"

LTimer :: LTimer(){
    mStartTicks = 0;
    mPauseTicks = 0;
    mStart = false;
    mPause = false;
}

int LTimer :: getTicks()
{
    //the actual timer time
    int time = 0;

    //if timer is not started or stopped
    if (!isStarted())
    {
        time = 0;
    }
    else if (isPaused())
    {
        time = mPauseTicks;
    }
    else time = SDL_GetTicks() - mStartTicks;
    return time;
}

bool LTimer :: isStarted()
{
    return mStart;
}

bool LTimer :: isPaused()
{
    return mPause;
}

void LTimer :: start(){
    //start the timer
    mStart = true;

    //unpause the timer
    mPause = false;

    //get the current clock time
    mStartTicks = SDL_GetTicks();
    mPauseTicks = 0;
}

void LTimer :: stop()
{
    //stop the timer
    mStart = false;

    //unpause the timer
    mPause = false;

    //clear tick variables
    mStartTicks = 0;
    mPauseTicks = 0;
}

void LTimer :: pause()
{
    //if the timer is running and unpaused
    if (isStarted() && !isPaused())
    {
        mPause = true;

        //stores ticks
        mPauseTicks = SDL_GetTicks() - mStartTicks;

        //reset the timer
        mStartTicks = 0;
    }
}

void LTimer :: unpause()
{
    if (isStarted() && isPaused())
    {
        mPause = false;

        mStartTicks = SDL_GetTicks() - mPauseTicks;

        mPauseTicks = 0;
    }
}