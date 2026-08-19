#include <SDL2/SDL_timer.h>

#include "../../include/struct.h"
#include <stdio.h>
#include <stdlib.h>

int attack_classic(entity *attacker, entity *target) {
    int damage = attacker->attack - (target->defense / 2);
    if (damage < 0) damage = 0;
    target->hp -= damage;
    if (target->hp < 0) target->hp = 0;
    return damage;
}

void startCombat(entity *player, entity *enemy) {
    printf("\n=== Combat lancé ===\n");
    showEntity(*player);
    printf("\n");
    showEntity(*enemy);
    printf("\n");
    printf("\n");

    while (player->hp > 0 && enemy->hp > 0) {
        SDL_Delay(4000);
        int dmg = attack_classic(player, enemy);
        printf("Vous infligez %d dégâts. Ennemi HP: %d\n\n", dmg, enemy->hp);

        if (enemy->hp <= 0) {
            SDL_Delay(4000);
            printf("\nVictoire !\n\n");
            return;
        }


        SDL_Delay(1000);
        dmg = attack_classic(enemy, player);
        printf("L’ennemi riposte et inflige %d dégâts. Vos HP: %d\n\n", dmg, player->hp);

        if (player->hp <= 0) {
            SDL_Delay(4000);
            printf("\nDéfaite...\n");
            return;
        }
    }
}

int resolve_attack(entity *attacker, entity *target) {
    int dodgeChance = target->agility * 2;
    if (dodgeChance > 50) dodgeChance = 50; // Cap à 50%

    if ((rand() % 100) < dodgeChance) {
        return -1; // Code pour "Esquivé"
    }

    int damage = attacker->attack - (target->defense / 3);
    if (damage < 1) damage = 1;

    target->hp -= damage;
    if (target->hp < 0) target->hp = 0;

    return damage;
}