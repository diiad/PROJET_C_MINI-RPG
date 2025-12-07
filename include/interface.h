#ifndef INTERFACE_H
#define INTERFACE_H

void clearScreen();
void afficherMenuPrincipal();
int choixMenuPrincipal();

void afficherMenuClasses();
int choixClasse();

void afficherHUD(int hpJoueur, int hpEnnemi, int score);
void afficherMessage(const char *msg);

void afficherFin(int score);
int choixFin();

int lireChoix(int min, int  max);

#endif
