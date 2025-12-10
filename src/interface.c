#include <SDL2/SDL.h>
#include <SDL2/SDL_messagebox.h>
#include <SDL2/SDL_filesystem.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#include "../include/interface.h"
#include "../include/struct.h"
#include "../include/classes.h"

typedef enum { SC_MENU, SC_CLASS_SELECT, SC_COMBAT, SC_HIGHSCORES, SC_QUIT } Scene;

typedef struct { char ch; const char *rows[7]; } Glyph5x7;

static const Glyph5x7 FONT_5x7[] = {
    // C
    {'C', {"#####","#....","#....","#....","#....","#....","#####"}},
    // D
    {'D', {"####.","#...#","#...#","#...#","#...#","#...#","####."}},
    // E
    {'E', {"#####","#....","#####","#....","#....","#....","#####"}},
    // G
    {'G', {"#####","#....","#....","#.###","#...#","#...#","#####"}},
    // H
    {'H', {"#...#","#...#","#...#","#####","#...#","#...#","#...#"}},
    // I
    {'I', {"#####","..#..","..#..","..#..","..#..","..#..","#####"}},
    // J
    {'J', {"....#","....#","....#","....#","#...#","#...#","#####"}},
    // O
    {'O', {"#####","#...#","#...#","#...#","#...#","#...#","#####"}},
    // Q
    {'Q', {"#####","#...#","#...#","#...#","#.#.#","#..##","####."}},
    // R
    {'R', {"#####","#...#","#...#","#####","#..#.","#...#","#...#"}},
    // S
    {'S', {"#####","#....","#....","#####","....#","....#","#####"}},
    // T
    {'T', {"#####","..#..","..#..","..#..","..#..","..#..","..#.."}},
    // U
    {'U', {"#...#","#...#","#...#","#...#","#...#","#...#","#####"}},
    // Espace
    {' ', {".....",".....",".....",".....",".....",".....","....."}},
};

static const Glyph5x7* find_glyph(char c) {
    size_t n = sizeof(FONT_5x7)/sizeof(FONT_5x7[0]);
    for (size_t i = 0; i < n; ++i) {
        if (FONT_5x7[i].ch == c) return &FONT_5x7[i];
    }
    return NULL;
}

static void draw_char_5x7(SDL_Renderer *ren, int x, int y, int scale,
                          Uint8 r, Uint8 g, Uint8 b, Uint8 a, char c) {
    const Glyph5x7 *gph = find_glyph(c);
    if (!gph) return;
    SDL_SetRenderDrawColor(ren, r, g, b, a);
    for (int row = 0; row < 7; ++row) {
        const char *line = gph->rows[row];
        for (int col = 0; col < 5; ++col) {
            if (line[col] == '#') {
                SDL_Rect px = { x + col*scale, y + row*scale, scale, scale };
                SDL_RenderFillRect(ren, &px);
            }
        }
    }
}

static void draw_text_5x7(SDL_Renderer *ren, int x, int y, int scale,
                          Uint8 r, Uint8 g, Uint8 b, Uint8 a, const char *text) {
    if (!text) return;
    int cursor = 0;
    for (size_t i = 0; i < strlen(text); ++i) {
        char c = (char)toupper((unsigned char)text[i]);
        const Glyph5x7 *gph = find_glyph(c);
        if (gph) {
            draw_char_5x7(ren, x + cursor, y, scale, r, g, b, a, c);
            cursor += 5*scale; // glyph width
        }
        // lettre spacing (1 colonne vide)
        cursor += 1*scale;
    }
}

