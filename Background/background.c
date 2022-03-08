#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "background.h"

void initback(Background* b){
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    b->image=NULL;
    b->son=NULL;
}

void load(Background* b){
    b->image= IMG_Load("resources/seaport.png");
    b->son = Mix_LoadMUS("resources/mainTheme.mp3");
}

void aficherBack(Background b, SDL_Surface * screen){



    SDL_Rect offset;
        offset.x=0;
        offset.y=0;

    SDL_BlitSurface(b.image,NULL,screen,&offset);
    SDL_Flip(screen);

}