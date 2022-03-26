#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "image.h"

// SDL_Surface* load_image(const char* filename)
// {
//     SDL_Surface* loaded_image = NULL;
//     SDL_Surface* optimized_image = NULL;

//     loaded_image = IMG_Load(filename);
//     if (loaded_image == NULL) {
//         printf("Could not load image. Error: %s", IMG_GetError());
//         exit(1);
//     }

//     optimized_image = SDL_DisplayFormatAlpha(loaded_image);  // Match display bits

//     SDL_FreeSurface(loaded_image);  // Free old image

//     return optimized_image;
// }

SDL_Surface* load_image(const char* filename)
{
    SDL_Surface* loaded_image = NULL;
    SDL_Surface* optimized_image = NULL;

    loaded_image = IMG_Load(filename);
    if (loaded_image == NULL) {
        printf("Could not load image. Error: %s\n", IMG_GetError());
        exit(1);
    }

    optimized_image = SDL_DisplayFormatAlpha(loaded_image);  // Match display bits

    if (optimized_image == NULL) {
        printf("Image failed to optimize. Error: %s\n", IMG_GetError());
    }

    SDL_FreeSurface(loaded_image);  // Free old image

    return optimized_image;
}

void apply_surface(SDL_Surface* source, SDL_Rect* clip, SDL_Surface* destination, int x, int y)
{
    // Store offsets in a temporary rectangle:
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;

    SDL_BlitSurface(source, clip, destination, &offset);    // Blit the surface
}




// void remove_background(SDL_Surface* loaded_image, Uint8 r, Uint8 g, Uint8 b)
// {
//     Uint32 color_key = SDL_MapRGB(loaded_image->format, r, g, b);    // Map the color key

//     SDL_SetColorKey(loaded_image, SDL_SRCCOLORKEY, color_key);  // Make the color key transparent
// }

void fill_screen_white(SDL_Surface* screen) 
{
    SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));
}


