#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED

typedef struct {
    SDL_Surface* image; 
    Mix_Music* son;
    int niveau;
}Background;

void initback(Background* b);
void load(Background* b);
void aficherBack(Background b, SDL_Surface* screen);
void animerBackground( Background * e);
int collisionPP( Personne p, SDL_Surface * Masque);
void scrolling (background * b, int direction, int pasAvancement); 
#endif // FONCTION_H_INCLUDED
