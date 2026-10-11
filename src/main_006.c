#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_006", func_0011D110);

void func_0011D380(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28) {
    func_0027DE20(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                  arg_sp0, arg_sp8, arg_sp10, arg_sp18, arg_sp20,
                  0, 1500, arg_sp28);
}

INCLUDE_ASM("asm/nonmatchings/main_006", func_0011D3E0);

INCLUDE_ASM("asm/nonmatchings/main_006", func_0011D4E0);

s32 func_0011D6D0(s32 arg0, s32 arg1) {
    s32 value;

    value = func_001E1090(arg0, arg1);
    switch (value & 0xFF) {
    case 0:
        value >>= 8;
        if ((value >= 0) && (value < 7)) {
            return 3;
        }
        break;
    case 2:
        value >>= 8;
        if ((value > 1) && (value < 5)) {
            return 0;
        }
        break;
    case 4:
        value >>= 8;
        if ((value > 1) && (value < 5)) {
            return 1;
        }
        break;
    case 6:
        value >>= 8;
        if ((value >= 0) && (value < 7)) {
            return 4;
        }
        break;
    }
    return -1;
}

s32 func_0011D7B0(s32 arg0, u8 arg1) {
    s32 row;
    s32 column;
    s32 last_column;
    s32 low;
    s32 high;
    s32 value;

    switch (arg1) {
    case 0:
        column = 2;
        last_column = 4;
        row = 2;
        break;
    case 1:
        column = 2;
        row = 4;
        last_column = 4;
        break;
    case 2:
        column = 1;
        last_column = 5;
        row = 0;
        break;
    case 3:
    default:
        row = 6;
        column = 1;
        last_column = 5;
        break;
    }
    for (; column <= last_column; column++) {
        value = func_001E3790(row, column);
        if (value >= 0) {
            high = value >> 8;
            low = value & 0xFF;
            if ((arg0 == func_00250360(high, low)) &&
                ((func_001E0700(high, low) >> 5) == 0)) {
                return 0;
            }
        }
    }
    return 1;
}

s32 func_0011D8D0(s32 arg0, s32 arg1) {
    s32 result;

    switch (arg1) {
    case 0:
        result = 0x204;
        break;
    case 1:
        result = 0x202;
        break;
    case 2:
        result = 0;
        break;
    default:
    case 3:
        result = 6;
        break;
    }

    return result;
}

