#ifndef CLASSES_H
#define CLASSES_H

#include "struct.h"

// Définition d'une classe
typedef struct {
    char  name[64];
    int   hp;
    int   attack;
    int   defense;
    float range;
    int   agility;
} ClassDef;

// Chargement des classes depuis un j son
int load_classes_from_file(const char* path);

// Infos sur les classes chargées
int get_class_count(void);
const ClassDef* get_class_def(int index);
const char* get_class_name(int index);


void apply_class_to_entity_by_index(entity* out, int index);

// Copie les stats d'une classe par index
void get_class_entity_by_index(int index, entity* out);

#endif // CLASSES_H