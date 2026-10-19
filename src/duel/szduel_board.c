/* The duel screen, part 8 of 12: the board squares, card records, unit requests, duel and map set-up. */

#include "common.h"

/* Clears a board square's record. */
void SzDuel_InitMapInfo(void *cell) {
    MapInfo *info = cell;

    info->unit = NULL;
    info->TargetHighlight.r = 0;
    info->TargetHighlight.g = 0;
    info->TargetHighlight.b = 0;
    info->TargetHighlight.a = 0;
    info->Highlight.r = 0;
    info->Highlight.g = 0;
    info->Highlight.b = 0;
    info->Highlight.a = 0;
    info->TargetBorderOutline.r = 0;
    info->TargetBorderOutline.g = 0;
    info->TargetBorderOutline.b = 0;
    info->TargetBorderOutline.a = 0;
    info->BorderOutline.r = 0;
    info->BorderOutline.g = 0;
    info->BorderOutline.b = 0;
    info->BorderOutline.a = 0;
    info->field = 0;
    info->MapMovable = 0;
    info->TargetSelectionHighlight = 0;
    info->SelectionHighlightType = 0;
    info->mapAlpha = 0x80;
    info->fieldRate = 0;
}

/* The record of board square (x, y), or NULL off the board. */
void *SzDuel_GetMapInfo(s32 x, s32 y) {
    return SzDuel_MapInfo(x, y);
}

typedef struct Pair_001DCD70 {
    f32 x;
    f32 y;
} Pair_001DCD70;

typedef union Slot_001DCD70 {
    Pair_001DCD70 value;
    struct {
        s32 x;
        s32 y;
    } bits;
} Slot_001DCD70;

typedef struct State_001DCD70 {
    u8 *record;
    s32 field04;
    Slot_001DCD70 slots[5];
    s32 field30;
    s16 field34;
    s16 field36;
    s16 field38;
    s16 field3A;
    s16 id;
    u8 field3E;
    u8 field3F;
    u8 field40;
    u8 field41;
    u8 field42;
    u8 field43;
    u8 field44;
    u8 field45;
    u8 field46;
    u8 field47;
    u8 field48;
    u8 field49;
    u8 field4A;
    u8 field4B;
    u8 field4C;
    u8 field4D;
    u8 field4E;
    u8 field4F;
    u8 field50;
    u8 field51;
    u8 field52;
    u8 field53;
    u8 field54;
    u8 field55;
    s8 flag56_0 : 2;
    s8 flag56_1 : 2;
    s8 flag56_2 : 2;
    s8 flag56_3 : 2;
    s8 flag57_0 : 1;
    s8 flag57_1 : 1;
    s8 flag57_2 : 1;
    s8 flag57_3 : 1;
    s8 flag57_4 : 1;
    s8 flag57_5 : 1;
    s8 flag57_6 : 1;
    s8 flag57_7 : 1;
    s8 flag58_0 : 1;
    s8 flag58_1 : 1;
    s8 flag58_2 : 1;
    s8 flag58_3 : 1;
    s16 flag58_4 : 6;
} State_001DCD70;

extern Pair_001DCD70 D_002C9DF0[][5];
extern Pair_001DCD70 D_002CC5F0[];

