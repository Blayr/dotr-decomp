#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_007", func_00124610);

INCLUDE_ASM("asm/nonmatchings/main_007", func_00124810);

INCLUDE_ASM("asm/nonmatchings/main_007", func_00124A30);

s32 func_00124C10(s32 arg0) {
    s32 value;

    if ((func_0026FCE0(arg0) >> 5) != 0) {
        return 1;
    }
    value = func_0026FCE0(arg0) & 0x1F;
    if ((value == 0) || (value == 0xF) || (value == 0x12)) {
        return 1;
    }
    return 0;
}

void func_0026FD30(s32, s32 *);
void func_00123D70(s32, s32 *);

typedef struct {
    u8 pad0[6];
    u8 slot[5];
} Obj1_00124C90;

typedef struct {
    u8 pad0[0x3C];
    u16 id;
} Obj2_00124C90;

s32 func_00124C90(s32 arg0, void *arg1, void *arg2, s32 arg3) {
    Obj1_00124C90 *o1 = arg1;
    Obj2_00124C90 *o2 = arg2;
    s32 list[8];
    s32 i;
    u8 t;

    for (i = 0; i < 5; i++) {
        o1->slot[i] = 0xFF;
    }
    func_0026FD30(arg0, list);
    if (o2 == NULL) {
        return -1;
    }
    if ((arg3 & 0xFF) == 0) {
        for (i = 0; i < func_0026FE20(arg0); i++) {
            if (i != o1->slot[0] && i != o1->slot[1]) {
                if (o2->id == list[i] && func_0026FB10(arg0, list[i]) == 1) {
                    o1->slot[0] = i;
                }
            }
        }
        return 0;
    }
    func_00123D70(arg0, list);
    for (i = 0; i < func_0026FE20(arg0); i++) {
        t = func_0026FCE0(list[i]);
        if ((t >> 5) == 0 && (t & 0x1F) == 0 && func_0026FB10(arg0, list[i]) == 1) {
            o1->slot[0] = i;
        }
    }
    for (i = 0; i < func_0026FE20(arg0); i++) {
        t = func_0026FCE0(list[i]);
        if ((t >> 5) == 0 && (t & 0x1F) == 0x12 && func_0026FB10(arg0, list[i]) == 1) {
            o1->slot[1] = i;
        }
    }
    for (i = 0; i < func_0026FE20(arg0); i++) {
        t = func_0026FCE0(list[i]);
        if ((t >> 5) == 0 && (t & 0x1F) == 0xF && func_0026FB10(arg0, list[i]) == 1) {
            o1->slot[2] = i;
        }
    }
    return 0;
}

void func_00124F50(void) {
    func_0024E410();
}

INCLUDE_ASM("asm/nonmatchings/main_007", func_00124F60);

