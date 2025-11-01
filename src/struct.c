#include "../include/struct.h"
#include <stdio.h>

entity Goblin = {
    .hp = 40,
    .attack = 50,
    .defense = 10,
    .range = 25
};

entity Orc = {
    .hp = 80,
    .attack = 80,
    .defense = 35,
    .range = 35
};



//Pour afficher une entity (pourquoi pas ?)
void showEntity(entity e) {
    printf("HP: %d | ATT: %d | DEF: %d | RANGE: %.1f\n", e.hp, e.attack, e.defense, e.range);
}


//proto fonction dégâts (peut etre évolué)
int attack_classic(entity *attacker, entity *target) {

    int damage = (int)(attacker->attack - (target->defense /2.5));

    if (damage < 0) {
        damage = 0;
    }

    target->hp -= damage;
    return damage;
}