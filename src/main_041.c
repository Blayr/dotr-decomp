#include "common.h"

void func_001C2530(void) {

}

INCLUDE_ASM("asm/nonmatchings/main_041", func_001C2540);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001C2720);

typedef struct {
    u8 padding[0x6E0];
    u8 *first;
    u8 *second;
} State_001C32B0;


s32 func_001C32B0(void) {
    State_001C32B0 *state = (State_001C32B0 *)D_00317490;
    s32 var_s1;
    s32 var_a1;
    s32 var_a2;
    u8 *temp_a3;
    u8 *temp_t0;
    u8 temp_a0;
    u8 temp_a1;

    var_s1 = 0;
    var_a2 = 0;
    do {
        temp_a3 = state->first + var_a2;
        temp_a1 = *temp_a3;
        if (temp_a1 != 0) {
            temp_t0 = state->second + var_a2;
            temp_a0 = *temp_t0;
            if (temp_a0 != 0) {
                if ((temp_a1 & 0xFF) > (temp_a0 & 0xFF)) {
                    *temp_a3 = temp_a1 - temp_a0;
                    state->second[var_a2] = 0;
                } else {
                    *temp_t0 = temp_a0 - temp_a1;
                    state->first[var_a2] = 0;
                }
            }
        }
        var_a2 += 1;
    } while (var_a2 < 0x356);
    func_001C33A0(0);
    func_001C33A0(1);
    for (var_a1 = 0; var_a1 < 0x356; var_a1++) {
        var_s1 += state->first[var_a1];
        var_s1 += state->second[var_a1];
    }
    return var_s1;
}

typedef struct {
    u32 id : 31;
    u32 flag : 1;
    u32 position : 30;
    u32 state : 2;
} Entry_001C33A0;

typedef struct {
    u8 padding[0x6E0];
    u8 *counts0;
    u8 *counts1;
} State_001C33A0;

void *func_00214F00(s32, s32, s32);
s32 func_00215060(s32, u32, u32, s32);
void func_00216280(s32, u32, u32, s32);

void func_001C33A0(s32 player) {
    s32 id;
    s32 slot;
    Entry_001C33A0 *entry;
    u8 *counts;
    u8 *count;
    s32 opponent;
    State_001C33A0 *state;

    state = (State_001C33A0 *)D_00317490;
    if (player != 0) {
        counts = state->counts1;
    } else {
        counts = state->counts0;
    }
    id = 0;
    opponent = player ^ 1;
    do {
        count = counts + id;
        while (*count != 0) {
            if (func_00216AC0(opponent, id, -1) >= 9) {
                break;
            }
            slot = 0;
            do {
                entry = func_00214F00(player, id, slot);
                if (entry->id != 0 && entry->state == 3 &&
                    func_00215060(opponent, entry->id, entry->position, id) == 0) {
                    break;
                }
                slot++;
            } while (slot < 9);
            if (slot >= 9) {
                break;
            }
            func_00216280(opponent, entry->id, entry->position, id);
            func_00214FD0(entry);
            (*count)--;
        }
        id++;
    } while (id < 0x356);
}

typedef struct {
    u8 pad_000[0x6D8];
    s32 values[2];
    u8 pad_6E0[0x67C];
    s8 selection;
} State_001C3520;

void func_001C3520(s32 arg0) {
    State_001C3520 *state = (State_001C3520 *)D_00317490;
    s32 var_a1;
    void (*var_a3)(void);

    if (arg0 != 0) {
        var_a1 = state->values[1];
    } else {
        var_a1 = state->values[0];
    }
    if (arg0 != 0) {
        var_a3 = func_001BA710;
    } else {
        var_a3 = func_001BA630;
    }
    state->selection = arg0;
    func_00199BC0(var_a1, 0x356, 2, var_a3);
}

void func_001C3570(void) {
    func_00209D30(func_001C35A0(func_00209D20()));
}

typedef struct State_001C35A0 {
    u8 pad0[0x6D8];
    u16 *values0;
    u16 *values1;
    u8 pad1[0x5AA];
    u16 index0;
    u16 condition0;
    u16 index1;
    u16 condition1;
    s16 amount0;
    s16 amount1;
    u8 pad2[0x28];
    u8 mode0;
    u8 mode1;
    u8 pad3[0x9C];
    u8 side;
    u8 pad4;
    u8 selection0;
    u8 selection1;
} State_001C35A0;

