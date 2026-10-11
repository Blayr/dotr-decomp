#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010C940);

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010CE20);

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010D080);

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010D490);

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010D820);

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010D880);

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010DB00);

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010DC40);

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010DD50);

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010DFC0);

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010E320);

s32 func_0010E540(s32 arg0, void *arg1, s32 arg2, s32 arg3) {
    s32 count;
    s32 *p;
    s32 i;
    s32 values[8];
    s32 j;
    s32 value;
    u8 *slot;
    u8 *out = (u8 *)arg1;

    if (arg2 == 0) return -1;
    j = 0;
    do {
        out[j + 6] = 255;
        j++;
    } while (j < 5);
    func_0026FD30(arg0, values);
    if (!(arg3 & 255)) {
        func_0010F290(arg0, arg1, arg2, 0);
        count = 2;
        if (func_0023C160() > 3) {
            i = 0;
            if (i < func_0026FE20(arg0)) {
                p = values;
                do {
                    if (i != out[6] && i != out[7] && func_00248F60(427, *p) >= 0 && (func_0026FCE0(*p) >> 5) == 2) {
                        value = *p;
                        if (value != 795 && value != 796) {
                            slot = out + count;
                            count++;
                            slot[6] = i;
                        }
                    }
                    p++;
                    i++;
                } while (i < func_0026FE20(arg0));
            }
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010E6B0);

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010E890);

void func_0010ED90(void) {
    func_0024E410();
}

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010EDA0);

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010EE00);

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010F030);

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010F220);

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010F290);

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010F450);

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010F6F0);

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010F850);

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010F940);

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010FA60);

INCLUDE_ASM("asm/nonmatchings/main_004", func_0010FFF0);

INCLUDE_ASM("asm/nonmatchings/main_004", func_001106F0);

INCLUDE_ASM("asm/nonmatchings/main_004", func_00110F00);

INCLUDE_ASM("asm/nonmatchings/main_004", func_001110D0);

INCLUDE_ASM("asm/nonmatchings/main_004", func_00111320);

INCLUDE_ASM("asm/nonmatchings/main_004", func_001123C0);

INCLUDE_ASM("asm/nonmatchings/main_004", func_00112600);

INCLUDE_ASM("asm/nonmatchings/main_004", func_00112850);

s32 func_00112960(s32 arg0) {
    s32 result;

    result = (u32) (arg0 - 0x36) < 4U ? 1 : 0;
    return result;
}

INCLUDE_ASM("asm/nonmatchings/main_004", func_00112980);

INCLUDE_ASM("asm/nonmatchings/main_004", func_00112A40);

INCLUDE_ASM("asm/nonmatchings/main_004", func_00112B90);

INCLUDE_ASM("asm/nonmatchings/main_004", func_00113140);

INCLUDE_ASM("asm/nonmatchings/main_004", func_00113370);

INCLUDE_ASM("asm/nonmatchings/main_004", func_00113760);

INCLUDE_ASM("asm/nonmatchings/main_004", func_00113A00);

INCLUDE_ASM("asm/nonmatchings/main_004", func_00113A60);

s32 func_00113B60(s32 arg0, s32 arg1) {
    s32 result;

    if (arg1 >= 5) {
        result = 0x602;
    } else if (arg0 >= 5) {
        result = 0x206;
    } else if (arg0 >= arg1) {
        result = 0x105;
    } else {
        result = 0x501;
    }
    return result;
}

INCLUDE_ASM("asm/nonmatchings/main_004", func_00113BB0);

INCLUDE_ASM("asm/nonmatchings/main_004", func_00113ED0);

INCLUDE_ASM("asm/nonmatchings/main_004", func_00114080);

INCLUDE_ASM("asm/nonmatchings/main_004", func_00114310);

INCLUDE_ASM("asm/nonmatchings/main_004", func_001146C0);

INCLUDE_ASM("asm/nonmatchings/main_004", func_001147B0);

INCLUDE_ASM("asm/nonmatchings/main_004", func_00114B40);