/* Sets up a card record for card `card`: its constant data and starting values. */
void SzDuel_InitCardInfo(void *info, s32 card) {
    State_001DCD70 *state;
    s32 i;
    s32 *words;
    Pair_001DCD70 *source;
    s32 index;

    state = info;
    state->record = NULL;
    state->field04 = 0;
    i = 0;
    words = (s32 *)state;
    do {
        i++;
        words[2] = -1;
        words[3] = -1;
        words += 2;
    } while (i < 5);
    state->field30 = 0;
    state->field34 = 0;
    state->field36 = 0;
    state->field38 = 0;
    state->field3A = 0;
    state->id = 999;
    state->field3E = 0xFF;
    state->field3F = 0xFF;
    state->field40 = 7;
    state->field41 = 7;
    state->field42 = 7;
    state->field43 = 7;
    state->field44 = 2;
    state->field45 = 11;
    state->field46 = 84;
    state->field47 = 0;
    state->field48 = 0;
    state->field49 = 0;
    state->field4A = 0;
    state->field4B = 0;
    state->field4C = 0;
    state->field4D = 0x80;
    state->field4E = 1;
    state->field4F = 7;
    state->field50 = 0x80;
    state->field51 = 0x80;
    state->field52 = 0x80;
    state->field53 = 0;
    state->field54 = 0;
    state->field55 = 0;
    state->flag56_0 = 0;
    state->flag56_1 = 0;
    state->flag56_2 = 0;
    state->flag56_3 = 0;
    state->flag57_0 = 0;
    state->flag57_1 = 0;
    state->flag57_2 = 0;
    state->flag57_3 = 0;
    state->flag57_4 = 0;
    state->flag57_5 = 0;
    state->flag57_6 = 0;
    state->flag57_7 = 0;
    state->flag58_0 = 0;
    state->flag58_1 = 0;
    state->flag58_2 = 0;
    state->flag58_3 = 0;
    state->flag58_4 = 63;
    if (card == 0x29F) {
        card = 999;
    }
    if (card >= 0 && card < 0x356) {
        state->id = card;
        state->record = SzDuel_GetCardConstInfo(card);
        state->field3E = state->record[0];
        state->field3F = state->record[2] & 0xF;
        index = *(u16 *)(state->record + 4);
        if (index != 0xFFFF) {
            if (card >= 0x2AB) {
                state->slots[0].value = D_002CC5F0[index];
            } else {
                source = D_002C9DF0[index];
                i = 0;
                do {
                    state->slots[0].value = *source;
                    i++;
                    source++;
                    state = (State_001DCD70 *)((u8 *)state + 8);
                } while (i < 5);
            }
        }
    }
}

/* The constant data (20 bytes) of card `card`, or NULL for a bad id. */
u8 *SzDuel_GetCardConstInfo(s32 card) {
    extern u8 gSzDuel_CardConstInfo[];
    u8 *ret;

    if (card == 0x29F) {
        card = 0x3E7;
    }
    if (card < 0 || card >= 0x356) {
        ret = NULL;
    } else {
        ret = &gSzDuel_CardConstInfo[card * 0x14];
    }
    return ret;
}

/* Card record `index` of group `group`. */
void *SzDuel_GetCardInfo(s32 group, s32 index) {
    extern s32 SzModel_GetModelType();
    s32 type;
    s32 offset;

    if (group < 0) {
        type = SzModel_GetModelType(index);
        if (type < 0) {
            return NULL;
        }
        switch (type) {
        case 5:
            group = index - 30;
            index = 0;
            break;
        case 4:
            offset = index - 20;
            group = offset < 5 ? 0 : 1;
            index = offset % 5 + 1;
            break;
        default:
            return NULL;
        }
    }
    if (group < 0 || group >= 3 || index < 0 || index >= 11) {
        return NULL;
    }
    return &duelUnits[group][index];
}

/* Runs the pending move/summon requests of every board square. */
void SzDuel_DoUnitRequest(void) {
    s32 x;
    s32 z;
    MapInfo *info;
    MapInfo *cell;
    MapInfo *row;

    row = boardSquares[0];
    z = 0;
    do {
        x = 0;
        cell = row;
        do {
            info = SzDuel_MapInfoAt(x, z, cell);
            lSzDuel_DoUnitRequest(info, (s32)info->unit);
            x += 1;
            cell++;
        } while (x < 7);
        z += 1;
        row += 7;
    } while (z < 7);
}

extern int func_001AAF60_b(int a);
extern int func_001F2800_b(int index, int value);

