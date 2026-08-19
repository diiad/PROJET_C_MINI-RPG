#include <SDL2/SDL.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "../include/interface.h"
#include "../include/jeu.h"
#include "../include/map.h"
#include "../include/scores.h"
#include "../include/classes.h"

int interface_init(SDL_Window **fenetre, SDL_Renderer **rendu) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erreur SDL_Init: %s\n", SDL_GetError());
        return 0;
    }

    *fenetre = SDL_CreateWindow("RPG C - Projet",
                                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                800, 600,
                                SDL_WINDOW_SHOWN);
    if (!*fenetre) {
        printf("Erreur SDL_CreateWindow: %s\n", SDL_GetError());
        SDL_Quit();
        return 0;
    }

    *rendu = SDL_CreateRenderer(*fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!*rendu) {
        printf("Erreur SDL_CreateRenderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(*fenetre);
        SDL_Quit();
        return 0;
    }

    return 1;
}

void interface_fermer(SDL_Window *fenetre, SDL_Renderer *rendu) {
    if (rendu) SDL_DestroyRenderer(rendu);
    if (fenetre) SDL_DestroyWindow(fenetre);
    SDL_Quit();
}

typedef struct { char ch; const char *rows[7]; } Glyph5x7;

static const Glyph5x7 FONT_5x7[] = {
    {'A', {"..#..",".#.#.","#...#","#####","#...#","#...#","#...#"}}, {'B', {"####.","#...#","#...#","####.","#...#","#...#","####."}},
    {'C', {"#####","#....","#....","#....","#....","#....","#####"}}, {'D', {"####.","#...#","#...#","#...#","#...#","#...#","####."}},
    {'E', {"#####","#....","#####","#....","#....","#....","#####"}}, {'F', {"#####","#....","#####","#....","#....","#....","#...."}},
    {'G', {"#####","#....","#....","#.###","#...#","#...#","#####"}}, {'H', {"#...#","#...#","#...#","#####","#...#","#...#","#...#"}},
    {'I', {"#####","..#..","..#..","..#..","..#..","..#..","#####"}}, {'J', {"...##","....#","....#","....#","#...#","#...#","#####"}},
    {'K', {"#...#","#..#.","#.#..","##...","#.#..","#..#.","#...#"}}, {'L', {"#....","#....","#....","#....","#....","#....","#####"}},
    {'M', {"#...#","##.##","#.#.#","#.#.#","#...#","#...#","#...#"}}, {'N', {"#...#","##..#","#.#.#","#..##","#...#","#...#","#...#"}},
    {'O', {"#####","#...#","#...#","#...#","#...#","#...#","#####"}}, {'P', {"####.","#...#","#...#","####.","#....","#....","#...."}},
    {'Q', {"#####","#...#","#...#","#...#","#.#.#","#..##","####."}}, {'R', {"####.","#...#","#...#","####.","#.#..","#..#.","#...#"}},
    {'S', {"#####","#....","#....","#####","....#","....#","#####"}}, {'T', {"#####","..#..","..#..","..#..","..#..","..#..","..#.."}},
    {'U', {"#...#","#...#","#...#","#...#","#...#","#...#","#####"}}, {'V', {"#...#","#...#","#...#","#...#",".#.#.","..#..","..#.."}},
    {'W', {"#...#","#...#","#...#","#.#.#","#.#.#","##.##","#...#"}}, {'X', {"#...#",".#.#.","..#..","..#..",".#.#.","#...#","#...#"}},
    {'Y', {"#...#",".#.#.","..#..","..#..","..#..","..#..","..#.."}}, {'Z', {"#####","....#","...#.","..#..",".#...","#....","#####"}},
    {'0', {"#####","#...#","#..##","#.#.#","##..#","#...#","#####"}}, {'1', {"..#..",".##..","..#..","..#..","..#..","..#..","#####"}},
    {'2', {"#####","....#","...#.","..#..",".#...","#....","#####"}}, {'3', {"#####","....#","....#","#####","....#","....#","#####"}},
    {'4', {"#...#","#...#","#...#","#####","....#","....#","....#"}}, {'5', {"#####","#....","#....","#####","....#","....#","#####"}},
    {'6', {"#####","#....","#....","#####","#...#","#...#","#####"}}, {'7', {"#####","....#","...#.","..#..",".#...","#....","#...."}},
    {'8', {"#####","#...#","#...#","#####","#...#","#...#","#####"}}, {'9', {"#####","#...#","#...#","#####","....#","....#","#####"}},
    {'.', {".....",".....",".....",".....",".....","..#..","..#.."}}, {',', {".....",".....",".....",".....","..#..","..#..",".#..."}},
    {':', {".....","..#..",".....",".....","..#..",".....","....."}}, {'-', {".....",".....",".....","#####",".....",".....","....."}},
    {'/', {"....#","...#.","..#..",".#...","#....",".....","....."}}, {'!', {"..#..","..#..","..#..","..#..","..#..",".....","..#.."}},
    {'?', {".###.","#...#","....#","...#.","..#..",".....","..#.."}}, {')', {".#...","..#..","...#.","...#.","...#.","..#..",".#..."}},
    {'(', {"...#.","..#..",".#...",".#...",".#...","..#..","...#."}}, {'[', {"#####","#....","#....","#....","#....","#....","#####"}},
    {']', {"#####","....#","....#","....#","....#","....#","#####"}}, {' ', {".....",".....",".....",".....",".....",".....","....."}},
};

