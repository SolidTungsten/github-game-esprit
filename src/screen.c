#include "screen.h"

SDL_Surface* setScreen()
{
	SDL_Surface* screen = NULL;
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, BIT, SDL_SWSURFACE);

	if (screen == NULL) {
		printf("Could not set screen: %s\n", SDL_GetError());
		exit(1);
	}

	return screen;
}

// TODO
SDL_Surface* toggleWindowFullscreen()
{
    SDL_Surface* screen = NULL;
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, BIT, SDL_SWSURFACE | SDL_FULLSCREEN);

	if (screen == NULL) {
		printf("Could not set screen: %s\n", SDL_GetError());
		exit(1);
	}

	return screen;
}