s32 func_001C38E0(s32);
s32 func_001C3E20(s32, s32, s32, s32);
s32 func_001C5550(s32, s32, s32, s32, s32);
s32 func_001C5870(s32, s32, s32);
s32 func_001BDAF0(s32, s32, s32, s32, s32, s32, s32, s32);
extern u16 D_0031811C;

s32 func_001C35A0(s32 arg0) {
    State_001C35A0 *state = (State_001C35A0 *)D_00317490;
    s32 result;
    s32 next;
    extern s32 func_001C3D50();
    extern s32 func_001B8260();
    extern s32 func_001C5980();
    extern s32 func_001C5B30();
    extern s32 func_001C5CE0();

    next = func_001C3D50(func_001C38E0(func_001AEFD0(arg0, 2)), 0, 0);
    next = func_001C3E20(next, 0, 0, 0);
    if (D_0031811C != 0) {
        next = func_001C5550(next, 0, 0, 0, state->selection0);
    }
    if (state->amount0 != 0) {
        next = func_001B8260(next, 0, 0, 320, 448,
                            (u8)(((s16)state->amount0 << 6) / 320));
        state->side = 0;
        next = func_001BDAF0(next, state->values0[state->index0 + state->selection0],
                            state->amount0, 0, 0, 1, 1, 0);
    }
    if (!(state->mode0 != 4 && state->mode0 != 6 && state->mode0 != 7)) {
        next = func_001B8260(next, 0, 0, 320, 448, 64);
        next = func_001C5870(next, -160, 0);
    }
    result = func_001C3E20(next, 1, 0, 0);
    if (state->condition1 != 0) {
        result = func_001C5550(result, 1, 0, 0, state->selection1);
    }
    if (state->amount1 != 0) {
        result = func_001B8260(result, 320, 0, 320, 448,
                              (u8)(((s16)state->amount1 << 6) / 320));
        state->side = 1;
        result = func_001BDAF0(result, state->values1[state->index1 + state->selection1],
                              -state->amount1, 0, 1, 1, 1, 0);
    }
    if (!(state->mode1 != 4 && state->mode1 != 6 && state->mode1 != 7)) {
        result = func_001B8260(result, 320, 0, 320, 448, 64);
        result = func_001C5870(result, 160, 0);
    }
    if (state->mode0 == 5 || state->mode1 == 5) {
        result = func_001C5980(result, 0, 0);
    }
    if (state->mode0 == 6 || state->mode1 == 6) {
        result = func_001C5B30(result, 0, 0);
    }
    if (state->mode0 == 8 || state->mode1 == 8) {
        result = func_001C5CE0(result, 0, 0);
    }
    func_001FEAF0(0);
    return result;
}

INCLUDE_ASM("asm/nonmatchings/main_041", func_001C38E0);

void func_001C3D50(s32 arg0, s32 arg1, s32 arg2) {
    s32 text = (s32)&D_002BF00B;
    s32 x = arg1 + 0xE0;
    s32 y = arg2 + 0x20;
    s32 element;

    arg0 = func_001B62F0(arg0, x, y, 6, 1);
    element = func_001B4780(arg0, -1, 0x73, 4, x, y, 0x15, 2, 1);
    func_001B6F70(element, arg1 + 0x140, arg2 + 0x27, 2, 3,
                  func_0019BEF0((const char *)text), (s8 *)text, 0);
}

INCLUDE_ASM("asm/nonmatchings/main_041", func_001C3E20);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001C4B00);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001C5550);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001C5870);

