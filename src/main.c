#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "image.h"
#include "screen.h"
#include "framerate.h"
#include "perso.h"

void init_all()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {	// Initialize SDL
		printf("SDL could not initialize: %s\n", SDL_GetError());
		exit(1);
	}

	if (TTF_Init() == -1) {	// Check font
		printf("Could not initialize font. Error: %s\n", TTF_GetError());
		exit(1);
	}

	// Initialize SDL_mixer:
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		printf("Could not load sound: %s\n", SDL_GetError());
		exit(4);
	}
}

int main(int argc, char* args[])
{
	init_all();
	
	SDL_Surface* screen = setScreen();
    SDL_WM_SetCaption("Game", NULL);	// Set the window caption

	// Game loop:
	SDL_Event event, input_manager;
	struct Timer fps;	// Animation (TODO)

	SDL_Flip(screen);

	int x_vel = 0;
	Perso p;
	Uint32 t_prev = 0, dt = 0;	// Initialize timers
	t_prev = SDL_GetTicks();

	initialiserPerso(&p);
	int quit = 0;
	while (!quit) {
		startTimer(&fps);	// Start fps timer

		if ((p.acceleration < 0.001) && (p.acceleration > -0.001)) {
			t_prev = SDL_GetTicks();	// Reset timer when acceleration reaches 0
			dt = 0;
		}

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) 
				quit = 1;
		}

		SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));	// Fill screen black
		deplacerPerso(&p, dt, event);
		afficherPerso(p, screen);
		printf("%lf %d %d\n", p.acceleration, p.x, dt);

		// Update screen:
		if (SDL_Flip(screen) == -1) {
			printf("Screen failed to update. Error: %s\n", SDL_GetError());
			exit(1);
		}
		

		//Cap the frame rate
        if( get_ticksTimer(&fps) < 1000 / FRAMES_PER_SECOND )
        {
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - get_ticksTimer(&fps) );
        }

		dt = SDL_GetTicks() - t_prev;
	}

	SDL_Quit();	
			
	return 0;
}

