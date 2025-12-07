#include <SDL2/SDL.h>
#include <stdio.h>
#include <string.h>
#include "../include/map_editor.h"

char mapGrid[MAP_H][MAP_W];

void sauvegarderMap() {
    FILE *f = fopen("assets/maps/map1.map", "w");
    if(!f) {
        printf("Impossible d'ouvrir le fichier de sauvegarde.\n");
        return;
    }

    for (int y = 0; y < MAP_H; y++) {
        for (int x = 0; x < MAP_W; x++) {
            fputc(mapGrid[y][x], f);
        }
        fputc('\n', f);
    }

    fclose(f);
    printf("Carte sauvegardée dans assets/maps/map1.map\n");
}

void lancerEditeurMap() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *win = SDL_CreateWindow(
        "Editeur de Carte - MINI RPG",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        MAP_W * TILE, MAP_H * TILE,
        SDL_WINDOW_SHOWN
    );

    SDL_Renderer *ren = SDL_CreateRenderer(
        win, -1, SDL_RENDERER_ACCELERATED
    );

    memset(mapGrid, '.', sizeof(mapGrid));

    int running = 1;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                running = 0;

            if (e.type == SDL_MOUSEBUTTONDOWN) {

                int x = e.button.x / TILE;
                int y = e.button.y / TILE;

                if (x < 0 || x >= MAP_W || y < 0 || y >= MAP_H)
                    continue;

                if (e.button.button == SDL_BUTTON_LEFT) {

                    mapGrid[y][x] = '#';
                }
                else if (e.button.button == SDL_BUTTON_RIGHT) {

                    mapGrid[y][x] = '.';
                }
            }

            if (e.type == SDL_KEYDOWN) {

                switch (e.key.keysym.sym) {

                    case SDLK_p:

                        mapGrid[5][5] = 'P';
                        break;
                    
                    case SDKL_e:

                        mapGrid[8][10] = 'E';
                        break;
                    
                    case SDKL_s:

                        sauvegarderMap();
                        break;
                    
                    case SDKL_ESCAPE:
                        running = 0;
                        break;
                }
            }
        }

        SDL_SetRenderDrawColor(ren, 30, 30, 30, 255);
        SDL_RenderClear(ren);

        for (int y = 0; y < MAP_H; y++) {
            for (int x = 0; x < MAP_W; x++) {

                SDL_Rect tile = { x * TILE, y * TILE, TILE, TILE };

                if (mapGrid[y][x] == '#')
                    SDL_SetRenderDrawColor(ren, 120, 120, 120, 255);
                else if (mapGrid[y][x] == "P")
                    SDL_SetRenderDrawColor(ren, 0, 180, 50, 255);
                else if (mapGrid[y][x] == "E")
                    SDL_SetRenderDrawColor(ren, 200, 40, 40, 255);
                else 
                    SDL_SetRenderDrawColor(ren, 60, 60, 60, 255);

                SDL_RenderFillRect(ren, &tile);

                SDL_SetRenderDrawColor(ren, 20, 20, 20, 255);
                SDL_RenderDrawRect(ren, &tile);
            }
        }

        SDL_RenderPresent(ren);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}