#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_005", func_00114D40);

INCLUDE_ASM("asm/nonmatchings/main_005", func_00114F20);

INCLUDE_ASM("asm/nonmatchings/main_005", func_00115100);

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

INCLUDE_ASM("asm/nonmatchings/main_005", func_00117BD0);

INCLUDE_ASM("asm/nonmatchings/main_005", func_00117C30);

INCLUDE_ASM("asm/nonmatchings/main_005", func_00117C90);

INCLUDE_ASM("asm/nonmatchings/main_005", func_00117E60);

INCLUDE_ASM("asm/nonmatchings/main_005", func_00118330);

INCLUDE_ASM("asm/nonmatchings/main_005", func_00118510);

INCLUDE_ASM("asm/nonmatchings/main_005", func_001188F0);

INCLUDE_ASM("asm/nonmatchings/main_005", func_00118B60);

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

INCLUDE_ASM("asm/nonmatchings/main_005", func_0011AA10);

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