static void draw_text_centered_in_rect(SDL_Renderer *ren, SDL_Rect rect, int scale,
                                       Uint8 r, Uint8 g, Uint8 b, Uint8 a,
                                       const char *text) {
    if (!text) return;
    // Calcul largeur du texte
    int count = 0;
    for (size_t i = 0; i < strlen(text); ++i) {
        if (find_glyph((char)toupper((unsigned char)text[i]))) count++;
    }
    int char_w = 5*scale;
    int spacing = 1*scale;
    int text_w = count*char_w + (count>0 ? (count)*spacing : 0);
    int text_h = 7*scale;
    int tx = rect.x + (rect.w - text_w)/2;
    int ty = rect.y + (rect.h - text_h)/2;
    draw_text_5x7(ren, tx, ty, scale, r, g, b, a, text);
}

static void launch_editor(SDL_Window* win) {
#ifdef _WIN32
    const char* exeName = "RPG_C_Editor.exe";
#else
    const char* exeName = "RPG_C_Editor";
#endif


    char cmd[1024] = {0};
    int launched = 0;

    char* base = SDL_GetBasePath(); 
    if (base) {
        char path1[768];
        snprintf(path1, sizeof(path1), "%s%s", base, exeName);
        SDL_free(base);

#ifdef _WIN32
        snprintf(cmd, sizeof(cmd), "\"%s\"", path1);
#else
        snprintf(cmd, sizeof(cmd), "\"%s\"", path1);
#endif
        int rc = system(cmd);
        if (rc == 0) {
            launched = 1;
        }
    }

    if (!launched) {
        
#ifdef _WIN32
        snprintf(cmd, sizeof(cmd), "%s", exeName);
#else
        snprintf(cmd, sizeof(cmd), "./%s", exeName);
#endif
        int rc = system(cmd);
        if (rc == 0) {
            launched = 1;
        }
    }

    if (!launched) {
        
#ifdef _WIN32
        snprintf(cmd, sizeof(cmd), "cmake-build-debug/%s", exeName);
#else
        snprintf(cmd, sizeof(cmd), "\"cmake-build-debug/%s\"", exeName);
#endif
        int rc = system(cmd);
        if (rc == 0) {
            launched = 1;
        }
    }

    if (!launched) {
        SDL_ShowSimpleMessageBox(
            SDL_MESSAGEBOX_ERROR,
            "Editeur introuvable",
            "Impossible de lancer l'editeur.\n"
            "Vérifiez que la cible 'RPG_C_Editor' est compilée (build),\n"
            "et que l'exécutable se trouve à côté du jeu (cmake-build-debug).",
            win
        );
    }
}

