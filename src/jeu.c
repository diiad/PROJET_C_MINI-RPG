#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

#include "../include/jeu.h"
#include "../include/interface.h"
#include "../include/map.h"
#include "../include/scores.h"
#include "../include/classes.h"
#include "../include/moves.h"
#include "../include/inputs.h" // Pour inputs_traiter
#include "../include/logic.h"  // Pour logic_update

// --- VARIABLES GLOBALES ---
SceneJeu g_scene = SCENE_MENU;
EtatCombat g_etatCombat;
entity g_joueur;
entity g_ennemiActuel;
char g_logCombat[128];
int g_jeuActif = 1;
Uint32 g_timerFinTour = 0;
int g_indexClasseSelectionnee = 0;



void inputs_traiter(SDL_Event *e);
void logic_update(void);

/* Lance la boucle principale du jeu */
void lancer_jeu(void) {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    if (!interface_init(&window, &renderer)) {
        printf("Erreur init interface\n");
        return;
    }

    // Chargement des données
    srand((unsigned)time(NULL));
    load_moves_from_file("../assets/moves.json");
    load_classes_from_file("../assets/classes.json");
    initEnemies();
    map_init();
    map_spawn_random_enemy();
    scores_init("../assets/highscores.txt");

    // Init joueur
    apply_class_to_entity_by_index(&g_joueur, 0);

    SDL_Event event;
    while (g_jeuActif) {
        // INPUT
        while (SDL_PollEvent(&event)) {
            inputs_traiter(&event);
        }

        // UPDATE
        logic_update();


        interface_dessiner_tout(renderer);
    }

    interface_fermer(window, renderer);
}