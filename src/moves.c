#include "../include/moves.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Move moveRegistry[64];
static int moveCount = 0;

Move get_default_move(void) {
    Move m = {0, "Coup", ACT_PHYSIQUE, 10, 100};
    return m;
}

Move get_move_by_id(int id) {
    for(int i=0; i<moveCount; i++) {
        if (moveRegistry[i].id == id) return moveRegistry[i];
    }
    return get_default_move();
}

int load_moves_from_file(const char* path) {
    moveCount = 0;
    FILE* f = fopen(path, "rb");
    if (!f) return 0;

    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    fseek(f, 0, SEEK_SET);
    char* fileBuffer = (char*)malloc(len + 1);
    fread(fileBuffer, 1, len, f);
    fileBuffer[len] = '\0';
    fclose(f);

    char* cursor = fileBuffer;
    while (*cursor && moveCount < 64) {
        char* objectStart = strchr(cursor, '{');
        if (!objectStart) break;
        char* objectEnd = strchr(objectStart, '}');
        if (!objectEnd) break;

        int moveId=0, moveType=0, movePower=0, moveAccuracy=0;
        char moveName[32] = "Inconnu";

        char* fieldPtr;
        char objectData[256];
        int dist = (int)(objectEnd - objectStart);
        if(dist > 255) dist = 255;
        strncpy(objectData, objectStart, dist);
        objectData[dist] = '\0';

        if ((fieldPtr = strstr(objectData, "\"id\""))) sscanf(fieldPtr, "\"id\"%*[^0-9]%d", &moveId);
        if ((fieldPtr = strstr(objectData, "\"type\""))) sscanf(fieldPtr, "\"type\"%*[^0-9]%d", &moveType);
        if ((fieldPtr = strstr(objectData, "\"power\""))) sscanf(fieldPtr, "\"power\"%*[^0-9]%d", &movePower);
        if ((fieldPtr = strstr(objectData, "\"accuracy\""))) sscanf(fieldPtr, "\"accuracy\"%*[^0-9]%d", &moveAccuracy);

        if ((fieldPtr = strstr(objectData, "\"name\""))) {
            char* start_quote = strchr(fieldPtr + 6, '"');
            if(start_quote) {
                char* end_quote = strchr(start_quote + 1, '"');
                if(end_quote) {
                    size_t l = end_quote - (start_quote + 1);
                    if(l > 31) l = 31;
                    strncpy(moveName, start_quote + 1, l);
                    moveName[l] = '\0';
                }
            }
        }

        Move m;
        m.id = moveId;
        m.type = (ActionType)moveType;
        m.attackStrength = movePower;
        m.hitRate = moveAccuracy;
        strcpy(m.name, moveName);

        moveRegistry[moveCount++] = m;
        cursor = objectEnd + 1;
    }

    free(fileBuffer);
    return moveCount;
}