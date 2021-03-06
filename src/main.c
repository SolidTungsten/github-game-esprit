#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "image.h"
#include "button.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int BIT = 32;

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
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		printf("Could not load sound: %s\n", SDL_GetError());
		exit(4);
	}
}

SDL_Surface* set_screen()
{
	SDL_Surface* screen = NULL;
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, BIT, SDL_SWSURFACE);

	if (screen == NULL) {
		printf("Could not set screen: %s\n", SDL_GetError());
		exit(1);
	}

	return screen;
}

Mix_Music* load_music(const char* filename)
{
	Mix_Music* music = NULL;
	music = Mix_LoadMUS(filename);	// Load music from file

	if (music == NULL) {
		printf("Music failed to load. Error: %s\n", SDL_GetError());
		exit(1);
	}

	return music;
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
	
	SDL_Surface* screen = set_screen();
    SDL_WM_SetCaption("Menu", NULL);	// Set the window caption

	// struct image background = {"../../res/seaport.png", NULL, 0, 0};
	SDL_Surface* background = load_image("../../res/seaport.png");
		
	Mix_Music* music = load_music("../../res/Main Theme.mp3");

	apply_surface(background, NULL, screen, 0, 0);	// Apply image to screen

	// struct image icon = {"../../res/icons.png", NULL, 100, 100};
	SDL_Surface* icons = load_image("../../res/Buttons.png");	

	SDL_Rect clips[100];

	set_clips(clips);

	// Game loop:
	SDL_Event event;

	SDL_Rect* clip = clips;

	struct buttons PLAY_BUTTON;
	struct buttons OPTIONS_BUTTON;
	struct buttons EXIT_BUTTON;

	init_button(&PLAY_BUTTON, 218, 419, 105, 33); 
	init_button(&OPTIONS_BUTTON, 218, PLAY_BUTTON.y + PLAY_BUTTON.h + 33, 176, 33);
	init_button(&EXIT_BUTTON, 218, OPTIONS_BUTTON.y + OPTIONS_BUTTON.h + 33, 96, 33);

	// Set center positions	
	PLAY_BUTTON.x = PLAY_BUTTON.x - PLAY_BUTTON.w / 2;
	PLAY_BUTTON.y = PLAY_BUTTON.y - PLAY_BUTTON.h / 2;

	OPTIONS_BUTTON.x = OPTIONS_BUTTON.x - OPTIONS_BUTTON.w / 2;
	OPTIONS_BUTTON.y = OPTIONS_BUTTON.y - OPTIONS_BUTTON.h / 2;

	EXIT_BUTTON.x = EXIT_BUTTON.x - EXIT_BUTTON.w / 2;
	EXIT_BUTTON.y = EXIT_BUTTON.y - EXIT_BUTTON.h / 2;

	// init_button(&EXIT_BUTTON, 184, 6, 158, 67);

	// apply_surface(icons, &clip[0], screen, icon.x, icon.y);
	// apply_surface(icon.surface, &clips[3], screen, 184, 456);
	// EXIT_BUTTON.clip = &clips[EXIT_BUTTON_MOUSEOVER];
	// apply_surface(icon.surface, &clips[5], screen, EXIT_BUTTON.x, EXIT_BUTTON.y);

	int quit = 0;
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)	
				quit = 1;
			else {
				if (event.type == SDL_MOUSEMOTION) {	// Check mouse motion
					if (mouseover_BUTTON(PLAY_BUTTON))	// Play button
						PLAY_BUTTON.clip = &clips[PLAY_BUTTON_MOUSEOVER];
					else 
						PLAY_BUTTON.clip = &clips[PLAY_BUTTON_MOUSEOUT];
					
					if (mouseover_BUTTON(OPTIONS_BUTTON))
						OPTIONS_BUTTON.clip = &clips[OPTIONS_BUTTON_MOUSEOVER];
					else
						OPTIONS_BUTTON.clip = &clips[OPTIONS_BUTTON_MOUSEOUT];

					if (mouseover_BUTTON(EXIT_BUTTON))
						EXIT_BUTTON.clip = &clips[EXIT_BUTTON_MOUSEOVER];
					else
						EXIT_BUTTON.clip = &clips[EXIT_BUTTON_MOUSEOUT];

				}

				if (event.type == SDL_MOUSEBUTTONDOWN) {
					if (event.button.button == SDL_BUTTON_LEFT) {
						if (mouseover_BUTTON(PLAY_BUTTON));
							// PLAY_BUTTOOPTIONS_BUTTON.yN.clip = &clips[PLAY_BUTTON_MOUSEDOWN];
						
						else if (mouseover_BUTTON(EXIT_BUTTON)) {
							quit = 1;
						}	
					}
				}
			}

		}
		// if (message != NULL) {
		// 	apply_surface(background.surface, background.rect, screen, background.x, background.y);
		// 	apply_surface(message, NULL, screen, (SCREEN_WIDTH - message->w) / 2, (SCREEN_HEIGHT - message->h) / 2);			
		// 	message = NULL;
		// }
		if (Mix_PlayingMusic() == 0)
		if (Mix_PlayMusic(music, -1) == -1)	// Play music
			printf("Music failed to play. Error: %s\n", Mix_GetError());	

		apply_surface(icons, PLAY_BUTTON.clip, screen, PLAY_BUTTON.x, PLAY_BUTTON.y);
		apply_surface(icons, OPTIONS_BUTTON.clip, screen, OPTIONS_BUTTON.x, OPTIONS_BUTTON.y);
		apply_surface(icons, EXIT_BUTTON.clip, screen, EXIT_BUTTON.x, EXIT_BUTTON.y);

			
		// Update screen:
		if (SDL_Flip(screen) == -1) {
			printf("Screen failed to update. Error: %s\n", SDL_GetError());
			exit(1);
		}
	}

	SDL_FreeSurface(background);
	// SDL_FreeSurface(message);
	Mix_FreeMusic(music);
	// TTF_CloseFont(font);
	SDL_Quit();	
			
	return 0;
}

