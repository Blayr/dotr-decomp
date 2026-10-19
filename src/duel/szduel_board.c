/* The duel screen, part 11 of 15: the board squares, card records, unit requests, duel and map set-up. */

#include "common.h"

/* Clears a board square's record. */
void SzDuel_InitMapInfo(void *cell) {
    *(s32 *)cell = 0;
    ((u8 *)cell)[6] = 0;
    ((u8 *)cell)[5] = 0;
    ((u8 *)cell)[4] = 0;
    ((u8 *)cell)[7] = 0;
    ((u8 *)cell)[0xA] = 0;
    ((u8 *)cell)[9] = 0;
    ((u8 *)cell)[8] = 0;
    ((u8 *)cell)[0xB] = 0;
    ((u8 *)cell)[0xE] = 0;
    ((u8 *)cell)[0xD] = 0;
    ((u8 *)cell)[0xC] = 0;
    ((u8 *)cell)[0xF] = 0;
    ((u8 *)cell)[0x12] = 0;
    ((u8 *)cell)[0x11] = 0;
    ((u8 *)cell)[0x10] = 0;
    ((u8 *)cell)[0x13] = 0;
    ((u8 *)cell)[0x16] = 0;
    ((u8 *)cell)[0x17] = 0;
    ((u8 *)cell)[0x18] = 0;
    ((u8 *)cell)[0x19] = 0;
    ((u8 *)cell)[0x1A] = 0x80;
    *(s16 *)((u8 *)cell + 0x14) = 0;
}

