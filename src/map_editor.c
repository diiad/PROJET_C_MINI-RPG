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

/* Sauvegarde de la map dans un fichier */
void sauvegarderMap() {
    // au cas ou y'a pas de dossier
#if defined(_WIN32)
    _mkdir("../assets");
    _mkdir("../assets/maps");
#else
    mkdir("../assets", 0777);
    mkdir("../assets/maps", 0777);
#endif

    FILE *f = fopen("../assets/maps/map1.map", "w");
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
    printf("Carte sauvegardée dans assets/maps/map1.map\nRelancez le prendre pour que les modifications prennent effet.");
}

// Lance l'éditeur de carte
void lancerEditeurMap() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init error: %s\n", SDL_GetError());
        return;
    }

    SDL_Window *win = SDL_CreateWindow(
        "Editeur de Carte - Pitié mettez nous 20/20",
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

    int isRunning = 1;
    SDL_Event event;

    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                isRunning = 0;

            if (event.type == SDL_MOUSEBUTTONDOWN) {

                int tileX = event.button.x / TILE;
                int tileY = event.button.y / TILE;

                if (tileX < 0 || tileX >= MAP_W || tileY < 0 || tileY >= MAP_H)
                    continue;

                if (event.button.button == SDL_BUTTON_LEFT) {

                    mapGrid[tileY][tileX] = '#';
                }
                else if (event.button.button == SDL_BUTTON_RIGHT) {

                    mapGrid[tileY][tileX] = '.';
                }
            }

            if (event.type == SDL_KEYDOWN) {

                switch (event.key.keysym.sym) {

                    case SDLK_p: {
                        // Point de départ du joueur avec p et
                        //la position de la souris
                        int mouseX, mouseY; SDL_GetMouseState(&mouseX, &mouseY);
                        int tileX = mouseX / TILE; int tileY = mouseY / TILE;
                        if (tileX >= 0 && tileX < MAP_W && tileY >= 0 && tileY < MAP_H) {
                            // Nettoyer l'ancien 'P'
                            for (int yy = 0; yy < MAP_H; yy++) {
                                for (int xx = 0; xx < MAP_W; xx++) {
                                    if (mapGrid[yy][xx] == 'P') mapGrid[yy][xx] = '.';
                                }
                            }
                            mapGrid[tileY][tileX] = 'P';
                        }
                        break;
                    }

                    case SDLK_e: {
                        // Placer un ennemie avec e à la position de la souris
                        int mouseX, mouseY; SDL_GetMouseState(&mouseX, &mouseY);
                        int tileX = mouseX / TILE; int tileY = mouseY / TILE;
                        if (tileX >= 0 && tileX < MAP_W && tileY >= 0 && tileY < MAP_H) {
                            mapGrid[tileY][tileX] = 'E';
                        }
                        break;
                    }

                    case SDLK_s:

                        sauvegarderMap();
                        break;

                    case SDLK_ESCAPE:
                        isRunning = 0;
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


int main(int argc, char *argv[]) {
    (void)argc; (void)argv;
    lancerEditeurMap();
    return 0;
}