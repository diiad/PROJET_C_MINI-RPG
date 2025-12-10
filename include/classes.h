#ifndef CLASSES_H
#define CLASSES_H

#include "struct.h"

typedef enum {
    CLASS_WARRIOR = 0,
    CLASS_ARCHER  = 1,
    CLASS_MAGE    = 2,
    CLASS_COUNT
} PlayerClass;


const char* class_name(PlayerClass c);


void get_class_entity(PlayerClass c, entity* out);


void apply_class_to_entity(entity* out, PlayerClass c);

#endif // CLASSES_H
