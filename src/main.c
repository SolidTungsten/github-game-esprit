#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "image.h"
#include "button.h"
#include "screen.h"
#include "framerate.h"

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
	
	SDL_Surface* screen = setScreen();
    SDL_WM_SetCaption("Menu", NULL);	// Set the window caption

	SDL_Surface* background = load_image("../../res/seaport.png");
	SDL_Surface* icons = load_image("../../res/Buttons.png");
	SDL_Surface* cursor_image = load_image("../../res/Cursor_Sword.png");
		
	Mix_Music* music = load_music("../../res/mainTheme.mp3");

	apply_surface(background, NULL, screen, 0, 0);	// Apply image to screen

	SDL_ShowCursor(SDL_ENABLE);


	SDL_Rect clips[100];

	set_clips(clips);

	// Game loop:
	SDL_Event event;

	SDL_Rect* clip = clips;

	struct buttons PLAY_BUTTON;
	struct buttons OPTIONS_BUTTON;
	struct buttons EXIT_BUTTON;

	init_button(&PLAY_BUTTON, 218, 419, 76, 22); 
	init_button(&OPTIONS_BUTTON, 218, PLAY_BUTTON.y + PLAY_BUTTON.h + 22, 136, 22);
	init_button(&EXIT_BUTTON, 218, OPTIONS_BUTTON.y + OPTIONS_BUTTON.h + 22, 74, 22);

	// Set center positions	
	PLAY_BUTTON.x = PLAY_BUTTON.x - PLAY_BUTTON.w / 2;
	PLAY_BUTTON.y = PLAY_BUTTON.y - PLAY_BUTTON.h / 2;

	OPTIONS_BUTTON.x = OPTIONS_BUTTON.x - OPTIONS_BUTTON.w / 2;
	OPTIONS_BUTTON.y = OPTIONS_BUTTON.y - OPTIONS_BUTTON.h / 2;

	EXIT_BUTTON.x = EXIT_BUTTON.x - EXIT_BUTTON.w / 2;
	EXIT_BUTTON.y = EXIT_BUTTON.y - EXIT_BUTTON.h / 2;

	SDL_Rect* options_holder = NULL;
	SDL_Rect options;
	options.x = 345;
	options.y = 0;
	options.w = 508;
	options.h = 349;
	int options_holder_x = (SCREEN_WIDTH - options.w) / 2;
	int options_holder_y = (SCREEN_HEIGHT - options.h) / 2;
	int cursor_x = 0;
	int cursor_y = 0;

	// Animation:
	struct Timer fps;
	struct Timer delta;
	struct Timer delta2;
	startTimer(&delta);
	startTimer(&delta2);

	unsigned int frame = 0;
	unsigned int frame2 = 1;

	SDL_Rect seagull[2];
	seagull[0].x = 0;
	seagull[0].y = 139;
	seagull[0].w = 25;
	seagull[0].h = 24;
	seagull[1].x = 25;
	seagull[1].y = 139;
	seagull[1].w = 25;
	seagull[1].h = 24;

	SDL_Rect flag[6];
	int flag_w = 120;
	int flag_frame = 0;
	flag[0].x = 0;
	flag[0].y = 366;
	flag[0].w = 120;
	flag[0].h = 50;

	flag[1].x = 119;
	flag[1].y = 366;
	flag[1].w = 120;
	flag[1].h = 50;

	flag[2].x = 247;
	flag[2].y = 366;
	flag[2].w = 120;
	flag[2].h = 50;

	flag[3].x = 382;
	flag[3].y = 366;
	flag[3].w = 120;
	flag[3].h = 50;

	flag[4].x = 634;
	flag[4].y = 366;
	flag[4].w = 120;
	flag[4].h = 50;

	SDL_Rect volume_bump[1];
	volume_bump[0].x = 0;
	volume_bump[0].y = 165;
	volume_bump[0].w = 31;
	volume_bump[0].h = 27;
	
	
	Mix_Chunk* chunk_test = NULL;
	chunk_test = Mix_LoadWAV("../../res/Menu_Tick.wav");

	if (chunk_test == NULL) {
		printf("Chunk failed to load. Error: %s\n", SDL_GetError());
		exit(1);
	}

	if (Mix_PlayMusic(music, -1) == -1)	// Play music
			printf("Music failed to play. Error: %s\n", Mix_GetError());

	int check = 0; int repeatonce = 1;
	int quit = 0;
	int windowed = 0;
	int options_show = 0;
	while (!quit) {
		startTimer(&fps);	// Start the timer

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)	
				quit = 1;
			else {
				if (event.type == SDL_MOUSEMOTION) {	// Check mouse motion
					if (mouseover_BUTTON(PLAY_BUTTON)) {	// Play button
						PLAY_BUTTON.clip = &clips[PLAY_BUTTON_MOUSEOVER];
						if (check == 0) {
							check = 1;
						}
					}
					else {
						PLAY_BUTTON.clip = &clips[PLAY_BUTTON_MOUSEOUT];
						check = 0;
						repeatonce = 1;
					}
					
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
						int x, y;
						SDL_GetMouseState(&x, &y);

						cursor_x = x;
						cursor_y = y;

						if (mouseover_BUTTON(PLAY_BUTTON));
							// TODO
						
						if (mouseover_BUTTON(OPTIONS_BUTTON)) {
							SDL_Delay(300);
							options_holder = &options;
							options_show = 1;
						}

						if ((x > 407) && (x < 407 + 26) && (y > 197) && (y < 197 + 18)) {	// OPTIONS button
							SDL_Delay(300);
							options_show = 0;
						}
						
						if ((x > options_holder_x+40) && (x < options_holder_x+40+volume_bump->w) &&
							(y > options_holder_y+97) && (y < options_holder_y+97+volume_bump->h)) {

							Mix_VolumeMusic(Mix_VolumeMusic(-1) - MIX_MAX_VOLUME/9);
						}
						else if (((x > options_holder_x+418) && (x < options_holder_x+418+volume_bump->w) &&
								(y > options_holder_y+97) && (y < options_holder_y+97+volume_bump->h))) {

							Mix_VolumeMusic(Mix_VolumeMusic(-1) + MIX_MAX_VOLUME/9);
						}

						if (mouseover_BUTTON(EXIT_BUTTON)) {
							quit = 1;
						}

					}
				}

				if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_f)) {
					if (windowed) {
						screen = toggleWindowFullscreen();
						windowed = 0;
					}
					else {
						screen = setScreen();
						windowed = 1;
					}
				}

				if ((event.type == SDL_KEYDOWN)) {
					if (event.key.keysym.sym == SDLK_0) 
						Mix_VolumeMusic(Mix_VolumeMusic(-1) + MIX_MAX_VOLUME/9);
					
					else if (event.key.keysym.sym == SDLK_9) 
						Mix_VolumeMusic(Mix_VolumeMusic(-1) - MIX_MAX_VOLUME/9);
				}

				if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_ESCAPE))
					quit = 1;

				// if (event.type == SDL_VIDEORESIZE) {
				// 	// Resize the screen
				// 	screen = SDL_SetVideoMode(event.resize.w, event.resize.h, BIT, SDL_SWSURFACE | SDL_RESIZABLE);
				// }
			}

		}
		// if (message != NULL) {
		// 	apply_surface(background.surface, background.rect, screen, background.x, background.y);
		// 	apply_surface(message, NULL, screen, (SCREEN_WIDTH - message->w) / 2, (SCREEN_HEIGHT - message->h) / 2);			
		// 	message = NULL;
		// }
		
		
		Mix_AllocateChannels(16);
		// if (Mix_PlayingMusic() == 0)
		if (Mix_PlayMusic(music, -1) == -1)	// Play music
			printf("Music failed to play. Error: %s\n", Mix_GetError());	

		if (check == 1 && repeatonce == 1) {
			if (Mix_PlayChannel(-1, chunk_test, 0) == -1) 
				printf("Chunk failed to play. Error: %s\n", SDL_GetError());
			repeatonce = 0;
		}

		if (get_ticksTimer(&delta2) > 200) {
			++flag_frame;
			startTimer(&delta2);
		}

		if (get_ticksTimer(&delta) > 500) {
			++frame;
			++frame2;
			startTimer(&delta);	// Reset timer
		}

		if (frame > 1)
			frame = 0;
		if (frame2 > 1)
			frame2 = 0;
		if (flag_frame > 4)
			flag_frame = 0;

		if (SDL_ShowCursor(SDL_QUERY) == SDL_ENABLE)
			SDL_ShowCursor(SDL_DISABLE);

		apply_surface(background, NULL, screen, 0, 0);
		apply_surface(icons, PLAY_BUTTON.clip, screen, PLAY_BUTTON.x, PLAY_BUTTON.y);
		apply_surface(icons, OPTIONS_BUTTON.clip, screen, OPTIONS_BUTTON.x, OPTIONS_BUTTON.y);
		apply_surface(icons, EXIT_BUTTON.clip, screen, EXIT_BUTTON.x, EXIT_BUTTON.y);

		// Seagulls:
		apply_surface(icons, &seagull[frame], screen, 922, 105);
		apply_surface(icons, &seagull[frame2], screen, 866, 174);
		apply_surface(icons, &seagull[frame], screen, 1105, 143);
		apply_surface(icons, &seagull[frame2], screen, 1229, 193);

		// Flag:
		apply_surface(icons, &flag[flag_frame], screen, 697, 431);
		


		if (options_show) {
			apply_surface(icons, options_holder, screen, options_holder_x, options_holder_y);

			int volume = Mix_VolumeMusic(-1);
			int volume_x = options_holder_x + 89;
			int volume_y = options_holder_y + 98;
			int volume_width = 0;

			while (volume > 0) {
				
				apply_surface(icons, &volume_bump[0], screen, volume_x + volume_width, volume_y);

				volume_width += volume_bump->w;
				volume -= MIX_MAX_VOLUME/9;
			}
		}

		// Change cursor:
		int x, y;
		SDL_GetMouseState(&x, &y);
		apply_surface(cursor_image, NULL, screen, x, y);
		
		// Update screen:
		if (SDL_Flip(screen) == -1) {
			printf("Screen failed to update. Error: %s\n", SDL_GetError());
			exit(1);
		}

		// Mix_CloseAudio();
		//Cap the frame rate
        if( get_ticksTimer(&fps) < 1000 / FRAMES_PER_SECOND )
        {
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - get_ticksTimer(&fps) );
        }
	}

	SDL_FreeSurface(background);
	SDL_FreeSurface(icons);
	SDL_FreeSurface(cursor_image);
	// SDL_FreeSurface(message);
	Mix_FreeMusic(music);
	Mix_FreeChunk(chunk_test);
	// TTF_CloseFont(font);
	SDL_Quit();	
			
	return 0;
}

