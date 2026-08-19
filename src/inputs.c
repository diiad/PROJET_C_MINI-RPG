#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/jeu.h"
#include "../include/map.h"
#include "../include/classes.h"
#include "../include/scores.h"

void logic_preparer_combat(void);
void logic_resoudre_action(entity *attaquant, entity *cible, const Move *coup);

static void handle_menu(SDL_Keycode key) {
    if (key == SDLK_1) {
        apply_class_to_entity_by_index(&g_joueur, g_indexClasseSelectionnee);
        g_scene = SCENE_EXPLORATION;
    }
    if (key == SDLK_2) g_scene = SCENE_SCORES;
    if (key == SDLK_3) {
        #ifdef _WIN32
            system("start RPG_C_Editor.exe");
        #else
            system("./RPG_C_Editor &");
        #endif
    }
    if (key == SDLK_4) g_jeuActif = 0;
    if (key == SDLK_c) g_scene = SCENE_SELECTION_CLASSE;
}

static void handle_exploration(SDL_Keycode key) {
    int deltaX=0, deltaY=0;
    if(key == SDLK_UP) deltaY=-1;
    if(key == SDLK_DOWN) deltaY=1;
    if(key == SDLK_LEFT) deltaX=-1;
    if(key == SDLK_RIGHT) deltaX=1;

    if(deltaX!=0 || deltaY!=0) {
        int res = map_move_player(deltaX, deltaY);
        if(res == 2) {
            logic_preparer_combat();
            g_scene = SCENE_COMBAT;
        }
    }
}

static void handle_combat(SDL_Keycode key) {
    if (g_etatCombat == COMBAT_TOUR_JOUEUR) {
        int moveIndex = -1;
        if(key == SDLK_1) moveIndex=0;
        if(key == SDLK_2) moveIndex=1;
        if(key == SDLK_3) moveIndex=2;

        if (moveIndex != -1 && g_joueur.moves[moveIndex].id != 0) {
            logic_resoudre_action(&g_joueur, &g_ennemiActuel, &g_joueur.moves[moveIndex]);

            if (g_ennemiActuel.currentHp <= 0) {
                g_etatCombat = COMBAT_VICTOIRE;
                int scoreEarned = 100 + g_joueur.currentHp;
                scores_submit(g_joueur.name, scoreEarned);
                snprintf(g_logCombat, sizeof(g_logCombat), "VICTOIRE ! (ESPACE)");
            } else {
                g_etatCombat = COMBAT_TOUR_ENNEMI;
                g_timerFinTour = SDL_GetTicks() + 1000;
            }
        }
    }
    else if (g_etatCombat == COMBAT_VICTOIRE || g_etatCombat == COMBAT_DEFAITE) {
        if (key == SDLK_SPACE) {
            if(g_etatCombat == COMBAT_VICTOIRE) {
                g_scene = SCENE_EXPLORATION;
                map_spawn_random_enemy();
            } else {
                g_scene = SCENE_MENU;
            }
        }
    }
}

static void handle_classe_selection(SDL_Keycode key) {
    if (key >= SDLK_1 && key <= SDLK_9) {
        int idx = key - SDLK_1;
        if (idx < get_class_count()) {
            g_indexClasseSelectionnee = idx;
            apply_class_to_entity_by_index(&g_joueur, g_indexClasseSelectionnee);
            g_scene = SCENE_MENU;
        }
    }
}

void inputs_traiter(SDL_Event *event) {
    if (event->type == SDL_QUIT) g_jeuActif = 0;
    if (event->type == SDL_KEYDOWN) {
        if (event->key.keysym.sym == SDLK_ESCAPE) {
            if (g_scene == SCENE_MENU) g_jeuActif = 0;
            else g_scene = SCENE_MENU;
            return;
        }

        switch(g_scene) {
            case SCENE_MENU:             handle_menu(event->key.keysym.sym); break;
            case SCENE_SELECTION_CLASSE: handle_classe_selection(event->key.keysym.sym); break;
            case SCENE_EXPLORATION:      handle_exploration(event->key.keysym.sym); break;
            case SCENE_COMBAT:           handle_combat(event->key.keysym.sym); break;
            default: break;
        }
    }
}