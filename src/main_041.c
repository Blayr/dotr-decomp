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

void func_001C33A0(s32);

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
s32 func_00216AC0(s32, s32, s32);

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

INCLUDE_ASM("asm/nonmatchings/main_041", func_001C35A0);

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

INCLUDE_ASM("asm/nonmatchings/main_041", func_001C5980);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001C5B30);

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

INCLUDE_ASM("asm/nonmatchings/main_041", func_001C6130);

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

INCLUDE_ASM("asm/nonmatchings/main_041", func_001CD710);

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

INCLUDE_ASM("asm/nonmatchings/main_041", func_001CDAA0);

INCLUDE_ASM("asm/nonmatchings/main_041", func_001CDB00);
