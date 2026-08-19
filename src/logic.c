#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "../include/jeu.h"
#include "../include/struct.h"
#include "../include/scores.h"
#include "../include/logic.h"

void logic_preparer_combat(void) {
    g_ennemiActuel = randomEnemy();
    resetEntity(&g_ennemiActuel);

    if (g_joueur.agilityStat >= g_ennemiActuel.agilityStat) {
        g_etatCombat = COMBAT_TOUR_JOUEUR;
        snprintf(g_logCombat, sizeof(g_logCombat), "%s a l'initiative !", g_joueur.name);
    } else {
        g_etatCombat = COMBAT_TOUR_ENNEMI;
        g_timerFinTour = SDL_GetTicks() + 1000;
        snprintf(g_logCombat, sizeof(g_logCombat), "%s est plus rapide !", g_ennemiActuel.name);
    }
}

void logic_resoudre_action(entity *attaquant, entity *cible, const Move *coup) {
    if (!coup || coup->id == 0) return;

    if ((rand() % 100) > coup->hitRate) {
        snprintf(g_logCombat, sizeof(g_logCombat), "%s rate son coup !", attaquant->name);
        return;
    }

    if (coup->type == ACT_SOIN) {
        int soin = coup->attackStrength + (attaquant->maxHealth / 10);
        attaquant->currentHp += soin;
        if(attaquant->currentHp > attaquant->maxHealth) attaquant->currentHp = attaquant->maxHealth;
        snprintf(g_logCombat, sizeof(g_logCombat), "%s se soigne (+%d)", attaquant->name, soin);
        return;
    }

    int chanceEsquive = cible->agilityStat * 2;
    if ((rand() % 100) < chanceEsquive) {
        snprintf(g_logCombat, sizeof(g_logCombat), "%s esquive !", cible->name);
        return;
    }

    int degats = (attaquant->attackPower + coup->attackStrength) - (cible->defensePower / 3);
    if(degats < 1) degats = 1;
    cible->currentHp -= degats;
    if(cible->currentHp < 0) cible->currentHp = 0;

    snprintf(g_logCombat, sizeof(g_logCombat), "%s inflige %d degats !", attaquant->name, degats);
}

void logic_update(void) {
    if (g_scene == SCENE_COMBAT && g_etatCombat == COMBAT_TOUR_ENNEMI) {
        if (SDL_GetTicks() > g_timerFinTour) {
            Move attaqueBase = {999, "Attaque", ACT_PHYSIQUE, 0, 95};
            logic_resoudre_action(&g_ennemiActuel, &g_joueur, &attaqueBase);

            if (g_joueur.currentHp <= 0) {
                g_etatCombat = COMBAT_DEFAITE;
                snprintf(g_logCombat, sizeof(g_logCombat), "DEFAITE... (ESPACE)");
            } else {
                g_etatCombat = COMBAT_TOUR_JOUEUR;
            }
        }
    }
}