void func_001C5980(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 func_001B0CE0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
    extern s32 *func_001FEAB0(s32);
    extern s32 func_001FE7D0(s32, s32, s32, s32, s32, void (*)(void));
    extern s32 func_001B6F70(s32, s32, s32, s32, s32, s32, s8 *, s32);
    u8 *state = D_00317490;
    s32 text = (s32)D_002BEF98;
    s8 *text2 = D_002BEF6F;
    s8 *text3 = D_002BEF73;
    s32 id;
    s32 *size;

    arg0 = func_001B0CE0(arg0, 2, -1, 0x7E, arg1 + 0x140, arg2 + 0x83, 0x140, 0xBA,
                         func_0019BEF0((char *)text), text, 0);
    id = func_0020F290(func_001FD680(arg0, 1, 0x7F, 0, 0x16));
    size = func_001FEAB0(1);
    id = func_001FE7D0(id, 1, arg1 + 0x140 - (size[3] >> 1), arg2 + 0x119 - (size[4] + 12), 0,
                       func_001FDFE0);
    func_001FEAF0(1);
    id = func_001B6F70(id, arg1 + 0xF0, arg2 + 0x119, 2, 3, func_0019BEF0((char *)text2), text2,
                       D_003181C6 != 0 ? 0 : (s32)D_002BE944);
    func_001B6F70(id, arg1 + 0x190, arg2 + 0x119, 2, 3, func_0019BEF0((char *)text3), text3,
                  state[0xD36] != 0 ? (s32)D_002BE944 : 0);
}

void func_001C5B30(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 func_001B0CE0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
    extern s32 *func_001FEAB0(s32);
    extern s32 func_001FE7D0(s32, s32, s32, s32, s32, void (*)(void));
    extern s32 func_001B6F70(s32, s32, s32, s32, s32, s32, s8 *, s32);
    u8 *state = D_00317490;
    s32 text = (s32)&D_002BF00B;
    s8 *text2 = D_002BEF6F;
    s8 *text3 = D_002BEF73;
    s32 id;
    s32 *size;

    arg0 = func_001B0CE0(arg0, 2, -1, 0x7D, arg1 + 0x140, arg2 + 0x8E, 0x140, 0xA4,
                         func_0019BEF0((char *)text), text, 0);
    id = func_0020F290(func_001FD680(arg0, 1, 0x7F, 0, 0x16));
    size = func_001FEAB0(1);
    id = func_001FE7D0(id, 1, arg1 + 0x140 - (size[3] >> 1), arg2 + 0x10E - (size[4] + 12), 0,
                       func_001FDFE0);
    func_001FEAF0(1);
    id = func_001B6F70(id, arg1 + 0xF0, arg2 + 0x10E, 2, 3, func_0019BEF0((char *)text2), text2,
                       D_003181C6 != 0 ? 0 : (s32)D_002BE944);
    func_001B6F70(id, arg1 + 0x190, arg2 + 0x10E, 2, 3, func_0019BEF0((char *)text3), text3,
                  state[0xD36] != 0 ? (s32)D_002BE944 : 0);
}

void func_001C5CE0(s32 arg0, s32 arg1, s32 arg2) {
    s32 text = (s32) &D_002BF040;
    s32 length = func_0019BEF0((const char *) text);

    func_001B0CE0(arg0, 2, -1, 0x80, arg1 + 0x140, arg2 + 0xA3,
                  0x140, 0x7A, length, text, 1);
}

INCLUDE_ASM("asm/nonmatchings/main_041", func_001C5D70);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001C5DB8);

void func_001C6120(void) {

}

s32 func_001C6130(void) {
    s32 result = func_001C6170(0);

    if (result != 0 || *(u8 *)0xA9C088 != 0) {
        return result;
    }
    return func_001C6170(1);
}

INCLUDE_ASM("asm/nonmatchings/main_041", func_001C6170);

void func_001C7430(void) {
    func_00209D30(func_001C7460(func_00209D20()));
}

INCLUDE_ASM("asm/nonmatchings/main_041", func_001C7460);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001C7790);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001C7C00);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001C7D20);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001C8590);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001C8690);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001C8DC0);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001C92C0);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001C9C60);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001CA0E0);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001CA450);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001CA7C0);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001CB6B0);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001CC380);

typedef struct {
    u8 enabled : 1;
} Flags_001CC4B0;

typedef struct {
    f32 data[4];
} Vec4_001CC4B0;

extern Vec4_001CC4B0 D_002914B0;
extern Vec4_001CC4B0 D_002914C0;

