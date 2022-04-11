#include "perso.h"
#include "image.h"
#include "framerate.h"
#include <stdint.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

SDL_Rect** allocMatrix(int nRow, int nCol)
{
    // int i;
    // int ext_status;
    SDL_Rect** matrix = NULL;
    matrix = malloc(nRow * sizeof(int));

    if (matrix == NULL) 
        exit(1);
    for (int i = 0; i < nRow; ++i) {
        matrix[i]= malloc(nCol * sizeof(int));

        if (matrix[i] == NULL)
            exit(1);
    }

    return matrix;
}

void initialiserPerso(Perso* p)
{
    SDL_Surface* model = load_image("../../res/zoro.png");
    // SDL_Surface* model = load_image("../../res/seif.png");
    p->model = model;

    p->clips = allocMatrix(PERSO_MAX_STATES, PERSO_MAX_FRAMES);
    
    // Delete later, only testing:
    p->clips[0][0].x = 10;
    p->clips[0][0].y = 20;
    p->clips[0][0].w = 40;
    p->clips[0][0].h = 70;
    p->clip = &p->clips[0][0];

    // p->clips[0][0].x = 5;
    // p->clips[0][0].y = 1;
    // p->clips[0][0].w = 10;
    // p->clips[0][0].h = 18;
    // p->clip = &p->clips[0][0];

    p->state = STATE_IDLE;
    p->frame = 0;

    p->vitesse = PERSO_VITESSE;
    p->acceleration = 0;

    p->x = 0;
    p->y = 0;
    p->keydown = 0;
    p->on_ground = 0;
}

void afficherPerso(Perso p, SDL_Surface* screen) 
{
    apply_surface(p.model, p.clip, screen, p.x, p.y);
}

void deplacerPerso(Perso* p, Uint32 dt, SDL_Event e)
{
    double v0 = PERSO_VITESSE_INITIALE; // vitesse intitiale

    if (p->keydown == 0) {
        if (e.type == SDL_KEYDOWN) {
            switch(e.key.keysym.sym) {
                case SDLK_LEFT: p->acceleration -= 0.005; break;
                case SDLK_RIGHT: p->acceleration += 0.005; break;
            }

            p->keydown = 1;
        }
    }

    if ((e.type == SDL_KEYUP) && ((e.key.keysym.sym == SDLK_LEFT) || (e.key.keysym.sym == SDLK_RIGHT))) {
        p->keydown = 0;
    }
    
    if (p->keydown == 0) {
        if (p->acceleration > 0) {  // Décélération avec un cumul de la constante
            p->acceleration -= 0.001;
        }
        else if (p->acceleration < 0)
            p->acceleration += 0.001;
    }

    if (p->accelerationY < 0)
        p->state = STATE_JUMPING;
    else if ((p->acceleration > 0) || (p->acceleration < 0))
        p->state = STATE_RUNNING;
    else
        p->state = STATE_IDLE;


    double fac = 0.01;
    p->x += (0.5*p->acceleration*dt*dt + v0*dt)*fac;

    p->accelerationY += GRAVITY;    // Make the character fall if no obstacle is met
    p->y += p->accelerationY;

    // Cap velocity:
    if (p->y > DEF_COLL) {
        p->y = DEF_COLL;
        p->accelerationY = 0;
        p->on_ground = 1;
    }
}

void saut(Perso* p, SDL_Event e)
{
    if ((e.type == SDL_KEYDOWN) && (e.key.keysym.sym == SDLK_UP) && p->on_ground) {
        p->accelerationY = -12;
        p->on_ground = 0;
    }
}

void animerPerso(Perso* p)
{
    
}