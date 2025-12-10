#include "../include/struct.h"
#include "ui.h"
#include <stdio.h>
#include <stdlib.h>

int initUI(SDL_Window **window, SDL_Renderer **renderer){
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur SDL: %s\n", SDL_GetError());
        return 0;
    }

    if (TTF_Init() == -1) {
        printf("Erreur SDL_ttf: %s\n", TTF_GetError());
        return 0;
    }

    *window = SDL_CreateWindow("Menu du jeu", 
                                SDL_WINDOWPOS_CENTERED, 
                                SDL_WINDOWPOS_CENTERED, 
                                640, 480, 
                                SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Erreur création fenêtre: %s\n", SDL_GetError());
        return 0;
    }

    .renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Erreur création renderer: %s\n", SDL_GetError());
        return 0;
    }
    
    return 1;
}

void showMenu(entity *player, SDL_Renderer *renderer) {
    int running = 1;
    SDL_Event e;

    TTF_Font *font = TTF_OpenFont("arial.ttf", 24);
    if (!font) {
        printf("Erreur chargement police: %s\n", TTF_GetError());
        return;
    }
    while (running) {
        while (SDL_PollEvent(&e)) {
           if (e.type == SDL_QUIT) {
               running = 0;
           }
           if (e.type == SDL_KEYDOWN) {
               switch (e.key.keysym.sym) {
                   case SDLK_1: {
                       entity enemy = randomEnemy();
                       resetEntity(&enemy);
                       startCombat(player, &enemy);
                       break;
                   }
                   case SDLK_2:
                       showEntity(*player);
                       break;
                   case SDLK_3:
                       running = 0;
                       break;
               }
           }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_Color white = {255, 255, 255};
        SDL_Surface *surface = TTF_RenderText_Solid(font, "1. Combattre un ennemi", white);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect rect = {50, 100, surface->w, surface->h};
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);

        surface = TTF_RenderText_Solid(font, "2. Voir mes statistiques", white);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        rect.y = 150; rect.w = surface->w; rect.h = surface->h;
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);

        surface = TTF_RenderText_Solid(font, "3. Quitter", white);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        rect.y = 200; rect.w = surface->w; rect.h = surface->h;
        SDL_RenderCopy(renderer, texture, NULL, &rest);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);

        SDL_RenderPresent(renderer);
    }

    TTF_CloseFont(font);
 
}

void cleanupUI(SDL_Window *window, SDL_Renderer *renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}
