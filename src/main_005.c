#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_005", func_00114D40);

INCLUDE_ASM("asm/nonmatchings/main_005", func_00114F20);

s32 func_00115100(s32 arg0) {
    if ((func_0026FCE0(arg0) >> 5) != 0) {
        return 1;
    }
    if (func_0026FC10(arg0) == 1) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_005", func_00115160);

INCLUDE_ASM("asm/nonmatchings/main_005", func_00115340);

INCLUDE_ASM("asm/nonmatchings/main_005", func_00115850);

INCLUDE_ASM("asm/nonmatchings/main_005", func_00115E20);

INCLUDE_ASM("asm/nonmatchings/main_005", func_001162F0);

INCLUDE_ASM("asm/nonmatchings/main_005", func_00116B60);

INCLUDE_ASM("asm/nonmatchings/main_005", func_001170A0);

s32 func_00117340(void) {
    if (func_0027DD20(func_001DE540(), 3, 2) != 0 ||
        func_0027DD20(func_001DE540(), 3, 0x345) != 0 ||
        func_0024CA40(0, 0, func_001DE540(), 1, 0x2001C, 14) != 0) {
        return 1;
    }
    return 0;
}

s32 func_001173E0(s32 arg0) {
    s32 i;
    u8 n = 0;
    s32 need;
    u8 m;
    s32 j;

    if (func_001DF470() < 0x5DC) {
        return 0;
    }
    need = func_0027DD20(arg0, 3, 2) & 0xFF;
    if (need > 0) {
        for (i = 0; i < 8; i++) {
            if (func_0024E300(arg0, i, 1) >= 0) {
                n++;
            }
        }
        if (n >= need && 5 - func_001E0150(arg0) >= need) {
            return 1;
        }
    }
    m = 0;
    need = func_0027DD20(arg0, 3, 0) & 0xFF;
    if (need > 0) {
        for (j = 0; j < 8; j++) {
            if (func_0024E300(arg0, j, 1) >= 0) {
                m++;
            }
        }
        if (m >= need && 5 - func_001E0150(arg0) >= need) {
            return 1;
        }
    }
    return 0;
}

s32 func_00117550(s32 arg0) {
    s32 count;

    if (func_001DF470() < 0x5DC) {
        return 0;
    }
    count = func_0024CA40(0, 0, arg0, 1, 0x2001C, 14);
    count += func_0024CA40(0, 0, arg0, 1, 0x2001C, 14);
    if (count != 0) {
        if (func_001E0150(arg0) >= 4) {
            return 1;
        }
    }
    return 0;
}

s32 func_00117600(s32 arg0) {
    if (func_0024CA40(0, 0, arg0, 1, 0x2001C, 0xE) != 0) {
        return 1;
    }
    return (func_0024CA40(0, 0, arg0, 1, 0x1C, 0xE) != 0) ? 1 : 0;
}

INCLUDE_ASM("asm/nonmatchings/main_005", func_00117680);

INCLUDE_ASM("asm/nonmatchings/main_005", func_00117870);

static inline s32 min_00117B10(s32 a, s32 b) {
    return (a < b) ? a : b;
}

static inline s32 max_00117B10(s32 a, s32 b) {
    return (a > b) ? a : b;
}

static inline s32 distance_00117B10(s32 x, s32 y) {
    return (max_00117B10(y, 3) - min_00117B10(y, 3)) +
           (max_00117B10(x, 3) - min_00117B10(x, 3));
}

s32 func_00117B10(s32 arg0) {
    s32 temp_s0;
    s32 temp_v0;

    if (arg0 == 0x303) {
        return 1;
    }
    temp_v0 = func_001E36E0(3, 3);
    if (temp_v0 != 0) {
        temp_s0 = func_00250370((void *) temp_v0);
        if (temp_s0 != func_001DE540()) {
            if (distance_00117B10(arg0 >> 8, arg0 & 0xFF) == 1) {
                return 1;
            }
        }
    }
    return 0;
}

s32 func_00117BD0(s32 arg0, s32 arg1) {
    s32 sp20[3];

    func_00254C90(sp20, *(s32 *)((u8 *)func_0026FC90(arg1, 0) + 4));
    if (func_00254890(sp20, arg0) < 0) {
        return 0;
    }
    return 1;
}

s32 func_00117C30(s32 arg0) {
    if (func_001DF470() > 0x4B0) {
        if (func_001E0150(arg0) >= 4) {
            return 0x2EE;
        } else {
            return 0x5DC;
        }
    } else {
        return 0x9C4;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_005", func_00117C90);

INCLUDE_ASM("asm/nonmatchings/main_005", func_00117E60);

INCLUDE_ASM("asm/nonmatchings/main_005", func_00118330);

INCLUDE_ASM("asm/nonmatchings/main_005", func_00118510);

INCLUDE_ASM("asm/nonmatchings/main_005", func_001188F0);

void func_00118B60(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28) {
    func_0027DE20(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                 arg_sp0, arg_sp8, arg_sp10, arg_sp18, arg_sp20,
                 0, 0x5DC, arg_sp28);
}

INCLUDE_ASM("asm/nonmatchings/main_005", func_00118BC0);

s32 func_00118CE0(s32 arg0, s32 arg1) {
    s32 index;
    s32 row;
    s32 low;
    s32 high;
    s32 slot;

    switch ((u8)arg1) {
    case 0:
        row = 2;
        break;
    case 1:
        row = 4;
        break;
    case 2:
        row = 0;
        break;
    case 3:
    default:
        row = 6;
        break;
    }
    index = 1;
    while (1) {
        slot = func_001E3790(row, index);
        if (slot >= 0) {
            high = slot >> 8;
            low = slot & 0xFF;
            if (arg0 == func_00250360(high, low) &&
                (func_001E0700(high, low) >> 5) == 0) {
                return 0;
            }
        }
        index++;
        if (index > 5) {
            return 1;
        }
    }
}

s32 func_00118DD0(s32 arg0) {
    s32 i;

    i = 0;
    do {
        if (func_00118CE0(arg0, (u8)i) != 0) {
            switch (i) {
            case 0:
                return 0x102;
            case 1:
                return 0x104;
            case 2:
                return 0x100;
            case 3:
            default:
                return 0x106;
            }
        }
        i++;
    } while (i < 4);
    return -1;
}

s32 func_00118E90(s32 arg0) {
    s32 i = 0;

    do {
        if (func_00118CE0(arg0, (u8)i) == 0) {
            switch (i) {
            case 0:
                return 0x602;
            case 1:
                return 0x604;
            case 2:
                return 0x600;
            case 3:
            default:
                return 0x606;
            }
        }
        i++;
    } while (i < 4);

    return -1;
}

INCLUDE_ASM("asm/nonmatchings/main_005", func_00118F50);

INCLUDE_ASM("asm/nonmatchings/main_005", func_00119300);

INCLUDE_ASM("asm/nonmatchings/main_005", func_00119520);

INCLUDE_ASM("asm/nonmatchings/main_005", func_00119A40);

INCLUDE_ASM("asm/nonmatchings/main_005", func_00119D30);

INCLUDE_ASM("asm/nonmatchings/main_005", func_00119F30);

INCLUDE_ASM("asm/nonmatchings/main_005", func_0011A0D0);

INCLUDE_ASM("asm/nonmatchings/main_005", func_0011A2F0);

void func_0011A4C0(void) {
    func_0024E410();
}

INCLUDE_ASM("asm/nonmatchings/main_005", func_0011A4D0);

s32 func_0011AA10(s32 arg0) {
    if (func_001DF470() > 0x5DC) {
        if (func_001E0150(arg0) >= 3) {
            return 0;
        } else {
            return 0;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_005", func_0011AA70);

INCLUDE_ASM("asm/nonmatchings/main_005", func_0011B0E0);

INCLUDE_ASM("asm/nonmatchings/main_005", func_0011B680);

INCLUDE_ASM("asm/nonmatchings/main_005", func_0011C140);

INCLUDE_ASM("asm/nonmatchings/main_005", func_0011C2E0);

typedef struct {
    u8 pad[8];
    u32 value;
} Data_0011C3E0;

void func_0011C3E0(void *arg0, u8 arg1) {
    Data_0011C3E0 *data = arg0;

    if (arg1 < 2) {
        if (arg1 == 1) {
            data->value = (data->value & 0xFFFF) | 0xFFFF0000;
        } else {
            data->value = (data->value & 0xFFFF0000) | 0xFFFF;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/main_005", func_0011C430);

INCLUDE_ASM("asm/nonmatchings/main_005", func_0011C600);

INCLUDE_ASM("asm/nonmatchings/main_005", func_0011CB20);

INCLUDE_ASM("asm/nonmatchings/main_005", func_0011CD30);
