#ifndef MOVES_H
#define MOVES_H

#include "struct.h"

// Charge les attaques depuis le JSON
int load_moves_from_file(const char* path);

// Récupère une attaque par son ID
Move get_move_by_id(int id);

// Remplit un tableau de moves par défaut si le chargement échoue
Move get_default_move(void);

#endif