void func_001CC4B0(s32 arg0) {
    u8 *state = D_00317490;
    s32 i;
    Vec4_001CC4B0 vector0;
    Vec4_001CC4B0 vector1;

    vector0 = D_002914B0;
    vector1 = D_002914C0;
    i = 0;
    do {
        func_001F30B0(i, 0);
        i++;
    } while (i < 0x54);
    i = 0;
    do {
        func_001F30B0(i, 1);
        i++;
    } while (i < 5);
    i = 0;
    do {
        func_001F30B0(i + 0x4A, 1);
        i++;
    } while (i < 0xA);
    func_001F9D80(0, vector0.data);
    func_001FB360(0, vector1.data);
    *(s8 *)0xA9C08F = 3;
    *(s8 *)0xA9C090 = 3;
    *(s8 *)0xA9C091 = 0;
    ((Flags_001CC4B0 *)0xA9C092)->enabled = 0;
    func_001E2FC0(0, 0, 1, 0);
    state[0xD57] = 0x63;
    if (arg0 != 0) {
        *(u8 *)0xA9C08D = 5;
        *(u8 *)0xA9C08C = *(u8 *)0xA9C08D - 2;
    }
    state[0xD63] = 0;
}

void func_001CC610(void) {

}

INCLUDE_ASM("asm/nonmatchings/main_041", func_001CC620);

void func_001CCB80(void) {
    func_00209D30(func_001CCBB0(func_00209D20()));
}

INCLUDE_ASM("asm/nonmatchings/main_041", func_001CCBB0);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001CCEA0);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001CD560);

void func_001CD6E0(void) {
    func_00209D30(func_001CD710(func_00209D20()));
}

typedef struct Vec4_001CD710 {
    f32 x, y, z, w;
} Vec4_001CD710;

typedef struct Command_001CD710 {
    __int128 position;
    u8 pad10[0x33];
    u8 flags;
    u8 pad44[0x4C];
} Command_001CD710;

typedef struct Flags_001CD710 {
    s8 low : 6;
    s8 active : 1;
    s8 high : 1;
} Flags_001CD710;

typedef struct Object_001CD710 {
    u8 pad00[4];
    Command_001CD710 *command;
    u8 pad08[0x3C];
    u8 field44;
    u8 field45;
    u8 pad46[0x11];
    Flags_001CD710 flags;
} Object_001CD710;

s32 func_001AF180(s32);
s32 func_001D9F00(void *, s32);
s32 func_001DC790(s32, s32, f32 *, s32, s32);

s32 func_001CD710(s32 arg0) {
    Vec4_001CD710 position;
    Command_001CD710 command;
    u8 *base = D_00317490;
    u8 *selected = D_00317490 + D_003181E4 * 0x350;
    s32 original;
    s64 mode;
    s32 special;
    s32 value;
    s32 final_value;
    Object_001CD710 *object;
    extern s32 func_001F9D30();
    extern s32 func_001DBD30();
    extern s32 func_00208030();

    mode = func_001AAF60(1);
    original = arg0;
    switch (mode) {
    case 1:
    case 0:
        if (func_001F3130(0) == 0) {
            return original;
        }
        arg0 = func_00207FA0(arg0);
        arg0 = func_001D9A20(arg0);
        arg0 = func_001CDB00(arg0);
        arg0 = func_0020A0B0(arg0, 1);
        func_001E11B0(0, 0, &position.x);
        position.y = 0.0f;
        arg0 = func_001DC790(arg0, 0, &position.x, 0x80, 1);
        func_001E11B0(1, 0, &position.x);
        position.y = 0.0f;
        value = func_0020A0B0(func_001DC790(arg0, 1, &position.x, 0x80, 1), 0);
        if (*(Object_001CD710 **)(base + 0x6C8) != NULL) {
            if ((*(Object_001CD710 **)(base + 0x6C8))->flags.active != 0) {
                special = 0;
                if (base[0xD57] == 0x1D && func_001FA6F0(-1, -1) != NULL) {
                    special = 1;
                }
                if (special != 0) {
                    position = *(Vec4_001CD710 *)func_001F9D30(0);
                } else {
                    func_001E10F0(selected[0x33D], selected[0x33E], 0, &position);
                }
                position.y = 1.0f;
                object = *(Object_001CD710 **)(base + 0x6C8);
                if (object->field45 == 0) {
                    value = func_0020A0B0(value, 1);
                    value = func_001DC790(value, (*(Object_001CD710 **)(base + 0x6C8))->field44, &position.x, 0x40, 0);
                    value = func_0020A0B0(value, 0);
                } else if (object->command != NULL) {
                    command = *object->command;
                    command.flags = ((s32)command.flags << 6) >> 7;
                    *(__int128 *)&command = *(__int128 *)&position;
                    object = func_001D9F00(&command, 1) ? object : NULL;
                    value = func_001DBC40(value, (s32)object, &command);
                    value = func_0020A0B0(value, 1);
                    value = func_001DBD30(value, &command);
                    value = func_0020A0B0(value, 0);
                }
            }
        }
        final_value = func_001D9E00(func_001AF180(value));
        return func_00208030(final_value, original, func_00207500(), 0xFFFFFF);
    default:
        return original;
    }
}

