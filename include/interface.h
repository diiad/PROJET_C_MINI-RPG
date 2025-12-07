#ifndef INTERFACE_H
#define INTERFACE_H

// Point d'entrée unique de l'interface du jeu (UI SDL)
// Lance la boucle du jeu (menu, sélection de classe, combat, highscores, etc.).
// Retourne 0 en cas de succès, >0 en cas d'erreur d'initialisation.
int run_game(void);

#endif
