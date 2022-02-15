#ifndef _IMAGE_H_
#define _IMAGE_H_

struct image {
    const char* filename;
    SDL_Rect* rect;
    int x;
    int y;
    SDL_Surface* surface;
};

// SDL_Surface* load_image(const char* filename);
SDL_Surface* load_image(const char* filename);
void apply_surface(SDL_Surface* source, SDL_Rect* clip, SDL_Surface* destination, int x, int y);
void fill_screen_white(SDL_Surface* screen);

#endif