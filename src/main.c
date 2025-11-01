#include <SDL2/SDL.h>
#include <stdio.h>
#include "../include/struct.h"

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *win = SDL_CreateWindow("Mini RPG", 100, 100, 640, 480, 0);
    SDL_Delay(1000);
    SDL_DestroyWindow(win);
    SDL_Quit();





    //test pour check si l'arborescence fonctionne
    printf("test entités\n\n");

    showEntity(Goblin);
    showEntity(Orc);
    printf("\n\n");

    int dmg = attack_classic(&Goblin, &Orc);
    printf("Goblin attaque Orc et fait %d dégat\n", dmg);
    printf("hp restant de l'orc : %d \n", Orc.hp);

    return 0;
}