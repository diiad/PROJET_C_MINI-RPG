#ifndef RPG_MAP_HEADER_H
#define RPG_MAP_HEADER_H

#include <SDL2/SDL.h>

#define MAP_W 20
#define MAP_H 15
#define TILE_SIZE 32

void map_init(void);
void map_render(SDL_Renderer *ren);
int map_move_player(int dx, int dy);
void map_spawn_random_enemy(void);

#endif