#include "../include/classes.h"
#include <string.h>

static void set_entity(entity* e, int hp, int attack, int defense, float range, int agility) {
    e->maxHp = hp;
    e->hp = hp;
    e->attack = attack;
    e->defense = defense;
    e->range = range;
    e->agility = agility;
}

const char* class_name(PlayerClass c) {
    switch (c) {
        case CLASS_WARRIOR: return "Guerrier";
        case CLASS_ARCHER:  return "Archer";
        case CLASS_MAGE:    return "Mage";
        default:            return "Inconnu";
    }
}

void get_class_entity(PlayerClass c, entity* out) {
    if (!out) return;
    switch (c) {
        case CLASS_WARRIOR:
            set_entity(out, /*hp*/140, /*att*/20, /*def*/40, /*range*/10.0f, /*agi*/8);
            break;
        case CLASS_ARCHER:
            set_entity(out, 100, 24, 20, 40.0f, 14);
            break;
        case CLASS_MAGE:
            set_entity(out, 80,  32, 15, 30.0f, 12);
            break;
        default:
            set_entity(out, 100, 20, 20, 20.0f, 10);
            break;
    }
}

void apply_class_to_entity(entity* out, PlayerClass c) {
    if (!out) return;
    get_class_entity(c, out);
    resetEntity(out);
}
