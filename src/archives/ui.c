#include "../../include/struct.h"
#include <stdio.h>
#include <stdlib.h>

void showMenu(entity *player) {
    int choix;
    do {
        printf("========== Menu ==========\n");
        printf("1.  Combattre un ennemie\n");
        printf("2.  Voir mes statistiques\n");
        printf("3.  Quitter\n");
        printf("==========================\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        if (choix == 1) {
            entity enemy = randomEnemy();
            resetEntity(&enemy);
            startCombat(player, &enemy);
        }else if (choix == 2) {
            showEntity(*player);
        }else if (choix != 3) {
            printf("Choix invalide.");
        }
    }while (choix !=3);
        printf("A bientôt héros.");

}