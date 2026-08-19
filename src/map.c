#include "../include/map.h"
#include <stdio.h>
#include <stdlib.h>

static char mapGrid[MAP_H][MAP_W];
static int playerPosX = 1;
static int playerPosY = 1;

// initialise la map depuis le fichier
void map_init(void) {
    // Remplissage par défaut
    for(int y=0; y<MAP_H; y++) {
        for(int x=0; x<MAP_W; x++) mapGrid[y][x] = '.';
    }

    FILE *f = fopen("../assets/maps/map1.map", "r");
    if (f) {
        for (int y = 0; y < MAP_H; y++) {
            for (int x = 0; x < MAP_W; x++) {
                int c = fgetc(f);
                while (c == '\n' || c == '\r') c = fgetc(f);

                if (c == 'P') {
                    playerPosX = x;
                    playerPosY = y;
                    mapGrid[y][x] = '.';
                } else if (c != EOF) {
                    mapGrid[y][x] = (char)c;
                }
            }
        }
        fclose(f);
    } else {
        printf("Erreur chargement map.\n");
    }
}

// gère les deplacement du j dans la map
int map_move_player(int dx, int dy) {
    int nextX = playerPosX + dx;
    int nextY = playerPosY + dy;

    if (nextX < 0 || nextX >= MAP_W || nextY < 0 || nextY >= MAP_H) return 0;

    char tile = mapGrid[nextY][nextX];
    if (tile == '#') return 0; // Mur

    if (tile == 'E') {
        mapGrid[nextY][nextX] = '.';
        playerPosX = nextX;
        playerPosY = nextY;
        return 2; // Combat
    }

    playerPosX = nextX;
    playerPosY = nextY;
    return 1;
}

// affiche la carte et le j
void map_render(SDL_Renderer *ren) {
    for (int y = 0; y < MAP_H; y++) {
        for (int x = 0; x < MAP_W; x++) {
            SDL_Rect tileRect = { x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
            char tile = mapGrid[y][x];

            if (tile == '#') SDL_SetRenderDrawColor(ren, 100, 100, 100, 255);
            else if (tile == 'E') SDL_SetRenderDrawColor(ren, 200, 50, 50, 255);
            else SDL_SetRenderDrawColor(ren, 30, 30, 30, 255);

            SDL_RenderFillRect(ren, &tileRect);
            SDL_SetRenderDrawColor(ren, 40, 40, 40, 255);
            SDL_RenderDrawRect(ren, &tileRect);
        }
    }
    // Joueur
    SDL_Rect playerRect = { playerPosX * TILE_SIZE + 4, playerPosY * TILE_SIZE + 4, TILE_SIZE - 8, TILE_SIZE - 8 };
    SDL_SetRenderDrawColor(ren, 50, 150, 255, 255);
    SDL_RenderFillRect(ren, &playerRect);
}

// fait apparaitre un ennemie dans une position random dans la map
void map_spawn_random_enemy(void) {
    int placed = 0;
    int attempts = 0;
    while (!placed && attempts < 100) {
        int spawnX = rand() % MAP_W;
        int spawnY = rand() % MAP_H;
        if (mapGrid[spawnY][spawnX] == '.' && (spawnX != playerPosX || spawnY != playerPosY)) {
            mapGrid[spawnY][spawnX] = 'E';
            placed = 1;
        }
        attempts++;
    }
}