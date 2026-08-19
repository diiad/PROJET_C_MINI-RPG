#include "../include/scores.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static HighscoreEntry highscoreList[MAX_HIGHSCORES];
static int highscoreCount = 0;
static char highscoreFilePath[256];

void scores_init(const char* filepath) {
    strncpy(highscoreFilePath, filepath, 255);
    highscoreCount = 0;

    FILE* f = fopen(highscoreFilePath, "r");
    if (!f) return;

    while (highscoreCount < MAX_HIGHSCORES) {
        char playerNameBuffer[32];
        int scoreValue;
        if (fscanf(f, "%31s %d", playerNameBuffer, &scoreValue) == 2) {
            strcpy(highscoreList[highscoreCount].playerName, playerNameBuffer);
            highscoreList[highscoreCount].scoreValue = scoreValue;
            highscoreCount++;
        } else {
            break;
        }
    }
    fclose(f);
}

void scores_save(void) {
    if (strlen(highscoreFilePath) == 0) return;

    FILE* f = fopen(highscoreFilePath, "w");
    if (!f) {
        printf("Erreur: Impossible d'ecrire les scores dans %s\n", highscoreFilePath);
        return;
    }

    for (int i = 0; i < highscoreCount; i++) {
        fprintf(f, "%s %d\n", highscoreList[i].playerName, highscoreList[i].scoreValue);
    }
    fclose(f);
}

int scores_submit(const char* name, int score) {
    int insertPosition = -1;
    for (int i = 0; i < highscoreCount; i++) {
        if (score > highscoreList[i].scoreValue) {
            insertPosition = i;
            break;
        }
    }

    if (insertPosition == -1) {
        if (highscoreCount < MAX_HIGHSCORES) {
            insertPosition = highscoreCount;
        } else {
            return 0;
        }
    }

    for (int i = MAX_HIGHSCORES - 1; i > insertPosition; i--) {
        highscoreList[i] = highscoreList[i - 1];
    }

    strcpy(highscoreList[insertPosition].playerName, name);
    highscoreList[insertPosition].scoreValue = score;

    if (highscoreCount < MAX_HIGHSCORES) {
        highscoreCount++;
    }

    scores_save();
    return 1;
}

int scores_count(void) {
    return highscoreCount;
}

HighscoreEntry scores_get(int index) {
    if (index < 0 || index >= highscoreCount) {
        HighscoreEntry empty = {"-", 0};
        return empty;
    }
    return highscoreList[index];
}