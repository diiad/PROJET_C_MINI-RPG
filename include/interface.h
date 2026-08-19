#ifndef INTERFACE_H
#define INTERFACE_H

#include <SDL2/SDL.h>

// Initialise la SDL, la fenêtre et le rendu
int interface_init(SDL_Window **fenetre, SDL_Renderer **rendu);

// ferme la SDL
void interface_fermer(SDL_Window *fenetre, SDL_Renderer *rendu);

// Fonction principale qui dessine toute l'interface selon l'état du jeu
void interface_dessiner_tout(SDL_Renderer *rendu);

#endif