/* Runs one board square's pending request. */
void lSzDuel_DoUnitRequest(void *cell_v, int unknown)
{
    MapInfo *cell = cell_v;
    CardRequest *o;
    Vec4f v;
    int mode;
    Unit *u = (Unit *)unknown;
    int n, flag;
    signed char d;
    unsigned char level;
    float f;
    mode = func_001AAF60_b(1);
    if (cell == 0) {
        return;
    }
    if (u == 0) {
        return;
    }
    if (!u->status.fCardBusy) {
        if (!u->modelStatusFlags.fCardColBusy) {
            if (u->status.fFinish) {
                n = u->CardHighlight - 4;
                n = n > 64 ? n : 64;
                u->CardHighlight = n;
            } else {
                n = u->CardHighlight + 4;
                n = n < 128 ? n : 128;
                u->CardHighlight = n;
            }
        }
        if (u->SomeStatusBitfield.nOpenFlip) {
            d = u->SomeStatusBitfield.nOpenFlip;
            if ((d > 0 && u->openRate >= 255) || (d < 0 && u->openRate <= 0)) {
                u->SomeStatusBitfield.nOpenFlip = 0;
            } else if (d > 0) {
                n = u->openRate + 32;
                n = n < 255 ? n : 255;
                u->openRate = n;
            } else {
                n = u->openRate - 32;
                n = n > 0 ? n : 0;
                u->openRate = n;
            }
        }
        if (u->SomeStatusBitfield.nDefenseFlip) {
            d = u->SomeStatusBitfield.nDefenseFlip;
            if ((d > 0 && u->defenseRate >= 255) || (d < 0 && u->defenseRate <= 0)) {
                u->SomeStatusBitfield.nDefenseFlip = 0;
            } else if (d > 0) {
                n = u->defenseRate + 32;
                n = n < 255 ? n : 255;
                u->defenseRate = n;
            } else {
                n = u->defenseRate - 32;
                n = n > 0 ? n : 0;
                u->defenseRate = n;
            }
        }
        n = u->SomeStatusBitfield.nCtlFlipC;
        if ((n > 0 && u->ctlRateC >= u->ctlGoalC) || (n < 0 && u->ctlRateC <= 0)) {
            if (mode == 1) {
                u->ctlModeC = 1;
            } else {
                u->ctlModeC = 0;
            }
            u->SomeStatusBitfield.nCtlFlipC = 0;
        } else if (n > 0) {
            int t = u->ctlRateC + 8;
            t = t < u->ctlGoalC ? t : u->ctlGoalC;
            u->ctlRateC = t;
        } else if (n < 0) {
            int t = u->ctlRateC - 8;
            t = t > 0 ? t : 0;
            u->ctlRateC = t;
        }
        o = u->cardModel;
        if (o != 0) {
            if (u->modelStatusFlags.fCardColBusy) {
                level = 128;
            } else {
                level = cell->mapAlpha;
            }
            o->rot.y = -((u->defenseRate << 14) / 255);
            if (u->team == 0) {
                o->rot.y = o->rot.y + 0x8000;
            }
            o->rot.z = (u->openRate << 15) / 255;
            n = (u->CardHighlight * level) >> 7;
            o->color.r = n;
            o->color.g = n;
            o->color.b = n;
            if (u->ctlModeC & 1) {
                o->color.a = u->ctlRateC;
            }
            if (u->ctlModeC & 2) {
                f = (float)(unsigned)u->ctlRateC / 1280.0f;
                o->scale.z = f;
                o->scale.y = f;
                o->scale.x = f;
            }
        }
    }
    if (u->slot >= 6) {
        return;
    }
    if (u->modelStatusFlags.fModelBusy) {
        return;
    }
    flag = 0;
    if (SzModel_IsModelStandby(u->modelId)) {
        if (u->slot == 0) {
            flag = 1;
        } else if (u->status.fOpenF) {
            flag = 1;
        }
    }
    if (flag) {
        n = u->SomeStatusBitfield.nCtlFlipM;
        if ((n > 0 && u->ctlRateM >= u->ctlGoalM) || (n < 0 && u->ctlRateM <= 0)) {
            if (mode == 1) {
                u->ctlModeM = 1;
            } else {
                u->ctlModeM = 0;
            }
            u->SomeStatusBitfield.nCtlFlipM = 0;
        } else if (n > 0) {
            int t = u->ctlRateM + 8;
            t = t < u->ctlGoalM ? t : u->ctlGoalM;
            u->ctlRateM = t;
        } else if (n < 0) {
            int t = u->ctlRateM - 8;
            t = t > 0 ? t : 0;
            u->ctlRateM = t;
        }
    }
    if (u->ctlModeM & 1) {
        func_001F2800_b(u->modelId, u->ctlRateM);
    }
    if (u->ctlModeM & 2) {
        f = (float)(unsigned)u->ctlRateM / 128.0f;
        f = f < 1.0f ? f : 1.0f;
        v.z = f;
        v.y = f;
        v.x = f;
        SzModel_SetScale(u->modelId, &v);
    }
}

