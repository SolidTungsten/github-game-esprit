#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "background.h"


int main (){
    //declaration
    Background b;




    //----------------------------------------------------------------------------------------------------------------
     SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    
    initback(&b);
    
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);
    SDL_Surface* screen;
    screen= SDL_SetVideoMode(1280,720,32,SDL_SWSURFACE);
    load(&b);

    Mix_PlayMusic(b.son, -1);
     aficherBack(b,screen);
    SDL_Delay(20000);
    



}