int run_game(void) {
    srand((unsigned)time(NULL));
    initEnemies();

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
        fprintf(stderr, "SDL_Init error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow(
        "MINI RPG",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        960, 540,
        SDL_WINDOW_SHOWN
    );
    if (!win) {
        fprintf(stderr, "SDL_CreateWindow error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *ren = SDL_CreateRenderer(
        win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    if (!ren) {
        fprintf(stderr, "SDL_CreateRenderer error: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    
    PlayerClass selectedClass = CLASS_WARRIOR;
    entity player;
    apply_class_to_entity(&player, selectedClass);

    int running = 1;
    Scene scene = SC_MENU;

    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) { running = 0; break; }
            if (e.type == SDL_KEYDOWN) {
                if (scene == SC_MENU) {
                    switch (e.key.keysym.sym) {
                        case SDLK_1:
                            
                            apply_class_to_entity(&player, selectedClass);
                            scene = SC_COMBAT;
                            break;
                        case SDLK_2:
                            scene = SC_HIGHSCORES;
                            
                            SDL_ShowSimpleMessageBox(
                                SDL_MESSAGEBOX_INFORMATION,
                                "Highscores",
                                "Top 5: (à venir)\nAjoutez le module scores pour persister les résultats.",
                                win
                            );
                            break;
                        case SDLK_3:
                            
                            launch_editor(win);
                            break;
                        case SDLK_4:
                            running = 0;
                            break;
                        case SDLK_c: 
                            
                            scene = SC_CLASS_SELECT;
                            break;
                        default:
                            break;
                    }
                } else if (scene == SC_COMBAT) {
                
                    if (e.key.keysym.sym == SDLK_ESCAPE) scene = SC_MENU;
                } else if (scene == SC_HIGHSCORES) {
                    if (e.key.keysym.sym == SDLK_ESCAPE) scene = SC_MENU;
                } else if (scene == SC_CLASS_SELECT) {
                    switch (e.key.keysym.sym) {
                        case SDLK_1:
                            selectedClass = CLASS_WARRIOR;
                            apply_class_to_entity(&player, selectedClass);
                            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Classe", "Classe choisie: Guerrier", win);
                            scene = SC_MENU;
                            break;
                        case SDLK_2:
                            selectedClass = CLASS_ARCHER;
                            apply_class_to_entity(&player, selectedClass);
                            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Classe", "Classe choisie: Archer", win);
                            scene = SC_MENU;
                            break;
                        case SDLK_3:
                            selectedClass = CLASS_MAGE;
                            apply_class_to_entity(&player, selectedClass);
                            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Classe", "Classe choisie: Mage", win);
                            scene = SC_MENU;
                            break;
                        case SDLK_ESCAPE:
                            scene = SC_MENU;
                            break;
                        default:
                            break;
                    }
                }
            }
        }

        
        if (scene == SC_MENU) {
            SDL_SetRenderDrawColor(ren, 30, 30, 60, 255);
            SDL_RenderClear(ren);

        
            SDL_Rect btn1 = { 360, 120, 240, 50 }; // Jouer
            SDL_Rect btn2 = { 360, 190, 240, 50 }; // Highscores
            SDL_Rect btn3 = { 360, 260, 240, 50 }; // Editeur
            SDL_Rect btn4 = { 360, 330, 240, 50 }; // Quitter

            SDL_SetRenderDrawColor(ren, 80, 80, 160, 255); SDL_RenderFillRect(ren, &btn1);
            SDL_SetRenderDrawColor(ren, 80, 160, 80, 255); SDL_RenderFillRect(ren, &btn2);
            SDL_SetRenderDrawColor(ren, 160, 80, 80, 255); SDL_RenderFillRect(ren, &btn3);
            SDL_SetRenderDrawColor(ren, 120, 120, 120, 255); SDL_RenderFillRect(ren, &btn4);

            
            int scale = 3; 
            draw_text_centered_in_rect(ren, btn1, scale, 255, 255, 255, 255, "Jouer");
            draw_text_centered_in_rect(ren, btn2, scale, 255, 255, 255, 255, "Highscores");
            draw_text_centered_in_rect(ren, btn3, scale, 255, 255, 255, 255, "Editeur");
            draw_text_centered_in_rect(ren, btn4, scale, 255, 255, 255, 255, "Quitter");
        } else if (scene == SC_CLASS_SELECT) {
            SDL_SetRenderDrawColor(ren, 20, 20, 40, 255);
            SDL_RenderClear(ren);

            
            SDL_Rect c1 = { 200, 120, 180, 80 }; // Guerrier
            SDL_Rect c2 = { 390, 120, 180, 80 }; // Archer
            SDL_Rect c3 = { 580, 120, 180, 80 }; // Mage

            SDL_SetRenderDrawColor(ren, 120, 100, 60, 255); SDL_RenderFillRect(ren, &c1);
            SDL_SetRenderDrawColor(ren, 80, 120, 80, 255);  SDL_RenderFillRect(ren, &c2);
            SDL_SetRenderDrawColor(ren, 120, 80, 120, 255); SDL_RenderFillRect(ren, &c3);
        } else if (scene == SC_COMBAT) {
            SDL_SetRenderDrawColor(ren, 60, 30, 30, 255);
            SDL_RenderClear(ren);
        } else if (scene == SC_HIGHSCORES) {
            SDL_SetRenderDrawColor(ren, 20, 50, 20, 255);
            SDL_RenderClear(ren);
        } else {
            SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
            SDL_RenderClear(ren);
        }

        SDL_RenderPresent(ren);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