s32 func_001254A0(s32 arg0) {
    if (func_001DF470() > 0x3E8) {
        if (func_001E0150(arg0) >= 3) {
            return 0x1F4;
        } else {
            return 0x3E8;
        }
    } else {
        return 0x7D0;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_007", func_00125500);

INCLUDE_ASM("asm/nonmatchings/main_007", func_00125B70);

INCLUDE_ASM("asm/nonmatchings/main_007", func_00126380);

static inline s32 max_00126840(s32 a, s32 b) {
    if (a < b) {
        return b;
    }
    return a;
}

s32 func_00126840(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 min_y;
    s32 min_x;

    min_y = arg3 < arg5 ? arg3 : arg5;
    arg5 = max_00126840(arg5, arg3);
    min_x = arg2 < arg4 ? arg2 : arg4;
    arg4 = max_00126840(arg4, arg2);
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

typedef struct State_00126940 {
    u8 pad0[4];
    u16 field4;
    u16 pad6;
    u32 field8;
} State_00126940;

void func_00126940(void *arg0, u8 arg1) {
    State_00126940 *state = (State_00126940 *)arg0;

    if (arg1 < 2) {
        if (arg1 == 1) {
            state->field4 = (state->field4 & 0xFF) | 0xFF00;
        } else {
            state->field4 = (state->field4 & 0xFF00) | 0xFF;
        }
        if (arg1 == 1) {
            state->field8 = (state->field8 & 0xFFFF) | 0xFFFF0000;
        } else {
            state->field8 = (state->field8 & 0xFFFF0000) | 0xFFFF;
        }
    }
}

s32 func_001269C0(s32 arg0, s32 arg1) {
    s32 data[4];
    s32 i;
    s32 mask;
    s32 y;
    s32 x;
    s32 cell;
    s32 coords;

    func_00254C90(data, *(s32 *)((u8 *)func_0026FC90(arg1, 0) + 4));
    if ((mask = func_00254890(data, arg0)) < 0) {
        return 0;
    }
    for (i = 0; i < func_0024E910(mask); i++) {
        cell = func_0024EC50(mask, i);
        x = cell >> 8;
        y = cell & 0xFF;
        coords = func_001E1090(x, y);
        if (func_002509E0(x, y, coords & 0xFF, coords >> 8) >= 0xA28) {
            return 0;
        }
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_007", func_00126AB0);

INCLUDE_ASM("asm/nonmatchings/main_007", func_00126C80);

INCLUDE_ASM("asm/nonmatchings/main_007", func_001271F0);

INCLUDE_ASM("asm/nonmatchings/main_007", func_001273E0);

INCLUDE_ASM("asm/nonmatchings/main_007", func_001277C0);

void func_00127A30(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28) {
    func_0027DE20(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                  arg_sp0, arg_sp8, arg_sp10, arg_sp18, arg_sp20,
                  0, 2000, arg_sp28);
}

void func_00127A90(void *arg0) {
    s32 temp_v0_2;
    u16 temp_v0;

    temp_v0 = *(u16 *)arg0;
    temp_v0_2 = func_001E1090((s32) temp_v0 >> 8, temp_v0 & 0xFF);
    *(s16 *)((u8 *)arg0 + 4) = 0x6FF;
    if ((temp_v0_2 >> 8) < 3) {
        *(u32 *)((u8 *)arg0 + 8) = *(u16 *)((u8 *)arg0 + 8) | 0x03010000;
    } else {
        *(u32 *)((u8 *)arg0 + 8) = *(u16 *)((u8 *)arg0 + 8) | 0x05020000;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_007", func_00127B00);

INCLUDE_ASM("asm/nonmatchings/main_007", func_00127D20);

INCLUDE_ASM("asm/nonmatchings/main_007", func_00127E30);

INCLUDE_ASM("asm/nonmatchings/main_007", func_001280C0);

s32 func_00128430(s32 arg0, void *arg1, void *arg2, s32 arg3) {
    s32 index;
    s32 *entry;
    s32 target;
    s32 entries[8];

    func_0026FD30(arg0, entries);
    index = 0;
    if (index < func_0026FE20(arg0)) {
        target = arg3 & 0xFFFF;
        entry = entries;
        do {
            if (target == *entry && func_0026FB10(arg0, *entry) == 1) {
                *((s8 *)arg1 + 6) = index;
                func_001DCD70(arg2, entries[index]);
                return func_0026FCE0(entries[index]) >> 5;
            }
            entry++;
            index++;
        } while (index < func_0026FE20(arg0));
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/main_007", func_00128520);

INCLUDE_ASM("asm/nonmatchings/main_007", func_00128720);

INCLUDE_ASM("asm/nonmatchings/main_007", func_00128900);

s32 func_00128AE0(s32 arg0) {
    if ((func_0026FCE0(arg0) >> 5) != 0) {
        return 1;
    }
    if (arg0 == 0x6C || arg0 == 0x6F || arg0 == 0x68) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_007", func_00128B50);

INCLUDE_ASM("asm/nonmatchings/main_007", func_00128D40);

INCLUDE_ASM("asm/nonmatchings/main_007", func_001291C0);

INCLUDE_ASM("asm/nonmatchings/main_007", func_00129700);

INCLUDE_ASM("asm/nonmatchings/main_007", func_00129D00);

INCLUDE_ASM("asm/nonmatchings/main_007", func_0012A2E0);

INCLUDE_ASM("asm/nonmatchings/main_007", func_0012AAC0);

INCLUDE_ASM("asm/nonmatchings/main_007", func_0012B000);

s32 func_0012B1B0(s32 arg0) {
    if (func_001DF470() > 0x4B0) {
        if (func_001E0150(arg0) >= 4) {
            return 0x3E8;
        }
        return 0x7D0;
    }
    return 0x960;
}

INCLUDE_ASM("asm/nonmatchings/main_007", func_0012B210);

static inline s32 max_0012B730(s32 a, s32 b) {
    s32 maximum;

    if (a < b) {
        maximum = b;
    } else {
        maximum = a;
    }
    return maximum;
}

s32 func_0012B730(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 min_y;
    s32 min_x;
    s32 result;
    s32 status;

    min_y = arg3 < arg5 ? arg3 : arg5;
    arg5 = max_0012B730(arg5, arg3);
    min_x = arg2 < arg4 ? arg2 : arg4;
    arg4 = max_0012B730(arg4, arg2);
    if ((arg4 - min_x) + (arg5 - min_y) != 2) {
        return 0;
    }
    if (func_001DF540(arg0, arg1) == 0) {
        return 0;
    }
    if (func_001E2100(arg0, arg1, 0) == 0) {
        status = func_0024DF00(func_001E22B0(arg2, arg3), arg0, arg1);
        result = 1;
        if (status != 1) {
            return 0;
        }
        return result;
    }
    return 0;
}

typedef struct {
    u8 pad0[4];
    u16 value4;
    u8 pad6[2];
    u32 value8;
} Data_0012B830;

void func_0012B830(void *arg0, u8 arg1) {
    Data_0012B830 *data = arg0;

    if (arg1 < 2) {
        if (arg1 == 1) {
            data->value4 = (data->value4 & 0xFF) | 0xFF00;
        } else {
            data->value4 = (data->value4 & 0xFF00) | 0xFF;
        }
        if (arg1 == 1) {
            data->value8 = (data->value8 & 0xFFFF) | 0xFFFF0000;
        } else {
            data->value8 = (data->value8 & 0xFFFF0000) | 0xFFFF;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/main_007", func_0012B8B0);

INCLUDE_ASM("asm/nonmatchings/main_007", func_0012B9A0);

INCLUDE_ASM("asm/nonmatchings/main_007", func_0012BB70);

INCLUDE_ASM("asm/nonmatchings/main_007", func_0012C1A0);

INCLUDE_ASM("asm/nonmatchings/main_007", func_0012C3F0);

INCLUDE_ASM("asm/nonmatchings/main_007", func_0012C7F0);

void func_0012CB80(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28) {
    func_0027DE20(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                  arg_sp0, arg_sp8, arg_sp10, arg_sp18, arg_sp20,
                  0, 2500, arg_sp28);
}

INCLUDE_ASM("asm/nonmatchings/main_007", func_0012CBE0);
