#ifndef LOGIC_H
#define LOGIC_H

#include "struct.h"
#include "moves.h"

// Prépare le combat
void logic_preparer_combat(void);

// Résout une attaque
void logic_resoudre_action(entity *attaquant, entity *cible, const Move *coup);

// Met à jour le jeu
void logic_update(void);

#endif