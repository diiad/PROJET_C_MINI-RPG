#ifndef JEU_H
#define JEU_H

#include <SDL2/SDL.h>
#include "struct.h" // Nécessaire pour connaître le type 'entity'

// --- ÉNUMÉRATIONS ---
typedef enum {
    SCENE_MENU,
    SCENE_EXPLORATION,
    SCENE_COMBAT,
    SCENE_SCORES,
    SCENE_SELECTION_CLASSE,
    SCENE_EDITEUR
} SceneJeu;

typedef enum {
    COMBAT_TOUR_JOUEUR,
    COMBAT_TOUR_ENNEMI,
    COMBAT_VICTOIRE,
    COMBAT_DEFAITE
} EtatCombat;

// --- VARIABLES GLOBALES ---
extern SceneJeu g_scene;
extern EtatCombat g_etatCombat;
extern entity g_joueur;
extern entity g_ennemiActuel;
extern char g_logCombat[128];
extern int g_jeuActif;
extern Uint32 g_timerFinTour;
extern int g_indexClasseSelectionnee;

// Fonction principale
void lancer_jeu(void);

#endif