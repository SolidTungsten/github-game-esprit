#ifndef _PERSO_H_
#define _PERSO_H_
#include <SDL/SDL.h>

#define PERSO_VITESSE 5
#define PERSO_VITESSE_INITIALE 0.5

#define PERSO_MAX_STATES 3
#define PERSO_MAX_FRAMES 12

#define STATE_IDLE 0
#define STATE_RUNNING 1
#define STATE_JUMPING 2

typedef struct {
    SDL_Surface* model;
    SDL_Rect** clips;
    SDL_Rect* clip;
    int frame;
    int state;
    double vitesse, acceleration;
    int x, y;
    int keydown;
} Perso;

void initialiserPerso(Perso* p);
void afficherPerso(Perso p, SDL_Surface* screen);
void deplacerPerso(Perso* p, uint32_t dt, SDL_Event e);

#endif