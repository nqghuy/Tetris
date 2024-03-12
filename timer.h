#pragma once
class LTimer{
private:
    //the clock time when timer starts
    int mStartTicks;

    //the ticks stored when timer is paused
    int mPauseTicks;

    //clock status
    bool mStart;
    bool mPause;

public:
    //the various clock actions
    void start();
    void stop();
    void pause();
    void unpause();

    //constructor
    LTimer();

    //get the timer ticks
    int getTicks();

    //check the status of timer
    bool isPaused();
    bool isStarted();
};