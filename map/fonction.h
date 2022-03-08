#ifndef Image_H
#define Image_H
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#define SCREEN_W 1920
#define SCREEN_H 1228
typedef struct{
    SDL_Rect posmap;
    SDL_Rect posjoueur;
    SDL_Surface * camera;
    SDL_Surface * bon;
}minimap;
void initminimap( minimap * m);
 void MAJMinimap(SDL_Rect posJoueur,  minimap * m, SDL_Rect camera, int redimensionnement);
void afficher (minimap m, SDL_Surface * screen);
void Liberer (minimap * m);
 void sauvegarder( int score, char nomjoueur[], char nomfichier[]); 
 void meilleur( char nomfichier[], int *score, char nomjoueur[]); 
#endif