static const Glyph5x7* trouver_glyphe(char c) {
    size_t n = sizeof(FONT_5x7)/sizeof(FONT_5x7[0]);
    for (size_t i = 0; i < n; ++i) if (FONT_5x7[i].ch == c) return &FONT_5x7[i];
    return NULL;
}

static void dessiner_char(SDL_Renderer *ren, int x, int y, int echelle, Uint8 r, Uint8 g, Uint8 b, char c) {
    const Glyph5x7 *glyphe = trouver_glyphe(c);
    if (!glyphe) return;

    SDL_SetRenderDrawColor(ren, r, g, b, 255);
    for (int row = 0; row < 7; ++row) {
        const char *ligne = glyphe->rows[row];
        for (int col = 0; col < 5; ++col) {
            if (ligne[col] == '#') {
                SDL_Rect pixel = { x + col*echelle, y + row*echelle, echelle, echelle };
                SDL_RenderFillRect(ren, &pixel);
            }
        }
    }
}

static void dessiner_texte(SDL_Renderer *ren, int x, int y, int echelle, Uint8 r, Uint8 g, Uint8 b, const char *texte) {
    if (!texte) return;
    int curseur = 0;
    for (size_t i = 0; i < strlen(texte); ++i) {
        char c = (char)toupper((unsigned char)texte[i]);
        dessiner_char(ren, x + curseur, y, echelle, r, g, b, c);
        curseur += 6 * echelle;
    }
}

static void dessiner_texte_centre(SDL_Renderer *ren, SDL_Rect rect, int echelle, Uint8 r, Uint8 g, Uint8 b, const char *texte) {
    if (!texte) return;
    int largeur = strlen(texte) * 6 * echelle;
    int hauteur = 7 * echelle;
    int tx = rect.x + (rect.w - largeur)/2;
    int ty = rect.y + (rect.h - hauteur)/2;
    dessiner_texte(ren, tx, ty, echelle, r, g, b, texte);
}

static void dessiner_barre_vie(SDL_Renderer *ren, int x, int y, int w, int h, int hp, int maxHp) {
    SDL_Rect fond = {x, y, w, h};
    SDL_SetRenderDrawColor(ren, 70, 0, 0, 255);
    SDL_RenderFillRect(ren, &fond);

    if (maxHp <= 0) maxHp = 1;
    float ratio = (float)hp / (float)maxHp;
    if (ratio < 0.0f) ratio = 0.0f;
    if (ratio > 1.0f) ratio = 1.0f;

    SDL_Rect barre = {x, y, (int)(w * ratio), h};
    if(ratio > 0.5f) SDL_SetRenderDrawColor(ren, 0, 200, 0, 255);
    else if(ratio > 0.2f) SDL_SetRenderDrawColor(ren, 200, 200, 0, 255);
    else SDL_SetRenderDrawColor(ren, 200, 0, 0, 255);

    SDL_RenderFillRect(ren, &barre);
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    SDL_RenderDrawRect(ren, &fond);
}

