#include <SDL2/SDL.h>
#include <stdio.h>
#include "../include/struct.h"
#include <time.h>
#include "../include/ui.h"

int main(int argc, char *argv[]) {
    srand(time(NULL));
    initEnemies();

    entity player = {100, 50, 25, 30};
    resetEntity(&player);

    showMenu(&player);
    return 0;
}