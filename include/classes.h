#ifndef CLASSES_H
#define CLASSES_H

#include "struct.h"

typedef enum {
    CLASS_WARRIOR = 0,
    CLASS_ARCHER  = 1,
    CLASS_MAGE    = 2,
    CLASS_COUNT
} PlayerClass;

// Retourne le nom lisible de la classe
const char* class_name(PlayerClass c);

// Copie dans "out" les stats par défaut associées à la classe
void get_class_entity(PlayerClass c, entity* out);

// Applique la classe au joueur (équivaut à get_class_entity + reset des PV)
void apply_class_to_entity(entity* out, PlayerClass c);

#endif // CLASSES_H