s32 func_0011D940(s32 arg0, s32 arg1) {
    switch (arg1) {
    case 0:
        return 0x402;
    case 1:
        return 0x404;
    case 2:
        return 0x600;
    default:
    case 3:
        return 0x606;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_006", func_0011D9B0);

INCLUDE_ASM("asm/nonmatchings/main_006", func_0011DC00);

INCLUDE_ASM("asm/nonmatchings/main_006", func_0011DFB0);

INCLUDE_ASM("asm/nonmatchings/main_006", func_0011E270);

INCLUDE_ASM("asm/nonmatchings/main_006", func_0011E6E0);

INCLUDE_ASM("asm/nonmatchings/main_006", func_0011EB10);

INCLUDE_ASM("asm/nonmatchings/main_006", func_0011ED50);

INCLUDE_ASM("asm/nonmatchings/main_006", func_0011EF60);

INCLUDE_ASM("asm/nonmatchings/main_006", func_0011F150);

s32 func_0011F330(s32 arg0) {
    if ((func_0026FCE0(arg0) >> 5) != 0) {
        return 1;
    }
    if ((arg0 == 0x1F0) || (arg0 == 0x1FD) || (arg0 == 0x1FE) ||
        (arg0 == 0x202) || (arg0 == 0x1F6) || (arg0 == 0x20B)) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_006", func_0011F3C0);

void func_0011F530(void) {
    func_0024E410();
}

INCLUDE_ASM("asm/nonmatchings/main_006", func_0011F540);

s32 func_0011FA80(s32 arg0) {
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

INCLUDE_ASM("asm/nonmatchings/main_006", func_0011FAE0);

INCLUDE_ASM("asm/nonmatchings/main_006", func_00120150);

INCLUDE_ASM("asm/nonmatchings/main_006", func_001206F0);

INCLUDE_ASM("asm/nonmatchings/main_006", func_001211B0);

INCLUDE_ASM("asm/nonmatchings/main_006", func_001214E0);

void func_001215E0(void *arg0, u8 arg1) {
    if (arg1 < 2) {
        if (arg1 == 1) {
            *(u32 *)((u8 *)arg0 + 8) =
                (*(u32 *)((u8 *)arg0 + 8) & 0xFFFF) | 0xFFFF0000;
        } else {
            *(u32 *)((u8 *)arg0 + 8) =
                (*(u32 *)((u8 *)arg0 + 8) & 0xFFFF0000) | 0xFFFF;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/main_006", func_00121630);

INCLUDE_ASM("asm/nonmatchings/main_006", func_00121800);

INCLUDE_ASM("asm/nonmatchings/main_006", func_00121CE0);

INCLUDE_ASM("asm/nonmatchings/main_006", func_00121E90);

INCLUDE_ASM("asm/nonmatchings/main_006", func_00122270);

void func_001224D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28) {
    func_0027DE20(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                  arg_sp0, arg_sp8, arg_sp10, arg_sp18, arg_sp20,
                  0, 1500, arg_sp28);
}

typedef struct {
    u16 coordinates;
    u16 unk02;
    s16 state;
    u16 unk06;
    union {
        u32 word;
        struct {
            u16 low;
            u16 high;
        } halves;
    } data;
} Entry_00122530;

s32 func_00122680(s32, s32);
s32 func_00122810(s32, s32);
s32 func_00122970(s32);
void func_00123500(s32, s32, s32, s32 *);

void func_00122530(void *arg0) {
    Entry_00122530 *entry = arg0;
    s32 packed;
    s32 position;
    s32 result[2];
    u16 coordinates;

    coordinates = entry->coordinates;
    if (func_001DF540((s32) coordinates >> 8, coordinates & 0xFF) != 0) {
        coordinates = entry->coordinates;
        func_0024DE70((s32) coordinates >> 8, coordinates & 0xFF);
        coordinates = entry->coordinates;
        packed = func_001E1090((s32) coordinates >> 8, coordinates & 0xFF);
        entry->state = 0x6FF;
        coordinates = entry->coordinates;
        if (func_001E0290((s32) coordinates >> 8, coordinates & 0xFF, 0) >= 0x5DC) {
            coordinates = entry->coordinates;
            position = func_00122680((s32) coordinates >> 8, coordinates & 0xFF);
            if (position >= 0) {
                entry->data.word = entry->data.halves.low | (func_00122970((position + 1) % 8) << 16);
                return;
            }
            entry->data.word = entry->data.halves.low | (func_00122810(packed & 0xFF, packed >> 8) << 16);
            return;
        }
        coordinates = entry->coordinates;
        func_00123500(func_001DF540((s32) coordinates >> 8, coordinates & 0xFF), packed & 0xFF, packed >> 8, result);
        if (result[0] >= 0) {
            entry->data.word = (result[0] << 16) | entry->data.halves.low;
            return;
        }
        entry->state = 0x5FF;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_006", func_00122680);

INCLUDE_ASM("asm/nonmatchings/main_006", func_00122810);

INCLUDE_ASM("asm/nonmatchings/main_006", func_00122970);

INCLUDE_ASM("asm/nonmatchings/main_006", func_001229F0);

INCLUDE_ASM("asm/nonmatchings/main_006", func_00122B50);

INCLUDE_ASM("asm/nonmatchings/main_006", func_00122D30);

INCLUDE_ASM("asm/nonmatchings/main_006", func_00123010);

INCLUDE_ASM("asm/nonmatchings/main_006", func_00123500);

s32 func_00123670(s32 arg0) {
    switch (arg0) {                                 /* irregular */
    case 0:
        return 0x303;
    case 1:
        return 0x304;
    default:
    case 2:
        return 0x302;
    }
}

s32 func_001236C0(s32 arg0) {
    s32 var_v0;

    switch (arg0) {
        case 0:
            var_v0 = 0x303;
            break;
        case 1:
            var_v0 = 0x304;
            break;
        case 2:
        default:
            var_v0 = 0x302;
            break;
    }
    if ((var_v0 >= 0) && (func_001E36E0(var_v0 & 0xFF, var_v0 >> 8) == 0)) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_006", func_00123740);

INCLUDE_ASM("asm/nonmatchings/main_006", func_00123D70);

INCLUDE_ASM("asm/nonmatchings/main_006", func_00123F90);

INCLUDE_ASM("asm/nonmatchings/main_006", func_00124040);

s32 func_00124520(s32 arg0, void *arg1, void *arg2, s32 arg3) {
    s32 entries[8];
    s32 i;

    func_0026FD30(arg0, entries);
    for (i = 0; i < func_0026FE20(arg0); i++) {
        if (((arg3 & 0xFFFF) == entries[i]) && (func_0026FB10(arg0, entries[i]) == 1)) {
            ((s8 *)arg1)[6] = i;
            func_001DCD70(arg2, entries[i]);
            return func_0026FCE0(entries[i]) >> 5;
        }
    }
    return -1;
}