void interface_dessiner_tout(SDL_Renderer *ren) {
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderClear(ren);

    if (g_scene == SCENE_MENU) {
        SDL_SetRenderDrawColor(ren, 30, 30, 60, 255);
        SDL_RenderClear(ren);

        SDL_Rect b1={360,120,240,50}, b2={360,190,240,50}, b3={360,260,240,50}, b4={360,330,240,50};
        SDL_SetRenderDrawColor(ren, 80, 80, 160, 255); SDL_RenderFillRect(ren, &b1);
        SDL_SetRenderDrawColor(ren, 80, 160, 80, 255); SDL_RenderFillRect(ren, &b2);
        SDL_SetRenderDrawColor(ren, 160, 80, 80, 255); SDL_RenderFillRect(ren, &b3);
        SDL_SetRenderDrawColor(ren, 120, 120, 120, 255); SDL_RenderFillRect(ren, &b4);

        dessiner_texte_centre(ren, b1, 3, 255,255,255, "1. JOUER");
        dessiner_texte_centre(ren, b2, 3, 255,255,255, "2. SCORES");
        dessiner_texte_centre(ren, b3, 3, 255,255,255, "3. EDITEUR");
        dessiner_texte_centre(ren, b4, 3, 255,255,255, "4. QUITTER");

        char buf[128];
        snprintf(buf, 128, "CLASSE: %s  -  [C] CHANGER", g_joueur.name);
        dessiner_texte(ren, 20, 500, 2, 255, 255, 0, buf);
    }
    else if (g_scene == SCENE_EXPLORATION) {
        map_render(ren);
        dessiner_texte(ren, 10, 10, 2, 255, 255, 255, "EXPLORATION (UTILISEZ LES FLECHES)");
    }
    else if (g_scene == SCENE_COMBAT) {
        SDL_SetRenderDrawColor(ren, 20, 20, 20, 255);
        SDL_RenderClear(ren);

        dessiner_texte(ren, 50, 350, 2, 255, 255, 255, g_joueur.name);
        dessiner_barre_vie(ren, 50, 380, 200, 20, g_joueur.currentHp, g_joueur.maxHealth);

        char txtHp[32]; snprintf(txtHp, 32, "%d / %d", g_joueur.currentHp, g_joueur.maxHealth);
        dessiner_texte(ren, 50, 410, 2, 200, 200, 200, txtHp);

        dessiner_texte(ren, 600, 50, 2, 255, 100, 100, g_ennemiActuel.name);
        dessiner_barre_vie(ren, 600, 80, 200, 20, g_ennemiActuel.currentHp, g_ennemiActuel.maxHealth);

        SDL_Rect boiteLog = {200, 200, 560, 60};
        SDL_SetRenderDrawColor(ren, 50, 50, 80, 255);
        SDL_RenderDrawRect(ren, &boiteLog);
        dessiner_texte_centre(ren, boiteLog, 2, 255, 255, 255, g_logCombat);

        if (g_etatCombat == COMBAT_TOUR_JOUEUR) {
            SDL_Rect menuRect = { 350, 450, 260, 80 };
            SDL_SetRenderDrawColor(ren, 40, 40, 80, 255); SDL_RenderFillRect(ren, &menuRect);
            SDL_SetRenderDrawColor(ren, 255, 255, 255, 255); SDL_RenderDrawRect(ren, &menuRect);

            char buf[64];
            snprintf(buf, 64, "1. %s", g_joueur.moves[0].id ? g_joueur.moves[0].name : "---");
            dessiner_texte(ren, 360, 460, 2, 255, 255, 255, buf);

            snprintf(buf, 64, "2. %s", g_joueur.moves[1].id ? g_joueur.moves[1].name : "---");
            dessiner_texte(ren, 360, 485, 2, 200, 255, 200, buf);

            snprintf(buf, 64, "3. %s", g_joueur.moves[2].id ? g_joueur.moves[2].name : "---");
            dessiner_texte(ren, 360, 510, 2, 200, 255, 200, buf);
        }
    }
    else if (g_scene == SCENE_SCORES) {
        SDL_SetRenderDrawColor(ren, 20, 50, 20, 255);
        SDL_RenderClear(ren);

        dessiner_texte(ren, 50, 50, 3, 255, 215, 0, "MEILLEURS SCORES");

        int count = scores_count();
        if(count == 0) {
            dessiner_texte(ren, 50, 120, 2, 200, 200, 200, "AUCUN SCORE.");
        } else {
            for(int i=0; i<count; i++) {
                char ligne[64];
                HighscoreEntry e = scores_get(i);
                snprintf(ligne, 64, "%d. %s : %d", i+1, e.playerName, e.scoreValue);
                dessiner_texte(ren, 50, 120 + i*40, 2, 255, 255, 255, ligne);
            }
        }
        dessiner_texte(ren, 50, 450, 2, 200, 200, 200, "[ECHAP] RETOUR");
    }
    else if (g_scene == SCENE_SELECTION_CLASSE) {
        SDL_SetRenderDrawColor(ren, 20, 20, 40, 255);
        SDL_RenderClear(ren);

        dessiner_texte(ren, 50, 50, 3, 255, 255, 255, "CHOISIR UNE CLASSE (1-9)");

        int count = get_class_count();
        for(int i=0; i<count; i++) {
            char ligne[64];
            snprintf(ligne, 64, "%d. %s", i+1, get_class_name(i));
            dessiner_texte(ren, 50, 120 + i*40, 2, 200, 200, 255, ligne);
        }
    }

    SDL_RenderPresent(ren);
}