#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_008", func_0012CE50);

INCLUDE_ASM("asm/nonmatchings/main_008", func_0012D270);

INCLUDE_ASM("asm/nonmatchings/main_008", func_0012D520);

s32 func_0012D960(s32 arg0, s32 *arg1, void *arg2, void *arg3) {
    s32 i;
    s32 *p;
    s32 *q;
    s32 j;
    s32 value;

    i = 0;
    if (i < func_0026FE20(arg0)) {
        p = arg1;
        do {
            if (func_001DE020(func_0026FCE0(*p) >> 5) == 2) {
                *((s8 *)arg3 + 6) = i;
                func_001DCD70(arg2, arg1[i]);
                return func_0026FCE0(arg1[i]) >> 5;
            }
            p++;
            i++;
        } while (i < func_0026FE20(arg0));
    }

    j = 0;
    if (j < func_0026FE20(arg0)) {
        q = arg1;
        do {
            if (func_0026FB10(arg0, *q) == 1) {
                value = *q;
                if (value == 0x31B || value == 0x2AC || value == 0x137) {
                    *((s8 *)arg3 + 6) = j;
                    func_001DCD70(arg2, arg1[j]);
                    return func_0026FCE0(arg1[j]) >> 5;
                }
            }
            q++;
            j++;
        } while (j < func_0026FE20(arg0));
    }
    return -1;
}

