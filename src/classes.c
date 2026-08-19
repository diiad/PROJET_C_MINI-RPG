#include "../include/classes.h"
#include "../include/moves.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    ClassDef def;
    int moveIds[3];
} ClassData;

static ClassData g_classes_data[32];
static int g_class_count = 0;

void apply_class_to_entity_by_index(entity* out, int index) {
    if (!out || index < 0 || index >= g_class_count) return;

    ClassData* cd = &g_classes_data[index];

    out->maxHealth = cd->def.hp;
    out->currentHp = cd->def.hp;
    out->attackPower = cd->def.attack;
    out->defensePower = cd->def.defense;
    out->attackRange = cd->def.range;
    out->agilityStat = cd->def.agility;

    for(int i=0; i<3; i++) {
        int mid = cd->moveIds[i];
        if(mid > 0) {
            out->moves[i] = get_move_by_id(mid);
        } else {
            out->moves[i] = get_default_move();
        }
    }
}

const char* get_class_name(int index) {
    if (index < 0 || index >= g_class_count) return "Inconnu";
    return g_classes_data[index].def.name;
}
int get_class_count(void) { return g_class_count; }

int load_classes_from_file(const char* path) {
    g_class_count = 0;
    FILE* f = fopen(path, "rb");
    if (!f) return 0;

    fseek(f, 0, SEEK_END); long len = ftell(f); fseek(f, 0, SEEK_SET);
    char* buf = (char*)malloc(len + 1);
    fread(buf, 1, len, f); buf[len] = '\0'; fclose(f);

    char* p = buf;
    while (*p && g_class_count < 32) {
        char* obj = strchr(p, '{');
        if (!obj) break;
        char* end = strchr(obj, '}');
        if (!end) break;

        char temp[512];
        size_t dist = end - obj;
        if(dist > 511) dist = 511;
        strncpy(temp, obj, dist); temp[dist] = '\0';

        ClassData* cd = &g_classes_data[g_class_count];
        cd->def.range = 0; cd->moveIds[0]=1; cd->moveIds[1]=0; cd->moveIds[2]=0;

        char* t;
        if ((t = strstr(temp, "\"name\""))) {
            sscanf(t, "\"name\"%*[^\"]\"%[^\"]", cd->def.name);
        }
        if ((t = strstr(temp, "\"hp\""))) sscanf(t, "\"hp\"%*[^0-9]%d", &cd->def.hp);
        if ((t = strstr(temp, "\"attack\""))) sscanf(t, "\"attack\"%*[^0-9]%d", &cd->def.attack);
        if ((t = strstr(temp, "\"defense\""))) sscanf(t, "\"defense\"%*[^0-9]%d", &cd->def.defense);
        if ((t = strstr(temp, "\"agility\""))) sscanf(t, "\"agility\"%*[^0-9]%d", &cd->def.agility);
        if ((t = strstr(temp, "\"range\""))) sscanf(t, "\"range\"%*[^0-9.]%f", &cd->def.range);

        if ((t = strstr(temp, "\"moves\""))) {
            char* bracket = strchr(t, '[');
            if(bracket) {
                sscanf(bracket+1, "%d , %d , %d", &cd->moveIds[0], &cd->moveIds[1], &cd->moveIds[2]);
            }
        }

        g_class_count++;
        p = end + 1;
    }
    free(buf);
    return g_class_count;
}