/* The record of board square (x, y), or NULL off the board. */
void *SzDuel_GetMapInfo(s32 x, s32 y) {
    if ((x < 0) || (x >= 7) || (y < 0) || (y >= 7)) {
        return NULL;
    }
    return (x * 0x1C) + (boardSquares + (y * 0xC4));
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
    extern u8 D_002BF080[];
    u8 *ret;

    if (card == 0x29F) {
        card = 0x3E7;
    }
    if (card < 0 || card >= 0x356) {
        ret = NULL;
    } else {
        ret = &D_002BF080[card * 0x14];
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
    return group * 0x3F4 + duelUnits + index * 0x5C;
}

extern u8 boardSquares[]; /* original: gSzDuel_aaMapInfo */

/* A board square's record, or NULL off the board. */
static inline u8 *cell_001DD220(s32 x, s32 y, u8 *cell) {
    if (x < 0 || x >= 7 || y < 0 || y >= 7) {
        return NULL;
    }
    return cell;
}

/* Runs the pending move/summon requests of every board square. */
void SzDuel_DoUnitRequest(void) {
    s32 x;
    s32 z;
    u8 *info;
    u8 *cell;
    u8 *row;

    row = boardSquares;
    z = 0;
    do {
        x = 0;
        cell = row;
        do {
            info = cell_001DD220(x, z, cell);
            lSzDuel_DoUnitRequest(info, *(s32 *)info);
            x += 1;
            cell += 0x1C;
        } while (x < 7);
        z += 1;
        row += 0xC4;
    } while (z < 7);
}

struct DotrStateItemBits {
    signed char unknown_bit_0 : 1;
    signed char unknown_bit_1 : 1;
    signed char unknown_bit_2 : 1;
    signed char unknown_bit_3 : 1;
    signed char unknown_bit_4 : 1;
    signed char unknown_bit_5 : 1;
    signed char unknown_bit_6 : 1;
    signed char unknown_bit_7 : 1;
};
struct DotrStateItemPairs {
    signed char unknown_bits_0_1 : 2;
    signed char unknown_bits_2_3 : 2;
    signed char unknown_bits_4_5 : 2;
    signed char unknown_bits_6_7 : 2;
};
struct DotrStateItemFlags {
    signed char unknown_bit_0 : 1;
    signed char unknown_bit_1 : 1;
    signed char unknown_bit_2 : 1;
    signed char unknown_bit_3 : 1;
    signed char unknown_bits_4_7 : 4;
};
struct DotrStateItemObject;
struct DotrStateItemSource {
    unsigned char unknown_00;
    unsigned char unknown_01;
    unsigned char unknown_02_low : 4;
    unsigned char unknown_02_high : 4;
    unsigned char unknown_03;
    unsigned short unknown_04;
    unsigned char unknown_06[2];
    unsigned short unknown_08;
    unsigned short unknown_0a;
};
struct DotrStateEntry8 {
    int unknown_words[2];
};
struct DotrStateItem {
    struct DotrStateItemSource *unknown_00;
    struct DotrStateItemObject *unknown_04; 
    struct DotrStateEntry8 unknown_08[5];
    int unknown_30;
    unsigned char unknown_34[4];
    short unknown_38;
    short unknown_3a;
    unsigned short unknown_3c;
    unsigned char unknown_3e;
    unsigned char unknown_3f;
    unsigned char unknown_40;
    unsigned char unknown_41;
    unsigned char unknown_42[2];
    unsigned char unknown_44;
    unsigned char unknown_45;
    unsigned char unknown_46;
    unsigned char unknown_47;
    unsigned char unknown_48;
    unsigned char unknown_49;
    unsigned char unknown_4a;
    unsigned char unknown_4b;
    unsigned char unknown_4c[2];
    unsigned char unknown_4e;
    unsigned char unknown_4f;
    unsigned char unknown_50;
    unsigned char unknown_51;
    unsigned char unknown_52;
    unsigned char unknown_53;
    unsigned char unknown_54;
    unsigned char unknown_55;
    struct DotrStateItemPairs unknown_56;
    struct DotrStateItemBits unknown_57;
    struct DotrStateItemFlags unknown_58;
    unsigned char unknown_59[3];
};
typedef char DotrStateItemMustBe5c[(sizeof(struct DotrStateItem) == 0x5c) ? 1 : -1];
struct DotrStateVector {
    float x, y, z;
    float unknown_w;
};
struct DotrStateCellQuad_1dd2d0 {
    unsigned char unknown_0;
    unsigned char unknown_1;
    unsigned char unknown_2;
    unsigned char unknown_3;
};
typedef int DotrStateWord_1dd2d0;
struct DotrStateCell_1dd2d0 {
    DotrStateWord_1dd2d0 unknown_00;
    struct DotrStateCellQuad_1dd2d0 unknown_04[4];
    short unknown_14;
    unsigned char unknown_16;
    unsigned char unknown_17;
    unsigned char unknown_18;
    unsigned char unknown_19;
    unsigned char unknown_1a;
};
typedef char DotrStateCellMustBe1c[(sizeof(struct DotrStateCell_1dd2d0) == 0x1c) ? 1 : -1];
struct DotrStateItemObject {
    struct DotrStateVector unknown_00;
    struct DotrStateVector unknown_10;
    unsigned char unknown_20[0x10];
    struct DotrStateVector unknown_30;
    struct DotrStateCellQuad_1dd2d0 unknown_40;
};
struct DotrUnitRequestObject {
    unsigned char unknown_00[0x14];
    int unknown_14;
    int unknown_18;
    unsigned char unknown_1c[0x14];
    struct DotrStateVector unknown_30;
    struct DotrStateCellQuad_1dd2d0 unknown_40;
};
extern int func_001AAF60_b(int a);
extern int func_001F2800_b(int index, int value);

/* Runs one board square's pending request. */
void lSzDuel_DoUnitRequest(void *cell_v, int unknown)
{
    struct DotrStateCell_1dd2d0 * cell = cell_v;
    struct DotrUnitRequestObject *o;
    struct DotrStateVector v;
    int mode;
    struct DotrStateItem *u = (struct DotrStateItem *)unknown;
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
    if (!u->unknown_57.unknown_bit_7) {
        if (!u->unknown_58.unknown_bit_1) {
            if (u->unknown_57.unknown_bit_0) {
                n = u->unknown_4c[1] - 4;
                n = n > 64 ? n : 64;
                u->unknown_4c[1] = n;
            } else {
                n = u->unknown_4c[1] + 4;
                n = n < 128 ? n : 128;
                u->unknown_4c[1] = n;
            }
        }
        if (u->unknown_56.unknown_bits_4_5) {
            d = u->unknown_56.unknown_bits_4_5;
            if ((d > 0 && u->unknown_54 >= 255) || (d < 0 && u->unknown_54 <= 0)) {
                u->unknown_56.unknown_bits_4_5 = 0;
            } else if (d > 0) {
                n = u->unknown_54 + 32;
                n = n < 255 ? n : 255;
                u->unknown_54 = n;
            } else {
                n = u->unknown_54 - 32;
                n = n > 0 ? n : 0;
                u->unknown_54 = n;
            }
        }
        if (u->unknown_56.unknown_bits_6_7) {
            d = u->unknown_56.unknown_bits_6_7;
            if ((d > 0 && u->unknown_55 >= 255) || (d < 0 && u->unknown_55 <= 0)) {
                u->unknown_56.unknown_bits_6_7 = 0;
            } else if (d > 0) {
                n = u->unknown_55 + 32;
                n = n < 255 ? n : 255;
                u->unknown_55 = n;
            } else {
                n = u->unknown_55 - 32;
                n = n > 0 ? n : 0;
                u->unknown_55 = n;
            }
        }
        n = u->unknown_56.unknown_bits_0_1;
        if ((n > 0 && u->unknown_52 >= u->unknown_50) || (n < 0 && u->unknown_52 <= 0)) {
            if (mode == 1) {
                u->unknown_4e = 1;
            } else {
                u->unknown_4e = 0;
            }
            u->unknown_56.unknown_bits_0_1 = 0;
        } else if (n > 0) {
            int t = u->unknown_52 + 8;
            t = t < u->unknown_50 ? t : u->unknown_50;
            u->unknown_52 = t;
        } else if (n < 0) {
            int t = u->unknown_52 - 8;
            t = t > 0 ? t : 0;
            u->unknown_52 = t;
        }
        o = (struct DotrUnitRequestObject *)u->unknown_04;
        if (o != 0) {
            if (u->unknown_58.unknown_bit_1) {
                level = 128;
            } else {
                level = cell->unknown_1a;
            }
            o->unknown_14 = -((u->unknown_55 << 14) / 255);
            if (u->unknown_44 == 0) {
                o->unknown_14 = o->unknown_14 + 0x8000;
            }
            o->unknown_18 = (u->unknown_54 << 15) / 255;
            n = (u->unknown_4c[1] * level) >> 7;
            o->unknown_40.unknown_0 = n;
            o->unknown_40.unknown_1 = n;
            o->unknown_40.unknown_2 = n;
            if (u->unknown_4e & 1) {
                o->unknown_40.unknown_3 = u->unknown_52;
            }
            if (u->unknown_4e & 2) {
                f = (float)(unsigned)u->unknown_52 / 1280.0f;
                o->unknown_30.z = f;
                o->unknown_30.y = f;
                o->unknown_30.x = f;
            }
        }
    }
    if (u->unknown_45 >= 6) {
        return;
    }
    if (u->unknown_58.unknown_bit_0) {
        return;
    }
    flag = 0;
    if (SzModel_IsModelStandby(u->unknown_46)) {
        if (u->unknown_45 == 0) {
            flag = 1;
        } else if (u->unknown_57.unknown_bit_4) {
            flag = 1;
        }
    }
    if (flag) {
        n = u->unknown_56.unknown_bits_2_3;
        if ((n > 0 && u->unknown_53 >= u->unknown_51) || (n < 0 && u->unknown_53 <= 0)) {
            if (mode == 1) {
                u->unknown_4f = 1;
            } else {
                u->unknown_4f = 0;
            }
            u->unknown_56.unknown_bits_2_3 = 0;
        } else if (n > 0) {
            int t = u->unknown_53 + 8;
            t = t < u->unknown_51 ? t : u->unknown_51;
            u->unknown_53 = t;
        } else if (n < 0) {
            int t = u->unknown_53 - 8;
            t = t > 0 ? t : 0;
            u->unknown_53 = t;
        }
    }
    if (u->unknown_4f & 1) {
        func_001F2800_b(u->unknown_46, u->unknown_53);
    }
    if (u->unknown_4f & 2) {
        f = (float)(unsigned)u->unknown_53 / 128.0f;
        f = f < 1.0f ? f : 1.0f;
        v.z = f;
        v.y = f;
        v.x = f;
        SzModel_SetScale(u->unknown_46, &v);
    }
}

/* Turns the units on squares (x0, z0) and (x1, z1) to face each other. */
s32 SzDuel_TrimUnitDir(s32 x0, s32 z0, s32 x1, s32 z1) {
    u8 *first;
    u8 *second;
    s32 result;

    first = (u8 *)SzDuel_GetUnit(x0, z0);
    second = (u8 *)SzDuel_GetUnit(x1, z1);
    result = 0;
    if (first == second) {
        second = 0;
    }
    if (first != 0 && second != 0) {
        result |= SzDuel_TrimUnitDir2(x0, z0, second[0x40], second[0x41]);
        result |= SzDuel_TrimUnitDir2(x1, z1, first[0x40], first[0x41]);
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

typedef struct Flags_001DD990 {
    s8 unused : 1;
    s8 facing : 1;
    s8 remaining : 6;
} Flags_001DD990;

typedef struct State_001DD990 {
    u8 pad00[0x30];
    s32 angle;
    u8 pad34[0x23];
    Flags_001DD990 flags;
} State_001DD990;

/* Turns the unit on square (x, z) to face its side's way. */
s32 SzDuel_TrimUnitDir1(s32 x, s32 z) {
    State_001DD990 *state;
    s32 result;
    s32 target;
    s32 delta;

    state = (State_001DD990 *)SzDuel_GetUnit(x, z);
    result = 0;
    if (state != 0) {
        target = state->flags.facing ? 0x8000 : 0;
        if (state->angle != target) {
            delta = (target - state->angle) % 0x10000;
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
                    state->angle += delta;
                } else {
                    if (delta < -0x800) {
                        delta = -0x800;
                    }
                    state->angle += delta;
                }
                state->angle = (state->angle + 0x10000) % 0x10000;
                if (state->angle > 0x8000) {
                    state->angle -= 0x10000;
                }
            }
        }
        result = 1;
    }
    return result;
}

typedef struct Unit_001DDAC0 {
    u8 pad00[0x30];
    s32 rotation;
    s16 x;
    s16 y;
    u8 pad38[8];
    u8 grid_x;
    u8 grid_y;
    u8 pad42[2];
    u8 reversed;
} Unit_001DDAC0;

/* Turns the unit on square (x, z) towards square (targetX, targetZ). */
s32 SzDuel_TrimUnitDir2(s32 sx, s32 sz, s32 targetX, s32 targetZ) {
    extern s32 func_001A22C0(f32);
    Unit_001DDAC0 *self;
    Unit_001DDAC0 *target;
    s32 x;
    s32 result;
    s32 y;
    s32 difference;

    self = (Unit_001DDAC0 *)SzDuel_GetUnit(sx, sz);
    target = (Unit_001DDAC0 *)SzDuel_GetMapUnit(targetX, targetZ);
    x = func_001A22C0((f32)((targetX - 3) * 50));
    y = func_001A22C0((f32)((targetZ - 3) * 50));
    result = 0;
    if (self == target) {
        return SzDuel_TrimUnitDir1(sx, sz);
    }
    if (target != 0) {
        x += target->x;
        y += target->y;
    }
    if (self != 0) {
        f32 dx;
        f32 dy;
        s32 desired_angle;

        dx = (f32)x - ((f32)self->x + (f32)((self->grid_x - 3) * 50));
        dy = (f32)y - ((f32)self->y + (f32)((self->grid_y - 3) * 50));
        desired_angle = ((((self->reversed == 0 ? 0 : 0x8000) +
            func_001A22C0(65536.0f * (func_001A6C18(
                dy, dx) /
                6.2831855f)) + 0x400) >> 11) << 11);
        desired_angle += self->rotation;
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
                self->rotation += difference;
            } else {
                if (difference < -0x800) {
                    difference = -0x800;
                }
                self->rotation += difference;
            }
            self->rotation = (self->rotation + 0x10000) % 0x10000;
            if (self->rotation > 0x8000) {
                self->rotation -= 0x10000;
            }
            result = 1;
        }
    }
    return result;
}

extern u8 D_002BF080[];

/* The constant data of card `index`, or NULL. */
static inline u8 *lookup_001DDD80(s32 index) {
    if (index < 0 || index >= 0x356) {
        return NULL;
    }
    return D_002BF080 + index * 0x14;
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

extern u8 D_002CEE5C[][7][7];

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
                SzDuel_SetField(x, y, D_002CEE5C[map][y][x]);
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
