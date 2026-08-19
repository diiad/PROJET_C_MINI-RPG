#ifndef STRUCT_H
#define STRUCT_H

/* Types d'actions possibles pour les attaques */
typedef enum { ACT_PHYSIQUE=0, ACT_SOIN=1, ACT_MAGIE=2 } ActionType;

/* Données d'une attaque */
typedef struct {
    int id;
    char name[32];
    ActionType type;
    int attackStrength;
    int hitRate;
} Move;

/* Représente une entité du jeu */
typedef struct {
    char name[32];
    int currentHp;
    int maxHealth;
    int attackPower;
    int defensePower;
    float attackRange;
    int agilityStat;

    Move moves[3];
} entity;

// ennemis pré-définis
extern entity Goblin;
extern entity Orc;
extern entity Skeleton;
extern entity Troll;
extern entity enemies[4];
extern int enemyCount;


void initEnemies(void);
entity randomEnemy();
void resetEntity(entity *e);

#endif