s32 func_0012DAE0(s32 arg0, s32 *arg1, void *arg2, void *arg3, s32 arg4) {
    s32 i;
    s32 *entry;
    s32 wanted;

    i = 0;
    if (i < func_0026FE20(arg0)) {
        wanted = arg4 & 0xFFFF;
        entry = arg1;
        do {
            if (func_0026FB10(arg0, *entry) == 1) {
                if (wanted == *entry && func_0026FB10(arg0, *entry) == 1) {
                    *((u8 *)arg3 + 6) = i;
                    func_001DCD70(arg2, arg1[i]);
                    return func_0026FCE0(arg1[i]) >> 5;
                }
            }
            entry++;
            i++;
        } while (i < func_0026FE20(arg0));
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/main_008", func_0012DBE0);

INCLUDE_ASM("asm/nonmatchings/main_008", func_0012DDE0);

INCLUDE_ASM("asm/nonmatchings/main_008", func_0012DFC0);

s32 func_0012E1A0(s32 arg0) {
    if ((func_0026FCE0(arg0) >> 5) != 0) {
        return 1;
    }
    return func_0026FC10(arg0) != 0 ? 1 : 0;
}

INCLUDE_ASM("asm/nonmatchings/main_008", func_0012E1F0);

INCLUDE_ASM("asm/nonmatchings/main_008", func_0012E3F0);

INCLUDE_ASM("asm/nonmatchings/main_008", func_0012E820);

INCLUDE_ASM("asm/nonmatchings/main_008", func_0012ED70);

INCLUDE_ASM("asm/nonmatchings/main_008", func_0012F350);

INCLUDE_ASM("asm/nonmatchings/main_008", func_0012F930);

INCLUDE_ASM("asm/nonmatchings/main_008", func_00130120);

INCLUDE_ASM("asm/nonmatchings/main_008", func_00130660);

s32 func_00130780(s32 arg0) {
    if (func_001DF470(arg0) > 0x7D0) {
        if (func_001E0150(arg0) >= 4) {
            return 0x2EE;
        } else {
            return 0x5DC;
        }
    } else {
        return 0x960;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_008", func_001307E0);

INCLUDE_ASM("asm/nonmatchings/main_008", func_00130940);

static inline s32 max_00130BB0(s32 a, s32 b) {
    if (a < b) {
        return b;
    }
    return a;
}

s32 func_00130BB0(s32 arg0, s32 arg1, s32 arg2, s32 arg3,
                  s32 arg4, s32 arg5) {
    s32 min_y;
    s32 min_x;

    min_y = arg3 < arg5 ? arg3 : arg5;
    arg5 = max_00130BB0(arg5, arg3);
    min_x = arg2 < arg4 ? arg2 : arg4;
    arg4 = max_00130BB0(arg4, arg2);
    if ((arg4 - min_x) + (arg5 - min_y) != 2) {
        return 0;
    }
    if (func_001DF540(arg0, arg1) == 0) {
        return 0;
    }
    if (func_001E2100(arg0, arg1, 0) == 0) {
        if (func_0024DF00(func_001E22B0(arg2, arg3), arg0, arg1) != 1) {
            return 0;
        }
        return 1;
    }
    return 0;
}

s32 func_00130CB0(void) {
    /* both really take (player, slot); the headers say (void) */
    s32 func_001E1580();
    s32 func_001E1640();
    s32 player;
    u8 count3;
    s32 i;
    u8 count1;
    u8 count2;
    s32 j;

    player = func_001DE540();
    count1 = 0;
    count3 = 0;
    for (i = 0; i < 11; i++) {
        if (func_001E1580(player, i) > 0 || func_001E1640(player, i) > 0 ||
            func_00250360(player, i) != player) {
            count1++;
        }
        if (func_001E1580(player == 0 ? 1 : 0, i) > 0 || func_001E1640(player == 0 ? 1 : 0, i) > 0 ||
            func_00250360(player == 0 ? 1 : 0, i) != player) {
            count1++;
        }
    }
    if (count1 >= 4) {
        return 0;
    }
    count2 = 0;
    for (j = 0; j < 11; j++) {
        if (func_00250360(player, j) != player) {
            count2++;
        }
        if (func_00250360(player == 0 ? 1 : 0, j) != player) {
            count2++;
        }
    }
    for (j = 0; j < 11; j++) {
        if (func_00250360(player, j) == player) {
            count3++;
        }
        if (func_00250360(player == 0 ? 1 : 0, j) == player) {
            count3++;
        }
    }
    if (count2 < 2 && count3 >= 4) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_008", func_00130E90);

INCLUDE_ASM("asm/nonmatchings/main_008", func_00131060);

INCLUDE_ASM("asm/nonmatchings/main_008", func_00131540);

INCLUDE_ASM("asm/nonmatchings/main_008", func_00131750);

INCLUDE_ASM("asm/nonmatchings/main_008", func_00131B30);

void func_00131DE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28) {
    func_0027DE20(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                  arg_sp0, arg_sp8, arg_sp10, arg_sp18, arg_sp20,
                  0, 0x708, arg_sp28);
}

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Nibbles_00131E40;

typedef struct {
    u16 position;
    u16 pad2;
    u16 state;
    u16 pad6;
    union {
        u32 value;
        u16 low;
    } data;
} State_00131E40;

s32 func_00131F80(s32, s32, s32);

void func_00131E40(void *arg0) {
    s32 occupied;
    s32 destination;
    State_00131E40 *state = arg0;
    Nibbles_00131E40 entries[12];
    s32 i;
    Nibbles_00131E40 *entry;
    u32 *kind;
    s32 result;
    u16 position;

    position = state->position;
    occupied = func_00250360(position >> 8, position & 0xFF);
    position = state->position;
    destination = func_001E1090(position >> 8, position & 0xFF);
    position = state->position;
    kind = func_001E0B70(position >> 8, position & 0xFF, 1);
    entry = entries;
    i = 0;
    do {
        entry->low = entry->high = 15;
        entry++;
        i++;
    } while (i < 12);
    if (kind != NULL && (*kind >> 8) == 8) {
        state->state = 0x2FF;
        state->data.value = state->data.low | ((occupied != 0 ? 0 : 1) << 24);
    } else {
        state->state = 0x6FF;
        position = state->position;
        result = func_00131F80(func_001DF540(position >> 8, position & 0xFF),
                              destination & 0xFF, destination >> 8);
        if (result >= 0) {
            state->data.value = (result << 16) | state->data.low;
        } else {
            state->state = 0x5FF;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/main_008", func_00131F80);

INCLUDE_ASM("asm/nonmatchings/main_008", func_00132280);

INCLUDE_ASM("asm/nonmatchings/main_008", func_00132460);

INCLUDE_ASM("asm/nonmatchings/main_008", func_001326F0);

s32 func_00132A10(s32 arg0, void *arg1, void *arg2, s32 arg3) {
    s32 values[8];
    s32 index;
    s32 *value;

    func_0026FD30(arg0, values);
    index = 0;
    if (index < func_0026FE20(arg0)) {
        value = values;
        do {
            if (((arg3 & 0xFFFF) == *value) && (func_0026FB10(arg0, *value) == 1)) {
                *((s8 *)arg1 + 6) = index;
                func_001DCD70(arg2, values[index]);
                return func_0026FCE0(values[index]) >> 5;
            }
            value++;
            index++;
        } while (index < func_0026FE20(arg0));
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/main_008", func_00132B00);

INCLUDE_ASM("asm/nonmatchings/main_008", func_00132D00);

INCLUDE_ASM("asm/nonmatchings/main_008", func_00132EE0);

s32 func_001330C0(s32 arg0) {
    if ((func_0026FCE0(arg0) >> 5) != 0) {
        return 1;
    }
    if ((arg0 == 0x23D) || (arg0 == 0x216) || (arg0 == 0x63)) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_008", func_00133130);

INCLUDE_ASM("asm/nonmatchings/main_008", func_00133320);

INCLUDE_ASM("asm/nonmatchings/main_008", func_001336A0);

INCLUDE_ASM("asm/nonmatchings/main_008", func_00133BE0);

INCLUDE_ASM("asm/nonmatchings/main_008", func_001341C0);

s32 func_001349A0(s32 arg0) {
    s32 row;
    s32 column;
    s32 position;

    for (row = 0; row < 7; row++) {
        if (row % 2 == 1) {
            column = 1;
            do {
                if (func_001E22B0(column, row) != 8) {
                    return (row << 8) | column;
                }
                column++;
            } while (column <= 5);
        }
    }

    for (row = 0; row < 7; row++) {
        column = 0;
        do {
            position = func_001E3790(row, column);
            if (position >= 0 &&
                arg0 != func_00250360(position >> 8, position & 0xFF) &&
                column < 3 &&
                func_001E22B0(6, 0) != 8 &&
                func_001E22B0(5, 0) != 8) {
                return 6;
            }
            column++;
        } while (column <= 6);
    }

    return -1;
}

s32 func_00134AE0(s32 arg0) {
    if (func_001DF470(arg0) > 0x3E8) {
        if (func_001E0150(arg0) >= 4) {
            return 0x2EE;
        } else {
            return 0x5DC;
        }
    } else {
        return 0x6A4;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_008", func_00134B40);

static inline s32 min_00134F00(s32 a, s32 b) {
    if (a < b) {
        return a;
    }
    return b;
}

static inline s32 max_00134F00(s32 a, s32 b) {
    if (a < b) {
        return b;
    }
    return a;
}

s32 func_00134F00(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 min_y;
    s32 min_x;

    min_y = min_00134F00(arg3, arg5);
    arg5 = max_00134F00(arg5, arg3);
    min_x = min_00134F00(arg2, arg4);
    arg4 = max_00134F00(arg4, arg2);
    if ((arg4 - min_x) + (arg5 - min_y) != 2) {
        return 0;
    }
    if (func_001DF540(arg0, arg1) == 0) {
        return 0;
    }
    if (func_001E2100(arg0, arg1, 0) == 0) {
        return func_0024DF00(func_001E22B0(arg2, arg3), arg0, arg1) != 1 ? 0 : 1;
    }
    return 0;
}

s32 func_00135000(s32 arg0, s32 arg1) {
    s32 sp20[4];

    func_00254C90(sp20, *(s32 *)((u8 *)func_0026FC90(arg1, 0) + 4));
    if (func_00254890(sp20, arg0) < 0) {
        return 0;
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_008", func_00135060);

INCLUDE_ASM("asm/nonmatchings/main_008", func_00135230);