/* Turns the units on squares (x0, z0) and (x1, z1) to face each other. */
s32 SzDuel_TrimUnitDir(s32 x0, s32 z0, s32 x1, s32 z1) {
    Unit *first;
    Unit *second;
    s32 result;

    first = (Unit *)SzDuel_GetUnit(x0, z0);
    second = (Unit *)SzDuel_GetUnit(x1, z1);
    result = 0;
    if (first == second) {
        second = 0;
    }
    if (first != 0 && second != 0) {
        result |= SzDuel_TrimUnitDir2(x0, z0, second->locCol, second->locRow);
        result |= SzDuel_TrimUnitDir2(x1, z1, first->locCol, first->locRow);
    } else {
        if (first != 0) {
            result |= SzDuel_TrimUnitDir1(x0, z0);
        }
        if (second != 0) {
            result |= SzDuel_TrimUnitDir1(x1, z1);
        }
    }
    return result;
}

/* Turns the unit on square (x, z) to face its side's way. */
s32 SzDuel_TrimUnitDir1(s32 x, s32 z) {
    Unit *state;
    s32 result;
    s32 target;
    s32 delta;

    state = (Unit *)SzDuel_GetUnit(x, z);
    result = 0;
    if (state != 0) {
        target = state->status.fRevolt ? 0x8000 : 0;
        if (state->VisualRelated != target) {
            delta = (target - state->VisualRelated) % 0x10000;
            if (delta < -0x7FFF) {
                delta += 0x10000;
            } else if (delta > 0x8000) {
                delta -= 0x10000;
            }
            if (delta != 0) {
                if (delta > 0) {
                    if (delta > 0x800) {
                        delta = 0x800;
                    }
                    state->VisualRelated += delta;
                } else {
                    if (delta < -0x800) {
                        delta = -0x800;
                    }
                    state->VisualRelated += delta;
                }
                state->VisualRelated = (state->VisualRelated + 0x10000) % 0x10000;
                if (state->VisualRelated > 0x8000) {
                    state->VisualRelated -= 0x10000;
                }
            }
        }
        result = 1;
    }
    return result;
}

