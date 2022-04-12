#ifndef _PERSO_H_
#define _PERSO_H_
#include <SDL/SDL.h>
#include "screen.h"

#define PERSO_VITESSE 5
#define PERSO_VITESSE_INITIALE 0.5

#define PERSO_MAX_STATES 3
#define PERSO_MAX_FRAMES 12

#define STATE_IDLE 0
#define STATE_IDLE_MAX_FRAMES 1
#define STATE_RUNNING 1
#define STATE_RUNNING_MAX_FRAMES 8
#define STATE_JUMPING 2
#define STATE_JUMPING_MAX_FRAMES 2

#define GRAVITY 0.5f

// TO BE REMOVED:
#define DEF_COLL SCREEN_HEIGHT / 2  // collision testing

typedef struct {
    SDL_Surface* model;
    SDL_Rect** clips;
    SDL_Rect* clip;
    int frame;
    int state;
    double vitesse, acceleration, accelerationY;
    float x, y;
    int keydown;
    int on_ground;
} Perso;

void initialiserPerso(Perso* p);
void afficherPerso(Perso p, SDL_Surface* screen);
void deplacerPerso(Perso* p, uint32_t dt, SDL_Event e);
void saut(Perso* p, SDL_Event e);
void animerPerso(Perso* p);

#endif