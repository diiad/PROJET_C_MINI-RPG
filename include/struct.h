#ifndef STRUCT_H
#define STRUCT_H

typedef struct {
    int hp;
    int attack;
    int defense;
    float range;
    int agility;
} entity;


extern entity Goblin;
extern entity Orc;

void showEntity(entity e);
int attack_classic(entity *attacker, entity *target);

#endif