/* Turns the unit on square (x, z) towards square (targetX, targetZ). */
s32 SzDuel_TrimUnitDir2(s32 sx, s32 sz, s32 targetX, s32 targetZ) {
    extern s32 func_001A22C0(f32);
    Unit *self;
    Unit *target;
    s32 x;
    s32 result;
    s32 y;
    s32 difference;

    self = (Unit *)SzDuel_GetUnit(sx, sz);
    target = (Unit *)SzDuel_GetMapUnit(targetX, targetZ);
    x = func_001A22C0((f32)((targetX - 3) * 50));
    y = func_001A22C0((f32)((targetZ - 3) * 50));
    result = 0;
    if (self == target) {
        return SzDuel_TrimUnitDir1(sx, sz);
    }
    if (target != 0) {
        x += target->xOffsetTerrain;
        y += target->yOffsetTerrain;
    }
    if (self != 0) {
        f32 dx;
        f32 dy;
        s32 desired_angle;

        dx = (f32)x - ((f32)self->xOffsetTerrain + (f32)((self->locCol - 3) * 50));
        dy = (f32)y - ((f32)self->yOffsetTerrain + (f32)((self->locRow - 3) * 50));
        desired_angle = ((((self->team == 0 ? 0 : 0x8000) +
            func_001A22C0(65536.0f * (func_001A6C18(
                dy, dx) /
                6.2831855f)) + 0x400) >> 11) << 11);
        desired_angle += self->VisualRelated;
        difference = -((desired_angle + 0x14000) % 0x10000);
        if (difference < -0x7FFF) {
            difference += 0x10000;
        } else if (difference > 0x8000) {
            difference -= 0x10000;
        }
        if (difference != 0) {
            if (difference > 0) {
                if (difference > 0x800) {
                    difference = 0x800;
                }
                self->VisualRelated += difference;
            } else {
                if (difference < -0x800) {
                    difference = -0x800;
                }
                self->VisualRelated += difference;
            }
            self->VisualRelated = (self->VisualRelated + 0x10000) % 0x10000;
            if (self->VisualRelated > 0x8000) {
                self->VisualRelated -= 0x10000;
            }
            result = 1;
        }
    }
    return result;
}

extern u8 gSzDuel_CardConstInfo[];

/* The constant data of card `index`, or NULL. */
static inline u8 *lookup_001DDD80(s32 index) {
    if (index < 0 || index >= 0x356) {
        return NULL;
    }
    return gSzDuel_CardConstInfo + index * 0x14;
}

/* Loads what a duel needs: the effects module, both leaders' models and the map's models. */
void SzDuel_SetupDuel(s32 arg0, s32 arg1, s32 arg2, void *arg3) {
    s32 leader;
    s32 side;
    s32 modelBase;
    u8 *info;

    SzEffect_LoadModule(0, 0x26C, 0, arg3);
    SzModel_LoadMerge(6, 0, 0);
    SzModel_LoadMerge(0, 0, 0);
    side = 0;
    modelBase = 0;
    do {
        leader = SzData_GetLeader(side, SzData_GetCurrentDeck(side));
        if (leader == 0x29F) {
            leader = 0x3E7;
        }
        info = lookup_001DDD80(leader);
        if (info != NULL) {
            SzModel_Load(side + 5, -1, (*info & 0x1F) + modelBase, 1);
        }
        side += 1;
        modelBase += 0x64;
    } while (side < 2);
}

extern u8 gSzDuel_MapData[][7][7];

typedef struct {
    u8 pad[0xFEA3];
    u8 maps[5][7][7];
} Maps_001DDE80;

/* Lays out the board's field types for map `map` (built-in maps, then the player's edited ones). */
void SzDuel_SetupMap(s32 map) {
    s32 y;
    s32 x;
    Maps_001DDE80 *maps;
    extern s32 SzDuel_SetField();

    if (map >= 0 && map < 0x2E) {
        for (y = 0; y < 7; y++) {
            for (x = 0; x < 7; x++) {
                SzDuel_SetField(x, y, gSzDuel_MapData[map][y][x]);
            }
        }
    } else if (map < 0x33) {
        maps = SzData_GetData(0);
        map -= 0x2E;
        for (y = 0; y < 7; y++) {
            for (x = 0; x < 7; x++) {
                SzDuel_SetField(x, y, maps->maps[map][y][x]);
            }
        }
    } else if (map < 0x38) {
        maps = SzData_GetData(1);
        map -= 0x33;
        for (y = 0; y < 7; y++) {
            for (x = 0; x < 7; x++) {
                SzDuel_SetField(x, y, maps->maps[map][y][x]);
            }
        }
    }
}
