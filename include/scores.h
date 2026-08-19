#ifndef SCORES_H
#define SCORES_H

#define MAX_HIGHSCORES 5

typedef struct {
    char playerName[32];
    int scoreValue;
} HighscoreEntry;

void scores_init(const char* filepath);

/* Ajoute un score au classement */
int scores_submit(const char* name, int score);

/* Sauvegarde dans un fichier*/
void scores_save(void);

/* nombre de scores enregistrés */
int scores_count(void);

/* Renvoie une entrée du classement selon son id */
HighscoreEntry scores_get(int index);

#endif