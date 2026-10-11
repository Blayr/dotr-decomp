#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_078", func_00276120);

INCLUDE_ASM("asm/nonmatchings/main_078", func_002761D0);

INCLUDE_ASM("asm/nonmatchings/main_078", func_00276290);

INCLUDE_ASM("asm/nonmatchings/main_078", func_00276B60);

s32 func_00276C80(u16 *arg0, s32 arg1) {
    s32 i = 0;

    do {
        if (arg1 == *arg0) {
            return i;
        }
        i++;
        arg0 += 8;
    } while (i < 0x16);
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/main_078", func_00276CC0);

INCLUDE_ASM("asm/nonmatchings/main_078", func_00276EC0);

INCLUDE_ASM("asm/nonmatchings/main_078", func_00276F10);

INCLUDE_ASM("asm/nonmatchings/main_078", func_002770E0);

INCLUDE_ASM("asm/nonmatchings/main_078", func_00277160);

INCLUDE_ASM("asm/nonmatchings/main_078", func_002774F0);

INCLUDE_ASM("asm/nonmatchings/main_078", func_002777F0);

INCLUDE_ASM("asm/nonmatchings/main_078", func_00277C60);

INCLUDE_ASM("asm/nonmatchings/main_078", func_00277CD0);

INCLUDE_ASM("asm/nonmatchings/main_078", func_00278150);

s32 func_002781B0(s32 arg0, s32 arg1, s32 arg2) {
    if (arg2 != 0) {
        return 1;
    }
    if (func_001E2100(arg0, arg1, 2) == 1) {
        return 1;
    }
    return 0;
}

s32 func_002781F0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return func_00278250(func_001DF540(arg0 >> 8, arg0 & 0xFF), arg1, arg2, arg3);
}

INCLUDE_ASM("asm/nonmatchings/main_078", func_00278250);

INCLUDE_ASM("asm/nonmatchings/main_078", func_00278420);

INCLUDE_ASM("asm/nonmatchings/main_078", func_00278510);

INCLUDE_ASM("asm/nonmatchings/main_078", func_002785D0);

INCLUDE_ASM("asm/nonmatchings/main_078", func_002787F0);

void func_00278890(s32 arg0, s32 arg1) {
    if (arg1 == 1) {
        func_001E01F0(arg0);
        return;
    }
    func_001E0150(arg0);
}

typedef struct {
    u8 b[0x18];
} Ent_002788D0;

void *func_002788D0(u16 *arg0, u16 *arg1) {
    u16 idx;

    if ((s64)(u32)(*arg0 + 0x38) > 0x10000) {
        return 0;
    }
    idx = *arg1;
    *arg1 = idx + 1;
    *arg0 += 0x18;
    return &((Ent_002788D0 *)0x01ED0000)[idx];
}

INCLUDE_ASM("asm/nonmatchings/main_078", func_00278930);

INCLUDE_ASM("asm/nonmatchings/main_078", func_002789F0);

INCLUDE_ASM("asm/nonmatchings/main_078", func_00278A90);

INCLUDE_ASM("asm/nonmatchings/main_078", func_00278C80);

INCLUDE_ASM("asm/nonmatchings/main_078", func_00278D20);

s32 func_00278D90(u8 *arg0) {
    s32 index;
    s32 count;

    index = 0;
    count = 0;
    do {
        if (arg0[index] == 0xFF) {
            return count;
        }
        index++;
        count++;
    } while (index < 5);
    return count;
}

void func_00278DD0(u8 *src, u8 *dst) {
    s32 i;

    i = 0;
    do {
        dst[i] = src[i];
        i++;
    } while (i < 5);
}

s32 func_00278E00(u8 value, u8 *values) {
    s32 i;

    i = 0;
    do {
        if (value == values[i]) {
            return 1;
        }
        i++;
    } while (i < 5);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_078", func_00278E40);

INCLUDE_ASM("asm/nonmatchings/main_078", func_00278F10);

s32 func_00279130(s32 arg0, u16 *arg1) {
    u32 temp_s0;

    temp_s0 = func_0026FBB0(*arg1) >> 0x10;
    return (temp_s0 << 0x10) | (func_0026FBB0(*arg1) & 0xFFFF);
}

INCLUDE_ASM("asm/nonmatchings/main_078", func_00279170);

INCLUDE_ASM("asm/nonmatchings/main_078", func_00279230);

INCLUDE_ASM("asm/nonmatchings/main_078", func_002792C0);

INCLUDE_ASM("asm/nonmatchings/main_078", func_002794E0);

INCLUDE_ASM("asm/nonmatchings/main_078", func_00279850);

INCLUDE_ASM("asm/nonmatchings/main_078", func_002798C0);

INCLUDE_ASM("asm/nonmatchings/main_078", func_00279C40);

INCLUDE_ASM("asm/nonmatchings/main_078", func_00279CC0);

INCLUDE_ASM("asm/nonmatchings/main_078", func_0027A090);

INCLUDE_ASM("asm/nonmatchings/main_078", func_0027A130);

INCLUDE_ASM("asm/nonmatchings/main_078", func_0027A360);

INCLUDE_ASM("asm/nonmatchings/main_078", func_0027A710);

INCLUDE_ASM("asm/nonmatchings/main_078", func_0027ABD0);

void func_0027AC70(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp18;
    u8 sp1F;

    sp1F = 0xFF;
    sp18 = 0;
    func_0027ACB0(arg0, &sp18, &sp1F, arg1, arg2, arg3, arg0, 0);
}

INCLUDE_ASM("asm/nonmatchings/main_078", func_0027ACB0);
