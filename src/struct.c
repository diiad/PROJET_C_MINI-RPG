#include "../include/struct.h"
#include <stdio.h>
#include <stdlib.h>

entity Goblin = {
    .hp = 40,
    .maxHp = 40,
    .attack = 21,
    .defense = 10,
    .range = 25
};

entity Orc = {
    .hp = 80,
    .maxHp = 80,
    .attack = 80,
    .defense = 35,
    .range = 35
};

entity Skeleton={
    .hp = 120,
    .maxHp = 120,
    .attack = 20,
    .defense = 50,
    .range =20
};

entity Troll={
    .hp = 120,
    .maxHp = 120,
    .attack = 20,
    .defense = 20,
    .range = 30
};

entity enemies[];

int enemyCount = 4;

void initEnemies() {
    enemies[0] = Goblin;
    enemies[1] = Orc;
    enemies[2] = Skeleton;
    enemies[3] = Troll;
}


//Pour afficher une entity (pourquoi pas ?)
void showEntity(entity e) {
    printf("HP: %d | ATT: %d | DEF: %d | RANGE: %.1f\n", e.hp, e.attack, e.defense, e.range);
}



entity randomEnemy() {
    int r = rand() % enemyCount;
    return enemies[r];
}


void resetEntity(entity *e) {
    e->hp = e->maxHp;
}

