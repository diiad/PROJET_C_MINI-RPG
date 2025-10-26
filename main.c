#include <SDL2/SDL.h>

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *win = SDL_CreateWindow("Mini RPG", 100, 100, 640, 480, 0);
    SDL_Delay(1000);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}