void func_001CDA10(void) {
    u8 *entry;
    s32 i;

    entry = D_003193C0;
    i = 0;
    do {
        func_001CDA60(entry);
        i += 1;
        entry += 0xA0;
    } while (i < 0x20);
}

s32 func_001CDA60(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    func_001CD560();
    *(s32 *)((u8 *)arg0 + 0x90) = 0;
    return 1;
}

void func_001CD560();

typedef struct {
    u8 pad_00[0x90];
    s32 in_use;
    u8 pad_94[0xC];
} Slot_001CDAA0;

u8 *func_001CDAA0(void) {
    s32 i;
    Slot_001CDAA0 *slot;

    slot = (Slot_001CDAA0 *)D_003193C0;
    i = 0;
    do {
        if (slot->in_use == 0) {
            func_001CD560(slot);
            return (u8 *)slot;
        }
        i += 1;
        slot++;
    } while (i < 0x20);
    return NULL;
}

typedef struct {
    s8 unused : 4;
    u8 mode : 2;
    s8 unused6 : 1;
    s8 set : 1;
} Flags_001CDB00;

typedef struct {
    u8 r, g, b, a;
} Color_001CDB00;

typedef struct {
    f32 value;
} PackedColor_001CDB00;

typedef union {
    struct {
        f32 x, y, z, w;
    } value;
    __int128 quad;
} Vector_001CDB00;

typedef struct {
    Vector_001CDB00 position;
    u8 pad10[0x33];
    u8 visible;
    Color_001CDB00 color;
    u8 pad48[0x39];
    Flags_001CDB00 flags81;
    u8 pad82;
    Flags_001CDB00 flags83;
    u8 pad84[0xC];
} Draw_001CDB00;

typedef struct {
    u8 pad00[0x34];
    s16 x, z;
    u8 pad38[8];
    u8 index40, index41;
    u8 pad42[7];
    u8 color49, color4A;
    u8 pad4B[0xC];
    Flags_001CDB00 flags57;
} Unit_001CDB00;

typedef struct {
    Draw_001CDB00 draw;
    Unit_001CDB00 *unit;
    u8 pad94[0xC];
} Entry_001CDB00;

s32 func_001D9F00(void *, s32);
extern f32 D_002914D8;

s32 func_001CDB00(s32 arg0) {
    Draw_001CDB00 draw;
    PackedColor_001CDB00 color;
    Entry_001CDB00 *entry;
    s32 i;
    void *position;
    s32 height;

    entry = (Entry_001CDB00 *)D_003193C0;
    i = 0;
    color = *(PackedColor_001CDB00 *)&D_002914D8;
    do {
        if (entry->unit != NULL) {
            Unit_001CDB00 *unit = entry->unit;

            position = func_001DCD00(unit->index40, unit->index41);
            draw = entry->draw;
            if (!draw.flags83.set && (!draw.flags81.set || draw.visible != 0)) {
                if (!unit->flags57.set) {
                    if (position != NULL) {
                        height = *(s16 *)((u8 *)position + 0x14);
                        height = height > 0 ? height : 0;
                        draw.position.value.y = (f32)(height * 35) / 128.0f;
                        if (unit->color49 != 0 || unit->color4A != 0) {
                            draw.flags83.mode = 3;
                            draw.color = *(Color_001CDB00 *)&color;
                        }
                    }
                    draw.position.value.x += (f32)unit->x;
                    draw.position.value.z += (f32)unit->z;
                }
                arg0 = func_001DBC40(arg0, (s32)(func_001D9F00(&draw, 1) ? unit : NULL), &draw);
                arg0 = func_0020A0B0(arg0, 1);
                arg0 = func_001DBD30(arg0, (s32)&draw);
                arg0 = func_0020A0B0(arg0, 0);
            }
        }
        i++;
        entry++;
    } while (i < 32);
    return arg0;
}
