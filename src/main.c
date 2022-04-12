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

TTF_Font* load_font(const char* filename, int size)
{
	// Font stuff:
	TTF_Font* font = NULL;
	font = TTF_OpenFont(filename, size);

	if (font == NULL) {
		printf("Font failed to load. Error: %s\n", TTF_GetError());
		exit(1);
	}

	return font;
}

SDL_Surface* render_text(TTF_Font* font, const char* text, Uint8 r, Uint8 g, Uint8 b)
{
	SDL_Surface* message = NULL;
	SDL_Color color = {r, g, b};
	
	message = TTF_RenderText_Solid(font, text, color);
	if (message == NULL) {
		printf("text failed to render. Error: %s\n", TTF_GetError());
	}

	return message;
}

int main(int argc, char* args[])
{
	init_all();
	
	SDL_Surface* screen = setScreen();
    SDL_WM_SetCaption("Game", NULL);	// Set the window caption

	TTF_Font* font = NULL;
	SDL_Surface* message = NULL;
	font = load_font("../../res/pixelmix.ttf", 28);
	char str[2];
	int score = 0;
	sprintf(str, "%d", score);
	message = render_text(font, str, 255, 255, 255);

	// Game loop:
	SDL_Event event;
	struct Timer fps;	// Animation (TODO)

	SDL_Flip(screen);

	int x_vel = 0;
	Perso p;
	initialiserPerso(&p);

	Uint32 t_prev = 0, dt = 0;	// Initialize timers
	t_prev = SDL_GetTicks();

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
		saut(&p, event);
		deplacerPerso(&p, dt, event);
		afficherPerso(p, screen);
		animerPerso(&p);
		printf("%lf %.2f %.2f %d %d %lf %d %p\n", p.acceleration, p.x, p.y, dt, p.keydown, p.vitesse, p.state, p.clip);
		apply_surface(message, NULL, screen, 0, 0);

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

