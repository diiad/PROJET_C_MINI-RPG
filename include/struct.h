#ifndef STRUCT_H
#define STRUCT_H

typedef struct {
    int hp;
    int maxHp;
    int attack;
    int defense;
    float range;
    int agility;
} entity;


extern entity Goblin;
extern entity Orc;
extern entity Skeleton;
extern entity Troll;
extern entity enemies[4];
extern int enemyCount;

void initEnemies(void);
void showEntity(entity e);
int attack_classic(entity *attacker, entity *target);
void startCombat(entity *player, entity *enemy);
entity randomEnemy();
void resetEntity(entity *e);



#endif