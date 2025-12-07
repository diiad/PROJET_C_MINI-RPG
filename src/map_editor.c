#include <SDL2/SDL.h>
#include <stdio.h>
#include <string.h>
#include "../include/map_editor.h"

#if defined(_WIN32)
#  include <direct.h>
#else
#  include <sys/stat.h>
#  include <sys/types.h>
#endif

char mapGrid[MAP_H][MAP_W];

void sauvegarderMap() {
    // S'assurer que les dossiers existent
#if defined(_WIN32)
    _mkdir("assets");
    _mkdir("assets/maps");
#else
    mkdir("assets", 0777);
    mkdir("assets/maps", 0777);
#endif

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
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init error: %s\n", SDL_GetError());
        return;
    }

    SDL_Window *win = SDL_CreateWindow(
        "Editeur de Carte - MINI RPG",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        MAP_W * TILE, MAP_H * TILE,
        SDL_WINDOW_SHOWN
    );
    if (!win) {
        printf("SDL_CreateWindow error: %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }

    SDL_Renderer *ren = SDL_CreateRenderer(
        win, -1, SDL_RENDERER_ACCELERATED
    );
    if (!ren) {
        printf("SDL_CreateRenderer error: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return;
    }

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

                    case SDLK_p: {
                        // Placer 'P' à la position de la souris (unique sur la carte)
                        int mx, my; SDL_GetMouseState(&mx, &my);
                        int tx = mx / TILE; int ty = my / TILE;
                        if (tx >= 0 && tx < MAP_W && ty >= 0 && ty < MAP_H) {
                            // Nettoyer l'ancien 'P'
                            for (int yy = 0; yy < MAP_H; yy++) {
                                for (int xx = 0; xx < MAP_W; xx++) {
                                    if (mapGrid[yy][xx] == 'P') mapGrid[yy][xx] = '.';
                                }
                            }
                            mapGrid[ty][tx] = 'P';
                        }
                        break;
                    }
                    
                    case SDLK_e: {
                        // Placer 'E' à la position de la souris (multiples autorisés)
                        int mx, my; SDL_GetMouseState(&mx, &my);
                        int tx = mx / TILE; int ty = my / TILE;
                        if (tx >= 0 && tx < MAP_W && ty >= 0 && ty < MAP_H) {
                            mapGrid[ty][tx] = 'E';
                        }
                        break;
                    }
                    
                    case SDLK_s:

                        sauvegarderMap();
                        break;
                    
                    case SDLK_ESCAPE:
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
                else if (mapGrid[y][x] == 'P')
                    SDL_SetRenderDrawColor(ren, 0, 180, 50, 255);
                else if (mapGrid[y][x] == 'E')
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

// Point d'entrée de l'éditeur (exécutable séparé)
int main(int argc, char *argv[]) {
    (void)argc; (void)argv;
    lancerEditeurMap();
    return 0;
}