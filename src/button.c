#include <SDL/SDL.h>
#include <stdio.h>
#include "button.h"

void set_clips(SDL_Rect clips[])
{
    clips[PLAY_BUTTON_MOUSEOUT].x = 0;
	clips[PLAY_BUTTON_MOUSEOUT].y = 0;
	clips[PLAY_BUTTON_MOUSEOUT].w = 76;
	clips[PLAY_BUTTON_MOUSEOUT].h = 22;

	clips[PLAY_BUTTON_MOUSEOVER].x = 91;
	clips[PLAY_BUTTON_MOUSEOVER].y = 0;
	clips[PLAY_BUTTON_MOUSEOVER].w = 76;
	clips[PLAY_BUTTON_MOUSEOVER].h = 22;

	clips[OPTIONS_BUTTON_MOUSEOUT].x = 0;
	clips[OPTIONS_BUTTON_MOUSEOUT].y = 56;
	clips[OPTIONS_BUTTON_MOUSEOUT].w = 136;
	clips[OPTIONS_BUTTON_MOUSEOUT].h = 22;

	clips[OPTIONS_BUTTON_MOUSEOVER].x = 197;
	clips[OPTIONS_BUTTON_MOUSEOVER].y = 56;
	clips[OPTIONS_BUTTON_MOUSEOVER].w = 136;
	clips[OPTIONS_BUTTON_MOUSEOVER].h = 22;

	clips[EXIT_BUTTON_MOUSEOUT].x = 0;
	clips[EXIT_BUTTON_MOUSEOUT].y = 107;
	clips[EXIT_BUTTON_MOUSEOUT].w = 74;
	clips[EXIT_BUTTON_MOUSEOUT].h = 22;

	clips[EXIT_BUTTON_MOUSEOVER].x = 112;
	clips[EXIT_BUTTON_MOUSEOVER].y = 107;
	clips[EXIT_BUTTON_MOUSEOVER].w = 74;
	clips[EXIT_BUTTON_MOUSEOVER].h = 22;
}

void init_button(struct buttons* button, int x, int y, int w, int h)
{
	// Load offsets to button:
	button->x = x;
	button->y = y;
	button->w = w;
	button->h = h;
}

int mouseover_BUTTON(struct buttons button)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	// printf("%d %d %d\n", x, y, ((x > button.x) && (x < button.x + button.w) && (y > button.y) && (y < button.y + button.h)));
	if ((x > button.x) && (x < button.x + button.w) && (y > button.y) && (y < button.y + button.h))
        return 1;
    else
        return 0;
}

// TODO
// void handle_events(struct button button)
// {
//     SDL_Event event;

//     int x = 0, y = 0;   // The mouse offsets

//     if (event.type == SDL_MOUSEMOTION) // Detect mouse motion
//     {
//         SDL_GetMouseState(&x, &y);  // Get the mouse offsets:
    
//         // If the mouse is over the button
//         if ((x > button.x) && (x < button.x + button.w) && (y > button.y) && (y < button.y + button.h))
//             button.clip = &clips[PLAY_BUTTON_MOUSEOVER];   // Set the button sprite   
//         else
//             button.clip = &clips[PLAY_BUTTON_MOUSEOUT]; // Set the button sprite
//     }

//     if (event.type == SDL_MOUSEBUTTONDOWN)
//     {
//         if (event.button.button == SDL_BUTTON_LEFT)
//         {
//             SDL_GetMouseState(&x, &y);  

//             if ((x > button.x) && (x < button.x + button.w) && (y > button.y) && (y < button.y + button.h))
//                 button.clip = &clips[PLAY_BUTTON_MOUSEDOWN];     
//         }
//     }

//     if (event.type == SDL_MOUSEBUTTONUP)
//     {
//         if (event.button.button == SDL_BUTTON_LEFT)
//         {
//             SDL_GetMouseState(&x, &y);  

//             if ((x > button.x) && (x < button.x + button.w) && (y > button.y) && (y < button.y + button.h))
//                 button.clip = &clips[PLAY_BUTTON_MOUSEOUT];     
//         }
//     }
// }

