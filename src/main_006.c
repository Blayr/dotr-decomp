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

typedef struct {
    u8 pad[6];
    u8 indices[5];
} CardState_0011F3C0;

void func_0011EB10(s32, s32, s32, s32);

s32 func_0011F3C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 cards[5];
    s32 *card;
    s32 i;
    s32 card_id;

    if (arg2 == 0) {
        return -1;
    }
    for (i = 0; i < 5; i++) {
        ((CardState_0011F3C0 *)(arg1 + i))->indices[0] = 0xFF;
    }
    func_0026FD30(arg0, cards);
    if ((arg3 & 0xFF) == 0) {
        func_0011EB10(arg0, arg1, arg2, 0);
        i = 0;
        if (0 < func_0026FE20(arg0)) {
            card = cards;
            do {
                if ((i != ((CardState_0011F3C0 *)arg1)->indices[0]) && (i != ((CardState_0011F3C0 *)arg1)->indices[1]) && (func_00248F60(0x1E8, *card) >= 0) && ((func_0026FCE0(*card) >> 5) == 2)) {
                    card_id = *card;
                    if ((card_id != 0x31B) && (card_id != 0x31C)) {
                        ((CardState_0011F3C0 *)arg1)->indices[2] = i;
                    }
                }
                card++;
                i++;
            } while (i < func_0026FE20(arg0));
        }
    } else if ((arg3 & 0xFF) == 1) {
        func_0011EB10(arg0, arg1, arg2, 0);
    }
    return 0;
}

void func_0011F530(void) {
    func_0024E410();
}

INCLUDE_ASM("asm/nonmatchings/main_006", func_0011F540);

s32 func_0011FA80(s32 arg0) {
    if (func_001DF470(arg0) > 0x3E8) {
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

typedef struct Unit_00121CE0 {
    u16 pos;
    u16 unk2;
    u16 unk4;
    u16 unk6;
    s32 unk8;
} Unit_00121CE0;

void func_001229F0(void *, s32);
void func_00122270(void *);
void func_00122B50(void *);
void func_0027CA50(void *, s32, s32, s32);

s32 func_00121CE0(void *arg0) {
    Unit_00121CE0 *unit = arg0;
    s32 handle;

    handle = func_00250360(unit->pos >> 8, unit->pos & 0xFF);
    if (func_001DF540(unit->pos >> 8, unit->pos & 0xFF) != 0 &&
        func_001E2100(unit->pos >> 8, unit->pos & 0xFF, 0) == 0 && unit->pos != 0xFFFF) {
    if ((unit->pos & 0xFF) == 0) {
        if (unit->unk8 == -1) {
            func_0027E210(unit, 3, 2, 0);
        }
    } else {
        switch (func_001E0700(unit->pos >> 8, unit->pos & 0xFF) >> 5) {
        case 0:
            if (func_002507D0(unit->pos >> 8, unit->pos & 0xFF) == 1) {
                func_001229F0(unit, 1);
            } else {
                func_00122270(unit);
            }
            break;
        case 1:
        case 5:
            unit->unk4 = 0x5FF;
            break;
        case 2:
            func_0027CA50(unit, 2, 0, (u8)func_001254A0(handle));
            break;
        case 4:
            func_00122B50(unit);
            break;
        default:
            unit->unk4 = 0x5FF;
            break;
        }
    }
    return 1;
    }
    return 0;
}

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

s32 func_00122680(s32 arg0, s32 arg1) {
    s32 x;
    s32 y;

    x = func_001E1090(arg0, arg1) & 0xFF;
    y = func_001E1090(arg0, arg1) >> 8;
    if ((x >= 2) && (x < 6) && (y == 0)) {
        return 0;
    }
    if ((x == 6) && (y >= 0) && (y < 4)) {
        return 1;
    }
    if ((x > 4) && (x < 7) && (y == 4)) {
        return 2;
    }
    if ((x == 4) && (y >= 4) && (y < 6)) {
        return 3;
    }
    if ((x > 0) && (x < 5) && (y == 6)) {
        return 4;
    }
    if ((x == 0) && (y > 2) && (y < 7)) {
        return 5;
    }
    if ((x >= 0) && (x < 2) && (y == 2)) {
        return 6;
    }
    if ((x == 2) && (y > 0) && (y < 3)) {
        return 7;
    }
    return -1;
}

s32 func_00122810(s32 arg0, s32 arg1) {
    s32 var_s0;
    s32 var_s1;
    s32 var_s2;
    s32 var_s3;
    s32 var_s6;
    s32 var_v0;

    var_s1 = -1;
    var_s0 = 0;
    do {
        if (arg1 < (func_00122970(var_s0) >> 8)) {
            var_s2 = arg1;
        } else {
            var_s2 = func_00122970(var_s0) >> 8;
        }
        if ((func_00122970(var_s0) >> 8) < arg1) {
            var_s3 = arg1;
        } else {
            var_s3 = func_00122970(var_s0) >> 8;
        }
        if (arg0 < (func_00122970(var_s0) & 0xFF)) {
            var_s6 = arg0;
        } else {
            var_s6 = func_00122970(var_s0) & 0xFF;
        }
        if ((func_00122970(var_s0) & 0xFF) < arg0) {
            var_v0 = arg0;
        } else {
            var_v0 = func_00122970(var_s0) & 0xFF;
        }
        if (((var_v0 - var_s6) + (var_s3 - var_s2)) >= -1) {
            var_s1 = func_00122970(var_s0);
        }
        var_s0 += 1;
    } while (var_s0 < 8);
    return var_s1;
}

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
