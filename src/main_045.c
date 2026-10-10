#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_045", func_001DF540);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001DF580);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001DF5F0);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001DFAF0);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001DFBB0);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001DFD50);

s32 func_001E0110(s32 arg0) {
    s32 temp_s0;

    temp_s0 = func_001E0150(arg0);
    return temp_s0 + func_001E01F0(arg0);
}

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E0150);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E01F0);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E0290);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E02F0);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E0370);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E03D0);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E0450);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E04C0);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E0570);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E05E0);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E0690);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E0700);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E0760);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E07C0);

void *func_001DD130();

static inline u8 *check_001E0830(s32 a0, s32 a1) {
    u8 *p = func_001DD130(a0, a1);
    if (p == NULL) {
        return NULL;
    }
    if (p[0x45] >= 0xB) {
        return NULL;
    }
    return p;
}

s32 func_001E0830(s32 arg0, s32 arg1) {
    u8 *p;

    p = check_001E0830(arg0, arg1);
    if (p != NULL) {
        return p[0x3F];
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E0890);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E08F0);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E0950);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E09E0);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E0B70);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E0C00);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E0C70);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E0C80);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E1030);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E1090);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E10F0);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E11B0);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E1360);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E13C0);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E1420);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E14B0);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E1520);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E1580);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E15E0);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E1640);

void *func_001DD130();

static inline u8 *check_001E16A0(s32 a0, s32 a1) {
    u8 *p = func_001DD130(a0, a1);
    if (p == NULL) {
        return NULL;
    }
    if (p[0x45] >= 0xB) {
        return NULL;
    }
    return p;
}

s32 func_001E16A0(s32 a0, s32 a1, s8 arg2) {
    u8 *p;

    p = check_001E16A0(a0, a1);
    if (p == NULL) {
        return 0;
    }
    p[0x4B] = arg2;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E1700);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E1760);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E17D0);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E1840);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E18A0);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E1900);

INCLUDE_ASM("asm/nonmatchings/main_045", func_001E1970);
