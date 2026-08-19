#include "../include/struct.h"
#include "../include/moves.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

entity Goblin = { .currentHp=40, .maxHealth=40, .attackPower=15, .defensePower=5, .attackRange=5, .agilityStat=12 };
entity Orc =    { .currentHp=80, .maxHealth=80, .attackPower=25, .defensePower=15, .attackRange=5, .agilityStat=5 };
entity Skeleton={ .currentHp=60, .maxHealth=60, .attackPower=20, .defensePower=5, .attackRange=25,.agilityStat=10 };
entity Troll =  { .currentHp=120,.maxHealth=120,.attackPower=35, .defensePower=20, .attackRange=5, .agilityStat=2 };

entity enemies[4];
int enemyCount = 4;

void initEnemies() {
    strcpy(Goblin.name, "GOBELIN");
    Goblin.maxHealth = 40; Goblin.currentHp = 40;
    Goblin.attackPower = 12; Goblin.defensePower = 5; Goblin.agilityStat = 12; Goblin.attackRange = 5;
    Goblin.moves[0] = get_move_by_id(1);
    Goblin.moves[1] = get_move_by_id(5);
    Goblin.moves[2] = get_default_move();

    strcpy(Orc.name, "ORC");
    Orc.maxHealth = 80; Orc.currentHp = 80;
    Orc.attackPower = 20; Orc.defensePower = 10; Orc.agilityStat = 6; Orc.attackRange = 5;
    Orc.moves[0] = get_move_by_id(1);
    Orc.moves[1] = get_move_by_id(0);
    Orc.moves[2] = get_move_by_id(0);

    strcpy(Skeleton.name, "SQUELETTE");
    Skeleton.maxHealth = 50; Skeleton.currentHp = 50;
    Skeleton.attackPower = 18; Skeleton.defensePower = 5; Skeleton.agilityStat = 10; Skeleton.attackRange = 30;
    Skeleton.moves[0] = get_move_by_id(2);
    Skeleton.moves[1] = get_move_by_id(5);
    Skeleton.moves[2] = get_move_by_id(0);

    strcpy(Troll.name, "TROLL");
    Troll.maxHealth = 120; Troll.currentHp = 120;
    Troll.attackPower = 15; Troll.defensePower = 15; Troll.agilityStat = 2; Troll.attackRange = 10;
    Troll.moves[0] = get_move_by_id(1);
    Troll.moves[1] = get_move_by_id(4);
    Troll.moves[2] = get_move_by_id(0);

    enemies[0] = Goblin;
    enemies[1] = Orc;
    enemies[2] = Skeleton;
    enemies[3] = Troll;
}

entity randomEnemy() {
    int r = rand() % enemyCount;
    return enemies[r];
}

void resetEntity(entity *e) {
    e->currentHp = e->maxHealth;
}