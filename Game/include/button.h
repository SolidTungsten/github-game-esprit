#ifndef _BUTTON_H_
#define _BUTTON_H_

#define PLAY_BUTTON_MOUSEOUT 0
#define PLAY_BUTTON_MOUSEOVER 1
#define PLAY_BUTTON_MOUSEDOWN 2
#define OPTIONS_BUTTON_MOUSEOUT 3
#define OPTIONS_BUTTON_MOUSEOVER 4
#define OPTIONS_BUTTON_MOUSEDOWN 5
#define EXIT_BUTTON_MOUSEOUT 6
#define EXIT_BUTTON_MOUSEOVER 7
#define EXIT_BUTTON_MOUSEDOWN 8

struct buttons {
    SDL_Rect* clip;
    int x;
    int y;
    int w;
    int h;
};

void set_clips(SDL_Rect clips[]);
void init_button(struct buttons* button, int x, int y, int w, int h);
int mouseover_BUTTON(struct buttons button);

int mouseover_PLAY(int x, int y);
int mouseover_EXIT(int x, int y);

#endif