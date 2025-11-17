#include <stdio.h>
#include <stdlib.h>
#include <../include/interface.h>


void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


int lireChoix(int min, int max) {
    int choix;

    while (1) {
        printf("> ");

        if (scanf("%d", &choix) == 1 && choix >= min && choix <= max) {
            while (getchar() != '\n');
            return choix;
        }

        printf("Choix invalide.\n");
        while (getchar() != '\n');
    }
}


void afficherMenuPrincipal() {
    clearScreen();
    printf("==== MINI RPG ====\n");
    printf("1. Jouer\n");
    printf("2. Choisir une classe\n");
    pritnf("3. Quitter\n");
    printf("===================\n");
}

int choixMenuPrincipal() {
    printf("Votre choix :\n");
    return lireChoix(1, 3);
}


void afficherMenuClasses() {
    clearScreen()
    printf("==== CHOIX DES CLASSES ====\n");
    printf("1. Guerrier (Tank)\n");
    printf("2. Archer (Distance)\n");
    printf("3. Mage (Dégât élevés)\n");
}

int choixClasse(){
    return lireChoix(1, 3);
}


void afficherHUD(int hpJoueur, int hpEnnemi, int score) {
    clearScreen();
    printf("==== COMBAT ====\n");
    printf("Vos HP : %d\n", hpJoueur);
    printf("HP Ennemi : %d\n", hpEnnemi);
    printf("Score : %d\n", score);
    printf("================\n");
}


void afficherMessage(const char *msg){
    printf("\n%s\n", msg);
}


void afficherFin(int score) {
    clearScreen();
    printf("==== FIN DE PARTIE ====\n");
    printf("Score final : %d\n", score);
    printf("1. Rejouer\n");
    printf("2. Retour menu principal\n");
    printf("3. Quitter\n");
}

int choixFin() {
    
}