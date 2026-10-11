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

INCLUDE_ASM("asm/nonmatchings/main_005", func_00117340);

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

INCLUDE_ASM("asm/nonmatchings/main_005", func_00117550);

INCLUDE_ASM("asm/nonmatchings/main_005", func_00117600);

INCLUDE_ASM("asm/nonmatchings/main_005", func_00117680);

INCLUDE_ASM("asm/nonmatchings/main_005", func_00117870);

INCLUDE_ASM("asm/nonmatchings/main_005", func_00117B10);

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

INCLUDE_ASM("asm/nonmatchings/main_005", func_00118CE0);

INCLUDE_ASM("asm/nonmatchings/main_005", func_00118DD0);

INCLUDE_ASM("asm/nonmatchings/main_005", func_00118E90);

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
