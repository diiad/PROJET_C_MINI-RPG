#ifndef UI_H
#define UI_H

#include "struct.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

int initUI(SDL_Window **window, SDL_Renderer **renderer);

void showMenu(entity *player, SDL_Renderer *renderer);

void cleanupUI(SDL_Window *window, SDL_Renderer *renderer);

#endif
