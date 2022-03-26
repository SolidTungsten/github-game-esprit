#ifndef FRAMERATE_H
#define FRAMERATE_H

#define FRAMES_PER_SECOND 60

struct Timer {
    int startTicks;
    int pausedTicks;
    int paused;
    int started;
};

void initTimer(struct Timer* timer);
void startTimer(struct Timer* timer);
void stopTimer(struct Timer* timer);
void pauseTimer(struct Timer* timer);
void unpauseTimer(struct Timer* timer);
int get_ticksTimer(struct Timer* timer);
int is_startedTimer(struct Timer* timer);
int is_pausedTimer(struct Timer* timer);


#endif