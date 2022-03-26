#include "framerate.h"
#include <SDL/SDL.h>
#include <stdbool.h>

void initTimer(struct Timer* timer)
{
    // Initialize the variables
    timer->startTicks = 0;
    timer->pausedTicks = 0;
    timer->paused = 0;
    timer->started = 0;
}

void startTimer(struct Timer* timer)
{
    //Start the timer
    timer->started = true;

    //Unpause the timer
    timer->paused = false;

    //Get the current clock time
    timer->startTicks = SDL_GetTicks();
}

void stopTimer(struct Timer* timer)
{
    //Stop the timer
    timer->started = false;

    //Unpause the timer
    timer->paused = false;
}

void pauseTimer(struct Timer* timer)
{
    //If the timer is running and isn't already paused
    if( ( timer->started == true ) && ( timer->paused == false ) )
    {
        //Pause the timer
        timer->paused = true;

        //Calculate the paused ticks
        timer->pausedTicks = SDL_GetTicks() - timer->startTicks;
    }
}

void unpauseTimer(struct Timer* timer)
{
    //If the timer is paused
    if( timer->paused == true )
    {
        //Unpause the timer
        timer->paused = false;

        //Reset the starting ticks
        timer->startTicks = SDL_GetTicks() - timer->pausedTicks;

        //Reset the paused ticks
        timer->pausedTicks = 0;
    }
}

int get_ticksTimer(struct Timer* timer)
{
    //If the timer is running
    if( timer->started == true )
    {
        //If the timer is paused
        if( timer->paused == true )
        {
            //Return the number of ticks when the timer was paused
            return timer->pausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            return SDL_GetTicks() - timer->startTicks;
        }
    }

    //If the timer isn't running
    return 0;
}

int is_startedTimer(struct Timer* timer)
{
    return timer->started;
}

int is_pausedTimer(struct Timer* timer)
{
    return timer->paused;
}